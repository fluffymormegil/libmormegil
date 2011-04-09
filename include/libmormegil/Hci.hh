// libmormegil/Hci.hh
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_Hci_hh
#define libmormegil_Hci_hh

namespace libmormegil
{
    class Hci
    {
    protected:
        Hci_tilemode my_tilemode;
    public:
        enum Hci_tilemode {
            Hci_tile_invalid = -1,
            Hci_tile_wchar,
            Hci_tile_pixel
        };
        Hci() : my_tilemode(Hci_tile_invalid) { }
        virtual ~Hci() { }
        Hci_tilemode tilemode() const { return my_tilemode; }
        // Now for the interesting part of the interface. It's not nearly as
        // ambitious as I _want_ it to be, but that's because I don't feel 
        // like writing the elaborate separation mechanisms required.
        virtual void init() = 0;
        virtual void cleanup() = 0;
        virtual void emit_message(const std::string& msg) = 0;
        virtual void emit_message_decorated(const std::string& msg) = 0;
        virtual void set_tile(int tile_layer, int tile_id) = 0;
        virtual int register_tile_data(int layer, void *data) = 0;
    };

}
#endif // libmormegil_Hci_hh

// vim:ts=8:sw=4:expandtab:fo=croq
