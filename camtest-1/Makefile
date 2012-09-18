#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CFLAGS += -O2 -g -Wall #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS +=


all: camtest
	$(CC) -Wall -std=gnu99  -O3 camtest.c -o camtest 

clean:
	-rm -f camtest

install:


.PHONY: all install clean

# end of development makefile
