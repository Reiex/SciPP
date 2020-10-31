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
    std::string testName("ClassVec.AdditionOperators");

    {
        printSection(testName, "Vec<T, n>::operator+=(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
        x += y;
        EXPECT_FLOAT_EQ(x[0], 2.195);
        EXPECT_FLOAT_EQ(x[1], 9.81);
        EXPECT_FLOAT_EQ(x[2], 4.132);
    }

    {
        printSection(testName, "operator+(const Vec<T, n>& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x + y;
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }

    {
        printSection(testName, "operator+(Vec<T, n>&& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = std::move(x) + y;
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }

    {
        printSection(testName, "operator+(const Vec<T, n>& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x + std::move(y);
        EXPECT_FLOAT_EQ(z[0], 2.195);
        EXPECT_FLOAT_EQ(z[1], 9.81);
        EXPECT_FLOAT_EQ(z[2], 4.132);
    }

    {
        printSection(testName, "operator+(Vec<T, n>&& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
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
        printSection(testName, "Vec<T, n>::operator-=(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
        x -= y;
        EXPECT_FLOAT_EQ(x[0], 1.041);
        EXPECT_FLOAT_EQ(x[1], -3.53);
        EXPECT_FLOAT_EQ(x[2], -1.304);
    }

    {
        printSection(testName, "operator-(const Vec<T, n>& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x - y;
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }

    {
        printSection(testName, "operator-(Vec<T, n>&& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = std::move(x) - y;
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }

    {
        printSection(testName, "operator-(const Vec<T, n>& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x - std::move(y);
        EXPECT_FLOAT_EQ(z[0], 1.041);
        EXPECT_FLOAT_EQ(z[1], -3.53);
        EXPECT_FLOAT_EQ(z[2], -1.304);
    }

    {
        printSection(testName, "operator-(Vec<T, n>&& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
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
        printSection(testName, "Vec<T, n>::operator*=(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
        x *= y;
        EXPECT_FLOAT_EQ(x[0], 0.933586);
        EXPECT_FLOAT_EQ(x[1], 20.9438);
        EXPECT_FLOAT_EQ(x[2], 3.843252);
    }

    {
        printSection(testName, "operator*(const Vec<T, n>& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x * y;
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }

    {
        printSection(testName, "operator*(Vec<T, n>&& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = std::move(x) * y;
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }

    {
        printSection(testName, "operator*(const Vec<T, n>& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x * std::move(y);
        EXPECT_FLOAT_EQ(z[0], 0.933586);
        EXPECT_FLOAT_EQ(z[1], 20.9438);
        EXPECT_FLOAT_EQ(z[2], 3.843252);
    }

    {
        printSection(testName, "operator*(Vec<T, n>&& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
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
        printSection(testName, "Vec<T, n>::operator/=(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
        x /= y;
        EXPECT_NEAR(x[0], 2.8042, 1e-4);
        EXPECT_NEAR(x[1], 0.4708, 1e-4);
        EXPECT_NEAR(x[2], 0.5202, 1e-4);
    }

    {
        printSection(testName, "operator/(const Vec<T, n>& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = x / y;
        EXPECT_NEAR(z[0], 2.8042, 1e-4);
        EXPECT_NEAR(z[1], 0.4708, 1e-4);
        EXPECT_NEAR(z[2], 0.5202, 1e-4);
    }

    {
        printSection(testName, "operator/(Vec<T, n>&& x, const Vec<T, n>& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
        z = std::move(x) / y;
        EXPECT_NEAR(z[0], 2.8042, 1e-4);
        EXPECT_NEAR(z[1], 0.4708, 1e-4);
        EXPECT_NEAR(z[2], 0.5202, 1e-4);
    }

    {
        printSection(testName, "operator/(Vec<T, n>&& x, Vec<T, n>&& y)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f}), z;
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
        printSection(testName, "Vec<T, n>::operator%=(const Vec<T, n>& x)");

        Vec<uint64_t, 3> x({1618, 314, 1414}), y({58, 67, 27});
        x %= y;
        EXPECT_FLOAT_EQ(x[0], 52);
        EXPECT_FLOAT_EQ(x[1], 46);
        EXPECT_FLOAT_EQ(x[2], 10);
    }

    {
        printSection(testName, "operator%(const Vec<T, n>& x, const Vec<T, n>& y)");

        Vec<uint64_t, 3> x({1618, 314, 1414}), y({58, 67, 27}), z;
        z = x % y;
        EXPECT_FLOAT_EQ(z[0], 52);
        EXPECT_FLOAT_EQ(z[1], 46);
        EXPECT_FLOAT_EQ(z[2], 10);
    }

    {
        printSection(testName, "operator%(Vec<T, n>&& x, const Vec<T, n>& y)");

        Vec<uint64_t, 3> x({1618, 314, 1414}), y({58, 67, 27}), z;
        z = std::move(x) % y;
        EXPECT_FLOAT_EQ(z[0], 52);
        EXPECT_FLOAT_EQ(z[1], 46);
        EXPECT_FLOAT_EQ(z[2], 10);
    }

    {
        printSection(testName, "operator%(Vec<T, n>&& x, Vec<T, n>&& y)");

        Vec<uint64_t, 3> x({1618, 314, 1414}), y({58, 67, 27}), z;
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
        printSection(testName, "operator-(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y;
        y = -x;
        EXPECT_FLOAT_EQ(x[0], 1.618);
        EXPECT_FLOAT_EQ(x[1], 3.14);
        EXPECT_FLOAT_EQ(x[2], 1.414);
        EXPECT_FLOAT_EQ(y[0], -1.618);
        EXPECT_FLOAT_EQ(y[1], -3.14);
        EXPECT_FLOAT_EQ(y[2], -1.414);
    }

    {
        printSection(testName, "operator+(const Vec<T, n>& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y;
        y = +x;
        EXPECT_FLOAT_EQ(x[0], 1.618);
        EXPECT_FLOAT_EQ(x[1], 3.14);
        EXPECT_FLOAT_EQ(x[2], 1.414);
        EXPECT_FLOAT_EQ(y[0], 1.618);
        EXPECT_FLOAT_EQ(y[1], 3.14);
        EXPECT_FLOAT_EQ(y[2], 1.414);
    }

    {
        printSection(testName, "operator-(Vec<T, n>&& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y;
        y = -std::move(x);
        EXPECT_FLOAT_EQ(y[0], -1.618);
        EXPECT_FLOAT_EQ(y[1], -3.14);
        EXPECT_FLOAT_EQ(y[2], -1.414);
    }

    {
        printSection(testName, "operator+(Vec<T, n>&& x)");

        Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y;
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
        printSection(testName, "operator==(const Vec<T, n>& x, const Vec<T, n>& y)");

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 1.414f});
            EXPECT_EQ(x == x, true);
            EXPECT_EQ(x == y, true);
            EXPECT_EQ(y == y, true);
        }

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 2.718f});
            EXPECT_EQ(x == y, false);
            EXPECT_EQ(y == x, false);
        }

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            EXPECT_EQ(x == y, false);
            EXPECT_EQ(y == x, false);
        }
    }

    {
        printSection(testName, "operator!=(const Vec<T, n>& x, const Vec<T, n>& y)");

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 1.414f});
            EXPECT_EQ(x != x, false);
            EXPECT_EQ(x != y, false);
            EXPECT_EQ(y != y, false);
        }

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({1.618f, 3.14f, 2.718f});
            EXPECT_EQ(x != y, true);
            EXPECT_EQ(y != x, true);
        }

        {
            Vec<float, 3> x({1.618f, 3.14f, 1.414f}), y({0.577f, 6.67f, 2.718f});
            EXPECT_EQ(x != y, true);
            EXPECT_EQ(y != x, true);
        }
    }
}

TEST(ClassVec, StreamOperators)
{
    std::string testName("ClassVec.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Vec<T, n>& x)");

        {
            Vec<float, 3> x({ 1.618f, 3.14f, 1.414f });
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "<1.618, 3.14, 1.414>");
        }

        {
            Vec<float, 3> x;
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "<0, 0, 0>");
        }

        {
            Vec<float, 0> x;
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "<>");
        }
    }
}

TEST(ClassVec, SpecificFunctions)
{
    std::string testName("ClassVec.SpecificFunctions");

    {
        printSection(testName, "dot(const Vec<T, n>& u, const Vec<T, n>& v)");

        {
            Vec<float, 3> x({ 1.618f, 3.14f, 1.414f }), y({ 0.577f, 6.67f, 2.718f });
            EXPECT_FLOAT_EQ(dot(x, y), 25.720638);
        }

        {
            Vec<float, 4> x({ 1.618f, 3.14f, 1.414f, -6.67f }), y({ 0.577f, 6.67f, 2.718f, 6.28f });
            EXPECT_FLOAT_EQ(dot(x, y), -16.166962);
        }

        {
            Vec<float, 0> x, y;
            EXPECT_FLOAT_EQ(dot(x, y), 0);
        }
    }

    {
        printSection(testName, "cross(const Vec<T, 3>& u, const Vec<T, 3>& v)");

        {
            Vec<float, 3> x({ 1.f, 2.f, 3.f }), y({ 4.f, 5.f, 6.f }), z({ -3.f, 6.f, -3.f });
            EXPECT_EQ(cross(x, y), z);
        }

        {
            Vec<float, 3> x({ 1.618f, 3.14f, 1.414f }), y({ 0.577f, 6.67f, 2.718f }), z(cross(x, y));
            EXPECT_FLOAT_EQ(z[0], -0.89686f);
            EXPECT_FLOAT_EQ(z[1], -3.581846f);
            EXPECT_FLOAT_EQ(z[2], 8.98028f);
        }
    }
}
