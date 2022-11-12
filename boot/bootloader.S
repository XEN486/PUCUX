[org 0x7c00]
; loadx bootloader

; clear screen to remove that very stupid bios text (its actually stupid) no legit its so stupid I hate this stupid bios text please remove it oh my god thank you but also set video mode
mov ah, 0x00
mov al, 0x03
int 0x10

KERNEL_OFFSET equ 0x1000 ; where the kernel is located

    mov [BOOT_DRIVE], dl ; bios sets boot drive to dl so set BOOT_DRIVE to that
    mov bp, 0x9000
    mov sp, bp

    call load_kernel ; read the kernel from disk
    call switch_to_pm ; call our 32-bit loader, when it wraps up its loading, we will be placed in BEGIN_PM
    jmp $ ; if we ever get back here somehow just go in an infinite loop

; include stuff
%include "boot/b_print_16.S"
%include "boot/b_print_hex_16.S"
%include "boot/b_disk_16.S"
%include "boot/gdt.S"
%include "boot/b32_helper.S"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; read the kernel offset
    mov dh, 25 ; how many sectors do we want to load
    mov dl, [BOOT_DRIVE] ; put our boot drive to where disk_load can access it
	
    call disk_load ; load the sectors we specified
    ret

[bits 32]
BEGIN_PM:
	; we are in 32-bit land, do any initialization here and then jump to the kernel
	jp KERNEL
	
KERNEL:
	; do any initialization right before the kernel is called
    call KERNEL_OFFSET ; Give control to the kernel
    jmp $ ; if the kernel exits we will just go in an infinite loop

BOOT_DRIVE db 0 ; store our boot drive so we dont loose it if dl gets overwritten

times 510 - ($-$$) db 0 ; if we have any data left over fill it with 0 until the last two bytes
dw 0xaa55 ; last two bytes specify if its bootable, 0xAA55 says that its bootable.