[org 0x7c00]
mov bp, 0x8000 ; move stack
mov sp, bp

mov bx, 0x9000 ; set starting position for disk
mov dh, 2 ; read 2 sectors
call disk_load ; load values from disk

mov dx, [0x9000] ; read first sector from the disk
call print_hex

call print_nl

mov dx, [0x9000 + 512] ; read next sector (each sector is 512 bytes long)
call print_hex

jmp $ ; hang

; load bootloader libraries
%include "./boot/b_print-16.S"
%include "./boot/b_print_hex-16.S"
%include "./boot/b_disk.S"

; make bootloader bootable
times 510-($-$$) db 0
dw 0xaa55

; we are currently on sector 1
times 256 dw 0xdead ; this will write 0xdead to be the first value of sector 2
times 256 dw 0xbeef ; this will write 0xbeef to be the first value of sector 3