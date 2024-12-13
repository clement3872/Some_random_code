SOURCES = $(wildcard *.java)
CLASSES = $(SOURCES:.java=.class)

all: $(CLASSES)

%.class: %.java
	javac $<

run: all
	java Main

clean:
	rm -f *.class

