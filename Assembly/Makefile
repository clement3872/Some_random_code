# Makefile for assembling x86_64 assembly programs with NASM on Linux in the current directory

# Compiler and linker
ASM=nasm
LD=ld

# Assembly format
FORMAT=elf64

# Source files and target names
SOURCES=$(wildcard *.asm)
OBJECTS=$(SOURCES:.asm=.o)
EXECUTABLES=$(SOURCES:.asm=)

# Default target
all: $(EXECUTABLES)

# Rule to create executable files from object files
%: %.o
	$(LD) $< -o $@

# Rule to create object files from assembly source files
%.o: %.asm
	$(ASM) -f $(FORMAT) $< -o $@

# Clean up binary files
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)

.PHONY: all 

