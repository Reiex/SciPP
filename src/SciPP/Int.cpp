#include <SciPP/SciPP.hpp>

namespace scp
{
    namespace
    {
        const uint64_t CAPACITY = 1ULL << 32;
        const uint64_t MAX = CAPACITY - 1;
    }

    // Constructors

    Int::Int() :
        _values(1, 0),
        _sign(true)
    {
    }

    Int::Int(int64_t x) :
        _sign(x >= 0)
    {
        if (!_sign)
            x = -x;

        int64_t y = x / CAPACITY;
        uint64_t size = y == 0 ? 1: 2;

        _values.resize(size);
        _values[0] = x % CAPACITY;
        if (size == 2)
            _values[1] = y;
    }


    // Intern operators

    Int& Int::operator+=(const Int& x)
    {
        if (_sign == x._sign)
        {
            uint64_t buffer;
            uint64_t size;

            // Determiner la taille de l'Int

            if (_values.size() > x._values.size())
            {
                uint64_t i(_values.size() - 1);
                size = _values.size();
                while (i >= x._values.size() && _values[i] == MAX)
                    i--;

                if (i == x._values.size() - 1)
                {
                    buffer = _values[i] + x._values[i];
                    while (buffer >= MAX)
                    {
                        if (buffer >= CAPACITY)
                        {
                            size = _values.size() + 1;
                            break;
                        }

                        i--;
                        if (i < 0)
                            break;
                        else
                            buffer = _values[i] + x._values[i];
                    }
                }
            }
            else if (_values.size() < x._values.size())
            {
                uint64_t i(x._values.size() - 1);
                size = x._values.size();
                while (i >= _values.size() && x._values[i] == MAX)
                    i--;

                if (i == _values.size() - 1)
                {
                    buffer = _values[i] + x._values[i];
                    while (buffer >= MAX)
                    {
                        if (buffer >= CAPACITY)
                        {
                            size = _values.size() + 1;
                            break;
                        }

                        i--;
                        if (i < 0)
                            break;
                        else
                            buffer = _values[i] + x._values[i];
                    }
                }
            }
            else
            {
                uint64_t i(_values.size() - 1);
                buffer = _values[i] + x._values[i];
                size = _values.size();
                while (buffer >= MAX)
                {
                    if (buffer >= CAPACITY)
                    {
                        size = _values.size() + 1;
                        break;
                    }

                    i--;
                    if (i < 0)
                        break;
                    else
                        buffer = _values[i] + x._values[i];
                }
            }

            // Allouer un nouvel espace memoire si necessaire

            if (size != _values.size())
                _values.resize(size);

            // Faire la somme elle-meme

            buffer = 0;
            for (uint64_t i(0); i < size; i++)
            {
                if (i < _values.size())
                    buffer += _values[i];
                if (i < x._values.size())
                    buffer += x._values[i];
                _values[i] = buffer % CAPACITY;
                buffer >>= 32;
            }
        }
        else
        {
            _sign = !_sign;
            *this -= x;
            _sign = !_sign;
        }

        return *this;
    }

    Int& Int::operator-=(const Int& x)
    {
        if (_sign == x._sign)
        {
            std::vector<uint32_t> grand, petit;
            uint64_t grandeTaille, petiteTaille;

            if (*this == x)
            {
                _values.clear();
                _values.resize(1, 0);
                _sign = true;

                return *this;
            }

            if ((_sign && *this > x) || (!_sign && *this < x))
            {
                grand = _values;
                grandeTaille = _values.size();
                petit = x._values;
                petiteTaille = x._values.size();
            }
            else
            {
                grand = x._values;
                grandeTaille = x._values.size();
                petit = _values;
                petiteTaille = _values.size();
                _sign = !_sign;
            }

            uint64_t taille(grandeTaille);
            if (grandeTaille == petiteTaille)
                while (grand[taille - 1] == petit[taille - 1] && taille > 1)
                    taille--;

            _values.resize(taille);

            for (uint64_t i(taille - 1); i != UINT64_MAX; i--)
            {
                _values[i] = grand[i];
                if (i < petiteTaille)
                {
                    if (grand[i] >= petit[i])
                    {
                        _values[i] -= petit[i];
                    }
                    else
                    {
                        _values[i] += CAPACITY - petit[i];
                        uint64_t j(1);
                        while (_values[i + j] == 0)
                            j++;
                        _values[i + j]--;
                        for (uint64_t k(1); k < j; k++)
                            _values[i + k] = MAX;
                    }
                }
            }

            if (_values[_values.size() - 1] == 0)
                _values.resize(_values.size() - 1);
        }
        else
        {
            _sign = !_sign;
            *this += x;
            _sign = !_sign;
        }

        return *this;
    }

    Int& Int::operator*=(const Int& x)
    {
        if (*this == 0 || x == 0)
        {
            _values.clear();
            _values.resize(1, 0);
            _sign = true;
        }
        else
        {
            uint64_t buffer;
            std::vector<uint32_t> tmp(_values.size() + x._values.size(), 0);
            for (uint64_t i(0); i < _values.size(); i++)
            {
                buffer = 0;
                for (uint64_t j(0); j < x._values.size(); j++)
                {
                    buffer += (uint64_t) _values[i] * (uint64_t) x._values[j];
                    buffer += tmp[i + j];
                    tmp[i + j] = buffer % CAPACITY;
                    buffer >>= 32;
                }
                tmp[i + x._values.size()] = buffer;
            }

            uint64_t taille(_values.size() + x._values.size());
            while (tmp[taille - 1] == 0)
                taille--;

            _sign = (_sign == x._sign);
            _values.resize(taille);
            for (int i(0); i < taille; i++)
                _values[i] = tmp[i];
        }

        return *this;
    }

    uint64_t getNbBits(uint32_t x)
    {
        uint64_t i(0);
        while (x != 0)
        {
            x >>= 1;
            i++;
        }

        return i;
    }

    Int& Int::operator/=(const Int& x)
    {
        if (x == 0)
            throw std::runtime_error(scippError("Division of Int by 0."));

        uint64_t tailleBits((_values.size() - 1) * 32 + getNbBits(_values[_values.size() - 1]));
        uint64_t xTailleBits((x._values.size() - 1) * 32 + getNbBits(x._values[x._values.size() - 1]));

        if (xTailleBits > tailleBits || *this == 0)
        {
            _values.clear();
            _values.resize(1, 0);
            _sign = true;

            return *this;
        }

        uint64_t taille((tailleBits - xTailleBits + 1) / 32 + ((tailleBits - xTailleBits + 1) % 32 != 0));
        std::vector<uint32_t> newValues(taille, 0);

        for (uint64_t i(tailleBits - xTailleBits); i != UINT64_MAX; i--)
        {
            bool soustrairePossible(true);
            uint8_t bitA, bitB;
            uint64_t k;
            if (i != tailleBits - xTailleBits && (_values[(i + xTailleBits) >> 5] >> ((i + xTailleBits) % 32)) % 2)
            {
                soustrairePossible = true;
            }
            else
            {
                for (uint64_t j(xTailleBits - 1); j != UINT64_MAX; j--)
                {
                    bitA = (x._values[j >> 5] >> (j % 32)) % 2;
                    bitB = (_values[(i + j) >> 5] >> ((i + j) % 32)) % 2;

                    if (bitA < bitB)
                    {
                        soustrairePossible = true;
                        break;
                    }
                    else if (bitA > bitB)
                    {
                        soustrairePossible = false;
                        break;
                    }
                }
            }

            if (soustrairePossible)
            {
                for (uint64_t j(xTailleBits - 1); j != UINT64_MAX; j--)
                {
                    k = i + j;
                    bitA = (x._values[j >> 5] >> (j % 32)) % 2;
                    bitB = (_values[k >> 5] >> (k % 32)) % 2;
                    if (bitA && bitB)
                        _values[k >> 5] -= 1 << (k % 32);
                    else if (bitA && !bitB)
                    {
                        uint64_t l(1);
                        while (!((_values[(k + l) >> 5] >> ((k + l) % 32)) % 2))
                            l++;
                        _values[(k + l) >> 5] -= 1 << ((k + l) % 32);
                        l--;
                        while (l != UINT64_MAX)
                        {
                            _values[(k + l) >> 5] += 1 << ((k + l) % 32);
                            l--;
                        }
                    }
                }

                newValues[i >> 5] += 1 << (i % 32);
            }
        }

        _sign = (_sign == x._sign);
        _values = newValues;

        return *this;
    }

    Int& Int::operator%=(const Int& x)
    {
        *this -= (*this / x) * x;
        return *this;
    }


    // Specific methods

    std::string Int::toString() const
    {
        std::stringstream stream;
        stream << *this;

        return stream.str();
    }

    int64_t Int::toInt() const
    {
        if (*this > INT64_MAX || *this < INT64_MIN)
            throw std::runtime_error("Int to big to be converted to int64_t.");

        int64_t x(0);

        for (int64_t i(_values.size() - 1); i >= 0; i--)
        {
            x <<= 32;
            x += _values[i];
        }

        if (!_sign)
            x = -x;

        return x;
    }

    void Int::setSign(bool sign)
    {
        if (*this != 0)
            _sign = sign;
    }

    bool Int::getSign() const
    {
        return _sign;
    }

    // Extern operators

    Int operator+(const Int& x, const Int& y)
    {
        Int z(x);
        z += y;
        return z;
    }

    Int&& operator+(Int&& x, const Int& y)
    {
        x += y;
        return std::move(x);
    }

    Int&& operator+(const Int& x, Int&& y)
    {
        y += x;
        return std::move(y);
    }

    Int&& operator+(Int&& x, Int&& y)
    {
        x += y;
        return std::move(x);
    }


    Int operator-(const Int& x, const Int& y)
    {
        Int z(x);
        z -= y;
        return z;
    }

    Int&& operator-(Int&& x, const Int& y)
    {
        x -= y;
        return std::move(x);
    }

    Int&& operator-(const Int& x, Int&& y)
    {
        y -= x;
        return -std::move(y);
    }

    Int&& operator-(Int&& x, Int&& y)
    {
        x -= y;
        return std::move(x);
    }


    Int operator*(const Int& x, const Int& y)
    {
        Int z(x);
        z *= y;
        return z;
    }

    Int&& operator*(Int&& x, const Int& y)
    {
        x *= y;
        return std::move(x);
    }

    Int&& operator*(const Int& x, Int&& y)
    {
        y *= x;
        return std::move(y);
    }

    Int&& operator*(Int&& x, Int&& y)
    {
        x *= y;
        return std::move(x);
    }


    Int operator/(const Int& x, const Int& y)
    {
        Int z(x);
        z /= y;
        return z;
    }

    Int&& operator/(Int&& x, const Int& y)
    {
        x /= y;
        return std::move(x);
    }

    Int&& operator/(Int&& x, Int&& y)
    {
        x /= y;
        return std::move(x);
    }


    Int operator%(const Int& x, const Int& y)
    {
        Int z(x);
        z %= y;
        return z;
    }

    Int&& operator%(Int&& x, const Int& y)
    {
        x %= y;
        return std::move(x);
    }

    Int&& operator%(Int&& x, Int&& y)
    {
        x %= y;
        return std::move(x);
    }


    Int operator-(const Int& x)
    {
        Int y(x);
        y.setSign(!y.getSign());

        return y;
    }

    Int&& operator-(Int&& x)
    {
        x.setSign(!x.getSign());
        return std::move(x);
    }

    Int operator+(const Int& x)
    {
        return x;
    }

    Int&& operator+(Int&& x)
    {
        return std::move(x);
    }


    // Comparators

    bool operator==(const Int& x, const Int& y)
    {
        if (x._values.size() != y._values.size())
            return false;

        if (x._sign != y._sign)
            return false;

        for (uint64_t i(x._values.size() - 1); i != UINT64_MAX; i--)
            if (x._values[i] != y._values[i])
                return false;

        return true;
    }

    bool operator!=(const Int& x, const Int& y)
    {
        return !(x == y);
    }

    bool operator>(const Int& x, const Int& y)
    {
        if (x._sign != y._sign)
            return x._sign;

        if (x._values.size() != y._values.size())
            return (x._sign == (x._values.size() > y._values.size()));

        for (uint64_t i(x._values.size() - 1); i != UINT64_MAX; i--)
            if (x._values[i] != y._values[i])
                return (x._sign == (x._values[i] > y._values[i]));

        return false;
    }

    bool operator<(const Int& x, const Int& y)
    {
        return !(x >= y);
    }

    bool operator>=(const Int& x, const Int& y)
    {
        if (x._sign != y._sign)
            return x._sign;

        if (x._values.size() != y._values.size())
            return (x._sign == (x._values.size() > y._values.size()));

        for (uint64_t i(x._values.size() - 1); i != UINT64_MAX; i--)
            if (x._values[i] != y._values[i])
                return (x._sign == (x._values[i] > y._values[i]));

        return true;
    }

    bool operator<=(const Int& x, const Int& y)
    {
        return !(x > y);
    }


    // Display

    std::ostream& operator<<(std::ostream& stream, const Int& x)
    {
        if (x == 0)
        {
            stream << "0";
            return stream;
        }

        Int p(1), y(x);
        if (x < 0)
        {
            stream << "-";
            y = -x;
        }

        while (p <= y)
            p *= 10;
        p /= 10;
        while (p > 0)
        {
            stream << int((y / p)._values[0]);
            y %= p;
            p /= 10;
        }

        return stream;
    }

    std::istream& operator>>(std::istream& stream, Int& x)
    {
        if (!stream)
            return stream;

        Int y(0);

        char c;

        stream.get(c);
        if (c < 48 || c > 57)
        {
            stream.putback(c);
            stream.setstate(std::ios::failbit);
            return stream;
        }

        while (stream)
        {
            switch (c)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                y = 10 * y + Int((int)c - 48);
                break;
            default:
                x = y;
                stream.putback(c);
                return stream;
            }
            stream.get(c);
        }
        return stream;
    }


    // Specific functions
    
    Int binom(const Int& n, const Int& p)
    {
        if (p > n || p < 0)
            return 0;

        Int num(1), denom(1);

        for (Int i(0); i < p; i += 1)
        {
            num *= n - i;
            denom *= p - i;
        }

        return num / denom;
    }
}
