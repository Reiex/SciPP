#pragma once

#include <SciPP/Quaternion.hpp>

namespace scp
{
    // Constructors

    template<typename T>
    Quaternion<T>::Quaternion() :
        a(0),
        b(0),
        c(0),
        d(0)
    {
    }

    template<typename T>
    Quaternion<T>::Quaternion(int64_t x) :
        a(x),
        b(0),
        c(0),
        d(0)
    {
    }
    
    template<typename T>
    Quaternion<T>::Quaternion(const T& x) :
        a(x),
        b(0),
        c(0),
        d(0)
    {
    }
    
    template<typename T>
    Quaternion<T>::Quaternion(const T& aValue, const T& bValue, const T& cValue, const T& dValue) :
        a(aValue),
        b(bValue),
        c(cValue),
        d(dValue)
    {
    }
    
    template<typename T>
    Quaternion<T>::Quaternion(const std::array<T, 4> values) :
        a(values[0]),
        b(values[1]),
        c(values[2]),
        d(values[3])
    {
    }


    // Internal operators

    template<typename T>
    Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& q)
    {
        a += q.a;
        b += q.b;
        c += q.c;
        d += q.d;

        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& q)
    {
        a -= q.a;
        b -= q.b;
        c -= q.c;
        d -= q.d;

        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& q)
    {
        T newA = a*q.a - b*q.b - c*q.c - d*q.d;
        T newB = a*q.b + b*q.a + c*q.d - d*q.c;
        T newC = a*q.c - b*q.d + c*q.a + d*q.b;
        T newD = a*q.d + b*q.c - c*q.b + d*q.a;

        a = newA;
        b = newB;
        c = newC;
        d = newD;

        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator/=(const T& x)
    {
        a /= x;
        b /= x;
        c /= x;
        d /= x;

        return *this;
    }



    // External operators

    template<typename T>
    Quaternion<T> operator+(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        Quaternion<T> r(p);
        r += q;

        return r;
    }

    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& p, const Quaternion<T>& q)
    {
        p += q;
        return std::move(p);
    }

    template<typename T>
    Quaternion<T>&& operator+(const Quaternion<T>& p, Quaternion<T>&& q)
    {
        q += p;
        return std::move(q);
    }

    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& p, Quaternion<T>&& q)
    {
        p += q;
        return std::move(p);
    }


    template<typename T>
    Quaternion<T> operator-(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        Quaternion<T> r(p);
        r -= q;

        return r;
    }

    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& p, const Quaternion<T>& q)
    {
        p -= q;
        return std::move(p);
    }

    template<typename T>
    Quaternion<T>&& operator-(const Quaternion<T>& p, Quaternion<T>&& q)
    {
        q -= p;
        return -std::move(q);
    }

    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& p, Quaternion<T>&& q)
    {
        p -= q;
        return std::move(p);
    }


    template<typename T>
    Quaternion<T> operator*(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        Quaternion<T> r(p);
        r *= q;

        return r;
    }

    template<typename T>
    Quaternion<T>&& operator*(Quaternion<T>&& p, const Quaternion<T>& q)
    {
        p *= q;
        return std::move(p);
    }

    template<typename T>
    Quaternion<T>&& operator*(Quaternion<T>&& p, Quaternion<T>&& q)
    {
        p *= q;
        return std::move(p);
    }


    template<typename T>
    Quaternion<T> operator/(const Quaternion<T>& q, const T& x)
    {
        Quaternion<T> r(q);
        r /= x;

        return r;
    }

    template<typename T>
    Quaternion<T>&& operator/(Quaternion<T>&& q, const T& x)
    {
        q /= x;
        return std::move(q);
    }


    template<typename T>
    Quaternion<T> operator-(const Quaternion<T>& q)
    {
        return Quaternion<T>(-q.a, -q.b, -q.c, -q.d);
    }

    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& q)
    {
        q.a = -q.a;
        q.b = -q.b;
        q.c = -q.c;
        q.d = -q.d;

        return std::move(q);
    }


    template<typename T>
    Quaternion<T> operator+(const Quaternion<T>& q)
    {
        return q;
    }

    template<typename T>
    Quaternion<T>&& operator+(Quaternion<T>&& q)
    {
        return std::move(q);
    }


    // Comparators

    template<typename T>
    bool operator==(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        return p.a == q.a && p.b == q.b && p.c == q.c && p.d == q.d;
    }

    template<typename T>
    bool operator!=(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        return !(p == q);
    }


    // Display

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& q)
    {
        stream << q.a << " " << q.b << " " << q.c << " " << q.d;

        return stream;
    }


    // Specific functions

    template<typename T>
    Quaternion<T> inverse(const Quaternion<T>& q)
    {
        T l(normSq(q));

        if (l == T(0))
            throw std::runtime_error("Cannot inverse Quaternion<T>(T(0)).");

        return {q.a/l, -q.b/l, -q.c/l, -q.d/l};
    }

    template<typename T>
    T normSq(const Quaternion<T>& q)
    {
        return q.a*q.a + q.b*q.b + q.c*q.c + q.d*q.d;
    }

    template<typename T>
    T norm(const Quaternion<T>& q)
    {
        return sqrt(normSq(q));
    }
}
