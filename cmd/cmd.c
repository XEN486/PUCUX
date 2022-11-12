#include "cmd.h"
int cmd = 1;

static void play_sound(unsigned int nFrequence) {
	unsigned int Div;
	unsigned char tmp;
	
	Div = 1193180 / nFrequence;	
	outb(0x43, 0xb6);
	outb(0x42, (unsigned char) (Div));
	outb(0x42, (unsigned char) (Div >> 8));
	
	tmp = inb(0x61);
	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}
}

static void stop_sound() {
	unsigned char tmp = inb(0x61) & 0xFC;
	
	outb(0x61, tmp);
}

int getCmdShouldLoad() {
	if (cmd == 1) {
		return 1;
	} else {
		return 0;
	}
}

void cmd_init() {
	kprint("[CMD] Initializing the keyboard...\n");
	keyboard = 1;
	init_keyboard(); // keyboard
	kprint("[CMD] Done! Keyboard is now active.\n");
}

void cmd_input(char *input) {
	char todo[] = "This isn't implemented yet. Stop asking, it will be.\n";
    	if (strcmp(input, "HALT") == 0) { // halt
        	kprint("Stopping the CPU. Bye!\n");
        	halt();
    	} else if (strcmp(input, "HELP") == 0) { // help
		kprint("-=-=Commands=-=-\nHALT - halt the cpu\nHELP - display this help dialog\nCLEAR - clear the screen\nDIR - list directories\nEDIT - edit a file\nCAT - read file\nEXECUTE - execute file\nDEMO - first program made ever\nUPDATENOTES - notes about the update\n");
	} else if (strcmp(input, "CLEAR") == 0) { // clear
		clear_screen();
	} else if (strcmp(input, "CLS") == 0) { // clear
		clear_screen();
	} else if (strcmp(input, "CREDITS") == 0) { // easter egg
		kprint("CREDITS:\nDeveloper - XENON\nTutorial from cfenollosa\nGoodbye CPU!\n");
		halt();
	} else if (strcmp(input, "DIR") == 0) { // dir (todo)
		kprint(todo);
	} else if (strcmp(input, "EDIT") == 0) { // edit (todo)
		kprint(todo);	
	} else if (strcmp(input, "CAT") == 0) { // cat (todo)
		kprint(todo);
	} else if (strcmp(input, "EXECUTE") == 0) { // execute (todo)
		kprint(todo);
	} else if (strcmp(input, "DEMO") == 0) { // demo program
		cmd = 0;
		keyboard = 0;
		demo_init();
	} else if (strcmp(input, "UPDATENOTES") == 0) {
		kprint("PUCUX 0.3\n");
	} else if (strcmp(input, "TESTCRASH") == 0) {
		kernel_crash("TEST_CRASH");
	} else if (strcmp(input, "SOUND") == 0) {
		play_sound(1000);
		kprint("That probably sounds really bad\n");
	} else if (strcmp(input, "STOPSOUND") == 0) {
		stop_sound();
		kprint("Done!\n");
	} else if (strcmp(input, "") == 0) { // enter pressed
		kprint("\n");
	}
	// if command is not recognized
	else {
		kprint("'");
		kprint(input);
		kprint("'");
		kprint(" is not a command!\n");
	}
	
	if (cmd == 1) {
		kprint("\n> ");
	}
}
