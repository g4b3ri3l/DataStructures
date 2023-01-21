#pragma once

template<typename MyVector>
class VectorIterator
{
public:
	using ValueType = typename MyVector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	VectorIterator(PointerType ptr)
		: m_Ptr(ptr)
	{

	}

	VectorIterator& operator++()
	{
		m_Ptr++;
		return *this;
	}

	VectorIterator& operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator& operator--()
	{
		m_Ptr--;
		return *this;
	}

	VectorIterator& operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(m_Ptr + index);
	}

	PointerType operator->()
	{
		return m_Ptr;
	}

	ReferenceType operator*()
	{
		return *m_Ptr;
	}

	bool operator==(const VectorIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(const VectorIterator& other) const
	{
		return !(*this == other);
	}
private:
	PointerType m_Ptr;
};


template <typename T>
class MyVector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<MyVector<T>>;

	MyVector()
	{
		ReAlloc(2);
	}

	//releases memory and calls destructor on eahc element
	~MyVector()
	{
		Clear();
		::operator delete(m_Data, m_Capacity * sizeof(T));
	}

	void PushBack(const T& value)
	{
		if (m_Size >= m_Capacity)
		{
			ReAlloc((size_t)(m_Capacity * 1.5));
		}

		m_Data[m_Size] = value;
		m_Size++;
	}

	void PushBack(const T&& value) //move semantic
	{
		if (m_Size >= m_Capacity)
		{
			ReAlloc((size_t)(m_Capacity * 1.5));
		}

		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size >= m_Capacity)
			ReAlloc((size_t)(m_Capacity * 1.5));

		new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
		return m_Data[m_Size++];
	}

	void PopBack()
	{
		if (m_Size > 0)
		{
			m_Size--;
			m_Data[m_Size].~T();
		}
	}

	void Clear()
	{
		for (size_t i = 0; i < m_Size; i++)
		{
			m_Data[i].~T();
		}

		m_Size = 0;
	}

	const T& operator[](size_t index) const
	{
		return m_Data[index];
	}

	T& operator[](size_t index)
	{
		return m_Data[index];
	}

	size_t Size() const
	{
		return m_Size;
	}

	Iterator begin()
	{
		return Iterator(m_Data);
	}

	Iterator end()
	{
		return Iterator(m_Data + m_Size);
	}
private:
	T* m_Data = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;

	void ReAlloc(size_t newCapacity)
	{
		T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

		if (newCapacity < m_Size)
			m_Size = newCapacity;

		for (size_t i = 0; i < m_Size; i++) //moves elements into new block
			new(&newBlock[i]) T(std::move(m_Data[i]));

		for (size_t i = 0; i < m_Size; i++) //calls destructor on old blocl
		{
			m_Data[i].~T();
		}

		//releases memory from old block
		::operator delete(m_Data, m_Capacity * sizeof(T));
		//updates data pointer and capacity
		m_Data = newBlock;
		m_Capacity = newCapacity;
	}

};