// libmormegil/stlfgets.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#include <stdio.h>
#include <string>

namespace libmormegil
{
    int stlfgets(std::string& str, FILE *fp, size_t size_suggest = 128, size_t hard_size = 0x7fffffff);
    int stlwfgets(std::wstring& str, FILE *fp, size_t size_suggest = 128, size_t hard_size = 0x7fffffff);
}

// vim:ts=8:sw=4:expandtab:fo=croq
