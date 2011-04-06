// libmormegil/dice.h
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_dice_h
#define libmormegil_dice_h

#include <stdint.h>
// this function is pitched at C99 users.

#ifdef __cplusplus
extern "C" {
#endif
extern int dice(int count, int sides);
extern void dice_setstate(const uint32_t *key, const uint32_t *nonce, const uint64_t *counter, const int *subcounter);
extern void dice_getstate(uint32_t *key, uint32_t *nonce, uint64_t *counter, int *subcounter);
#ifdef __cplusplus
};
#endif
#endif // libmormegil_dice_h

// vim:ts=8:sw=4:expandtab:fo=c
