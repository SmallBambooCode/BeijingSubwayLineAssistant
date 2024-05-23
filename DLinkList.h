#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// 节点类
template<typename T>
class Node {
private:
	T data;
	Node<T>* pre;
	Node<T>* next;
public:
	// 构造析构
	Node(Node<T>* next = nullptr, Node<T>* pre = nullptr) {
		this->next = next;
		this->pre = pre;
	}
	Node(const T& data, Node<T>* next = nullptr, Node<T>* pre = nullptr) {
		this->data = data;
		this->next = next;
		this->pre = pre;
	}

	// 节点操作
	Node<T>* getNext() {
		return this->next;
	}
	Node<T>* getPre() {
		return this->pre;
	}
	T getData() {
		return this->data;
	}
	void setNext(Node<T>* next) {
		this->next = next;
	}
	void setPre(Node<T>* pre) {
		this->pre = pre;
	}
	void setData(const T& item) {
		this->data = item;
	}
	// 运算符重载
	bool operator==(Node<T>& obj) {
		if (this->getData() == obj.getData()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(Node<T>& obj) {
		if (this->getData() == obj.getData()) {
			return false;
		}
		else {
			return true;
		}
	}
	friend ostream& operator<< (ostream& out, Node<T>& t) {
		out << t.getData();
		return out;
	}
	friend istream& operator>> (istream& in, Node<T>& t) {
		T temp;
		cin >> temp;
		t.setData(temp);
		return in;
	}
	Node<T>& operator=(Node<T>& obj) {
		this->setData(obj.data);
		this->next = obj.next;
		this->pre = obj.pre;
		return *this;
	}
};

// 双向链表类
template<typename T>
class DLinkList {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	// 构造析构
	DLinkList() {
		head = new Node<T>;
		tail = new Node<T>;
		head->setNext(tail);
		tail->setPre(head);
	}
	DLinkList(const T& data) {
		this->head = new Node<T>;
		this->tail = new Node<T>;
		this->head->setNext(new Node<T>(data));
		tail->setPre(head->getNext());
	}
	DLinkList(const DLinkList<T>& list) {
		// 创建头尾节点
		head = new Node<T>;
		tail = new Node<T>;
		head->setNext(tail);
		tail->setPre(head);

		// 复制list中的所有节点
		Node<T>* temp = list.head->getNext();
		while (temp != list.tail) {
			this->addNode(temp->getData());
			temp = temp->getNext();
		}
	}

	~DLinkList() {
		this->clearList();
		delete this->head;
		delete this->tail;
		this->head = nullptr;
		this->tail = nullptr;
	}
	// 链表操作
	Node<T>* getHead() {
		return this->head;
	}
	Node<T>* getTail() {
		return this->tail;
	}
	bool addNode(T data) {
		Node<T>* newNode = new Node<T>(data);
		Node<T>* temp = head;
		while (temp->getNext() != tail) {
			temp = temp->getNext();
		}
		temp->setNext(newNode);
		newNode->setPre(temp);
		newNode->setNext(tail);
		tail->setPre(newNode);
		return true;
	}
	void printList() {
		Node<T>* temp = head;
		while (temp->getNext() != tail) {
			cout << temp->getNext()->getData() << endl;
			temp = temp->getNext();
		}
		return;
	}
	void rprintList() {
		Node<T>* temp = tail;
		while (temp->getPre() != head) {
			cout << temp->getPre()->getData() << endl;
			temp = temp->getPre();
		}
		return;
	}
	bool deleteNode(T data) {
		Node<T>* temp = tail;
		while (temp->getPre() != head) {
			if (temp->getPre()->getData() == data) {
				Node<T>* toDelete = temp->getPre();
				toDelete->getPre()->setNext(toDelete->getNext());
				toDelete->getNext()->setPre(toDelete->getPre());
				delete toDelete;
				toDelete = nullptr;
				return true;
			}
			temp = temp->getPre();
		}
		return false;
	}
	bool modifyNode(T from, T to) {
		Node<T>* temp = tail;
		while (temp->getPre() != head) {
			if (temp->getPre()->getData() == from) {
				temp->getPre()->setData(to);
				return true;
			}
			temp = temp->getPre();
		}
		return false;
	}
	bool searchNode(T data) {
		Node<T>* temp = tail;
		while (temp->getPre() != head) {
			if (temp->getPre()->getData() == data) {
				return true;
			}
			temp = temp->getPre();
		}
		return false;
	}
	void clearList() {
		Node<T>* toDelete = head->getNext();
		// 遍历链表删除所有节点
		while (toDelete != this->tail) {
			Node<T>* nextNode = toDelete->getNext();
			delete toDelete;
			toDelete = nextNode;
		}
		this->head->setNext(this->tail);
		this->tail->setPre(this->head);
	}
	// 运算符重载
	bool operator==(DLinkList<T>& obj) {
		if (this->head == obj.getHead() && this->tail == obj.tail) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!=(DLinkList<T>& obj) {
		if (this->head == obj.getHead() && this->tail == obj.tail) {
			return false;
		}
		else {
			return true;
		}
	}
	friend ostream& operator<< (ostream& out, DLinkList<T>& t) {
		Node<T>* temp = t.getHead();
		if (temp->getNext() == t.getTail()) {
			return out;
		}
		while (temp->getNext() != t.getTail()) {
			out << temp->getNext()->getData() << endl;
			temp = temp->getNext();
		}
		return out;
	}

	DLinkList<T>& operator=(const DLinkList<T>& list) {
		if (this != &list) {
			// 先清空当前链表
			this->clearList();

			// 复制list中的所有节点
			Node<T>* temp = list.head->getNext();
			while (temp != list.tail) {
				this->addNode(temp->getData());
				temp = temp->getNext();
			}
		}
		return *this;
	}
};