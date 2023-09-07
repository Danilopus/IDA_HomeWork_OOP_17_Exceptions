#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Service functions.h"
//#include <windows.h>
#include <conio.h>
#include <cassert>
#include <map>

class Fraction
{
private:
	int _numerator{ 1 };
	int _denominator{ 1 };
	static std::vector<Fraction*>* static_pointer_Available_fractions;// = nullptr это сделано в cpp т.к. поле статическое;
	int MaxCommonDivider(int a, int b);
	bool Fraction_reduction();

public:
	static std::map <int, std::string> codes_of_operation;
	static void Set_static_pointer_Available_fractions(std::vector<Fraction*>& Available_fractions);

	// Constructors // Destructors // Memory Clean -------------------------
	Fraction(int A1, int A2, std::vector<Fraction*>& Available_fractions);
	Fraction(std::vector<Fraction*>& Available_fractions) { Available_fractions.push_back(this); }
	Fraction(int new_numerator, int new_denominator);
	Fraction() {}
	~Fraction()	{/*т.к. сам объект Fraction не работает с динмической памятью - в деструкторе ничего чистить не надо
		
		*/ }
	static void Memory_Clean(const std::vector<Fraction*>& Available_fractions);

	// Setters // Getters --------------------------------------------------
	void Set_numerator(int numerator);
	void Set_denominator(int denominator);
	int Get_numerator() { return _numerator; }
	int Get_denominator() { return _denominator; }

	// Shows ---------------------------------------------------------------
	void ShowValues();
	static void ShowMethods();
	void ShowAvailableFractions(std::vector<Fraction*> Available_fractions);
	static void ShowAvailableFractions();

	// Inputs handle -------------------------------------------------------		
	static int UserChoiceHandle()
	{
		std::cout << "choose a method: ";
		int action = Get_Int_Positive(0, 9, "Please, focus your attention on methods amount -> [0..9] ");
		return action;
	}
	static Fraction& Choose_Operand_Handle(int Operand_number)	{
		
		std::cout << "\nchoose operand " << Operand_number << ": ";
		//std::string coomment = "index out of range "+"[1.." + std::to_string(static_pointer_Available_fractions->size());
		std::string comment = "index out of range ";
		comment += "[1.." + std::to_string(static_pointer_Available_fractions->size()) + "] ";
		int fraction_index = Get_Int_Positive(1, static_pointer_Available_fractions->size(), comment);
		--fraction_index; //transform number to index

		return *(*static_pointer_Available_fractions)[fraction_index];
	}

	//Overload operators - pointer returned -----------------------------------------
	
	Fraction* Add(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);
	Fraction* Subtract(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);
	Fraction* Multiply(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);
	Fraction* Divide(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);

	friend Fraction* operator+(const Fraction& Fraction_Operand_1, const Fraction& Fraction_Operand_2);
	Fraction* operator+(const Fraction& another_Fraction);
	Fraction* operator+(Fraction& another_Fraction);
	Fraction* operator-(const Fraction& another_Fraction);
	Fraction* operator*(const Fraction& another_Fraction);
	Fraction* operator/(const Fraction& another_Fraction);

	Fraction* operator++();
	Fraction* operator++(int);
	Fraction* operator--() //prefix
	{
		_numerator--;
		return this;
	}
	Fraction* operator--(int) //postfix
	{
		Fraction* tmp_obj = new Fraction(*this);
		_numerator--;
		return tmp_obj;
	}

	Fraction* operator+() 
	{
		return this;
	}
	Fraction* operator-()
	{
		_numerator = -_numerator;
		return this;
	}

	friend std::ostream& operator << (std::ostream& out, Fraction& just_a_fraction);
};
