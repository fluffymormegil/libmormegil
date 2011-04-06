// Appcfg.cc
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

#include <stdint.h>
#include <string.h>
#include <libmormegil/Appcfg.hh>

bool libmormegil::Appcfg::register_bool(const std::string& name, bool defval)
{
    if (data.find(name) != data.end())
    {
        return false;
    }
    libmormegil::Appcfg::Entry e;
    e.bval = defval;
    e.t = Appcfg_boolean;
    data[name] = e;
    return true;
}

bool libmormegil::Appcfg::register_integer(const std::string& name, int64_t defval)
{
    if (data.find(name) != data.end())
    {
        return false;
    }
    libmormegil::Appcfg::Entry e;
    e.ival = defval;
    e.t = Appcfg_integer;
    data[name] = e;
}

bool libmormegil::Appcfg::register_string(const std::string& name, const std::string& defval)
{
    if (data.find(name) != data.end())
    {
        return false;
    }
    libmormegil::Appcfg::Entry e;
    e.sval = defval;
    e.t = Appcfg_string;
    data[name] = e;
}

bool libmormegil::Appcfg::get(const std::string& name, int64_t& val)
{
    data_iterator iter = data.find(name);
    if ((iter != data.end()) && (iter->second.t == Appcfg_integer))
    {
        val = iter->second.ival;
        return true;
    }
    return false;
}

bool libmormegil::Appcfg::get(const std::string& name, std::string& val)
{
    data_iterator iter = data.find(name);
    if ((iter != data.end()) && (iter->second.t == Appcfg_string))
    {
        val = iter->second.sval;
        return true;
    }
    return false;
}

bool libmormegil::Appcfg::get(const std::string& name, bool& val) const
{
    data_iterator iter = data.find(name);
    if ((iter != data.end()) && (iter->second.t == Appcfg_boolean))
    {
        val = iter->second.bval;
        return true;
    }
    return false;
}

bool libmormegil::Appcfg::set(const std::string& name, int64_t val)
{
    data_iterator iter = data.find(name);
    if ((iter != data.end()) && (iter->second.t == Appcfg_integer))
    {
        iter->second.ival = val;
        return true;
    }
    return false;
}

bool libmormegil::Appcfg::set(const std::string& name, const std::string& val)
{
    data_iterator iter = data.find(name);
    if ((iter != data.end()) && (iter->second.t == Appcfg_string))
    {
        iter->second.sval = val;
        return true;
    }
    return false;
}

bool libmormegil::Appcfg::set(const std::string& name, bool val)
{
    data_iterator iter = data.find(name);
    if ((iter != data.end()) && (iter->second.t == Appcfg_boolean))
    {
        iter->second.bval = val;
        return true;
    }
    return false;
}

// vim:ts=8:sw=4:expandtab:fo=cq

