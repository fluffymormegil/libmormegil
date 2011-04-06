// namegen.cc - phonotactic name generators
// 
// Copyright 2011 Martin Read
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <string>
#include <string.h>
#include <ctype.h>

namespace libmormegil {
    // This file is derived from Martin's Dungeon Bash's misc.cc.

    // The "dark angel" name generator uses a pseudo-Semitic structure for the
    // words it generates.

    Phoneme dark_angel_phonemes[] =
    {
        // Five vowels, like Hebrew (and incidentally, Latin).
        { Vowel, Vow_open | Vow_unrounded | Vow_backness_unspecified, "a", "A" },
        { Vowel, Vow_mid | Vow_unrounded | Vow_front, "e", "E" },
        { Vowel, Vow_mid | Vow_rounded | Vow_back, "o", "O" },
        { Vowel, Vow_close | Vow_unrounded | Vow_front, "i", "I" },
        { Vowel, Vow_close | Vow_rounded | Vow_back, "u", "U" },
    };

    void name_dark_angel(std::string& dest)
    {
    }
}

/*
 * Phonotactic dark angel name generator
 * =====================================
 * Dark angels are named using different phonotactics to demons.
 *
 * Name structure consists of 3-5 consonants; if more than three, the terminal
 * is restricted to /l/ /h/ /(theta)/
 * 
 * Phonemes are:
 *    Glottal: voiceless fricative, stop.
 *    Velar: voiceless fricative, ejective, voiceless plosive
 *    Alveolar: plosive (modal, ten.), ejective, fricative (modal, ten.)
 *    Labial: voiced plosive
 *    Vowels: /a/ /e/ /i/ /o/ /u/
 *    and a homorganic (naturally coronal) nasal
 *
 * ASCII notation is:
 *    h `
 *    x k' k
 *    n t d t' s z
 *    th dh
 *    b
 *    
 */


/******************************************************************************
 *
 * Phonotactic demon name generator
 * ================================
 *
 * Syllable structure is (C)CVC, with a null onset permissible in the
 * word-initial position.
 *
 * Phonemes are:
 *    Uvular: tenuis plosive, tenuis fricative, trill
 *    Velar: plosive (ten + modal), fric. (ten + modal), labio approx.
 *    Palatal: approx.
 *    Alveolar: plosive (ten + modal), fric. (ten + modal)
 *    Dental: fric. (ten + modal)
 *    Labial: modal plosive, modal fricative.
 *    Vowels: /a/ /i/ /u/
 * 
 * Dorsal fricatives only occur in the coda.  Uvular trill appears only in
 * word-initial onset.
 */

/* A D_ptac_state variable is used to track what category the last letter was.
 * Akvudnik uses CVC syllables (with possible null onset at word-initial).
 */
enum D_ptac_state
{
    D_ptac_start, D_ptac_null_onset, D_ptac_dorsal_onset, D_ptac_coronal_onset,
    D_ptac_labial_onset, D_ptac_w_onset, D_ptac_j_onset,
    D_ptac_low_nucleus, D_ptac_high_nucleus, D_ptac_coda,
    D_ptac_end
};

struct D_ptac_transition
{
    int weight;
    const char *fragment;
    D_ptac_state newstate;
};

D_ptac_state demon_extend_word(std::string *word, D_ptac_state current);

#define PTAC_FENCEPOST { 0, 0, D_ptac_end }

D_ptac_transition demon_start[] =
{
    { 5, "", D_ptac_null_onset },
    { 3, "q", D_ptac_dorsal_onset },
    { 3, "r", D_ptac_dorsal_onset },
    { 12, "k", D_ptac_dorsal_onset },
    { 3, "g", D_ptac_dorsal_onset },
    { 1, "w", D_ptac_w_onset },
    { 1, "j", D_ptac_j_onset },
    { 8, "t", D_ptac_coronal_onset },
    { 2, "d", D_ptac_coronal_onset },
    { 6, "s", D_ptac_coronal_onset },
    { 2, "z", D_ptac_coronal_onset },
    { 4, "th", D_ptac_coronal_onset },
    { 1, "dh", D_ptac_coronal_onset },
    { 8, "b", D_ptac_labial_onset },
    { 4, "v", D_ptac_labial_onset },
    PTAC_FENCEPOST
};

D_ptac_transition demon_null_onset[] =
{
    { 10, "u", D_ptac_high_nucleus },
    { 10, "i", D_ptac_high_nucleus },
    { 10, "a", D_ptac_low_nucleus },
    PTAC_FENCEPOST
};

D_ptac_transition demon_dorsal_onset[] =
{
    { 20, "u", D_ptac_high_nucleus },
    { 10, "i", D_ptac_high_nucleus },
    { 10, "a", D_ptac_low_nucleus },
    PTAC_FENCEPOST
};

D_ptac_transition demon_j_onset[] =
{
    { 10, "u", D_ptac_high_nucleus },
    { 30, "a", D_ptac_low_nucleus },
    PTAC_FENCEPOST
};

D_ptac_transition demon_w_onset[] =
{
    { 10, "i", D_ptac_high_nucleus },
    { 30, "a", D_ptac_low_nucleus },
    PTAC_FENCEPOST
};

D_ptac_transition demon_labial_onset[] =
{
    { 14, "u", D_ptac_high_nucleus },
    { 10, "i", D_ptac_high_nucleus },
    { 14, "a", D_ptac_low_nucleus },
    PTAC_FENCEPOST
};

D_ptac_transition demon_coronal_onset[] =
{
    { 10, "u", D_ptac_high_nucleus },
    { 30, "i", D_ptac_high_nucleus },
    { 10, "a", D_ptac_low_nucleus },
    PTAC_FENCEPOST
};

D_ptac_transition demon_low_nucleus[] =
{
    { 3, "q", D_ptac_coda },
    { 3, "qh", D_ptac_coda },
    { 10, "k", D_ptac_coda },
    { 3, "g", D_ptac_coda },
    { 3, "x", D_ptac_coda },
    { 1, "gh", D_ptac_coda },
    { 1, "w", D_ptac_coda },
    { 1, "j", D_ptac_coda },
    { 8, "t", D_ptac_coda },
    { 2, "d", D_ptac_coda },
    { 6, "s", D_ptac_coda },
    { 2, "z", D_ptac_coda },
    { 4, "th", D_ptac_coda },
    { 1, "dh", D_ptac_coda },
    { 8, "b", D_ptac_coda },
    { 4, "v", D_ptac_coda },
    PTAC_FENCEPOST
};

D_ptac_transition demon_high_nucleus[] =
{
    { 3, "q", D_ptac_coda },
    { 3, "qh", D_ptac_coda },
    { 10, "k", D_ptac_coda },
    { 3, "g", D_ptac_coda },
    { 3, "x", D_ptac_coda },
    { 1, "gh", D_ptac_coda },
    { 8, "t", D_ptac_coda },
    { 2, "d", D_ptac_coda },
    { 6, "s", D_ptac_coda },
    { 2, "z", D_ptac_coda },
    { 4, "th", D_ptac_coda },
    { 1, "dh", D_ptac_coda },
    { 8, "b", D_ptac_coda },
    { 4, "v", D_ptac_coda },
    PTAC_FENCEPOST
};

D_ptac_transition demon_coda[] =
{
    { 3, "q", D_ptac_dorsal_onset },
    { 12, "k", D_ptac_dorsal_onset },
    { 3, "g", D_ptac_dorsal_onset },
    { 1, "w", D_ptac_w_onset },
    { 1, "j", D_ptac_j_onset },
    { 8, "t", D_ptac_coronal_onset },
    { 2, "d", D_ptac_coronal_onset },
    { 5, "s", D_ptac_coronal_onset },
    { 2, "z", D_ptac_coronal_onset },
    { 4, "th", D_ptac_coronal_onset },
    { 1, "dh", D_ptac_coronal_onset },
    { 8, "b", D_ptac_labial_onset },
    { 4, "v", D_ptac_labial_onset },
    PTAC_FENCEPOST
};

int demon_start_sum;
int demon_low_nucleus_sum;
int demon_high_nucleus_sum;
int demon_null_onset_sum;
int demon_dorsal_onset_sum;
int demon_coronal_onset_sum;
int demon_labial_onset_sum;
int demon_j_onset_sum;
int demon_w_onset_sum;
int demon_coda_sum;

void ptac_init(void)
{
    int i;
    for (i = 0; demon_start[i].fragment != 0; ++i)
    {
        demon_start_sum += demon_start[i].weight;
    }
    for (i = 0; demon_null_onset[i].fragment != 0; ++i)
    {
        demon_null_onset_sum += demon_null_onset[i].weight;
    }
    for (i = 0; demon_labial_onset[i].fragment != 0; ++i)
    {
        demon_labial_onset_sum += demon_labial_onset[i].weight;
    }
    for (i = 0; demon_coronal_onset[i].fragment != 0; ++i)
    {
        demon_coronal_onset_sum += demon_coronal_onset[i].weight;
    }
    for (i = 0; demon_dorsal_onset[i].fragment != 0; ++i)
    {
        demon_dorsal_onset_sum += demon_dorsal_onset[i].weight;
    }
    for (i = 0; demon_j_onset[i].fragment != 0; ++i)
    {
        demon_j_onset_sum += demon_j_onset[i].weight;
    }
    for (i = 0; demon_w_onset[i].fragment != 0; ++i)
    {
        demon_w_onset_sum += demon_w_onset[i].weight;
    }
    for (i = 0; demon_coda[i].fragment != 0; ++i)
    {
        demon_coda_sum += demon_coda[i].weight;
    }
    for (i = 0; demon_high_nucleus[i].fragment != 0; ++i)
    {
        demon_high_nucleus_sum += demon_high_nucleus[i].weight;
    }
    for (i = 0; demon_low_nucleus[i].fragment != 0; ++i)
    {
        demon_low_nucleus_sum += demon_low_nucleus[i].weight;
    }
}

char *demon_get_name(void)
{
    std::string working_copy;
    D_ptac_state current = D_ptac_start;
    int syllables = 1;
    do
    {
        current = demon_extend_word(&working_copy, current);
        if (current == D_ptac_coda)
        {
            if (zero_die(6) < (syllables - 1))
            {
                current = D_ptac_end;
            }
            ++syllables;
        }
    } while (current != D_ptac_end);
    char *s = strdup(working_copy.c_str());
    s[0] = toupper(s[0]);
    return s;
}

D_ptac_state demon_extend_word(std::string *word, D_ptac_state current)
{
    D_ptac_transition const *arr = 0;
    int dieroll = 0;
    int idx;
    switch (current)
    {
    case D_ptac_start:
        dieroll = zero_die(demon_start_sum);
        arr = demon_start;
        break;
    case D_ptac_dorsal_onset:
        dieroll = zero_die(demon_dorsal_onset_sum);
        arr = demon_dorsal_onset;
        break;
    case D_ptac_coronal_onset:
        dieroll = zero_die(demon_coronal_onset_sum);
        arr = demon_coronal_onset;
        break;
    case D_ptac_labial_onset:
        dieroll = zero_die(demon_labial_onset_sum);
        arr = demon_labial_onset;
        break;
    case D_ptac_w_onset:
        dieroll = zero_die(demon_w_onset_sum);
        arr = demon_w_onset;
        break;
    case D_ptac_j_onset:
        dieroll = zero_die(demon_j_onset_sum);
        arr = demon_j_onset;
        break;
    case D_ptac_null_onset:
        dieroll = zero_die(demon_null_onset_sum);
        arr = demon_null_onset;
        break;
    case D_ptac_coda:
        dieroll = zero_die(demon_coda_sum);
        arr = demon_coda;
        break;
    case D_ptac_high_nucleus:
        dieroll = zero_die(demon_high_nucleus_sum);
        arr = demon_high_nucleus;
        break;
    case D_ptac_low_nucleus:
        dieroll = zero_die(demon_low_nucleus_sum);
        arr = demon_low_nucleus;
        break;
    case D_ptac_end:
        print_msg(MSGCHAN_INTERROR, "Attempt to extend name in an end state?!");
        return D_ptac_end;
    }
    for (idx = 0; ; ++idx)
    {
        if (dieroll < arr[idx].weight)
        {
            break;
        }
        dieroll -= arr[idx].weight;
    }
    (*word) += arr[idx].fragment;
    return arr[idx].newstate;
}

// namegen.cc
