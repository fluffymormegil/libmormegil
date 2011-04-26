// points.cc
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

#include <string.h>
#include <errno.h>
#include <libmormegil/Points.hh>

int32_t libmormegil::Points::gain(int32_t amount, libmormegil::Points::Gain_mode mode)
{
    amount = std::min(amount, 0x7fffffff - maxval);
    if (amount < 1)
    {
        return 0;
    }
    switch (mode)
    {
    case Gain_proportional:
        curr *= (maxval + amount);
        /* for non-zero gain_proportional, always gain at least one point. */
        curr = divup(curr, maxval);
        maxval += amount;
        return amount;
    case Gain_match:
        maxval += amount;
        curr += amount;
        return amount;
    case Gain_norestore:
        maxval += amount;
        return amount;
    }
    // should never happen, but be paranoid.
    errno = ENOTSUP;
    return -1;
}

// vim:ts=8:sw=4:expandtab:fo=croq
// points.cc
