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
    std::string *tagify(const char *name, const char *prefix);
    // By default, the generated path is not namespaced.  Please note that this
    // function has no bounds checks and no return value; it's your job to pass
    // it sensible strings and FILE * objects, and to close them when you're
    // done. It has default arguments for damage limitation.
    void emit_chebyshev_spiral(FILE *srcfile = stdout, FILE *hdrfile = stdout, unsigned int radius = 10,
                              const char *macrotag = "cheby_spiral", const char *nmsp = 0);
}

// vim:ts=8:sw=4:expandtab:fo=croq
