// HomeWork template project v 4.0 // 20.06.2023 //

/*
Основы ООП с использованием языка с++

Задание

Дополнить класс Дробь выбрасывая исключения в методах класса которые могут
генерировать ошибки(например попытка установить 0 в знаменатель)
в функции Main провести обработку исключений с помощью конструкции try cath

*/

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
//My own headers
#include "Service functions.h"
#include "MainMenu.h"
#include "Fraction.h"



// Homework OOP 17 ----------------------------------------------------	


/// защита от нуля в знаменателе 

/*
*	1. Первоначально было реализовано через assert
*	2. В этом задании добавлен также throw
*
*/

//Task 1 Fractions class demo with overloaded operators:\nBinary: + | - | / | * \nUnary: + | - | ++ | --
void Task_1(std::string name_of_task)
{
	//Вариант хранения объектов класса Fraction в векторе объектов вне класса (из точки вызова, с передачей указателя на этот вектор)
	std::vector<Fraction*> Available_fractions;

	// вот такой костыль родился на третьей итерации ДЗ про дроби, дабы избавиться от частой передачи указателя на вектор с объектами
	// старые функции переделывать не стал
	Fraction::Set_static_pointer_Available_fractions(Available_fractions);

	const int list_size = 5; //наполняем объектами дробей лист дробей для дальнейшей работы с ними
	for (int i = 0; i < list_size; i++)	{ Fraction& new_fraction = *new Fraction(Get_Random(1,100), Get_Random(1, 100)); }
		
	do
	{	
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";

		Fraction::ShowAvailableFractions();
		Fraction::ShowMethods();

		int action = Fraction::UserChoiceHandle();					
		if (action <= 4 && action>0)//разделяем бинарные и унарные операции
		{
			Fraction& Operand_1 = Fraction::Choose_Operand_Handle(1);
			Fraction& Operand_2 = Fraction::Choose_Operand_Handle(2);

			switch (action)
			{
			case 1: Operand_1 + Operand_2; break;
			case 2: Operand_1 - Operand_2; break;
			case 3: Operand_1 * Operand_2; break;
			case 4: Operand_1 / Operand_2; break;
			}
			std::cout << std::endl << Operand_1 << Fraction::codes_of_operation[action] << Operand_2 << " = " << *Available_fractions[Available_fractions.size() - 1];

		}
		else
		{
			Fraction& Operand = Fraction::Choose_Operand_Handle(0);
			Fraction tmp(Operand); // Благодаря конструктору копирования этот временный объект не попадает в общий вектор объектов
			switch (action)
			{
			case 5: ++Operand; break;
			case 6: Operand++; break;
			case 7: --Operand; break;
			case 8: Operand--; break;
			case 9: +Operand; break;
			case 0: -Operand; break;
			}
			//Разделяем вывод префиксных и постфиксных форм
			if (action == 8 || action == 6 )
			std::cout << std::endl << "(" << tmp << ")"<< Fraction::codes_of_operation[action] << " = " << Operand;
			else
				std::cout << std::endl << Fraction::codes_of_operation[action] <<"(" << tmp << ") = " << Operand;
		}

		std::cout << "\n\nEsc - for exit, any key to continue";
	} while (_getch() != 27);
	Fraction::Memory_Clean(Available_fractions);
	/*
	* сам вектор std::vector<Fraction*> Available_fractions вроде должен быть уничтожен автоматически,
	* т.к. находится в стэке (мне так кажется)
	*/
}

// Task 2 Fractions class : exception demo

/// По поводу деления на 0 в C++
/*

Раздел 5.6  стандарта C++11 конкретно указывает:
Если второй операнд / или % равен нулю, поведение undefined.

По изучению материала по теме я пришел к выводу: проблему деления на 0 в С++
надо решать собственными проверками.

* есть какой-то путь по обработке и превращению аппартаных исключений,
* (которые и случаются при делению на ноль) в программные, но им идти не рекоммендуют:
* 1) называют его скользким
* 2) по причине плохой платформенной переносимости такого кода

Итак, будем использовать собственные контсрукции try-throw-catch 
используя наиболее подходящего наследника std::exception

Посмотрим какие они вообще бывают:

Standard exceptions
logic_error
	invalid_argument
	domain_error
	length_error
	out_of_range
	future_error (since C++11)
runtime_error
	range_error
	overflow_error
	underflow_error
	regex_error (since C++11)
	---system_error (since C++11)
		ios_base::failure (since C++11)
		filesystem::filesystem_error (since C++17)
	tx_exception (TM TS)
	nonexistent_local_time (since C++20)
	ambiguous_local_time (since C++20)
	format_error (since C++20)

bad_typeid
bad_cast
	bad_any_cast (since C++17)
bad_optional_access (since C++17)
bad_expected_access (since C++23)
bad_weak_ptr (since C++11)
bad_function_call (since C++11)
bad_alloc
	bad_array_new_length (since C++11)
bad_exception
ios_base::failure (until C++11)
bad_variant_access (since C++17)

В большинстве случаев рекомендуется использовать обработку исключений C++ по стандарту ISO.
Таким образом, если убрать нововведения останется:

namespace std 
{
	class logic_error;
		class domain_error;
		class invalid_argument;
		class length_error;
		class out_of_range;
	class runtime_error;
		class range_error;
		class overflow_error;
		class underflow_error;
}

Из все существующих типов на мой взгляд самый подходящий в нашем случае: invalid_argument


PS
Страуструп говорит в "Дизайне и эволюции C ++" (Addison Wesley, 1994): 
"Предполагается, что события низкого уровня, такие как арифметические переполнения и деление на ноль, 
обрабатываются специализированным механизмом более низкого уровня, а не исключениями. 
Это позволяет C ++ соответствовать поведению других языков, когда дело доходит до арифметики. 
Это также позволяет избежать проблем, возникающих в сильно конвейерных архитектурах, 
где такие события, как деление на ноль, являются асинхронными ".

*/
void Task_2(std::string name_of_task)
{
	Fraction demo_fraction;

	try
	{
		std::cout << std::endl << "demo_fraction.Set_numerator(1)";
		demo_fraction.Set_numerator(3);
		std::cout << std::endl << "demo_fraction.Set_denominator(0)";
		demo_fraction.Set_denominator(0);
	}	
	catch (const std::exception& e)
	{
		std::cerr << std::endl << "\nError occurred!";
		std::cerr << std::endl << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}
	
	// код блоков try-catch выше на самом деле не срабатывает 
	// приведен здесь только для соответствия заданию
	// Реально обработка ошибки со нулевым знаменателем происходит 
	// в момент создания дроби и при попытке Set_denominator(0)
	std::cout << std::endl << "Fraction demo_fraction_2(1,0)";
	Fraction demo_fraction_2(1,0);

	std::cout << std::endl << "demo_fraction_2.Set_denominator(0)";
	demo_fraction_2.Set_denominator(0);

	_getch();
}





// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	srand(time(NULL));
	//system("mode con cols=60 lines=40"); 
	Main_menu MainMenu;	
	MainMenu.AddElement("OOP Home Work 17: Exceptions");	// Homework name
	MainMenu.AddElement("Fractions class demo with overloaded operators:\n\tBinary: + | - | / | * \n\tUnary: + | - | ++ | --\nZero denominator guarded by exception\n");
	MainMenu.AddElement("Fractions class: exception demo");

	do 
	{		
		MainMenu.Show_menu();
		if (!MainMenu.User_Choice_Handle(_getch()))	break;
	} while (true);
	return 0;
}

