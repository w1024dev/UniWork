#include <iostream>
#include <fstream>
#include <string>
#include "HashTableManagement.h"
#include "BinaryFileManagement.h"
#include "BinFileMngmntViaHT.h"
#include <chrono>

using namespace std;


Patient linear_search(string filename, int key) {
	Patient patient_temp;
	fstream fs;
	fs.open(filename, ios::in | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return patient_temp;
	}
	while (patient_temp.CardNumber != key) {
		fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
	}
	fs.close();
	return patient_temp;
}

void app() {
	string filename[] = {"longfile.bin", "longestfile.bin"};

	Patient patient_temp;

	int choice = 0;
	int choice2 = 0;

	//ќсновна€ хеш-таблица
	float load = 0;
	float load_factor = 0;
	int size = 10;
	hashtablestruct* hashtable = new hashtablestruct[size];

	//’еш-таблица дл€ подсчета времени доступа к записи
	float load2 = 0;
	float load_factor2 = 0;
	int size2 = 10;
	hashtablestruct* hashtable2 = new hashtablestruct[size2];

	while (1) {
		cout << "\nOptions:\n";
		cout << "1. Create hash table from longfile.bin\n";
		cout << "2. Remove entry from file and hashtable\n";
		cout << "3. Find entry in file through hash table\n";
		cout << "4. Measure access times for direct access vs linear search\n";
		cout << "5. Exit app\n";

		cin >> choice;

		switch (choice) {
		case 1:
			for (int i = 1; i < 51; i++) {
				read_entry_into_hashtable(filename[0], hashtable, size, i, load, load_factor);
			}
			display(hashtable, size);
			break;
		case 2:
			cout << "\nInput key of entry to delete: ";
			cin >> choice2;
			file_hashtable_remove_entry(filename[0], hashtable, size, choice2, load, load_factor);
			display(hashtable, size);
			break;
		case 3:
			cout << "\nInput key of entry to find: ";
			cin >> choice2;
			patient_temp = file_hashtable_find_entry(filename[0], hashtable, size, choice2);
			if (patient_temp.CardNumber != 0) {
				cout << "\nPatient data:" << endl
					<< "Card number: " << patient_temp.CardNumber << endl
					<< "Illness code: " << patient_temp.IllnessCode << endl
					<< "Doctor name: " << patient_temp.DoctorName << endl;
			}
			break;
		case 4: {
			for (int i = 1; i < 501; i++) {
				read_entry_into_hashtable(filename[1], hashtable2, size2, i, load2, load_factor2);
			}
			display(hashtable2, size2);

			//First element
			cout << "\nTime to access first element directly:  ";
			auto start{ chrono::steady_clock::now() }; //начало замера времени
			patient_temp = file_hashtable_find_entry(filename[1], hashtable2, size2, 1000);
			auto end{ chrono::steady_clock::now() }; //конец замера времени
			chrono::duration<double> elapsed_seconds{ end - start };
			printf("%21fs\n", elapsed_seconds);

			cout << "\nTime to access first element through linear search:  ";
			start = chrono::steady_clock::now(); //начало замера времени
			patient_temp = linear_search(filename[1], 1000);
			end = chrono::steady_clock::now(); //конец замера времени
			elapsed_seconds = end - start;
			printf("%fs\n", elapsed_seconds);

			cout << "\nPatient data:" << endl
				<< "Card number: " << patient_temp.CardNumber << endl
				<< "Illness code: " << patient_temp.IllnessCode << endl
				<< "Doctor name: " << patient_temp.DoctorName << endl;

			//Median element
			cout << "\nTime to access median element directly: ";
			start = chrono::steady_clock::now(); //начало замера времени
			patient_temp = file_hashtable_find_entry(filename[1], hashtable2, size2, 1249);
			end = chrono::steady_clock::now(); //конец замера времени
			elapsed_seconds = end - start;
			printf("%21fs\n", elapsed_seconds);

			cout << "\nTime to access median element through linear search: ";
			start = chrono::steady_clock::now(); //начало замера времени
			patient_temp = linear_search(filename[1], 1249);
			end = chrono::steady_clock::now(); //конец замера времени
			elapsed_seconds = end - start;
			printf("%fs\n", elapsed_seconds);

			cout << "\nPatient data:" << endl
				<< "Card number: " << patient_temp.CardNumber << endl
				<< "Illness code: " << patient_temp.IllnessCode << endl
				<< "Doctor name: " << patient_temp.DoctorName << endl;

			//Last element
			cout << "\nTime to access last element directly:   ";
			start = chrono::steady_clock::now(); //начало замера времени
			patient_temp = file_hashtable_find_entry(filename[1], hashtable2, size2, 1499);
			end = chrono::steady_clock::now(); //конец замера времени
			elapsed_seconds = end - start;
			printf("%21fs\n", elapsed_seconds);

			cout << "\nTime to access last element through linear search:   ";
			start = chrono::steady_clock::now(); //начало замера времени
			patient_temp = linear_search(filename[1], 1499);
			end = chrono::steady_clock::now(); //конец замера времени
			elapsed_seconds = end - start;
			printf("%fs\n", elapsed_seconds);

			cout << "\nPatient data:" << endl
				<< "Card number: " << patient_temp.CardNumber << endl
				<< "Illness code: " << patient_temp.IllnessCode << endl
				<< "Doctor name: " << patient_temp.DoctorName << endl;
		}
			break;
		case 5:
			return;
		}
	}
	delete_hashtable(hashtable, size);
	delete_hashtable(hashtable2, size2);
}


int main() {
	
	setlocale(LC_ALL, "Russian");
	cout << "Ћабораторна€ работа є3 \n\"ѕрименение хеш-таблицы дл€ поиска данных в двоичном файле с запис€ми фиксированной длины.\" ƒемидов ћ.ƒ.";

	//testHeshT();
	//testBinF();

	app();

	//—оздание тестового файла 500 записей длиной
	/*
	string filename = "longestfile.bin";
	fstream fs;
	fs.open(filename, ios::binary | ios::out | ios::trunc);
	Patient temp;
	strcpy_s(temp.DoctorName, "name");

	for (int i = 0; i < 500; i++) {
		temp.CardNumber = 1000 + i;
		temp.IllnessCode = 100 + (i % 4);
		fs.write(reinterpret_cast<char*>(&temp), sizeof(Patient));
	}
	fs.close();
	
	file_output_bin(filename);*/

	return 0;
}
