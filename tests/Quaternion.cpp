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
    std::string testName("ClassQuaternion.AssignmentOperators");

    {
        printSection(testName, "Quaternion<T>::operator=(const Quaternion<T>& x)");

        Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718), y;
        y = x;
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
        printSection(testName, "Quaternion<T>::operator=(Quaternion<T>&& x)");

        Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718), y;
        y = std::move(x);
        EXPECT_FLOAT_EQ(y.a, -1.618);
        EXPECT_FLOAT_EQ(y.b, 3.1416);
        EXPECT_FLOAT_EQ(y.c, -1.414);
        EXPECT_FLOAT_EQ(y.d, 2.718);
    }

    {
        printSection(testName, "Bonus tests");

        {
            Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718), y, z, t;
            t = z = y = x;
            EXPECT_FLOAT_EQ(x.a, -1.618);
            EXPECT_FLOAT_EQ(x.b, 3.1416);
            EXPECT_FLOAT_EQ(x.c, -1.414);
            EXPECT_FLOAT_EQ(x.d, 2.718);
            EXPECT_FLOAT_EQ(y.a, -1.618);
            EXPECT_FLOAT_EQ(y.b, 3.1416);
            EXPECT_FLOAT_EQ(y.c, -1.414);
            EXPECT_FLOAT_EQ(y.d, 2.718);
            EXPECT_FLOAT_EQ(z.a, -1.618);
            EXPECT_FLOAT_EQ(z.b, 3.1416);
            EXPECT_FLOAT_EQ(z.c, -1.414);
            EXPECT_FLOAT_EQ(z.d, 2.718);
            EXPECT_FLOAT_EQ(t.a, -1.618);
            EXPECT_FLOAT_EQ(t.b, 3.1416);
            EXPECT_FLOAT_EQ(t.c, -1.414);
            EXPECT_FLOAT_EQ(t.d, 2.718);
        }

        {
            Quaternion<float> x(-1.618, 3.1416, -1.414, 2.718), y, z, t;
            t = std::move(z = y = x);
            EXPECT_FLOAT_EQ(x.a, -1.618);
            EXPECT_FLOAT_EQ(x.b, 3.1416);
            EXPECT_FLOAT_EQ(x.c, -1.414);
            EXPECT_FLOAT_EQ(x.d, 2.718);
            EXPECT_FLOAT_EQ(y.a, -1.618);
            EXPECT_FLOAT_EQ(y.b, 3.1416);
            EXPECT_FLOAT_EQ(y.c, -1.414);
            EXPECT_FLOAT_EQ(y.d, 2.718);
            EXPECT_FLOAT_EQ(t.a, -1.618);
            EXPECT_FLOAT_EQ(t.b, 3.1416);
            EXPECT_FLOAT_EQ(t.c, -1.414);
            EXPECT_FLOAT_EQ(t.d, 2.718);
        }
    }
}

TEST(ClassQuaternion, Destructor)
{
    std::string testName("ClassQuaternion.Destructor");

    {
        printSection(testName, "Destructor on a simple quaternion");

        Quaternion<float>* x(new Quaternion<float>(-1.618, 3.1416, -1.414, 2.718));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on an quaternion created by copy");

        Quaternion<float>* x(new Quaternion<float>(-1.618, 3.1416, -1.414, 2.718)), *y(new Quaternion<float>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on an quaternion created by move constructor");

        Quaternion<float>* x(new Quaternion<float>(-1.618, 3.1416, -1.414, 2.718)), *y(new Quaternion<float>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassQuaternion, AdditionOperators)
{
    std::string testName("ClassQuaternion.AdditionOperators");

    {
        printSection(testName, "Quaternion<T>::operator+=(const Quaternion<T>& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8);
        x += y;
        EXPECT_FLOAT_EQ(x.a, -1.1);
        EXPECT_FLOAT_EQ(x.b, 1.9);
        EXPECT_FLOAT_EQ(x.c, -0.8);
        EXPECT_FLOAT_EQ(x.d, 0.9);
    }

    {
        printSection(testName, "operator+(const Quaternion<T>& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = x + y;
        EXPECT_FLOAT_EQ(z.a, -1.1);
        EXPECT_FLOAT_EQ(z.b, 1.9);
        EXPECT_FLOAT_EQ(z.c, -0.8);
        EXPECT_FLOAT_EQ(z.d, 0.9);
    }

    {
        printSection(testName, "operator+(Quaternion<T>&& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = std::move(x) + y;
        EXPECT_FLOAT_EQ(z.a, -1.1);
        EXPECT_FLOAT_EQ(z.b, 1.9);
        EXPECT_FLOAT_EQ(z.c, -0.8);
        EXPECT_FLOAT_EQ(z.d, 0.9);
    }

    {
        printSection(testName, "operator+(const Quaternion<T>& x, Quaternion<T>&& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = x + std::move(y);
        EXPECT_FLOAT_EQ(z.a, -1.1);
        EXPECT_FLOAT_EQ(z.b, 1.9);
        EXPECT_FLOAT_EQ(z.c, -0.8);
        EXPECT_FLOAT_EQ(z.d, 0.9);
    }

    {
        printSection(testName, "operator+(Quaternion<T>&& x, Quaternion<T>&& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = std::move(x) + std::move(y);
        EXPECT_FLOAT_EQ(z.a, -1.1);
        EXPECT_FLOAT_EQ(z.b, 1.9);
        EXPECT_FLOAT_EQ(z.c, -0.8);
        EXPECT_FLOAT_EQ(z.d, 0.9);
    }
}

TEST(ClassQuaternion, SubstractionOperators)
{
    std::string testName("ClassQuaternion.SubstractionOperators");

    {
        printSection(testName, "Quaternion<T>::operator-=(const Quaternion<T>& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8);
        x -= y;
        EXPECT_FLOAT_EQ(x.a, -2.1);
        EXPECT_FLOAT_EQ(x.b, 4.3);
        EXPECT_FLOAT_EQ(x.c, -2.0);
        EXPECT_FLOAT_EQ(x.d, 4.5);
    }

    {
        printSection(testName, "operator-(const Quaternion<T>& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = x - y;
        EXPECT_FLOAT_EQ(z.a, -2.1);
        EXPECT_FLOAT_EQ(z.b, 4.3);
        EXPECT_FLOAT_EQ(z.c, -2.0);
        EXPECT_FLOAT_EQ(z.d, 4.5);
    }

    {
        printSection(testName, "operator-(Quaternion<T>&& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = std::move(x) - y;
        EXPECT_FLOAT_EQ(z.a, -2.1);
        EXPECT_FLOAT_EQ(z.b, 4.3);
        EXPECT_FLOAT_EQ(z.c, -2.0);
        EXPECT_FLOAT_EQ(z.d, 4.5);
    }

    {
        printSection(testName, "operator-(const Quaternion<T>& x, Quaternion<T>&& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = x - std::move(y);
        EXPECT_FLOAT_EQ(z.a, -2.1);
        EXPECT_FLOAT_EQ(z.b, 4.3);
        EXPECT_FLOAT_EQ(z.c, -2.0);
        EXPECT_FLOAT_EQ(z.d, 4.5);
    }

    {
        printSection(testName, "operator-(Quaternion<T>&& x, Quaternion<T>&& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = std::move(x) - std::move(y);
        EXPECT_FLOAT_EQ(z.a, -2.1);
        EXPECT_FLOAT_EQ(z.b, 4.3);
        EXPECT_FLOAT_EQ(z.c, -2.0);
        EXPECT_FLOAT_EQ(z.d, 4.5);
    }
}

TEST(ClassQuaternion, MultiplicationOperators)
{
    std::string testName("ClassQuaternion.MultiplicationOperators");

    {
        printSection(testName, "Quaternion<T>::operator*=(const Quaternion<T>& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8);
        x *= y;
        EXPECT_NEAR(x.a, 8.62, 1e-6);
        EXPECT_NEAR(x.b, 4.37, 1e-6);
        EXPECT_NEAR(x.c, 0.68, 1e-6);
        EXPECT_NEAR(x.d, 4.41, 1e-6);
    }

    {
        printSection(testName, "operator*(const Quaternion<T>& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = x * y;
        EXPECT_NEAR(z.a, 8.62, 1e-6);
        EXPECT_NEAR(z.b, 4.37, 1e-6);
        EXPECT_NEAR(z.c, 0.68, 1e-6);
        EXPECT_NEAR(z.d, 4.41, 1e-6);
    }

    {
        printSection(testName, "operator*(Quaternion<T>&& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = std::move(x) * y;
        EXPECT_NEAR(z.a, 8.62, 1e-6);
        EXPECT_NEAR(z.b, 4.37, 1e-6);
        EXPECT_NEAR(z.c, 0.68, 1e-6);
        EXPECT_NEAR(z.d, 4.41, 1e-6);
    }

    {
        printSection(testName, "operator*(const Quaternion<T>& x, Quaternion<T>&& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = x * std::move(y);
        EXPECT_NEAR(z.a, 8.62, 1e-6);
        EXPECT_NEAR(z.b, 4.37, 1e-6);
        EXPECT_NEAR(z.c, 0.68, 1e-6);
        EXPECT_NEAR(z.d, 4.41, 1e-6);
    }

    {
        printSection(testName, "operator*(Quaternion<T>&& x, Quaternion<T>&& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(0.5, -1.2, 0.6, -1.8), z;
        z = std::move(x) * std::move(y);
        EXPECT_NEAR(z.a, 8.62, 1e-6);
        EXPECT_NEAR(z.b, 4.37, 1e-6);
        EXPECT_NEAR(z.c, 0.68, 1e-6);
        EXPECT_NEAR(z.d, 4.41, 1e-6);
    }
}

TEST(ClassQuaternion, DivisionOperators)
{
    std::string testName("ClassQuaternion.DivisionOperators");

    {
        printSection(testName, "Quaternion<T>::operator/=(const T& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7);
        x /= 2.f;
        EXPECT_FLOAT_EQ(x.a, -0.8);
        EXPECT_FLOAT_EQ(x.b, 1.55);
        EXPECT_FLOAT_EQ(x.c, -0.7);
        EXPECT_FLOAT_EQ(x.d, 1.35);
    }

    {
        printSection(testName, "operator/(const Quaternion<T>& x, const T& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
        y = x / 2.f;
        EXPECT_FLOAT_EQ(y.a, -0.8);
        EXPECT_FLOAT_EQ(y.b, 1.55);
        EXPECT_FLOAT_EQ(y.c, -0.7);
        EXPECT_FLOAT_EQ(y.d, 1.35);
    }

    {
        printSection(testName, "operator/(Quaternion<T>&& x, const T& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
        y = std::move(x) / 2.f;
        EXPECT_FLOAT_EQ(y.a, -0.8);
        EXPECT_FLOAT_EQ(y.b, 1.55);
        EXPECT_FLOAT_EQ(y.c, -0.7);
        EXPECT_FLOAT_EQ(y.d, 1.35);
    }
}

TEST(ClassQuaternion, UnaryOperators)
{
    std::string testName("ClassQuaternion.UnaryOperators");

    {
        printSection(testName, "operator-(const Quaternion<T>& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
        y = -x;
        EXPECT_FLOAT_EQ(y.a, 1.6);
        EXPECT_FLOAT_EQ(y.b, -3.1);
        EXPECT_FLOAT_EQ(y.c, 1.4);
        EXPECT_FLOAT_EQ(y.d, -2.7);
    }

    {
        printSection(testName, "operator+(const Quaternion<T>& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
        y = +x;
        EXPECT_FLOAT_EQ(y.a, -1.6);
        EXPECT_FLOAT_EQ(y.b, 3.1);
        EXPECT_FLOAT_EQ(y.c, -1.4);
        EXPECT_FLOAT_EQ(y.d, 2.7);
    }

    {
        printSection(testName, "operator-(Quaternion<T>&& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
        y = -std::move(x);
        EXPECT_FLOAT_EQ(y.a, 1.6);
        EXPECT_FLOAT_EQ(y.b, -3.1);
        EXPECT_FLOAT_EQ(y.c, 1.4);
        EXPECT_FLOAT_EQ(y.d, -2.7);
    }

    {
        printSection(testName, "operator+(Quaternion<T>&& x)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
        y = +std::move(x);
        EXPECT_FLOAT_EQ(y.a, -1.6);
        EXPECT_FLOAT_EQ(y.b, 3.1);
        EXPECT_FLOAT_EQ(y.c, -1.4);
        EXPECT_FLOAT_EQ(y.d, 2.7);
    }
}

TEST(ClassQuaternion, Comparators)
{
    std::string testName("ClassQuaternion.Comparators");

    {
        printSection(testName, "operator==(const Quaternion<T>& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(-1.6, 3.1, -1.4, 2.7);
        EXPECT_EQ(x == y, true);

        x = Quaternion<float>(-1.6, 3.1, -1.4, 2.7);
        y = Quaternion<float>(-1.6, 3.1, -1.4, 2.2);
        EXPECT_EQ(x == y, false);
    }

    {
        printSection(testName, "operator!=(const Quaternion<T>& x, const Quaternion<T>& y)");

        Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y(-1.6, 3.1, -1.4, 2.7);
        EXPECT_EQ(x != y, false);

        x = Quaternion<float>(-1.6, 3.1, -1.4, 2.7);
        y = Quaternion<float>(-1.6, 3.1, -1.4, 2.2);
        EXPECT_EQ(x != y, true);
    }
}

TEST(ClassQuaternion, StreamOperators)
{
    std::string testName("ClassQuaternion.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Quaternion<T>& x)");

        {
            Quaternion<float> x(-1.6, 3.1, -1.4, 2.7);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(-1.6,3.1,-1.4,2.7)");
        }

        {
            Quaternion<float> x;
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(0,0,0,0)");
        }
    }
}

TEST(ClassQuaternion, SpecificFunctions)
{
    std::string testName("ClassQuaternion.SpecificFunctions");

    {
        printSection(testName, "inverse(const Quaternion<T>& q)");
        
        {
            Quaternion<float> x(-1.6, 3.1, -1.4, 2.7), y;
            y = x * inverse(x);
            EXPECT_NEAR(y.a, 1.0, 1e-6);
            EXPECT_NEAR(y.b, 0.0, 1e-6);
            EXPECT_NEAR(y.c, 0.0, 1e-6);
            EXPECT_NEAR(y.d, 0.0, 1e-6);
        }
        
        {
            Quaternion<float> x;
            EXPECT_THROW(inverse(x), std::runtime_error);
        }
    }

    {
        printSection(testName, "normSq(const Quaternion<T>& q)");
        
        {
            Quaternion<float> x(-1.6, 3.1, -1.4, 2.7);
            EXPECT_NEAR(normSq(x), 21.42, 1e-6);
        }
        
        {
            Quaternion<float> x;
            EXPECT_FLOAT_EQ(normSq(x), 0.0);
        }
    }

    {
        printSection(testName, "norm(const Quaternion<T>& q)");
        
        {
            Quaternion<float> x(-1.6, 3.1, -1.4, 2.7);
            EXPECT_NEAR(norm(x), 4.6282, 1e-4);
        }
        
        {
            Quaternion<float> x;
            EXPECT_FLOAT_EQ(norm(x), 0.0);
        }
    }
}
