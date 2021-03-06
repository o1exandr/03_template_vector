/*
Завдання 1(  підгрупа 31НС- 14  виконує відмічені завдання).
Визначити клас Дріб(чисельник  та знаменник - цілі).
Визначити для класу:
o	конструктор за замовчуванням( дріб 0/1)
o	конструктор з  1 параметром (знаменник у дробу == 1)
o	конструктор з  2 параметрами( передбачити валідацію для знаменника)
o	методи доступу до полів класу
o	метод виводу дробу на екран у вигляді чисельник / знаменник
o	метод скорочення дробу
Операції
o	додавання(+) двох дробів(глобальна функція)
o	віднімання(-) двох дробів(дружня глобальна функція)
o	множення(*) двох дробів(метод класу)
o	ділення(/) двох дробів(метод класу)
o	(++) 2 форми, збільшення дробу на 1(методи класу)
o	(--) 2 форми, зменшення дробу на 1(глобальні функції)
o	порівняння дробів (==, !=) (глобальні функції)
o	порівняння дробів(>, <) (методи класу)
o	виклику функції() для зміни чисельника та знаменника  дробу, наприклад, результатом a(5, 7) повинно бути зміна дробу a на 5 / 7
o	індексація([]),  що надаватиме доступ до чисельника чи знаменника  дробу за рядковим індексом(наприклад, a[“num”] надаватиме доступ до чисельника дробу)
o	перетворення до типу int, що повертає цілу частину дробу, наприклад, для дробу 10/4 ціла частина рівна 2
o	перетворення до типу double, що повертає десятковий  дріб, наприклад, звичайному  дробу 10/4 відповідає десятковий дріб 2.5
o	потокові операції для введення та виведення дробу

Перевірити роботу перевантажених операцій
Валідація: знаменник не повинен дорівнювати нулю, знаменник не повинен бути від’ємним(тобто дріб 1/ -2 перетворювати у  -1/ 2)
Перевірити роботу класу

*/


#include "stdafx.h"
#include <iostream> 
#include <string>

using namespace std;

class Drib
{
private:

	int a; //numerator
	int b; //denominator

public:

	//конструктор за замовчуванням( дріб 0/1)
	Drib()
	{
		setA(0);
		setB(1);
	}

	//конструктор з  1 параметром (знаменник у дробу == 1)
	Drib(int a):a(a)
	{
		setB(1);
	}

	//конструктор з  2 параметрами(передбачити валідацію для знаменника)
	Drib(int a, int b) :a(a), b(b)
	{
		if (b == 0)
		{
			cerr << "Wrong denomiantor 0! Apply value 1\n";
			setB(1);
		}

		if (b < 0)
		{
			setB(-getB());
			setA(-getA());
		}
	}

	~Drib()
	{
	}

	void setA(int num)
	{
		a = num;
	}

	int getA() const
	{
		return a;
	}

	void setB(int denom)
	{
		b = denom;
	}

	int getB() const
	{
		return b;
	}

	//метод виводу дробу на екран у вигляді чисельник / знаменник
	void print() 
	{
		this->abbr();
		cout << getA() << "/" << getB();
	}

	//метод скорочення дробу
	void abbr()
	{
		for (int i = 100; i >= 2; --i)
			if (getA() % i == 0 && getB() % i == 0)
			{
				setA(getA() / i);
				setB(getB() / i);
			}
	}

	//множення(*) двох дробів(метод класу)
	Drib operator * (const Drib &num2)
	{
		Drib answer;
		answer.setA(this->getA() * num2.getA());
		answer.setB(this->getB() * num2.getB());
		return answer;
	}

	//ділення(/) двох дробів(метод класу)
	Drib operator / (const Drib &num2)
	{
		Drib answer;
		answer.setA(this->getA() * num2.getB());
		answer.setB(this->getB() * num2.getA());
		return answer;
	}


	// (++) 2 форми, збільшення дробу на 1(методи класу)
	// 1 префікс
	Drib & operator ++ ()
	{
		this->setA(this->getA() + this->getB());
		return *this;
	}

	// 2 постфікс
	Drib operator ++ (int)
	{
		Drib old = *this;
		this->setA(this->getA() + this->getB());
		return old;
	}

	//порівняння дробів(>, <) (методи класу)
	// >
	bool operator > (const Drib &num2)
	{
		if (double(this->getA()) / double(this->getB()) > double(num2.getA()) / double(num2.getB()))
			return 1;
		else
			return 0;
	}

	// <
	bool operator < (const Drib &num2)
	{
		if (double(this->getA()) / double(this->getB()) < double(num2.getA()) / double(num2.getB()))
			return 1;
		else
			return 0;
	}

	//виклику функції() для зміни чисельника та знаменника  дробу, 
	//наприклад, результатом a(5, 7) повинно бути зміна дробу a на 5 / 7
	void operator() (int newA, int newB)
	{
		setA(newA);
		setB(newB);
	}

	//індексація([]),  що надаватиме доступ до чисельника чи знаменника  дробу за рядковим індексом
	//(наприклад, a[“num”] надаватиме доступ до чисельника дробу)
	int & operator[] (int index)
	{
		static int error = INT_MIN;
		if (index == 0)
			return a;
		else
			if (index == 1)
				return b;
		else
		{
			cerr << "Bad index\n";
			return error;
		}
	}

	//перетворення до типу int, що повертає цілу частину дробу, наприклад, для дробу 10/4 ціла частина рівна 2
	operator int()
	{
		return getA() / getB();
	}

	//перетворення до типу double, що повертає десятковий  дріб, 
	//наприклад, звичайному  дробу 10 / 4 відповідає десятковий дріб 2.5
	operator double()
	{
		return double(getA()) / double(getB());
	}


	friend Drib operator - (const Drib &num1, const Drib &num2);

};

//додавання(+) двох дробів(глобальна функція)
Drib operator + (const Drib &num1, const Drib &num2)
{
	Drib answer;
	answer.setA(num1.getA() * num2.getB() + num2.getA() * num1.getB());
	answer.setB(num1.getB() * num2.getB());
	return answer;
}

//віднімання(-) двох дробів(дружня глобальна функція)
Drib operator - (const Drib &num1, const Drib &num2)
{
	Drib answer;
	answer.a = num1.a * num2.b - num2.a * num1.b;
	answer.b = num1.b * num2.b;
	return answer;
}

// (--) 2 форми, зменшення дробу на 1(глобальні функції)
// 1 префікс
Drib & operator -- (Drib &num)
{
	num.setA(num.getA() - num.getB());
	return num;
}

// 2 постфікс
Drib operator -- (Drib &num, int)
{
	Drib old = num;
	num.setA(num.getA() - num.getB());
	return old;
}

//порівняння дробів (==, !=) (глобальні функції)
// ==
void operator == (const Drib &num1, const Drib &num2)
{
	if (num1.getA() == num2.getA() && num1.getB() == num2.getB())
		cout << true << endl;
	else
		cout << false << endl;
}

// !=
void operator != (const Drib &num1, const Drib &num2)
{
	if (num1.getA() != num2.getA() || num1.getB() != num2.getB())
		cout << true << endl;
	else
		cout << false << endl;
}


//потокові операції для введення та виведення дробу
// <<
std::ostream & operator  << (std::ostream & os, const Drib & num)
{
	os << num.getA() << "/" << num.getB();
	return os;
}

// >>
std::istream & operator  >> (std::istream & is, Drib & num)
{
	int n;
	cout << endl << "numerator = ";
	is >> n;
	num.setA(n);
	cout << endl << "denominator = ";
	is >> n;
	num.setB(n);
	return is;
}

