#pragma once

#include <SciPP/Polynomial.hpp>

namespace scp
{
    // Static attributes

    template<typename T>
    const Polynomial<T> Polynomial<T>::X({T(0), T(1)});


    // Constructors

    template<typename T>
    Polynomial<T>::Polynomial() :
        _coeffs(1, 0)
    {
    }

    template<typename T>
    Polynomial<T>::Polynomial(int64_t x) :
        _coeffs(1, x)
    {
    }
    
    template<typename T>
    Polynomial<T>::Polynomial(const T& x) :
        _coeffs(1, x)
    {
    }
    
    template<typename T>
    Polynomial<T>::Polynomial(const std::vector<T>& values) :
        _coeffs(values)
    {
        if (values.size() == 0)
            _coeffs = { 0 };
        reduce();
    }
    

    // Accessors

    template<typename T>
    T& Polynomial<T>::operator[](uint64_t i)
    {
        if (i >= _coeffs.size())
            _coeffs.resize(i + 1, 0);

        return _coeffs[i];
    }
    
    template<typename T>
    const T& Polynomial<T>::operator[](uint64_t i) const
    {
        if (i >= _coeffs.size())
            _coeffs.resize(i + 1, 0);

        return _coeffs[i];
    }
    

    // Internal operators

    template<typename T>
    Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& p)
    {
        if (p._coeffs.size() > _coeffs.size())
            _coeffs.resize(p._coeffs.size(), 0);
        
        for (uint64_t i(0); i < p._coeffs.size(); i++)
            _coeffs[i] += p._coeffs[i];
        
        reduce();

        return *this;
    }
    
    template<typename T>
    Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& p)
    {
        if (p._coeffs.size() > _coeffs.size())
            _coeffs.resize(p._coeffs.size(), 0);
        
        for (uint64_t i(0); i < p._coeffs.size(); i++)
            _coeffs[i] -= p._coeffs[i];
        
        reduce();

        return *this;
    }
    
    template<typename T>
    Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& p)
    {
        if (p == Polynomial<T>(T(0)) || *this == Polynomial<T>(T(0)))
        {
            _coeffs = {0};
            return *this;
        }

        std::vector<T> coeffs(_coeffs.size() + p._coeffs.size() - 1, 0);
        for (uint64_t i(_coeffs.size() - 1); i != UINT64_MAX; i--)
            for (uint64_t j(p._coeffs.size() - 1); j != UINT64_MAX; j--)
                coeffs[i + j] += _coeffs[i] * p._coeffs[j];

        _coeffs = coeffs;
        
        reduce();

        return *this;
    }
    
    template<typename T>
    Polynomial<T>& Polynomial<T>::operator/=(const Polynomial<T>& p)
    {
        if (p == Polynomial<T>(T(0)))
            throw std::runtime_error("Cannot divide Polynomial by 0.");
        
        if (p.degree() > degree())
        {
            _coeffs = {0};
            return *this;
        }

        std::vector<T> coeffs(_coeffs.size() - p._coeffs.size() + 1, 0);
        uint64_t offset = p._coeffs.size() - 1;
        for (uint64_t i(coeffs.size() - 1); i != UINT64_MAX; i--)
        {
            coeffs[i] = _coeffs[i + offset] / p._coeffs[p._coeffs.size() - 1];
            for (uint64_t j(0); j < p._coeffs.size(); j++)
                _coeffs[i + j] -= coeffs[i] * p._coeffs[j];
        }

        _coeffs = coeffs;
        
        reduce();

        return *this;
    }
    
    template<typename T>
    Polynomial<T>& Polynomial<T>::operator%=(const Polynomial<T>& p)
    {
        if (p == Polynomial<T>(T(0)))
            throw std::runtime_error("Cannot divide Polynomial by 0.");
        
        if (p.degree() > degree())
            return *this;

        uint64_t offset = p._coeffs.size() - 1;
        for (uint64_t i(_coeffs.size() - p._coeffs.size()); i != UINT64_MAX; i--)
        {
            T c(_coeffs[i + offset] / p._coeffs[p._coeffs.size() - 1]);
            for (uint64_t j(0); j < p._coeffs.size(); j++)
                _coeffs[i + j] -= c * p._coeffs[j];
        }
        
        reduce();

        return *this;
    }
    

    // Call operators

    template<typename T>
    T Polynomial<T>::operator()(const T& x) const
    {
        reduce();

        T y(0);
        for (uint64_t i(_coeffs.size() - 1); i != UINT64_MAX; i--)
            y = _coeffs[i] + y * x;
        
        return y;
    }


    // Specific methods

    template<typename T>
    uint64_t Polynomial<T>::degree() const
    {
        reduce();

        return _coeffs.size() - 1;
    }
    
    template<typename T>
    Polynomial<T> Polynomial<T>::derivative() const
    {
        reduce();

        std::vector<T> coeffs(_coeffs.size() - 1, 0);
        for (uint64_t i(0); i < coeffs.size(); i++)
            coeffs[i] = _coeffs[i+1] * (i+1);
        
        return Polynomial<T>(coeffs);
    }
    
    template<typename T>
    Polynomial<T> Polynomial<T>::primitive(T const& c) const
    {
        reduce();

        std::vector<T> coeffs(_coeffs.size() + 1, c);
        for (uint64_t i(1); i < coeffs.size(); i++)
            coeffs[i] = _coeffs[i-1] / i;
        
        return Polynomial<T>(coeffs);
    }


    // Private members

    template<typename T>
    void Polynomial<T>::reduce() const
    {
        uint64_t size = _coeffs.size();
        while (_coeffs[size - 1] == 0 && size > 1)
            size--;
        
        if (size != _coeffs.size())
        {
            if (size == 0)
                _coeffs = {0};
            else
                _coeffs.resize(size);
        }
    }


    // External operators

    template<typename T>
    Polynomial<T> operator+(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        Polynomial<T> r(p);
        r += q;

        return r;
    }

    template<typename T>
    Polynomial<T>&& operator+(Polynomial<T>&& p, const Polynomial<T>& q)
    {
        p += q;
        return std::move(p);
    }
    
    template<typename T>
    Polynomial<T>&& operator+(const Polynomial<T>& p, Polynomial<T>&& q)
    {
        q += p;
        return std::move(q);
    }
    
    template<typename T>
    Polynomial<T>&& operator+(Polynomial<T>&& p, Polynomial<T>&& q)
    {
        p += q;
        return std::move(p);
    }
    

    template<typename T>
    Polynomial<T> operator-(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        Polynomial<T> r(p);
        r -= q;

        return r;
    }
    
    template<typename T>
    Polynomial<T>&& operator-(Polynomial<T>&& p, const Polynomial<T>& q)
    {
        p -= q;
        return std::move(p);
    }
    
    template<typename T>
    Polynomial<T>&& operator-(const Polynomial<T>& p, Polynomial<T>&& q)
    {
        q -= p;
        return -std::move(q);
    }
    
    template<typename T>
    Polynomial<T>&& operator-(Polynomial<T>&& p, Polynomial<T>&& q)
    {
        p -= q;
        return std::move(p);
    }
    

    template<typename T>
    Polynomial<T> operator*(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        Polynomial<T> r(p);
        r *= q;

        return r;
    }
    
    template<typename T>
    Polynomial<T>&& operator*(Polynomial<T>&& p, const Polynomial<T>& q)
    {
        p *= q;
        return std::move(p);
    }
    
    template<typename T>
    Polynomial<T>&& operator*(const Polynomial<T>& p, Polynomial<T>&& q)
    {
        q *= p;
        return std::move(q);
    }
    
    template<typename T>
    Polynomial<T>&& operator*(Polynomial<T>&& p, Polynomial<T>&& q)
    {
        p *= q;
        return std::move(p);
    }
    

    template<typename T>
    Polynomial<T> operator/(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        Polynomial<T> r(p);
        r /= q;

        return r;
    }
    
    template<typename T>
    Polynomial<T>&& operator/(Polynomial<T>&& p, const Polynomial<T>& q)
    {
        p /= q;
        return std::move(p);
    }
    
    template<typename T>
    Polynomial<T>&& operator/(Polynomial<T>&& p, Polynomial<T>&& q)
    {
        p /= q;
        return std::move(p);
    }
    

    template<typename T>
    Polynomial<T> operator%(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        Polynomial<T> r(p);
        r %= q;

        return r;
    }
    
    template<typename T>
    Polynomial<T>&& operator%(Polynomial<T>&& p, const Polynomial<T>& q)
    {
        p %= q;
        return std::move(p);
    }
    
    template<typename T>
    Polynomial<T>&& operator%(Polynomial<T>&& p, Polynomial<T>&& q)
    {
        p %= q;
        return std::move(p);
    }


    template<typename T>
    Polynomial<T> operator-(const Polynomial<T>& p)
    {
        Polynomial<T> q;
        for (uint64_t i(0); i <= p.degree(); i++)
            q[i] = -p[i];
        
        return q;
    }

    template<typename T>
    Polynomial<T>&& operator-(Polynomial<T>&& p)
    {
        for (uint64_t i(0); i <= p.degree(); i++)
            p[i] = -p[i];
        
        return std::move(p);
    }


    template<typename T>
    Polynomial<T> operator+(const Polynomial<T>& p)
    {
        return p;
    }

    template<typename T>
    Polynomial<T>&& operator+(Polynomial<T>&& p)
    {
        return std::move(p);
    }


    // Comparators

    template<typename T>
    bool operator==(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        if (p.degree() != q.degree())
            return false;
        
        for (uint64_t i(0); i <= p.degree(); i++)
            if (p[i] != q[i])
                return false;
        
        return true;
    }

    template<typename T>
    bool operator!=(const Polynomial<T>& p, const Polynomial<T>& q)
    {
        return !(p == q);
    }
    

    // Display

    template<typename T>
    std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& p)
    {
        for (uint64_t i(0); i <= p.degree(); i++)
            if (i == p.degree())
                stream << p[i];
            else
                stream << p[i] << " ";

        return stream;
    }
}
