#include <SciPP/Plot.hpp>

namespace scp
{
	// Styles

	CurveStyle::CurveStyle() :
		m_color({0, 0, 0}),
		m_linkStyle(LinkStyle::Line),
		m_markerStyle(MarkerStyle::Hidden)
	{

	}

	CurveStyle::CurveStyle(MarkerStyle markerStyle, LinkStyle linkStyle, Vect<int> const& color) :
		m_color(color),
		m_linkStyle(linkStyle),
		m_markerStyle(markerStyle)
	{

	}

	Vect<int> const& CurveStyle::getColor() const
	{
		return m_color;
	}

	CurveStyle::LinkStyle CurveStyle::getLinkStyle() const
	{
		return m_linkStyle;
	}

	CurveStyle::MarkerStyle CurveStyle::getMarkerStyle() const
	{
		return m_markerStyle;
	}


	MatrixStyle::MatrixStyle() :
		m_color({255, 255, 255}),
		m_displayStyle(DisplayStyle::Flat)
	{

	}

	MatrixStyle::MatrixStyle(DisplayStyle displayStyle, Vect<int> const& color) :
		m_color(color),
		m_displayStyle(displayStyle)
	{

	}

	Vect<int> const& MatrixStyle::getColor() const
	{
		return m_color;
	}

	MatrixStyle::DisplayStyle MatrixStyle::getDisplayStyle() const
	{
		return m_displayStyle;
	}

	// Plot

	int Timeline::WINDOW_SIZE[] = { 800, 800 };
	List<Timeline*> Timeline::m_timelineList;
	List<Vect<long double>> Timeline::m_subplotBorders;

	char const* Timeline::IllegalMatrixPlotException::what() const throw()
	{
		return "Tentative de plot d'une matrice alors que des courbes font déjà partie de la timeline.";
	}

	char const* Timeline::IllegalCurvePlotException::what() const throw()
	{
		return "Tentative de plot d'une courbe alors que des matrices font déjà partie de la timeline.";
	}

	char const* Timeline::InvalidCurveException::what() const throw()
	{
		return "Tentative de plot d'une courbe où le nombre de coordonnées selon x et selon y n'est pas le même.";
	}

	char const* Timeline::InvalidSubplotBordersException::what() const throw()
	{
		return "Les frontières des subplots ne sont pas bien définies.";
	}

	Timeline::Timeline() :
		m_framerate(60),
		m_subplot(0)
	{
		m_timelineList.append(this);
	}

	Timeline::Timeline(Timeline const& timeline) :
		m_framerate(timeline.m_framerate),
		m_curves(timeline.m_curves),
		m_matrices(timeline.m_matrices),
		m_curveStyle(timeline.m_curveStyle),
		m_matrixStyle(timeline.m_matrixStyle),
		m_subplot(timeline.m_subplot)
	{
		m_timelineList.append(this);
	}

	void Timeline::setFramerate(int framerate)
	{
		m_framerate = framerate;
	}

	void Timeline::setCurveStyle(CurveStyle style)
	{
		m_curveStyle = style;
	}

	void Timeline::setMatrixStyle(MatrixStyle style)
	{
		m_matrixStyle = style;
	}

	void Timeline::setSubplot(int i)
	{
		m_subplot = i;
	}

	void Timeline::setSubplotBorders(List<Vect<long double>> const& borders)
	{
		m_subplotBorders = borders;
	}

	void Timeline::plot(long double x, long double y)
	{
		if (m_matrices.size() != 0)
			throw IllegalCurvePlotException();

		m_curves.append({ {x}, {y} });

		if (m_curveStyle.getMarkerStyle() == CurveStyle::MarkerStyle::Hidden)
			m_curveStyle = CurveStyle(CurveStyle::MarkerStyle::Circle, CurveStyle::LinkStyle::Hidden, { 0, 0, 0 });
	}

	void Timeline::plot(List<long double> const& x, List<long double> const& y)
	{
		if (m_matrices.size() != 0)
			throw IllegalCurvePlotException();

		m_curves.append({ x, y });
	}

	void Timeline::plot(Matrice<long double> const& M)
	{
		if (m_curves.size() != 0)
			throw IllegalMatrixPlotException();

		m_matrices.append(M);
	}

	void Timeline::show(sf::RenderWindow& window)
	{
		int w(window.getSize().x), h(window.getSize().y);

		if (m_timelineList.size() == 0)
			return;

		if (m_subplotBorders.size() != 0)
			checkSubplotBorders();
		else
			computeSubplotBorders(w, h);

		List<Vect<long double>> mathBorders(Timeline::computeBorders());
		List<Vect<long double>> matrixLimits(Timeline::computeMatrixLimits());

		// Ouverture de la fenêtre

		sf::Clock clock;
		sf::Event event;
		while (window.isOpen())
		{
			window.display();
			window.clear(sf::Color(255, 255, 255));

			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed)
					window.close();

			for (int i(0); i < m_timelineList.size(); i++)
			{
				int s(m_timelineList[i]->m_subplot);
				m_timelineList[i]->display(window, mathBorders[s], m_subplotBorders[m_timelineList[i]->m_subplot], matrixLimits[s], clock.getElapsedTime().asSeconds());
			}
		}
	}

	void Timeline::show(std::string const& title)
	{
		if (m_timelineList.size() == 0)
			return;

		sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE[0], WINDOW_SIZE[1]), title);

		Timeline::show(window);
	}

	void Timeline::resetWindowSize()
	{
		WINDOW_SIZE[0] = 800;
		WINDOW_SIZE[1] = 800;
	}

	Timeline::~Timeline()
	{
		for (int i(0); i < m_timelineList.size(); i++)
		{
			if (m_timelineList[i] == this)
			{
				m_timelineList.remove(i);
				i--;
			}
		}
	}

	List<Vect<long double>> Timeline::computeBorders()
	{
		int n(m_subplotBorders.size());
		List<Vect<long double>> borderList(n);

		for (int s(0); s < n; s++)
		{
			Vect<long double> borders(4);

			for (int i(0); i < m_timelineList.size(); i++)
			{
				if (m_timelineList[i]->m_subplot == s && m_timelineList[i]->m_curves.size() != 0)
				{
					borders = { m_timelineList[i]->m_curves[0][0][0], m_timelineList[i]->m_curves[0][1][0] , m_timelineList[i]->m_curves[0][0][0] , m_timelineList[i]->m_curves[0][1][0] };
					break;
				}
			}

			for (int i(0); i < m_timelineList.size(); i++)
			{
				if (m_timelineList[i]->m_subplot == s)
				{
					for (int j(0); j < m_timelineList[i]->m_curves.size(); j++)
					{
						for (int k(0); k < m_timelineList[i]->m_curves[j][0].size(); k++)
						{
							List<long double>& x(m_timelineList[i]->m_curves[j][0]), y(m_timelineList[i]->m_curves[j][1]);
							if (x[k] < borders[0]) borders[0] = x[k];
							if (x[k] > borders[2]) borders[2] = x[k];
							if (y[k] < borders[1]) borders[1] = y[k];
							if (y[k] > borders[3]) borders[3] = y[k];
						}
					}
				}
			}

			if (borders[0] == borders[2])
			{
				borders[0] -= 1;
				borders[2] += 1;
			}

			if (borders[1] == borders[3])
			{
				borders[1] -= 1;
				borders[3] += 1;
			}

			borderList[s] = borders;
		}

		return borderList;
	}

	List<Vect<long double>> Timeline::computeMatrixLimits()
	{
		int n(m_subplotBorders.size());
		List<Vect<long double>> limitList(n);

		for (int s(0); s < n; s++)
		{
			Vect<long double> limits(2);

			for (int i(0); i < m_timelineList.size(); i++)
			{
				if (m_timelineList[i]->m_subplot == s && m_timelineList[i]->m_matrices.size() != 0)
				{
					limits = { m_timelineList[i]->m_matrices[0][0][0], m_timelineList[i]->m_matrices[0][0][0] };
					break;
				}
			}

			for (int i(0); i < m_timelineList.size(); i++)
			{
				if (m_timelineList[i]->m_subplot == s)
				{
					for (int j(0); j < m_timelineList[i]->m_matrices.size(); j++)
					{
						for (int k(0); k < m_timelineList[i]->m_matrices[j].size()[0]; k++)
						{
							for (int l(0); l < m_timelineList[i]->m_matrices[j].size()[1]; l++)
							{
								if (m_timelineList[i]->m_matrices[j][k][l] < limits[0]) limits[0] = m_timelineList[i]->m_matrices[j][k][l];
								if (m_timelineList[i]->m_matrices[j][k][l] > limits[1]) limits[1] = m_timelineList[i]->m_matrices[j][k][l];
							}
						}
					}
				}
			}

			if (limits[0] == limits[1])
			{
				limits[0] -= 1;
				limits[1] += 1;
			}

			limitList[s] = limits;
		}
	

		return limitList;
	}

	void Timeline::checkSubplotBorders()
	{
		for (int i(0); i < m_timelineList.size(); i++)
			if (m_timelineList[i]->m_subplot >= m_subplotBorders.size())
				throw InvalidSubplotBordersException();

		for (int i(0); i < m_subplotBorders.size(); i++)
			if (m_subplotBorders[i].size() != 4)
				throw InvalidSubplotBordersException();
	}

	void Timeline::computeSubplotBorders(int w, int h)
	{
		int n(0);
		for (int i(0); i < m_timelineList.size(); i++)
			if (m_timelineList[i]->m_subplot > n)
				n = m_timelineList[i]->m_subplot;
		n++;

		if (n == 1)
		{
			m_subplotBorders = { {0, 0, double(w), double(h)} };
		}
		else if (n == 2)
		{
			m_subplotBorders = { {0, 0, double(w), double(h)/2},
								 {0, double(h)/2, double(w), double(h)} };
		}
		else if (n == 3)
		{
			m_subplotBorders = { {0, 0, double(w), double(h)/2},
								 {0, double(h)/2, double(w)/2, double(h)},
								 {double(w)/2, double(h)/2, double(w), double(h)} };
		}
		else if (n == 4)
		{
			m_subplotBorders = { {0, 0, double(w)/2, double(h)/2},
								 {double(w)/2, 0, double(w), double(h)/2},
								 {0, double(h)/2, double(w)/2, double(h)},
								 {double(w)/2, double(h)/2, double(w), double(h)} };
		}
		else
		{
			for (int i(0); i < n; i++)
				m_subplotBorders.append({0, i*double(h)/n, double(w), (i+1)*double(h)/n});
		}
	}

	void Timeline::display(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, Vect<long double> const& matrixLimits, long double time) const
	{	
		long double xMath(mathBorders[0]), yMath(mathBorders[1]), wMath(mathBorders[2] - mathBorders[0]), hMath(mathBorders[3] - mathBorders[1]);
		long double xTarget(targetBorders[0]), yTarget(targetBorders[1]), wTarget(targetBorders[2] - targetBorders[0]), hTarget(targetBorders[3] - targetBorders[1]);

		unsigned int i(time * m_framerate);
		if (m_curves.size() != 0)
		{
			i %= m_curves.size();

			if (m_curveStyle.getLinkStyle() == CurveStyle::LinkStyle::Line)
				drawLineLinkCurve(target, mathBorders, targetBorders, m_curves[i][0], m_curves[i][1]);

			if (m_curveStyle.getMarkerStyle() == CurveStyle::MarkerStyle::Circle)
				drawCircleMarkerCurve(target, mathBorders, targetBorders, m_curves[i][0], m_curves[i][1]);
		}
		else if (m_matrices.size() != 0)
		{
			i %= m_matrices.size();

			if (m_matrixStyle.getDisplayStyle() == MatrixStyle::DisplayStyle::Flat)
				drawFlatMatrix(target, mathBorders, targetBorders, matrixLimits, m_matrices[i]); 
			else if (m_matrixStyle.getDisplayStyle() == MatrixStyle::DisplayStyle::Smooth)
				drawSmoothMatrix(target, mathBorders, targetBorders, matrixLimits, m_matrices[i]);
		}
	}

	void Timeline::drawLineLinkCurve(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, List<long double> const& x, List<long double> const& y) const
	{
		long double xMath(mathBorders[0]), yMath(mathBorders[1]), wMath(mathBorders[2] - mathBorders[0]), hMath(mathBorders[3] - mathBorders[1]);
		long double xTarget(targetBorders[0]), yTarget(targetBorders[1]), wTarget(targetBorders[2] - targetBorders[0]), hTarget(targetBorders[3] - targetBorders[1]);

		int n(x.size());
		sf::VertexArray vertices(sf::PrimitiveType::LineStrip, n);
		sf::Color color = sf::Color(m_curveStyle.getColor()[0], m_curveStyle.getColor()[1], m_curveStyle.getColor()[2]);
		for (int j(0); j < n; j++)
		{
			vertices[j].position.x = xTarget + wTarget * (x[j] - xMath) / wMath;
			vertices[j].position.y = yTarget + hTarget * (1 - (y[j] - yMath) / hMath);
			vertices[j].color = color;
		}

		target.draw(vertices);
	}

	void Timeline::drawCircleMarkerCurve(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, List<long double> const& x, List<long double> const& y) const
	{
		long double xMath(mathBorders[0]), yMath(mathBorders[1]), wMath(mathBorders[2] - mathBorders[0]), hMath(mathBorders[3] - mathBorders[1]);
		long double xTarget(targetBorders[0]), yTarget(targetBorders[1]), wTarget(targetBorders[2] - targetBorders[0]), hTarget(targetBorders[3] - targetBorders[1]);

		int n(x.size());
		sf::Color color = sf::Color(m_curveStyle.getColor()[0], m_curveStyle.getColor()[1], m_curveStyle.getColor()[2]);
		for (int j(0); j < n; j++)
		{
			sf::CircleShape circle;
			circle.setRadius(3);
			circle.setFillColor(color);
			circle.setPosition(xTarget + wTarget * (x[j] - xMath) / wMath - 3, yTarget + hTarget * (1 - (y[j] - yMath) / hMath) - 3);
			target.draw(circle);
		}
	}

	void Timeline::drawFlatMatrix(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, Vect<long double> const& matrixLimits, Matrice<long double> const& M) const
	{
		long double xMath(mathBorders[0]), yMath(mathBorders[1]), wMath(mathBorders[2] - mathBorders[0]), hMath(mathBorders[3] - mathBorders[1]);
		long double xTarget(targetBorders[0]), yTarget(targetBorders[1]), wTarget(targetBorders[2] - targetBorders[0]), hTarget(targetBorders[3] - targetBorders[1]);

		int m(M.size()[0]), n(M.size()[1]);
		sf::VertexArray vertices(sf::PrimitiveType::Triangles, 6*m*n);

		for (int j(0); j < m; j++)
		{
			for (int k(0); k < n; k++)
			{
				Vect<int> const& col(m_matrixStyle.getColor());
				Vect<int> x({k, k+1, k, k+1, k, k+1}), y({j, j, j+1, j, j+1, j+1});
				int i(x.size()*(j*n + k));

				for (int l(0); l < x.size(); l++)
				{
					vertices[i + l].position.x = xTarget + x[l]*wTarget/n;
					vertices[i + l].position.y = yTarget + y[l]*hTarget/m;
					long double c((M[j][k] - matrixLimits[0])/(matrixLimits[1] - matrixLimits[0]));
					vertices[i + l].color = sf::Color(col[0]*c, col[1]*c, col[2]*c);
				}
			}
		}

		target.draw(vertices);
	}

	void Timeline::drawSmoothMatrix(sf::RenderTarget& target, Vect<long double> const& mathBorders, Vect<long double> const& targetBorders, Vect<long double> const& matrixLimits, Matrice<long double> const& M) const
	{
		long double xMath(mathBorders[0]), yMath(mathBorders[1]), wMath(mathBorders[2] - mathBorders[0]), hMath(mathBorders[3] - mathBorders[1]);
		long double xTarget(targetBorders[0]), yTarget(targetBorders[1]), wTarget(targetBorders[2] - targetBorders[0]), hTarget(targetBorders[3] - targetBorders[1]);

		int m(M.size()[0]), n(M.size()[1]);
		sf::VertexArray vertices(sf::PrimitiveType::Triangles, 12*(m-1)*(n-1));

		for (int j(0); j < m-1; j++)
		{
			for (int k(0); k < n-1; k++)
			{
				Vect<int> const& col(m_matrixStyle.getColor());
				Vect<long double> y({double(k), double(k)+1, double(k)+0.5, double(k)+1, double(k)+1, double(k)+0.5, double(k), double(k)+0.5, double(k)+1, double(k), double(k)+0.5, double(k)});
				Vect<long double> x({double(j), double(j), double(j)+0.5, double(j), double(j)+1, double(j)+0.5, double(j)+1, double(j)+0.5, double(j)+1, double(j), double(j)+0.5, double(j)+1});
				long double moyenne((M[k][j] + M[k+1][j] + M[k][j+1] + M[k+1][j+1])/4);
				Vect<long double> Mvalues({ M[k][j], M[k+1][j], moyenne, M[k+1][j], M[k+1][j+1], moyenne, M[k][j+1], moyenne, M[k+1][j+1], M[k][j], moyenne, M[k][j+1] });
				int i(x.size()*(j*(n-1) + k));

				for (int l(0); l < x.size(); l++)
				{
					vertices[i + l].position.x = xTarget + x[l]*wTarget/(n-1);
					vertices[i + l].position.y = yTarget + y[l]*hTarget/(m-1);
					long double c((Mvalues[l] - matrixLimits[0])/(matrixLimits[1] - matrixLimits[0]));
					vertices[i + l].color = sf::Color(col[0]*c, col[1]*c, col[2]*c);
				}
			}
		}

		target.draw(vertices);
	}

	// Graphes 2D

	void plotChampVect2D(Vect<double>(*f)(Vect<double>), Vect<double> coord)
	{
		int nbCases(40);
		int w(Timeline::WINDOW_SIZE[0]), h(Timeline::WINDOW_SIZE[1]);

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
				v[0] = (i + 0.5) * (w / nbCases);
				v[1] = (j + 0.5) * (h / nbCases);

				M[i][j] /= sqrt(M[i][j] * M[i][j]);
				v[2] = v[0] + M[i][j][0] * w / (2 * nbCases);
				v[3] = v[1] - M[i][j][1] * h / (2 * nbCases);

				M[i][j] = v;
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
		int w(Timeline::WINDOW_SIZE[0]), h(Timeline::WINDOW_SIZE[1]);

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
				v[0] = (i + 0.5) * (w/nbCases);
				v[1] = (j + 0.5) * (h/nbCases);

				M[i][j] /= sqrt(M[i][j] * M[i][j]);
				v[2] = v[0] + M[i][j][0] * w / (2*nbCases);
				v[3] = v[1] - M[i][j][1] * h / (2*nbCases);

				M[i][j] = v;
			}
		}

		// Ouverture de la fenêtre

		sf::RenderWindow window(sf::VideoMode(w, h), "Plot SciPP");
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
						orbites[orbites.size() - 1][i].position.x = Timeline::WINDOW_SIZE[0]*(courbe[i][0] - coord[0])/(coord[1] - coord[0]);
						orbites[orbites.size() - 1][i].position.y = Timeline::WINDOW_SIZE[1]*(1 - (courbe[i][1] - coord[2])/(coord[3] - coord[2]));
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

	// Bezier, Hermite & Lagrange

	Polynome<long double> bernstein(int n, int i)
	{
		long double tab[2] = {0, 1};
		long double coeff(binom(n, i).toInt());

		if (n == 0)
			return coeff;
		if (i == 0)
			return Polynome<long double>(coeff) * expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
		if (i == n)
			return Polynome<long double>(coeff) * expoRapide(Polynome<long double>(tab, 2), i);

		return Polynome<long double>(coeff) * expoRapide(Polynome<long double>(tab, 2), i) * expoRapide(Polynome<long double>(1) - Polynome<long double>(tab, 2), n - i);
	}

	Vect<long double> getBorder(Vect<long double> x, Vect<long double> y)
	{
		int nbPoints(x.size());
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
		if (x.size() != y.size())
			throw "Les Vects x et y doivent être de même taille !";
	
		int n(x.size());
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

	Vect<Vect<long double>> plotBezier(Vect<long double> const& x, Vect<long double> const& y)
	{
		int n(x.size()), nbPoints(1000);
		Vect<long double> xPolygone(x), yPolygone(y);
		Vect<Vect<long double>> courbeBezier(getBezier(xPolygone, yPolygone, nbPoints));
	
		int w(Timeline::WINDOW_SIZE[0]), h(Timeline::WINDOW_SIZE[1]);

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

					xPolygone.changerTaille(xPolygone.size() + 1);
					xPolygone[xPolygone.size() - 1] = pos[0];
					yPolygone.changerTaille(yPolygone.size() + 1);
					yPolygone[yPolygone.size() - 1] = pos[1];
			
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

		Vect<Vect<long double>> r(4);
		r[0] = courbeBezier[0];
		r[1] = courbeBezier[1];
		r[2] = xPolygone;
		r[3] = yPolygone;

		return r;
	}

	Vect<Vect<long double>> getHermite(Vect<long double> const& x, Vect<long double> const& y, Vect<long double> const& mx, Vect<long double> const& my, int nbPoints)
	{
		if (x.size() != y.size() || mx.size() != my.size() || x.size() != mx.size())
			throw "Les tailles des Vects ne se correspondent pas !";
	
		int n(x.size()), j(0);
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

		if (n > 1 && nbPoints != 0)
		{
			xCourbe[nbPoints - 1] = x[n - 1];
			yCourbe[nbPoints - 1] = y[n - 1];
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
		int w(Timeline::WINDOW_SIZE[0]), h(Timeline::WINDOW_SIZE[1]);

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

	Vect<Vect<long double>> plotHermite(Vect<long double> const& x, Vect<long double> const& y, Vect<long double> const& mx, Vect<long double> const& my)
	{
	
		int n(x.size()), nbPoints(1000);
		Vect<long double> xPolygone(x), yPolygone(y), mxPolygone(mx), myPolygone(my);
		Vect<Vect<long double>> controle, courbeHermite(getHermite(xPolygone, yPolygone, mxPolygone, myPolygone, nbPoints));
	
		int w(Timeline::WINDOW_SIZE[0]), h(Timeline::WINDOW_SIZE[1]);

		// Calcule des coordonnées des points des courbes

		Vect<long double> border(getBorder(xPolygone, yPolygone));
		sf::VertexArray polygoneVertex(sf::LineStrip, n), courbeVertex(sf::LineStrip, nbPoints);
		std::vector<sf::CircleShape> derivees;
		for (int i(0); i < n; i++)
			derivees.push_back(sf::CircleShape(3));
		calculRendu(polygoneVertex, courbeVertex, derivees, xPolygone, yPolygone, mxPolygone, myPolygone, courbeHermite, border);

		// Ouverture de la fenêtre

		sf::RenderWindow window(sf::VideoMode(w, h), "Plot SciPP");
		window.setKeyRepeatEnabled(true);

		int selection(-1);
		long double c(0);
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
				else if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Up)
						c -= 0.1;
					else if (event.key.code == sf::Keyboard::Down)
						c += 0.1;
					else if (event.key.code == sf::Keyboard::Space)
						c = 0;

					switch (event.key.code)
					{
						case sf::Keyboard::Up:
						case sf::Keyboard::Down:
						case sf::Keyboard::Space:
							controle = getSmoothDerivatives(xPolygone, yPolygone, c);
							mxPolygone = controle[0];
							myPolygone = controle[1];
							courbeHermite = getHermite(xPolygone, yPolygone, mxPolygone, myPolygone, nbPoints);
							calculRendu(polygoneVertex, courbeVertex, derivees, xPolygone, yPolygone, mxPolygone, myPolygone, courbeHermite, border);
							break;
						default:
							break;
					}
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

		Vect<Vect<long double>> r(6);
		r[0] = courbeHermite[0];
		r[1] = courbeHermite[1];
		r[2] = xPolygone;
		r[3] = yPolygone;
		r[4] = mxPolygone;
		r[5] = myPolygone;

		return r;
	}

	Vect<Vect<long double>> getSmoothDerivatives(Vect<long double> const& x, Vect<long double> const& y, long double c)
	{
		if (x.size() != y.size())
			throw "Les tailles ne se correspondent pas !";

		int n(x.size());
		Vect<Vect<long double>> m(2);
		m[0] = Vect<long double>(n);
		m[1] = Vect<long double>(n);

		if (n < 2)
			return m;

		// Calcul des dérivées au milieu de la courbe

		for (int i(1); i < n-1; i++)
		{
			m[0][i] = (1-c)*(x[i+1] - x[i-1])/2;
			m[1][i] = (1-c)*(y[i+1] - y[i-1])/2;
		}

		// Courbe tangeante aux bords du polygone de contrôle

		m[0][0] = 0;
		m[1][0] = 0;

		m[0][n-1] = 0;
		m[1][n-1] = 0;

		return m;
	}

	Polynome<long double> lagrangePolynome(int i, int n)
	{
		long double tab[2] = {0, 1};
		Polynome<long double> L(1), X(tab, 2);
		for (int j(0); j < n; j++)
			if (i != j)
				L *= (X - Polynome<long double>(j))/Polynome<long double>(i - j);
	
		return L;
	}

	Vect<Vect<long double>> getLagrange(Vect<long double> const& x, Vect<long double> const& y, int nbPoints)
	{
		if (x.size() != y.size())
			throw "Les Vects x et y doivent être de même taille !";
	
		int n(x.size());
		Polynome<long double> Bx, By;

		for (int i(0); i < n; i++)
		{
			Polynome<long double> L(lagrangePolynome(i, n));
			Bx += Polynome<long double>(x[i]) * L;
			By += Polynome<long double>(y[i]) * L;
		}

		Vect<long double> xCourbe(nbPoints), yCourbe(nbPoints);
		for (int i(0); i < nbPoints; i++)
		{
			xCourbe[i] = Bx((n-1) * double(i) / (nbPoints-1));
			yCourbe[i] = By((n-1) * double(i) / (nbPoints-1));
		}

		Vect<Vect<long double>> courbeLagrange(2);
		courbeLagrange[0] = xCourbe;
		courbeLagrange[1] = yCourbe;

		return courbeLagrange;
	}

	Vect<Vect<long double>> plotLagrange(Vect<long double> const& x, Vect<long double> const& y)
	{
		int n(x.size()), nbPoints(1000);
		Vect<long double> xPolygone(x), yPolygone(y);
		Vect<Vect<long double>> courbeLagrange(getLagrange(xPolygone, yPolygone, nbPoints));
	
		int w(Timeline::WINDOW_SIZE[0]), h(Timeline::WINDOW_SIZE[1]);

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
			courbeVertex[i].position.x = w*(courbeLagrange[0][i] - border[0]) / (border[1] - border[0]);
			courbeVertex[i].position.y = h*(1 - (courbeLagrange[1][i] - border[2]) / (border[3] - border[2]));
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

					xPolygone.changerTaille(xPolygone.size() + 1);
					xPolygone[xPolygone.size() - 1] = pos[0];
					yPolygone.changerTaille(yPolygone.size() + 1);
					yPolygone[yPolygone.size() - 1] = pos[1];
			
					courbeLagrange = getLagrange(xPolygone, yPolygone, nbPoints);

					polygoneVertex.resize(n);

					for (int i(0); i < n; i++)
					{
						polygoneVertex[i].position.x = w * (xPolygone[i] - border[0]) / (border[1] - border[0]);
						polygoneVertex[i].position.y = h * (1 - (yPolygone[i] - border[2]) / (border[3] - border[2]));
						polygoneVertex[i].color = sf::Color(255, 0, 0);
					}
					for (int i(0); i < nbPoints; i++)
					{
						courbeVertex[i].position.x = w * (courbeLagrange[0][i] - border[0]) / (border[1] - border[0]);
						courbeVertex[i].position.y = h * (1 - (courbeLagrange[1][i] - border[2]) / (border[3] - border[2]));
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
						courbeVertex[i].position.x = w * (courbeLagrange[0][i] - border[0]) / (border[1] - border[0]);
						courbeVertex[i].position.y = h * (1 - (courbeLagrange[1][i] - border[2]) / (border[3] - border[2]));
						courbeVertex[i].color = sf::Color(0, 0, 0);
					}
				}

			window.draw(polygoneVertex);
			window.draw(courbeVertex);
		}

		Vect<Vect<long double>> r(4);
		r[0] = courbeLagrange[0];
		r[1] = courbeLagrange[1];
		r[2] = xPolygone;
		r[3] = yPolygone;

		return r;
	}

	Vect<long double> getCourbure(Vect<long double> const& x, Vect<long double> const& y)
	{
		if (x.size() != y.size())
			throw "Les Vects x et y doivent être de même taille !";

		int n(x.size());
		Vect<long double> c(n-2);

		for (int i(1); i < n-1; i++)
		{
			long double dx, ddx, dy, ddy, a, b;

			ddx = x[i-1] - 2*x[i] + x[i+1];
			ddy = y[i-1] - 2*y[i] + y[i+1];

			dx = x[i-1] - x[i];
			dy = y[i-1] - y[i];

			a = dx*ddy  - dy*ddx;
			b = dx*dx + dy*dy;
			b = b*sqrt(b);
			c[i-1] = a/b;
		}

		return c;
	}
}
