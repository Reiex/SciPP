#include "Plot.h"

static const int TAILLE_PLOT[] = { 600, 600 };
std::vector<Timeline*> Timeline::timelineList;

Timeline::Timeline()
{
	timelineList.push_back(this);
	m_delay = 1.0/24.0;
	m_border = Vecteur<long double>(4);
	m_borderSet = false;
}

void Timeline::setFramerate(int framerate)
{
	m_delay = 1.0/framerate;
}

void Timeline::plot(long double x, long double y)
{
	sf::VertexArray figure(sf::LinesStrip, 1);

	if (!m_borderSet)
	{
		m_borderSet = true;
		m_border[0] = x;
		m_border[1] = x;
		m_border[2] = y;
		m_border[3] = y;
	}
	else
	{
		m_border[0] = x < m_border[0] ? x: m_border[0];
		m_border[1] = x > m_border[1] ? x: m_border[1];
		m_border[2] = y < m_border[2] ? y: m_border[2];
		m_border[3] = y > m_border[3] ? y: m_border[3];
	}

	figure[0].position.x = x;
	figure[0].position.y = y;
	figure[0].color = sf::Color(0, 0, 0);

	m_courbes.push_back(figure);
}

void Timeline::plot(Vecteur<long double> x, Vecteur<long double> y)
{
	if (x.taille() != y.taille() || x.taille() < 1)
		throw "La taille des vecteurs est invalide.";

	int n(x.taille());

	sf::VertexArray figure(sf::LinesStrip, n);
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

	if (!m_borderSet)
	{
		m_borderSet = true;
		m_border[0] = min_x;
		m_border[1] = max_x;
		m_border[2] = min_y;
		m_border[3] = max_y;
	}
	else
	{
		m_border[0] = min_x < m_border[0] ? min_x: m_border[0];
		m_border[1] = max_x > m_border[1] ? max_x: m_border[1];
		m_border[2] = min_y < m_border[2] ? min_y: m_border[2];
		m_border[3] = max_y > m_border[3] ? max_y: m_border[3];
	}

	for (int i(0); i < n; i++)
	{
		figure[i].position.x = x[i];
		figure[i].position.y = y[i];
		figure[i].color = sf::Color(0, 0, 0);
	}

	m_courbes.push_back(figure);
}

void Timeline::plot(Matrice<long double> M, long double min_z, long double max_z)
{
	int w(TAILLE_PLOT[0]), h(TAILLE_PLOT[1]);

	sf::Image image;
	image.create(w, h);

	float facteurX(float(M.taille()[0]) / w), facteurY(float(M.taille()[1]) / h);
	for (int x(0); x < w; x++)
	{
		for (int y(0); y < h; y++)
		{
			int i(facteurX * x), j(facteurY * y);

			if (M[i][j] < min_z)
				image.setPixel(x, y, sf::Color(0, 0, 0));
			else if (M[i][j] > max_z)
				image.setPixel(x, y, sf::Color(255, 255, 255));
			else
			{
				int color(255 * (M[i][j] - min_z) / (max_z - min_z));
				image.setPixel(x, y, sf::Color(color, color, color));
			}
		}
	}

	m_matrices.push_back(image);
	m_courbes.clear();
}

void Timeline::show()
{
	int w(TAILLE_PLOT[0]), h(TAILLE_PLOT[1]);

	if (timelineList.size() == 0)
	{
		return;
	}

	// Calcule des coordonnées des points des courbes

	Vecteur<long double> border(timelineList[0]->m_border);
	for (int i(1); i < timelineList.size(); i++)
	{
		if (timelineList[i]->m_courbes.size() != 0)
		{
			Vecteur<long double>& other(timelineList[i]->m_border);
			border[0] = other[0] < border[0] ? other[0] : border[0];
			border[1] = other[1] > border[1] ? other[1] : border[1];
			border[2] = other[2] < border[2] ? other[2] : border[2];
			border[3] = other[3] > border[3] ? other[3] : border[3];
		}
		else if (timelineList[i]->m_matrices.size() == 0)
		{
			timelineList.erase(timelineList.begin() + i);
			i--;
		}
	}

	border[0] -= 0.05*(border[1] - border[0]);
	border[1] += 0.05*(border[1] - border[0]);
	border[2] -= 0.05*(border[3] - border[2]);
	border[3] += 0.05*(border[3] - border[2]);

	if (border[0] == border[1])
	{
		border[0] -= 0.5;
		border[1] += 0.5;
	}
	if (border[2] == border[3])
	{
		border[2] -= 0.5;
		border[3] += 0.5;
	}

	for (int i(0); i < timelineList.size(); i++)
	{
		for (int j(0); j < timelineList[i]->m_courbes.size(); j++)
		{
			sf::VertexArray& courbe(timelineList[i]->m_courbes[j]);
			
			for (int k(0); k < courbe.getVertexCount(); k++)
			{
				courbe[k].position.x = w*(courbe[k].position.x - border[0]) / (border[1] - border[0]);
				courbe[k].position.y = h*(1 - (courbe[k].position.y - border[2]) / (border[3] - border[2]));
			}
		}
	}

	// Initialisation des courbes/matrices affichées

	std::vector<int> affichees;
	std::vector<sf::Clock> clocks;
	bool matriceTrouvee(false);
	for (int i(0); i < timelineList.size(); i++)
	{
		affichees.push_back(0);
		clocks.push_back(sf::Clock());

		if (timelineList[i]->m_matrices.size() != 0)
		{
			if (matriceTrouvee)
				throw "On ne peut pas dessiner plus d'une matrice à la fois.";

			Timeline* t(timelineList[0]);

			timelineList[0] = timelineList[i];
			timelineList[i] = t;

			matriceTrouvee = true;
		}
	}

	// Ouverture de la fenêtre

	sf::RenderWindow window(sf::VideoMode(w, h), "Plot SciPP");

	sf::Event event;
	while (window.isOpen())
	{
		window.display();
		window.clear(sf::Color(255, 255, 255));

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		for (int i(0); i < timelineList.size(); i++)
		{
			Timeline& timeline(*timelineList[i]);

			if (timeline.m_matrices.size() != 0)
			{
				sf::Texture texture;
				texture.loadFromImage(timeline.m_matrices[affichees[i]]);
				window.draw(sf::Sprite(texture));

				if (clocks[i].getElapsedTime().asSeconds() > timeline.m_delay)
				{
					affichees[i] = (affichees[i] + 1) % timeline.m_matrices.size();
					clocks[i].restart();
				}
			}
			else
			{
				sf::VertexArray& courbe(timeline.m_courbes[affichees[i]]);
				if (courbe.getVertexCount() == 1)
				{
					sf::CircleShape cercle;
					cercle.setRadius(3);
					cercle.setFillColor(sf::Color(0, 0, 0));
					cercle.setPosition(courbe[0].position.x, courbe[0].position.y);
					window.draw(cercle);
				}
				else
				{
					window.draw(courbe);
				}
				
				if (clocks[i].getElapsedTime().asSeconds() > timeline.m_delay)
				{
					affichees[i] = (affichees[i] + 1) % timeline.m_courbes.size();
					clocks[i].restart();
				}
			}
		}
	}
}

Timeline::~Timeline()
{
	for (int i(0); i < timelineList.size(); i++)
	{
		if (timelineList[i] == this)
		{
			timelineList.erase(timelineList.begin() + i);
			i--;
		}
	}
}


void plotChampVect2D(Vecteur<double>(*f)(Vecteur<double>), Vecteur<double> coord)
{
	int nbCases(40);

	double pasX((coord[1] - coord[0]) / (nbCases - 1)), pasY((coord[3] - coord[2]) / (nbCases - 1));
	Matrice<Vecteur<double>> M(nbCases, nbCases);

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vecteur<double> v(2);
			v[0] = coord[0] + i * pasX;
			v[1] = coord[3] - j * pasY;

			M[i][j] = f(v);
		}
	}

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vecteur<double> v(4);
			v[0] = i * 15 + 8;
			v[1] = j * 15 + 8;

			M[i][j] /= sqrt(M[i][j] * M[i][j]);
			v[2] = v[0] + M[i][j][0]*7;
			v[3] = v[1] - M[i][j][1]*7;

			M[i][j] = v;
		}
	}

	// Ouverture de la fenêtre

	sf::RenderWindow window(sf::VideoMode(600, 600), "Plot SciPP");

	sf::Event event;
	while (window.isOpen())
	{
		window.display();
		window.clear(sf::Color(255, 255, 255));

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		for (int i(0); i < nbCases; i++)
		{
			for (int j(0); j < nbCases; j++)
			{
				sf::VertexArray ligne(sf::LineStrip, 2);

				ligne[0].position.x = M[i][j][0];
				ligne[0].position.y = M[i][j][1];
				ligne[0].color = sf::Color(0, 0, 0);
				ligne[1].position.x = M[i][j][2];
				ligne[1].position.y = M[i][j][3];
				ligne[1].color = sf::Color(255, 0, 0);

				window.draw(ligne);
			}
		}
	}
}

void plotFlot2D(Vecteur<double>(*f)(Vecteur<double>), Vecteur<double> coord, int precision, double distCourbe)
{
	// Calculer le champ vectoriel a afficher

	int nbCases(40);

	double pasX((coord[1] - coord[0]) / (nbCases - 1)), pasY((coord[3] - coord[2]) / (nbCases - 1));
	Matrice<Vecteur<double>> M(nbCases, nbCases);

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vecteur<double> v(2);
			v[0] = coord[0] + i * pasX;
			v[1] = coord[3] - j * pasY;

			M[i][j] = f(v);
		}
	}

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vecteur<double> v(4);
			v[0] = i * 15 + 8;
			v[1] = j * 15 + 8;

			M[i][j] /= sqrt(M[i][j] * M[i][j]);
			v[2] = v[0] + M[i][j][0] * 7;
			v[3] = v[1] - M[i][j][1] * 7;

			M[i][j] = v;
		}
	}

	// Ouverture de la fenêtre

	sf::RenderWindow window(sf::VideoMode(600, 600), "Plot SciPP");
	std::vector<sf::VertexArray> orbites;
	sf::Event event;
	while (window.isOpen())
	{
		window.display();
		window.clear(sf::Color(255, 255, 255));

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				Vecteur<double> pos(2);
				pos[0] = coord[0] + (coord[1] - coord[0])*(double(event.mouseButton.x)/window.getSize().x);
				pos[1] = coord[2] + (coord[3] - coord[2])*(1 - double(event.mouseButton.y)/window.getSize().y);

				std::cout << pos << std::endl;

				std::vector<Vecteur<double>> courbe;
				courbe.push_back(pos);
				double h((coord[1] - coord[0]) / precision), k((coord[3] - coord[2]) / precision), d(0);
				while (d < distCourbe)
				{
					int n(courbe.size());
					Vecteur<double> xp(f(courbe[n - 1])), x(2);
					x[0] = courbe[n - 1][0] + h * xp[0];
					x[1] = courbe[n - 1][1] + k * xp[1];
					courbe.push_back(x);

					double dD(sqrt((courbe[n - 1] - x) * (courbe[n - 1] - x)));
					d += dD;

					if (dD == 0)
						break;
				}

				orbites.push_back(sf::VertexArray(sf::LineStrip, courbe.size()));
				for (int i(0); i < courbe.size(); i++)
				{
					orbites[orbites.size() - 1][i].position.x = 600*(courbe[i][0] - coord[0])/(coord[1] - coord[0]);
					orbites[orbites.size() - 1][i].position.y = 600*(1 - (courbe[i][1] - coord[2])/(coord[3] - coord[2]));
					orbites[orbites.size() - 1][i].color = sf::Color(0, 0, 255);
				}
			}
		}

		for (int i(0); i < nbCases; i++)
		{
			for (int j(0); j < nbCases; j++)
			{
				sf::VertexArray ligne(sf::LineStrip, 2);

				ligne[0].position.x = M[i][j][0];
				ligne[0].position.y = M[i][j][1];
				ligne[0].color = sf::Color(0, 0, 0);
				ligne[1].position.x = M[i][j][2];
				ligne[1].position.y = M[i][j][3];
				ligne[1].color = sf::Color(255, 0, 0);

				window.draw(ligne);
			}
		}

		for (int i(0); i < orbites.size(); i++)
		{
			window.draw(orbites[i]);
		}
	}
}