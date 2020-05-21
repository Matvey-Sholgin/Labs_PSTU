// lab11.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

struct point
{
	int key;
	point* next;
	point* prev;
};
//Для каждого вариант разработать следующие функции:
//  1. Создание списка.
//  2. Добавление элемента в список(в соответствии со своим вариантом).
//  3. Удаление элемента из списка(в соответствии со своим вариантом).
//  4. Печать списка.
//  5. Запись списка в файл.
//  6. Уничтожение списка.
//  7. Восстановление списка из файла.

//Записи в линейном списке содержат ключевое поле типа int. Сформировать двунаправленный список. Удалить из него К элементов перед элементом с заданным номером, добавить К элементов в конец списка.

//Создание списка.
point* make_point(int n)
{
	point* first, * p;
	first = NULL;
	for (int i = n; i > 0; i--)
	{
		p = new(point);
		if (first != NULL)
		{
			first->prev = p;
		}
		p->key = i;
		p->next = first;
		p->prev = NULL;
		first = p;
	}
	return first;
}

//Печать списка.
point* print_point(point* first)
{
	std::cout << "\nПечать списка\n";
	if (first == NULL)
	{
		std::cout << "Элеметов нет\n";

		return NULL;
	}
	point* p = first;
	while (p != NULL)
	{
		//Подробный вывод для проверки
		/*std::cout << p->key << "(";
		if (p->prev == NULL) std::cout << "NULL"; else std::cout << p->prev->key;
		std::cout << ",";
		if (p->next == NULL) std::cout << "NULL"; else std::cout << p->next->key;
		std::cout << ") ";*/
	
		//Простой вывод
		std::cout << p->key << " ";
		p = p->next;
	}
	std::cout << "\n";

	return first;
}

// Удаление элемента из списка(в соответствии со своим вариантом).
point* delete_point(point* first, int j, int k) {
	std::cout << "\nУдаление элемента из списка\n";

	if (first == NULL)
	{

		return NULL;
	}
	point* p = first;
	while (p != NULL)
	{
		if (p->key == j)
		{
			std::cout << "\n";
			for (int i = 0; i < k; i++)
			{
				struct point* prev, * next;
				prev = p->prev; // узел, предшествующий lst
				next = p->next; // узел, следующий за lst

				if (prev != NULL)
				{
					prev->next = p->next; // переставляем указатель
				}
				else
				{
					if (next != NULL)
					{
						next->prev = NULL;
					}
					delete p;

					return next;
				}

				if (next != NULL)
				{
					next->prev = p->prev; // переставляем указатель
				}

				delete p; // освобождаем память удаляемого элемента

				p = prev;
			}
		}
		p = p->next;
	}

	return first;
}

//добавить К элементов в конец списка
point* add_point(point* first, int k) {
	std::cout << "\nДобавить элементов в конец списка\n";

	if (first == NULL)
	{
		return make_point(k);
	}
	point* last = first;
	do 
	{		
		if (last->next == NULL) {
			point* p;
			for (int i = 0; i < k; i++)
			{
				p = new(point);

				p->key = last->key + 1;
				p->next = NULL;
				p->prev = last;
				last->next = p;
				last = p;
			}
		}
		last = last->next;
	} while (last != NULL);

	return first;
}

// Запись списка в файл
void saveFile(point* first) {
	std::cout << "\nЗапись списка в файл\n";

	FILE* fp;
	fopen_s(&fp, "save.txt", "w+b");
	if (fp == NULL) {
		perror("\nошибка при открытии файла(Запись)");
		exit(0);
	}

	if (first != NULL)
	{
		point* p = first;
		while (p != NULL)
		{
			point* pointNew = new (point);
			pointNew->next = NULL;
			pointNew->prev = NULL;
			pointNew->key = p->key;

			// записываем запись е в файл
			fwrite(&pointNew, sizeof(point), 1, fp);
			p = p->next;
		}
	}

	fclose(fp);
}

// Уничтожение списка.
point* delete_all_point(point* first) {
	std::cout << "\nУничтожение списка\n";

	if (first == NULL)
	{
		std::cout << "\n";

		return NULL;
	}

	point* p = first;
	point* prev = NULL;
	while (p != NULL)
	{
		prev = p->prev;
		p->prev = NULL;
		p = p->next;

		if (prev != NULL)
		{
			delete prev;
		}
		
	}

	return NULL;
}

//Восстановление списка из файла
point* restore_all_point() {
	std::cout << "\nВосстановление списка из файла\n";

	FILE* fp;
	fopen_s(&fp, "save.txt", "r+b");

	if (fp == NULL) {
		perror("\nошибка при открытии файла(Восстановление) ");
		exit(0);
	}
	point* first, *last, * p;
	first = NULL;
	last = NULL;
	while (!feof(fp))
	{
		int count = fread(&p, sizeof(point), 1, fp);

		if (count > 0)
		{			
			if (first == NULL)
			{		
				first = p;
			}
	
			p->next = NULL;
			p->prev = last;
			if (last != NULL)
			{			
				last->next = p;
			}
			
			last = p;
		}
	}
	fclose(fp);

	return first;
}

int main()
{
	setlocale(0, "");
	int n, k, j;
	point* first;
	std::cout << "\nВведите количество элементов: ";
	std::cin >> n;
	first = make_point(n);
	print_point(first);

	std::cout << "\nВведите номер элемента перед которым удалятся К элеменотов: ";
	std::cin >> j;

	std::cout << "\nВведите К количество элементов которые нужно удалить: ";
	std::cin >> k;

	first = delete_point(first, j, k);
	print_point(first);

	first = add_point(first, k);
	print_point(first);

	saveFile(first);
	first = delete_all_point(first);
	print_point(first);

	first = restore_all_point();
	print_point(first);

}
