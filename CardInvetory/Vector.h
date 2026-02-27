#pragma once
#include <utility>
#include <assert.h>

template<typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointType = ValueType*;
	using ReferenceType = ValueType&;

	VectorIterator(PointType ptr)
		: ptr(ptr)
	{
	}

	VectorIterator& operator++()
	{
		ptr++;
		return *this;
	}

	VectorIterator& operator++(int)
	{
		VectorIterator prevIter = *this;
		(*this)++;
		return prevIter;
	}

	VectorIterator& operator--()
	{
		ptr--;
		return *this;
	}

	VectorIterator& operator--(int)
	{
		VectorIterator prevIter = *this;
		(*this)--;
		return prevIter;
	}

	ReferenceType operator->()
	{
		return ptr;
	}

	ReferenceType operator*()
	{
		return *ptr;
	}

	bool operator==(const ReferenceType& other) const
	{
		return ptr == other.ptr;
	}

	bool operator!=(const ReferenceType& other) const
	{
		return !(*this == other);
	}

private:
	PointType ptr = nullptr;
};

template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<T>>;

	Vector()
	{
		Reallocate(capacity);
	}

	Vector(int size)
		:size(size)
	{
		Reallocate(size);
	}

	~Vector()
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}
	}

	void Add(const T& value)
	{
		if (size == capacity)
		{
			Reallocate(capacity * 2);
		}
		data[size++] = value;
	}

	void Add(T&& value)
	{
		if (size == capacity)
		{
			Reallocate(capacity * 2);
		}
		data[size++] = std::move(value);
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < size);
		return data[index];
	}
	int Size() const { return size; }
	int Capacity() const { return capacity; }


	T* begin()
	{
		return data;
	}

	T* end()
	{
		return data + size;
	}

private:
	void Reallocate(int newCapacity)
	{
		T* newData = new T[newCapacity];
		if (data)
		{
			for (int i = 0; i < size; i++)
				newData[i] = std::move(data[i]);

			delete[] data;
		}

		data = newData;
		capacity = newCapacity;
	}

private:
	T* data = nullptr;

	int size = 0;
	int capacity = 2;
};

