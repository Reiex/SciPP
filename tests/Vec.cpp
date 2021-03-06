#include "main.hpp"


TEST(ClassVec, Constructors)
{
    std::string testName("ClassVec.Constructors");

    {
        printSection(testName, "Vec<T>::Vec(uint64_t count, int64_t x)");

        {
            Vec<float> x(0);
            Vec<float> y(0, (int64_t) 5);
        }

        {
            Vec<float> x(3);
            EXPECT_EQ(x[0], 0.f);
            EXPECT_EQ(x[1], 0.f);
            EXPECT_EQ(x[2], 0.f);
        }

        {
            Vec<Rational> x(3);
            EXPECT_EQ(x[0], Rational(0, 1));
            EXPECT_EQ(x[1], Rational(0, 1));
            EXPECT_EQ(x[2], Rational(0, 1));
        }

        {
            Vec<float> x(3, (int64_t) 1618);
            EXPECT_EQ(x[0], 1618);
            EXPECT_EQ(x[1], 1618);
            EXPECT_EQ(x[2], 1618);
        }

        {
            Vec<Rational> x(3, (int64_t) -1618);
            EXPECT_EQ(x[0], Rational(-1618, 1));
            EXPECT_EQ(x[1], Rational(-1618, 1));
            EXPECT_EQ(x[2], Rational(-1618, 1));
        }
    }

    {
        printSection(testName, "Vec<T>::Vec(uint64_t count, const T& x)");

        {
            Vec<float> y(0, 1.f);
        }

        {
            Vec<float> x(3, 1.f);
            EXPECT_EQ(x[0], 1.f);
            EXPECT_EQ(x[1], 1.f);
            EXPECT_EQ(x[2], 1.f);
        }

        {
            Vec<Rational> x(3, Rational(1, 7));
            EXPECT_EQ(x[0], Rational(1, 7));
            EXPECT_EQ(x[1], Rational(1, 7));
            EXPECT_EQ(x[2], Rational(1, 7));
        }

        {
            Vec<float> x(3, 1.618f);
            EXPECT_EQ(x[0], 1.618f);
            EXPECT_EQ(x[1], 1.618f);
            EXPECT_EQ(x[2], 1.618f);
        }

        {
            Vec<Rational> x(3, (int64_t) -1618);
            EXPECT_EQ(x[0], Rational(-1618, 1));
            EXPECT_EQ(x[1], Rational(-1618, 1));
            EXPECT_EQ(x[2], Rational(-1618, 1));
        }
    }

    {
        printSection(testName, "Vec<T>::Vec(const std::vector<T>& values)");

        {
            Vec<float> x(std::vector<float>({}));
            EXPECT_EQ(x.n, 0);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f});
            EXPECT_EQ(x.n, 3);
            EXPECT_FLOAT_EQ(x[0], 1.618f);
            EXPECT_FLOAT_EQ(x[1], 3.14f);
            EXPECT_FLOAT_EQ(x[2], 1.414f);
        }
    }

    {
        printSection(testName, "Vec<T>::Vec(const Vec<T>& x)");

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f }), y(x);
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 3.14);
            EXPECT_FLOAT_EQ(x[2], 1.414);
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 3.14);
            EXPECT_FLOAT_EQ(y[2], 1.414);
        }
    }

    {
        printSection(testName, "Vec<T, n>::Vec(Vec<T, n>&& x)");

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f }), y(std::move(x));
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 3.14);
            EXPECT_FLOAT_EQ(y[2], 1.414);
        }
    }
}

TEST(ClassVec, AssignmentOperators)
{
    std::string testName("ClassVec.AssignmentOperators");

    {
        printSection(testName, "Vec<T>::operator=(const Vec<T>& x)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y(3);
            y = x;
            EXPECT_FLOAT_EQ(x[0], 1.618);
            EXPECT_FLOAT_EQ(x[1], 3.14);
            EXPECT_FLOAT_EQ(x[2], 1.414);
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 3.14);
            EXPECT_FLOAT_EQ(y[2], 1.414);
        }
    }

    {
        printSection(testName, "Vec<T>::operator=(Vec<T>&& x)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y(3);
            y = std::move(x);
            EXPECT_FLOAT_EQ(y[0], 1.618);
            EXPECT_FLOAT_EQ(y[1], 3.14);
            EXPECT_FLOAT_EQ(y[2], 1.414);
        }
    }

    {
        printSection(testName, "Bonus tests");

        {
            Vec<float> x(std::vector<float>{1.618f, 3.14f}), y(2), z(2), t(2);
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
            Vec<float> x(std::vector<float>{1.618f, 3.14f}), y(2), z(2), t(2);
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

        Vec<float>* x(new Vec<float>({1.618f, 3.14f, 1.414f}));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on a vector created by copy");

        Vec<float>* x(new Vec<float>({1.618f, 3.14f, 1.414f})), *y(new Vec<float>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on a vector created by move constructor");

        Vec<float>* x(new Vec<float>({1.618f, 3.14f, 1.414f})), *y(new Vec<float>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassVec, AdditionOperators)
{
    std::string testName("ClassVec.AdditionOperators");

    {
        printSection(testName, "Vec<T>::operator+=(const Vec<T>& x)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            x += y;
            EXPECT_FLOAT_EQ(x[0], 2.195);
            EXPECT_FLOAT_EQ(x[1], 9.81);
            EXPECT_FLOAT_EQ(x[2], 4.132);
        }
    }

    {
        printSection(testName, "operator+(const Vec<T>& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x + y;
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }

    {
        printSection(testName, "operator+(Vec<T>&& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) + y;
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }

    {
        printSection(testName, "operator+(const Vec<T>& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x + std::move(y);
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }

    {
        printSection(testName, "operator+(Vec<T>&& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) + std::move(y);
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }
}

TEST(ClassVec, SubstractionOperators)
{
    std::string testName("ClassVec.SubstractionOperators");

    {
        printSection(testName, "Vec<T>::operator-=(const Vec<T>& x)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            x -= y;
            EXPECT_FLOAT_EQ(x[0], 1.041);
            EXPECT_FLOAT_EQ(x[1], -3.53);
            EXPECT_FLOAT_EQ(x[2], -1.304);
        }
    }

    {
        printSection(testName, "operator-(const Vec<T>& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x - y;
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }

    {
        printSection(testName, "operator-(Vec<T>&& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) - y;
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }

    {
        printSection(testName, "operator-(const Vec<T>& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x - std::move(y);
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }

    {
        printSection(testName, "operator-(Vec<T>&& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) - std::move(y);
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }
}

TEST(ClassVec, MultiplicationOperators)
{
    std::string testName("ClassVec.MultiplicationOperators");

    {
        printSection(testName, "Vec<T>::operator*=(const Vec<T>& x)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            x *= y;
            EXPECT_FLOAT_EQ(x[0], 0.933586);
            EXPECT_FLOAT_EQ(x[1], 20.9438);
            EXPECT_FLOAT_EQ(x[2], 3.843252);
        }
    }

    {
        printSection(testName, "operator*(const Vec<T>& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x * y;
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }

    {
        printSection(testName, "operator*(Vec<T>&& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) * y;
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }

    {
        printSection(testName, "operator*(const Vec<T>& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x * std::move(y);
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }

    {
        printSection(testName, "operator*(Vec<T>&& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) * std::move(y);
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }
}

TEST(ClassVec, DivisionOperators)
{
    std::string testName("ClassVec.DivisionOperators");

    {
        printSection(testName, "Vec<T>::operator/=(const Vec<T>& x)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            x /= y;
            EXPECT_NEAR(x[0], 2.8042, 1e-4);
            EXPECT_NEAR(x[1], 0.4708, 1e-4);
            EXPECT_NEAR(x[2], 0.5202, 1e-4);
        }
    }

    {
        printSection(testName, "operator/(const Vec<T>& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = x / y;
        EXPECT_NEAR(z[0], 2.8042, 1e-4);
        EXPECT_NEAR(z[1], 0.4708, 1e-4);
        EXPECT_NEAR(z[2], 0.5202, 1e-4);
    }

    {
        printSection(testName, "operator/(Vec<T>&& x, const Vec<T>& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) / y;
        EXPECT_NEAR(z[0], 2.8042, 1e-4);
        EXPECT_NEAR(z[1], 0.4708, 1e-4);
        EXPECT_NEAR(z[2], 0.5202, 1e-4);
    }

    {
        printSection(testName, "operator/(Vec<T>&& x, Vec<T>&& y)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z(3);
        z = std::move(x) / std::move(y);
        EXPECT_NEAR(z[0], 2.8042, 1e-4);
        EXPECT_NEAR(z[1], 0.4708, 1e-4);
        EXPECT_NEAR(z[2], 0.5202, 1e-4);
    }
}

TEST(ClassVec, ModuloOperators)
{
    std::string testName("ClassVec.ModuloOperators");

    {
        printSection(testName, "Vec<T>::operator%=(const Vec<T>& x)");

        {
            Vec<uint64_t> x({1618, 314, 1414}), y({58, 67, 27});
            x %= y;
            EXPECT_FLOAT_EQ(x[0], 52);
            EXPECT_FLOAT_EQ(x[1], 46);
            EXPECT_FLOAT_EQ(x[2], 10);
        }
    }

    {
        printSection(testName, "operator%(const Vec<T>& x, const Vec<T>& y)");

        Vec<uint64_t> x({1618, 314, 1414}), y({58, 67, 27}), z(3);
        z = x % y;
        EXPECT_FLOAT_EQ(z[0], 52);
        EXPECT_FLOAT_EQ(z[1], 46);
        EXPECT_FLOAT_EQ(z[2], 10);
    }

    {
        printSection(testName, "operator%(Vec<T>&& x, const Vec<T>& y)");

        Vec<uint64_t> x({1618, 314, 1414}), y({58, 67, 27}), z(3);
        z = std::move(x) % y;
        EXPECT_FLOAT_EQ(z[0], 52);
        EXPECT_FLOAT_EQ(z[1], 46);
        EXPECT_FLOAT_EQ(z[2], 10);
    }

    {
        printSection(testName, "operator%(Vec<T>&& x, Vec<T>&& y)");

        Vec<uint64_t> x({1618, 314, 1414}), y({58, 67, 27}), z(3);
        z = std::move(x) % std::move(y);
        EXPECT_FLOAT_EQ(z[0], 52);
        EXPECT_FLOAT_EQ(z[1], 46);
        EXPECT_FLOAT_EQ(z[2], 10);
    }
}

TEST(ClassVec, UnaryOperators)
{
    std::string testName("ClassVec.UnaryOperators");

    {
        printSection(testName, "operator-(const Vec<T>& x)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y(3);
        y = -x;
        EXPECT_FLOAT_EQ(x[0], 1.618);
        EXPECT_FLOAT_EQ(x[1], 3.14);
        EXPECT_FLOAT_EQ(x[2], 1.414);
        EXPECT_FLOAT_EQ(y[0], -1.618);
        EXPECT_FLOAT_EQ(y[1], -3.14);
        EXPECT_FLOAT_EQ(y[2], -1.414);
    }

    {
        printSection(testName, "operator+(const Vec<T>& x)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y(3);
        y = +x;
        EXPECT_FLOAT_EQ(x[0], 1.618);
        EXPECT_FLOAT_EQ(x[1], 3.14);
        EXPECT_FLOAT_EQ(x[2], 1.414);
        EXPECT_FLOAT_EQ(y[0], 1.618);
        EXPECT_FLOAT_EQ(y[1], 3.14);
        EXPECT_FLOAT_EQ(y[2], 1.414);
    }

    {
        printSection(testName, "operator-(Vec<T>&& x)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y(3);
        y = -std::move(x);
        EXPECT_FLOAT_EQ(y[0], -1.618);
        EXPECT_FLOAT_EQ(y[1], -3.14);
        EXPECT_FLOAT_EQ(y[2], -1.414);
    }

    {
        printSection(testName, "operator+(Vec<T>&& x)");

        Vec<float> x({1.618f, 3.14f, 1.414f}), y(3);
        y = +std::move(x);
        EXPECT_FLOAT_EQ(y[0], 1.618);
        EXPECT_FLOAT_EQ(y[1], 3.14);
        EXPECT_FLOAT_EQ(y[2], 1.414);
    }
}

TEST(ClassVec, Comparators)
{
    std::string testName("ClassVec.Comparators");

    {
        printSection(testName, "operator==(const Vec<T>& x, const Vec<T>& y)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 1.414f});
            EXPECT_EQ(x == x, true);
            EXPECT_EQ(x == y, true);
            EXPECT_EQ(y == y, true);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 2.718f});
            EXPECT_EQ(x == y, false);
            EXPECT_EQ(y == x, false);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            EXPECT_EQ(x == y, false);
            EXPECT_EQ(y == x, false);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y(std::vector<float>{6.67f, 2.718f});
            EXPECT_EQ(x == y, false);
            EXPECT_EQ(y == x, false);
        }
    }

    {
        printSection(testName, "operator!=(const Vec<T>& x, const Vec<T>& y)");

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 1.414f});
            EXPECT_EQ(x != x, false);
            EXPECT_EQ(x != y, false);
            EXPECT_EQ(y != y, false);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 2.718f});
            EXPECT_EQ(x != y, true);
            EXPECT_EQ(y != x, true);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            EXPECT_EQ(x != y, true);
            EXPECT_EQ(y != x, true);
        }

        {
            Vec<float> x({1.618f, 3.14f, 1.414f}), y(std::vector<float>{6.67f, 2.718f});
            EXPECT_EQ(x != y, true);
            EXPECT_EQ(y != x, true);
        }
    }
}

TEST(ClassVec, StreamOperators)
{
    std::string testName("ClassVec.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Vec<T>& x)");

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f });
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "1.618 3.14 1.414");
        }

        {
            Vec<float> x(3);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "0 0 0");
        }

        {
            Vec<float> x(0);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "");
        }
    }
}

TEST(ClassVec, SpecificFunctions)
{
    std::string testName("ClassVec.SpecificFunctions");

    {
        printSection(testName, "minElement(const Vec<T>& a)");

        Vec<float> x({ 1.6f, -1.8f, 0.3f, -3.9f, 8.8f, -7.4f });
        EXPECT_FLOAT_EQ(minElement(x), -7.4f);
    }

    {
        printSection(testName, "maxElement(const Vec<T>& a)");

        Vec<float> x({ 1.6f, -1.8f, 0.3f, -3.9f, 8.8f, -7.4f });
        EXPECT_FLOAT_EQ(maxElement(x), 8.8f);
    }

    {
        printSection(testName, "dot(const Vec<T>& u, const Vec<T>& v)");

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f }), y({ 0.577f, 6.67f, 2.718f });
            EXPECT_FLOAT_EQ(dot(x, y), 25.720638);
        }

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f, -6.67f }), y({ 0.577f, 6.67f, 2.718f, 6.28f });
            EXPECT_FLOAT_EQ(dot(x, y), -16.166962);
        }

        {
            Vec<float> x(0), y(0);
            EXPECT_FLOAT_EQ(dot(x, y), 0);
        }
    }

    {
        printSection(testName, "cross(const Vec<T>& u, const Vec<T>& v)");

        {
            Vec<float> x({ 1.f, 2.f, 3.f }), y({ 4.f, 5.f, 6.f }), z({ -3.f, 6.f, -3.f });
            EXPECT_EQ(cross(x, y), z);
        }

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f }), y({ 0.577f, 6.67f, 2.718f }), z(cross(x, y));
            EXPECT_FLOAT_EQ(z[0], -0.89686f);
            EXPECT_FLOAT_EQ(z[1], -3.581846f);
            EXPECT_FLOAT_EQ(z[2], 8.98028f);
        }
    }

    {
        printSection(testName, "normSq(const Vec<T>& v)");

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f });
            EXPECT_FLOAT_EQ(normSq(x), 14.47692);
        }

        {
            Vec<float> x(0);
            EXPECT_FLOAT_EQ(normSq(x), 0);
        }
    }

    {
        printSection(testName, "norm(const Vec<T>& v)");

        {
            Vec<float> x({ 1.618f, 3.14f, 1.414f });
            EXPECT_NEAR(norm(x), 3.805, 1e-3);
        }

        {
            Vec<float> x(0);
            EXPECT_FLOAT_EQ(norm(x), 0);
        }
    }

    {
        printSection(testName, "convolve(const Vec<T>& a, const Vec<T>& b, ConvolveMethod method)");

        {
            Vec<float> x({ 1.6f, 1.8f, 0.3f, 3.9f }), y({ 1.f, 0.01f, 0.0001f }), z(4);

            z = convolve(x, y);
            EXPECT_NEAR(z[0], 3.91618f, 1e-5);
            EXPECT_NEAR(z[1], 1.61803f, 1e-5);
            EXPECT_NEAR(z[2], 1.80339f, 1e-5);
            EXPECT_NEAR(z[3], 0.33916f, 1e-5);

            z = convolve(x, y, ConvolveMethod::Continuous);
            EXPECT_NEAR(z[0], 1.61618f, 1e-5);
            EXPECT_NEAR(z[1], 1.61803f, 1e-5);
            EXPECT_NEAR(z[2], 1.80339f, 1e-5);
            EXPECT_NEAR(z[3], 0.33939f, 1e-5);

            z = convolve(x, y, ConvolveMethod::Zero);
            EXPECT_NEAR(z[0], 0.01618f, 1e-5);
            EXPECT_NEAR(z[1], 1.61803f, 1e-5);
            EXPECT_NEAR(z[2], 1.80339f, 1e-5);
            EXPECT_NEAR(z[3], 0.33900f, 1e-5);
        }
    }

    {
        printSection(testName, "dft(const Vec<std::complex<T>>& f)");

        {
            Vec<std::complex<float>> f({
                    std::complex<float>(1, 0),
                    std::complex<float>(0, 1),
                    std::complex<float>(-1, 0),
                    std::complex<float>(0, -1)
                });

            Vec<std::complex<float>> fh({
                    std::complex<float>(0, 0),
                    std::complex<float>(4, 0),
                    std::complex<float>(0, 0),
                    std::complex<float>(0, 0)
                });

            float l = std::abs(normSq(fh - dft(f)));

            EXPECT_NEAR(l, 0, 1e-10);
        }

        {
            const uint64_t n = 100;
            Vec<std::complex<float>> f(n);
            for (uint64_t i(0); i < n; i++)
            {
                float x = (2.f * pi * i) / n;
                f[i] = std::complex<float>(std::cos(x), std::sin(x));
            }

            Vec<std::complex<float>> fh(dft(f));
            for (uint64_t i(0); i < n; i++)
            {
                if (i == 1)
                    EXPECT_NEAR(fh[i].real(), n, 1e-3);
                else
                    EXPECT_NEAR(fh[i].real(), 0, 1e-3);
                EXPECT_NEAR(fh[i].imag(), 0, 1e-3);
            }
        }
    }

    {
        printSection(testName, "idft(const Vec<std::complex<T>>& fh)");

        const uint64_t n = 100;
        Vec<std::complex<float>> f(n);
        for (uint64_t i(0); i < n; i++)
            f[i] = (float(std::rand()) / RAND_MAX);

        Vec<std::complex<float>> g(idft(dft(f)));
        for (uint64_t i(0); i < n; i++)
        {
            EXPECT_NEAR(f[i].real(), g[i].real(), 1e-3);
            EXPECT_NEAR(f[i].imag(), g[i].imag(), 1e-3);
        }
    }

    {
        printSection(testName, "dct(const Vec<T>& f) and idct(const Vec<T>& fh)");

        const uint64_t n = 100;
        Vec<float> f(n);
        for (uint64_t i(0); i < n; i++)
            f[i] = (float(std::rand()) / RAND_MAX);

        Vec<float> g = idct(dct(f));
        for (uint64_t i(0); i < n; i++)
        {
            EXPECT_NEAR(f[i], g[i], 1e-3);
        }
    }
}
