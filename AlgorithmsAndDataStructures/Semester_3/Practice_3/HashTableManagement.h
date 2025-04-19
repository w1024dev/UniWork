#pragma once
#include <iostream>
#include <fstream>
#include <string>

const float LOAD_FACTOR_MAX = 3.0;
const int TEST_COUNT = 50;

struct hashtablestruct {
	int key = -1;
	int filepos = -1;
	hashtablestruct* next = NULL;
};

int myhash(int key, int size);

void insert_key(hashtablestruct*& hashtable, int& size, int key, int pos, float& load, float& load_factor);

hashtablestruct* rehash_table(hashtablestruct* hashtable, int& size, float& load, float& load_factor);

int remove(hashtablestruct*& hashtable, int size, int key, float& load, float& load_factor);

int entry_search(hashtablestruct* hashtable, int size, int key);

void display(hashtablestruct* hashtable, int TABLESIZE);

void delete_hashtable(hashtablestruct* hashtable, int size);

void delete_linked_list(hashtablestruct* current_node);

void testHeshT();