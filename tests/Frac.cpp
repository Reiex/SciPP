#include "main.hpp"


TEST(ClassFrac, Constructors)
{
    std::string testName("ClassFrac.Constructors");

    {
        printSection(testName, "Frac<T>::Frac()");

        Frac<int> x;
        EXPECT_EQ(x.num(), 0);
        EXPECT_EQ(x.denom(), 1);

        Frac<Int> y;
        EXPECT_EQ(y.num(), 0);
        EXPECT_EQ(y.denom(), 1);
    }

    {
        printSection(testName, "Frac<T>::Frac(int64_t x)");

        Frac<Int> x((int64_t) 0);
        EXPECT_EQ(x.num(), 0);
        EXPECT_EQ(x.denom(), 1);

        Frac<Int> y((int64_t) 161803398874989);
        EXPECT_EQ(y.num(), 161803398874989);
        EXPECT_EQ(y.denom(), 1);

        Frac<Int> z((int64_t) -161803398874989);
        EXPECT_EQ(z.num(), -161803398874989);
        EXPECT_EQ(z.denom(), 1);
    }

    {
        printSection(testName, "Frac<T>::Frac(const T& x)");

        Frac<Int> x(Int(0));
        EXPECT_EQ(x.num(), 0);
        EXPECT_EQ(x.denom(), 1);

        Frac<Int> y(Int(161803398874989));
        EXPECT_EQ(y.num(), 161803398874989);
        EXPECT_EQ(y.denom(), 1);

        Frac<Int> z(Int(-161803398874989));
        EXPECT_EQ(z.num(), -161803398874989);
        EXPECT_EQ(z.denom(), 1);
    }

    {
        printSection(testName, "Frac<T>::Frac(const T& p, const T& q)");

        {
            Frac<Int> x(Int(0), Int(1));
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Frac<Int> x(Int(0), Int(161803398874989));
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Frac<Int> x(Int(0), Int(-161803398874989));
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Frac<Int> x(Int(5), Int(3));
            EXPECT_EQ(x.num(), 5);
            EXPECT_EQ(x.denom(), 3);
        }

        {
            Frac<Int> x(Int(-5), Int(-3));
            EXPECT_EQ(x.num(), 5);
            EXPECT_EQ(x.denom(), 3);
        }

        {
            Frac<Int> x(Int(5), Int(-3));
            EXPECT_EQ(x.num(), -5);
            EXPECT_EQ(x.denom(), 3);
        }

        {
            Frac<Int> x(Int(128), Int(-96));
            EXPECT_EQ(x.num(), -4);
            EXPECT_EQ(x.denom(), 3);
        }

        {
            Frac<Int> x(-9, -21);
            EXPECT_EQ(x.num(), 3);
            EXPECT_EQ(x.denom(), 7);
        }
    }

    {
        printSection(testName, "Frac<T>::Frac(const Frac<T>& x)");

        Frac<Int> x(3, 7), y(x);
        EXPECT_EQ(x.num(), 3);
        EXPECT_EQ(x.denom(), 7);
        EXPECT_EQ(y.num(), 3);
        EXPECT_EQ(y.denom(), 7);
    }

    {
        printSection(testName, "Frac<T>::Frac(Frac<T>&& x)");

        Frac<Int> x(3, 7), y(std::move(x));
        EXPECT_EQ(y.num(), 3);
        EXPECT_EQ(y.denom(), 7);
    }
}

TEST(ClassFrac, AssignmentOperators)
{
    std::string testName("ClassFrac.AssignmentOperators");

    {
        printSection(testName, "Frac<T>::operator=(const Frac<T>& x)");

        Frac<Int> x(3, 7), y;
        y = x;
        EXPECT_EQ(x.num(), 3);
        EXPECT_EQ(x.denom(), 7);
        EXPECT_EQ(y.num(), 3);
        EXPECT_EQ(y.denom(), 7);
    }

    {
        printSection(testName, "Frac<T>::operator=(Frac<T>&& x)");

        Frac<Int> x(3, 7), y;
        y = std::move(x);
        EXPECT_EQ(y.num(), 3);
        EXPECT_EQ(y.denom(), 7);
    }

    {
        printSection(testName, "Bonus tests");

        {
            Frac<Int> x(3, 7), y, z, t;
            t = z = y = x;
            EXPECT_EQ(x.num(), 3);
            EXPECT_EQ(x.denom(), 7);
            EXPECT_EQ(y.num(), 3);
            EXPECT_EQ(y.denom(), 7);
            EXPECT_EQ(z.num(), 3);
            EXPECT_EQ(z.denom(), 7);
            EXPECT_EQ(t.num(), 3);
            EXPECT_EQ(t.denom(), 7);
        }

        {
            Frac<Int> x(3, 7), y, z, t;
            t = std::move(z = y = x);
            EXPECT_EQ(x.num(), 3);
            EXPECT_EQ(x.denom(), 7);
            EXPECT_EQ(y.num(), 3);
            EXPECT_EQ(y.denom(), 7);
            EXPECT_EQ(t.num(), 3);
            EXPECT_EQ(t.denom(), 7);
        }
    }
}

TEST(ClassFrac, Destructor)
{
    std::string testName("ClassFrac.Destructor");

    {
        printSection(testName, "Destructor on a simple fraction");

        Frac<Int>* x(new Frac<Int>(3, 7));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on a fraction created by copy");

        Frac<Int>* x(new Frac<Int>(3, 7)), *y(new Frac<Int>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on a fraction created by move constructor");

        Frac<Int>* x(new Frac<Int>(161803398874989)), *y(new Frac<Int>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassFrac, AdditionOperators)
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

TEST(ClassFrac, SubstractionOperators)
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

TEST(ClassFrac, MultiplicationOperators)
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

TEST(ClassFrac, DivisionOperators)
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

TEST(ClassFrac, UnaryOperators)
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

TEST(ClassFrac, Comparators)
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

TEST(ClassFrac, StreamOperators)
{
    std::string testName("ClassFrac.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Frac<T>& x)");

        {
            Frac<Int> x(1618, 3141);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "1618 3141");
        }

        {
            Frac<Int> x(-1618);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "-1618 1");
        }

        {
            Frac<Int> x(0);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "0 1");
        }
    }

    {
        printSection(testName, "operator>>(std::ostream& stream, const Frac<T>& x)");

        {
            Frac<Int> x;
            std::stringstream stream;
            stream << "1618 3141";
            stream >> x;
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 3141);
        }

        {
            Frac<Int> x;
            std::stringstream stream;
            stream << "-1618 1";
            stream >> x;
            EXPECT_EQ(x.num(), -1618);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Frac<Int> x;
            std::stringstream stream;
            stream << "0 1";
            stream >> x;
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }
    }
}

TEST(ClassFrac, ClassRational)
{
    std::string testName("ClassFrac.ClassRational");

    {
        printSection(testName, "Rational::Rational()");

        Rational x;
        EXPECT_EQ(x.num(), 0);
        EXPECT_EQ(x.denom(), 1);
    }

    {
        printSection(testName, "Rational::Rational(int16_t x)");

        {
            Rational x((int16_t) 0);
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x((int16_t) 1618);
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x((int16_t) -1618);
            EXPECT_EQ(x.num(), -1618);
            EXPECT_EQ(x.denom(), 1);
        }
    }

    {
        printSection(testName, "Rational::Rational(int32_t x)");

        {
            Rational x((int32_t) 0);
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x((int32_t) 1618);
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x((int32_t) -1618);
            EXPECT_EQ(x.num(), -1618);
            EXPECT_EQ(x.denom(), 1);
        }
    }

    {
        printSection(testName, "Rational::Rational(int64_t x)");

        {
            Rational x((int64_t) 0);
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x((int64_t) 1618);
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x((int64_t) -1618);
            EXPECT_EQ(x.num(), -1618);
            EXPECT_EQ(x.denom(), 1);
        }
    }

    {
        printSection(testName, "Rational::Rational(const Int& x)");

        {
            Rational x(Int(0));
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x(Int(1618));
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x(Int(-1618));
            EXPECT_EQ(x.num(), -1618);
            EXPECT_EQ(x.denom(), 1);
        }
    }

    {
        printSection(testName, "Rational::Rational(const Int& p, const Int& q)");

        {
            Rational x(0, -129);
            EXPECT_EQ(x.num(), 0);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x(1618, -2);
            EXPECT_EQ(x.num(), -809);
            EXPECT_EQ(x.denom(), 1);
        }

        {
            Rational x(1618, 1617);
            EXPECT_EQ(x.num(), 1618);
            EXPECT_EQ(x.denom(), 1617);
        }
    }

    {
        printSection(testName, "Rational::Rational(float x)");

        {
            Rational x(1.618f);
            long double y = std::stold(x.decimals(7));
            EXPECT_NEAR(y, 1.618L, 1e-7L);
        }

        {
            Rational x(-1e-6f);
            long double y = std::stold(x.decimals(7));
            EXPECT_NEAR(y, -1e-6L, 1e-7L);
        }

        {
            Rational x(1e16f);
            long double y = std::stold(x.decimals(0));
            EXPECT_NEAR(y, 1e16L, 1e9L);
        }
    }

    {
        printSection(testName, "Rational::Rational(double x)");

        {
            Rational x(1.618);
            long double y = std::stold(x.decimals(15));
            EXPECT_NEAR(y, 1.618L, 1e-15L);
        }

        {
            Rational x(-1e-6);
            long double y = std::stold(x.decimals(15));
            EXPECT_NEAR(y, -1e-6L, 1e-15L);
        }

        {
            Rational x(1e16);
            long double y = std::stold(x.decimals(0));
            EXPECT_NEAR(y, 1e16L, 1);
        }
    }

    {
        printSection(testName, "Rational::Rational(long double x)");

        {
            Rational x(1.618L);
            long double y = std::stold(x.decimals(25));
            EXPECT_NEAR(y, 1.618L, 1e-25L);
        }

        {
            Rational x(-1e-6L);
            long double y = std::stold(x.decimals(25));
            EXPECT_NEAR(y, -1e-6L, 1e-25L);
        }

        {
            Rational x(1e16L);
            long double y = std::stold(x.decimals(10));
            EXPECT_NEAR(y, 1e16L, 1e-10);
        }
    }

    {
        printSection(testName, "Rational::Rational(const Frac<Int>& x)");

        EXPECT_EQ(0, 1);
    }

    {
        printSection(testName, "Rational::decimals(uint64_t n)");
    }

    {
        printSection(testName, "operator<<(std::ostream& stream, const Rational& x)");
    }
}

TEST(ClassFrac, BonusTests)
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
