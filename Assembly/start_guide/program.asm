.global _start
.intel_syntax
.section .text

_start:

  # Loop to print "Hello, World" twice
  mov %r8, 2         # Number of times to print "Hello, World"
loop:
  # write the output
  mov %rax, 1           # syscall number for sys_write
  mov %rdi, 1           # stdin = 0; stdout = 1; stderror = 2 - stdout is where we write to
  lea %rsi, [message]   # lea = load effective address
  mov %rdx, 13          # size of the message
  syscall               # also called an interrupt

  dec %r8              # Decrement the loop counter
  cmp %r8, 0           # Compare rcx with 1
  je exit               # Jump to done if rcx equals 1
  jmp loop              # Jump back to loop

  # for demonstration purposes
  mov %rdi, %rax      # rdi = rax
  mov %rdi, 0         # the number for the exit code
  add %rdi, 123       # add 123 to rdi
  sub %rdi, 12        # subtract 12 to rdi

  # exit the program
exit:
  mov %rax, 60    # syscall for exit (just to make sure)
  mov %rdi, 1     # exit number code
  syscall



.section .data
  message: .ascii "Hello, World\n"

