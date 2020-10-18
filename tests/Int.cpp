#include "main.hpp"


TEST(ClassInt, Constructors)
{
    std::string testName("ClassInt.Constructors");

    {
        printSection(testName, "Int::Int()");

        Int x;
        EXPECT_EQ(x.toInt(), 0);
    }
    
    {
        printSection(testName, "Int::Int(int64_t x)");

        Int x(0);
        EXPECT_EQ(x.toInt(), 0);

        Int y(161803398874989);
        EXPECT_EQ(y.toInt(), 161803398874989);

        Int z(-161803398874989);
        EXPECT_EQ(z.toInt(), -161803398874989);
    }
    
    {
        printSection(testName, "Int::Int(const Int& x)");

        Int x(31415926535), y(x);
        EXPECT_EQ(x.toInt(), 31415926535);
        EXPECT_EQ(y.toInt(), 31415926535);
    }
    
    {
        printSection(testName, "Int::Int(Int&& x)");

        Int x(31415926535), y(std::move(x));
        EXPECT_EQ(y.toInt(), 31415926535);
    }
}

TEST(ClassInt, AssignmentOperators)
{
    std::string testName("ClassInt.AssignmentOperators");

    {
        printSection(testName, "Int::operator=(const Int& x)");

        Int x(-161803398874989), y;
        y = x;
        EXPECT_EQ(x.toInt(), -161803398874989);
        EXPECT_EQ(y.toInt(), -161803398874989);
    }

    {
        printSection(testName, "Int::operator=(Int&& x)");

        Int x(-161803398874989), y;
        y = std::move(x);
        EXPECT_EQ(y.toInt(), -161803398874989);
    }

    {
        printSection(testName, "Bonus tests");

        {
            Int x(-161803398874989), y, z, t;
            t = z = y = x;
            EXPECT_EQ(x.toInt(), -161803398874989);
            EXPECT_EQ(y.toInt(), -161803398874989);
            EXPECT_EQ(z.toInt(), -161803398874989);
            EXPECT_EQ(t.toInt(), -161803398874989);
        }

        {
            Int x(-161803398874989), y, z, t;
            t = std::move(z = y = x);
            EXPECT_EQ(x.toInt(), -161803398874989);
            EXPECT_EQ(y.toInt(), -161803398874989);
            EXPECT_EQ(t.toInt(), -161803398874989);
        }

        {
            Int x;
            x = -161803398874989;
            EXPECT_EQ(x.toInt(), -161803398874989);
        }
    }
}

TEST(ClassInt, Destructor)
{
    std::string testName("ClassInt.Destructor");

    {
        printSection(testName, "Destructor on a simple integer");

        Int* x(new Int(161803398874989));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on an integer created by copy");

        Int* x(new Int(161803398874989)), *y(new Int(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on an integer created by move constructor");

        Int* x(new Int(161803398874989)), *y(new Int(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassInt, AdditionOperators)
{
    std::string testName("ClassInt.AdditionOperators");

    {
        printSection(testName, "Int::operator+=(const Int& x)");

        Int x(31415926536), y(-16180339887);
        x += y;
        EXPECT_EQ(x.toInt(), 15235586649);
    }

    {
        printSection(testName, "operator+(const Int& x, const Int& y)");

        Int x(31415926536), y(-16180339887), z;
        z = x + y;
        EXPECT_EQ(z.toInt(), 15235586649);
    }

    {
        printSection(testName, "operator+(Int&& x, const Int& y)");

        Int x(31415926536), y(-16180339887), z;
        z = std::move(x) + y;
        EXPECT_EQ(z.toInt(), 15235586649);
    }

    {
        printSection(testName, "operator+(const Int& x, Int&& y)");

        Int x(31415926536), y(-16180339887), z;
        z = x + std::move(y);
        EXPECT_EQ(z.toInt(), 15235586649);
    }

    {
        printSection(testName, "operator+(Int&& x, Int&& y)");

        Int x(31415926536), y(-16180339887), z;
        z = std::move(x) + std::move(y);
        EXPECT_EQ(z.toInt(), 15235586649);
    }
}

TEST(ClassInt, SubstractionOperators)
{
    std::string testName("ClassInt.SubstractionOperators");

    {
        printSection(testName, "Int::operator-=(const Int& x)");

        Int x(-31415926536), y(-16180339887);
        x -= y;
        EXPECT_EQ(x.toInt(), -15235586649);
    }

    {
        printSection(testName, "operator-(const Int& x, const Int& y)");

        Int x(-31415926536), y(-16180339887), z;
        z = x - y;
        EXPECT_EQ(z.toInt(), -15235586649);
    }

    {
        printSection(testName, "operator-(Int&& x, const Int& y)");

        Int x(-31415926536), y(-16180339887), z;
        z = std::move(x) - y;
        EXPECT_EQ(z.toInt(), -15235586649);
    }

    {
        printSection(testName, "operator-(const Int& x, Int&& y)");

        Int x(-31415926536), y(-16180339887), z;
        z = x - std::move(y);
        EXPECT_EQ(z.toInt(), -15235586649);
    }

    {
        printSection(testName, "operator-(Int&& x, Int&& y)");

        Int x(-31415926536), y(-16180339887), z;
        z = std::move(x) - std::move(y);
        EXPECT_EQ(z.toInt(), -15235586649);
    }
}

TEST(ClassInt, MultiplicationOperators)
{
    std::string testName("ClassInt.MultiplicationOperators");

    {
        printSection(testName, "Int::operator*=(const Int& x)");

        Int x(31416), y(-1618);
        x *= y;
        EXPECT_EQ(x.toInt(), -50831088);
    }

    {
        printSection(testName, "operator*(const Int& x, const Int& y)");

        Int x(31416), y(-1618), z;
        z = x * y;
        EXPECT_EQ(z.toInt(), -50831088);
    }

    {
        printSection(testName, "operator*(Int&& x, const Int& y)");

        Int x(31416), y(-1618), z;
        z = std::move(x) * y;
        EXPECT_EQ(z.toInt(), -50831088);
    }

    {
        printSection(testName, "operator*(const Int& x, Int&& y)");

        Int x(31416), y(-1618), z;
        z = x * std::move(y);
        EXPECT_EQ(z.toInt(), -50831088);
    }

    {
        printSection(testName, "operator*(Int&& x, Int&& y)");

        Int x(31416), y(-1618), z;
        z = std::move(x) * std::move(y);
        EXPECT_EQ(z.toInt(), -50831088);
    }
}

TEST(ClassInt, DivisionOperators)
{
    std::string testName("ClassInt.DivisionOperators");

    {
        printSection(testName, "Int::operator/=(const Int& x)");

        Int x(31415926536), y(-1618);
        x /= y;
        EXPECT_EQ(x.toInt(), -19416518);
    }

    {
        printSection(testName, "operator/(const Int& x, const Int& y)");

        Int x(31415926536), y(-1618), z;
        z = x / y;
        EXPECT_EQ(z.toInt(), -19416518);
    }

    {
        printSection(testName, "operator/(Int&& x, const Int& y)");

        Int x(31415926536), y(-1618), z;
        z = std::move(x) / y;
        EXPECT_EQ(z.toInt(), -19416518);
    }

    {
        printSection(testName, "operator/(Int&& x, Int&& y)");

        Int x(31415926536), y(-1618), z;
        z = std::move(x) / std::move(y);
        EXPECT_EQ(z.toInt(), -19416518);
    }
}

TEST(ClassInt, ModuloOperators)
{
    std::string testName("ClassInt.ModuloOperators");

    {
        printSection(testName, "Int::operator%=(const Int& x)");

        Int x(31415926536), y(-1618);
        x %= y;
        EXPECT_EQ(x.toInt(), 412);
    }

    {
        printSection(testName, "operator%(const Int& x, const Int& y)");

        Int x(31415926536), y(-1618), z;
        z = x % y;
        EXPECT_EQ(z.toInt(), 412);
    }

    {
        printSection(testName, "operator%(Int&& x, const Int& y)");

        Int x(31415926536), y(-1618), z;
        z = std::move(x) % y;
        EXPECT_EQ(z.toInt(), 412);
    }

    {
        printSection(testName, "operator%(Int&& x, Int&& y)");

        Int x(31415926536), y(-1618), z;
        z = std::move(x) % std::move(y);
        EXPECT_EQ(z.toInt(), 412);
    }
}

TEST(ClassInt, UnaryOperators)
{
    std::string testName("ClassInt.UnaryOperators");

    {
        printSection(testName, "operator-(const Int& x)");

        Int x(161803398874989), y;
        y = -x;
        EXPECT_EQ(x.toInt(), 161803398874989);
        EXPECT_EQ(y.toInt(), -161803398874989);
    }

    {
        printSection(testName, "operator+(const Int& x)");

        Int x(161803398874989), y;
        y = +x;
        EXPECT_EQ(x.toInt(), 161803398874989);
        EXPECT_EQ(y.toInt(), 161803398874989);
    }

    {
        printSection(testName, "operator-(Int&& x)");

        Int x(161803398874989), y;
        y = -std::move(x);
        EXPECT_EQ(y.toInt(), -161803398874989);
    }

    {
        printSection(testName, "operator+(Int&& x)");

        Int x(161803398874989), y;
        y = +std::move(x);
        EXPECT_EQ(y.toInt(), 161803398874989);
    }
}

TEST(ClassInt, Comparators)
{
    std::string testName("ClassInt.Comparators");

    {
        printSection(testName, "operator==(const Int& x, const Int& y)");

        {
            Int x(161803398874989), y(161803398874989);
            EXPECT_EQ(x == y, true);
        
            x = (x + 3 % 50) * (x + 10) * (x - 12) * x / 7;
            y = (y + 3 % 50) * (y + 10) * (y - 12) * y / 7;
            EXPECT_EQ(x == y, true);
        }

        {
            Int x(161803398874989), y(-31415926);
            EXPECT_EQ(x == y, false);

            x = 161803398874989;
            y = -161803398874989;
            EXPECT_EQ(x == y, false);
        
            x = ((uint64_t) UINT32_MAX) + 1;
            y = 0;
            EXPECT_EQ(x == y, false);
        }

        {
            Int x(0), y(-x);
            EXPECT_EQ(x == y, true);

            x = -161803398874989;
            y = x - x;
            x -= x;
            EXPECT_EQ(x == y, true);

            x = -161803398874989;
            x -= x;
            y = 0;
            EXPECT_EQ(x == y, true);
        }
    }

    {
        printSection(testName, "operator!=(const Int& x, const Int& y)");

        {
            Int x(161803398874989), y(161803398874989);
            EXPECT_EQ(x != y, false);
        
            x = (x + 3 % 50) * (x + 10) * (x - 12) * x / 7;
            y = (y + 3 % 50) * (y + 10) * (y - 12) * y / 7;
            EXPECT_EQ(x != y, false);
        }

        {
            Int x(161803398874989), y(-31415926);
            EXPECT_EQ(x != y, true);

            x = 161803398874989;
            y = -161803398874989;
            EXPECT_EQ(x != y, true);
        
            x = ((uint64_t) UINT32_MAX) + 1;
            y = 0;
            EXPECT_EQ(x != y, true);
        }

        {
            Int x(0), y(-x);
            EXPECT_EQ(x != y, false);

            x = -161803398874989;
            y = x - x;
            x -= x;
            EXPECT_EQ(x != y, false);

            x = -161803398874989;
            x -= x;
            y = 0;
            EXPECT_EQ(x != y, false);
        }
    }

    {
        printSection(testName, "operator>(const Int& x, const Int& y)");

        {
            Int x(161803398874989), y(31415926536);
            EXPECT_EQ(x > y, true);
            EXPECT_EQ(y > x, false);
        }

        {
            Int x(-161803398874989), y(31415926536);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, true);
        }

        {
           Int x(161803398874989), y(161803398874989);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);
        }

        {
           Int x(-161803398874989), y(-161803398874989);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);
        }

        {
            Int x(0), y(-x);
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);

            x = -161803398874989;
            y = x - x;
            x -= x;
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);

            x = -161803398874989;
            x -= x;
            y = 0;
            EXPECT_EQ(x > y, false);
            EXPECT_EQ(y > x, false);
        }
    }

    {
        printSection(testName, "operator<(const Int& x, const Int& y)");

        {
            Int x(161803398874989), y(31415926536);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, true);
        }

        {
            Int x(-161803398874989), y(31415926536);
            EXPECT_EQ(x < y, true);
            EXPECT_EQ(y < x, false);
        }

        {
           Int x(161803398874989), y(161803398874989);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);
        }

        {
           Int x(-161803398874989), y(-161803398874989);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);
        }

        {
            Int x(0), y(-x);
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);

            x = -161803398874989;
            y = x - x;
            x -= x;
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);

            x = -161803398874989;
            x -= x;
            y = 0;
            EXPECT_EQ(x < y, false);
            EXPECT_EQ(y < x, false);
        }
    }

    {
        printSection(testName, "operator>=(const Int& x, const Int& y)");

        {
            Int x(161803398874989), y(31415926536);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, false);
        }

        {
            Int x(-161803398874989), y(31415926536);
            EXPECT_EQ(x >= y, false);
            EXPECT_EQ(y >= x, true);
        }

        {
           Int x(161803398874989), y(161803398874989);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);
        }

        {
           Int x(-161803398874989), y(-161803398874989);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);
        }

        {
            Int x(0), y(-x);
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);

            x = -161803398874989;
            y = x - x;
            x -= x;
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);

            x = -161803398874989;
            x -= x;
            y = 0;
            EXPECT_EQ(x >= y, true);
            EXPECT_EQ(y >= x, true);
        }
    }

    {
        printSection(testName, "operator<=(const Int& x, const Int& y)");

        {
            Int x(161803398874989), y(31415926536);
            EXPECT_EQ(x <= y, false);
            EXPECT_EQ(y <= x, true);
        }

        {
            Int x(-161803398874989), y(31415926536);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, false);
        }

        {
           Int x(161803398874989), y(161803398874989);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);
        }

        {
           Int x(-161803398874989), y(-161803398874989);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);
        }

        {
            Int x(0), y(-x);
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);

            x = -161803398874989;
            y = x - x;
            x -= x;
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);

            x = -161803398874989;
            x -= x;
            y = 0;
            EXPECT_EQ(x <= y, true);
            EXPECT_EQ(y <= x, true);
        }
    }
}

TEST(ClassInt, StreamOperators)
{
    std::string testName("ClassInt.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Int& x)");

        {
            Int x(161803398874989);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "161803398874989");
        }

        {
            Int x(-161803398874989);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "-161803398874989");
        }

        {
            Int x(0);
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "0");
        }
    }

    {
        printSection(testName, "operator>>(std::ostream& stream, const Int& x)");

        {
            Int x;
            std::stringstream stream;
            stream << "161803398874989";
            stream >> x;
            EXPECT_EQ(x.toInt(), 161803398874989);
        }

        {
            Int x;
            std::stringstream stream;
            stream << "-161803398874989";
            stream >> x;
            EXPECT_EQ(x.toInt(), -161803398874989);
        }

        {
            Int x(1618);
            std::stringstream stream;
            stream << "0";
            stream >> x;
            EXPECT_EQ(x.toInt(), 0);
        }
    }
}

TEST(ClassInt, SpecificMethods)
{
    std::string testName("ClassInt.SpecificMethods");

    {
        printSection(testName, "Int::toString()");

        Int x(161803398874989);
        EXPECT_EQ(x.toString(), "161803398874989");

        Int y(-161803398874989);
        EXPECT_EQ(y.toString(), "-161803398874989");

        Int z(0);
        EXPECT_EQ(z.toString(), "0");
    }

    {
        printSection(testName, "Int::toInt()");

        Int a(161803398874989);
        EXPECT_EQ(a.toInt(), 161803398874989);

        Int b(-161803398874989);
        EXPECT_EQ(b.toInt(), -161803398874989);

        Int c(0);
        EXPECT_EQ(c.toInt(), 0);

        Int d(INT64_MAX);
        EXPECT_EQ(d.toInt(), INT64_MAX);

        Int e(INT64_MIN);
        EXPECT_EQ(e.toInt(), INT64_MIN);

        Int f(INT64_MAX);
        f += 1;
        EXPECT_THROW(f.toInt(), std::runtime_error);

        Int g(INT64_MIN);
        g -= 1;
        EXPECT_THROW(g.toInt(), std::runtime_error);

        Int h(INT64_MAX);
        h = (h + 2) * (h + 5) * (h + 12);
        EXPECT_THROW(h.toInt(), std::runtime_error);

        Int i(INT64_MIN);
        i = (i - 2) * (i - 5) * (i - 12);
        EXPECT_THROW(i.toInt(), std::runtime_error);
    }

    {
        printSection(testName, "Int::setSign(bool sign)");

        Int x(161803398874989);
        EXPECT_EQ(x.toInt(), 161803398874989);

        x.setSign(false);
        EXPECT_EQ(x.toInt(), -161803398874989);

        Int y(0);
        EXPECT_EQ(y.toString(), "0");

        y.setSign(false);
        EXPECT_EQ(y.toString(), "0");
    }

    {
        printSection(testName, "Int::getSign()");

        Int x(161803398874989);
        EXPECT_EQ(x.getSign(), true);

        Int y(-161803398874989);
        EXPECT_EQ(y.getSign(), false);

        Int z(0);
        EXPECT_EQ(z.getSign(), true);
    }
}

TEST(ClassInt, SpecificFunctions)
{
    std::string testName("ClassInt.SpecificFunctions");

    {
        printSection(testName, "Int binom(const Int& n, const Int& p)");

        EXPECT_EQ(binom(50, 42).toInt(), 536878650);
        EXPECT_EQ(binom(50, 0).toInt(), 1);
        EXPECT_EQ(binom(0, 0).toInt(), 1);
        EXPECT_EQ(binom(50, 100).toInt(), 0);
        EXPECT_EQ(binom(50, -10).toInt(), 0);
        EXPECT_EQ(binom(-50, -10).toInt(), 0);
    }
}

TEST(ClassInt, BonusTests)
{
    std::string testName("ClassInt.BonusTests");

    {
        printSection(testName, "Factorial round-trip");
        
        Int x(1);
        for (int i(1); i < 100; i++)
            x *= i;
        for (int i(99); i > 2; i--)
            x /= i;

        EXPECT_EQ(x, 2);
    }
}
