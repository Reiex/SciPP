#pragma once

/**
 * \file Containers/List.hpp
 * \brief Ensemble des fonctions et classes permettant la manipulation de listes
 * \author Reiex
 * 
 * Pour une description plus détaillée, voir la description de la classe List
 * 
 */

#include <iostream>
#include <exception>
#include <initializer_list>

/**
 * \class List
 * \brief Classe permettant de manipuler des listes
 * 
 * Par liste on entend un tableau réalloué dynamiquement.
 * 
 * Cette classe est template mais ne requiert que les opérateurs d'affectations de copie et de déplacement classiques.
 */
template<typename T> class List
{
	public:

		/** \brief Erreur renvoyée lors d'une tentative d'accès à un indice invalide de la liste. */
		class IndexException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		/** \brief Constructeur par défaut, initialise une liste vide. */
		List();
		/** \brief Initialise une liste de taille n contenant n instances T(). */
		List(unsigned int n);
		/** \brief Initialise une liste avec une liste d'initialisation. */
		List(std::initializer_list<T> tab);
		/** \brief Initialise une liste contenant les éléments du tableau tab */
		List(T const* tab, unsigned int taille);
		List(List<T> const& l);
		List(List<T>&& l);

		List<T>& operator=(List<T> const& l);
		List<T>& operator=(List<T>&& l);
		T& operator[](unsigned int i);
		T const& operator[](unsigned int i) const;
		
		/** \brief Retourne la taille de la liste. */
		unsigned int size() const;
		/** \brief Ajout un élément à la fin de la liste. */
		void append(T const& x);
		/**
		 * \brief Retire l'élément d'indice i de la liste.
		 * 
		 * Tout les éléments d'indice supérieur à i sont alors décalés d'un rang.
		 */
		void remove(unsigned int i);

		/**
		 * \todo unsigned int find(T const& x);
		 * \todo void sort(int (*key)(T const&));
		 */

		/** \brief Concaténation de deux listes. */
		List<T>& operator+=(List<T> const& l);

		~List();

	private:
		
		void liberer();
		void incAllocSize();

		T* m_x;
		unsigned int m_n;
		unsigned int m_allocSize;
};


template<typename T> const char* List<T>::IndexException::what() const throw()
{
	return "Tentative d'accès à un indice invalide de la liste.";
}


template<typename T> List<T>::List() : m_n(0), m_allocSize(0), m_x(nullptr)
{

}

template<typename T> List<T>::List(unsigned int n) : List()
{
	if (n != 0)
	{
		m_n = n;
		while (m_n > m_allocSize)
			incAllocSize();
		m_x = new T[m_allocSize];
		for (unsigned int i(0); i < m_n; i++)
			m_x[i] = T();
	}
}

template<typename T> List<T>::List(std::initializer_list<T> tab) : List()
{
	if (tab.size() > 0)
	{
		m_n = tab.size();
		while (m_n > m_allocSize)
			incAllocSize();
		m_x = new T[m_allocSize];
		for (unsigned int i(0); i < m_n; i++)
			m_x[i] = tab.begin()[i];
	}
}

template<typename T> List<T>::List(T const* tab, unsigned int taille) : List()
{
	if (taille > 0)
	{
		m_n = taille;
		while (m_n > m_allocSize)
			incAllocSize();
		m_x = new T[m_allocSize];
		for (unsigned int i(0); i < m_n; i++)
			m_x[i] = tab[i];
	}
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
		incAllocSize();
		T* oldX(m_x);
		m_x = new T[m_allocSize];
		if (oldX != nullptr)
		{
			for (unsigned int i(0); i < m_n - 1; i++)
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

	for (unsigned int j(i); j < m_n; j++)
		m_x[j] = m_x[j + 1];
}


template<typename T> List<T>& List<T>::operator+=(List<T> const& l)
{
	if (m_n + l.m_n > m_allocSize)
	{
		while (m_n + l.m_n > m_allocSize)
			incAllocSize();
		T* oldX(m_x);
		m_x = new T[m_allocSize];
		if (oldX != nullptr)
		{
			for (unsigned int i(0); i < m_n - 1; i++)
				m_x[i] = oldX[i];
			delete[] oldX;
		}
	}

	for (unsigned int i(0); i < l.m_n; i++)
		m_x[m_n + i] = l.m_x[i];
	m_n += l.m_n;
}

template<typename T> List<T> operator+(List<T> const& a, List<T> const& b)
{
	List<T> c(a);
	c += b;

	return c;
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

template<typename T> void List<T>::incAllocSize()
{
	m_allocSize = m_allocSize == 0 ? 32 : m_allocSize * 2;
}


template<typename T> std::ostream& operator<<(std::ostream& stream, List<T> const& l)
{
	stream << "[";
	for (unsigned int i(0); i < l.size(); i++)
	{
		if (i != l.size() - 1)
			stream << l[i] << ", ";
		else
			stream << l[i];
	}

	stream << "]";

	return stream;
}
