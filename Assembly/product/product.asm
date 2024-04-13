; This does not compile.
; This is not my code, maybe I'll fix it later

o.rg 100h  ; Set the code to start at memory offset 100h, standard for .COM programs

section .data
input1_msg  db 'Enter First Number: $'
input2_msg  db 'Enter Second Number: $'
result_msg  db 'The Product is: $'

section .bss
number1 resb 1  ; Reserve 1 byte for the first number
number2 resb 1  ; Reserve 1 byte for the second number
product resw 1  ; Reserve a word (2 bytes) for the product

section .text
start:
    ; Get the first number
    mov dx, input1_msg
    call PrintString
    call GetNumber
    mov [number1], al

    ; Get the second number
    mov dx, input2_msg
    call PrintString
    call GetNumber
    mov [number2], al

    ; Multiply the numbers
    mov al, [number1]
    mov bl, [number2]
    mul bl  ; AL = AL * BL, result is in AX
    mov [product], ax

    ; Print the result
    mov dx, result_msg
    call PrintString
    mov ax, [product]
    call PrintNumber

    ; Exit program
    mov ah, 4Ch
    int 21h

PrintString:  ; Function to print a null-terminated string
    push ax
    push dx
    mov ah, 09h
    int 21h
    pop dx
    pop ax
    ret

GetNumber:  ; Function to get a number from the user
    push ax
    mov ah, 01h
    int 21h  ; Read character
    sub al, '0'  ; Convert from ASCII to integer
    pop ax
    ret

PrintNumber:  ; Function to print number in AX
    push ax
    push bx
    push cx
    push dx
    mov bx, 10    ; divisor
    mov cx, 0     ; counter for digits
    xor dx, dx    ; clear dx

PrintNumber_loop:
    div bx       ; divide AX by 10, result in AL, remainder in AH
    push ax      ; store result (without remainder)
    inc cx       ; increment digit count
    test ax, ax  ; test if quotient is 0
    jnz PrintNumber_loop

PrintDigits:
    pop ax       ; get back the stored number
    or al, '0'   ; convert to ASCII
    mov ah, 0Eh  ; function to print single character
    int 10h      ; print character
    loop PrintDigits

    ; Restore registers and return
    pop dx
    pop cx
    pop bx
    pop ax
    ret

times 256-($-$$) db 0  ; Pad the rest of the 256-byte block with zeroes

end start

