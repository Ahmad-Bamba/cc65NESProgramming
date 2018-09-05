#ifndef NESFUNCS_Y
#define NESFUNCS_Y

void load_text(void) {
    if (text_i < (WORD) sizeof(text)) {
        PPU_ADDRESS = 0x21;
        PPU_ADDRESS = 0xCA + text_i;
        PPU_DATA    = text[text_i];

        PPU_ADDRESS = 0x21;
        PPU_ADDRESS = 0xEA + text_i; // one line down, apparently
        PPU_DATA    = text[text_i];

        text_i++;
    } else {
        // we're out of text, time to start over
        // clear the text by putting tile #0 (blank block) in its place
        text_i = 0;
        PPU_ADDRESS = 0x21;
		PPU_ADDRESS = 0xCA;
		for (i = 0; i < sizeof(text); i++)
			PPU_DATA = 0;
        PPU_ADDRESS = 0x21;
        PPU_ADDRESS = 0xEA;
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

    PPU_ADDRESS = 0x23;
    PPU_ADDRESS = 0xDA;
    for (i = 0; i < sizeof(attribute_T); i++)
        PPU_DATA = attribute_T[i];
}

void screen_reset(void) {
    //	turn off the screen
	all_off();
	load_palette();
	reset_scroll();
	//	turn on screen
	all_on();
}


#endif /* end of include guard: NESFUNCS_Y */
