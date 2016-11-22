print_char:
    pusha
    mov ah,0x0e
    int 0x10
    popa
    ret

print_string:
    pusha
    iterate_char:
        mov al,[si]
        inc si
        or al,al
        jz exit_print_string
        call print_char
        jmp iterate_char
    exit_print_string:
        popa
        ret	
        

load_disk:
    push dx
    mov ah,0x02
    mov al,dh
    mov ch,0x00
    mov dh,0x00
    mov cl,0x02
    int 0x13
    
    jc disk_error
    
    pop dx
    cmp dh,al
    jne disk_error
    ret
    
disk_error:
    mov si, disk_error_msg
    call print_string
    jmp $
    
disk_error_msg:
    db "Disk read error !"