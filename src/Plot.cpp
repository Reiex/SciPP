#include "Plot.h"

int Timeline::TAILLE_PLOT[] = { 600, 600 };
std::vector<Timeline*> Timeline::timelineList;

Timeline::Timeline()
{
	timelineList.push_back(this);
	m_delay = 1.0/24.0;
	m_border = Vect<long double>(4);
	m_borderSet = false;
	m_color = Vect<int>(3);
}

void Timeline::setFramerate(int framerate)
{
	m_delay = 1.0/framerate;
}

void Timeline::setColor(int r, int g, int b)
{
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
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

void Timeline::plot(Vect<long double> x, Vect<long double> y)
{
	if (x.taille() != y.taille() || x.taille() < 1)
		throw "La taille des Vects est invalide.";

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

	Vect<long double> border(timelineList[0]->m_border);
	for (int i(1); i < timelineList.size(); i++)
	{
		if (timelineList[i]->m_courbes.size() != 0)
		{
			Vect<long double>& other(timelineList[i]->m_border);
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
			Vect<int>& color(timelineList[i]->m_color);
			
			for (int k(0); k < courbe.getVertexCount(); k++)
			{
				courbe[k].position.x = w*(courbe[k].position.x - border[0]) / (border[1] - border[0]);
				courbe[k].position.y = h*(1 - (courbe[k].position.y - border[2]) / (border[3] - border[2]));
				courbe[k].color = sf::Color(color[0], color[1], color[2]);
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

// Graphes 2D

void plotChampVect2D(Vect<double>(*f)(Vect<double>), Vect<double> coord)
{
	int nbCases(40);

	double pasX((coord[1] - coord[0]) / (nbCases - 1)), pasY((coord[3] - coord[2]) / (nbCases - 1));
	Matrice<Vect<double>> M(nbCases, nbCases);

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vect<double> v(2);
			v[0] = coord[0] + i * pasX;
			v[1] = coord[3] - j * pasY;

			M[i][j] = f(v);
		}
	}

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vect<double> v(4);
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

void plotFlot2D(Vect<double>(*f)(Vect<double>), Vect<double> coord, int precision, double distCourbe)
{
	// Calculer le champ vectoriel a afficher

	int nbCases(40);

	double pasX((coord[1] - coord[0]) / (nbCases - 1)), pasY((coord[3] - coord[2]) / (nbCases - 1));
	Matrice<Vect<double>> M(nbCases, nbCases);

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vect<double> v(2);
			v[0] = coord[0] + i * pasX;
			v[1] = coord[3] - j * pasY;

			M[i][j] = f(v);
		}
	}

	for (int i(0); i < nbCases; i++)
	{
		for (int j(0); j < nbCases; j++)
		{
			Vect<double> v(4);
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
				Vect<double> pos(2);
				pos[0] = coord[0] + (coord[1] - coord[0])*(double(event.mouseButton.x)/window.getSize().x);
				pos[1] = coord[2] + (coord[3] - coord[2])*(1 - double(event.mouseButton.y)/window.getSize().y);

				std::cout << pos << std::endl;

				std::vector<Vect<double>> courbe;
				courbe.push_back(pos);
				double h((coord[1] - coord[0]) / precision), k((coord[3] - coord[2]) / precision), d(0);
				while (d < distCourbe)
				{
					int n(courbe.size());
					Vect<double> xp(f(courbe[n - 1])), x(2);
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

// Bezier & Hermite

Polynome<long double> bernstein(int n, int i)
{
    long double tab[2] = {0, 1};
    long double coeff(binom(n, i).toInt());

	if (n == 0)
		return coeff;
	if (i == 0)
		return coeff * expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
	if (i == n)
		return coeff * expoRapide(Polynome<long double>(tab, 2), i);

    return coeff * expoRapide(Polynome<long double>(tab, 2), i) * expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
}

Vect<long double> getBorder(Vect<long double> x, Vect<long double> y)
{
	int nbPoints(x.taille());
	Vect<long double> border(4);

	if (nbPoints != 0)
	{
		border[0] = x[0];
		border[1] = x[0];
		border[2] = y[0];
		border[3] = y[0];

		for (int i(0); i < nbPoints; i++)
		{
			border[0] = x[i] < border[0] ? x[i] : border[0];
			border[1] = x[i] > border[1] ? x[i] : border[1];
			border[2] = y[i] < border[2] ? y[i] : border[2];
			border[3] = y[i] > border[3] ? y[i] : border[3];
		}
		
		border[0] -= 0.05*(border[1] - border[0]);
		border[1] += 0.05*(border[1] - border[0]);
		border[2] -= 0.05*(border[3] - border[2]);
		border[3] += 0.05*(border[3] - border[2]);
	}

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

	return border;
}

Vect<Vect<long double>> getBezier(Vect<long double> const& x, Vect<long double> const& y, int nbPoints)
{
    if (x.taille() != y.taille())
        throw "Les Vects x et y doivent être de même taille !";
	
	int n(x.taille());
    Polynome<long double> Bx, By;

    for (int i(0); i < n; i++)
    {
		Bx += Polynome<long double>(x[i]) * bernstein(n-1, i);
		By += Polynome<long double>(y[i]) * bernstein(n-1, i);
    }

	Vect<long double> xCourbe(nbPoints), yCourbe(nbPoints);
	for (int i(0); i < nbPoints; i++)
	{
		xCourbe[i] = Bx(double(i) / nbPoints);
		yCourbe[i] = By(double(i) / nbPoints);
	}

	Vect<Vect<long double>> courbeBezier(2);
	courbeBezier[0] = xCourbe;
	courbeBezier[1] = yCourbe;

	return courbeBezier;
}

void plotBezier(Vect<long double> const& x, Vect<long double> const& y)
{
	int n(x.taille()), nbPoints(1000);
	Vect<long double> xPolygone(x), yPolygone(y);
	Vect<Vect<long double>> courbeBezier(getBezier(xPolygone, yPolygone, nbPoints));
	
	int w(Timeline::TAILLE_PLOT[0]), h(Timeline::TAILLE_PLOT[1]);

	// Calcule des coordonnées des points des courbes

	Vect<long double> border(getBorder(xPolygone, yPolygone));
	sf::VertexArray polygoneVertex(sf::LineStrip, n), courbeVertex(sf::LineStrip, nbPoints);

	for (int i(0); i < n; i++)
	{
		polygoneVertex[i].position.x = w*(xPolygone[i] - border[0]) / (border[1] - border[0]);
		polygoneVertex[i].position.y = h*(1 - (yPolygone[i] - border[2]) / (border[3] - border[2]));
		polygoneVertex[i].color = sf::Color(255, 0, 0);
	}
	for (int i(0); i < nbPoints; i++)
	{
		courbeVertex[i].position.x = w*(courbeBezier[0][i] - border[0]) / (border[1] - border[0]);
		courbeVertex[i].position.y = h*(1 - (courbeBezier[1][i] - border[2]) / (border[3] - border[2]));
		courbeVertex[i].color = sf::Color(0, 0, 0);
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
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				Vect<double> pos(2);
				pos[0] = border[0] + (border[1] - border[0])*(double(event.mouseButton.x)/window.getSize().x);
				pos[1] = border[2] + (border[3] - border[2])*(1 - double(event.mouseButton.y)/window.getSize().y);

				std::cout << pos << std::endl;

				n++;

				xPolygone.changerTaille(xPolygone.taille() + 1);
				xPolygone[xPolygone.taille() - 1] = pos[0];
				yPolygone.changerTaille(yPolygone.taille() + 1);
				yPolygone[yPolygone.taille() - 1] = pos[1];
			
				courbeBezier = getBezier(xPolygone, yPolygone, nbPoints);

				polygoneVertex.resize(n);

				for (int i(0); i < n; i++)
				{
					polygoneVertex[i].position.x = w * (xPolygone[i] - border[0]) / (border[1] - border[0]);
					polygoneVertex[i].position.y = h * (1 - (yPolygone[i] - border[2]) / (border[3] - border[2]));
					polygoneVertex[i].color = sf::Color(255, 0, 0);
				}
				for (int i(0); i < nbPoints; i++)
				{
					courbeVertex[i].position.x = w * (courbeBezier[0][i] - border[0]) / (border[1] - border[0]);
					courbeVertex[i].position.y = h * (1 - (courbeBezier[1][i] - border[2]) / (border[3] - border[2]));
					courbeVertex[i].color = sf::Color(0, 0, 0);
				}
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				float zoom(exp(-0.1*event.mouseWheelScroll.delta));
				double centreX(border[0] + (border[1] - border[0]) / 2), centreY(border[2] + (border[3] - border[2]) / 2);

				border[1] = centreX + (centreX - border[0]) * zoom;
				border[0] = centreX - (centreX - border[0]) * zoom;
				border[3] = centreY + (centreY - border[2]) * zoom;
				border[2] = centreY - (centreY - border[2]) * zoom;

				for (int i(0); i < n; i++)
				{
					polygoneVertex[i].position.x = w * (xPolygone[i] - border[0]) / (border[1] - border[0]);
					polygoneVertex[i].position.y = h * (1 - (yPolygone[i] - border[2]) / (border[3] - border[2]));
					polygoneVertex[i].color = sf::Color(255, 0, 0);
				}
				for (int i(0); i < nbPoints; i++)
				{
					courbeVertex[i].position.x = w * (courbeBezier[0][i] - border[0]) / (border[1] - border[0]);
					courbeVertex[i].position.y = h * (1 - (courbeBezier[1][i] - border[2]) / (border[3] - border[2]));
					courbeVertex[i].color = sf::Color(0, 0, 0);
				}
			}

		window.draw(polygoneVertex);
		window.draw(courbeVertex);
	}
}

Vect<Vect<long double>> getHermite(Vect<long double> const& x, Vect<long double> const& y, Vect<long double> const& mx, Vect<long double> const& my, int nbPoints)
{
    if (x.taille() != y.taille() || mx.taille() != my.taille() || x.taille() != mx.taille())
        throw "Les tailles des Vects ne se correspondent pas !";
	
	int n(x.taille()), j(0);
	Vect<long double> xCourbe(nbPoints), yCourbe(nbPoints);
	for (int k(0); k < n - 1; k++)
	{
		Vect<long double> xBezier(4), yBezier(4);
		xBezier[0] = x[k]; yBezier[0] = y[k];
		xBezier[1] = x[k] + mx[k]/3; yBezier[1] = y[k] + my[k]/3;
		xBezier[2] = x[k+1] - mx[k+1]/3; yBezier[2] = y[k+1] - my[k+1]/3;
		xBezier[3] = x[k+1]; yBezier[3] = y[k+1];
		int l((k+1)*nbPoints/(n-1));
		Vect<Vect<long double>> courbeBezier(getBezier(xBezier, yBezier, l - j));

		for (int i(0); j + i < l; i++)
		{
			xCourbe[j+i] = courbeBezier[0][i];
			yCourbe[j+i] = courbeBezier[1][i];
		}
		j = l;
	}

	Vect<Vect<long double>> courbeHermite(2);
	courbeHermite[0] = xCourbe;
	courbeHermite[1] = yCourbe;

	return courbeHermite;
}

void calculRendu(sf::VertexArray& polygoneVertex, sf::VertexArray& courbeVertex, std::vector<sf::CircleShape>& derivees, Vect<long double> const& xPolygone, Vect<long double> const& yPolygone, Vect<long double> const& mxPolygone, Vect<long double> const& myPolygone, Vect<Vect<long double>> const& courbeHermite, Vect<long double> const& border)
{
	int n(polygoneVertex.getVertexCount());
	int nbPoints(courbeVertex.getVertexCount());
	int w(Timeline::TAILLE_PLOT[0]), h(Timeline::TAILLE_PLOT[1]);

	int x, y;
	for (int i(0); i < n; i++)
	{
		polygoneVertex[i].position.x = w*(xPolygone[i] - border[0]) / (border[1] - border[0]);
		polygoneVertex[i].position.y = h*(1 - (yPolygone[i] - border[2]) / (border[3] - border[2]));
		polygoneVertex[i].color = sf::Color(255, 0, 0);

		sf::CircleShape point(3);
		x = polygoneVertex[i].position.x - 3 + mxPolygone[i]*w/(border[1] - border[0])/3;
		y = polygoneVertex[i].position.y - 3 - myPolygone[i]*h/(border[3] - border[2])/3;
		point.setPosition(x, y);
		point.setFillColor(sf::Color(255, 0, 0));
		derivees[i] = point;
	}
	for (int i(0); i < nbPoints; i++)
	{
		courbeVertex[i].position.x = w*(courbeHermite[0][i] - border[0]) / (border[1] - border[0]);
		courbeVertex[i].position.y = h*(1 - (courbeHermite[1][i] - border[2]) / (border[3] - border[2]));
		courbeVertex[i].color = sf::Color(0, 0, 0);
	}
}

int deriveeSelectionnee(std::vector<sf::CircleShape> const& derivees, int xSouris, int ySouris)
{
	for (int i(0); i < derivees.size(); i++)
		if (expoRapide(derivees[i].getPosition().x - xSouris, 2) + expoRapide(derivees[i].getPosition().y - ySouris, 2) < 100)
			return i;

	return -1;
}

void plotHermite(Vect<long double> const& x, Vect<long double> const& y, Vect<long double> const& mx, Vect<long double> const& my)
{
	
	int n(x.taille()), nbPoints(1000);
	Vect<long double> xPolygone(x), yPolygone(y), mxPolygone(mx), myPolygone(my);
	Vect<Vect<long double>> courbeHermite(getHermite(xPolygone, yPolygone, mxPolygone, myPolygone, nbPoints));
	
	int w(Timeline::TAILLE_PLOT[0]), h(Timeline::TAILLE_PLOT[1]);

	// Calcule des coordonnées des points des courbes

	Vect<long double> border(getBorder(xPolygone, yPolygone));
	sf::VertexArray polygoneVertex(sf::LineStrip, n), courbeVertex(sf::LineStrip, nbPoints);
	std::vector<sf::CircleShape> derivees;
	for (int i(0); i < n; i++)
		derivees.push_back(sf::CircleShape(3));
	calculRendu(polygoneVertex, courbeVertex, derivees, xPolygone, yPolygone, mxPolygone, myPolygone, courbeHermite, border);

	// Ouverture de la fenêtre

	sf::RenderWindow window(sf::VideoMode(w, h), "Plot SciPP");

	int selection(-1);
	sf::Event event;
	while (window.isOpen())
	{
		window.display();
		window.clear(sf::Color(255, 255, 255));

		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				selection = deriveeSelectionnee(derivees, event.mouseButton.x, event.mouseButton.y);

				if (selection != -1)
					continue; 

				Vect<double> pos(2);
				pos[0] = border[0] + (border[1] - border[0])*(double(event.mouseButton.x)/window.getSize().x);
				pos[1] = border[2] + (border[3] - border[2])*(1 - double(event.mouseButton.y)/window.getSize().y);

				std::cout << pos << std::endl;

				n++;
				polygoneVertex.resize(n);
				derivees.push_back(sf::CircleShape(3));

				xPolygone.changerTaille(n);
				yPolygone.changerTaille(n);
				mxPolygone.changerTaille(n);
				myPolygone.changerTaille(n);
				xPolygone[n - 1] = pos[0];
				yPolygone[n - 1] = pos[1];
				if (n > 1)
				{
					mxPolygone[n - 1] = pos[0] - xPolygone[n - 2];
					myPolygone[n - 1] = pos[1] - yPolygone[n - 2];
				}
				else
				{
					mxPolygone[n - 1] = 0;
					myPolygone[n - 1] = 0;
				}
			
				courbeHermite = getHermite(xPolygone, yPolygone, mxPolygone, myPolygone, nbPoints);
				calculRendu(polygoneVertex, courbeVertex, derivees, xPolygone, yPolygone, mxPolygone, myPolygone, courbeHermite, border);
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				float zoom(exp(-0.1*event.mouseWheelScroll.delta));
				double centreX(border[0] + (border[1] - border[0]) / 2), centreY(border[2] + (border[3] - border[2]) / 2);

				border[1] = centreX + (centreX - border[0]) * zoom;
				border[0] = centreX - (centreX - border[0]) * zoom;
				border[3] = centreY + (centreY - border[2]) * zoom;
				border[2] = centreY - (centreY - border[2]) * zoom;

				calculRendu(polygoneVertex, courbeVertex, derivees, xPolygone, yPolygone, mxPolygone, myPolygone, courbeHermite, border);
			}
			else if (event.type == sf::Event::MouseMoved && selection != -1)
			{
				Vect<double> pos(2);
				pos[0] = border[0] + (border[1] - border[0])*(double(event.mouseMove.x)/window.getSize().x);
				pos[1] = border[2] + (border[3] - border[2])*(1 - double(event.mouseMove.y)/window.getSize().y);

				mxPolygone[selection] = (pos[0] - xPolygone[selection])*3;
				myPolygone[selection] = (pos[1] - yPolygone[selection])*3;

				courbeHermite = getHermite(xPolygone, yPolygone, mxPolygone, myPolygone, nbPoints);
				calculRendu(polygoneVertex, courbeVertex, derivees, xPolygone, yPolygone, mxPolygone, myPolygone, courbeHermite, border);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				selection = -1;
			}

		window.draw(polygoneVertex);
		window.draw(courbeVertex);
		for (int i(0); i < n; i++)
			window.draw(derivees[i]);
	}
}
