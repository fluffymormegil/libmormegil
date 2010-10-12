// dice.cc
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

#include <stdint.h>
#include <string.h>
#include <libmormegil/dice.h>
#include <libmormegil/S20prng.hh>

libmormegil::S20prng dice_generator;

extern "C" int dice(int count, int sides)
{
    int value = 0;
    unsigned divisor;
    unsigned limit;
    uint32_t genned;
    value = count;
    divisor = 0xffffffffu / unsigned(sides);
    limit = divisor * sides;
    for ( ; count; --count)
    {
        do
        {
            genned = dice_generator.generate();
        } while (genned >= limit);
        value += genned / divisor;
    }
    return value;
}

extern "C" void dice_setstate(const uint32_t *key, const uint32_t *nonce, const uint64_t *counter, const int *subcounter)
{
    dice_generator.initialize(key, nonce, counter, subcounter);
}

extern "C" void dice_getstate(uint32_t *key, uint32_t *nonce, uint64_t *counter, int *subcounter)
{
    dice_generator.extract_state(key, nonce, counter, subcounter);
}

// vim:ts=8:sw=4:expandtab:fo=cq

