print_char:
    pusha
    mov ah,0x0e
    int 0x10
    popa
    ret
    
print_new_line:
    mov al,13
    call print_char
    mov al,10
    call print_char
    ret
    
print_string:
    pusha
    iterate_char:
        mov al,[bx]
        inc bx
        or al,al
        jz exit_print_string
        call print_char
        jmp iterate_char
    exit_print_string:
        popa
        ret	

print_hex_word:  
    mov bx,ax
    mov bh,al
    call print_hex_byte
    
    mov bl,al
    call print_hex_byte
    
    ret

print_hex_byte:  
    mov bl,al
    
    shr al,0x4
    and al,0xf
    call print_low_nibble
    
    mov al,bl
    and al,0xf
    call print_low_nibble
    
    ret
    
print_low_nibble:    
    cmp al,10
    jl is_digit
     
    is_leter:
    sub al,10
    add al,'a'
    call print_char
    ret
    
    is_digit:
    add al,'0'   
    call print_char
    ret
    

load_disk:
    push dx
    mov ah,0x02 ; read sector function
    mov al,dh
    mov ch,0x00 ; select cylinder
    mov dh,0x00 ; select head
    mov cl,0x01 ; reading from 1st sector
    int 0x13
    
    pop dx
    jc load_disk_error
    
    cmp dh,al
    jne load_disk_error
    
    cmp ah,0
    jne load_disk_error
        
    jmp load_disk_success