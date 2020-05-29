#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <array>
#include <list>
#include <functional>

//This program uses closed hashing.
//Each array index stores a linked list.
//    **takes about a minute to read from
//    **this large file size
//
//My hashing algorithm is effiecient b/c
//no matter how many indexes there are,
//closed hashing allows for objects to be 
//chained together and not worry about 
//collisions.
//
//In terms of my hashing algorithm, I 
//chose a fairly simple algorithm to
//demonstrate the efficiency of chaining
//large amounts of information
//
//Jaydon Hashimoto
//CST-201
//Hash Tables

class HashElement {
private:
	int hash;
	std::string key;
	int value;
	HashElement *next;
	HashElement *head = NULL;

public:
	HashElement(int h, std::string k, int v) {
		this->key = k;
		this->hash = h;
		this->value = v;
		this->next = NULL;
	}

	//getters and setters

	void setHead(HashElement *h) {
		head = h;
	}

	int getValue() {
		return value;
	}

	std::string getKey() {
		return key;
	}

	int getHash() {
		return hash;
	}

	void incValue() {
		this->value += 1;
	}

	HashElement *getNext() {
		return next;
	}

	void setNext(HashElement *e) {
		this->next = e;
	}
};

//this struct is used to sort by value
struct HashE
{
	int hash;
	std::string key;
	int value;

	//constructor
	HashE(int h, std::string k, int v) :
		hash(h), key(k), value(v){}

	//compare values
	bool operator <(const HashE & h) const
	{
		return value > h.value;
	}
};

class HashTable {
private:
	HashElement **table;
	std::list<HashE> mylist;
	std::list<HashE>::iterator it;
	int size;

public:
	//constructor
	HashTable(int s) {
		size = s;
		table = new HashElement*[size];
		for (int i = 0; i < size; ++i) {
			table[i] = NULL;
		}
	}
	//destuctor
	~HashTable() {
		for (int i = 0; i < size; i++)
			if (table[i] != NULL) {
				HashElement *prev = NULL;
				HashElement *hashE = table[i];
				while (hashE != NULL) {
					prev = hashE;
					hashE = hashE->getNext();
					delete prev;
				}
			}
		delete[] table;
	}

	void insert(std::string key) {
		int hash = calcHash(key);
		//check collision
		if (table[hash] != NULL) {
			//if hash matches, check value
			HashElement *current = table[hash];
			//if key exists, increment value
			while (current->getNext() != NULL && current->getKey() != key) {
				current = current->getNext();
			}
			if (current->getKey() == key) {
				current->incValue();
			}
			else
				//else, append to linked list
				current->setNext(new HashElement(hash, key, 1));
		}
		else {
			//if hash not found, insert new hash
			table[hash] = new HashElement(hash, key, 1);
			table[hash]->setHead(table[hash]);
		}
	}

	int calcHash(std::string key) {
		//hash == total of first three letters
		int *initValues;
		int arrayL;
		int hash;

		if (key.length() == 1) {
			initValues = new int[1];
			arrayL = 1;
		} 
		else if(key.length() == 2) {
			initValues = new int[2];
			arrayL = 2;
		}
		else {
			initValues = new int[3];
			arrayL = 3;
		}
		for (int i = 0; i < arrayL; ++i) {
			switch (key.at(i)) {
			case 'a': case 'A': initValues[i] = 1; break;
			case 'b': case 'B': initValues[i] = 2; break;
			case 'c': case 'C': initValues[i] = 3; break;
			case 'd': case 'D': initValues[i] = 4; break;
			case 'e': case 'E': initValues[i] = 5; break;
			case 'f': case 'F': initValues[i] = 6; break;
			case 'g': case 'G': initValues[i] = 7; break;
			case 'h': case 'H': initValues[i] = 8; break;
			case 'i': case 'I': initValues[i] = 9; break;
			case 'j': case 'J': initValues[i] = 10; break;
			case 'k': case 'K': initValues[i] = 11; break;
			case 'l': case 'L': initValues[i] = 12; break;
			case 'm': case 'M': initValues[i] = 13; break;
			case 'n': case 'N': initValues[i] = 14; break;
			case 'o': case 'O': initValues[i] = 15; break;
			case 'p': case 'P': initValues[i] = 16; break;
			case 'q': case 'Q': initValues[i] = 17; break;
			case 'r': case 'R': initValues[i] = 18; break;
			case 's': case 'S': initValues[i] = 19; break;
			case 't': case 'T': initValues[i] = 20; break;
			case 'u': case 'U': initValues[i] = 21; break;
			case 'v': case 'V': initValues[i] = 22; break;
			case 'w': case 'W': initValues[i] = 23; break;
			case 'x': case 'X': initValues[i] = 24; break;
			case 'y': case 'Y': initValues[i] = 25; break;
			case 'z': case 'Z': initValues[i] = 26; break;
			default: initValues[i] = 26; break;
			}
		}

		if (key.length() == 1) {
			hash = initValues[0];
		}
		else if (key.length() == 2) {
			hash = initValues[0] + initValues[1];
		}
		else {
			hash = initValues[0] + initValues[1] + initValues[2];
		}
		return hash;
	}

	int searchValue(std::string key) {
		//retrieve occurence value
		int hash = calcHash(key);
		if (table[hash] == NULL) {
			return -1;
		}
		else {
			HashElement *newElement = table[hash];		
			if (newElement == NULL)
				return -1;
			else
				return newElement->getValue();
		}
	}

	int searchHash(std::string key) {
		//retrieve hash value
		int hash = calcHash(key);
		if (table[hash] == NULL) {
			return -1;
		}
		else {
			HashElement *newElement = table[hash];			
			if (newElement == NULL)
				return -1;
			else
				return newElement->getHash();
		}
	}

	void sort() {
		//copy all hashtable elements into a list
		int i = 0;
		while (i < size) {
			HashElement *current = table[i];
			if (table[i] != NULL) {
				while (current != NULL) {
					mylist.push_front(HashE(current->getHash(), 
						current->getKey(), current->getValue()));
					current = current->getNext();
				}
			}
			++i;
		}
		//sort elements
		mylist.sort();	
	}

	void printSorted() {
		//iterate through sorted list and print top 10
		int count = 1;
		for (it = mylist.begin(); it != mylist.end(); ++it) {
			std::cout << count << ": hash = " << it->hash << 
				", key = " << it->key << " - " << it->value << std::endl;
			++count;
			if (count == 11) {
				return;
			}
		}
	}

	void print() {
		//go through all elements in the hashtable 
		//and print each attribute
		int count = 0;
		int i = 0;
		while (i < size) {
			HashElement *current = table[i];
			if (table[i] != NULL) {
				while (current != NULL) {
					std::cout << count << ": " << "hash: " << current->getHash() << " | key: "
						<< current->getKey() << " | value: "
						<< current->getValue() << std::endl;
					current = current->getNext();
					++count;
				}
			}
			++i;
		}	
	}
};

//**this is code from the professor**
void remove_punct(std::string& str) {
	str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
		return std::ispunct(static_cast<unsigned char>(c)); }
		), str.end());
};

int main()
{
	HashTable *ht = new HashTable(81);
	std::string word;

	std::ifstream infile("C:/CST201/CLC3/bible.txt");
	//if file is accessable
	if (infile.is_open()) {
		while (infile >> word) {
			if (word != "") {
				//remove punctuation
				remove_punct(word);

				//insert
				if (word != "") {
					ht->insert(word);
				}
			}
		}
	}
	else {
		std::cout << "cannot open file" << std::endl;
	}

	//prints all
	//ht->print();

	//sort and print
	ht->sort();
	ht->printSorted();

    return 0;
}

