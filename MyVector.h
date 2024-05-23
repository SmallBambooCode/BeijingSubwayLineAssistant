#pragma once
#include <iostream>
using namespace std;

template <typename T>
class MyVector {
private:
    // 指向动态分配的数组
    T* base;
    // 容器容量
    int capacity;
    // 当前元素数量
    int current;

public:
    // 构造函数，初始化为1容量的数组
    MyVector() {
        base = new T[1];
        capacity = 1;
        current = 0;
    }
    // 带参构造函数，用指定的初始值和容量初始化元素
    MyVector(int initCapacity, const T& initValue) {
        base = new T[initCapacity];
        capacity = initCapacity;
        current = initCapacity;
        for (int i = 0; i < initCapacity; i++) {
            base[i] = initValue;
        }
    }
    // 拷贝构造函数
    MyVector(const MyVector& other) {
        capacity = other.capacity;
        current = other.current;
        base = new T[capacity];
        for (int i = 0; i < current; i++) {
            base[i] = other.base[i];
        }
    }
    // 析构函数，清理动态分配的内存
    ~MyVector() {
        delete[] base;
        base = nullptr;
    }
    // 向容器尾部添加元素
    void push_back(T data) {
        if (current == capacity) {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = base[i];
            }
            delete[] base;
            capacity *= 2;
            base = temp;
        }
        base[current] = data;
        current++;
    }
    // 移除容器尾部的元素
    void pop_back() {
        current--;
    }
    void erase(int index) {
        if (index >= 0 && index < current) {
            for (int i = index; i < current - 1; i++) {
                base[i] = base[i + 1];
            }
            current--;
        }
        else {
            return;
        }
    }
    // 获取当前元素个数
    int size() {
        return current;
    }
    // 获取容量
    int getcapacity() {
        return capacity;
    }
    // 返回一个指向数组首元素的指针
    T* begin() {
        return base;
    }
    // 返回一个指向数组尾后元素的指针
    T* end() {
        return base + current;
    }
    // 判断容器是否为空
    bool empty() {
        return current == 0;
    }
    // 重载下标操作符，允许使用数组下标访问方式
    T& operator[](int index) {
        return base[index];
    }
    // 重载赋值运算符
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] base;

            capacity = other.capacity;
            current = other.current;
            base = new T[capacity];
            for (int i = 0; i < current; i++) {
                base[i] = other.base[i];
            }
        }
        return *this;
    }
};