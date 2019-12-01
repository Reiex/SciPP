#pragma once

#include <iostream>

/*
	T::operator=(T const&)
	ostream& operator<<(ostream&, T const&)
*/
template<typename T> class Liste
{
	public:

		Liste();
		Liste(Liste<T> const& l);

		Liste<T>& operator=(Liste<T> const& l);
		T& operator[](int i);
		T const& operator[](int i) const;

		void ajouter(T const& x);

		int taille() const;

		~Liste();

	private:

		struct Cellule
		{
			T x;
			Cellule* suivante;
		};

		Cellule* m_tete;
		Cellule* m_queue;
		int m_taille;
};


template<typename T> Liste<T>::Liste()
{
	m_taille = 0;
	m_tete = nullptr;
	m_queue = nullptr;
}

template<typename T> Liste<T>::Liste(Liste<T> const& l)
{
	m_taille = l.m_taille;
	m_tete = nullptr;
	m_queue = nullptr;

	if (m_taille == 0)
		return;

	m_tete = new Cellule;
	m_tete->x = l.m_tete->x;
	m_tete->suivante = new Cellule;

	Cellule* courante(m_tete), *lCourante(l.m_tete);
	for (int i(1); i < m_taille; i++)
	{
		courante = courante->suivante;
		lCourante = lCourante->suivante;
		courante->x = lCourante->x;
		courante->suivante = new Cellule;
	}

	delete courante->suivante;
	courante->suivante = nullptr;
	m_queue = courante;
}

template<typename T> Liste<T>& Liste<T>::operator=(Liste<T> const& l)
{
	Cellule *courante(m_tete), *tmp;
	while (courante != nullptr)
	{
		tmp = courante->suivante;
		delete courante;
		courante = tmp;
	}

	m_taille = l.m_taille;
	m_tete = nullptr;
	m_queue = nullptr;

	if (m_taille == 0)
		return *this;

	m_tete = new Cellule;
	m_tete->x = l.m_tete->x;
	m_tete->suivante = new Cellule;
	courante = m_tete;

	Cellule* lCourante(l.m_tete);
	for (int i(1); i < m_taille; i++)
	{
		courante = courante->suivante;
		lCourante = lCourante->suivante;
		courante->x = lCourante->x;
		courante->suivante = new Cellule;
	}

	delete courante->suivante;
	courante->suivante = nullptr;
	m_queue = courante;

	return *this;
}

template<typename T> T& Liste<T>::operator[](int i)
{
	if (i >= m_taille || i < 0)
		throw "L'indice n'est pas valide.";

	int j(0);
	Cellule* courante(m_tete);
	while (j < i)
	{
		courante = courante->suivante;
		j++;
	}

	return courante->x;
}

template<typename T> T const& Liste<T>::operator[](int i) const
{
	if (i >= m_taille || i < 0)
		throw "L'indice n'est pas valide.";

	int j(0);
	Cellule* courante(m_tete);
	while (j < i)
	{
		courante = courante->suivante;
		j++;
	}

	return courante->x;
}

template<typename T> void Liste<T>::ajouter(T const& x)
{
	m_taille++;

	if (m_tete == nullptr)
	{
		m_tete = new Cellule;
		m_tete->x = x;
		m_tete->suivante = nullptr;
		m_queue = m_tete;
		return;
	}

	m_queue->suivante = new Cellule;
	m_queue->suivante->x = x;
	m_queue->suivante->suivante = nullptr;
	m_queue = m_queue->suivante;
}

template<typename T> int Liste<T>::taille() const
{
	return m_taille;
}

template<typename T> Liste<T>::~Liste()
{
	Cellule *courante(m_tete), *tmp;
	while (courante != nullptr)
	{
		tmp = courante->suivante;
		delete courante;
		courante = tmp;
	}
}

template<typename T> std::ostream& operator<<(std::ostream& stream, Liste<T> const& l)
{
	stream << "[";
	for (int i(0); i < l.taille(); i++)
	{
		if (i != l.taille() - 1)
			stream << l[i] << ", ";
		else
			stream << l[i];
	}

	stream << "]";

	return stream;
}
