#include "main.hpp"


TEST(ClassQuaternion, Constructors)
{
    std::string testName("ClassQuaternion.Constructors");

    {
        printSection(testName, "Quaternion<T>::Quaternion()");

        {
            Quaternion<int> x;
            EXPECT_EQ(x.a, 0);
            EXPECT_EQ(x.b, 0);
            EXPECT_EQ(x.c, 0);
            EXPECT_EQ(x.d, 0);
        }

        {
            Quaternion<float> x;
            EXPECT_FLOAT_EQ(x.a, 0);
            EXPECT_FLOAT_EQ(x.b, 0);
            EXPECT_FLOAT_EQ(x.c, 0);
            EXPECT_FLOAT_EQ(x.d, 0);
        }
    }

    {
        printSection(testName, "Quaternion<T>::Quaternion(int64_t x)");

        Quaternion<float> x((int64_t) 161803398874989);
        EXPECT_FLOAT_EQ(x.a, 161803398874989);
        EXPECT_FLOAT_EQ(x.b, 0);
        EXPECT_FLOAT_EQ(x.c, 0);
        EXPECT_FLOAT_EQ(x.d, 0);
    }

    {
        printSection(testName, "Quaternion<T>::Quaternion(const T& x)");

        Quaternion<float> x(1.618f);
        EXPECT_FLOAT_EQ(x.a, 1.618f);
        EXPECT_FLOAT_EQ(x.b, 0);
        EXPECT_FLOAT_EQ(x.c, 0);
        EXPECT_FLOAT_EQ(x.d, 0);
    }

    {
        printSection(testName, "Quaternion<T>::Quaternion(const T& aValue, const T& bValue, const T& cValue, const T& dValue)");

        Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718);
        EXPECT_FLOAT_EQ(x.a, -1.618);
        EXPECT_FLOAT_EQ(x.b, 3.1416);
        EXPECT_FLOAT_EQ(x.c, -1.414);
        EXPECT_FLOAT_EQ(x.d, 2.718);
    }

    {
        printSection(testName, "Quaternion<T>::Quaternion(const std::array<T, 4>& values)");

        Quaternion<float> x(std::array<float, 4>{-1.618, 3.1416, -1.414, 2.718});
        EXPECT_FLOAT_EQ(x.a, -1.618);
        EXPECT_FLOAT_EQ(x.b, 3.1416);
        EXPECT_FLOAT_EQ(x.c, -1.414);
        EXPECT_FLOAT_EQ(x.d, 2.718);
    }

    {
        printSection(testName, "Quaternion<T>::Quaternion(const Quaternion<T>& x)");

        Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718), y(x);
        EXPECT_FLOAT_EQ(x.a, -1.618);
        EXPECT_FLOAT_EQ(x.b, 3.1416);
        EXPECT_FLOAT_EQ(x.c, -1.414);
        EXPECT_FLOAT_EQ(x.d, 2.718);
        EXPECT_FLOAT_EQ(y.a, -1.618);
        EXPECT_FLOAT_EQ(y.b, 3.1416);
        EXPECT_FLOAT_EQ(y.c, -1.414);
        EXPECT_FLOAT_EQ(y.d, 2.718);
    }

    {
        printSection(testName, "Quaternion<T>::Quaternion(Quaternion<T>&& x)");

        Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718), y(std::move(x));
        EXPECT_FLOAT_EQ(y.a, -1.618);
        EXPECT_FLOAT_EQ(y.b, 3.1416);
        EXPECT_FLOAT_EQ(y.c, -1.414);
        EXPECT_FLOAT_EQ(y.d, 2.718);
    }
}

TEST(ClassQuaternion, AssignmentOperators)
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

TEST(ClassQuaternion, Destructor)
{
    std::string testName("ClassFrac.Destructor");

    {
        printSection(testName, "Destructor on a simple fraction");

        Frac<Int>* x(new Frac<Int>(3, 7));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on an fraction created by copy");

        Frac<Int>* x(new Frac<Int>(3, 7)), *y(new Frac<Int>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on an fraction created by move constructor");

        Frac<Int>* x(new Frac<Int>(161803398874989)), *y(new Frac<Int>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassQuaternion, AdditionOperators)
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

TEST(ClassQuaternion, SubstractionOperators)
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

TEST(ClassQuaternion, MultiplicationOperators)
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

TEST(ClassQuaternion, DivisionOperators)
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

TEST(ClassQuaternion, UnaryOperators)
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

TEST(ClassQuaternion, Comparators)
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

TEST(ClassQuaternion, StreamOperators)
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

TEST(ClassQuaternion, BonusTests)
{
    std::string testName("ClassFrac.BonusTests");
}
