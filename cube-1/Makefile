#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
PREFIX := /usr
CFLAGS += -O2 -g -Wall #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS += -lSDLmain -lSDL -lSDL_gfx -lSDL_image


all: cube

cube: cube.cpp

clean:
	-rm -f cube

install: cube
	cp cube $(DESTDIR)$(PREFIX)/bin/cube


.PHONY: all install clean

# end of development makefile
