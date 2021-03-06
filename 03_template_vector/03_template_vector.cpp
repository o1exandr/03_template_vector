/*
На оцінку 12
Завдання 2.
Перетворити раніше створений клас Вектор у шаблон класу.
o	Доповнити шаблон класу конструктором, що створює об’єкт Вектору на основі списку ініціалізації.
o	Додати до шаблону класу статичне поле, що буде рахувати кількість об’єктів відповідного класу
Протестувати роботу шаблону класу для  типів int(double),  string та  користувацького типу(Fraction чи ін).


*/


#include "stdafx.h"
#include <iostream> 
#include <string>
#include "class_fraction.cpp"

using namespace std;

template<typename T>
class Vector
{
private:

	T *buffer;
	int capacity;
	int size;

	static int count;

public:

	//Конструктор за замовчуванням – масив порожній
	Vector()
	{
		reserve(0);
		resize(0);
		//setSize(0);
		//setCapacity(0);
		buffer = new T[size]{};
		++count;
	}
	
	//Vector(size_t size) – резервує пам'ять для масиву, фактичний розмір = size, ємність- Ваша формула, елементи - нулі
	Vector(size_t size)
	{
		setSize(size);
		setCapacity(getSize() * 2);
		buffer = new T[size] {};
		++count;
	}

	//Vector(size_t size, int value) – резервує пам'ять для масиву, фактичний розмір = size, ємність- Ваша формула, елементи = value
	Vector(size_t size, T value)
	{
		setSize(size);
		setCapacity(getSize() * 2);
		buffer = new T[size];
		for (int i = 0; i < getSize(); i++)
			buffer[i] = value;
		++count;
	}

	//Конструктор копії
	Vector(const Vector &vector)
	{
		this->buffer = new T[size = vector.size];
		for (int i = 0; i < size; ++i)
			this->buffer[i] = vector.buffer[i];
		++count;
		cout << "Ctor copy\n";
	}

	//конструктор переносу
	Vector(Vector && vct)
	{
		this->capacity = vct.capacity;
		this->size = vct.size;
		buffer = vct.buffer;
		vct.buffer = nullptr;
		++count;
		cout << "\tmove ctor works\n";
	}

	//Оператор присвоєння з переносом
	Vector & operator = (Vector && vct)
	{
		if (this == &vct)
		{
			cout << "It was assigned itself(&)\n";
			return *this;
		}
		else
		{
			delete buffer;
			buffer = vct.buffer;
			this->capacity = vct.capacity;
			this->size = vct.size;

			buffer = new T[size];
			for (int i = 0; i < size; i++)
				this->buffer[i] = vct.buffer[i];

			delete vct.buffer;
			vct.buffer = nullptr;
			cout << "\toperator= (&&) work\n";
		}
		++count;
		return *this;
	}


	//Деструктор
	~Vector()
	{
		delete buffer;
		buffer = nullptr;
		--count;
	}

	int getCapacity()const
	{
		return capacity;
	}

	void setCapacity(int c)
	{
		if (c < 1)
			c = 1;
		capacity = c;
	}

	int getSize()const
	{
		return size;
	}

	void setSize(int s)
	{
		if (s < 0)
			s = 0;
		size = s;
	}

	int getCount()const
	{
		return count;
	}

	//Метод перевірки чи вектор пустий(чи актуальна довжина =0, bool empty())
	bool empty()
	{
		if (size == 0)
			return 1;
		else
			return 0;
	}

	//Метод встановлення(зміни) елемента за індексом(void setValue(int index, T value)
	void setValue(int index, T value)
	{
		buffer[index] = value;
	}

	//Метод доступу(читання) елемента за індексом
	T getValue(int index) const
	{
		return buffer[index];
	}

	//Метод додавання нового елемента(pushBack(int elem)) у кінець масиву( при цьому, якщо потрібно то змінювати capacity)
	void pushBack(T elem)
	{
		if (getSize() == getCapacity())
			setCapacity(getCapacity() + 2);
		setSize(getSize() + 1);
		setValue(size - 1, elem);
	}

	//Метод вилучення останнього  елемента(popBack(int elem)), перевіряти чи можна вилучити
	void popBack()
	{
		if (getSize() == 0)
			cout << "Array is empty";
		else
			--size;
	}

	//Метод, що повертає посилання на перший елемент вектору int &front(), 
	//якщо вектор пустий повертати посилання на деяку статичну локальну змінну методу
	int &front()
	{
		int static errorFront = 0;
		if (empty())
			return errorFront;
		else
			return buffer[0];
	}

	//Метод, що повертає посилання на останній елемент вектору int &back(), 
	//якщо вектор пустий повертати посилання на деяку статичну локальну змінну методу
	int &back()
	{
		int static errorFront = 0;
		if (empty())
			return errorFront;
		else
			return buffer[size - 1];
	}

	//Метод вставки нового елемента за вказаним індексом(валідувати індекс)
	void insElem(int index, T elem)
	{
		if (getSize() - 1 < index)
			cout << "Wrong index!\n";
		else
		{
			++size;
			if (getSize() >= getCapacity())
				setCapacity(getCapacity() * 1.5);
			for (int i = index; i < size - 1; i++)
				setValue(i + 1, getValue(i));
			setValue(index, elem);
		}
	}

	//Метод вилучення елемента за індексом(валідувати індекс)
	void delElem(int index)
	{
		if (getSize() - 1 < index)
			cout << "Wrong index!\n";
		else
		{
			for (int i = index; i < size - 1; i++)
				setValue(i, getValue(i + 1));
			--size;
		}
	}

	//Метод  очистки вектору(clear()), capacity    не змінювати
	void clear()
	{
		setSize(0);
	}

	//Метод зміни capacity(reserve(size_t newCapacity),  
	//дані не втрачаються при збільшення  capacity, не дозволяти зменшувати  capacity  
	void reserve(size_t newCapacity)
	{
		if (getCapacity() > newCapacity)
			cout << "Wrong capacity!\n";
		else
			setCapacity(newCapacity);
	}

	//Метод зміни фактичної довжини масиву void resize(size_t newSize, int value), 
	//ємність масиву якщо потрібно - збільшується
	void resize(size_t newSize, T value)
	{
		if (getSize() > newSize)
			cout << "Wrong size!\n";
		else
			if (getCapacity() < newSize)
			{
				setCapacity(newSize * 1.5);
				int oldSize = getSize();
				setSize(newSize);
				for (int i = oldSize; i < getSize(); i++)
					setValue(i, value);
			}
			else
			{
				int oldSize = getSize();
				setSize(newSize);
				for (int i = oldSize; i < getSize(); i++)
					setValue(i, value);
			}
	}

	//Метод виводу  масиву
	void print()
	{
		if (buffer == nullptr)
			cout << "Empty!\n";
		else
			for (int i = 0; i < getSize(); i++)
				cout << getValue(i) << "\t";
		cout << endl;
	}


};


template<typename T>
int Vector<T>::count = 0;


int main()
{
	cout << "\nInt\n\n";
	Vector<int> v1(2); // фактичний розмір = 2, елементи нулі, buffer -> [0][0], 
				  //buffer - може вказувати на більшу ділянку, якщо capacity більше(capcity = 4, то buffer -> [0][0][.][.])
	v1.print();
	v1.pushBack(10);
	v1.pushBack(20);
	v1.print();
	cout << "The size of v is " << v1.getSize() << endl; // 4
	cout << "The capacity of v is " << v1.getCapacity() << endl; // >=4, якась Ваша формула, н-д, якщо ємності не вистачає можна збільшувати ємність масиву з певним коефіціентом(1.5 чи 2)
	v1.print(); // 0 0 10 20
	if (!v1.empty())// якщо не пусто
		v1.popBack(); // вилучили останній
	v1.print(); // 0 0 10
	cout << "The size of v is " << v1.getSize() << endl; // 3
	v1.reserve(20); // capacity = 20, size = яке було(3)
	v1.front() = 1234; // перший елемент замінили на 1234
	v1.print();
	cout << "Insert elem 100 in 2 position\n";
	v1.insElem(2, 100);// size 4
	v1.print();
	Vector<int> v2(v1);
	v2.print();
	v1.clear();
	cout << "The size of v after clearing is " << v1.getSize() << endl; //size 0

	cout << "\nDouble\n\n";
	Vector<double> vd(3, 5.0);
	vd.print();
	vd.pushBack(10);
	vd.pushBack(20);
	vd.print();
	
	//не поздужав я, на жаль, вивід string. свариться на індекс елемента при присвоєнні, а що хоче - не розумію
	/*
	cout << "\nString\n\n";
	Vector<string> vs(1 , "one");
	//cout << "Size: " << vs.getSize() << endl;
	vs.pushBack("t");
	vs.print();
	*/
	
	
	cout << "\nFraction\n\n";
	Drib one(1, 3);
	Drib two(2, 5);
	Vector<Drib> vDrib(1, one);
	vDrib.pushBack(two);
	vDrib.print();
	cout << "Q-ty of Drib: " << vDrib.getCount();
	
	




	cout << endl;
	system("pause");
	return 0;
}


