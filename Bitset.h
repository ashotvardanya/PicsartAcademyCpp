#pragma once
#include <limits>
#include <string>
#include <iostream>

template <size_t n>
class bitset
{
public:
	bitset();
	~bitset();
	bitset(const bitset& other);

public:

	size_t Size();
	unsigned int count();
	bool test(size_t pos);
	bool none();
	bool any();
	bool all();

	void set(int pos);
	void reset(int pos);
	void flip(int pos);
	std::string to_string();
	bool& operator[](int pospos);
private:

	void clear();

	unsigned int* m_arr;
	int size;
};



template <size_t n>
bitset<n>::bitset()
{
	if (n < 0)
		throw "Size of your bitset is not a natural number!\n";
	if (n % 32 == 0)
		size = n / 32;
	else
		size = n / 32 + 1;
	m_arr = new unsigned int[size];
	for (int i = 0; i < size; ++i)
		m_arr[i] = 0;

}

template <size_t n>
void bitset<n>::clear()
{
	delete[] m_arr;
	m_arr = nullptr;

}

template <size_t n>
bitset<n>::~bitset()
{
	clear();
}

template <size_t n>
bitset<n>::bitset(const bitset& other)
{

	if (this->Size() < other.size)
		throw("The size of your original bitset is too big!");
	size = other.size;
	clear();
	this->m_arr = new unsigned int[size];
	for (int i = 0; i < other.size; ++i)
		this->m_arr[i] = other.m_arr[i];

}

template <size_t n>
size_t bitset<n>::Size()
{
	return n;
}

template <size_t n>
unsigned int bitset<n>::count()
{
	bitset<n> other = *this;
	unsigned int count = 0;
	unsigned int mask = 1;
	for (int i = 0; i < other.size; ++i)
	{

		for (int j = 0; j < 32; ++j)
		{
			count += (other.m_arr[i] & mask);
			other.m_arr[i] = other.m_arr[i] >> 1;

		}
	}
	return count;
}


template <size_t n>
bool bitset<n>::test(size_t pos)
{
	if (pos > n)
		throw ("The number is too large!");
	int m = pos / 32;
	int mask = 1;
	if (pos % 32 == 0)
	{
		m--;
		mask << 31;
	}
	mask << (pos % 32 - 1);
	return (m_arr[m] & mask);
}

template <size_t n>
bool bitset<n>::none()
{
	for (int i = 0; i < size; ++i)
	{
		if (m_arr[i] != 0)
			return 0;
	}
	return 1;
}

template <size_t n>
bool bitset<n>::any()
{
	return (!none());
}

template <size_t n>
bool bitset<n>::all()
{
	if (size != 1)
		for (int i = 0; i < size; ++i)
		{
			if (m_arr[i] != UINT_MAX)
				return 0;
		}
	else
	{
		unsigned int tmp = 1;
		for (int i = 0; i < n - 1; i++)
		{
			tmp = tmp << 1;
			tmp += 1;
		}
		return(m_arr[0] == tmp);

	}
	return 1;
}

template <size_t n>
void bitset<n>::set(int pos)
{
	if (pos > n) { throw ("The number is too large!"); }
	int m = pos / 32;
	int mask = 1;
	if (pos % 32 == 0)
	{
		m--;
		mask = mask << 31;
	}
	mask = mask << (pos % 32 - 1);
	m_arr[m] = m_arr[m] | mask;
}

template <size_t n>
void bitset<n>::reset(int pos)
{
	if (pos > n)
		throw ("The number is too large!");
	int m = pos / 32;
	unsigned int mask = UINT_MAX;
	if (pos % 32 == 0)
	{
		m--;
		mask = mask >> 1;
	}
	else
	{
		mask = mask << 1;
		for (int i = 0; i < (pos % 32 - 1); ++i)
		{
			mask = mask << 1;
			mask += 1;
		}
	}
	m_arr[m] = m_arr[m] & mask;
}

template <size_t n>
void bitset<n>::flip(int pos)
{
	if (pos > n)
		throw ("The number is too large!");
	int m = pos / 32;
	int mask = 1;
	if (pos % 32 == 0)
	{
		m--;
		mask = mask << 31;
	}

	mask = mask << (pos % 32 - 1);
	m_arr[m] = (m_arr[m] ^ mask);

}

template <size_t n>
std::string bitset<n>::to_string()
{

	unsigned int mask = 1 << (n - 1);
	std::string s = {};
	if (size == 1)
	{
		for (int i = 0; i < n; i++)
		{
			s.push_back((m_arr[0] & mask) ? '1' : '0');
			mask = mask >> 1;
		}
	}
	else
	{
		mask = 1 << (n % 32 - 1);
		for (int j = 0; j < n % 32; ++j)
		{
			s.push_back((m_arr[size - 1] & mask) ? '1' : '0');
			mask = mask >> 1;
		}
		for (int i = size - 2; i >= 0; --i)
		{
			int temp = m_arr[i];
			mask = 1 << 31;
			for (int j = 0; j < 32; ++j)
			{
				s.push_back((temp & mask) ? '1' : '0');
				mask = mask >> 1;
			}
		}

	}


	return s;
}

template <size_t n>
bool& bitset<n>::operator[](int pos)
{
	if (pos > n)
		throw ("The number is too large!");
	int m = pos / 32;
	int mask = 1;
	if (pos % 32 == 0)
	{
		m--;
		mask = mask << 31;
	}
	mask = mask << (pos % 32 - 1);
	bool b = (m_arr[m] & mask) % 2;
	return b;
}

