SOURCES = $(wildcard *.java)
CLASSES = $(SOURCES:.java=.class)

# Detect the main class by looking for the one with the main method
MAIN_CLASS = $(shell grep -l 'public static void main' *.java | sed 's/\.java//')

all: $(CLASSES)
	java $(MAIN_CLASS)

%.class: %.java
	javac $<

clean:
	rm -f *.class

