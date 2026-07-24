CC = gcc

TARGET = qfetch

CFLAGS = -lcurl -lcjson -o $(TARGET)

PREFIX = /usr

all: $(TARGET)

install: 
	$(CC) main.c $(CFLAGS)
	install -m 755 $(TARGET) $(PREFIX)/bin

uninstall: 
	rm $(PREFIX)/bin/$(TARGET)

clean:
	rm -f ./$(TARGET)
