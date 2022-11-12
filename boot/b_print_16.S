print:
    pusha

; we are trying to replicate
; while (string[i] != 0) { print string[i]; i++ }
; in assembly

; the comparison for string end (null byte)
start:
    mov al, [bx] ; bx is where the string is
    cmp al, 0 
    je done

    ; tell the bios to print character
    mov ah, 0x0e
    int 0x10 ; al already has the character

    ; increment pointer and do next iteration
    add bx, 1
    jmp start

done:
    popa
    ret



print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a ; print a newline
    int 0x10
    mov al, 0x0d ; CR
    int 0x10
    
    popa
	ret