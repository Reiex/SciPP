#pragma once

#include <SciPP/types.hpp>

namespace scp
{
    template<typename T, uint64_t m, uint64_t n = m>
    class Mat
    {
        public:

            static const uint64_t M = m;
            static const uint64_t N = n;

            Mat();
            Mat(int64_t x);
            Mat(const T& x);
            Mat(const std::vector<T>& diag);
            Mat(const std::vector<std::vector<T>>& values);
            Mat(const Mat<T, m, n>& a) = default;
            Mat(Mat<T, m, n>&& a) = default;

            Mat<T, m, n>& operator=(const Mat<T, m, n>& a) = default;
            Mat<T, m, n>& operator=(Mat<T, m, n>&& a) = default;

            Mat<T, m, n>& operator+=(const Mat<T, m, n>& a);
            Mat<T, m, n>& operator-=(const Mat<T, m, n>& a);

            Vec<T, n>& operator[](uint64_t i);
            const Vec<T, n>& operator[](uint64_t i) const;

        private:

            Vec<T, n> _values[m];
    };

    // External operators

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator+(const Mat<T, m, n>& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(const Mat<T, m, n>& a, Mat<T, m, n>&& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a, Mat<T, m, n>&& b);

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator-(const Mat<T, m, n>& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(const Mat<T, m, n>& a, Mat<T, m, n>&& b);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a, Mat<T, m, n>&& b);

    template<typename T, uint64_t m, uint64_t n, uint64_t p>
    Mat<T, m, p> operator*(const Mat<T, m, n>& a, const Mat<T, n, p>& b);

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator-(const Mat<T, m, n>& a);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator-(Mat<T, m, n>&& a);

    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n> operator+(const Mat<T, m, n>& a);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, m, n>&& operator+(Mat<T, m, n>&& a);

    // Comparators

    template<typename T, uint64_t m, uint64_t n>
    bool operator==(const Mat<T, m, n>& a, const Mat<T, m, n>& b);
    template<typename T, uint64_t m, uint64_t n>
    bool operator!=(const Mat<T, m, n>& a, const Mat<T, m, n>& b);

    // Display

    template<typename T, uint64_t m, uint64_t n>
    std::ostream& operator<<(std::ostream& stream, const Mat<T, m, n>& a);

    // Specific functions

    enum class ConvolveMethod
    {
        Periodic,
        Continuous,
        Zero
    };

    template<typename T, uint64_t m, uint64_t n, uint64_t p, uint64_t q>
    Mat<T, m, n> convolve(const Mat<T, m, n>& a, const Mat<T, p, q>& b, ConvolveMethod method = ConvolveMethod::Periodic);
    template<typename T, uint64_t n>
    Mat<T, n, n> inverse(const Mat<T, n, n>& a);
    template<typename T, uint64_t m, uint64_t n>
    Mat<T, n, m> transpose(const Mat<T, m, n>& a);
    template<typename T, uint64_t n>
    T det(const Mat<T, n, n>& a);
}

#include <SciPP/MatT.hpp>
