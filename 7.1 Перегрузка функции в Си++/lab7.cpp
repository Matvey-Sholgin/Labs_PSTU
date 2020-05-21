// lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>


//Класс обыкновенных дробей
struct CommonFraction
{
    //числитель 
    int numerator;
    //знаменатель
    int denominator;
};

float sum(int n, float mas[]) {
    float result = 0.0;
    for (int i = 0; i < n; i++)
    {
        result += mas[i];
    }

    return result;
}

//Функция вычисления общего знаменателя
int calcDenominatorСommon(int n, CommonFraction mas[]) {
    int denominatorСommon = NULL;
    for (int i = 0; i < n; i++)
    {
        CommonFraction a = mas[i];
        // Если общего знаменателя еще нет
        if (denominatorСommon == NULL) {
            denominatorСommon = a.denominator;
        }
        else
        {
            // Сравение общего знаменателя
            if (a.denominator > denominatorСommon) {
                // Если остакта от деления на меньший нет то перемнажаем знаменатели 
                if (a.denominator % denominatorСommon > 0) {
                    denominatorСommon = a.denominator * denominatorСommon;
                }
            }
            else
            {
                if (denominatorСommon > a.denominator) {
                    // Если остакта от деления на меньший нет то перемнажаем знаменатели 
                    if (denominatorСommon % a.denominator) {
                        denominatorСommon = a.denominator * denominatorСommon;
                    }
                }
            }


        }
    }

    return denominatorСommon;
}

CommonFraction sum(int n, CommonFraction mas[]) {
    CommonFraction result = { 0, 0 };
    //общий знаменатель
    int denominatorСommon = calcDenominatorСommon(n, mas);

    //В результа проставляем макс знаменатель
    result.denominator = denominatorСommon;
    //Расчет числителя в результ
    for (int i = 0; i < n; i++)
    {
        CommonFraction a = mas[i];
        result.numerator += a.numerator * denominatorСommon/a.denominator;
    }

    return result;
}

int main()
{
    setlocale(0, "");
    // количество чисел
    const int n = 3;
    //а) для сложения десятичных дробей;
    float a[n] = { 1.1f, 2.2f, 3.3f };
    //б) для сложения обыкновенных дробей.
    CommonFraction b[n] = { CommonFraction {1,2}, CommonFraction {2,3}, CommonFraction {5,4} };

    float resultA = sum(n, a);
    std::cout << "Результат для сложения десятичных дробей: "<< resultA;

    CommonFraction resultB = sum(n, b);

    std::cout << "\nРезультат для сложения обыкновенных дробей: числитель=" << resultB.numerator << " знаменател=" << resultB.denominator ;
}

