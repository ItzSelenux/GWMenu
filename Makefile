VERSION := $(shell cat VERSION)
CFLAGS = `pkg-config --cflags gtk+-3.0` -Dmver=\"$(VERSION)\" -Wall
CC = cc
LIBS = `pkg-config --libs gtk+-3.0`
SRC = gwmenu.c gwmenu-cfg.c
OBJ = $(SRC:.c=.o)
EXE = gwmenu

PREFIX = /usr
BIN_DIR = $(PREFIX)/bin
APP_DIR = $(PREFIX)/share/applications

all: $(EXE)
gwmenu: gwmenu.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -lm
gwmenu-cfg: gwmenu-cfg.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -lm
debug: gwmenu.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS) -lm -g
test:
	./$(EXE)
install:
	install -Dm755 $(EXE) $(BIN_DIR)/$(EXE)
	install -Dm644 $(EXE).desktop $(APP_DIR)/$(EXE).desktop
	install -Dm644 icons/gwmenu.svg $(PREFIX)/share/icons/hicolor/48x48/apps/gwmenu.svg
uninstall:
	rm $(BIN_DIR)/$(EXE)
	rm $(APP_DIR)/$(EXE).desktop
	rm $(PREFIX)/share/icons/hicolor/64x64/apps/menulibre.png
clean:
	rm -f $(OBJ) $(EXE) debug
