// libmormegil/divup.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_divup_hh
#define libmormegil_divup_hh

namespace libmormegil
{
    // TODO - use type traits to select an implementation.
    // TODO - do we want overflow checking or is that fairly the user's
    // problem?
    template<typename T> inline T divup(const T& i, const T& j)
    {
        return i + (j - 1) / j;
    }
}
#endif // libmormegil_abs_hh

// vim:ts=8:sw=4:expandtab:fo=c
