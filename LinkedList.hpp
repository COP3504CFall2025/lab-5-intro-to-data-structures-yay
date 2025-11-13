#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
		T data;
		Node* prev;
		Node* next;
	};
	// Behaviors
	void printForward() const{
		Node* current = head;
		while(current != nullptr){
			std::cout << current->data << endl;
			current = current->next;
		}
	};
	void printReverse() const{
		Node* current = tail;
		while(current != nullptr){
			std::cout << current->data << endl;
			current = current->prev;
		}
	};

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	};
	Node* getHead(){
		return head;
	};
	const Node* getHead() const{
		return head;
	};
	Node* getTail(){
		return tail;
	};
	const Node* getTail() const{
		return tail;
	};

	// Insertion
	void addHead(const T& data){
		Node* newHead = new Node();
		newHead->data = data;
		newHead->next = head;
		newHead->prev = nullptr;
		if (head) head->prev = newHead;
		else tail = newHead;
		head = newHead;
		count++;
	};
	void addTail(const T& data){
		Node* newTail = new Node();
		newTail->data = data;
		newTail->next = nullptr;
		newTail->prev = tail;
		if (tail) tail->next = newTail;
		else head = newTail;
		tail = newTail;
		count++;
	};

	// Removal
	bool removeHead(){
		if (head == nullptr) return false;
		Node* temp = head;
		head = head->next;
		if (head) head->prev = nullptr;
		else tail = nullptr;
		delete temp;
		count--;
		return true;
	};
	bool removeTail(){
		if (tail == nullptr) return false;
		Node* temp = tail;
		tail = tail->prev;
		if (tail) tail->next = nullptr;
		else head = nullptr;
		delete temp;
		count--;
		return true;
	};
	void Clear(){
		while(head != nullptr){
			removeHead();
		}
	};
	void clear(){
		Clear();
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if(this == &other){
			return *this;
		}
		if(head != nullptr){
			Clear();
		}
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if(this == &rhs){
			return *this;
		}
		if(head != nullptr){
			Clear();
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* current = rhs.head;
		while (current != nullptr) {
			addTail(current->data);
			current = current->next;
		}
		return *this;
	};

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;
	};
	LinkedList(const LinkedList<T>& list){
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node* current = list.head;
		while (current != nullptr) {
			addTail(current->data);
			current = current->next;
		}
	};
	LinkedList(LinkedList<T>&& other) noexcept{
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	};
	~LinkedList(){
		Clear();
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


