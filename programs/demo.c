#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../cmd/cmd.h"

void demo_init() {
	// start
	clear_screen();
	char* txtbuf = (char*) 0xB8000; // create pointer to text buffer
	int i;
	for (i=0;i<(80*60);i++) {
		txtbuf[i*2] = 0xDB;
		txtbuf[(i*2)+1] = i % 0xFF;
	}
}