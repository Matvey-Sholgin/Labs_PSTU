// lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

using namespace std;

//проверка что состоит только из чисел
bool onlyNumber(char* str, char delims[])
{
	char* mas;
	mas = strtok(str, delims);
	int count = 0;
	while (mas) {

		//если есть что то кроме чисел
		return false;
	}

	//только символы
	return true;
}

//проверка что в массиве нет таких элементов
bool addUnique(char* result[255], int count, char element[])
{
	for (int i = 0; i < count; i++)
	{
		if (strcmp(result[i], element) == 0) {

			return false;
		}
	}

	return true;
}

int main()
{
	//Функция уснавливает локаль(русские буквы) консоли
	setlocale(0, "");
	// Преобразовать строку так, чтобы все слова в ней стали идентификаторами, слова состоящие только из цифр - удалить.
	const int maxLenght = 255;
	char numbers[11] = "1234567890";
	char str[maxLenght];

	cout << "\nВведите текст не более 255 символов:\n";
	cin.get(str, maxLenght);

	char delims[] = "., ?.!";
	char* mas;

	//все слова
	char* all[255];
	//http://cppstudio.com/post/747/
	mas = strtok(str, delims);
	int countNumber = 0;
	while (mas) {
		all[countNumber++] = _strdup(mas);
		mas = strtok(NULL, delims);
	}

	//слова резулирующие (уникальные и без числе)
	char* result[255];

	int j = 0;
	for (int i = 0; i < countNumber; i++)
	{
		if (!onlyNumber(all[i], numbers) && addUnique(result, j, all[i]))
		{
			result[j++] = _strdup(all[i]);
		}
	}

	cout << "\nРезультирующие слова:\n";
	for (int i = 0; i < j; i++)
	{
		cout << result[i] << " ";
	}


}
