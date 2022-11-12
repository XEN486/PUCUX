#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../cmd/cmd.h"

int xeinit_init() {
	kprint("[XEInit] Installing ISR...\n");
	isr_install();
	kprint("[XEInit] Done!\n[XEInit] Installing IRQ...\n");
	irq_install();
	kprint("[XEInit] Loading shell...\n");
	cmd_init();
}