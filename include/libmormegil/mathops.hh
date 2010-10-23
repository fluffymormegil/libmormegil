// libmormegil/mathops.hh
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

#ifndef libmormegil_mathops_hh
#define libmormegil_mathops_hh

namespace libmormegil
{
    template<typename T> inline T abs(const T& i) { return i < T(0) ? -i : i; }
    template<typename T> inline T sign(const T& orig)
    {
        return (orig != 0) ? ((orig < 0) ? T(-1) : T(1)) : T(0);
    }
    // div_up provides an upward-rounding integer divide.
    // Before you ask: it isn't reasonable to use
    //      ceil(double(orig) / double(divisor)
    // because while x86 might allow you to conveniently do to-and-fro
    // translations between the GPRs and the FPRs, PowerPC (among others)
    // does not.
    template<typename T> inline T div_up(T orig, T divisor)
    {
        return (orig + (divisor - 1)) / divisor;
    }
}
#endif // libmormegil_mathops_hh

// vim:ts=8:sw=4:expandtab:fo=c
