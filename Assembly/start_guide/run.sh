as program.asm -o program.o
ld program.o -o program.elf
./program.elf
echo process returned code: $?
rm program.o program.elf
