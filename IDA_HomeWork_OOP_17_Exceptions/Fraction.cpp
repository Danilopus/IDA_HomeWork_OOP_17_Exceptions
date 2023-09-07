#include "Fraction.h"

// static variables
std::vector<Fraction*>* Fraction::static_pointer_Available_fractions{ nullptr };
std::map <int, std::string> Fraction::codes_of_operation{ {1," + "}, {2," - "}, {3," * "}, {4, " / "}, {5, "++"}, {6,"++"}, {7, "--"}, {8,"--"},{9,"+"}, {0, "-"} };


//::::::::::::::::::::::::::::::Fraction:: Fraction:: Fraction:: Fraction:: Fraction:: Fraction:: Fraction:: Fraction::::::::::::::::::::::::::::::
int Fraction::MaxCommonDivider(int a, int b)
{
	while (a > 0 && b > 0)
	{
		if (a > b)	a %= b;
		else		b %= a;
	}
	return a + b;
}
bool Fraction::Fraction_reduction()
{
	try
	{
		if (_denominator == 0) throw std::invalid_argument("Division by zero is undefined");
	}
	catch (const std::exception& e)
	{
			std::cerr << std::endl << "\nError occurred!";
			std::cerr << std::endl << "Caught in:   " << __FUNCTION__;
			std::cerr << std::endl << "Description: " << e.what() << std::endl;
			std::cerr			   << "Type:        " << typeid(e).name() << std::endl;
			std::cerr              << "Object location: " << this << std::endl;
			return false;
	}
	int max_common_divider = MaxCommonDivider(abs(Get_numerator()), abs(Get_denominator()));
	_numerator=(Get_numerator() / max_common_divider);
	_denominator=(Get_denominator() / max_common_divider);
	return true;
}
void Fraction::Set_static_pointer_Available_fractions(std::vector<Fraction*>& Available_fractions)
{
	static_pointer_Available_fractions = &Available_fractions;
}
Fraction::Fraction(int A1, int A2, std::vector<Fraction*>& Available_fractions) : _numerator(A1), _denominator(A2)
{
	if (!Fraction_reduction()) return;
	Available_fractions.push_back(this);
}
Fraction::Fraction(int new_numerator, int new_denominator) : _numerator{ new_numerator }, _denominator{ new_denominator }
{
	if (!Fraction_reduction()) return;
	if (static_pointer_Available_fractions) static_pointer_Available_fractions->push_back(this);
}
void Fraction::Set_numerator(int numerator)
{
	_numerator = numerator;
	Fraction_reduction();

}

void Fraction::Set_denominator(int denominator)
{
	//if (denominator == 0) throw std::invalid_argument("Division by zero is undefined");
	//assert(denominator && "Division by zero is undefined");
	if (!Fraction_reduction()) return;
	_denominator = denominator;
	Fraction_reduction();
}
void Fraction::ShowValues() { std::cout << this->Get_numerator() << " / " << this->Get_denominator(); }
void Fraction::ShowMethods()
{
	std::cout << "\n* Available methods:\nBinary:\t\t\t\t" << "Unary:\n";
	std::cout << "Summation [+] -> [1]" << "\t\t" << "Prefix increment  [++v] -> [5]" << '\n';
	std::cout << "Substract [-] -> [2]" << "\t\t" << "Postfix increment [v++] -> [6]" << '\n';
	std::cout << "Multiply  [*] -> [3]" << "\t\t" << "Prefix decrement  [--v] -> [7]" << '\n';
	std::cout << "Divide    [/] -> [4]" << "\t\t" << "Postfix decrement [v--] -> [8]" << '\n';
	std::cout << "\t\t\t\tUnary plus        [+v]  -> [9]" << '\n';
	std::cout << "\t\t\t\tUnary minus       [-v]  -> [0]" << '\n';

}
// old implementation (with external pointer to fraction list)
void Fraction::ShowAvailableFractions(std::vector<Fraction*> Available_fractions)
{
	std::cout << "\n* Available fractions\n:";
	for (int i = 0; i < Available_fractions.size(); i++)
	{
		std::cout << "\nFraction [" << i + 1 << "] -> " << Available_fractions[i]->Get_numerator() << " / " << Available_fractions[i]->Get_denominator();
	}
	std::cout << "\n";
}
// new implementation (with internal pointer to fraction list)
void Fraction::ShowAvailableFractions()
{
	std::cout << "\n* Available fractions:";
	for (int i = 0; i < (*static_pointer_Available_fractions).size(); i++)
	{
		std::cout << "\nFraction [" << i + 1 << "] -> " << *(*static_pointer_Available_fractions)[i];
	}
	std::cout << "\n";
}
void Fraction::Memory_Clean(const std::vector<Fraction*>& Available_fractions)
{	
	for (int i = 0; i < Available_fractions.size(); i++)
		delete Available_fractions[i];
	static_pointer_Available_fractions = nullptr;
}
Fraction* Fraction::operator+(const Fraction& another_Fraction) {
	//std::cout << "\n" << "var2 Using member-function const& overload parameter, pointer return" << "\n";
	int new_numerator = (this->_numerator) * (another_Fraction._denominator) + (another_Fraction._numerator) * (this->_denominator);
	int new_denominator = (this->_denominator) * (another_Fraction._denominator);
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
	return result_fraction;
}
Fraction* Fraction::operator+(Fraction& another_Fraction)
{
	//std::cout << "\n" << "var3 Using member-function & overload parameter, pointer return" << "\n";
	int new_numerator = (this->_numerator) * (another_Fraction._denominator) + (another_Fraction._numerator) * (this->_denominator);
	int new_denominator = (this->_denominator) * (another_Fraction._denominator);
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
	return result_fraction;
}
Fraction* Fraction::Add(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions)

{
	int new_numerator = _numerator * another_Fraction.Get_denominator() + another_Fraction.Get_numerator() * _denominator;
	int new_denominator = _denominator * another_Fraction.Get_denominator();
	//вариант с сокращением дроби в момент создания через вызов Fraction_reduction в конструкторе
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator, Available_fractions); // вариант с внешним вектором для хранения объектов
	return result_fraction;
}
Fraction* Fraction::Subtract(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions)
{
	int new_numerator = _numerator * another_Fraction.Get_denominator() - another_Fraction.Get_numerator() * _denominator;
	int new_denominator = _denominator * another_Fraction.Get_denominator();
	//вариант с сокращением дроби в момент создания через вызов Fraction_reduction в конструкторе
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator, Available_fractions); // вариант с внешним вектором для хранения объектов

	//Fraction* result_fraction = new Fraction(Available_fractions); // вариант с внешним вектором для хранения объектов
	//result_fraction->Set_numerator(_numerator * another_Fraction.Get_denominator() - another_Fraction.Get_numerator() * _denominator);
	//result_fraction->Set_denominator(_denominator * another_Fraction.Get_denominator());
	//Fraction_reduction();
	return result_fraction;
}
Fraction* Fraction::Multiply(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions)
{
	int new_numerator = _numerator * another_Fraction.Get_numerator();
	int new_denominator = _denominator * another_Fraction.Get_denominator();
	//вариант с сокращением дроби в момент создания через вызов Fraction_reduction в конструкторе
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator, Available_fractions); // вариант с внешним вектором для хранения объектов

	//Fraction* result_fraction = new Fraction(Available_fractions); // вариант с внешним вектором для хранения объектов
	//result_fraction->Set_numerator(_numerator * another_Fraction.Get_numerator());
	//result_fraction->Set_denominator(_denominator * another_Fraction.Get_denominator());
	//Fraction_reduction();
	return result_fraction;
}
Fraction* Fraction::Divide(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions)
{
	int new_numerator = _numerator * another_Fraction.Get_denominator();
	int new_denominator = _denominator * another_Fraction.Get_numerator();
	//убираем знак из знаменателя
	if (new_denominator < 0) { new_denominator = -1 * new_denominator; new_numerator = -1 * new_numerator; }
	//вариант с сокращением дроби в момент создания через вызов Fraction_reduction в конструкторе
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator, Available_fractions); // вариант с внешним вектором для хранения объектов
	return result_fraction;
}
Fraction* Fraction::operator-(const Fraction& another_Fraction)
{
	//std::cout << "\n" << "Using member-function const& overload parameter, pointer return" << "\n";
	int new_numerator = (this->_numerator) * (another_Fraction._denominator) - (another_Fraction._numerator) * (this->_denominator);
	int new_denominator = (this->_denominator) * (another_Fraction._denominator);
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
	return result_fraction;
}
Fraction* Fraction::operator*(const Fraction& another_Fraction)
{
	//std::cout << "\n" << "Using member-function const& overload parameter, pointer return" << "\n";
	int new_numerator = (this->_numerator) * (another_Fraction._numerator);
	int new_denominator = (this->_denominator) * (another_Fraction._denominator);
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
	return result_fraction;
}
Fraction* Fraction::operator/(const Fraction& another_Fraction)
{
	//std::cout << "\n" << "Using member-function const& overload parameter, pointer return" << "\n";
	int new_numerator = (this->_numerator) * (another_Fraction._denominator);
	int new_denominator = (this->_denominator) * (another_Fraction._numerator);
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
	return result_fraction;
}
Fraction* Fraction::operator++() //prefix
{
	_numerator++;
	return this;
}
Fraction* Fraction::operator++(int) //postfix
{
	//Fraction& tmp_obj(*this);
	Fraction* tmp_obj = new Fraction(*this);
	_numerator++;
	//return &tmp_obj;
	return tmp_obj;
}
Fraction* operator+(const Fraction& Fraction_Operand_1, const Fraction& Fraction_Operand_2)
{
	//std::cout << "\n" << "var1 Using friend-function const& overload parameter, return pointer" << "\n";
	int new_numerator = (Fraction_Operand_1._numerator) * (Fraction_Operand_2._denominator) + (Fraction_Operand_2._numerator) * (Fraction_Operand_1._denominator);
	int new_denominator = (Fraction_Operand_1._denominator) * (Fraction_Operand_2._denominator);
	Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
	return result_fraction;
}

std::ostream& operator<<(std::ostream& out, Fraction& just_a_fraction)
{
	//just_a_fraction.ShowValues();

	out << just_a_fraction._numerator << "/" << just_a_fraction._denominator;

	return out;
}


