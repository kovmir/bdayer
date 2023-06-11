CC ?= cc

CFLAGS += -std=c99
CFLAGS += -pedantic
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wcast-align
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef

PREFIX ?= /usr/local
PROJECT = bdayer

INSTALL ?= install
STRIP ?= strip

all:
	$(CC) $(CFLAGS) -O3 $(PROJECT).c -o $(PROJECT)

debug:
	$(CC) $(CFLAGS) -g $(PROJECT).c -o $(PROJECT)

gdb: debug
	gdb ./$(PROJECT)

memcheck: debug
	valgrind --leak-check=yes ./$(PROJECT)

memcheck_v: debug
	valgrind --leak-check=yes -v ./$(PROJECT)

memcheck_full: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROJECT)

clean:
	rm -f ./$(PROJECT)

strip:
	$(STRIP) ./$(PROJECT)

install:
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	$(INSTALL) ./$(PROJECT) "$(DESTDIR)$(PREFIX)/bin/$(PROJECT)"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/$(PROJECT)"
	rmdir --ignore-fail-on-non-empty "$(DESTDIR)$(PREFIX)/bin"

.PHONY: all debug gdb memcheck memcheck_v memcheck_full clean strip install uninstall
