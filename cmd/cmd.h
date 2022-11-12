#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../krnl/krnl.h"

// programs
#include "../programs/demo.h"

void user_input(char *input);
void cmd_init();
int getCmdShouldLoad();
int cmd;