// libmormegil/Phones.hh - representation of speech sounds
//
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).
// It is provided without any warranty, express or implied.

#ifndef libmormegil_Phones_hh
#define libmormegil_Phones_hh

namespace libmormegil
{
    struct Phone
    {
        enum Sound_class {
            Vowel,
            Consonant,
            Pitch_accent,
            Stress_accent,
            Contour_tone
        };

        enum Vowel_heights {
            Vow_open,
            Vow_near_open,
            Vow_open_mid,
            Vow_mid,
            Vow_close_mid,
            Vow_near_close,
            Vow_close
        };

        enum Vowel_backness {
            Vow_unspecified,
            Vow_front,
            Vow_near_front,
            Vow_central,
            Vow_near_back,
            Vow_back
        };

        enum Vowel_roundness {
            Vow_rounding_unspecified,
            Vow_unrounded,
            Vow_endolabial,
            Vow_exolabial,
            Vow_compressed
        };

        enum Voicings {
            Voice_unspecified,
            Voice_aspirated,
            Voice_tenuis,
            Voice_breathy,
            Voice_modal,
            Voice_faucalized
        };

        enum Consonant_modes {
            Conson_nasal,
            Conson_plosive,
            Conson_affricate,
            Conson_fricative,
            Conson_approximant,
            Conson_tap,
            Conson_trill
        };
#define Conson_flap Conson_tap

        enum Conson_lat {
            Conson_nonlateral,
            Conson_unspec_lateral,
            Conson_lateral
        }

        enum Consonant_places {
            Conson_bilabial,
            Conson_labiodental,
            Conson_interdental,
            Conson_dental,
            Conson_alveolar,
            Conson_retroflex,
            Conson_palatoalveolar,
            Conson_alveolopalatal,
            Conson_palatal,
            Conson_velar,
            Conson_uvular,
            Conson_pharyngeal,
            Conson_epiglottal,
            Conson_glottal
        };

        enum Consonant_secondary {
            Conson_no_secondary,
            Conson_palatalized,
            Conson_velarized,
            Conson_glottalized
        };

        enum Stress_level {
            Stress_primary,
            Stress_secondary
        };

        Sound_class category;
        int qualification[10];
    };
}

#endif

// vim:ts=8:sw=4:expandtab:fo=c
// libmormegil/Phones.hh
