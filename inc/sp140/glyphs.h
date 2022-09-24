// 'triangle-exclamation-solid', 40x40px
const unsigned char lcd_bitmap_triangle_exclamation_solid [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 
	0x3f, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x0f, 
	0xff, 0xff, 0xf0, 0x3c, 0x0f, 0xff, 0xff, 0xe0, 0x3c, 0x07, 0xff, 0xff, 0xe0, 0x3c, 0x07, 0xff, 
	0xff, 0xc0, 0x3c, 0x03, 0xff, 0xff, 0x80, 0x3c, 0x01, 0xff, 0xff, 0x80, 0x3c, 0x01, 0xff, 0xff, 
	0x00, 0x3c, 0x00, 0xff, 0xff, 0x00, 0x3c, 0x00, 0xff, 0xfe, 0x00, 0x3c, 0x00, 0x7f, 0xfc, 0x00, 
	0x3c, 0x00, 0x3f, 0xfc, 0x00, 0x3c, 0x00, 0x3f, 0xf8, 0x00, 0x18, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
	0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x3c, 0x00, 
	0x07, 0xc0, 0x00, 0x3c, 0x00, 0x03, 0xc0, 0x00, 0x3c, 0x00, 0x03, 0x80, 0x00, 0x3c, 0x00, 0x01, 
	0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x22, 0x10, 0x01, 0x8f, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 224)
const int lcd_bitmap_allArray_LEN = 1;
const unsigned char* lcd_bitmap_allArray[1] = {
	lcd_bitmap_triangle_exclamation_solid
};
