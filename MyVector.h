#pragma once
#include <iostream>
using namespace std;

template <typename T>
class MyVector {
private:
    // ָ��̬���������
    T* base;
    // ��������
    int capacity;
    // ��ǰԪ������
    int current;

public:
    // ���캯������ʼ��Ϊ1����������
    MyVector() {
        base = new T[1];
        capacity = 1;
        current = 0;
    }
    // ���ι��캯������ָ���ĳ�ʼֵ��������ʼ��Ԫ��
    MyVector(int initCapacity, const T& initValue) {
        base = new T[initCapacity];
        capacity = initCapacity;
        current = initCapacity;
        for (int i = 0; i < initCapacity; i++) {
            base[i] = initValue;
        }
    }
    // �������캯��
    MyVector(const MyVector& other) {
        capacity = other.capacity;
        current = other.current;
        base = new T[capacity];
        for (int i = 0; i < current; i++) {
            base[i] = other.base[i];
        }
    }
    // ��������������̬������ڴ�
    ~MyVector() {
        delete[] base;
        base = nullptr;
    }
    // ������β�����Ԫ��
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
    // �Ƴ�����β����Ԫ��
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
    // ��ȡ��ǰԪ�ظ���
    int size() {
        return current;
    }
    // ��ȡ����
    int getcapacity() {
        return capacity;
    }
    // ����һ��ָ��������Ԫ�ص�ָ��
    T* begin() {
        return base;
    }
    // ����һ��ָ������β��Ԫ�ص�ָ��
    T* end() {
        return base + current;
    }
    // �ж������Ƿ�Ϊ��
    bool empty() {
        return current == 0;
    }
    // �����±������������ʹ�������±���ʷ�ʽ
    T& operator[](int index) {
        return base[index];
    }
    // ���ظ�ֵ�����
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