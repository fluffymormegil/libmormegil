// libmormegil/Appcfg.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0)

#ifndef libmormegil_Appcfg_hh
#define libmormegil_Appcfg_hh

#include <stdint.h>
#include <map>
#include <string>
#include <list>

namespace libmormegil
{
    // Registration functions
    class Appcfg
    {
    public:
        enum Type
        {
            Appcfg_boolean,
            Appcfg_string,
            Appcfg_integer
        };
        struct Entry
        {
            Type t;
            bool bval;
            int64_t ival;
            std::string sval;
        };
    private:
        std::map<std::string, Entry> data;
        typedef std::map<std::string, Entry>::iterator data_iterator;
        typedef std::map<std::string, Entry>::const_iterator data_const_iterator;
    public:
        // registration functions
        bool register_bool(const std::string& name, bool defval = false);
        bool register_integer(const std::string& name, int64_t defval = 0);
        bool register_string(const std::string& name, const char *defval = "");
        bool register_string(const std::string& name, const std::string& defval);

        // set functions
        bool set(const std::string& name, bool val);
        bool set(const std::string& name, int64_t val);
        bool set(const std::string& name, const char* val);
        bool set(const std::string& name, const std::string& val);

        // get functions
        bool get(const std::string& name, bool& dest) const;
        bool get(const std::string& name, int64_t& dest) const;
        // for code hygeine reasons, we don't support
        bool get(const std::string& name, std::string& dest) const;

        // dumper function
        int dump(std::list<Entry>& dest);

        // filler function
        void fill(const std::list<Entry>& src);
    };
}
#endif // libmormegil_Appcfg_hh

// vim:ts=8:sw=4:expandtab:fo=c
