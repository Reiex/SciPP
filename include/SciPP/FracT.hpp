#pragma once

#include <SciPP/Frac.hpp>

namespace scp
{
    // Constructeurs

    template<typename T>
    Frac<T>::Frac() :
        m_p(0),
        m_q(1)
    {
    }

    template<typename T>
    Frac<T>::Frac(int64_t x) :
        m_p(x),
        m_q(1)
    {
    }

    template<typename T>
    Frac<T>::Frac(const T& x) :
        m_p(x),
        m_q(1)
    {
    }

    template<typename T>
    Frac<T>::Frac(const T& p, const T& q) :
        m_p(p),
        m_q(q)
    {
        if (q == 0)
            throw std::runtime_error("You cannot init a Frac with the denominator at 0.");

        simplify();
    }


    // Acces et modification de la structure

    template<typename T>
    const T& Frac<T>::num() const
    {
        return m_p;
    }

    template<typename T>
    const T& Frac<T>::denom() const
    {
        return m_q;
    }


    // Operations internes

    template<typename T>
    Frac<T>& Frac<T>::operator+=(const Frac<T>& a)
    {
        m_p = m_p * a.m_q + a.m_p*m_q;
        m_q *= a.m_q;

        simplify();

        return *this;
    }

    template<typename T>
    Frac<T>& Frac<T>::operator-=(const Frac<T>& a)
    {
        m_p = m_p * a.m_q - a.m_p*m_q;
        m_q *= a.m_q;

        simplify();

        return *this;
    }

    template<typename T>
    Frac<T>& Frac<T>::operator*=(const Frac<T>& a)
    {
        m_p *= a.m_p;
        m_q *= a.m_q;

        simplify();

        return *this;
    }

    template<typename T>
    Frac<T>& Frac<T>::operator/=(const Frac<T>& a)
    {
        m_p *= a.m_q;
        m_q *= a.m_p;

        simplify();

        return *this;
    }


    // Fonctions specifiques

    template<typename T>
    void Frac<T>::simplify()
    {
        if (m_q < 0)
        {
            m_q = -m_q;
            m_p = -m_p;
        }

        if (m_p == 0)
        {
            m_q = 1;
            return;
        }

        T x(gcd(m_p, m_q));
        m_p /= x;
        m_q /= x;
    }

    // Operations externes

    template<typename T>
    Frac<T> operator+(const Frac<T>& a, const Frac<T>& b)
    {
        Frac<T> c(a);
        c += b;

        return c;
    }

    template<typename T>
    Frac<T> operator-(const Frac<T>& a, const Frac<T>& b)
    {
        Frac<T> c(a);
        c -= b;

        return c;
    }

    template<typename T>
    Frac<T> operator*(const Frac<T>& a, const Frac<T>& b)
    {
        Frac<T> c(a);
        c *= b;

        return c;
    }

    template<typename T>
    Frac<T> operator/(const Frac<T>& a, const Frac<T>& b)
    {
        Frac<T> c(a);
        c /= b;

        return c;
    }


    template<typename T>
    Frac<T> operator-(const Frac<T>& a)
    {
        return Frac<T>(-a.num(), a.denom());
    }

    template<typename T>
    Frac<T> operator+(const Frac<T>& a)
    {
        return a;
    }


    // Comparaisons

    template<typename T>
    bool operator==(const Frac<T>& a, const Frac<T>& b)
    {
        return a.num() == b.num() && a.denom() == b.denom();
    }

    template<typename T>
    bool operator!=(const Frac<T>& a, const Frac<T>& b)
    {
        return !(a == b);
    }

    template<typename T>
    bool operator>(const Frac<T>& a, const Frac<T>& b)
    {
        return a.num()*b.denom() > b.num()*a.denom();
    }

    template<typename T>
    bool operator<(const Frac<T>& a, const Frac<T>& b)
    {
        return !(a >= b);
    }

    template<typename T>
    bool operator>=(const Frac<T>& a, const Frac<T>& b)
    {
        return a.num()*b.denom() >= b.num()*a.denom();
    }

    template<typename T>
    bool operator<=(const Frac<T>& a, const Frac<T>& b)
    {
        return !(a > b);
    }


    // Affichage

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Frac<T>& a)
    {
        stream << "(" << a.num() << "/" << a.denom() << ")";
        return stream;
    }
    
    template<typename T>
    std::istream& operator>>(std::istream& stream, Frac<T>& a)
    {
        if (!stream)
            return stream;

        T x, y;
        char c;

        stream.get(c);
        if (c != '(')
        {
            if (stream) stream.putback(c);
            stream.setstate(std::ios::failbit);
            return stream;
        }

        stream >> x;
        if (!stream) return stream;

        stream.get(c);
        if (c != '/')
        {
            if (stream) stream.putback(c);
            stream.setstate(std::ios::failbit);
            return stream;
        }

        stream >> y;
        if (!stream) return stream;

        stream.get(c);
        if (c != ')')
        {
            if (stream) stream.putback(c);
            stream.setstate(std::ios::failbit);
            return stream;
        }

        a = Frac<T>(x, y);

        return stream;
    }
}
