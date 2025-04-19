#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define SIZE 30

int file_check(string filename);

struct Patient {
	int CardNumber = 0;
	int IllnessCode = 0;
	char DoctorName[SIZE];
};

void create_file_bin(string filename);

void file_output_bin(string filename);

void file_input_bin(string filename);

void file_add_bin(string filename);

Patient file_read_entry_bin(string filename, int index, bool display = 0);

void file_delete_entry_bin(string filename, int key);

string file_text_to_bin(string filename);

string file_bin_to_text(string filename);

void testBinF();