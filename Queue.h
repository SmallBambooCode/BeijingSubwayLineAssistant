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
	int front;  // ��ͷ�±�
	int rear;  // ��β�±�
public:
	// ��������
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
	// ���в���
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
			// ����
			this->memExpand();
		}
		this->base[this->rear] = data;
		this->rear = (this->rear + 1) % this->size;
		// cout << "��ӣ�" << data << endl;
		return true;
	}
	bool DeQueue() {
		// �ӿ��������
		if (this->front == this->rear) {
			return false;
		}
		// cout << "���ӣ�" << this->getHeadElem() << endl;
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
	// �ڴ���չ
	bool memExpand() {
		// �Ѿɵ��ڴ�ռ������
		T* oldData = this->base;
		// size����һ���������µ��ڴ�ռ�
		this->size *= 2;
		this->base = new T[this->size];
		// ���������
		// ��ͷ�±���ڶ�β
		if (front > rear) {
			// ��ʱ��Ҫ�ȰѶ�β���ռ俪ʼ�Ĳ��ָ��Ƶ��¿ռ���ǰ
			// memcpy(this->base, oldData, sizeof(T) * (this->rear));
			for (int i = 0; i < this->rear; ++i) {
				this->base[i] = oldData[i];
			}
			// �ٰѶ�ͷ���ռ�����Ĳ��ָ��Ƶ��¿ռ����
			// memcpy(this->base + (this->size / 2 + this->front), oldData + this->front, sizeof(T) * (this->size / 2 - this->front));
			for (int i = 0; i < this->size / 2 - this->front; ++i) {
				(this->base + (this->size / 2 + this->front))[i] = (oldData + this->front)[i];
			}
			this->front = this->size / 2 + this->front;
		}
		// ��ͷ�±�С�ڵ��ڶ�β
		else {
			// ��ʱ��Ҫ�Ѿɿռ�Ӷ�ͷ��ʼ�����ݣ���СΪ��β����ͷ����֮ǰ�Ĵ�С%֮ǰ�Ĵ�С�����Ƶ��µĴ洢�ռ���
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
	// ���е����ػ����е���ĵ�
	// ��sb memcpy��˭��˭���ӣ�����һ����bug�����memcpy�Ĺ�
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
	// ���������
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