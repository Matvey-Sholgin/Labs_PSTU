// lab10.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

// Функции для формирования массива(n-строки m-столбцов )
int** makeMatr(int n, int m)
{
    int** matr;
	matr = new int*[n];
    for (int i = 0; i < n; i++)
    {
        // сразу выделемил для расширения
        matr[i] = new int[m + 1];
        for (int j = 0; j < m; j++)
            matr[i][j] = rand()%10;
    }
    return matr;
}

// печати массива(n-строки m-столбцов )

void printMatr(int n, int m, int** matr)
{
    std::cout << "\nПечать массива\n";

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
		{
            std::cout << matr[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// преобразования массива(n-строки m-столбцов к-номер столбца который нужно добавить)
void transformationsMatr(int n, int m, int k, int** matr)
{
    std::cout << "\nПреобразование массива\n";
	int mNew = m + 1;
    for (int i = 0; i < n; i++)
    {
        int prevCol;
        for (int j = 0; j < mNew; j++)
        {
            //рассматриваем только столбцы больше чем k
            if (j == k || j > k)
			{
                
                if (j == k) 
                //первая встреча для замены
                {
                    prevCol = matr[i][j];
                    matr[i][j] = 123;
                }
                else
                {
                    if (j == m)
                    // последняя колонка(которую добавили) вставляем из заранее сохраненной
                    {
						matr[i][j] = prevCol;

                    }
                    else
                    // заменяем что было в предыдущей и сохраняем что в этой для вставки в следующую
                    {
                        int col = prevCol;
                        prevCol = matr[i][j];
                        matr[i][j] = col;
                    }
                    
                }
            }
        }
    }
}

// удаления массива
void deleteMatr(int n, int** matr) {
    std::cout << "\nУдаление массива\n";
    for (int i = 0; i < n; i++)
        delete matr[i];
    delete[] matr;
}

int main(void)
{
    // Сформировать двумерный массив.Добавить в него столбец с заданным номером
    setlocale(0, "");
    int n, m, k;

    std :: cout << "Введите количество строк: ";
    std :: cin >> n;
    std :: cout << "Введите количество столбцов: ";
	std :: cin >> m;

    int** matr = makeMatr(n, m);

    printMatr(n, m, matr);

    do 
    {
    std::cout << "\nВведите номер столбца который нужно добавить: ";
    std::cin >> k;
    } while (k == 0 || m<k);

    transformationsMatr(n, m, k-1, matr);

	printMatr(n, m + 1, matr);

    deleteMatr(n, matr);
}
