[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl; save drive in memory


mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call load_kernel ; load kernel

jmp $

%include "io.asm"
%include "gdt.asm"
%include "io_pm.asm"
%include "switch_pm.asm"

[bits 16]
load_kernel:
    xor si,si
    loop_device:
        mov al, [DRIVES_LIST+si]
        cmp al, [BOOT_DRIVE]
             
        push si ; push counter to stack
        je loop_device_increment ;we should not try to load from same device as bootloader   
    
        mov bx, MSG_LOADING_KERNEL
        call print_string
        
        mov al, [DRIVES_LIST+si]
        call print_hex_byte        
        
        call print_new_line
        
        mov bx, KERNEL_OFFSET ; where to load
        mov dh, 15 ; how many sectors to load
        mov dl, [DRIVES_LIST+si] ; from which drive to load
        jmp load_disk  
        
        load_disk_success:
        ; if we are here, we can switch to pm; our kernel is loaded
        pop si ; remove this from stack
        mov bx,MSG_KERNEL_EXIT
        call print_string      
        call switch_to_pm ; switch to protected mode 32bits
                
        load_disk_error:
        mov bx,MSG_LOADING_KERNEL_FAILED
        call print_string
                
        loop_device_increment:
        pop si ; pop counter from stack
        inc si
        cmp si,[DRIVES_COUNT]
        jl loop_device
    ret

[bits 32]
begin_pm:
    mov ebx, MSG_PROT_MODE
    call print_string_pm
    
    call KERNEL_OFFSET
    
    mov ebx, MSG_KERNEL_EXIT
    call print_string_pm
    
    jmp $

BOOT_DRIVE:
    db 0
MSG_LOADING_KERNEL:
    db " Trying to load kernel from " , 0
MSG_LOADING_KERNEL_FAILED:
    db " Failed to load " , 13,10,0
MSG_REAL_MODE:
    db " Bootloader was started in 16bit mode. " , 13, 10, 0
MSG_PROT_MODE:
    db " Switched to 32bit - Protected Mode " , 0
MSG_KERNEL_EXIT:
    db " Exited from kernel " , 0
DRIVES_LIST:
    db 0x00,0x01,0x80,0x81
DRIVES_COUNT:
    db 0x4

times 510-($-$$) db 0
dw 0xaa55