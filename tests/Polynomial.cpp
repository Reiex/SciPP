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

TEST(ClassPolynomial, ModuloOperators)
{
    std::string testName("ClassPolynomial.ModuloOperators");

    {
        printSection(testName, "Polynomial<T>::operator%=(const Polynomial<T>& x)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f });
        x %= y;
        EXPECT_EQ(x.degree(), 0);
        EXPECT_NEAR(x[0], 1.3582, 1e-4);
    }

    {
        printSection(testName, "operator%(const Polynomial<T>& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = x % y;
        EXPECT_EQ(z.degree(), 0);
        EXPECT_NEAR(z[0], 1.3582, 1e-4);
    }

    {
        printSection(testName, "operator%(Polynomial<T>&& x, const Polynomial<T>& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) % y;
        EXPECT_EQ(z.degree(), 0);
        EXPECT_NEAR(z[0], 1.3582, 1e-4);
    }

    {
        printSection(testName, "operator%(Polynomial<T>&& x, Polynomial<T>&& y)");

        Polynomial<float> x({ 1.618f, -0.577f }), y({ 1.414f, -3.14f }), z;
        z = std::move(x) % std::move(y);
        EXPECT_EQ(z.degree(), 0);
        EXPECT_NEAR(z[0], 1.3582, 1e-4);
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
    std::string testName("ClassPolynomial.Comparators");

    {
        printSection(testName, "operator==(const Polynomial<T>& x, const Polynomial<T>& y)");

        {
            Polynomial<float> x({ 1.f, 2.f, 3.f }), y({ 1.f, 2.f, 3.f });
            EXPECT_EQ(x == y, true);
            EXPECT_EQ(y == x, true);
        }

        {
            Polynomial<float> x, y;
            EXPECT_EQ(x == y, true);
            EXPECT_EQ(y == x, true);
        }

        {
            Polynomial<float> x({ 1.f, 2.f, 3.f }), y({ 1.f, 2.f, 3.f, 4.f });
            EXPECT_EQ(y == x, false);
            EXPECT_EQ(y == x, false);
        }

        {
            Polynomial<float> x({ 1.f, 2.f, 3.f }), y({ 1.f, 2.f, 4.f });
            EXPECT_EQ(y == x, false);
            EXPECT_EQ(y == x, false);
        }
    }

    {
        printSection(testName, "operator!=(const Polynomial<T>& x, const Polynomial<T>& y)");

        {
            Polynomial<float> x({ 1.f, 2.f, 3.f }), y({ 1.f, 2.f, 3.f });
            EXPECT_EQ(x != y, false);
            EXPECT_EQ(y != x, false);
        }

        {
            Polynomial<float> x, y;
            EXPECT_EQ(x != y, false);
            EXPECT_EQ(y != x, false);
        }

        {
            Polynomial<float> x({ 1.f, 2.f, 3.f }), y({ 1.f, 2.f, 3.f, 4.f });
            EXPECT_EQ(y != x, true);
            EXPECT_EQ(y != x, true);
        }

        {
            Polynomial<float> x({ 1.f, 2.f, 3.f }), y({ 1.f, 2.f, 4.f });
            EXPECT_EQ(y != x, true);
            EXPECT_EQ(y != x, true);
        }
    }
}

TEST(ClassPolynomial, StreamOperators)
{
    std::string testName("ClassPolynomial.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Polynomial<T>& x)");

        {
            Polynomial<float> x;
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "0");
        }

        {
            Polynomial<float> x({ 1.618f, 1.414f, -3.14f});
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "1.618 1.414 -3.14");
        }

        {
            Polynomial<float> x({ 1.618f, 0.f, -3.14f });
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "1.618 0 -3.14");
        }
    }
}

TEST(ClassPolynomial, SpecificMethods)
{
    std::string testName("ClassPolynomial.SpecificMethods");

    {
        printSection(testName, "Polynomial<T>::operator[](uint64_t i)");

        Polynomial<float> x({ 1.618f, 1.414f, -3.14f });
        EXPECT_FLOAT_EQ(x[0], 1.618f);
        EXPECT_FLOAT_EQ(x[3], 0.f);

        x[10] = 2.718f;
        EXPECT_FLOAT_EQ(x[10], 2.718f);

    }

    {
        printSection(testName, "Polynomial<T>::operator()(const T& x)");

        {
            Polynomial<float> x({ 1.618f, 1.414f, -3.14f });
            EXPECT_FLOAT_EQ(x(0), 1.618f);
            EXPECT_FLOAT_EQ(x(2), -8.114f);
        }

        {
            Polynomial<float> x;
            EXPECT_FLOAT_EQ(x(0), 0.f);
            EXPECT_FLOAT_EQ(x(2), 0.f);
        }
    }

    {
        printSection(testName, "Polynomial<T>::derivative()");

        {
            Polynomial<float> x({ 1.618f, 1.414f, -3.14f }), y;
            y = x.derivative();
            EXPECT_EQ(y.degree(), 1);
            EXPECT_FLOAT_EQ(y[0], 1.414f);
            EXPECT_FLOAT_EQ(y[1], -6.28f);
        }

        {
            Polynomial<float> x, y;
            y = x.derivative();
            EXPECT_EQ(y.degree(), 0);
            EXPECT_FLOAT_EQ(y[0], 0.f);
        }
    }

    {
        printSection(testName, "Polynomial<T>::primitive()");

        {
            Polynomial<float> x({ 1.618f, 1.414f, -3.14f }), y;
            y = x.primitive();
            EXPECT_EQ(y.degree(), 3);
            EXPECT_FLOAT_EQ(y[0], 0.f);
            EXPECT_FLOAT_EQ(y[3], -3.14/3);

            y = x.primitive(2.718f);
            EXPECT_EQ(y.degree(), 3);
            EXPECT_FLOAT_EQ(y[0], 2.718f);
        }

        {
            Polynomial<float> x, y;
            y = x.primitive();
            EXPECT_EQ(y.degree(), 0);
            EXPECT_FLOAT_EQ(y[0], 0.f);
        }
    }
}

TEST(ClassPolynomial, BonusTests)
{
    std::string testName("ClassPolynomial.BonusTests");

    {
        printSection(testName, "Binomial from polynomial");

        Polynomial<Int> x({ 1, 1 }), y;
        y = expoSq(x, 10);
        EXPECT_EQ(y[5], binom(10, 5));
    }
}
