#include <iostream>
#include <fstream>
#include <string>
#include "BinaryFileManagement.h"

#define SIZE 30

using namespace std;

int file_check(string filename) {
	fstream fs(filename);
	if (!fs.is_open()) {
		return -1;
	}

	if (fs.good()) {
		fs.close();
		return 0;
	}
	else {
		fs.close();
		return -2;
	}
}

void create_file_bin(string filename) {
	Patient patient;
	ofstream fs;
	fs.open(filename);
	fs.close();
	fs.open(filename, ios::out | ios::trunc | ios::binary);

	char empty = 'N';
	cout << "\nCreate empty file? (Y/N) ";
	cin >> empty;
	if (empty == 'N') {
		char default_name[SIZE] = "name_";
		for (int i = 0; i < 5; i++) {
			default_name[5] = static_cast<char>(i + 49);
			patient = { 1000 + i, 100 + (i % 3) };
			strncpy_s(patient.DoctorName, default_name, SIZE);
			fs.write(reinterpret_cast<char*>(&patient), sizeof(patient));
		}
	}
	else if (empty != 'Y') {
		cout << "\nError: Invalid input";
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	cout << "Created file \"" << filename << "\"\n";
}

void file_output_bin(string filename) {
	Patient patient_temp;
	int i = 0;
	ifstream fs;
	fs.open(filename, ios::in | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	while (fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp))) {
		cout << "Patient " << i + 1 << ": " << endl
			<< "Card number: " << patient_temp.CardNumber << endl
			<< "Illness code: " << patient_temp.IllnessCode << endl
			<< "Doctor name: " << patient_temp.DoctorName << endl;
		i++;
	}
	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void file_input_bin(string filename) {
	Patient patient_temp;
	ifstream fs;
	fs.open(filename, ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	ofstream fs2;
	fs2.open(filename, ios::binary | ios::trunc);
	cout << "How many entries to add? ";
	int num;
	cin >> num;
	char ar[SIZE];
	for (int i = 0; i < num; i++) {
		cout << "\nEnter card number: ";
		cin >> patient_temp.CardNumber;
		cout << "Enter illness code: ";
		cin >> patient_temp.IllnessCode;
		cout << "Enter doctor name (<" << SIZE << " characters): ";
		getchar();
		cin.getline(ar, SIZE);
		strcpy_s(patient_temp.DoctorName, ar);
		fs2.write(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void file_add_bin(string filename) {
	Patient patient_temp;
	ifstream fs;
	fs.open(filename, ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	ofstream fs2;
	fs2.open(filename, ios::binary | ios::app);
	cout << "How many entries to add? ";
	int num;
	cin >> num;
	char ar[SIZE];
	for (int i = 0; i < num; i++) {
		cout << "\nEnter card number: ";
		cin >> patient_temp.CardNumber;
		cout << "Enter illness code: ";
		cin >> patient_temp.IllnessCode;
		cout << "Enter doctor name (<" << SIZE << " characters): ";
		getchar();
		cin.getline(ar, SIZE);
		strcpy_s(patient_temp.DoctorName, ar);
		fs2.write(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

Patient file_read_entry_bin(string filename, int index, bool display) {
	Patient patient_temp;
	fstream fs;
	fs.open(filename, ios::in | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return patient_temp;
	}

	//Определение количества записей в файле
	fs.seekg(0, ios_base::end);
	int size = fs.tellg();
	fs.seekg(0, ios_base::beg);

	//Если позиция выходит за пределы файла
	if (index * sizeof(Patient) > size or index <= 0) {
		cout << "\nError: Entry not found in file\n";
	}

	else {
		fs.seekp(0 + sizeof(Patient) * (index - 1), ios::beg);

		fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
		if (display) {
			cout << "\nPatient data:" << endl
				<< "Card number: " << patient_temp.CardNumber << endl
				<< "Illness code: " << patient_temp.IllnessCode << endl
				<< "Doctor name: " << patient_temp.DoctorName << endl;
		}
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	return patient_temp;
}

void file_delete_entry_bin(string filename, int key) {
	Patient patient_temp;
	fstream fs;
	fs.open(filename, ios::in | ios::out | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	bool deleted = false;
	int position = 0;

	fs.seekg(0, ios_base::end);
	int size = fs.tellg();
	fs.seekg(0, ios_base::beg);

	while (fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(Patient))) {
		if (patient_temp.CardNumber == key) {
			deleted = true;
			fs.seekg(-1 * sizeof(Patient), ios_base::cur);
			position = fs.tellg();
			if (size != position + sizeof(Patient)) {
				while (position < size) {
					fs.seekp(position + sizeof(Patient));
					fs.read((char*)&patient_temp, sizeof(Patient));
					fs.seekg(-2 * sizeof(Patient), ios_base::cur);
					fs.write((char*)&patient_temp, sizeof(Patient));
					position += sizeof(Patient);
				}
			}
			fs.close();
			//delete last entry;
			ofstream fout("temp.bin", ios::binary | ios::trunc);
			ifstream fin(filename, ios::binary);
			position = 0;
			while (position < size - sizeof(Patient)) {
				fin.read(reinterpret_cast<char*>(&patient_temp), sizeof(Patient));
				fout.write(reinterpret_cast<char*>(&patient_temp), sizeof(Patient));
				position = fin.tellg();
			}
			fin.close();
			fout.close();
			const char* file = filename.c_str();
			remove(file);
			rename("temp.bin", file);
			break;
		}
	}
	if (!deleted) {
		cout << "\nError: Entry not found";
	}
	else {
		cout << "\nEntry successfully deleted from file";
	}
	if (file_check(filename) != 0) {
		cout << "\nError occured\n";
		exit(1);
	}
}

string file_text_to_bin(string filename) {
	Patient patient_temp;
	ifstream fs_text;
	ofstream fs_bin;
	fs_text.open(filename, ios::in);
	if (!fs_text) {
		cout << "\nFile does not exist" << endl;
		return "Error";
	}
	int dot = filename.find(".");
	string filename2 = filename.substr(0, dot) + ".bin";
	fs_bin.open(filename2);
	fs_bin.close();
	fs_bin.open(filename2, ios::out | ios::binary);
	int i = 0, temp = 0;
	while (fs_text >> temp) {
		i++;
		if (i == 1) patient_temp.CardNumber = temp;
		else if (i == 2) {
			patient_temp.IllnessCode = temp;
			fs_text.get();
			fs_text.get(patient_temp.DoctorName, SIZE, '\n');
			fs_bin.write(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
			i = 0;
		}
	}
	if (file_check(filename) != 0 or file_check(filename2) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	return filename2;
}

string file_bin_to_text(string filename) {
	Patient patient_temp;
	ofstream fs_text;
	ifstream fs_bin;
	fs_bin.open(filename, ios::out | ios::binary);
	if (!fs_bin) {
		cout << "\nFile does not exist" << endl;
		return "Error";
	}
	int dot = filename.find(".");
	string filename2 = filename.substr(0, dot) + "1.txt";
	fs_text.open(filename2);
	fs_text.close();
	fs_text.open(filename2, ios::in);
	while (fs_bin.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp))) {
		fs_text << patient_temp.CardNumber << ' ' << patient_temp.IllnessCode << ' ' << patient_temp.DoctorName << endl;
	}

	if (file_check(filename) != 0 or file_check(filename2) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	fstream fs;
	fs.open(filename2);
	cout << ".txt file contents: \n";
	fs >> cout.rdbuf();
	file_check(filename2);
	return filename2;
}

void testBinF() {
	cout << "\n-----Binary file management test-----";
	cout << "\nCreate new file:";
	create_file_bin("testfile.bin");
	cout << "\nFile contents:\n";
	file_output_bin("testfile.bin");

	cout << "\nWrite new data to file:\n";
	file_input_bin("testfile.bin");
	cout << "\nFile contents:\n";
	file_output_bin("testfile.bin");
	cout << "\nAdd new data to file:\n";
	file_add_bin("testfile.bin");
	cout << "\nFile contents:\n";
	file_output_bin("testfile.bin");

	cout << "\nRead specific entry:\n";
	int entry_number;
	cout << "Enter number of entry to read: ";
	cin >> entry_number;
	file_read_entry_bin("testfile.bin", entry_number, 1);
	cout << "\nDelete entry with specific key: ";
	cin >> entry_number;
	file_delete_entry_bin("testfile.bin", entry_number);
	cout << "\nFile contents:\n";
	file_output_bin("testfile.bin");

	cout << "\n.bin to .txt file and then new .txt to .bin file:\n";
	string file_copy = file_bin_to_text("testfile.bin");
	file_copy = file_text_to_bin(file_copy);
	cout << "\nNew .bin file contents:\n";
	file_output_bin(file_copy);
}