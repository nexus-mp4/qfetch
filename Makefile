CC = gcc

TARGET = qfetch

SRCDIR = ./src

CFLAGS = -lcurl -lcjson -o $(TARGET)

PREFIX = /usr

all: $(TARGET)

install: 
	$(CC) $(SRCDIR)/main.c $(CFLAGS)
	install -m 755 $(TARGET) $(PREFIX)/bin

uninstall: 
	rm $(PREFIX)/bin/$(TARGET)

clean:
	rm -f ./$(TARGET)
