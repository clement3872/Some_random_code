section .data
    hello_msg: db 'Hello, World!',0xA   ; 'Hello, World!' followed by a newline character
    hello_len: equ $ - hello_msg        ; Calculate the length of the string

section .text
    global _start

_start:
    mov eax, 4                  ; The system call for write (sys_write)
    mov ebx, 1                  ; File descriptor 1 is stdout
    mov ecx, hello_msg          ; Pointer to the message to write
    mov edx, hello_len          ; Message length
    int 0x80                    ; Call kernel

    mov eax, 1                  ; System call for exit (sys_exit)
    xor ebx, ebx                ; Return 0 status
    int 0x80                    ; Call kernel

