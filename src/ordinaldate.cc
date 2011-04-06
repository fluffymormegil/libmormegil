// ordinaldate.cc
//
// Copyright 2011 Martin Read. All rights reserved.
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

#include <string>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <libmormegil/isotime.h>

extern "C" int get_iso_8601_time(char *buf, int bufsz)
{
    time_t t;
    char tmpbuf[128];
    tm tdat;
    int bufreq;
    time(&t);
    gmtime_r(&t, &tdat);
    bufreq = snprintf(tmpbuf, 128, "%d-%3.3dT%2.2d%2.2d%2.2dZ", tdat.tm_year + 1900, tdat.tm_yday, tdat.tm_hour, tdat.tm_min, tdat.tm_sec);
    if (bufreq < bufsz)
    {
        strncpy(buf, tmpbuf, bufsz);
    }
    return bufreq;
}

void libmormegil::get_iso_8601_time(std::string& dest)
{
    time_t t;
    char buf[128];
    tm tdat;
    time(&t);
    gmtime_r(&t, &tdat);
    snprintf(buf, 128, "%d-%3.3dT%2.2d%2.2d%2.2dZ", tdat.tm_year + 1900, tdat.tm_yday, tdat.tm_hour, tdat.tm_min, tdat.tm_sec);
    dest = buf;
    return;
}

// ordinaldate.cc
