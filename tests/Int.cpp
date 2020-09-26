#include "main.h"

namespace
{
    std::string testConstructor(Test& test)
    {
        test.addSubTest("Int::Int()", [](Test& test)->std::string
        {
            std::string error;

            Int x;
            if (x.toString() != "0")
                error += "Expected result: 0. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("Int::Int(int64_t x)", [](Test& test)->std::string
        {
            test.addSubTest("x = 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0);
                if (x.toString() != "0")
                    error += "Expected result: 0. Returned result: " + x.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("x > 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989);
                if (x.toString() != "161803398874989")
                    error += "Expected result: 161803398874989. Returned result: " + x.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("x < 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989);
                if (x.toString() != "-161803398874989")
                    error += "Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
                
                return error;
            });

            return "";
        });

        test.addSubTest("Int::Int(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926535), y(x);
            if (y.toString() != "31415926535")
                error += "Expected result: 31415926535. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("Int::Int(Int&& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926535), y(std::move(x));
            if (y.toString() != "31415926535")
                error += "Expected result: 31415926535. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        return "";
    }

    std::string testAssignment(Test& test)
    {
        test.addSubTest("Int::operator=(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-161803398874989), y;
            y = x;
            if (y.toString() != "-161803398874989")
                error += "Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("Int::operator=(Int&& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-161803398874989), y;
            y = std::move(x);
            if (y.toString() != "-161803398874989")
                error += "Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("Bonus tests", [](Test& test)->std::string
        {
            test.addSubTest("Chained copy assignement", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y, z, t;
                t = z = y = x;
                if (x.toString() != "-161803398874989")
                    error += "#1 - Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
                if (y.toString() != "-161803398874989")
                    error += "#2 - Expected result: -161803398874989. Returned result: " + y.toString() + ".\n";
                if (z.toString() != "-161803398874989")
                    error += "#3 - Expected result: -161803398874989. Returned result: " + z.toString() + ".\n";
                if (t.toString() != "-161803398874989")
                    error += "#4 - Expected result: -161803398874989. Returned result: " + t.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Chained copy and move assignement", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y, z, t;
                t = std::move(z = y = x);
                if (x.toString() != "-161803398874989")
                    error += "#1 - Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
                if (y.toString() != "-161803398874989")
                    error += "#2 - Expected result: -161803398874989. Returned result: " + y.toString() + ".\n";
                if (t.toString() != "-161803398874989")
                    error += "#3 - Expected result: -161803398874989. Returned result: " + t.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Assignment by an int64_t directly", [](Test& test)->std::string
            {
                std::string error;

                Int x;
                x = -161803398874989;
                if (x.toString() != "-161803398874989")
                    error += "Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
                
                return error;
            });

            return "";
        });

        return "";
    }

    std::string testDestructor(Test& test)
    {
        test.addSubTest("Destructor on a simple integer", [](Test& test)->std::string
        {
            Int* x(new Int(161803398874989));
            delete x;
            return "";
        });

        test.addSubTest("Destructor on an integer created by copy", [](Test& test)->std::string
        {
            Int* x(new Int(161803398874989)), *y(new Int(*x));
            delete x;
            delete y;
            return "";
        });

        test.addSubTest("Destructor on an integer created by move constructor", [](Test& test)->std::string
        {
            Int* x(new Int(161803398874989)), *y(new Int(std::move(*x)));
            delete x;
            delete y;
            return "";
        });

        return "";
    }

    std::string testAddition(Test& test)
    {
        test.addSubTest("Int::operator+=(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-16180339887);
            x += y;
            if (x.toString() != "15235586649")
                error += "Expected result: 15235586649. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator+(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-16180339887), z;
            z = x + y;
            if (z.toString() != "15235586649")
                error += "Expected result: 15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator+(Int&& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-16180339887), z;
            z = std::move(x) + y;
            if (z.toString() != "15235586649")
                error += "Expected result: 15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator+(const Int& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-16180339887), z;
            z = x + std::move(y);
            if (z.toString() != "15235586649")
                error += "Expected result: 15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator+(Int&& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-16180339887), z;
            z = std::move(x) + std::move(y);
            if (z.toString() != "15235586649")
                error += "Expected result: 15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        return "";
    }

    std::string testSubstraction(Test& test)
    {
        test.addSubTest("Int::operator-=(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-31415926536), y(-16180339887);
            x -= y;
            if (x.toString() != "-15235586649")
                error += "Expected result: -15235586649. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator-(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-31415926536), y(-16180339887), z;
            z = x - y;
            if (z.toString() != "-15235586649")
                error += "Expected result: -15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator-(Int&& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-31415926536), y(-16180339887), z;
            z = std::move(x) - y;
            if (z.toString() != "-15235586649")
                error += "Expected result: -15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator-(const Int& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-31415926536), y(-16180339887), z;
            z = x - std::move(y);
            if (z.toString() != "-15235586649")
                error += "Expected result: -15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });
        
        test.addSubTest("operator-(Int&& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(-31415926536), y(-16180339887), z;
            z = std::move(x) - std::move(y);
            if (z.toString() != "-15235586649")
                error += "Expected result: -15235586649. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        return "";
    }

    std::string testMultiplication(Test& test)
    {
        test.addSubTest("Int::operator*=(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31416), y(-1618);
            x *= y;
            if (x.toString() != "-50831088")
                error += "Expected result: -50831088. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator*(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31416), y(-1618), z;
            z = x * y;
            if (z.toString() != "-50831088")
                error += "Expected result: -50831088. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator*(Int&& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31416), y(-1618), z;
            z = std::move(x) * y;
            if (z.toString() != "-50831088")
                error += "Expected result: -50831088. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator*(const Int& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31416), y(-1618), z;
            z = x * std::move(y);
            if (z.toString() != "-50831088")
                error += "Expected result: -50831088. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator*(Int&& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31416), y(-1618), z;
            z = std::move(x) * std::move(y);
            if (z.toString() != "-50831088")
                error += "Expected result: -50831088. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        return "";
    }

    std::string testDivision(Test& test)
    {
        test.addSubTest("Int::operator/=(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618);
            x /= y;
            if (x.toString() != "-19416518")
                error += "Expected result: -19416518. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator/(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618), z;
            z = x / y;
            if (z.toString() != "-19416518")
                error += "Expected result: -19416518. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator/(Int&& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618), z;
            z = std::move(x) / y;
            if (z.toString() != "-19416518")
                error += "Expected result: -19416518. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator/(Int&& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618), z;
            z = std::move(x) / std::move(y);
            if (z.toString() != "-19416518")
                error += "Expected result: -19416518. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("Bonus tests", [](Test& test)->std::string
        {
            test.addSubTest("Division by 0", [](Test& test)->std::string
            {
                std::string error;

                try
                {
                    Int x(31415926536);
                    x /= 0;
                    error += "The division by 0 worked. Obtained value: " + x.toString() + ".";
                }
                catch (std::runtime_error& e)
                {
                }

                return error;
            });

            return "";
        });

        return "";
    }

    std::string testModulo(Test& test)
    {
        test.addSubTest("Int::operator%=(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618);
            x %= y;
            if (x.toString() != "412")
                error += "Expected result: 412. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator%(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618), z;
            z = x % y;
            if (z.toString() != "412")
                error += "Expected result: 412. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator%(Int&& x, const Int& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618), z;
            z = std::move(x) % y;
            if (z.toString() != "412")
                error += "Expected result: 412. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator%(Int&& x, Int&& y)", [](Test& test)->std::string
        {
            std::string error;

            Int x(31415926536), y(-1618), z;
            z = std::move(x) % std::move(y);
            if (z.toString() != "412")
                error += "Expected result: 412. Returned result: " + z.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("Bonus tests", [](Test& test)->std::string
        {
            test.addSubTest("Modulo by zero", [](Test& test)->std::string
            {
                std::string error;

                try
                {
                    Int x(31415926536);
                    x %= 0;
                    error += "The modulo by 0 worked. Obtained value: " + x.toString() + ".";
                }
                catch (std::runtime_error& e)
                {
                }

                return error;
            });
        
            return "";
        });

        return "";
    }

    std::string testUnary(Test& test)
    {
        test.addSubTest("operator-(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(161803398874989), y;
            y = -x;
            if (y.toString() != "-161803398874989")
                error += "Expected result: -161803398874989. Returned result: " + y.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator+(const Int& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(161803398874989), y;
            y = +x;
            if (y.toString() != "161803398874989")
                error += "Expected result: 161803398874989. Returned result: " + y.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator-(Int&& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(161803398874989), y;
            y = -std::move(x);
            if (y.toString() != "-161803398874989")
                error += "Expected result: -161803398874989. Returned result: " + y.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("operator+(Int&& x)", [](Test& test)->std::string
        {
            std::string error;

            Int x(161803398874989), y;
            y = +std::move(x);
            if (y.toString() != "161803398874989")
                error += "Expected result: 161803398874989. Returned result: " + y.toString() + ".\n";
            
            return error;
        });

        return "";
    }

    std::string testToInt(Test& test)
    {
        test.addSubTest("x > 0", [](Test& test)->std::string
        {
            std::string error;

            Int x(161803398874989);
            if (x.toInt() != 161803398874989)
                error += "Expected result: 161803398874989. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("x < 0", [](Test& test)->std::string
        {
            std::string error;

            Int x(-161803398874989);
            if (x.toInt() != -161803398874989)
                error += "Expected result: -161803398874989. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("x = 0", [](Test& test)->std::string
        {
            std::string error;

            Int x(0);
            if (x.toInt() != 0)
                error += "Expected result: 0. Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("x = INT64_MAX", [](Test& test)->std::string
        {
            std::string error;

            Int x(INT64_MAX);
            if (x.toInt() != INT64_MAX)
                error += "Expected result: " + std::to_string(INT64_MAX) + ". Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("x = INT64_MIN", [](Test& test)->std::string
        {
            std::string error;

            Int x(INT64_MIN);
            if (x.toInt() != INT64_MIN)
                error += "Expected result: " + std::to_string(INT64_MIN) + ". Returned result: " + x.toString() + ".\n";
            
            return error;
        });

        test.addSubTest("x = INT64_MAX + 1", [](Test& test)->std::string
        {
            std::string error;

            Int x(INT64_MAX);
            x += 1;
            try
            {
                x.toInt();
                error += "The Int has been converted into int64_t. Obtained value: " + std::to_string(x.toInt()) + ".";
            }
            catch (std::runtime_error& e)
            {
            }

            return error;
        });

        test.addSubTest("x = INT64_MIN - 1", [](Test& test)->std::string
        {
            std::string error;

            Int x(INT64_MIN);
            x -= 1;
            try
            {
                x.toInt();
                error += "The Int has been converted into int64_t. Obtained value: " + std::to_string(x.toInt()) + ".";
            }
            catch (std::runtime_error& e)
            {
            }

            return error;
        });

        test.addSubTest("x > INT64_MAX", [](Test& test)->std::string
        {
            std::string error;

            Int x(INT64_MAX);
            x = (x + 2) * (x + 5) * (x + 12);
            try
            {
                x.toInt();
                error += "The Int has been converted into int64_t. Obtained value: " + std::to_string(x.toInt()) + ".";
            }
            catch (std::runtime_error& e)
            {
            }

            return error;
        });

        test.addSubTest("x < INT64_MIN", [](Test& test)->std::string
        {
            std::string error;

            Int x(INT64_MIN);
            x = (x + 2) * (x + 5) * (x + 12);
            try
            {
                x.toInt();
                error += "The Int has been converted into int64_t. Obtained value: " + std::to_string(x.toInt()) + ".";
            }
            catch (std::runtime_error& e)
            {
            }

            return error;
        });

        return "";
    }

    std::string testComparators(Test& test)
    {
        test.addSubTest("operator==(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            test.addSubTest("Equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(161803398874989);
                if (!(x == y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                x = (x + 3 % 50) * (x + 10) * (x - 12) * x / 7;
                y = (y + 3 % 50) * (y + 10) * (y - 12) * y / 7;
                if (!(x == y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Different integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(-31415926);
                if (x == y)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = 161803398874989;
                y = -161803398874989;
                if (x == y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                x = ((uint64_t) UINT32_MAX) + 1;
                y = 0;
                if (x == y)
                    error += "#3 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Comparisons to 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0), y(-x);
                if (!(x == y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                y = x - x;
                x -= x;
                if (!(x == y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                x -= x;
                y = 0;
                if (!(x == y))
                    error += "#3 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            return "";
        });

        test.addSubTest("operator!=(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            test.addSubTest("Equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(161803398874989);
                if (x != y)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                x = (x + 3 % 50) * (x + 10) * (x - 12) * x / 7;
                y = (y + 3 % 50) * (y + 10) * (y - 12) * y / 7;
                if (x != y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Different integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(-31415926);
                if (!(x != y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = 161803398874989;
                y = -161803398874989;
                if (!(x != y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                x = ((uint64_t) UINT32_MAX) + 1;
                y = 0;
                if (!(x != y))
                    error += "#3 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Comparisons to 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0), y(-x);
                if (x != y)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                y = x - x;
                x -= x;
                if (x != y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                x -= x;
                y = 0;
                if (x != y)
                    error += "#3 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            return "";
        });

        test.addSubTest("operator>(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            test.addSubTest("Different integers, same signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(31415926536);
                if (!(x > y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (y > x)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Different integers, different signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(31415926536);
                if (!(y > x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x > y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Positive equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(161803398874989);
                if (y > x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x > y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Negative equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(-161803398874989);
                if (y > x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x > y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Comparisons to 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0), y(-x);
                if (y > x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x > y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                y = x - x;
                x -= x;
                if (y > x)
                    error += "#3 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x > y)
                    error += "#4 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                x -= x;
                y = 0;
                if (y > x)
                    error += "#5 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x > y)
                    error += "#6 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            return "";
        });

        test.addSubTest("operator<(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            test.addSubTest("Different integers, same signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(31415926536);
                if (x < y)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(y < x))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Different integers, different signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(31415926536);
                if (y < x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x < y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Positive equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(161803398874989);
                if (y < x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x < y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Negative equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(-161803398874989);
                if (y < x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x < y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Comparisons to 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0), y(-x);
                if (y < x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x < y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                y = x - x;
                x -= x;
                if (y < x)
                    error += "#3 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x < y)
                    error += "#4 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                x -= x;
                y = 0;
                if (y < x)
                    error += "#5 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x < y)
                    error += "#6 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            return "";
        });

        test.addSubTest("operator>=(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            test.addSubTest("Different integers, same signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(31415926536);
                if (!(x >= y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (y >= x)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Different integers, different signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(31415926536);
                if (!(y >= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (x >= y)
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Positive equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(161803398874989);
                if (!(y >= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x >= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Negative equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(-161803398874989);
                if (!(y >= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x >= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Comparisons to 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0), y(-x);
                if (!(y >= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x >= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                y = x - x;
                x -= x;
                if (!(y >= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x >= y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                x -= x;
                y = 0;
                if (!(y >= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x >= y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            return "";
        });

        test.addSubTest("operator<=(const Int& x, const Int& y)", [](Test& test)->std::string
        {
            test.addSubTest("Different integers, same signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(31415926536);
                if (x <= y)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(y <= x))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Different integers, different signs", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(31415926536);
                if (y <= x)
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x <= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            test.addSubTest("Positive equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(161803398874989), y(161803398874989);
                if (!(y <= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x <= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Negative equal integers", [](Test& test)->std::string
            {
                std::string error;

                Int x(-161803398874989), y(-161803398874989);
                if (!(y <= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x <= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";
                
                return error;
            });

            test.addSubTest("Comparisons to 0", [](Test& test)->std::string
            {
                std::string error;

                Int x(0), y(-x);
                if (!(y <= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x <= y))
                    error += "#2 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                y = x - x;
                x -= x;
                if (!(y <= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x <= y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                x = -161803398874989;
                x -= x;
                y = 0;
                if (!(y <= x))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                if (!(x <= y))
                    error += "#1 - Unexpected result. x: " + x.toString() + ", y: " + y.toString() + ".\n";

                return error;
            });

            return "";
        });

        return "";
    }

    std::string testStream(Test& test)
    {
        test.addSubTest("operator<<(std::ostream& stream, const Int& x)", [](Test& test)->std::string
        {
            return "Test needs to be implemented.";
        });

        test.addSubTest("operator>>(std::ostream& stream, const Int& x)", [](Test& test)->std::string
        {
            return "Test needs to be implemented.";
        });

        return "";
    }

    std::string bonusTests(Test& test)
    {
        test.addSubTest("Factorial round-trip", [](Test& test)->std::string
        {
            std::string error;

            Int x(1);
            for (int i(1); i < 100; i++)
                x *= i;

            for (int i(99); i > 0; i--)
                x /= i;

            if (x != 1)
                error += "Expected result: 1. Returned result: " + x.toString() + ".\n";

            return error;
        });

        return "";
    }
}

std::string mainInt(Test& test)
{
    test.addSubTest("Constructors", &testConstructor);
    test.addSubTest("Assignment operators", &testAssignment);
    test.addSubTest("Destructor", &testDestructor);

    test.addSubTest("Addition operators", &testAddition);
    test.addSubTest("Substraction operators", &testSubstraction);
    test.addSubTest("Multiplication operators", &testMultiplication);
    test.addSubTest("Division operators", &testDivision);
    test.addSubTest("Modulo operators", &testModulo);
    test.addSubTest("Unary operators", &testUnary);

    test.addSubTest("Int::toInt()", &testToInt);

    test.addSubTest("Comparators", &testComparators);

    test.addSubTest("Stream operators", &testStream);

    test.addSubTest("Bonus tests", &bonusTests);

    return "";
}
