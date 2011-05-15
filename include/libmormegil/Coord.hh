// libmormegil/Coord.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

// We need std::max<> and std::min<>. The thing called std::abs<> is in
// <complex> and is intended for use on complex numbers only; did I mention I
// hate the standards committee sometimes?

#ifndef libmormegil_Coord_hh
#define libmormegil_Coord_hh
#include <algorithm>
#include <stdint.h>

#ifndef libmormegil_mathops_hh
#include <libmormegil/mathops.hh>
#endif

namespace libmormegil
{
    // Yes, the basic_offset and basic_coord templates do indeed look very
    // similar. They are kept distinct, however, as what one might choose
    // to call an "insurance policy" - you can't add two basic_coord objects
    // together.
    template<typename T> struct basic_offset
    {
        typedef basic_offset<T>& ref;
        typedef const basic_offset<T>& const_ref;
        int y;
        int x;
        ref operator +=(const_ref right)
        {
            y += right.y;
            x += right.x;
            return *this;
        }

        ref operator -=(const_ref right)
        {
            y -= right.y;
            x -= right.x;
            return *this;
        }

        ref operator *=(const_ref right)
        {
            y *= right.y;
            x *= right.x;
            return *this;
        }

        basic_offset<T> operator -() const
        {
            basic_offset<T> tmp = { -y, -x };
            return tmp;
        }


        bool operator <(const_ref right) const
        {
            return (y < right.y) || ((y == right.y) && (x < right.x));
        }

        bool operator ==(const_ref right) const
        {
            return (y == right.y) && (x == right.x);
        }

        bool operator !=(const_ref right) const
        {
            return (y != right.y) || (x != right.x);
        }

        bool operator >(const_ref right) const
        {
            return (y > right.y) || ((y == right.y) && (x > right.x));
        }

        int length_taxi() const { return abs(y) + abs(x); }
        int lengthsq() const { return y * y + x * x; }
        int length_inf() const { return std::max(abs(y), abs(x)); }
        bool cardinal() const { return (abs(y) == abs(x)) || (y && !x) || (x && !y); }
    };

    template<typename T> struct basic_coord
    {
        typedef basic_coord<T>& ref;
        typedef const basic_coord<T>& const_ref;
        int y;
        int x;
        ref operator +=(const basic_offset<T>& right)
        {
            y += right.y;
            x += right.x;
            return *this;
        }
        ref operator -=(const basic_offset<T>& right)
        {
            y -= right.y;
            x -= right.x;
            return *this;
        }
        ref operator *=(const basic_offset<T>& right)
        {
            y *= right.y;
            x *= right.x;
            return *this;
        }
        basic_offset<T> operator -(const_ref right) const
        {
            basic_offset<T> tmp = { y - right.y, x - right.x };
            return tmp;
        }
        bool operator <(const_ref right) const
        {
            return (y < right.y) || ((y == right.y) && (x < right.x));
        }

        bool operator ==(const_ref right) const
        {
            return (y == right.y) && (x == right.x);
        }

        bool operator !=(const_ref right) const
        {
            return (y != right.y) || (x != right.x);
        }

        basic_coord<T> operator -() const
        {
            basic_coord<T> tmp = { -y, -x };
            return tmp;
        }

        bool operator >(const_ref right) const
        {
            return (y > right.y) || ((y == right.y) && (x > right.x));
        }

        int dist_taxi(const_ref right) const
        {
            return abs(y - right.y) + abs(x - right.x);
        }
        int distsq(const_ref right) const
        {
            return ((y - right.y) * (y - right.y) +
                    (x - right.x) * (x - right.x));
        }
        int dist_inf(const_ref right) const
        {
            return std::max(abs(y - right.y), abs(x - right.x));
        }
        int size_taxi() const
        {
            return abs(y) + abs(x);
        }
        int sizesq() const
        {
            return y * y + x * x;
        }
        int size_inf() const
        {
            return std::max(abs(y), abs(x));
        }
    };
    template<typename T> inline basic_coord<T> operator +(const basic_coord<T>& left, const basic_offset<T>& right)
    {
        basic_coord<T> tmp = { left.y + right.y, left.x + right.x };
        return tmp;
    }
    template<typename T> inline basic_coord<T> operator -(const basic_coord<T>& left, const basic_offset<T>& right)
    {
        basic_coord<T> tmp = { left.y - right.y, left.x - right.x };
        return tmp;
    }

    typedef basic_offset<int32_t> Offset;
    typedef basic_coord<int32_t> Coord;
    typedef basic_offset<int64_t> Offset64;
    typedef basic_coord<int64_t> Coord64;
    
    template<> inline Offset abs<Offset>(const Offset& t)
    {
        Offset tmp = { abs(t.y), abs(t.x) };
        return tmp;
    }
    template<> inline Offset64 abs<Offset64>(const Offset64& t)
    {
        Offset64 tmp = { abs(t.y), abs(t.x) };
        return tmp;
    }
    template<> inline Coord abs<Coord>(const Coord& t)
    {
        Coord tmp = { abs(t.y), abs(t.x) };
        return tmp;
    }
    template<> inline Coord64 abs<Coord64>(const Coord64& t)
    {
        Coord64 tmp = { abs(t.y), abs(t.x) };
        return tmp;
    }
    template<> inline Offset sign<Offset>(const Offset& t)
    {
        Offset tmp = { sign(t.y), sign(t.x) };
        return tmp;
    }
    template<> inline Offset64 sign<Offset64>(const Offset64& t)
    {
        Offset64 tmp = { sign(t.y), sign(t.x) };
        return tmp;
    }
    template<> inline Coord sign<Coord>(const Coord& t)
    {
        Coord tmp = { sign(t.y), sign(t.x) };
        return tmp;
    }
    template<> inline Coord64 sign<Coord64>(const Coord64& t)
    {
        Coord64 tmp = { sign(t.y), sign(t.x) };
        return tmp;
    }
}
#endif // libmormegil_Coord_hh

// vim:ts=8:sw=4:expandtab:fo=croq
