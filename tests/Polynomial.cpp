#include "main.hpp"


TEST(ClassPolynomial, Constructors)
{
    std::string testName("ClassPolynomial.Constructors");

    {
        printSection(testName, "Polynomial<T>::Polynomial()");

        Polynomial<int> x;
        EXPECT_EQ(x.degree(), 0);
        EXPECT_EQ(x[0], 0);

        Polynomial<float> y;
        EXPECT_EQ(y.degree(), 0);
        EXPECT_FLOAT_EQ(y[0], 0);
    }

    {
        printSection(testName, "Polynomial<T>::Polynomial(int64_t x)");

        Polynomial<float> x((int64_t) 0);
        EXPECT_EQ(x.degree(), 0);
        EXPECT_FLOAT_EQ(x[0], 0);

        Polynomial<float> y((int64_t) 161803398874989);
        EXPECT_EQ(y.degree(), 0);
        EXPECT_FLOAT_EQ(y[0], 161803398874989);

        Polynomial<float> z((int64_t) -161803398874989);
        EXPECT_EQ(z.degree(), 0);
        EXPECT_FLOAT_EQ(z[0], -161803398874989);
    }

    {
        printSection(testName, "Polynomial<T>::Polynomial(const T& x)");

        Polynomial<float> x(0.f);
        EXPECT_EQ(x.degree(), 0);
        EXPECT_FLOAT_EQ(x[0], 0);

        Polynomial<float> y(1.618f);
        EXPECT_EQ(y.degree(), 0);
        EXPECT_FLOAT_EQ(y[0], 1.618f);

        Polynomial<float> z(-1.618f);
        EXPECT_EQ(z.degree(), 0);
        EXPECT_FLOAT_EQ(z[0], -1.618f);
    }

    {
        printSection(testName, "Polynomial<T>::Polynomial(const std::vector<T>& values)");

        Polynomial<float> x({ 1.618f, -0.577f, 1.414f });
        EXPECT_EQ(x.degree(), 2);
        EXPECT_FLOAT_EQ(x[0], 1.618f);
        EXPECT_FLOAT_EQ(x[1], -0.577f);
        EXPECT_FLOAT_EQ(x[2], 1.414f);

        Polynomial<float> y({ 1.618f, 0.f, 1.414f, 0.f, 0.f });
        EXPECT_EQ(y.degree(), 2);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], 0.f);
        EXPECT_FLOAT_EQ(y[2], 1.414f);
    }

    {
        printSection(testName, "Polynomial<T>::Polynomial(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f, 1.414f }), y(x);
        EXPECT_EQ(x.degree(), 2);
        EXPECT_FLOAT_EQ(x[0], 1.618f);
        EXPECT_FLOAT_EQ(x[1], -0.577f);
        EXPECT_FLOAT_EQ(x[2], 1.414f);
        EXPECT_EQ(y.degree(), 2);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], -0.577f);
        EXPECT_FLOAT_EQ(y[2], 1.414f);
    }

    {
        printSection(testName, "Polynomial<T>::Polynomial(Polynomial<T>&& x)");

        Polynomial<float> x({ 1.618f, -0.577f, 1.414f }), y(std::move(x));
        EXPECT_EQ(y.degree(), 2);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], -0.577f);
        EXPECT_FLOAT_EQ(y[2], 1.414f);
    }
}

TEST(ClassPolynomial, AssignmentOperators)
{
    std::string testName("ClassPolynomial.AssignmentOperators");

    {
        printSection(testName, "Polynomial<T>::operator=(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y;
        y = x;
        EXPECT_EQ(x.degree(), 1);
        EXPECT_FLOAT_EQ(x[0], 1.618f);
        EXPECT_FLOAT_EQ(x[1], -0.577f);
        EXPECT_EQ(y.degree(), 1);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], -0.577f);
    }

    {
        printSection(testName, "Frac<T>::operator=(Frac<T>&& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y;
        y = std::move(x);
        EXPECT_EQ(y.degree(), 1);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], -0.577f);
    }
}

TEST(ClassPolynomial, Destructor)
{
    std::string testName("ClassPolynomial.Destructor");

    {
        printSection(testName, "Destructor on a simple polynomial");

        Polynomial<float>* x(new Polynomial<float>({ 1.618f, -0.577f }));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on a polynomial created by copy");

        Polynomial<float>* x(new Polynomial<float>({ 1.618f, -0.577f })), *y(new Polynomial<float>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on a polynomial created by move constructor");

        Polynomial<float>* x(new Polynomial<float>({ 1.618f, -0.577f })), *y(new Polynomial<float>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassPolynomial, AdditionOperators)
{
    std::string testName("ClassPolynomial.AdditionOperators");

    {
        printSection(testName, "Polynomial<T>::operator+=(const Polynomial<T>& x)");

        {
            Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f });
            x += y;
            EXPECT_EQ(x.degree(), 1);
            EXPECT_FLOAT_EQ(x[0], 3.032f);
            EXPECT_FLOAT_EQ(x[1], -3.717f);
        }

        {
            Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, 0.577f });
            x += y;
            EXPECT_EQ(x.degree(), 0);
            EXPECT_FLOAT_EQ(x[0], 3.032f);
        }
    }

    {
        printSection(testName, "operator+(const Polynomial<T>& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x + y;
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 3.032f);
        EXPECT_FLOAT_EQ(z[1], -3.717f);
    }

    {
        printSection(testName, "operator+(Polynomial<T>&& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) + y;
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 3.032f);
        EXPECT_FLOAT_EQ(z[1], -3.717f);
    }

    {
        printSection(testName, "operator+(const Polynomial<T>& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x + std::move(y);
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 3.032f);
        EXPECT_FLOAT_EQ(z[1], -3.717f);
    }

    {
        printSection(testName, "operator+(Polynomial<T>&& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) + std::move(y);
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 3.032f);
        EXPECT_FLOAT_EQ(z[1], -3.717f);
    }
}

TEST(ClassPolynomial, SubstractionOperators)
{
    std::string testName("ClassPolynomial.SubstractionOperators");

    {
        printSection(testName, "Polynomial<T>::operator-=(const Polynomial<T>& x)");

        {
            Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f });
            x -= y;
            EXPECT_EQ(x.degree(), 1);
            EXPECT_FLOAT_EQ(x[0], 0.204f);
            EXPECT_FLOAT_EQ(x[1], 2.563f);
        }

        {
            Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -0.577f });
            x -= y;
            EXPECT_EQ(x.degree(), 0);
            EXPECT_FLOAT_EQ(x[0], 0.204f);
        }
    }

    {
        printSection(testName, "operator-(const Polynomial<T>& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x - y;
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 0.204f);
        EXPECT_FLOAT_EQ(z[1], 2.563f);
    }

    {
        printSection(testName, "operator-(Polynomial<T>&& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) - y;
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 0.204f);
        EXPECT_FLOAT_EQ(z[1], 2.563f);
    }

    {
        printSection(testName, "operator-(const Polynomial<T>& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x - std::move(y);
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 0.204f);
        EXPECT_FLOAT_EQ(z[1], 2.563f);
    }

    {
        printSection(testName, "operator-(Polynomial<T>&& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) - std::move(y);
        EXPECT_EQ(z.degree(), 1);
        EXPECT_FLOAT_EQ(z[0], 0.204f);
        EXPECT_FLOAT_EQ(z[1], 2.563f);
    }
}

TEST(ClassPolynomial, MultiplicationOperators)
{
    std::string testName("ClassPolynomial.MultiplicationOperators");

    {
        printSection(testName, "Polynomial<T>::operator*=(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f });
        x *= y;
        EXPECT_EQ(x.degree(), 2);
        EXPECT_FLOAT_EQ(x[0], 2.287852f);
        EXPECT_FLOAT_EQ(x[1], -5.896398f);
        EXPECT_FLOAT_EQ(x[2], 1.81178f);
    }

    {
        printSection(testName, "operator*(const Polynomial<T>& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x * y;
        EXPECT_EQ(z.degree(), 2);
        EXPECT_FLOAT_EQ(z[0], 2.287852f);
        EXPECT_FLOAT_EQ(z[1], -5.896398f);
        EXPECT_FLOAT_EQ(z[2], 1.81178f);
    }

    {
        printSection(testName, "operator*(Polynomial<T>&& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) * y;
        EXPECT_EQ(z.degree(), 2);
        EXPECT_FLOAT_EQ(z[0], 2.287852f);
        EXPECT_FLOAT_EQ(z[1], -5.896398f);
        EXPECT_FLOAT_EQ(z[2], 1.81178f);
    }

    {
        printSection(testName, "operator*(const Polynomial<T>& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x * std::move(y);
        EXPECT_EQ(z.degree(), 2);
        EXPECT_FLOAT_EQ(z[0], 2.287852f);
        EXPECT_FLOAT_EQ(z[1], -5.896398f);
        EXPECT_FLOAT_EQ(z[2], 1.81178f);
    }

    {
        printSection(testName, "operator*(Polynomial<T>&& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) * std::move(y);
        EXPECT_EQ(z.degree(), 2);
        EXPECT_FLOAT_EQ(z[0], 2.287852f);
        EXPECT_FLOAT_EQ(z[1], -5.896398f);
        EXPECT_FLOAT_EQ(z[2], 1.81178f);
    }
}

TEST(ClassPolynomial, DivisionOperators)
{
    std::string testName("ClassPolynomial.DivisionOperators");

    {
        printSection(testName, "Polynomial<T>::operator/=(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f });
        x /= y;
        EXPECT_EQ(x.degree(), 0);
        EXPECT_NEAR(x[0], 0.183758f, 1e-6);
    }

    {
        printSection(testName, "operator/(const Polynomial<T>& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x / y;
        EXPECT_EQ(z.degree(), 0);
        EXPECT_NEAR(z[0], 0.183758f, 1e-6);
    }

    {
        printSection(testName, "operator/(Polynomial<T>&& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) / y;
        EXPECT_EQ(z.degree(), 0);
        EXPECT_NEAR(z[0], 0.183758f, 1e-6);
    }

    {
        printSection(testName, "operator/(Polynomial<T>&& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) / std::move(y);
        EXPECT_EQ(z.degree(), 0);
        EXPECT_NEAR(z[0], 0.183758f, 1e-6);
    }
}

TEST(ClassPolynomial, UnaryOperators)
{
    std::string testName("ClassPolynomial.UnaryOperators");

    {
        printSection(testName, "operator-(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y;
        y = -x;
        EXPECT_EQ(x.degree(), 1);
        EXPECT_FLOAT_EQ(x[0], 1.618f);
        EXPECT_FLOAT_EQ(x[1], -0.577f);
        EXPECT_EQ(y.degree(), 1);
        EXPECT_FLOAT_EQ(y[0], -1.618f);
        EXPECT_FLOAT_EQ(y[1], 0.577f);
    }

    {
        printSection(testName, "operator+(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y;
        y = +x;
        EXPECT_EQ(x.degree(), 1);
        EXPECT_FLOAT_EQ(x[0], 1.618f);
        EXPECT_FLOAT_EQ(x[1], -0.577f);
        EXPECT_EQ(y.degree(), 1);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], -0.577f);
    }

    {
        printSection(testName, "operator-(Polynomial<T>&& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y;
        y = -std::move(x);
        EXPECT_EQ(y.degree(), 1);
        EXPECT_FLOAT_EQ(y[0], -1.618f);
        EXPECT_FLOAT_EQ(y[1], 0.577f);
    }

    {
        printSection(testName, "operator+(Polynomial<T>&& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y;
        y = +std::move(x);
        EXPECT_EQ(y.degree(), 1);
        EXPECT_FLOAT_EQ(y[0], 1.618f);
        EXPECT_FLOAT_EQ(y[1], -0.577f);
    }
}

TEST(ClassPolynomial, Comparators)
{
    std::string testName("ClassFrac.Comparators");

    {
        printSection(testName, "operator==(const Frac<T>& x, const Frac<T>& y)");

        {
            Frac<Int> x(3, 7), y(3, 7);
            EXPECT_EQ(x == y, true);

            x = Frac<Int>(3, 7);
            y = Frac<Int>(6, 14);
            EXPECT_EQ(x == y, true);

            x = Frac<Int>(-3, 7);
            y = Frac<Int>(6, -14);
            EXPECT_EQ(x == y, true);
        }

        {
            Frac<Int> x(3, 7), y(-4, 9);
            EXPECT_EQ(x == y, false);

            x = Frac<Int>(3, 7);
            y = Frac<Int>(-3, 7);
            EXPECT_EQ(x == y, false);
        }
    }

    {
        printSection(testName, "operator!=(const Frac<T>& x, const Frac<T>& y)");

        {
            Frac<Int> x(3, 7), y(3, 7);
            EXPECT_EQ(x != y, false);

            x = Frac<Int>(-3, 7);
            y = Frac<Int>(6, -14);
            EXPECT_EQ(x != y, false);
        }

        {
            Frac<Int> x(3, 7), y(-4, 9);
            EXPECT_EQ(x != y, true);

            x = Frac<Int>(3, 7);
            y = Frac<Int>(-3, 7);
            EXPECT_EQ(x != y, true);
        }
    }
}

TEST(ClassPolynomial, StreamOperators)
{
    std::string testName("ClassFrac.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Frac<T>& x)");

        {
            Frac<Int> x(1618, 3141);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(1618/3141)");
        }

        {
            Frac<Int> x(-1618);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(-1618/1)");
        }

        {
            Frac<Int> x(0);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(0/1)");
        }
    }

    {
        printSection(testName, "operator>>(std::ostream& stream, const Frac<T>& x)");

        {
            Frac<Int> x;
            std::stringstream stream;
            stream << "(1618/3141)";
            stream >> x;
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 3141);
        }

        {
            Frac<Int> x;
            std::stringstream stream;
            stream << "(-1618/1)";
            stream >> x;
            EXPECT_EQ(x.num(), -1618);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Frac<Int> x;
            std::stringstream stream;
            stream << "(0/1)";
            stream >> x;
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }
    }
}

TEST(ClassPolynomial, BonusTests)
{
    std::string testName("ClassFrac.BonusTests");

    {
        printSection(testName, "Decimals of neper constant");

        Rational p(1, 1), s(1, 1);
        for (int i(1); i < 15; i++)
        {
            p /= i;
            s += p;
        }

        EXPECT_EQ(s.decimals(9), "2.718281828");
    }
}
