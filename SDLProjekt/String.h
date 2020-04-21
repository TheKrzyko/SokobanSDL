#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

class String
{
	char* cstr;
	int size;

public:
	String()
	{
		size = 0;
		cstr = new char[size+1];
		cstr[0] = '\0';
	}
	String(const char* cString)
	{
		size = strlen(cString);
		cstr = new char[size + 1];
		for (int i = 0; i < size; i++)
		{
			cstr[i] = cString[i];
		}
		cstr[size] = '\0';
	}
	String(const String& string)
	{
		size = string.getSize();
		cstr = string.getCopy();
	}
	~String()
	{
		delete[] cstr;
	}
	char* getCopy() const
	{
		char* copy = new char[size+1];
		for(int i = 0; i <= size; i++)
		{
			copy[i] = cstr[i];
		}
		return copy;
	}
	char* getCstr() const
	{
		return cstr;
	}
	int getSize() const
	{
		return size;
	}
	
	String operator=(char* cString)
	{
		size = strlen(cString);
		delete cstr;
		cstr = new char[size+1];
		for(int i = 0; i < size; i++)
		{
			cstr[i] = cString[i];
		}
		cstr[size] = '\0';
		return *this;
	}
	String operator=(const String& string)
	{
		delete cstr;
		cstr = string.getCopy();
		size = string.getSize();
		return *this;
	}
	String operator+(const char* cString)
	{
		int cSize = strlen(cString);
		char* cResult = new char[cSize + getSize() + 1];
		for(int i = 0; i < getSize(); i++)
		{
			cResult[i] = cstr[i];
		}
		for(int i = 0; i < cSize; i++)
		{
			cResult[i + getSize()] = cString[i];
		}
		cResult[cSize + getSize()] = '\0';
		String result(cResult);
		delete[] cResult;
		return result;
	}
	String operator+(const char ch)
	{
		char* cResult = new char[getSize() + 2];
		for (int i = 0; i < getSize(); i++)
		{
			cResult[i] = cstr[i];
		}
		cResult[getSize()] = ch;
		
		cResult[getSize()+1] = '\0';
		String result(cResult);
		delete[] cResult;
		return result;
	}
	friend String operator+(const char* cString, const String& string)
	{
		int cSize = strlen(cString);
		char* cResult = new char[cSize + string.getSize() + 1];
		for (int i = 0; i < cSize; i++)
		{
			cResult[i] = cString[i];
		}
		for (int i = 0; i < string.getSize(); i++)
		{
			cResult[i + cSize] = string.cstr[i];
		}
		
		cResult[cSize + string.getSize()] = '\0';
		String result(cResult);
		delete[] cResult;
		return result;
	}
	friend String operator+(const char ch, const String& string)
	{
		char* cResult = new char[string.getSize() + 2];

		cResult[0] = ch;
		
		for (int i = 0; i < string.getSize(); i++)
		{
			cResult[i + 1] = string.cstr[i];
		}

		cResult[string.getSize() + 1] = '\0';
		String result(cResult);
		delete[] cResult;
		return result;
	}
	String& operator+=(char* cString)
	{
		(*this) = (*this) + cString;
		return *this;
	}
	String& operator+=(char ch)
	{
		(*this) = (*this) + ch;
		return *this;
	}
	String operator+(String string)
	{
		(*this) += string.getCstr();
		return (*this);
	}
	bool operator==(const String& string) const
	{
		if (getSize() != string.getSize())
			return false;
		for(int i = 0; i < getSize(); i++)
		{
			if (cstr[i] != string.cstr[i])
				return false;
		}
		return true;
	}
	bool operator!=(const String& string) const
	{
		return !operator==(string);
	}
	char& operator[](const int& pos)
	{
		return cstr[pos];
	}
	operator char*() const
	{
		return cstr;
	}

};
inline String toString(int number)
{
	char out[50];
	snprintf(out, 50, "%i", number);
	return String(out);
}
inline String toString(double number)
{
	char out[50];
	snprintf(out, 50, "%f", number);
	return String(out);
}
