[bits 16]
switch_to_pm:
    cli ; we dont old interrupts
    lgdt [gdt_descriptor] ; load the gdt
    mov eax, cr0
    or eax, 0x1 ; tell cr0 that we are in 32-bit land!
    mov cr0, eax
    jmp CODE_SEG:init_pm ; far jump (16-bit thing) to the 32-bit code

[bits 32]
init_pm:
	; we are now executing 32-bit stuff!
    mov ax, DATA_SEG ; update segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; update the stack
    mov esp, ebp

    call BEGIN_PM ; jump to BEGIN_PM wherever it is.