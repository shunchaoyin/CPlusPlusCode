// 1. 为什么程序1-7的交换函数没有把实参的值交换？
// 原因：形参x和y是值传递，函数内交换的只是x和y的副本，不影响主调函数中的实参。
// 修改方式：使用引用传递（&）。

void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

// 2. 模板函数count：返回数组中数值为value的元素个数
#include <iostream>
template<typename T>
int count(const T* a, int n, T value) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == value) ++cnt;
    }
    return cnt;
}

// 3. 模板函数fill：给数组a[start:end)赋值value
#include <algorithm>
template<typename T>
void fill(T* a, int start, int end, T value) {
    for (int i = start; i < end; ++i) {
        a[i] = value;
    }
}

// 4. 模板函数inner_product：返回数组a和b的内积

template<typename T>
T inner_product(const T* a, const T* b, int n) {
    T result = 0;
    for (int i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// 5. 模板函数iota：a[i] = value + i

template<typename T>
void iota(T* a, int n, T value) {
    for (int i = 0; i < n; ++i) {
        a[i] = value + i;
    }
}

// 6. 模板函数is_sorted：判断数组是否有序（升序）

template<typename T>
bool is_sorted(const T* a, int n) {
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i - 1]) return false;
    }
    return true;
}

// 7. 模板函数mismatch：返回a[i] != b[i]的最小索引

template<typename T>
int mismatch(const T* a, const T* b, int n) {
    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) return i;
    }
    return -1; // 全部相同
}

// 8. 下面两个函数具有不同签名吗？为什么？
// 是的，它们有不同的返回类型，虽然参数类型和数量相同。
// 在C++中，函数签名由函数名和参数类型构成，不包括返回类型，所以它们不是不同签名函数，不能因为返回类型不同而重载。

int abc(int a, int b, int c); // 合法
//float abc(int a, int b, int c); // 非法，重定义

// 测试代码（可选部分）
#include <cassert>
int main() {
    int a[5] = {1, 2, 2, 3, 2};
    assert(count(a, 5, 2) == 3);

    fill(a, 0, 5, 7);
    for (int i = 0; i < 5; ++i) assert(a[i] == 7);

    int b[3] = {1, 2, 3}, c[3] = {4, 5, 6};
    assert(inner_product(b, c, 3) == 32);

    iota(a, 5, 10);
    for (int i = 0; i < 5; ++i) assert(a[i] == 10 + i);

    assert(is_sorted(a, 5));

    int d[5] = {10, 11, 12, 99, 14};
    assert(mismatch(a, d, 5) == 3);

    int x = 1, y = 2;
    swap(x, y);
    assert(x == 2 && y == 1);

    return 0;
}