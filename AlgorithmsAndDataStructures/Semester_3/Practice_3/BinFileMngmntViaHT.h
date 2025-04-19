#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "HashTableManagement.h"
#include "BinaryFileManagement.h"
#include <chrono>


void read_entry_into_hashtable(string filename, hashtablestruct*& hashtable, int& hashtableSize, int index, float& load, float& load_factor);

void file_hashtable_remove_entry(string filename, hashtablestruct* hashtable, int hashtableSize, int key, float& load, float& load_factor);

Patient file_hashtable_find_entry(string filename, hashtablestruct* hashtable, int hashtableSize, int key);