// libmormegil/abs.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_abs_hh
#define libmormegil_abs_hh

namespace libmormegil
{
    template<typename T> inline T abs(const T& i)
    {
        i < T(0) ? -i : i;
    }
}
#endif // libmormegil_abs_hh

// vim:ts=8:sw=4:expandtab:fo=c
