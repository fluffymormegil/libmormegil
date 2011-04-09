// libmormegil/stlwprintf.hh - (v)sprintf-for-STL-strings
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_stlprintf_hh
#define libmormegil_stlprintf_hh
#include <stdarg.h>
#include <string>

namespace libmormegil
{
    extern std::wstring vstlwprintf(const wchar_t *fmt, va_list args);
    extern std::wstring stlwprintf(const wchar_t *fmt, ...);
}
#endif

// vim:ts=8:sw=4:fo=croq
// libmormegil/stlwprintf.hh
