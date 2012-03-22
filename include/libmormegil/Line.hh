// libmormegil/Line.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2012 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_Line_hh
#define libmormegil_Line_hh

#ifndef libmormegil_Coord_hh
#include <libmormegil/Coord.hh>
#endif

namespace libmormegil
{
    template<typename T> struct basic_line
    {
        typedef basic_line<T>& ref;
        typedef const basic_line<T>& const_ref;
        typedef basic_coord<T> punkt;
        typedef basic_coord<T>& punktref;
        typedef const basic_coord<T>& const_punktref;
        basic_coord<T> topleft;
        basic_coord<T> botright;
    };
    typedef basic_line<int32_t> Line;
    typedef basic_line<int64_t> Line64;
}
#endif // libmormegil_Line_hh

// vim:ts=8:sts=4:sw=4:expandtab:fo=croq
