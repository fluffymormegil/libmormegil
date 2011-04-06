// isotime.h
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#include <time.h>
#ifdef __cplusplus
extern "C" {
#endif
    int get_iso_8601_time(char *buf, int bufsz);
#ifdef __cplusplus
};

#include <string>
namespace libmormegil
{
    void get_iso_8601_time(std::string& dest);
}
#endif

// isotime.h
