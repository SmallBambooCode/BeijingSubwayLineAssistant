#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

template<typename T>
class ArrayQueue {
private:
	T* base;
	int size;
	int front;  // 队头下标
	int rear;  // 队尾下标
public:
	// 构造析构
	ArrayQueue() {
		this->base = new T[2];
		this->front = this->rear = 0;
		this->size = 2;
	}
	ArrayQueue(const T& data) {
		this->base = new T[2];
		this->front = this->rear = 0;
		this->size = 2;
		this->base[this->rear] = data;
		this->rear = (this->rear + 1) % this->size;
	}
	ArrayQueue(ArrayQueue<T>& Queue) {
		this->size = Queue.size;
		this->base = new T[this->size];
		this->front = Queue.front;
		this->rear = Queue.rear;
		for (int i = Queue.front; i != Queue.rear; i = (i + 1) % Queue.size) {
			this->base[i] = Queue.base[i];
		}
	}
	~ArrayQueue() {
		this->ClearQueue();
		delete[] this->base;
		this->base = nullptr;
	}
	// 队列操作
	int getFront() {
		return this->front;
	}
	int getRear() {
		return this->rear;
	}
	int getSize() {
		return this->size;
	}
	T* getBase() {
		return this->base;
	}
	T& getHeadElem() {
		return this->base[this->front];
	}
	bool QueueEmpty() {
		if (((this->rear - this->front + this->size) % this->size) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	int QueueLength() {
		return (this->rear - this->front + this->size) % this->size;
	}
	bool EnQueue(T data) {
		if ((this->rear + 1) % this->size == this->front) {
			// 扩容
			this->memExpand();
		}
		this->base[this->rear] = data;
		this->rear = (this->rear + 1) % this->size;
		// cout << "入队：" << data << endl;
		return true;
	}
	bool DeQueue() {
		// 队空无需出队
		if (this->front == this->rear) {
			return false;
		}
		// cout << "出队：" << this->getHeadElem() << endl;
		this->front = (this->front + 1) % this->size;
		if (this->QueueLength() < this->size / 2 && this->size > 2) {
			this->memShrink();
		}
		return true;
	}
	bool PrintQueue() {
		for (int i = this->front; i != this->rear; i = (i + 1) % this->size) {
			cout << this->base[i] << endl;
		}
		return true;
	}
	void ClearQueue() {
		while (this->DeQueue());
		return;
	}
	// 内存扩展
	bool memExpand() {
		// 把旧的内存空间存起来
		T* oldData = this->base;
		// size扩大一倍并开辟新的内存空间
		this->size *= 2;
		this->base = new T[this->size];
		// 分情况讨论
		// 队头下标大于队尾
		if (front > rear) {
			// 这时需要先把队尾到空间开始的部分复制到新空间最前
			// memcpy(this->base, oldData, sizeof(T) * (this->rear));
			for (int i = 0; i < this->rear; ++i) {
				this->base[i] = oldData[i];
			}
			// 再把队头到空间结束的部分复制到新空间最后
			// memcpy(this->base + (this->size / 2 + this->front), oldData + this->front, sizeof(T) * (this->size / 2 - this->front));
			for (int i = 0; i < this->size / 2 - this->front; ++i) {
				(this->base + (this->size / 2 + this->front))[i] = (oldData + this->front)[i];
			}
			this->front = this->size / 2 + this->front;
		}
		// 队头下标小于等于队尾
		else {
			// 这时需要把旧空间从队头开始的内容（大小为队尾减队头加上之前的大小%之前的大小）复制到新的存储空间中
			// memcpy(this->base, oldData + this->front, sizeof(T) * ((this->rear - this->front + this->size / 2) % (this->size / 2)));
			for (int i = 0; i < ((this->rear - this->front + this->size / 2) % (this->size / 2)); ++i) {
				this->base[i] = (oldData + this->front)[i];
			}
			this->rear = this->rear - this->front;
			this->front = 0;
		}
		delete[] oldData;
		oldData = nullptr;
		return true;
	}
	// 队列的缩回还是有点恶心的
	// 这sb memcpy，谁用谁被坑，改了一下午bug结果是memcpy的锅
	// https://blog.csdn.net/weixin_66151870/article/details/128511415
	bool memShrink() {
		T* oldData = this->base;
		this->size /= 2;
		this->base = new T[this->size];

		if (front > rear) {
			//memmove(this->base, oldData, sizeof(T) * this->rear);
			for (int i = 0; i < this->rear; ++i) {
				this->base[i] = oldData[i];
			}
			//memmove(this->base + (this->front - this->size), oldData + this->front, sizeof(T) * (this->size * 2 - this->front));
			for (int i = 0; i < (this->size * 2 - this->front); ++i) {
				(this->base + (this->front - this->size))[i] = (oldData + this->front)[i];
			}
			this->front = this->front - this->size;
		}
		else {
			//memmove(this->base, oldData + this->front, sizeof(T) * ((this->rear - this->front + this->size * 2) % (this->size * 2)));
			for (int i = 0; i < ((this->rear - this->front + this->size * 2) % (this->size * 2)); ++i) {
				this->base[i] = (oldData + this->front)[i];
			}
			this->rear = this->rear - this->front;
			this->front = 0;
		}

		delete[] oldData;
		oldData = nullptr;
		return true;
	}
	// 运算符重载
	bool operator==(ArrayQueue<T>& obj) {
		if (this->base == obj.getBase()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(ArrayQueue<T>& obj) {
		if (this->base == obj.getBase()) {
			return false;
		}
		else {
			return true;
		}
	}
	friend ostream& operator<< (ostream& out, ArrayQueue<T>& t) {
		if (t.QueueEmpty()) {
			return out;
		}
		for (int i = t.getFront(); i != t.getRear(); i = (i + 1) % t.getSize()) {
			out << t.getBase()[i] << endl;
		}
		return out;
	}
	ArrayQueue<T>& operator=(ArrayQueue<T>& obj) {
		this->base = obj.getBase();
		this->front = obj.getFront();
		this->rear = obj.getRear();
		this->size = obj.getSize();
		return *this;
	}
};