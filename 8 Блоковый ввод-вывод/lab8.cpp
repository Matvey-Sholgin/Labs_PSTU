// lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <stdio.h>
#include <string>

typedef struct Data
{
    char fio[50];
    char adress[50];
    char medkart[10];
    char polis[10];
} EMPLOYEE;

//вывод меню
int menu()
{
    int a;
    do
    {
        printf("\nМеню:\n");
        printf("1. Печать\n");
        printf("2. Добавление элементов 2-х элеметов\n");
        printf("3. Удалить элемент с заданным номером медицинской карты\n");
        printf("4. Выход\n");
        printf("Ваш выбор: ");
        std::cin >> a;
        std::cin.ignore();
    } while (a > 4);
    return a;
}

//заполенения данных о пациенте
Data createData() {
    Data data;
    
    std::cout << "Введите фамилию, имя, отчество: ";
    std::cin.get(data.fio, 50);
    std::cin.ignore();

    std::cout << "Введите домашний адрес: ";
    std::cin.get(data.adress, 50);
    std::cin.ignore();

    std::cout << "Введите номер медицинской карты: ";
    std::cin.get(data.medkart, 10);
    std::cin.ignore();

    printf("Введите номер страхового полиса: ");
    std::cin.get(data.polis, 10);
    std::cin.ignore();

    return data;
}

//печати файла
void print(FILE* fp)
{
    fopen_s(&fp, "t.txt", "r+b");

    if (fp == NULL) {
        perror("\nошибка при открытии файла(печать) ");
        exit(0);
    }

    int i = 0;
    while (!feof(fp) )
    {
        Data data;
        int count = fread(&data, sizeof(EMPLOYEE), 1, fp);

        if (count > 0)
        {
            printf("\nПациент %d\n", i + 1);
            printf("Фамилия, имя, отчество %d: ", i + 1);
            printf("%s\n", data.fio);

            printf("Домашний адрес %d: ", i + 1);
            printf("%s\n", data.adress);

            printf("Номер медицинской карты %d: ", i + 1);
            printf("%s\n", data.medkart);

            printf("Номер страхового полюса %d: ", i + 1);
            printf("%s\n", data.polis);

            i++;
        }
    }
    fclose(fp);

}
/**
копирование данных из fp1 d fp2
fp1-файл откуда
fp2-файл куда
*/
void copyFileToFile(FILE* fp1, FILE* fp2) {
    while (!feof(fp1))
    {
        Data data;
        int count = fread(&data, sizeof(EMPLOYEE), 1, fp1);

        if (count > 0)
        {
            // записываем запись в файл
            fwrite(&data, sizeof(EMPLOYEE), 1, fp2);
        }
    }
}

//добавления записи в файл
void addTwo(FILE* fp) {
    fopen_s(&fp, "t.txt", "r+b");

    if (fp == NULL) {
        perror("\nошибка при открытии файла(добавление двух) ");
        exit(0);
    }

    FILE* fpTemp;
    fopen_s(&fpTemp, "t_temp.txt", "w+b");
 
    if (fpTemp == NULL) {
        perror("\nошибка при открытии временного файла(добавление двух) ");
        exit(1);
    }

    //добавление 2-х элементов
    for (int i = 0; i < 2; i++) {
        printf("\nПациент %d\n", i + 1);
        Data data = createData();

        // записываем запись в файл
        fwrite(&data, sizeof(EMPLOYEE), 1, fpTemp);
    };
    //копируем из fp в fpTemp элементы
    copyFileToFile(fp, fpTemp);

    fclose(fp);
    fclose(fpTemp);

    fopen_s(&fp, "t.txt", "w+b");

    if (fp == NULL) {
        perror("\nошибка при открытии файла, перенос данных(добавление двух) ");
        exit(2);
    }

    fopen_s(&fpTemp, "t_temp.txt", "r+b");

    if (fpTemp == NULL) {
        perror("\nошибка при открытии временного файла, перенос данных(добавление двух) ");
        exit(3);
    }

    //копируем из fpTemp в fp элементы
    copyFileToFile(fpTemp, fp);

    fclose(fp);
    fclose(fpTemp);
}

//поиска структуры для удаления
bool needDeleteElement(char* str, char* medkart) {
    if (str == NULL || medkart == NULL)
        return false;
    int diff = strcmp(medkart, str);
    if (diff == 0 ) {
        return true;
    }

    return false;
}

//удаления записи из файла
void deleteData(FILE* fp) {
    fopen_s(&fp, "t.txt", "r+b");

    if (fp == NULL) {
        perror("\nошибка при открытии файла(Удалить элемент) ");
        exit(0);
    }

    FILE* fpTemp;
    fopen_s(&fpTemp, "t_temp.txt", "w+b");

    if (fpTemp == NULL) {
        perror("\nошибка при открытии временного файла(Удалить элемент) ");
        exit(1);
    }

    char str[10];
    printf("Введите номером медицинской карты для удаления\n");
    scanf_s("%s", str, 10);

    //копируем из fp в fpTemp элементы
    while (!feof(fp))
    {
        Data data;
        int count = fread(&data, sizeof(EMPLOYEE), 1, fp);
        
        if (count > 0)
        {
            if (!needDeleteElement(str, data.medkart)) {
                // записываем запись в файл
                fwrite(&data, sizeof(EMPLOYEE), 1, fpTemp);
            }
        }
    }

    fclose(fp);
    fclose(fpTemp);

    fopen_s(&fp, "t.txt", "w+b");

    if (fp == NULL) {
        perror("\nошибка при открытии файла, перенос данных(Удалить элемент) ");
        exit(2);
    }

    fopen_s(&fpTemp, "t_temp.txt", "r+b");

    if (fpTemp == NULL) {
        perror("\nошибка при открытии временного файла, перенос данных(Удалить элемент) ");
        exit(3);
    }

    //копируем из fpTemp в fp элементы
    copyFileToFile(fpTemp, fp);

    fclose(fp);
    fclose(fpTemp);
}

//формирования файла
void fileFormation(FILE* fp) {

    int n = 0;

    printf("Введите количество пациентов\n");
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        printf("\nПациент %d\n", i + 1);
        Data data = createData();

        // записываем запись е в файл
        fwrite(&data, sizeof(EMPLOYEE), 1, fp);
    };
}



int main(void)
{
    setlocale(0, "");
    // Структура "Пациент":
    //• фамилия, имя, отчество;
    //• домашний адрес;
    //• номер медицинской карты;
    //• номер страхового полиса.
    //    Удалить элемент с заданным номером медицинской карты, добавить 2 элемента в начало файла.

    FILE* fp;
    fopen_s(&fp, "t.txt", "w+b");
    if (fp == NULL) {
        perror("\nошибка при открытии файла");
        exit(0);
    }
    fileFormation(fp);
    fclose(fp);

    while (3)
        switch (menu())
        {

        case 1:
            print(fp);
            break;
        case 2:
            addTwo(fp);
            break;
        case 3:
            deleteData(fp);
            break;
        case 4:
            return 0;
        }

}


