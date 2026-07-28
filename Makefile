CC = gcc

TARGET = qfetch

SRCDIR = ./src

CFLAGS = -lcurl -lcjson -o $(TARGET)

MACOS_PREFIX = /usr/local

PREFIX = /usr

all: $(TARGET)

install_mac: 
	$(CC) $(SRCDIR)/main.c $(CFLAGS)
	install -m 755 $(TARGET) $(MACOS_PREFIX)/bin

install: 
	$(CC) $(SRCDIR)/main.c $(CFLAGS)
	install -m 755 $(TARGET) $(PREFIX)/bin

uninstall: 
	rm $(PREFIX)/bin/$(TARGET)

clean:
	rm -f ./$(TARGET)
