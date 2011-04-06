// libmormegil/sign.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_sign_hh
#define libmormegil_sign_hh

namespace libmormegil
    template<typename T> inline bool sign(const T& i)
    {
        return (i < T(0)) ? -1 : (i > T(0)) ? 1 : 0;
    }
}
#endif // libmormegil_sign_hh

// vim:ts=8:sw=4:expandtab:fo=c
