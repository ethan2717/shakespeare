// Filename: bard.cpp
//
// This is the main wrapper for the LinkedList class.
//
// Ethan Yeung, October 2022

#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <cstring>

int main(int argc, char** argv) {
	if (argc != 3) {
		throw std::invalid_argument("Usage: ./bard <INPUT FILE> <OUTPUT FILE>");
	}

	LinkedList arr[32];
	// I used this resource:
	// https://www.tutorialspoint.com/read-file-line-by-line-using-cplusplus
	fstream infile;
	infile.open("shakespeare-cleaned5.txt", ios::in);
	if (infile.is_open()) {
		string word;
		while (getline(infile, word)) {
			arr[word.length() - 5].insert(word);
		}
	}
	for (int i = 0; i < 32; i++) {
		if (i == 20 || i == 21 || (i > 22 && i < 31)) {
			arr[i].insert("-");
		} else {
			arr[i].sortAll();
		}
	}
	for (int i = 0; i < 32; i++) {
		Node *curr = arr[i].getHead();
		int r = 0;
		while (curr) {
			curr->rank = r;
			curr = curr->next;
			r++;
		}
	}

	ifstream input1;
	input1.open(argv[1]);
	string line;
	int queries = 0;
	while (getline(input1, line)) {
		queries++;
	}

	ifstream input2;
	input2.open(argv[1]);
	char *line_ca, *dummy; // create character arrays to be used with strtok and strtol
	int lengths[queries], ranks[queries];
	int i = 0;
	while (getline(input2, line)) {
		line_ca = strdup(line.c_str());
		lengths[i] = strtol(strtok(line_ca, " "), &dummy, 10); // split line up, then convert first portion to int
		ranks[i] = strtol(strtok(NULL, " "), &dummy, 10); // split line up, then convert second portion to int
		i++;
	}

	
	ofstream output;
	output.open(argv[2]);
	for (int i = 0; i < queries; i++) {
		int length = lengths[i], rank = ranks[i];
		// for lengths with no words, output a "-" and short circuit back to the start of the loop
		if (length < 5 || length == 25 || length == 26 || (length > 27 && length < 36) || length > 36) {
			output << "-" << endl;
			continue;
		}
		LinkedList currLL = arr[length - 5];
		Node *curr = currLL.getHead();
		while (curr) {
			if (rank == curr->rank) {
				output << curr->word << endl;
			}
			if (!(curr->next) && rank > curr->rank) {
				output << "-" << endl;
			}
			curr = curr->next;
		}
	}
	output.close();
	infile.close();
	input1.close();
	input2.close();
}