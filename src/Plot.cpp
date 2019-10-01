#include "Plot.h"

// Variables et fonctions internes

static const int TAILLE_PLOT[] = { 600, 600 };
static Courbe* COURBES(nullptr);
static Vecteur<sf::Image*> MATRICES;

void libererCourbes()
{
	Courbe* courrante(COURBES);
	Courbe* suivante(nullptr);

	while (courrante != nullptr)
	{
		suivante = courrante->suivante;
		delete courrante->figure;
		delete courrante;
		courrante = suivante;
	}

	COURBES = nullptr;
}

void libererMatrices()
{
	for (int i(0); i < MATRICES.taille(); i++)
		delete MATRICES[i];

	MATRICES.changerTaille(0);
}


// Variables et fonctions externes

void plot(long double x, long double y)
{
	Courbe* courbe(new Courbe);
	sf::VertexArray* figure(new sf::VertexArray(sf::LinesStrip, 1));

	courbe->min_x = x;
	courbe->max_x = x;
	courbe->min_y = y;
	courbe->max_y = y;

	(*figure)[0].position.x = x;
	(*figure)[0].position.y = y;
	(*figure)[0].color = sf::Color(0, 0, 0);

	courbe->figure = figure;
	courbe->suivante = nullptr;

	if (COURBES == nullptr)
	{
		COURBES = courbe;
	}
	else
	{
		Courbe* courrante(COURBES);

		while (courrante->suivante != nullptr)
		{
			courrante = courrante->suivante;
		}

		courrante->suivante = courbe;
	}
}

void plot(Vecteur<long double> x, Vecteur<long double> y)
{
	if (x.taille() != y.taille() || x.taille() < 1)
		throw "La taille des vecteurs est invalide.";

	int n(x.taille());

	Courbe* courbe(new Courbe);
	sf::VertexArray* figure(new sf::VertexArray(sf::LinesStrip, n));
	long double min_x(x[0]), max_x(x[0]), min_y(y[0]), max_y(y[0]);

	for (int i(0); i < n; i++)
	{
		if (x[i] < min_x)
			min_x = x[i];
		if (x[i] > max_x)
			max_x = x[i];
		if (y[i] < min_y)
			min_y = y[i];
		if (y[i] > max_y)
			max_y = y[i];
	}

	courbe->min_x = min_x;
	courbe->max_x = max_x;
	courbe->min_y = min_y;
	courbe->max_y = max_y;

	for (int i(0); i < n; i++)
	{
		(*figure)[i].position.x = x[i];
		(*figure)[i].position.y = y[i];
		(*figure)[i].color = sf::Color(0, 0, 0);
	}

	courbe->figure = figure;
	courbe->suivante = nullptr;

	if (COURBES == nullptr)
	{
		COURBES = courbe;
	}
	else
	{
		Courbe* courrante(COURBES);

		while (courrante->suivante != nullptr)
		{
			courrante = courrante->suivante;
		}

		courrante->suivante = courbe;
	}
}

void plot(Matrice<long double> M, long double min_z, long double max_z)
{
	int w(TAILLE_PLOT[0]), h(TAILLE_PLOT[1]);

	sf::Image* image(new sf::Image);
	image->create(w, h);

	float facteurX(float(M.taille()[0]) / w), facteurY(float(M.taille()[1]) / h);
	for (int x(0); x < w; x++)
	{
		for (int y(0); y < h; y++)
		{
			int i(facteurX * x), j(facteurY * y);

			if (M[i][j] < min_z)
				image->setPixel(x, y, sf::Color(0, 0, 0));
			else if (M[i][j] > max_z)
				image->setPixel(x, y, sf::Color(255, 255, 255));
			else
			{
				int color(255 * (M[i][j] - min_z) / (max_z - min_z));
				image->setPixel(x, y, sf::Color(color, color, color));
			}
		}
	}

	MATRICES.changerTaille(MATRICES.taille() + 1);
	MATRICES[MATRICES.taille() - 1] = image;

	libererCourbes();
}

void show(int framerate, bool animationCourbe)
{
	int w(TAILLE_PLOT[0]), h(TAILLE_PLOT[1]);

	// Calcule des coordonnées des points des courbes

	if (COURBES != nullptr)
	{
		Courbe* courrante(COURBES);
		long double min_x(courrante->min_x), max_x(courrante->max_x), min_y(courrante->min_y), max_y(courrante->max_y);
		while (courrante->suivante != nullptr)
		{
			courrante = courrante->suivante;

			min_x = courrante->min_x < min_x ? courrante->min_x : min_x;
			max_x = courrante->max_x > max_x ? courrante->max_x : max_x;
			min_y = courrante->min_y < min_y ? courrante->min_y : min_y;
			max_y = courrante->max_y > max_y ? courrante->max_y : max_y;
		}

		min_x -= 0.05*(max_x - min_x);
		max_x += 0.05*(max_x - min_x);
		min_y -= 0.05*(max_y - min_y);
		max_y += 0.05*(max_y - min_y);

		courrante = COURBES;

		while (courrante != nullptr)
		{
			for (int i(0); i < courrante->figure->getVertexCount(); i++)
			{
				(*courrante->figure)[i].position.x = w * ((*courrante->figure)[i].position.x - min_x) / (max_x - min_x);
				(*courrante->figure)[i].position.y = h * (1 - ((*courrante->figure)[i].position.y - min_y) / (max_y - min_y));
			}

			courrante = courrante->suivante;
		}
	}


	// Ouverture de la fenêtre

	sf::RenderWindow window(sf::VideoMode(w, h), "Plot SciPP");
	window.setFramerateLimit(framerate);

	sf::Event event;
	int t(0);
	Courbe* courbeAffichee(COURBES);
	while (window.isOpen())
	{
		window.display();
		window.clear(sf::Color(255, 255, 255));

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		if (MATRICES.taille() != 0)
		{
			sf::Texture texture;
			texture.loadFromImage(*MATRICES[t]);
			window.draw(sf::Sprite(texture));
			t = (t + 1) % MATRICES.taille();
		}
		else
		{
			if (COURBES != nullptr)
			{
				if (animationCourbe)
				{
					if (courbeAffichee->suivante == nullptr)
						courbeAffichee = COURBES;
					else
						courbeAffichee = courbeAffichee->suivante;

					if (courbeAffichee->figure->getVertexCount() == 1)
					{
						sf::CircleShape cercle;
						cercle.setRadius(3);
						cercle.setFillColor(sf::Color(0, 0, 0));
						cercle.setPosition((*courbeAffichee->figure)[0].position.x, (*courbeAffichee->figure)[0].position.y);
						window.draw(cercle);
					}
					else
						window.draw(*courbeAffichee->figure);
				}
				else
				{
					Courbe* courrante(COURBES);
					while (courrante != nullptr)
					{
						if (courrante->figure->getVertexCount() == 1)
						{
							sf::CircleShape cercle;
							cercle.setRadius(3);
							cercle.setFillColor(sf::Color(0, 0, 0));
							cercle.setPosition((*courrante->figure)[0].position.x, (*courrante->figure)[0].position.y);
							window.draw(cercle);
						}
						else
							window.draw(*courrante->figure);
						courrante = courrante->suivante;
					}
				}
			}
		}
	}

	libererCourbes();
	libererMatrices();
}
