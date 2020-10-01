#pragma once

#include <SciPP/types.hpp>

namespace scp
{
    template<typename T>
    class Quaternion
    {
        public:

            Quaternion();
            Quaternion(int64_t x);
            Quaternion(const T& x);
            Quaternion(const T& a, const T& b, const T& c, const T& d);
            Quaternion(const Quaternion<T>& q) = default;
            Quaternion(Quaternion<T>&& q) = default;

            Quaternion<T>& operator=(const Quaternion<T>& q) = default;
            Quaternion<T>& operator=(Quaternion<T>&& q) = default;

            Quaternion<T>& operator+=(const Quaternion<T>& q);
            Quaternion<T>& operator-=(const Quaternion<T>& q);
            Quaternion<T>& operator*=(const Quaternion<T>& q);
            Quaternion<T>& operator/=(const T& x);

            const T& real() const;
            void real(const T& a);
            std::array<T, 3> imag() const;
            void imag(const T& b, const T& c, const T& d);

        private:

            T _a;
            T _b;
            T _c;
            T _d;
    };

    template<typename T>
    Quaternion<T> operator+(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator+(const Quaternion<T>& p, Quaternion<T>&& q);
    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& p, Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator-(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator-(const Quaternion<T>& p, Quaternion<T>&& q);
    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& p, Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator*(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator*(Quaternion<T>&& p, const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator*(Quaternion<T>&& p, Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator/(const Quaternion<T>& q, const T& x);
    template<typename T>
    Quaternion<T>&& operator/(Quaternion<T>&& q, const T& x);

    template<typename T>
    Quaternion<T> operator-(const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& q);

    template<typename T>
    Quaternion<T> operator+(const Quaternion<T>& q);
    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& q);

    template<typename T>
    bool operator==(const Quaternion<T>& p, const Quaternion<T>& q);
    template<typename T>
    bool operator!=(const Quaternion<T>& p, const Quaternion<T>& q);

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& q);

    template<typename T>
    Quaternion<T> inverse(const Quaternion<T>& q);
}

namespace std
{
    template<typename T>
    T real(const scp::Quaternion<T>& q);
    template<typename T>
    array<T, 3> imag(const scp::Quaternion<T>& q);
    template<typename T>
    T abs(const scp::Quaternion<T>& q);
    template<typename T>
    T norm(const scp::Quaternion<T>& q);
    template<typename T>
    scp::Quaternion<T> conj(const scp::Quaternion<T>& q);
}

#include <SciPP/QuaternionT.hpp>
