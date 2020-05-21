// lab9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

// формирования файла
void fileFormation() {
    FILE* f1;
    fopen_s(&f1, "f1.txt", "w");
    if (f1 == NULL) {
        perror("\nошибка при открытии файла f1 для формирования");
        exit(0);
    }

    char str[255];
    char no[10] = "";
    while (strcmp(no, "n"))
    {
        

        printf("Введите строку для записи в файл(max длина 255)\n");
        std::cin.get(str, 255);
        std::cin.ignore();
        fputs(str, f1);
        fputs("\n", f1);

        printf("Продолжить ввод дальше: n - нет\n");
        std::cin.get(no, 10);
        std::cin.ignore();
        
        
    }

    fclose(f1);
}
// печати файла
void printFile() {
    FILE* f1;
    fopen_s(&f1, "f1.txt", "r");
    if (f1 == NULL) {
        perror("\nошибка при открытии файла f1 для печати файла");
        exit(0);
    }

    char str[255];
    std::cout << "\nПечати файла\n";
    // считать символы из файла
    while (fgets(str, 255, f1) != NULL) {
       std:: cout << str;  // вывод на экран
    }
    fclose(f1);
}

// копирования файлов
void copyFileToFile() {
    FILE* f1;
    fopen_s(&f1, "f1.txt", "r");
    if (f1 == NULL) {
        perror("\nошибка при открытии файла f1 для копирования файлов");
        exit(0);
    }

    FILE* f2;
    fopen_s(&f2, "f2.txt", "w");
    if (f2 == NULL) {
        perror("\nошибка при открытии файла f2 для копирования файлов");
        exit(0);
    }

    char str[255];
    std::cout << "\nПеренесенные строки\n";
    // считать символы из файла
    while (fgets(str, 255, f1) != NULL) {
        
        //положение предыдущего пробела
        int iPrev = -1;
        //счётчик слов
        int countWord = 0;

        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] == ' ' || str[i]== '\n')
            {
                // если между пробелами больше чем один символ
                if ( i - iPrev > 1 )
                {
                    //найдено слово
                    countWord++;
                }

                iPrev = i;
            }            
        }   

        if (countWord == 1)
        {
            std::cout << str; // вывод на экран которые перенесутся
            fputs(str, f2);  // записываем в файл f2
        }
    
    }

    fclose(f1);
    fclose(f2);
}
// выполнения задания
// поиск величены самого большого слова
int gexMaxSizeWord() {
    FILE* f2;
    fopen_s(&f2, "f2.txt", "r");
    if (f2 == NULL) {
        perror("\nошибка при открытии файла f2 для нахождения максимальной длины слова");
        exit(0);
    }

    char str[255];
    int sizeMax = 0;
    // считать символы из файла
    while (fgets(str, 255, f2) != NULL) {
        int sizeStr = strlen(str);
        if (sizeStr > sizeMax)
        {
            sizeMax = sizeStr;
        }
    }
    fclose(f2);

    return sizeMax;
}

// вывод самых больших слов
void findMaxWord(int size) {
    FILE* f2;
    fopen_s(&f2, "f2.txt", "r");
    if (f2 == NULL) {
        perror("\nошибка при открытии файла f2 для вывода максимального слова");
        exit(0);
    }

    char str[255];
    // считать символы из файла
    std::cout << "самое длинное слово в  файле F2\n";
    while (fgets(str, 255, f2) != NULL) {
        if (size == strlen(str))
        {
            std ::cout << str;
        }
    }
    fclose(f2);
}

int main(void)
{
    setlocale(0, "");
    // 1)  Скопировать из файла F1 в файл F2 все строки, которые содержат только одно слово.
    // 2)  Найти самое длинное слово в  файле F2.
    
    fileFormation();
    printFile();
    copyFileToFile();
    int sizeMax = gexMaxSizeWord();
    if (sizeMax == 0)
    {
        std::cout << "Слов в файле f2 нет";
    }
    else
    {
        findMaxWord(sizeMax);
    }
    
}
