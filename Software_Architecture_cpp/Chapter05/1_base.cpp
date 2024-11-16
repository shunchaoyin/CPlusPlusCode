#include <string>
#include <iostream>
#include <optional>
#include <chrono>
#include <iomanip>
#include <vector>
#include <gsl/pointers>

using namespace std::chrono_literals;

using CustomerId = int;
CustomerId get_current_customer_id() { return 42; }

struct Merchant
{
    int id;
};

struct Item
{
    std::string name;
    std::optional<std::string> photo_url;
    std::string description;
    std::optional<float> price;
    std::chrono::time_point<std::chrono::system_clock> data_added{};
    bool featured{};
};
std::ostream &operator<<(std::ostream &os, const Item &item)
{
    auto stringify_optional = [](const auto &optional)
    {
        using optional_value_type = typename std::__remove_cvref_t<decltype(optional)>::value_type;
        if constexpr (std::is_same_v<optional_value_type, std::string>)
        {
            return optional ? *optional : "missing";
        }
        else
        {
            return optional ? std::to_string(*optional) : "missing";
        }
    };
    auto time_added = std::chrono::system_clock::to_time_t(item.data_added);

    os << "name" << item.name
       << ",photo_url:" << stringify_optional(item.photo_url)
       << ",description:" << item.description
       << ",price:" << stringify_optional(item.price)
       << ",data_added" << std::put_time(std::localtime(&time_added), "%c %Z")
       << ", featured" << item.featured
       << "\n";

    return os;
}

enum class Category
{
    Food,
    Antiques,
    Books,
    Music,
    Photography,
    Handicraft,
    Artist,
};

struct Store
{
    gsl::not_null<const Merchant *> owner;
    std::vector<Item> items;
    std::vector<Category> categories;
};

using Stores = std::vector<gsl::not_null<const Store *>>;

Stores get_favorate_stores_for(const CustomerId &customer_id)
{
    static const auto merchants = std::vector<Merchant>{{17}, {19}};
    static const auto stores = std::vector<Store>{
        {&merchants[0],
         {
             {"Honey", {}, "Straight outta Compton's apiary", 9.99f, std::chrono::system_clock::now(), false},
             {"Oscypek", {}, "Tasty smoked cheese from the Tatra mountains", 1.23f, std::chrono::system_clock::now() - 1h, true},
         },
         {Category::Food}},
        {&merchants[1],
         {
             {"Handmade painted ceramic bowls", "http://example.com/beautiful_bowl.png", "Hand-crafted and hand-decorated bowls made of fired clay", {}, std::chrono::system_clock::now() - 12min, true},
         },
         {Category::Artist, Category::Handicraft}}};

    static auto favorite_stores_by_customer =
        std::unordered_map<CustomerId, Stores>{{42, {&stores[0], &stores[1]}}};
    return favorite_stores_by_customer[customer_id];
}

using Items = std::vector<gsl::not_null<const Item *>>;

Items get_featured_items_for_store(const Store &store)
{
    Items items_featured;
    for (const auto &item : store.items)
    {
        if (item.featured)
        {
            items_featured.push_back(&item);
        }
    }
    return items_featured;
}

Items get_all_featured_items(const Stores &stores)
{
    Items items_featured{};
    for (const auto &store : stores)
    {
        auto items_store_featured = get_featured_items_for_store(*store);
        items_featured.reserve(items_store_featured.size() + items_featured.size());
        std::copy(std::begin(items_store_featured),
                  std::end(items_store_featured),
                  std::back_inserter(items_featured));
    }
    return items_featured;
}

void order_items_by_date_added(Items &items)
{
    auto date_compare = [](auto &left, auto &right)
    {
        return left->data_added > right->data_added;
    };
    std::sort(std::begin(items), std::end(items), date_compare);
}

void render_item_gallery(const Items &items)
{
    for (const auto &item : items)
    {
        std::cout <<*item << "\n";
    }
}

int main()
{
    auto fav_stores = get_favorate_stores_for(get_current_customer_id());

    auto selected_items = get_all_featured_items(fav_stores);

    order_items_by_date_added(selected_items);

    render_item_gallery(selected_items);
}