[BITS 16]	;Tells the assembler that its a 16 bit code
[ORG 0x7C00]	;Origin, tell the assembler that where the code will
		;be in memory after it is been loaded

; Print Enter name message
mov si,MessageEnterFirstName
CALL PrintString

mov si,FirstName
CALL InputString

mov si,MessageEnterLastName
CALL PrintString

mov si,LastName
CALL InputString


; Print Welcome message
mov si,Message
CALL PrintString


; Print Name
mov si,FirstName
CALL PrintString

mov si,LastName
CALL PrintString


JMP $ 		;Infinite loop, hang it here.

NewLine:
	mov al,10
	call PrintCharacter
	mov al,13
	call PrintCharacter
RET

InputChar:
	mov ax, 0
	int 0x16
RET

InputString:
	iterate_input_char:
		call InputChar
		
		cmp al,0x0D ; compare if new line
		je exit_input_string
		
		call PrintCharacter
		mov [si],al
		inc si
		jmp iterate_input_char
	exit_input_string:
		mov al,0x00	
		inc si	
		mov [si],al
		call NewLine
RET		;Return to calling procedure
	
RET

PrintCharacter:	;Procedure to print character on screen
	;Assume that ASCII value is in register AL
MOV AH, 0x0E	;Tell BIOS that we need to print one charater on screen.
MOV BH, 0x00	;Page no.
MOV BL, 0x0F	

INT 0x10	;Call video interrupt
RET		;Return to calling procedure


PrintString:	;Procedure to print string on screen
	iterate_char:
		mov al,[si]
		inc si
		or al,al
		jz exit_print_string
		call PrintCharacter
		jmp iterate_char
	exit_print_string:
RET		;Return to calling procedure


;data

MessageEnterFirstName db "Please enter your first name(20 chars):",0
MessageEnterLastName db "Please enter your last name(20 chars):",0
FirstName times 21 db 0
LastName times 21 db 0
Message db "Hello, ",0


TIMES 510 - ($ - $$) db 0	;Fill the rest of sector with 0
DW 0xAA55			;Add boot signature at the end of bootloader
