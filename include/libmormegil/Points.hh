// libmormegil/Points.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

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
