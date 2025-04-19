// Вариант 5

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string bitout(unsigned int x, int r)
{
	string result;
	for (int i = 0; i < r; i++)
	{
		if (x % 2 == 1) result = "1" + result;
		else result = "0" + result;
		x /= 2;
	}
	return result;
}

unsigned int b_to_dec(string bin)
{
	unsigned int result = 0;
	reverse(bin.begin(), bin.end());
	int end = -1;
	for (int k = 0; k < bin.length(); k++)
	{
		if (bin[k] == '1') end = k;
	}
	if (bin.find('1') != -1)
	{
		for (int i = 0; i <= end; i++)
		{
			if (bin[i] == '1') 
			{
				result += pow(2, i);
			}
		}
	}
	return result;
}
int task_1()
{
	// 17, 15, 1 бит сделать единицей
	unsigned int n = 0x0A;
	cout << "c = " << setw(20) << bitout(n, 32) << " <- Изначальное число (" << b_to_dec(bitout(n, 32)) << ")" << endl;
	unsigned int mask = 0b101000000000000010;
	return n | mask;
}

int task_2(unsigned int x)
{
	// с 5-го три справа обнулить
	unsigned int mask = 0b011100;
	return x & ~mask;
}

int task_3(unsigned int x)
{
	return x << 6;
}

int task_4(unsigned int x)
{
	return x >> 6;
}

int task_5(unsigned int x, int n)
{
	unsigned int mask2 = 1 << 31; //Единица, сдвинутая влево на 31 разряд. Используем unsigned, т. к. иначе первый бит занят знаком
	mask2 = mask2 >> (32 - n - 1); // mask1 = ~mask1 - инвертирование
	return x & ~mask2;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа №1 \"Поразрядные операции и их применение\". Демидов М.Д.\n";
	cout << "Задание 1\n";
	unsigned int c = task_1();
	unsigned int n;

	cout << "c = " << setw(20) << bitout(c, 32) << " <- Число после работы функции (" << b_to_dec(bitout(c, 32)) << ")" << endl;
	unsigned int x;

	cout << "Задание 2\nВведите число: ";
	cin >> x;
	cout << "c = " << setw(20) << bitout(x, 32) << " <- Изначальное число (" << b_to_dec(bitout(x, 32)) << ")" << endl;
	c = task_2(x);
	cout << "c = " << setw(20) << bitout(c, 32) << " <- Число после работы функции (" << b_to_dec(bitout(c, 32)) << ")" << endl;
	cin.clear();

	cout << "Задание 3\nВведите число: ";
	cin >> x;
	cout << "c = " << setw(20) << bitout(x, 32) << " <- Изначальное число (" << b_to_dec(bitout(x, 32)) << ")" << endl;
	c = task_3(x);
	cout << "c = " << setw(20) << bitout(c, 32) << " <- Число после работы функции (" << b_to_dec(bitout(c, 32)) << ")" << endl;
	cin.clear();

	cout << "Задание 4\nВведите число: ";
	cin >> x;
	cout << "c = " << setw(20) << bitout(x, 32) << " <- Изначальное число (" << b_to_dec(bitout(x, 32)) << ")" << endl;
	c = task_4(x);
	cout << "c = " << setw(20) << bitout(c, 32) << " <- Число после работы функции (" << b_to_dec(bitout(c, 32)) << ")" << endl;
	cin.clear();

	cout << "Задание 5\nВведите число: ";
	cin >> x;
	cin.clear();
	cout << "Введите номер разряда, который необходимо обнулить: ";
	cin >> n;
	cout << "c = " << setw(20) << bitout(x, 32) << " <- Изначальное число (" << b_to_dec(bitout(x, 32)) << ")" << endl;
	c = task_5(x, n);
	cout << "c = " << setw(20) << bitout(c, 32) << " <- Число после работы функции (" << b_to_dec(bitout(c, 32)) << ")" << endl;

	return 0;
}