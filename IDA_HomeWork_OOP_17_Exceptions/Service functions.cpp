#include "Service functions.h"

// Service functions -----------------------------------------
int Get_Int_SA() {
	std::string a;
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{

		if ((a.find_first_not_of("-0123456789") == -1))
		{
			for (int i = 1; i < a.size(); i++) // определяем есть ли минусы кроме первого символа
			{
				if (a[i] == '-')
				{
					std::cout << "Input Error: Minus misstanding. [INTEGER] expected.\n";
					return Get_Int_SA();
				}
			}
			try
			{
				return stoi(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. [INTEGER] expected.\n";
				return Get_Int_SA();
			}


		}
		else
		{
			std::cout << "Input Error: Incorrect symbol. [INTEGER] expected.\n";
			return Get_Int_SA();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. [INTEGER] expected.\n";
		return Get_Int_SA();
	}
}
int Get_Int_Positive()
{
	std::string a;
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try {
				return stoi(a);
			}
			catch (std::out_of_range) {
				std::cout << "Input Error: overflow. Positive [INTEGER] expected.\n";
			}
		}
		else
		{
			std::cout << "Input Error: Positive [INTEGER] expected.\n";
			return Get_Int_Positive();
		}
	}
	else
		std::cout << "Input Error: NULL input. Positive [INTEGER] expected.\n";
	return Get_Int_Positive();
}
int Get_Int_Positive(int BOTTOM_limit, int UP_limit, std::string comment)
{
	
	std::string a;
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{

		if ((a.find_first_not_of("0123456789") == -1))
		{
			try {
				int try_to_get_int = stoi(a);
				if (try_to_get_int < BOTTOM_limit || try_to_get_int > UP_limit)
				{
					std::cout << comment;
					//return UP_limit;
					return Get_Int_Positive(BOTTOM_limit, UP_limit, comment);
				}

				return stoi(a);
			}
			catch (std::out_of_range) {
				std::cout << "Input Error: overflow. Positive [INTEGER] expected.\n";
			}
		}
		else
		{
			std::cout << "Input Error: Positive [INTEGER] expected.\n";
			return Get_Int_Positive(BOTTOM_limit, UP_limit, comment);
		}
	}
	else
		std::cout << "Input Error: NULL input. Positive [INTEGER] expected.\n";
	return Get_Int_Positive(BOTTOM_limit, UP_limit, comment);
}
int Get_Int_PG()
{
	int a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! [INTEGER] expected. Repeat please...\n";
	}
	return a;
}
double Get_Dbl_SA() {
	std::string a;
	std::cin.sync();
	getline(std::cin, a);
	if (a == "") { std::cout << "\nInput Error : NULL input\n"; return Get_Dbl_SA(); }
	if ((a.find_first_not_of("-.0123456789") == -1))
	{
		for (int i = 1; i < a.size(); i++) // Проверяем отсутсвие лишних минусов
		{
			if (a[i] == '-')
			{
				std::cout << "\nInput Error: Minus misstanding. [DOUBLE] expected.\n";
				return Get_Dbl_SA();
			}

		}
		bool Dot_Flag = 0;
		for (int i = 0; i < a.size(); i++) // проверяем отсутсвие лишних точек
		{
			if (a[i] == '.')
			{
				if (Dot_Flag == 1)
				{
					std::cout << "\nInput Error: Dot misstandig. [DOUBLE] expected.\n";
					return Get_Dbl_SA();
				}
				Dot_Flag = 1;
			}

		}
		try {
			return stod(a);
		}
		catch (std::out_of_range) {
			std::cout << "Input Error: overflow. [DOUBLE] expected.\n";
			return Get_Dbl_SA();
		}
	}
	else {
		std::cout << "Incorrect symbols: [DOUBLE] expected.\nUse dot instead of coma. Example 50.64\n";
		return Get_Dbl_SA();
	}
}
double Get_Dbl_Positive() {
	std::string a, dot = ".";
	std::cin.sync();
	std::cin.clear();
	getline(std::cin, a);
	if (a != "")
	{
		if ((a.find_first_not_of(".0123456789") == -1))
		{
			bool One_Dot_already = false;
			for (int i = 0; i < a.size(); i++)
			{
				if (a[i] == dot[0] && One_Dot_already == true) //проверяем количество разделителей
				{
					std::cout << "Input Error: Dot misstandig. Positive [DOUBLE] expected.\n";
					return Get_Dbl_Positive();
				}
				if (a[i] == dot[0])	One_Dot_already = true;
			}
			try
			{
				return stod(a);
			}
			catch (std::out_of_range)
			{
				std::cout << "Input Error: Data type overflow. Positive [DOUBLE] expected.\n";
				return Get_Dbl_Positive();
			}
		}
		else
		{
			//std::cout << "Incorrect symbols: positive REAL expected.\nUse coma instead of dot. Example 50,64\n"; // да точно говорю вот даже сообщение такое было, а теперь наоборот wtf*2?!
			std::cout << "Incorrect symbols: Positive [DOUBLE] expected.\nUse dot instead of coma. Example 50.64\n";
			return Get_Dbl_Positive();
		}
	}
	else
	{
		std::cout << "Input Error: NULL input. Positive [DOUBLE] expected.\n";
		return Get_Dbl_Positive();
	}
	return Get_Dbl_Positive();
}
double Get_Dbl_PG()
{
	double a;
	while (!(std::cin >> a) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Input error! [DOUBLE] expected. Repeat please...\n";
	}
	return a;
}
int Get_Random(int Range_min = -999, int Range_max = 999)
{
	if (Range_min > Range_max)
	{
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	//return (Range_min + rand() % (Range_max - Range_min + 1));
	double K_random = double((rand() % RAND_MAX)) / RAND_MAX;
	int random = Range_min + ((Range_max - Range_min) * K_random);
	//return Range_min + (Range_max - Range_min) * (rand() % RAND_MAX) / RAND_MAX;
	return random;
}
double Get_Random(double Range_min = -99999.0, double Range_max = 99999.0)
{
	if (Range_min > Range_max)
	{
		std::cout << "\nError: Range_min > Range_max. New range: [Range_max..Range_min]\n";
		std::swap(Range_min, Range_max);
	}
	return 	Range_min + (Range_max - Range_min) * double(rand() % RAND_MAX) / RAND_MAX;
}

// Templated functions are defined ditectly in Service functions.h
//template <typename ANY> void Array_Console_Out(ANY arr[], int Size)
//{
//	std::cout << "\n[";
//	for (int i = 0; i < Size; i++)
//		std::cout << arr[i] << ", ";
//	std::cout << "\b\b]\n";
//}
//template <typename ANY> void Fill_Array_with_Random(ANY arr[], int Size, ANY Range_min, ANY Range_max)
//{
//	for (int i = 0; i < Size; i++)
//	{
//		arr[i] = Get_Random(Range_min, Range_max);
//	}
//}