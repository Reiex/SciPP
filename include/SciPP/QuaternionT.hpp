#pragma once

#include <SciPP/Quaternion.hpp>

namespace scp
{
    template<typename T>
    Quaternion<T>::Quaternion() :
        _a(0),
        _b(0),
        _c(0),
        _d(0)
    {
    }

    template<typename T>
    Quaternion<T>::Quaternion(int64_t x) :
        _a(x),
        _b(0),
        _c(0),
        _d(0)
    {
    }
    
    template<typename T>
    Quaternion<T>::Quaternion(const T& x) :
        _a(x),
        _b(0),
        _c(0),
        _d(0)
    {
    }
    
    template<typename T>
    Quaternion<T>::Quaternion(const T& a, const T& b, const T& c, const T& d) :
        _a(a),
        _b(b),
        _c(c),
        _d(d)
    {
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& q)
    {
        _a += q._a;
        _b += q._b;
        _c += q._c;
        _d += q._d;

        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& q)
    {
        _a -= q._a;
        _b -= q._b;
        _c -= q._c;
        _d -= q._d;

        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator*=(const Quaternion<T>& q)
    {
        T a = _a*q._a - _b*q._b - _c*q._c - _d*q._d;
        T b = _a*q._b + _b*q._a + _c*q._d - _d*q._c;
        T c = _a*q._c - _b*q._d + _c*q._a + _d*q._b;
        T d = _a*q._d + _b*q._c - _c*q._b + _d*q._a;

        _a = a;
        _b = b;
        _c = c;
        _d = d;

        return *this;
    }
    
    template<typename T>
    Quaternion<T>& Quaternion<T>::operator/=(const T& x)
    {
        _a /= x;
        _b /= x;
        _c /= x;
        _d /= x;

        return *this;
    }

    template<typename T>
    const T& Quaternion<T>::real() const
    {
        return _a;
    }
    
    template<typename T>
    std::array<T, 3> Quaternion<T>::imag() const
    {
        return {_b, _c, _d};
    }

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
        std::array<T, 3> imag(q.imag());
        return Quaternion<T>(-q.real(), -imag[0], -imag[1], -imag[2]);
    }

    template<typename T>
    Quaternion<T>&& operator-(Quaternion<T>&& q)
    {
        q.real(-q.real());
        std::array<T, 3> imag(q.imag());
        q.imag(-imag[0], -imag[1], -imag[2]);

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

    template<typename T>
    bool operator==(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        return p.real() == q.real() && p.imag() == q.imag();
    }

    template<typename T>
    bool operator!=(const Quaternion<T>& p, const Quaternion<T>& q)
    {
        return !(p == q);
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& q)
    {
        std::array<T, 3> imag(q.imag());
        stream << "(" << q.real() << "," << imag[0] << "," << imag[1] << "," << imag[2] << ")";

        return stream;
    }

    template<typename T>
    Quaternion<T> inverse(const Quaternion<T>& q)
    {
        return std::conj(q)/std::norm(q);
    }
}

namespace std
{
    template<typename T>
    T real(const scp::Quaternion<T>& q)
    {
        return q.real();
    }

    template<typename T>
    array<T, 3> imag(const scp::Quaternion<T>& q)
    {
        return q.imag();
    }
    
    template<typename T>
    T abs(const scp::Quaternion<T>& q)
    {
        return sqrt(norm(q));
    }
    
    template<typename T>
    T norm(const scp::Quaternion<T>& q)
    {
        std::array<T, 3> imag(q.imag());
        return q.real()*q.real() + imag[0]*imag[0] + imag[1]*imag[1] + imag[2]*imag[2];
    }
    
    template<typename T>
    scp::Quaternion<T> conj(const scp::Quaternion<T>& q)
    {
        array<T, 3> imag(q.imag());
        return scp::Quaternion<T>(q.real(), -imag[0], -imag[1], -imag[2]);
    }
}
