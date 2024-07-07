#include <stdlib.h>
#define DEFAULT_CAPACITY 10
#define DEFAULT_EXPAND_FACTOR 2
#define DEFAULT_SHRINK_FACTOR 0.5
class Array
{
private:
    int *_elems = NULL;
    int _capacity;
    int _size;

private:
    void copyFrom(int const *A, int low, int high);
    void expand();
    void shrink();
    void exchange(int a, int b);
    int find(int e, int low, int high) const;

public:
    Array(int c = DEFAULT_CAPACITY, int s = 0, int v = 0);
    Array(int const *A, int size);
    Array(int const *A, int low, int high);
    Array(const Array &v);
    ~Array();
    int &operator[](int i) const;
    int size() const;
    int capacity() const;
    bool isEmpty() const;
    bool isOrdered() const;
    bool find(int e) const;
    int binarySearch(int e) const;
    int remove(int low, int high);
    int insert(int pos, int e);
    void push_back(int e);
    void sort(); // bubble sort
    void shuffle();
    void print();
};
