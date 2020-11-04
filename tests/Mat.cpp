#include "main.hpp"


TEST(ClassMat, Constructors)
{
    std::string testName("ClassMat.Constructors");

    {
        printSection(testName, "Mat<T, m, n>::Mat()");

        {
            Mat<float, 0> x;
        }

        {
            Mat<float, 3, 2> x;
            EXPECT_FLOAT_EQ(x[0][0], 0.f); EXPECT_FLOAT_EQ(x[0][1], 0.f);
            EXPECT_FLOAT_EQ(x[1][0], 0.f); EXPECT_FLOAT_EQ(x[1][1], 0.f);
            EXPECT_FLOAT_EQ(x[2][0], 0.f); EXPECT_FLOAT_EQ(x[2][1], 0.f);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::Mat(int64_t x)");

        {
            Mat<float, 3, 2> x((int64_t) 1618);
            EXPECT_FLOAT_EQ(x[0][0], 1618.f); EXPECT_FLOAT_EQ(x[0][1], 0.f);
            EXPECT_FLOAT_EQ(x[1][0], 0.f);    EXPECT_FLOAT_EQ(x[1][1], 1618.f);
            EXPECT_FLOAT_EQ(x[2][0], 0.f);    EXPECT_FLOAT_EQ(x[2][1], 0.f);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::Mat(const T& x)");

        {
            Mat<float, 3, 2> x(1.618f);
            EXPECT_FLOAT_EQ(x[0][0], 1.618f); EXPECT_FLOAT_EQ(x[0][1], 0.f);
            EXPECT_FLOAT_EQ(x[1][0], 0.f);    EXPECT_FLOAT_EQ(x[1][1], 1.618f);
            EXPECT_FLOAT_EQ(x[2][0], 0.f);    EXPECT_FLOAT_EQ(x[2][1], 0.f);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::Mat(const std::vector<T>& diag)");

        {
            Mat<float, 3, 2> x(std::vector<float>({ 1.618f, 3.14f }));
            EXPECT_FLOAT_EQ(x[0][0], 1.618f); EXPECT_FLOAT_EQ(x[0][1], 0.f);
            EXPECT_FLOAT_EQ(x[1][0], 0.f);    EXPECT_FLOAT_EQ(x[1][1], 3.14f);
            EXPECT_FLOAT_EQ(x[2][0], 0.f);    EXPECT_FLOAT_EQ(x[2][1], 0.f);
        }

        {
            Mat<float, 3, 2> x;
            EXPECT_THROW(x = std::vector<float>({}) , std::runtime_error);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::Mat(const std::array<std::array<T, n>, m>& values)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });

            EXPECT_FLOAT_EQ(x[0][0], 1.6f); EXPECT_FLOAT_EQ(x[0][1], -1.8f);
            EXPECT_FLOAT_EQ(x[1][0], 0.3f); EXPECT_FLOAT_EQ(x[1][1], 3.9f);
            EXPECT_FLOAT_EQ(x[2][0], 8.8f); EXPECT_FLOAT_EQ(x[2][1], -7.4f);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::Mat(const Mat<T, m, n>& x)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y(x);

            EXPECT_FLOAT_EQ(x[0][0], 1.6f); EXPECT_FLOAT_EQ(x[0][1], -1.8f);
            EXPECT_FLOAT_EQ(x[1][0], 0.3f); EXPECT_FLOAT_EQ(x[1][1], 3.9f);
            EXPECT_FLOAT_EQ(x[2][0], 8.8f); EXPECT_FLOAT_EQ(x[2][1], -7.4f);

            EXPECT_FLOAT_EQ(y[0][0], 1.6f); EXPECT_FLOAT_EQ(y[0][1], -1.8f);
            EXPECT_FLOAT_EQ(y[1][0], 0.3f); EXPECT_FLOAT_EQ(y[1][1], 3.9f);
            EXPECT_FLOAT_EQ(y[2][0], 8.8f); EXPECT_FLOAT_EQ(y[2][1], -7.4f);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::Mat(Mat<T, m, n>&& x)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y(std::move(x));

            EXPECT_FLOAT_EQ(y[0][0], 1.6f); EXPECT_FLOAT_EQ(y[0][1], -1.8f);
            EXPECT_FLOAT_EQ(y[1][0], 0.3f); EXPECT_FLOAT_EQ(y[1][1], 3.9f);
            EXPECT_FLOAT_EQ(y[2][0], 8.8f); EXPECT_FLOAT_EQ(y[2][1], -7.4f);
        }
    }
}

TEST(ClassMat, AssignmentOperators)
{
    std::string testName("ClassMat.AssignmentOperators");

    {
        printSection(testName, "Mat<T, m, n>::operator=(const Mat<T, m, n>& x)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y;
            y = x;

            EXPECT_FLOAT_EQ(x[0][0], 1.6f); EXPECT_FLOAT_EQ(x[0][1], -1.8f);
            EXPECT_FLOAT_EQ(x[1][0], 0.3f); EXPECT_FLOAT_EQ(x[1][1], 3.9f);
            EXPECT_FLOAT_EQ(x[2][0], 8.8f); EXPECT_FLOAT_EQ(x[2][1], -7.4f);

            EXPECT_FLOAT_EQ(y[0][0], 1.6f); EXPECT_FLOAT_EQ(y[0][1], -1.8f);
            EXPECT_FLOAT_EQ(y[1][0], 0.3f); EXPECT_FLOAT_EQ(y[1][1], 3.9f);
            EXPECT_FLOAT_EQ(y[2][0], 8.8f); EXPECT_FLOAT_EQ(y[2][1], -7.4f);
        }
    }

    {
        printSection(testName, "Mat<T, m, n>::operator=(Mat<T, m, n>&& x)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y;
            y = std::move(x);

            EXPECT_FLOAT_EQ(y[0][0], 1.6f); EXPECT_FLOAT_EQ(y[0][1], -1.8f);
            EXPECT_FLOAT_EQ(y[1][0], 0.3f); EXPECT_FLOAT_EQ(y[1][1], 3.9f);
            EXPECT_FLOAT_EQ(y[2][0], 8.8f); EXPECT_FLOAT_EQ(y[2][1], -7.4f);
        }
    }
}

TEST(ClassMat, Destructor)
{
    std::string testName("ClassMat.Destructor");

    {
        printSection(testName, "Destructor on a simple matrix");

        Mat<float, 3, 2>* x(new Mat<float, 3, 2>({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } }));
        EXPECT_NO_THROW(delete x);
    }

    {
        printSection(testName, "Destructor on a matrix created by copy");

        Mat<float, 3, 2>* x(new Mat<float, 3, 2>({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } }));
        Mat<float, 3, 2>* y(new Mat<float, 3, 2>(*x));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }

    {
        printSection(testName, "Destructor on a matrix created by move constructor");

        Mat<float, 3, 2>* x(new Mat<float, 3, 2>({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } }));
        Mat<float, 3, 2>* y(new Mat<float, 3, 2>(std::move(*x)));
        EXPECT_NO_THROW(delete x);
        EXPECT_NO_THROW(delete y);
    }
}

TEST(ClassMat, AdditionOperators)
{
    std::string testName("ClassMat.AdditionOperators");

    {
        printSection(testName, "Mat<T, m, n>::operator+=(const Mat<T, m, n>& x)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        x += y;

        EXPECT_FLOAT_EQ(x[0][0], 4.7f);  EXPECT_FLOAT_EQ(x[0][1], 2.3f);
        EXPECT_FLOAT_EQ(x[1][0], 6.2f);  EXPECT_FLOAT_EQ(x[1][1], -1.7f);
        EXPECT_FLOAT_EQ(x[2][0], 14.1f); EXPECT_FLOAT_EQ(x[2][1], -1.5f);
    }

    {
        printSection(testName, "operator+(const Mat<T, m, n>& x, const Mat<T, m, n>& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = x + y;

        EXPECT_FLOAT_EQ(z[0][0], 4.7f);  EXPECT_FLOAT_EQ(z[0][1], 2.3f);
        EXPECT_FLOAT_EQ(z[1][0], 6.2f);  EXPECT_FLOAT_EQ(z[1][1], -1.7f);
        EXPECT_FLOAT_EQ(z[2][0], 14.1f); EXPECT_FLOAT_EQ(z[2][1], -1.5f);
    }

    {
        printSection(testName, "operator+(Mat<T, m, n>&& x, const Mat<T, m, n>& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = std::move(x) + y;

        EXPECT_FLOAT_EQ(z[0][0], 4.7f);  EXPECT_FLOAT_EQ(z[0][1], 2.3f);
        EXPECT_FLOAT_EQ(z[1][0], 6.2f);  EXPECT_FLOAT_EQ(z[1][1], -1.7f);
        EXPECT_FLOAT_EQ(z[2][0], 14.1f); EXPECT_FLOAT_EQ(z[2][1], -1.5f);
    }

    {
        printSection(testName, "operator+(const Mat<T, m, n>& x, Mat<T, m, n>&& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = x + std::move(y);

        EXPECT_FLOAT_EQ(z[0][0], 4.7f);  EXPECT_FLOAT_EQ(z[0][1], 2.3f);
        EXPECT_FLOAT_EQ(z[1][0], 6.2f);  EXPECT_FLOAT_EQ(z[1][1], -1.7f);
        EXPECT_FLOAT_EQ(z[2][0], 14.1f); EXPECT_FLOAT_EQ(z[2][1], -1.5f);
    }

    {
        printSection(testName, "operator+(Mat<T, m, n>&& x, Mat<T, m, n>&& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = std::move(x) + std::move(y);

        EXPECT_FLOAT_EQ(z[0][0], 4.7f);  EXPECT_FLOAT_EQ(z[0][1], 2.3f);
        EXPECT_FLOAT_EQ(z[1][0], 6.2f);  EXPECT_FLOAT_EQ(z[1][1], -1.7f);
        EXPECT_FLOAT_EQ(z[2][0], 14.1f); EXPECT_FLOAT_EQ(z[2][1], -1.5f);
    }
}

TEST(ClassMat, SubstractionOperators)
{
    std::string testName("ClassMat.SubstractionOperators");

    {
        printSection(testName, "Mat<T, m, n>::operator-=(const Mat<T, m, n>& x)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        x -= y;

        EXPECT_FLOAT_EQ(x[0][0], -1.5f); EXPECT_FLOAT_EQ(x[0][1], -5.9f);
        EXPECT_FLOAT_EQ(x[1][0], -5.6f); EXPECT_FLOAT_EQ(x[1][1], 9.5f);
        EXPECT_FLOAT_EQ(x[2][0], 3.5f);  EXPECT_FLOAT_EQ(x[2][1], -13.3f);
    }

    {
        printSection(testName, "operator-(const Mat<T, m, n>& x, const Mat<T, m, n>& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = x - y;

        EXPECT_FLOAT_EQ(z[0][0], -1.5f); EXPECT_FLOAT_EQ(z[0][1], -5.9f);
        EXPECT_FLOAT_EQ(z[1][0], -5.6f); EXPECT_FLOAT_EQ(z[1][1], 9.5f);
        EXPECT_FLOAT_EQ(z[2][0], 3.5f);  EXPECT_FLOAT_EQ(z[2][1], -13.3f);
    }

    {
        printSection(testName, "operator-(Mat<T, m, n>&& x, const Mat<T, m, n>& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = std::move(x) - y;

        EXPECT_FLOAT_EQ(z[0][0], -1.5f); EXPECT_FLOAT_EQ(z[0][1], -5.9f);
        EXPECT_FLOAT_EQ(z[1][0], -5.6f); EXPECT_FLOAT_EQ(z[1][1], 9.5f);
        EXPECT_FLOAT_EQ(z[2][0], 3.5f);  EXPECT_FLOAT_EQ(z[2][1], -13.3f);
    }

    {
        printSection(testName, "operator-(const Mat<T, m, n>& x, Mat<T, m, n>&& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = x - std::move(y);

        EXPECT_FLOAT_EQ(z[0][0], -1.5f); EXPECT_FLOAT_EQ(z[0][1], -5.9f);
        EXPECT_FLOAT_EQ(z[1][0], -5.6f); EXPECT_FLOAT_EQ(z[1][1], 9.5f);
        EXPECT_FLOAT_EQ(z[2][0], 3.5f);  EXPECT_FLOAT_EQ(z[2][1], -13.3f);
    }

    {
        printSection(testName, "operator-(Mat<T, m, n>&& x, Mat<T, m, n>&& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y({ {
                {3.1f, 4.1f},
                {5.9f, -5.6f},
                {5.3f, 5.9f}
            } });
        Mat<float, 3, 2> z;
        z = std::move(x) - std::move(y);

        EXPECT_FLOAT_EQ(z[0][0], -1.5f); EXPECT_FLOAT_EQ(z[0][1], -5.9f);
        EXPECT_FLOAT_EQ(z[1][0], -5.6f); EXPECT_FLOAT_EQ(z[1][1], 9.5f);
        EXPECT_FLOAT_EQ(z[2][0], 3.5f);  EXPECT_FLOAT_EQ(z[2][1], -13.3f);
    }
}

TEST(ClassMat, MultiplicationOperators)
{
    std::string testName("ClassMat.MultiplicationOperators");

    {
        printSection(testName, "operator*(const Mat<T, m, n>& x, const Mat<T, m, n>& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 2, 3> y({ {
                {3.1f, 4.1f, 5.9f},
                {-5.6f, 5.3f, 5.9f}
            } });
        Mat<float, 3, 3> z;
        Mat<float, 2, 2> t;

        z = x * y;
        t = y * x;

        EXPECT_FLOAT_EQ(z[0][0], 15.04f);  EXPECT_FLOAT_EQ(z[0][1], -2.98f); EXPECT_FLOAT_EQ(z[0][2], 1.6f*5.9f - 1.8f*5.9f);
        EXPECT_FLOAT_EQ(z[1][0], -20.91f); EXPECT_FLOAT_EQ(z[1][1], 21.9f);  EXPECT_FLOAT_EQ(z[1][2], 24.78f);
        EXPECT_FLOAT_EQ(z[2][0], 68.72f);  EXPECT_FLOAT_EQ(z[2][1], -3.14f); EXPECT_FLOAT_EQ(z[2][2], 8.26f);

        EXPECT_FLOAT_EQ(t[0][0], 58.11f); EXPECT_FLOAT_EQ(t[0][1], -33.25f);
        EXPECT_FLOAT_EQ(t[1][0], 44.55f); EXPECT_FLOAT_EQ(t[1][1], -12.91f);
    }
}

TEST(ClassMat, DivisionOperators)
{
    std::string testName("ClassMat.DivisionOperators");

    {
        printSection(testName, "operator/(const Mat<T, m, n>& x, const T& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        float y = 3.14;
        Mat<float, 3, 2> z;
        z = x / y;

        EXPECT_NEAR(z[0][0], 0.5096f, 1e-4); EXPECT_NEAR(z[0][1], -0.5732f, 1e-4);
        EXPECT_NEAR(z[1][0], 0.0955f, 1e-4); EXPECT_NEAR(z[1][1], 1.2420f, 1e-4);
        EXPECT_NEAR(z[2][0], 2.8025f, 1e-4); EXPECT_NEAR(z[2][1], -2.3567f, 1e-4);
    }

    {
        printSection(testName, "operator/(Mat<T, m, n>&& x, const T& y)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        float y = 3.14;
        Mat<float, 3, 2> z;
        z = std::move(x) / y;

        EXPECT_NEAR(z[0][0], 0.5096f, 1e-4); EXPECT_NEAR(z[0][1], -0.5732f, 1e-4);
        EXPECT_NEAR(z[1][0], 0.0955f, 1e-4); EXPECT_NEAR(z[1][1], 1.2420f, 1e-4);
        EXPECT_NEAR(z[2][0], 2.8025f, 1e-4); EXPECT_NEAR(z[2][1], -2.3567f, 1e-4);
    }
}

TEST(ClassMat, UnaryOperators)
{
    std::string testName("ClassMat.UnaryOperators");

    {
        printSection(testName, "operator-(const Mat<T, m, n>& x)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y;
        y = -x;

        EXPECT_FLOAT_EQ(x[0][0], 1.6f); EXPECT_FLOAT_EQ(x[0][1], -1.8f);
        EXPECT_FLOAT_EQ(x[1][0], 0.3f); EXPECT_FLOAT_EQ(x[1][1], 3.9f);
        EXPECT_FLOAT_EQ(x[2][0], 8.8f); EXPECT_FLOAT_EQ(x[2][1], -7.4f);

        EXPECT_FLOAT_EQ(y[0][0], -1.6f); EXPECT_FLOAT_EQ(y[0][1], 1.8f);
        EXPECT_FLOAT_EQ(y[1][0], -0.3f); EXPECT_FLOAT_EQ(y[1][1], -3.9f);
        EXPECT_FLOAT_EQ(y[2][0], -8.8f); EXPECT_FLOAT_EQ(y[2][1], 7.4f);
    }

    {
        printSection(testName, "operator+(const Mat<T, m, n>& x)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y;
        y = +x;

        EXPECT_FLOAT_EQ(x[0][0], 1.6f); EXPECT_FLOAT_EQ(x[0][1], -1.8f);
        EXPECT_FLOAT_EQ(x[1][0], 0.3f); EXPECT_FLOAT_EQ(x[1][1], 3.9f);
        EXPECT_FLOAT_EQ(x[2][0], 8.8f); EXPECT_FLOAT_EQ(x[2][1], -7.4f);

        EXPECT_FLOAT_EQ(y[0][0], 1.6f); EXPECT_FLOAT_EQ(y[0][1], -1.8f);
        EXPECT_FLOAT_EQ(y[1][0], 0.3f); EXPECT_FLOAT_EQ(y[1][1], 3.9f);
        EXPECT_FLOAT_EQ(y[2][0], 8.8f); EXPECT_FLOAT_EQ(y[2][1], -7.4f);
    }

    {
        printSection(testName, "operator-(Mat<T, m, n>&& x)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y;
        y = -std::move(x);

        EXPECT_FLOAT_EQ(y[0][0], -1.6f); EXPECT_FLOAT_EQ(y[0][1], 1.8f);
        EXPECT_FLOAT_EQ(y[1][0], -0.3f); EXPECT_FLOAT_EQ(y[1][1], -3.9f);
        EXPECT_FLOAT_EQ(y[2][0], -8.8f); EXPECT_FLOAT_EQ(y[2][1], 7.4f);
    }

    {
        printSection(testName, "operator+(Mat<T, m, n>&& x)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 3, 2> y;
        y = +std::move(x);

        EXPECT_FLOAT_EQ(y[0][0], 1.6f); EXPECT_FLOAT_EQ(y[0][1], -1.8f);
        EXPECT_FLOAT_EQ(y[1][0], 0.3f); EXPECT_FLOAT_EQ(y[1][1], 3.9f);
        EXPECT_FLOAT_EQ(y[2][0], 8.8f); EXPECT_FLOAT_EQ(y[2][1], -7.4f);
    }
}

TEST(ClassMat, Comparators)
{
    std::string testName("ClassMat.Comparators");

    {
        printSection(testName, "operator==(const Mat<T, m, n>& x, const Mat<T, m, n>& y)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            EXPECT_EQ(x == y, true);
            EXPECT_EQ(y == x, true);
        }

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, 0.4f}
                } });
            EXPECT_EQ(x == y, false);
            EXPECT_EQ(y == x, false);
        }
    }

    {
        printSection(testName, "operator!=(const Mat<T, m, n>& x, const Mat<T, m, n>& y)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            EXPECT_EQ(x != y, false);
            EXPECT_EQ(y != x, false);
        }

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            Mat<float, 3, 2> y({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, 0.4f}
                } });
            EXPECT_EQ(x != y, true);
            EXPECT_EQ(y != x, true);
        }
    }
}

TEST(ClassMat, StreamOperators)
{
    std::string testName("ClassMat.StreamOperators");

    {
        printSection(testName, "operator<<(std::ostream& stream, const Mat<T, m, n>& x)");

        {
            Mat<float, 3, 2> x({ {
                    {1.6f, -1.8f},
                    {0.3f, 3.9f},
                    {8.8f, -7.4f}
                } });
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(1.6 -1.8\n 0.3 3.9\n 8.8 -7.4)");
        }

        {
            Mat<float, 3, 2> x;
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "(0 0\n 0 0\n 0 0)");
        }

        {
            Mat<float, 0, 0> x;
            std::stringstream stream;
            stream << x;
            EXPECT_EQ(stream.str(), "()");
        }
    }
}

TEST(ClassMat, SpecificFunctions)
{
    std::string testName("ClassMat.SpecificFunctions");

    {
        printSection(testName, "convolve(const Mat<T, m, n>& a, const Mat<T, p, q>& b, ConvolveMethod method)");

        {
            Mat<float, 3, 3> x({ {
                    {1.6f, -1.8f, 3.1f},
                    {0.3f, 3.9f, -4.1f},
                    {8.8f, -7.4f, 5.9f}
                } });
            Mat<float, 3, 1> y(std::array<std::array<float, 1>, 3>{ { {0.f}, {0.f}, {1.f} } });
            Mat<float, 3, 3> z;

            z = convolve(x, y);
            EXPECT_NEAR(z[0][0], 0.3f, 1e-10); EXPECT_NEAR(z[0][1], 3.9f, 1e-10);  EXPECT_NEAR(z[0][2], -4.1f, 1e-10);
            EXPECT_NEAR(z[1][0], 8.8f, 1e-10); EXPECT_NEAR(z[1][1], -7.4f, 1e-10); EXPECT_NEAR(z[1][2], 5.9f, 1e-10);
            EXPECT_NEAR(z[2][0], 1.6f, 1e-10); EXPECT_NEAR(z[2][1], -1.8f, 1e-10); EXPECT_NEAR(z[2][2], 3.1f, 1e-10);

            z = convolve(x, y, ConvolveMethod::Continuous);
            EXPECT_NEAR(z[0][0], 0.3f, 1e-10); EXPECT_NEAR(z[0][1], 3.9f, 1e-10);  EXPECT_NEAR(z[0][2], -4.1f, 1e-10);
            EXPECT_NEAR(z[1][0], 8.8f, 1e-10); EXPECT_NEAR(z[1][1], -7.4f, 1e-10); EXPECT_NEAR(z[1][2], 5.9f, 1e-10);
            EXPECT_NEAR(z[2][0], 8.8f, 1e-10); EXPECT_NEAR(z[2][1], -7.4f, 1e-10); EXPECT_NEAR(z[2][2], 5.9f, 1e-10);

            z = convolve(x, y, ConvolveMethod::Zero);
            EXPECT_NEAR(z[0][0], 0.3f, 1e-10); EXPECT_NEAR(z[0][1], 3.9f, 1e-10);  EXPECT_NEAR(z[0][2], -4.1f, 1e-10);
            EXPECT_NEAR(z[1][0], 8.8f, 1e-10); EXPECT_NEAR(z[1][1], -7.4f, 1e-10); EXPECT_NEAR(z[1][2], 5.9f, 1e-10);
            EXPECT_NEAR(z[2][0], 0.f, 1e-10);  EXPECT_NEAR(z[2][1], 0.f, 1e-10);   EXPECT_NEAR(z[2][2], 0.f, 1e-10);
        }

        {
            Mat<float, 3, 3> x({ {
                    {1.6f, 1.8f, 3.1f},
                    {0.3f, 3.9f, 4.1f},
                    {8.8f, 7.4f, 5.9f}
                } });
            Mat<float, 3, 1> y(std::array<std::array<float, 1>, 3>{ { {0.01f}, {1.f}, {0.0001f} } });
            Mat<float, 3, 3> z;

            z = convolve(x, y);
            EXPECT_NEAR(z[0][0], 1.68803f, 1e-5); EXPECT_NEAR(z[0][1], 1.87439f, 1e-5); EXPECT_NEAR(z[0][2], 3.15941f, 1e-5);
            EXPECT_NEAR(z[1][0], 0.31688f, 1e-5); EXPECT_NEAR(z[1][1], 3.91874f, 1e-5); EXPECT_NEAR(z[1][2], 4.13159f, 1e-5);
            EXPECT_NEAR(z[2][0], 8.80316f, 1e-5); EXPECT_NEAR(z[2][1], 7.43918f, 1e-5); EXPECT_NEAR(z[2][2], 5.94131f, 1e-5);

            z = convolve(x, y,  ConvolveMethod::Continuous);
            EXPECT_NEAR(z[0][0], 1.61603f, 1e-5); EXPECT_NEAR(z[0][1], 1.81839f, 1e-5); EXPECT_NEAR(z[0][2], 3.13141f, 1e-5);
            EXPECT_NEAR(z[1][0], 0.31688f, 1e-5); EXPECT_NEAR(z[1][1], 3.91874f, 1e-5); EXPECT_NEAR(z[1][2], 4.13159f, 1e-5);
            EXPECT_NEAR(z[2][0], 8.80388f, 1e-5); EXPECT_NEAR(z[2][1], 7.43974f, 1e-5); EXPECT_NEAR(z[2][2], 5.94159f, 1e-5);

            z = convolve(x, y,  ConvolveMethod::Zero);
            EXPECT_NEAR(z[0][0], 1.60003f, 1e-5); EXPECT_NEAR(z[0][1], 1.80039f, 1e-5); EXPECT_NEAR(z[0][2], 3.10041f, 1e-5);
            EXPECT_NEAR(z[1][0], 0.31688f, 1e-5); EXPECT_NEAR(z[1][1], 3.91874f, 1e-5); EXPECT_NEAR(z[1][2], 4.13159f, 1e-5);
            EXPECT_NEAR(z[2][0], 8.80300f, 1e-5); EXPECT_NEAR(z[2][1], 7.43900f, 1e-5); EXPECT_NEAR(z[2][2], 5.94100f, 1e-5);
        }

        {
            Mat<float, 3, 3> x({ {
                    {1.6f, 1.8f, 3.1f},
                    {0.3f, 3.9f, 4.1f},
                    {8.8f, 7.4f, 5.9f}
                } });
            Mat<float, 3, 2> y;
            Mat<float, 2, 3> z;

            EXPECT_THROW(convolve(x, y), std::runtime_error);
            EXPECT_THROW(convolve(x, z), std::runtime_error);
        }

        {
            Mat<float, 3, 3> x({ {
                    {1.6f, 1.8f, 3.1f},
                    {0.3f, 3.9f, 4.1f},
                    {8.8f, 7.4f, 5.9f}
                } });
            Mat<float, 5, 1> y;
            Mat<float, 1, 5> z;

            EXPECT_THROW(convolve(x, y), std::runtime_error);
            EXPECT_THROW(convolve(x, z), std::runtime_error);
        }
    }

    {
        printSection(testName, "inverse(const Mat<T, n, n>& a)");

        {
            Mat<float, 3, 3> x({ {
                    {1.6f, -1.8f, 3.1f},
                    {0.3f, 3.9f, -4.1f},
                    {8.8f, -7.4f, 5.9f}
                } });
            Mat<float, 3, 3> y;

            y = x * inverse(x);
            EXPECT_NEAR(y[0][0], 1, 1e-5); EXPECT_NEAR(y[0][1], 0, 1e-5);  EXPECT_NEAR(y[0][2], 0, 1e-5);
            EXPECT_NEAR(y[1][0], 0, 1e-5); EXPECT_NEAR(y[1][1], 1, 1e-5);  EXPECT_NEAR(y[1][2], 0, 1e-5);
            EXPECT_NEAR(y[2][0], 0, 1e-5); EXPECT_NEAR(y[2][1], 0, 1e-5);  EXPECT_NEAR(y[2][2], 1, 1e-5);

            y = inverse(x) * x;
            EXPECT_NEAR(y[0][0], 1, 1e-5); EXPECT_NEAR(y[0][1], 0, 1e-5);  EXPECT_NEAR(y[0][2], 0, 1e-5);
            EXPECT_NEAR(y[1][0], 0, 1e-5); EXPECT_NEAR(y[1][1], 1, 1e-5);  EXPECT_NEAR(y[1][2], 0, 1e-5);
            EXPECT_NEAR(y[2][0], 0, 1e-5); EXPECT_NEAR(y[2][1], 0, 1e-5);  EXPECT_NEAR(y[2][2], 1, 1e-5);
        }

        {
            Mat<float, 3, 3> x;
            EXPECT_THROW(inverse(x), std::runtime_error);
        }
    }

    {
        printSection(testName, "transpose(const Mat<T, m, n>& a)");

        Mat<float, 3, 2> x({ {
                {1.6f, -1.8f},
                {0.3f, 3.9f},
                {8.8f, -7.4f}
            } });
        Mat<float, 2, 3> y;
        y = transpose(x);
        EXPECT_FLOAT_EQ(y[0][0], 1.6f);  EXPECT_FLOAT_EQ(y[0][1], 0.3f); EXPECT_FLOAT_EQ(y[0][2], 8.8f);
        EXPECT_FLOAT_EQ(y[1][0], -1.8f); EXPECT_FLOAT_EQ(y[1][1], 3.9f); EXPECT_FLOAT_EQ(y[1][2], -7.4f);
    }

    {
        printSection(testName, "det(const Mat<T, n, n>& a)");

        {
            Mat<float, 3, 3> x({ {
                    {1.6f,  0.f,  0.f},
                    {0.3f,  3.9f, 0.f},
                    {8.8f, -7.4f, 5.9f}
                } });
            
            EXPECT_NEAR(det(x), 36.816f, 1e-5);
        }

        {
            Mat<float, 3, 3> x;
            EXPECT_NEAR(det(x), 0.f, 1e-5);
        }
    }

    {
        printSection(testName, "dft(const Mat<std::complex<T>, m, n>& f) and idft(const Mat<std::complex<T>, m, n>& fh)");

        {
            Mat<std::complex<float>, 3, 3> x({ {
                    {
                        std::complex<float>{1.6f, 1.8f},
                        std::complex<float>{0.3f, 3.9f},
                        std::complex<float>{8.8f, 7.4f}
                    },
                    {
                        std::complex<float>{9.8f, 9.3f},
                        std::complex<float>{1.4f, 1.5f},
                        std::complex<float>{9.2f, 6.5f}
                    },
                    {
                        std::complex<float>{3.5f, 8.9f},
                        std::complex<float>{2.7f, 2.8f},
                        std::complex<float>{1.8f, 2.8f}
                    }
                } });
            Mat<std::complex<float>, 3, 3> y;
            y = idft(dft(x));

            EXPECT_NEAR(y[0][0].real(), x[0][0].real(), 1e-5);
            EXPECT_NEAR(y[0][1].real(), x[0][1].real(), 1e-5);
            EXPECT_NEAR(y[0][2].real(), x[0][2].real(), 1e-5);

            EXPECT_NEAR(y[1][0].real(), x[1][0].real(), 1e-5);
            EXPECT_NEAR(y[1][1].real(), x[1][1].real(), 1e-5);
            EXPECT_NEAR(y[1][2].real(), x[1][2].real(), 1e-5);

            EXPECT_NEAR(y[2][0].real(), x[2][0].real(), 1e-5);
            EXPECT_NEAR(y[2][1].real(), x[2][1].real(), 1e-5);
            EXPECT_NEAR(y[2][2].real(), x[2][2].real(), 1e-5);

            EXPECT_NEAR(y[0][0].imag(), x[0][0].imag(), 1e-5);
            EXPECT_NEAR(y[0][1].imag(), x[0][1].imag(), 1e-5);
            EXPECT_NEAR(y[0][2].imag(), x[0][2].imag(), 1e-5);

            EXPECT_NEAR(y[1][0].imag(), x[1][0].imag(), 1e-5);
            EXPECT_NEAR(y[1][1].imag(), x[1][1].imag(), 1e-5);
            EXPECT_NEAR(y[1][2].imag(), x[1][2].imag(), 1e-5);

            EXPECT_NEAR(y[2][0].imag(), x[2][0].imag(), 1e-5);
            EXPECT_NEAR(y[2][1].imag(), x[2][1].imag(), 1e-5);
            EXPECT_NEAR(y[2][2].imag(), x[2][2].imag(), 1e-5);
        }
    }

    {
        printSection(testName, "dct(const Mat<T, m, n>& f) and idct(const Mat<T, m, n>& fh)");

        {
            Mat<float, 3, 3> x({ {
                    {1.6f, -1.8f, 3.1f},
                    {0.3f, 3.9f, 4.1f},
                    {8.8f, -7.4f, 5.9f}
                } });
            Mat<float, 3, 3> y;
            y = idct(dct(x));

            EXPECT_NEAR(y[0][0], x[0][0], 1e-5); EXPECT_NEAR(y[0][1], x[0][1], 1e-5); EXPECT_NEAR(y[0][2], x[0][2], 1e-5);
            EXPECT_NEAR(y[1][0], x[1][0], 1e-5); EXPECT_NEAR(y[1][1], x[1][1], 1e-5); EXPECT_NEAR(y[1][2], x[1][2], 1e-5);
            EXPECT_NEAR(y[2][0], x[2][0], 1e-5); EXPECT_NEAR(y[2][1], x[2][1], 1e-5); EXPECT_NEAR(y[2][2], x[2][2], 1e-5);
        }
    }
}
