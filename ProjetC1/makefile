CC=gcc
CFLAGS=-Wall
LDFLAGS=-lSDL2 -lSDL2_image -lm
SRCFILES=$(wildcard *.c)
OBJFILES=$(patsubst %.c, %.o, $(SRCFILES))
TARGET=PROJETC1

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
