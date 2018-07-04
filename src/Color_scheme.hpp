//
// Color_scheme header
//
// In FLTK, colours are represented as 32-bit unsigned integers where the last
// two bytes must be 00 (see defaults).
//

#ifndef BD_COLOR_SCHEME_H
#define BD_COLOR_SCHEME_H

struct Color_scheme {
    unsigned int background = 0x0b4f6c00;   // dark blue; bg
    unsigned int primary    = 0xfbfbff00;   // white; text
    unsigned int secondary  = 0xef3e3600;   // red; button face
    unsigned int tertiary   = 0x040f1600;   // black;
    unsigned int auxilliary = 0x01baef00;   // light blue;

    Color_scheme() = default;

    Color_scheme(unsigned int b, unsigned int p, unsigned int s,
            unsigned int t, unsigned int a)
        : background{b},
          primary{p},
          secondary{s},
          tertiary{t},
          auxilliary{a} { }
};

#endif  // BD_COLOR_SCHEME_H
