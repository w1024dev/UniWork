// Вариант 5

#include <string>
#include <fstream>
#include <iostream>

#define SIZE 30
#define QUANTITY 100

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

void file_input(string filename) {
	ifstream fs;
	ofstream fs2;
	fs.open(filename);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	fs2.open(filename, ios::trunc);
	string input;
	cout << "Write to file: ";
	getline(cin, input);
	fs2 << input << endl;
	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void file_output_text(string filename) {
	ifstream fs;
	fs.open(filename, ios::in);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	cout << "File contents: \n";
	fs >> cout.rdbuf();

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void create_file_text(string filename) {
	ofstream fs;
	fs.open(filename);
	fs.close();
	fs.open(filename, ios::out | ios::app);
	for (int i = 0; i < 5; i++) {
		fs << 1 << ' ' << 2 << ' ' << 4 << ' ' << 8 << ' ' << 16 << ' ' << 32 << endl;
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	cout << "Created file \"" << filename << "\"\n";
}

void append_string(string filename) {
	ifstream fs;
	ofstream fs2;
	fs.open(filename);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	cout << "Append string to file: ";
	string new_string;
	getline(cin, new_string);
	fs2.open(filename, ios::app);
	fs2 << new_string << endl;

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

int find_number(string filename) {
	int index;
	cout << "Input number position: ";
	cin >> index;
	ifstream fs;
	fs.open(filename);	
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return -1;
	}
	int counter = 0;
	int tempnumber = 0;
	while (fs >> tempnumber)
	{
		if (fs.fail()) {
			cout << "Error opening file." << endl;
			break;
		}
		else counter++;
		if (counter == index) {
			break;
		}
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	printf("Number #%i is: %i\n", counter, tempnumber);
	return tempnumber;
}

int count_numbers(string filename) {
	fstream fs;
	fs.open(filename);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return -1;
	}
	int counter = 0, tempnumber = 0;
	while (fs >> tempnumber)
	{
		if (fs.fail()) break;
		else counter++;
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	printf("%i numbers in total\n", counter);
	return counter;
}

void personal_task_1(string filename) {
	fstream fs, fs2;
	fs.open(filename, ios::in);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}

	int dot = filename.find(".");
	string filename2 = filename.substr(0, dot) + "2" + filename.substr(dot);

	fs2.open(filename2);
	fs2.close();
	fs2.open(filename2, ios::out | ios::trunc);
	int counter = 0, tempnumber = 0, multiplier = 0;
	while (fs >> tempnumber){
		if (fs.fail()) break;
	}
	multiplier = tempnumber;
	fs.clear(ios_base::goodbit);
	fs.seekg(0, ios::beg);

	while (fs >> tempnumber)
	{
		if (fs.fail()) break;
		else fs2 << tempnumber * multiplier << " ";
		counter++;
		if (counter % 6 == 0) fs2 << endl;
	}
	cout << "\nFile \"" << filename << "\":" << endl;
	file_output_text(filename);
	cout << "\nFile \"" << filename2 << "\":" << endl;
	file_output_text(filename2);
	if (file_check(filename) != 0 or file_check(filename2) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void app_txt() {
	cout << "-----TEXT FILE APP-----\n";
	while (1) {
		cout << "\nOptions:\n";
		cout << "1. Create text file\n";
		cout << "2. Read text file\n";
		cout << "3. Write to text file\n";
		cout << "4. Append string to text file\n";
		cout << "5. Find number at arbitrary position in text file\n";
		cout << "6. Count numbers in text file\n";
		cout << "7. Personal task\n";
		cout << "8. Exit app\n";

		int searched_for_number, number_count;
		int choice = 0;
		cin >> choice;
		string filename;
		switch (choice) {
		case 1:
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_check(filename);
			create_file_text(filename);
			break;
		case 2:
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_output_text(filename);
			break;
		case 3:
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_input(filename);
			break;
		case 4:
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			append_string(filename);
			break;
		case 5:
			cout << "Input file name: ";
			cin >> filename;
			searched_for_number = find_number(filename);
			break;
		case 6:
			cout << "Input file name: ";
			cin >> filename;
			number_count = count_numbers(filename);
			break;
		case 7:
			cout << "Input file name: ";
			cin >> filename;
			personal_task_1(filename);
			break;
		case 8:
			return;
		}
	}
}

/*BINARY*/
struct Patient {
	int CardNumber = 0;
	int IllnessCode = 0;
	char DoctorName[SIZE];
};

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

void file_read_entry_bin(string filename) {
	fstream fs;
	fs.open(filename, ios::in | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	int entry_number;
	cout << "Enter number of entry to read: ";
	cin >> entry_number;
	Patient patient_temp;
	int entry_count = 0;
	while (fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp))) {
		entry_count++;
	}
	if (entry_count < entry_number or entry_number <= 0) {
		cout << "Error: Entry not found";
	}
	else {
		fs.close();
		fs.open(filename, ios::in | ios::binary);
		fs.seekp(0 + sizeof(patient_temp) * (entry_number - 1), ios::beg);

		fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
		cout << "Patient data:" << endl
			<< "Card number: " << patient_temp.CardNumber << endl
			<< "Illness code: " << patient_temp.IllnessCode << endl
			<< "Doctor name: " << patient_temp.DoctorName << endl;
	}

	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void file_delete_entry_bin(string filename) {
	Patient patient_temp;
	fstream fs;
	fs.open(filename, ios::in | ios::out | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	int entry_count = 0;
	int entry_number;
	cout << "Enter number of entry to delete: ";
	cin >> entry_number;

	while (fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp))) {
		entry_count++;
		if (entry_count == entry_number) {
			fs.seekp(0 - sizeof(patient_temp), ios::end);
			fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
			fs.seekp(0 + sizeof(patient_temp) * (entry_number - 1), ios::beg);
			fs.write(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
			break;
		}
	}
	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	if (entry_count < entry_number or entry_number <= 0) {
		cout << "Error: Entry not found";
	}
	else {
		cout << "Successfully deleted entry #" << entry_number;
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
	int i = 0,temp = 0;
	while (fs_text >> temp) {
		i++;
		if (i == 1) patient_temp.CardNumber = temp;
		else if (i == 2) {
			patient_temp.IllnessCode = temp;
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
		fs_text << patient_temp.CardNumber << ' ' << patient_temp.IllnessCode << patient_temp.DoctorName << endl;
	}
	if (file_check(filename) != 0 or file_check(filename2) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	return filename2;
}

string personal_task_2_1(string filename) {
	Patient patient_temp;
	fstream fs, fs2;
	fs.open(filename, ios::in | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return "Error";
	}
	int illness_code, i = 0;
	cout << "\nInput illness code to sort patients by: ";
	cin >> illness_code;
	string illness_string = to_string(illness_code);
	char const* illness_char = illness_string.c_str();

	int dot = filename.find(".");
	string filename2 = filename.substr(0, dot) + "_illness_" + illness_char + filename.substr(dot);
	fs2.open(filename2);
	fs2.close();
	fs2.open(filename2, ios::out);
	while (fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp))) {
		if (patient_temp.IllnessCode == illness_code) {
			fs2.write(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
			i++;
		}
	}
	cout << "\nCreated file \"" << filename2 << "\" with " << i << " entries\n";

	if (file_check(filename) != 0 or file_check(filename2) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
	return filename2;
}

void personal_task_2_2(string filename) {
	fstream fs;
	fs.open(filename, ios::in | ios::out | ios::binary);
	if (!fs) {
		cout << "\nFile does not exist" << endl;
		return;
	}
	cout << "\nEnter number of patient accounts to update: ";
	int quantity_actual;
	cin >> quantity_actual;
	int patients[QUANTITY];
	for (int j = 0; j < quantity_actual; j++) {
		cout << "\nEnter patient ID: ";
		cin >> patients[j];
	}

	int i, pos, count = 0;
	char doctor_name[SIZE];
	Patient patient_temp;

	getchar();
	for (i = 0; i < quantity_actual; i++) {
		while (fs.read(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp))) {
			if (patient_temp.CardNumber = patients[i]) {
				pos = fs.tellp();
				fs.seekp(pos - sizeof(patient_temp));
				cout << "\nInput new doctor name for patient " << patients[i] << ": ";
				cin.getline(doctor_name, SIZE);
				strcpy_s(patient_temp.DoctorName, doctor_name);
				fs.write(reinterpret_cast<char*>(&patient_temp), sizeof(patient_temp));
				count++;
				break;
			}
		}
	}
	cout << "\nSuccessfully updated " << count << " patient accounts!\n";
	if (file_check(filename) != 0) {
		cout << "Error occured\n";
		exit(1);
	}
}

void app_bin() {
	cout << "-----BINARY FILE APP-----\n";
	while (1) {
		cout << "\nOptions:\n";
		cout << "1. Create binary file\n";
		cout << "2. Read binary/text file\n";
		cout << "3. Write to binary file\n";
		cout << "4. Append to binary file\n";
		cout << "5. Read specific entry by index\n";
		cout << "6. Delete specific entry by index\n";
		cout << "7. Text file to bin file\n";
		cout << "8. Bin file to text file\n";
		cout << "9. Personal task 1\n";
		cout << "10. Personal task 2\n";
		cout << "11. Exit app\n";


		int choice = 0;
		cin >> choice;
		string filename, filename2, filename3;
		switch (choice) {
		case 1:							//Create binary file
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_check(filename);
			create_file_bin(filename);
			break;
		case 2:							//Read binary/text file
			cout << "Input file name: ";
			cin >> filename;
			getchar();	
			if (filename.find("bin") != std::string::npos) {
				file_output_bin(filename);
			}
			else {
				file_output_text(filename);
			}
			break;
		case 3:							//Write to binary file
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_input_bin(filename);
			break;
		case 4:							//Append to binary file
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_add_bin(filename);
			break;
		case 5:							//Read specific entry by index
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_read_entry_bin(filename);
			break;
		case 6:							//Delete specific entry by index
			cout << "Input file name: ";
			cin >> filename;
			getchar();
			file_delete_entry_bin(filename);
			break;
		case 7:							//Text file to bin file
			cout << "Input file name: ";
			cin >> filename;
			filename2 = file_text_to_bin(filename);
			cout << "New file name: " << filename2;
			break;
		case 8:							//Bin file to text file
			cout << "Input file name: ";
			cin >> filename;
			filename3 = file_bin_to_text(filename);
			cout << "New file name: " << filename3;
			break;
		case 9:							//Personal task 1
			cout << "Input file name: ";
			cin >> filename;	
			personal_task_2_1(filename);
			break;
		case 10:						//Personal task 2
			cout << "Input file name: ";
			cin >> filename;
			personal_task_2_2(filename);
			break;
		case 11:						//Exit app
			return;
		}
	}	
}

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа №2 \"Внешние структуры данных: текстовый и двоичный файлы\". Демидов М.Д.\n";
	app_txt();
	app_bin();
	return 0;
}
