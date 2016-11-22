[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl; save drive in memory


mov bp, 0x9000
mov sp, bp

mov si, MSG_REAL_MODE
call print_string

call load_kernel ; load kernel

call switch_to_pm ; switch to protected mode 32bits

jmp $

%include "io.asm"
%include "gdt.asm"
%include "io_pm.asm"
%include "switch_pm.asm"

[bits 16]
load_kernel:
    mov si, MSG_LOADING_KERNEL
    call print_string
    
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call load_disk
    
    mov si, MSG_LOADING_KERNEL_FINISHED
    call print_string
    
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
    db " Loading kernel... " , 13, 10, 0
MSG_LOADING_KERNEL_FINISHED:
    db " Kernel loaded successfully. " , 13, 10, 0
MSG_REAL_MODE:
    db " Bootloader was started in 16bit mode. " , 13, 10, 0
MSG_PROT_MODE:
    db " Switched to 32bit - Protected Mode " , 0
MSG_KERNEL_EXIT:
    db " Exited from kernel " , 0

times 510-($-$$) db 0
dw 0xaa55


