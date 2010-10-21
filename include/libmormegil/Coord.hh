// libmormegil/Coord.hh
//
// Copyright 2010 Martin Read. All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the author nor the names of any other contributors
//    may be used to endorse or promote products derived from this software
//    without their specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// We need std::max<> and std::min<>. The thing called std::abs<> is in
// <complex> and is intended for use on complex numbers; dude what the fuck?

#ifndef libmormegil_Coord_hh
#define libmormegil_Coord_hh
#include <algorithm>
#include <stdint.h>

#ifndef libmormegil_abs_hh
#include <libmormegil/abs.hh>
#endif

namespace libmormegil
{
    /* Yes, the basic_offset and basic_coord templates do indeed look very
       similar. They are kept distinct, however, as what one might choose
       to call an "insurance policy" - you can't add basic_coord objects
       together. */
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

        ref operator *=(const basic_offset<T>& right)
        {
            y *= right.y;
            x *= right.x;
            return *this;
        }

        bool operator <(const basic_offset<T>& right) const
        {
            return (y < right.y) || ((y == right.y) && (x < right.x));
        }

        bool operator ==(const basic_offset<T>& right) const
        {
            return (y == right.y) && (x == right.x);
        }

        bool operator >(const basic_offset<T>& right) const
        {
            return (y > right.y) || ((y == right.y) && (x > right.x));
        }

        int length_taxi() { return abs(y) + abs(x); }
        int lengthsq() { return y * y + x * x; }
        int length_inf() { return std::min(abs(y), abs(x)); }
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

    typedef basic_offset<int32_t> Offset;
    typedef basic_coord<int32_t> Coord;
    typedef basic_offset<int64_t> Offset64;
    typedef basic_coord<int64_t> Coord64;
}
#endif // libmormegil_Coord_hh

// vim:ts=8:sw=4:expandtab:fo=c
