#include <iostream>

#include "MyArray.h"
#include "MyVector.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vector3() {}
	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar) {}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {}

	Vector3(const Vector3& other)
	{
		std::cout << "Copied!" << std::endl;
	}

	Vector3(const Vector3&& other) noexcept
	{
		std::cout << "Moved!" << std::endl;
	}

	~Vector3()
	{
		std::cout << "Destroyed!" << std::endl;
	}

	Vector3& operator=(const Vector3& other)
	{
		std::cout << "Copied!" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	Vector3& operator=(const Vector3&& other) noexcept
	{
		std::cout << "Moved!" << std::endl;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
};

template<typename T>
void PrintVector(const MyVector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << std::endl;

		std::cout << "--------------------------------\n";
	}
}

template<>
void PrintVector(const MyVector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i].x << ", " << vector[i].y << ", " << vector[i].z << std::endl;

		std::cout << "--------------------------------\n";
	}
}

int main()
{
	MyVector<int> values;
	values.EmplaceBack(1);
	values.EmplaceBack(2);
	values.EmplaceBack(3);
	values.EmplaceBack(4);
	values.EmplaceBack(5);

	std::cout << "Not using iterators:\n";
	for (int i = 0; i < values.Size(); i++)
	{
		std::cout << values[i] << std::endl;
	}

	std::cout << "Range-based for loop:\n";
	for (int value : values)
	{
		std::cout << value << std::endl;
	}

	std::cout << "Iterator:\n";
	for (MyVector<int>::Iterator it = values.begin(); it != values.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}