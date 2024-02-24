CC=gcc # defines the compiler
CFLAGS=$(shell pkg-config --cflags gtk4) # compiler flags
LIBS=$(shell pkg-config --libs gtk4) # linker flags
INPUTS=$(wildcard *.c) # uses wildcard to match all .c files (that we'll compile)
OUTPUT=application # output file name

# declares it as target i.e. they don't represent actual files
.PHONY: all clean run 

# The all target depends on $(OUTPUT)
all: $(OUTPUT)

# Compiles the .c files into an executable
$(OUTPUT): $(INPUTS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(INPUTS) $(LIBS)

# The run target depends on all and executes the compiled program
run: all
	./$(OUTPUT)

# The clean target removes the compiled executable
clean:
	rm -f $(OUTPUT)
