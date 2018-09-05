#ifndef PALETTE_Y
#define PALETTE_Y

// I have sinned

// note, 11 is the default background color = blue
// we are only writing the BG palettes (16 bytes total).
const WORD palette[16] = {
    0x11, 0x00, 0x00, 0x31, // blues
    0x00, 0x00, 0x00, 0x15, // red
    0x00, 0x00, 0x00, 0x27, // yellow
    0x00, 0x00, 0x00, 0x1a, // green
};

// each 2 bits defines a color palette
// for a 16x16 box
const WORD attribute_T[4] = {
    0x44, // 0100 0100
    0xbb, // 1011 1011
    0x44, // 0100 0100
    0xbb  // 1011 1011
};

#endif /* end of include guard: PALETTE_Y */
