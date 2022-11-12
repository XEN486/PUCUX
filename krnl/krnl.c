#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../cmd/cmd.h"
#include "../xeinit/xeinit.h"
#include "../drivers/screen.h"

void halt() {
	asm volatile("hlt");
}

void kernel_main() {
	int debug = 0;
	char name[] = "PUCUX";
	char ver[] = "0.3";
	
	kprint("[XKern] Loading init system...\n");
	xeinit_init();
	
	if (debug != 1) {
		clear_screen();
	}
	
	// Welcome to {name} v{ver}!
	kprint("\nWelcome to ");
	kprint(name);
	kprint(" v");
	kprint(ver);
	kprint("!\n");
	
	// Initial prompt
	kprint("> ");
	cmd = 1;
}

void user_input(char *input) {
	if (getCmdShouldLoad() == 1) {
		cmd_input(input);
	} else {
		// don't let shell access keyboard
		;
	}
}

// start of kernel api
void kernel_crash(char* reason[]) {
	clear_screen();
	kprint("PUCUX has crashed.\nPlease tell XENON#7763 on discord this:\n");
	kprint(reason);
	halt();
}
