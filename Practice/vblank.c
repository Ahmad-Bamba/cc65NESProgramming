// props to this tutorial: https://nesdoug.com/

#include <stdint.h>

// fast int types for NES ; keep consistent
typedef unsigned char WORD;    // 0 - 255, aka BYTE
typedef uint16_t      DWORD; // 0 - 65,536
typedef uint32_t      QWORD;   // 0 - 2,147,483,647

// these are all just important spots in memory
// we access them raw because we like living on the edge
#define PPU_CTRL    *((WORD*) 0x2000)
#define PPU_MASK    *((WORD*) 0x2001)
#define PPU_STATUS  *((WORD*) 0x2002)
#define SCROLL      *((WORD*) 0x2005)
#define PPU_ADDRESS *((WORD*) 0x2006)
#define PPU_DATA    *((WORD*) 0x2007)

// local variables are slow in assembly
static WORD i;
static WORD text_i;
// will be exported to the reset file, no static
WORD NMI_flag;
WORD frame_count;

static const WORD text[] = { "TEST" };
// black, green, grey, white
static const WORD palette[] = { 0x0F, 0x29, 0x00, 0x30 };

void load_text(void);
void screen_reset(void); // abstraction!
void all_off(void);
void all_on(void);
void reset_scroll(void);
void load_palette(void);

WORD main(void) {
    // zero out the screen to avoid graphical glitches
    screen_reset();

    // infinite loop, effective "end" of program
    while (1) {
        while (!NMI_flag); // wait for the NMI flag to flip
        NMI_flag = 0; // reset NMI flag
        if (frame_count == 30) { // 0.5 seconds
            load_text();
            reset_scroll();
            frame_count = 0;
        }
    }
    return 0; // shut up compiler!
}

void load_text(void) {
    if (text_i < (WORD) sizeof(text)) {
        PPU_ADDRESS = 0x21;
        PPU_ADDRESS = 0xce + text_i;
        PPU_DATA    = text[text_i];
        text_i++;
    } else {
        // we're out of text, time to start over
        // clear the text by putting tile #0 (blank block) in its place
        text_i = 0;
        PPU_ADDRESS = 0x21;
		PPU_ADDRESS = 0xce;
		for (i = 0; i < sizeof(text); i++)
			PPU_DATA = 0;
    }
}

void all_off(void) {
    PPU_CTRL = 0;
	PPU_MASK = 0;
}

void all_on(void) {
    // reference: http://wiki.nesdev.com/w/index.php/PPU_registers

    // screen on, NMI on
    PPU_CTRL = 0x90;
    // spr enable, bkg  enable, spr left col enable, bkg left col enable
	PPU_MASK = 0x1E;
}

void reset_scroll(void) {
    // remember we right twice because we have to write the
    // high and low bytes and the PPU addresses are written with
    // an index

    PPU_ADDRESS = 0;
	PPU_ADDRESS = 0;
	SCROLL = 0;
	SCROLL = 0;
}

void load_palette(void) {
    PPU_ADDRESS = 0x3F;
	PPU_ADDRESS = 0x00;
    // write palette data starting at 0x00
	for (i = 0; i < sizeof(palette); i++)
		PPU_DATA = palette[i];
}

void screen_reset(void) {
    //	turn off the screen
	all_off();
	load_palette();
	reset_scroll();
	//	turn on screen
	all_on();
}
