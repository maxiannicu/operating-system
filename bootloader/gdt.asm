gdt_start:

gdt_null: ; the mandatory null descriptor
    dd 0x0 ; ’ dd ’ means define double word ( i.e. 4 bytes )
    dd 0x0
gdt_code:
    dw 0xffff ; Limit ( bits 0 -15)
    dw 0x0 ; Base ( bits 0 -15)
    db 0x0 ; Base ( bits 16 -23)
    db 10011010b ; 1 st flags , type flags 434
    db 11001111b ; 2 nd flags , Limit ( bits 16 -19)
    db 0x0 ; Base ( bits 24 -31)

gdt_data : 
    dw 0xffff ; Limit ( bits 0 -15)
    dw 0x0 ; Base ( bits 0 -15)
    db 0x0
    db 10010010b ; 1 st flags , type flags
    db 11001111b ; 2 nd flags , Limit ( bits 16 -19)
    db 0x0

gdt_end :

gdt_descriptor :
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start