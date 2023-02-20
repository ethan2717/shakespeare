// Filename: linkedlist.cpp
//
// Ethan Yeung, October 2022

#include "linkedlist.h"
#include <string>
#include <iostream>

using namespace std;

LinkedList :: LinkedList() {
	head = NULL;
}

// returns the head node of the linked list
// why? what did you think it did, you dirty dog??
Node *LinkedList :: getHead() {
	return head;
}

// places a node containing the word at the front of the linked list
// or increments the word's count by 1 if it's already in the list
void LinkedList :: insert(string word) {
	Node *found = find(word);
	if (found) {
		found->count++;
	} else {
		Node *to_add = new Node;
		to_add->word = word;
		to_add->count = 1;
		to_add->next = head;
		head = to_add;
	}
}

// searches the linked list for a word and returns its node when found
// returns NULL if word not found
Node *LinkedList :: find(string word) {
	Node *curr = head;
	while (curr) {
		if (curr->word == word) {
			return curr;
		}
		curr = curr->next;
	}
	return NULL;
}

// uses the following functions to sort everything
void LinkedList :: sortAll() {
	head = sortNumer(head);
	head = sortLexi(head);
}

// places words in correct numerical order
void LinkedList :: insertNumer(Node *a, Node *b) {
	while (a->next && a->next->count < b->count) {
		a = a->next;
	}
	b->next = a->next;
	a->next = b;
}

// calls insertNumer to sort linked list and keep track of sorted words
Node *LinkedList :: sortNumer(Node *a) {
	Node *head = new Node;
	while (a) {
		Node *b = a;
		a = a->next;
		insertNumer(head, b);
	}
	return head->next;
}

// places words in correct lexicographic order
void LinkedList :: insertLexi(Node *a, Node *b) {
	while ((a->next) && ((a->next->word > b->word) == 0) && (a->next->count == b->count)) {
		a = a->next;
	}
	b->next = a->next;
	a->next = b;
}

// calls insertLexi to sort linked list and keep track of sorted words
Node *LinkedList :: sortLexi(Node *a) {
	Node *head = new Node;
	while (a) {
		Node *b = a;
		a = a->next;
		insertLexi(head, b);
	}
	return head->next;
}