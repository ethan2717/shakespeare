// Filename: linkedlist.h
//
// Ethan Yeung, October 2022

#include <string>

using namespace std;

struct Node {
	string word;
	int count, rank;
	Node *next;
};

class LinkedList {
	private:
		Node *head;
	public:
		LinkedList();
		Node *getHead();
		void insert(string);
		Node *find(string);
		void sortAll();
		void insertNumer(Node *, Node *);
		Node *sortNumer(Node *);
		void insertLexi(Node *, Node *);
		Node *sortLexi(Node *);
};

