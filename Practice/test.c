#include <stdint.h>

// fast int types for NES ; keep consistent
typedef unsigned char INT;    // 0 - 255, aka BYTE
typedef uint16_t      DOUBLE; // 0 - 65,536
typedef uint32_t      LONG;   // 0 - 2,147,483,647

// these are all just important spots in memory
// we access them raw because we like living on the edge
#define PPU_CTRL    *((INT*)0x2000)
#define PPU_MASK    *((INT*)0x2001)
#define PPU_STATUS  *((INT*)0x2002)
#define SCROLL      *((INT*)0x2005)
#define PPU_ADDRESS *((INT*)0x2006)
#define PPU_DATA    *((INT*)0x2007)

static const INT text[] = { "TEST" };
// should be like the matrix
// black, white, grey, green
static const INT palette[] = { 0x0F, 0x30, 0x00, 0x29 };

// local variables are slow in assembly
static INT i;
INT main() {
    // turn screen off
    PPU_CTRL = 0;
    PPU_MASK = 0;
    // palette stuff
    PPU_ADDRESS = 0x3f; // set an address in the PPU of 0x3f00
    PPU_ADDRESS = 0x00;
    for(i = 0; i < sizeof(palette); i++)
        PPU_DATA = palette[i];

    // load the text
    PPU_ADDRESS = 0x21; // set an address in the PPU of 0x21ca
    PPU_ADDRESS = 0xca;  // about the middle of the screen
    for(i = 0; i < sizeof(text); i++)
        PPU_DATA = text[i];

    // reset the scroll position
    PPU_ADDRESS = 0;
    PPU_ADDRESS = 0;
    SCROLL = 0;

    // turn on screen
    PPU_CTRL = 0x90; // NMI on
    PPU_MASK = 0x1e; // screen on

    while (1); // end of program
    return 0; // uh just to make compiler happy
}
