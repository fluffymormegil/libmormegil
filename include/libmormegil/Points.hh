// libmormegil/Points.hh
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

#ifndef libmormegil_Points_hh
#define libmormegil_Points_hh
#include <algorithm>
#include <stdint.h>

#ifndef libmormegil_divup_hh
#include <libmormegil/divup.hh>
#endif

#ifndef libmormegil_abs_hh
#include <libmormegil/abs.hh>
#endif

namespace libmormegil
{
    class Points
    {
    private:
        int32_t maxval;
        int32_t curr;
    public:
        enum Gain_mode {
            Gain_match,
            Gain_proportional,
            Gain_norestore
        };
        int32_t boost(int32_t amount)
        {
            amount = std::min(0x7fffffff - curr, amount);
            curr += amount;
            return amount;
        }
        int32_t restore(int32_t amount)
        {
            amount = std::max(0, std::min(amount, maxval - curr));
            curr += amount;
            return amount;
        }
        // gain() is non-inline because it's messy.
        int32_t gain(int32_t amount, Gain_mode mode);
        int32_t lose(int32_t amount) { amount = std::max(0, maxval); return amount; }
        int32_t current() const { return curr; }
        int32_t maximum() const { return maxval; }
    };
}
#endif // libmormegil_Points_hh

// vim:ts=8:sw=4:expandtab:fo=c
// libmormegil/Points.hh
