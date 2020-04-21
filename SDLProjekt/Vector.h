#pragma once
template<typename T>
class Vector
{
	T* array = nullptr;
	int size = 0;
public:
	Vector();
	Vector(int size);
	Vector(const Vector<T>& val);
	~Vector();

	int getSize();
	void pushBack(T val);
	void clear();
	void setSize(int size);
	bool contain(const T& val);
	T* find(bool(*condition)(T));
	T& operator[](int i)
	{
		return array[i];
	}
	Vector<T>& operator=(const Vector<T>& vec)
	{
		size = vec.size;
		if (array != nullptr)
			delete[] array;
		array = new T[size];
		for (int i = 0; i < size; i++)
		{
			array[i] = vec.array[i];
		}
		return *this;
	}
};

template <typename T>
bool Vector<T>::contain(const T& val)
{
	for(int i = 0; i < size; i++)
	{
		if (array[i] == val)
			return true;
	}
	return false;
}

template <typename T>
T* Vector<T>::find(bool(*condition)(T))
{
	for (int i = 0; i < size; i++)
	{
		if (condition(array[i]))
			return &(array[i]);
	}
	return nullptr;
}

template <typename T>
Vector<T>::Vector()
{
}

template <typename T>
Vector<T>::Vector(int size)
{
	this->size = size;
	array = new T[size];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& val)
{
	size = val.size;
	array = new T[size];
	for(int i = 0; i < size; i++)
	{
		array[i] = val[i];
	}
}

template <typename T>
Vector<T>::~Vector()
{
	if (array != nullptr)
		delete[] array;
}

template <typename T>
int Vector<T>::getSize()
{
	return size;
}

template <typename T>
void Vector<T>::pushBack(T val)
{
	size++;
	T* newArray = new T[size];
	for(int i = 0; i < size-1; i++)
	{
		newArray[i] = array[i];
	}
	newArray[size - 1] = val;
	if (array != nullptr)
		delete[] array;
	array = newArray;
}

template <typename T>
void Vector<T>::clear()
{
	if(array != nullptr)
		delete[] array;
	size = 0;
	array = nullptr;
}

template <typename T>
void Vector<T>::setSize(int size)
{
	clear();
	array = new T[size];
	this->size = size;
}

