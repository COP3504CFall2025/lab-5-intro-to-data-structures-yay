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
		while(head->next != nullptr){
			std::cout << head->data << endl;
			head = head->next;
		};
	};
	void printReverse() const{
		while(tail->prev != nullptr){
			std::cout << tail->data << endl;
			tail = tail->prev;
		};
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
		head = newHead;
		count++;
	};
	void addTail(const T& data){
		Node* newTail = new Node();
		newTail->data = data;
		newTail->next = nullptr;
		newTail->prev = tail;
		tail = newTail;
		count++;
	};

	// Removal
	bool removeHead(){
		if (head != nullptr){
			delete head;
			head = head->next;
			count--;
		};
	};
	bool removeTail(){
		if (tail != nullptr){
			delete tail;
			tail = tail->prev;
			count--;
		};
	};
	void Clear(){
		while(head->next != nullptr){
			removeHead();
		};
	};

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

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
		int noHead = 0;
		while (current != nullptr) {
			addTail(current->data);
			if(noHead == 0){
				head = tail;
				noHead = 1;
			}
			current = current->next;
			count++;
		};
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


