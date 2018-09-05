#include <stdint.h>
#include "types.h" // word, dword, qword

// these are all just important spots in memory related to the PPU
// we access them raw because we like living on the edge
#define PPU_CTRL    *((WORD*) 0x2000)
#define PPU_MASK    *((WORD*) 0x2001)
#define PPU_STATUS  *((WORD*) 0x2002)
#define SCROLL      *((WORD*) 0x2005)
#define PPU_ADDRESS *((WORD*) 0x2006)
#define PPU_DATA    *((WORD*) 0x2007)

#define READLO(addr) *((WORD*) (addr)) & ((WORD) 0x1)
#define READHI(addr) *((WORD*) (addr)) >> 7

// globals
#pragma bss-name(push, "ZEROPAGE")
/*	forces these variables to be in the zeropage of the RAM
 *	note, in colors_reset.s, changed the .import to .importzp
 *	zeropage code runs faster than anything outside the zeropage
 */

WORD NMI_flag;
WORD frame_count;
WORD i;
WORD text_i;

#pragma bss-name(push, "BSS")
//	these variables to be in the BSS of the RAM, set as 0x300 in the cfg file
WORD test;
const WORD text[] = "Triss Green";

// other #includes for code organization

// If I want to do this properly I could have an h and c file pair and compile it
// seperately, but I'm too lazy. I promise why I make the actual game I won't be
// #include-ing c files like a maniac

// takes advantage of the fact that c literally just copy/pastes code into files
// who made this fucking language

#include "palette.c"
#include "nesfuncs.c"

WORD main(void) {
    screen_reset();

    while (1) {
        while (NMI_flag == 0);
        NMI_flag = 0;

        if (frame_count == 30) {
            load_text();
            reset_scroll();
            frame_count = 0;
            test++; // dummy, just making sure this compiles into the BSS section 0x300
        }
    }

    return 0;
}
