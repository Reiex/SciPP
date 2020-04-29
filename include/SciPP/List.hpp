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
#include <limits.h>

namespace scp
{
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
		/** \brief Retourne l'indice i le plus petit tel que (*this)[i] == x. et la taille de la liste si l'élément n'est pas présent*/
		unsigned int find(T const& x) const;
		/**
		 * \brief Trie la liste dans l'ordre croissant selon key((*this)[i]) entre les indices i inclus et j exclus avec i > j.
		 */
		void sort(int (*key)(T const&), unsigned int i, unsigned int j);
		/**
		 * \brief Trie la liste dans l'ordre croissant selon key((*this)[i]).
		 *
		 * Le tri utilisé est un tri par tas.
		 */
		void sort(int (*key)(T const&));

		/**
		 * \todo unsigned int find(T const& x);
		 * \todo void sort(int (*key)(T const&));
		 */

		 /** \brief Concaténation de deux listes. */
		List<T>& operator+=(List<T> const& l);
		/**
		 * \brief Comparaison de deux listes.
		 *
		 * Deux listes sont égales si et seulement si elles font la même taille et que tout leurs éléments sont égaux
		 */
		bool operator==(List<T> const& l) const;
		/**
		 * \brief Comparaison de deux listes.
		 *
		 * Deux listes sont égales si et seulement si elles font la même taille et que tout leurs éléments sont égaux
		 */
		bool operator!=(List<T> const& l) const;

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

		return *this;
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

		return *this;
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

	template<typename T> unsigned int List<T>::find(T const& x) const
	{
		for (unsigned int i(0); i < m_n; i++)
			if (m_x[i] == x)
				return i;

		return m_n;
	}

	template<typename T> void List<T>::sort(int (*key)(T const&))
	{
		for (unsigned int i(0); i < m_n / 2; i++)
		{
			bool twoLeaves(2 * i + 1 < m_n);
			if (key(m_x[i]) < key(m_x[2 * i]) || (twoLeaves && key(m_x[i]) < key(m_x[2 * i + 1])))
			{
				unsigned int j(2 * i);
				if (twoLeaves && key(m_x[2 * i + 1]) > key(m_x[2 * i]))
					j++;

				while (key(m_x[j / 2]) < key(m_x[j]))
				{
					T tmp(m_x[j]);
					m_x[j] = m_x[j / 2];
					m_x[j / 2] = tmp;
					j /= 2;
				}
			}
		}

		for (unsigned int i(m_n - 1); i != UINT_MAX; i--)
		{
			T tmp(m_x[i]);
			m_x[i] = m_x[0];
			m_x[0] = tmp;

			unsigned int j(0);
			while ((2 * j < i && key(m_x[j]) < key(m_x[2 * j])) || (2 * j + 1 < i && key(m_x[j]) < key(m_x[2 * j + 1])))
			{
				if (2 * j + 1 >= i || key(m_x[2 * j]) > key(m_x[2 * j + 1]))
				{
					tmp = m_x[j];
					m_x[j] = m_x[2 * j];
					m_x[2 * j] = tmp;
					j = 2 * j;
				}
				else
				{
					tmp = m_x[j];
					m_x[j] = m_x[2 * j + 1];
					m_x[2 * j + 1] = tmp;
					j = 2 * j + 1;
				}
			}
		}
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

	template<typename T> bool List<T>::operator==(List<T> const& l) const
	{
		if (m_n != l.m_n)
			return false;

		for (unsigned int i(0); i < m_n; i++)
			if (m_x[i] != l.m_x[i])
				return false;

		return true;
	}

	template<typename T> bool List<T>::operator!=(List<T> const& l) const
	{
		return !(*this == l);
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
}
