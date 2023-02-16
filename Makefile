AS=gcc
CC=gcc
CXX=g++
AFLAGS=-s -Wall -Wextra -Werror -static -Os -m64 -nostartfiles -nostdlib \
       -masm=intel -Wl,--build-id=none -Wl,--nmagic
CFLAGS=-std=gnu11 -Os -pedantic -Wall -Wextra -Werror -D_GNU_SOURCE
CXXFLAGS=-std=gnu++20 -Os -pedantic -Wall -Wextra -Werror
PROGS=uname ps pstree killall statx

all: $(PROGS)

%: %.S
	$(AS) $(AFLAGS) -o $@ $<

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)

.PHONY: all clean
