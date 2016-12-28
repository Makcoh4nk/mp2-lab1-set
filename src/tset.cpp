// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp) , BitField(mp)
{
	if (mp >= 0) {
		MaxPower = mp;
		TBitField a(mp);
		BitField = a;
	}
	else {
		throw logic_error("Error description");
	}
}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()),BitField(bf)
{
	MaxPower = bf.GetLength();
	BitField = bf;
}

TSet::operator TBitField()
{
	TBitField temp(this->BitField);
	return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem >= 0) && (Elem < MaxPower))
		BitField.SetBit(Elem);
	else
		throw logic_error("Error description");
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem >= 0) && (Elem < MaxPower))
		BitField.ClrBit(Elem);
	else
		throw logic_error("Error description");
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.GetMaxPower();
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField ==s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp(BitField | s.BitField);
	return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem < MaxPower) && (Elem >= 0))
	{
		TSet temp(*this);
		temp.BitField.SetBit(Elem);
		return temp;
	}
	else
		throw logic_error("Error description");
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem < MaxPower) && (Elem >= 0)) 
	{
		BitField.ClrBit(Elem);
		return *this;
	}
	else 
		throw logic_error("Error description");
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp(BitField & s.BitField);
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(~BitField);
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int temp;
	char ch;
	do
	{
		istr >> ch;
	} while (ch != '{');
	do
	{
		istr >> temp;
		s.InsElem(temp);
		do
		{
			istr >> ch;
		} while ((ch != ',') && (ch != '}'));
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int i, n;
	char ch = ' ';
	ostr << "{";
	n = s.GetMaxPower();
	for (i = 0; i < n; ++i)
		if (s.IsMember(i))
		{
			ostr << ch << ' ' << i;
			ch = ',';
		}
	ostr << " }";
	return ostr;
}
