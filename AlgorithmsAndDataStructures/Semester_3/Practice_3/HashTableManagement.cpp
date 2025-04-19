#include <iostream>
#include <fstream>
#include <string>
#include "HashTableManagement.h" 

using namespace std;

int myhash(int key, int size) {
	int hash = key;
	hash = (hash + hash % 23) * 37;
	hash = hash % size;
	if (hash < 0) hash *= -1;
	return hash;
}

void insert_key(hashtablestruct*& hashtable, int& size, int key, int pos, float& load, float& load_factor) {
	load++;
	load_factor = load / size;
	if (load_factor > LOAD_FACTOR_MAX) {
		cout << "\nLoad factor: " << load_factor << " > " << LOAD_FACTOR_MAX <<", the table has been rehashed\n";
		hashtable = rehash_table(hashtable, size, load, load_factor);
	}

	int hash = myhash(key, size);
	if (hashtable[hash].key == -1) {
		hashtable[hash].key = key;
		hashtable[hash].filepos = pos;
	}
	else {
		hashtablestruct* node = &hashtable[hash];
		while (node->next != NULL) {
			node = node->next;
		}
		hashtablestruct* new_node = new hashtablestruct;
		node->next = new_node;
		new_node->key = key;
		new_node->filepos = pos;
	}
}

hashtablestruct* rehash_table(hashtablestruct* hashtable, int& size, float& load, float& load_factor) {
	load = 0;
	int old_size = size;
	size *= 2;
	hashtablestruct* new_hashtable = new hashtablestruct[size];
	int new_hash;
	hashtablestruct* node;
	for (int i = 0; i < old_size; i++) {
		if (hashtable[i].key != -1) {
			node = &hashtable[i];
			insert_key(new_hashtable, size, node->key, node->filepos, load, load_factor);
			while (node->next) {
				node = node->next;
				insert_key(new_hashtable, size, node->key, node->filepos, load, load_factor);
			}
		}
	}
	delete_hashtable(hashtable, old_size);
	return new_hashtable;
}

int remove(hashtablestruct*& hashtable, int size, int key, float& load, float& load_factor) {
	int hash = myhash(key, size);

	hashtablestruct* node = &hashtable[hash];
	hashtablestruct* deleted_node;
	deleted_node = &hashtable[hash];
	if (node->key != key and node->next) {
		// deleting a node in the middle/end of a list
		while (node->next->key != key and node->next->next) {
			node = node->next;
		}
		if (node->next->key == key) {
			deleted_node = node->next;
			node->next = node->next->next;
			delete deleted_node;
			load--;
			load_factor = load / size;
		}
	}
	// deleting a node at the start of a list
	else if (node->next) {
		hashtable[hash] = *(node->next);
		load--;
		load_factor = load / size;
	}
	else if (node->key == key){
		node->key = -1;
		node->filepos = -1;
		node->next = NULL;
		load--;
		load_factor = load / size;
	}
	else {
		cout << "\nError: Node " << key << " not found\n";
		return 1;
	}
	
	cout << "\nNode with key " << key << " successfully removed from hash table\n";
	return 0;
}

int entry_search(hashtablestruct* hashtable, int size, int key) {
	int hash = myhash(key, size);
	hashtablestruct* node = &hashtable[hash];
	if (hashtable[hash].key != key) {
		while (node->next) {
			node = node->next;
			if (node->key == key) return node->filepos;
		}
	}
	else if (hashtable[hash].key == key) {
		return node->filepos;
	}
	return -1;
}

void display(hashtablestruct* hashtable, int TABLESIZE) {
	cout << "\nhash table:\n" <<
		"[hash]:\t     key|\t filepos|\n" <<
		"=================================\n";
	hashtablestruct* node = &hashtable[0];
	for (int i = 0; i < TABLESIZE; i++) {
		if (hashtable[i].key == -1)
			printf("[%4d]:\n", i);
		else {
			printf("[%4d]:\t%8d|\t%8d|\n", i, hashtable[i].key, hashtable[i].filepos);
			node = &hashtable[i];
			while (node->next) {
				node = node->next;
				printf("[%4d]:\t%8d|\t%8d|\n", i, node->key, node->filepos);
			}
		}
	}
}

void delete_hashtable(hashtablestruct* hashtable, int size) {
	for (int i = 0; i < size; i++) {
		delete_linked_list(hashtable[i].next);
	}
	delete[] hashtable;
}

void delete_linked_list(hashtablestruct* current_node) {
	if (!current_node) return;
	else if (current_node->next) {
		delete_linked_list(current_node->next);
	}
	delete current_node;
}

void testHeshT() {
	cout << "-----Hash table management test-----\n";

	int TABLESIZE = 10;

	//create hash table
	hashtablestruct* hashtable = new hashtablestruct[TABLESIZE];
	hashtablestruct* node;
	hashtablestruct* new_node;

	//Тестовый набор ключей 1
	int testKeys[TEST_COUNT];
	int testPos[TEST_COUNT];
	for (int i = 0; i < TEST_COUNT; i++) {
		testKeys[i] = 1000 + i;
		testPos[i] = 40 * i;
	}

	float load = 0;
	float load_factor = 0;
	//Заполнение хеш-таблицы значениями тестового набора 1
	for (int i = 0; i < TEST_COUNT; i++) {
		insert_key(hashtable, TABLESIZE, testKeys[i], testPos[i], load, load_factor);
	}

	//Вывод таблицы
	display(hashtable, TABLESIZE);

	//Рехеширование до 2х размера и вывод таблицы
	cout << "\nRehashed to 2x the size:";
	hashtable = rehash_table(hashtable, TABLESIZE, load, load_factor);
	display(hashtable, TABLESIZE);

	//Удаление элемента с ключом 1003 из таблицы и ее вывод
	int key = 1003;
	int pos = entry_search(hashtable, TABLESIZE, key);
	if (pos > -1) {
		remove(hashtable, TABLESIZE, key, load, load_factor);
	}
	else cout << "\nError: No element with key " << key << " was found\n";
	display(hashtable, TABLESIZE);

	//Поиск элемента с ключом 1023
	cout << "\nPosition of key 1023 is: " << entry_search(hashtable, TABLESIZE, 1023) << "\n";

	//Вставка элемента с ключом 1003
	insert_key(hashtable, TABLESIZE, key, pos, load, load_factor);
	cout << "\nkey:" << key << " hash:" << myhash(key, TABLESIZE) << " position:" << pos << " successfully inserted" << '\n';
	display(hashtable, TABLESIZE);
	delete_hashtable(hashtable, TABLESIZE);
}