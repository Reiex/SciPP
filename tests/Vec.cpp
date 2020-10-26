#include "main.hpp"


TEST(ClassVec, Constructors)
{
    std::string testName("ClassVec.Constructors");

    {
        printSection(testName, "Vec<T, n>::Vec()");

        {
            Vec<float, 0> x;
        }

        {
            Vec<float, 3> x;
            EXPECT_EQ(x[0], 0);
            EXPECT_EQ(x[1], 0);
            EXPECT_EQ(x[2], 0);
        }

        {
            Vec<Rational, 3> x;
            EXPECT_EQ(x[0], Rational(0, 1));
            EXPECT_EQ(x[1], Rational(0, 1));
            EXPECT_EQ(x[2], Rational(0, 1));
        }
    }

    {
        printSection(testName, "Vec<T, n>::Vec(int64_t x)");

        {
            Vec<float, 3> x(int64_t(1618));
            EXPECT_EQ(x[0], 1618);
            EXPECT_EQ(x[1], 1618);
            EXPECT_EQ(x[2], 1618);
        }

        {
            Vec<Rational, 3> x(int64_t(1618));
            EXPECT_EQ(x[0], Rational(1618, 1));
            EXPECT_EQ(x[1], Rational(1618, 1));
            EXPECT_EQ(x[2], Rational(1618, 1));
        }
    }

    {
        printSection(testName, "Vec<T, n>::Vec(const T& x)");

        {
            Vec<float, 3> x(1.618f);
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 1.618);
            EXPECT_FLOAT_EQ(x[2], 1.618);
        }
    }

    {
        printSection(testName, "Vec<T, n>::Vec(const std::array<T, n>& values)");

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f});
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 3.14);
            EXPECT_FLOAT_EQ(x[2], 1.414);
        }
    }

    {
        printSection(testName, "Vec<T, n>::Vec(const Vec<T, n>& x)");

        {
            Vec<float, 3> x(1.618f), y(x);
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 1.618);
            EXPECT_FLOAT_EQ(x[2], 1.618);
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 1.618);
            EXPECT_FLOAT_EQ(y[2], 1.618);
        }
    }

    {
        printSection(testName, "Vec<T, n>::Vec(Vec<T, n>&& x)");

        {
            Vec<float, 3> x(1.618f), y(std::move(x));
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 1.618);
            EXPECT_FLOAT_EQ(y[2], 1.618);
        }
    }
}

TEST(ClassVec, AssignmentOperators)
{
    std::string testName("ClassVec.AssignmentOperators");

    {
        printSection(testName, "Vec<T, n>::operator=(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y;
        y = x;
        EXPECT_FLOAT_EQ(x[0], 1.618);
        EXPECT_FLOAT_EQ(x[1], 3.14);
        EXPECT_FLOAT_EQ(x[2], 1.414);
        EXPECT_FLOAT_EQ(y[0], 1.618);
        EXPECT_FLOAT_EQ(y[1], 3.14);
        EXPECT_FLOAT_EQ(y[2], 1.414);
    }

    {
        printSection(testName, "Vec<T, n>::operator=(Vec<T, n>&& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y;
        y = std::move(x);
        EXPECT_FLOAT_EQ(y[0], 1.618);
        EXPECT_FLOAT_EQ(y[1], 3.14);
        EXPECT_FLOAT_EQ(y[2], 1.414);
    }

    {
        printSection(testName, "Bonus tests");

        {
            Vec<float, 2> x({1.618f, 3.14f}), y, z, t;
            t = z = y = x;
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 3.14);
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 3.14);
            EXPECT_FLOAT_EQ(z[0], 1.618);
            EXPECT_FLOAT_EQ(z[1], 3.14);
            EXPECT_FLOAT_EQ(t[0], 1.618);
            EXPECT_FLOAT_EQ(t[1], 3.14);
        }

        {
            Vec<float, 2> x({1.618f, 3.14f}), y, z, t;
            t = std::move(z = y = x);
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 3.14);
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 3.14);
            EXPECT_FLOAT_EQ(t[0], 1.618);
            EXPECT_FLOAT_EQ(t[1], 3.14);
        }
    }
}

TEST(ClassVec, Destructor)
{
    std::string testName("ClassVec.Destructor");

    {
        printSection(testName, "Destructor on a simple vector");

        Vec<float, 3>* x(new Vec<float, 3>({1.618f, 3.14f, 1.414f}));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on a vector created by copy");

        Vec<float, 3>* x(new Vec<float, 3>({1.618f, 3.14f, 1.414f})), *y(new Vec<float, 3>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on a vector created by move constructor");

        Vec<float, 3>* x(new Vec<float, 3>({1.618f, 3.14f, 1.414f})), *y(new Vec<float, 3>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassVec, AdditionOperators)
{
    std::string testName("ClassFrac.AdditionOperators");

    {
        printSection(testName, "Frac<T>::operator+=(const Frac<T>& x)");

        Frac<Int> x(3, 7), y(-4, 9);
        x += y;
        EXPECT_EQ(x.num(), -1);
        EXPECT_EQ(x.denom(), 63);
    }

    {
        printSection(testName, "operator+(const Frac<T>& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x + y;
        EXPECT_EQ(z.num(), -1);
        EXPECT_EQ(z.denom(), 63);
    }

    {
        printSection(testName, "operator+(Frac<T>&& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) + y;
        EXPECT_EQ(z.num(), -1);
        EXPECT_EQ(z.denom(), 63);
    }

    {
        printSection(testName, "operator+(const Frac<T>& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x + std::move(y);
        EXPECT_EQ(z.num(), -1);
        EXPECT_EQ(z.denom(), 63);
    }

    {
        printSection(testName, "operator+(Frac<T>&& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) + std::move(y);
        EXPECT_EQ(z.num(), -1);
        EXPECT_EQ(z.denom(), 63);
    }
}

TEST(ClassVec, SubstractionOperators)
{
    std::string testName("ClassFrac.SubstractionOperators");

    {
        printSection(testName, "Frac<T>::operator-=(const Frac<T>& x)");

        Frac<Int> x(3, 7), y(-4, 9);
        x -= y;
        EXPECT_EQ(x.num(), 55);
        EXPECT_EQ(x.denom(), 63);
    }

    {
        printSection(testName, "operator-(const Frac<T>& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x - y;
        EXPECT_EQ(z.num(), 55);
        EXPECT_EQ(z.denom(), 63);
    }

    {
        printSection(testName, "operator-(Frac<T>&& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) - y;
        EXPECT_EQ(z.num(), 55);
        EXPECT_EQ(z.denom(), 63);
    }

    {
        printSection(testName, "operator-(const Frac<T>& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x - std::move(y);
        EXPECT_EQ(z.num(), 55);
        EXPECT_EQ(z.denom(), 63);
    }

    {
        printSection(testName, "operator-(Frac<T>&& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) - std::move(y);
        EXPECT_EQ(z.num(), 55);
        EXPECT_EQ(z.denom(), 63);
    }
}

TEST(ClassVec, MultiplicationOperators)
{
    std::string testName("ClassFrac.MultiplicationOperators");

    {
        printSection(testName, "Frac<T>::operator*=(const Frac<T>& x)");

        Frac<Int> x(3, 7), y(-4, 9);
        x *= y;
        EXPECT_EQ(x.num(), -4);
        EXPECT_EQ(x.denom(), 21);
    }

    {
        printSection(testName, "operator*(const Frac<T>& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x * y;
        EXPECT_EQ(z.num(), -4);
        EXPECT_EQ(z.denom(), 21);
    }

    {
        printSection(testName, "operator*(Frac<T>&& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) * y;
        EXPECT_EQ(z.num(), -4);
        EXPECT_EQ(z.denom(), 21);
    }

    {
        printSection(testName, "operator*(const Frac<T>& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x * std::move(y);
        EXPECT_EQ(z.num(), -4);
        EXPECT_EQ(z.denom(), 21);
    }

    {
        printSection(testName, "operator*(Frac<T>&& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) * std::move(y);
        EXPECT_EQ(z.num(), -4);
        EXPECT_EQ(z.denom(), 21);
    }
}

TEST(ClassVec, DivisionOperators)
{
    std::string testName("ClassFrac.DivisionOperators");

    {
        printSection(testName, "Frac<T>::operator/=(const Frac<T>& x)");

        Frac<Int> x(3, 7), y(-4, 9);
        x /= y;
        EXPECT_EQ(x.num(), -27);
        EXPECT_EQ(x.denom(), 28);
    }

    {
        printSection(testName, "operator/(const Frac<T>& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = x / y;
        EXPECT_EQ(z.num(), -27);
        EXPECT_EQ(z.denom(), 28);
    }

    {
        printSection(testName, "operator/(Frac<T>&& x, const Frac<T>& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) / y;
        EXPECT_EQ(z.num(), -27);
        EXPECT_EQ(z.denom(), 28);
    }

    {
        printSection(testName, "operator/(Frac<T>&& x, Frac<T>&& y)");

        Frac<Int> x(3, 7), y(-4, 9), z;
        z = std::move(x) / std::move(y);
        EXPECT_EQ(z.num(), -27);
        EXPECT_EQ(z.denom(), 28);
    }
}

TEST(ClassVec, UnaryOperators)
{
    std::string testName("ClassFrac.UnaryOperators");

    {
        printSection(testName, "operator-(const Frac<T>& x)");

        Frac<Int> x(-3, 7), y;
        y = -x;
        EXPECT_EQ(x.num(), -3);
        EXPECT_EQ(x.denom(), 7);
        EXPECT_EQ(y.num(), 3);
        EXPECT_EQ(y.denom(), 7);
    }

    {
        printSection(testName, "operator+(const Frac<T>& x)");

        Frac<Int> x(-3, 7), y;
        y = +x;
        EXPECT_EQ(x.num(), -3);
        EXPECT_EQ(x.denom(), 7);
        EXPECT_EQ(y.num(), -3);
        EXPECT_EQ(y.denom(), 7);
    }

    {
        printSection(testName, "operator-(Frac<T>&& x)");

        Frac<Int> x(-3, 7), y;
        y = -std::move(x);
        EXPECT_EQ(y.num(), 3);
        EXPECT_EQ(y.denom(), 7);
    }

    {
        printSection(testName, "operator+(Frac<T>&& x)");

        Frac<Int> x(-3, 7), y;
        y = +std::move(x);
        EXPECT_EQ(y.num(), -3);
        EXPECT_EQ(y.denom(), 7);
    }
}

TEST(ClassVec, Comparators)
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

    {
        printSection(testName, "operator>(const Frac<T>& x, const Frac<T>& y)");

        {
            Frac<Int> x(3, 7), y(4, 9);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, true);
        }

        {
            Frac<Int> x(-3, 7), y(4, 9);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, true);
        }

        {
            Frac<Int> x(-3, 7), y(-4, 9);
            EXPECT_EQ(x > y, true);
            EXPECT_EQ(y > x, false);
        }

        {
            Frac<Int> x(3, 7), y(3, 7);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);
        }

        {
            Frac<Int> x(-3, 7), y(-3, 7);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);
        }
    }

    {
        printSection(testName, "operator<(const Frac<T>& x, const Frac<T>& y)");

        {
            Frac<Int> x(3, 7), y(4, 9);
            EXPECT_EQ(x < y, true);
            EXPECT_EQ(y < x, false);
        }

        {
            Frac<Int> x(-3, 7), y(4, 9);
            EXPECT_EQ(x < y, true);
            EXPECT_EQ(y < x, false);
        }

        {
            Frac<Int> x(-3, 7), y(-4, 9);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, true);
        }

        {
            Frac<Int> x(3, 7), y(3, 7);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);
        }

        {
            Frac<Int> x(-3, 7), y(-3, 7);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);
        }
    }

    {
        printSection(testName, "operator>=(const Frac<T>& x, const Frac<T>& y)");

        {
            Frac<Int> x(3, 7), y(4, 9);
            EXPECT_EQ(x >= y, false);
            EXPECT_EQ(y >= x, true);
        }

        {
            Frac<Int> x(-3, 7), y(4, 9);
            EXPECT_EQ(x >= y, false);
            EXPECT_EQ(y >= x, true);
        }

        {
            Frac<Int> x(-3, 7), y(-4, 9);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, false);
        }

        {
            Frac<Int> x(3, 7), y(3, 7);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);
        }

        {
            Frac<Int> x(-3, 7), y(-3, 7);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);
        }
    }

    {
        printSection(testName, "operator<=(const Frac<T>& x, const Frac<T>& y)");

        {
            Frac<Int> x(3, 7), y(4, 9);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, false);
        }

        {
            Frac<Int> x(-3, 7), y(4, 9);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, false);
        }

        {
            Frac<Int> x(-3, 7), y(-4, 9);
            EXPECT_EQ(x <= y, false);
            EXPECT_EQ(y <= x, true);
        }

        {
            Frac<Int> x(3, 7), y(3, 7);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);
        }

        {
            Frac<Int> x(-3, 7), y(-3, 7);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);
        }
    }
}

TEST(ClassVec, StreamOperators)
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

TEST(ClassVec, BonusTests)
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
