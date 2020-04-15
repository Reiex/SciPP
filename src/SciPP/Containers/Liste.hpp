#pragma once


#include <iostream>
#include <exception>

template<typename T> class List
{
	public:

		class IndexException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		List();
		List(List<T> const& l);
		List(List<T>&& l);

		List<T>& operator=(List<T> const& l);
		List<T>& operator=(List<T>&& l);
		T& operator[](unsigned int i);
		T const& operator[](unsigned int i) const;
		
		unsigned int size() const;
		void append(T const& x);
		void remove(unsigned int i);

		~List();

	private:
		
		void liberer();

		T* m_x;
		unsigned int m_n;
		unsigned int m_allocSize;
};


template<typename T> const char* List<T>::IndexException::what() const throw()
{
	return "Tentative d'accès à un indice invalide de la liste.";
}


template<typename T> List<T>::List() : m_n(0), m_x(nullptr)
{

}

template<typename T> List<T>::List(List<T> const& l) : List()
{
	*this = l;
}

template<typename T> List<T>::List(List<T>&& l) : List()
{
	*this = std::move(l);
}


template<typename T> List<T>& List<T>::operator=(List<T> const& l)
{
	liberer();

	m_n = l.m_n;
	m_allocSize = l.m_allocSize;
	m_x = new T[m_allocSize];
	for (unsigned int i(0); i < m_n; i++)
		m_x[i] = l.m_x[i];
}

template<typename T> List<T>& List<T>::operator=(List<T>&& l)
{
	liberer();

	m_n = l.m_n;
	m_allocSize = l.m_allocSize;
	m_x = l.m_x;

	l.m_n = 0;
	l.m_allocSize = 0;
	l.m_x = nullptr;
}

template<typename T> T& List<T>::operator[](unsigned int i)
{
	if (i >= m_n)
		throw IndexException();

	return m_x[i];
}

template<typename T> T const& List<T>::operator[](unsigned int i) const
{
	if (i >= m_n)
		throw IndexException();

	return m_x[i];
}


template<typename T> unsigned int List<T>::size() const
{
	return m_n;
}

template<typename T> void List<T>::append(T const& x)
{
	m_n += 1;
	if (m_n > m_allocSize)
	{
		m_allocSize = m_allocSize == 0 ? 32 : m_allocSize * 2;
		T* oldX(m_x);
		m_x = new T[m_allocSize];
		if (oldX != nullptr)
		{
			for (int i(0); i < m_n - 1; i++)
				m_x[i] = oldX[i];
			delete[] oldX;
		}
	}

	m_x[m_n - 1] = x;
}

template<typename T> void List<T>::remove(unsigned int i)
{
	if (i >= m_n)
		throw IndexException();

	m_n--;

	for (int j(i); j < m_n; j++)
		m_x[j] = m_x[j + 1];
}


template<typename T> List<T>::~List()
{
	liberer();
}


template<typename T> void List<T>::liberer()
{
	if (m_x != nullptr)
	{
		delete[] m_x;
		m_x = nullptr;
		m_n = 0;
		m_allocSize = 0;
	}
}
