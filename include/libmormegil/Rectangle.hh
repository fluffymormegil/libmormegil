// libmormegil/Rectangle.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

// We need std::max<> and std::min<>. The thing called std::abs<> is in
// <complex> and is intended for use on complex numbers only; did I mention I
// hate the standards committee sometimes?

#ifndef libmormegil_Rectangle_hh
#define libmormegil_Rectangle_hh

#ifndef libmormegil_Coord_hh
#include <libmormegil/Coord.hh>
#endif

namespace libmormegil
{
    template<typename T> struct basic_rectangle
    {
        typedef basic_rectangle<T>& ref;
        typedef const basic_rectangle<T>& const_ref;
        typedef basic_coord<T> punkt;
        typedef basic_coord<T>& punktref;
        typedef const basic_coord<T>& const_punktref;
        basic_coord<T> topleft;
        basic_coord<T> botright;
        T area() const { return (botright.y + 1 - topleft.y) * (botright.x + 1 - topleft.x); }
        T topedge() const { return topleft.y; }
        T bottomedge() const { return botright.y; }
        T leftedge() const { return topleft.x; }
        T rightedge() const { return botright.x; }
        bool is_square() const
        {
            return (botright.y - topleft.y) == (botright.x - topleft.x);
        }
        bool contains(const_punktref p) const
        {
            return (p.y >= topleft.y) && (p.x >= topleft.x) && (p.y <= botright.y) && (p.x <= botright.x);
        }
        T hdist(const_ref other) const
        {
            if (leftedge() > other.rightedge())
            {
                return leftedge() - other.rightedge();
            }
            else if (rightedge() < other.leftedge())
            {
                return other.leftedge() - rightedge();
            }
            else
            {
                return 0;
            }
        }
        T vdist(const_ref other) const
        {
            if (topedge() > other.bottomedge())
            {
                return topedge() - other.bottomedge();
            }
            else if (bottomedge() < other.topedge())
            {
                return other.topedge() - bottomedge();
            }
            else
            {
                return 0;
            }
        }
        T mindist_taxi(const_ref other) const
        {
            T h = hdist(other), v = vdist(other);
            return h + v;
        }
        T mindistsq(const_ref other) const
        {
            T h = hdist(other), v = vdist(other);
            return h * h + v * v;
        }
        T mindist_inf(const_ref other) const
        {
            T h = hdist(other), v = vdist(other);
            return std::max(h, v);
        }
    };
    typedef basic_rectangle<int32_t> Rectangle;
    typedef basic_rectangle<int64_t> Rectangle64;
}
#endif // libmormegil_Rectangle_hh

// vim:ts=8:sts=4:sw=4:expandtab:fo=croq
