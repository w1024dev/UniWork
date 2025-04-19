#include <iostream>
#include <fstream>
#include <string>
#include "HashTableManagement.h"
#include "BinaryFileManagement.h"
#include "BinFileMngmntViaHT.h"
#include <chrono>

using namespace std;

void read_entry_into_hashtable(string filename, hashtablestruct*& hashtable, int& hashtableSize, int index, float& load, float& load_factor) {
	Patient patient_temp;
	fstream fs;
	fs.open(filename, ios::in | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	fs.close();
	
	patient_temp = file_read_entry_bin(filename, index);
	if (patient_temp.CardNumber == 0) return;
	insert_key(hashtable, hashtableSize, patient_temp.CardNumber, (index-1)*sizeof(Patient), load, load_factor);
}

void file_hashtable_remove_entry(string filename, hashtablestruct* hashtable, int hashtableSize, int key, float& load, float& load_factor) {
	file_delete_entry_bin(filename, key);
	remove(hashtable, hashtableSize, key, load, load_factor);
}

Patient file_hashtable_find_entry(string filename, hashtablestruct* hashtable, int hashtableSize, int key) {
	int pos = entry_search(hashtable, hashtableSize, key);
	return file_read_entry_bin(filename, pos / sizeof(Patient) + 1);
}