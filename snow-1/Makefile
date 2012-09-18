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
LDFLAGS += 
LDLIBS += -lSDLmain -lSDL -lSDL_gfx -lSDL_image

all: snow

snow: snow.cpp

clean:
	-rm -f snow

install: snow
	cp snow $(DESTDIR)$(PREFIX)/bin/snow


.PHONY: all install clean

# end of development makefile
