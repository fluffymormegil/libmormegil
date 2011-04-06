// libmormegil/s20prng.cc - PRNG using Salsa20 stream cipher
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_S20prng_hh
#define libmormegil_S20prng_hh

#include <stdint.h>

namespace libmormegil
{
    /* An S20prng object holds the state of a Salsa20 stream cipher
     * implementation. */
#define rotl(x, dist) (((x) << (dist)) | ((x) >> (32 - (dist))))
    struct S20prng
    {
        enum {
            Fixed1 = 0x4a409382,
            Fixed2 = 0x2299f31d,
            Fixed3 = 0x0082efa9,
            Fixed4 = 0x8ec4e6c8
        };
        uint32_t state[16];
        uint64_t counter;
        uint32_t key[8];
        uint32_t nonce[2];
        int subcounter;
        void doubleround()
        {
            state[ 4] ^= rotl(state[ 0]+state[12], 7);
            state[ 8] ^= rotl(state[ 4]+state[ 0], 9);
            state[12] ^= rotl(state[ 8]+state[ 4], 13);
            state[ 0] ^= rotl(state[12]+state[ 8], 18);
            state[ 9] ^= rotl(state[ 5]+state[ 1], 7);
            state[13] ^= rotl(state[ 9]+state[ 5], 9);
            state[ 1] ^= rotl(state[13]+state[ 9], 13);
            state[ 5] ^= rotl(state[ 1]+state[13], 18);
            state[14] ^= rotl(state[10]+state[ 6], 7);
            state[ 2] ^= rotl(state[14]+state[10], 9);
            state[ 6] ^= rotl(state[ 2]+state[14], 13);
            state[10] ^= rotl(state[ 6]+state[ 2], 18);
            state[ 3] ^= rotl(state[15]+state[11], 7);
            state[ 7] ^= rotl(state[ 3]+state[15], 9);
            state[11] ^= rotl(state[ 7]+state[ 3], 13);
            state[15] ^= rotl(state[11]+state[ 7], 18);

            state[ 1] ^= rotl(state[ 0]+state[ 3], 7);
            state[ 2] ^= rotl(state[ 1]+state[ 0], 9);
            state[ 3] ^= rotl(state[ 2]+state[ 1], 13);
            state[ 0] ^= rotl(state[ 3]+state[ 2], 18);
            state[ 6] ^= rotl(state[ 5]+state[ 3], 7);
            state[ 7] ^= rotl(state[ 6]+state[ 5], 9);
            state[ 4] ^= rotl(state[ 7]+state[ 6], 13);
            state[ 5] ^= rotl(state[ 4]+state[ 7], 18);
            state[11] ^= rotl(state[10]+state[ 9], 7);
            state[ 8] ^= rotl(state[11]+state[10], 9);
            state[ 9] ^= rotl(state[ 8]+state[11], 13);
            state[10] ^= rotl(state[ 9]+state[ 8], 18);
            state[12] ^= rotl(state[15]+state[14], 7);
            state[13] ^= rotl(state[12]+state[15], 9);
            state[14] ^= rotl(state[13]+state[12], 13);
            state[15] ^= rotl(state[14]+state[13], 18);
        }
        void slash(int n)
        {
            for (int i = 0; i < (n >> 1); ++i)
            {
                doubleround();
            }
        }
        void runstate()
        {
            state[0] = Fixed1;
            state[1] = key[0];
            state[2] = key[1];
            state[3] = key[2];
            state[4] = key[3];
            state[5] = Fixed2;
            state[6] = nonce[0];
            state[7] = nonce[1];
            state[8] = counter;
            state[9] = counter >> 32;
            state[10] = Fixed3;
            state[11] = key[4];
            state[12] = key[5];
            state[13] = key[6];
            state[14] = key[7];
            state[15] = Fixed4;
            slash(12);
        }
        uint32_t generate()
        {
            uint32_t ret;
            if (!subcounter)
            {
                runstate();
                ++counter;
            }
            ret = state[subcounter];
            ++subcounter;
            subcounter &= 15;
            return ret;
        }
        void initialize(const uint32_t *k, const uint32_t *n,
                        const uint64_t *c, const int *s)
        {
            int i;
            for (i = 0; i < 8; ++i)
            {
                key[i] = k[i];
            }
            nonce[0] = n[0];
            nonce[1] = n[1];
            counter = *c;
            subcounter = (*s) & 15;
            if (subcounter)
            {
                runstate();
            }
        }
        void extract_state(uint32_t *k, uint32_t *n, uint64_t *c, int *s) const
        {
            int i;
            for (i = 0; i < 8; ++i)
            {
                k[i] = key[i];
            }
            n[0] = nonce[0];
            n[1] = nonce[1];
            *c = counter;
            *s = subcounter;
        }
    };
}
#endif

// vim:ts=8:sw=4:expandtab:fo=c
// libmormegil/S20prng.hh
