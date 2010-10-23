// dice-test.cc
//
// Copyright 2010 Martin Read. All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the author nor the names of any other contributors
//    may be used to endorse or promote products derived from this software
//    without their specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <libmormegil/dice.h>

uint32_t keybuf[8];
uint32_t nonce[2];

int main()
{
    int fd;
    /* INITIALIZATION: Open the system (pseudo-)random number generator
     * device. */
    fd = open("/dev/urandom", O_RDONLY, 0);
    if (fd < 0)
    {
        perror("S20prng-test: can't open /dev/urandom");
        return 1;
    }

    int i = 0;
    int testroll;
    uint64_t counter = 0;
    int rolls[11];

    /* INITIALIZATION: Read data to use as the "key" and "nonce" from the
     * file descriptor previously obtained. */
    read(fd, keybuf, sizeof keybuf);
    read(fd, nonce, sizeof nonce);
    /* INITIALIZATION: Load the generator. */
    dice_setstate(keybuf, nonce, &counter, &i);
    /* INITIALIZATION: Clear the "rolls" array. */
    for (i = 0; i < 11; ++i)
    {
        rolls[i] = 0;
    }
    /* Roll 2d6 a million times and record the results. */
    for (i = 0; i < 1000000; ++i)
    {
        testroll = dice(2, 6);
        /* Bounds-check the result */
        if ((testroll < 2) || (testroll > 12))
        {
            fprintf(stderr, "S20prng-test: FAIL: 2d6 roll came up %d\n", testroll);
            return 2;
        }
        rolls[testroll - 2]++;
    }
    /* Print out the results. You'll notice that this doesn't actually test
     * the randomness of the results, just lets you visually inspect the
     * distribution. For reference, the ideal distribution is roughly: 
     *    2:  27777
     *    3:  55555
     *    4:  83333
     *    5: 111111
     *    6: 138888
     *    7: 166666
     *    8: 138888
     *    9: 111111
     *   10:  83333
     *   11:  55555
     *   12:  27777
     */
    for (i = 0; i < 11; ++i)
    {
        printf("%d: %d times\n", i + 2, rolls[i]);
    }
    return 0;
}

// vim:ts=8:sw=4:expandtab:fo=cq
// dice-test.cc
