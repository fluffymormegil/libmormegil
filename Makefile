#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include version.mk
LIBDIR=$(DESTDIR)lib
OBJDIR=$(DESTDIR)obj
MANDIR=$(DESTDIR)man
INCDIR=./include

LIBMORMEGIL=$(LIBDIR)/libmormegil.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIBOBJS=$(OBJDIR)/dice.o
MANPAGES=$(MANDIR)/dice.3

# GCC flags
COMMON_FLAGS=-fPIC -I$(INCDIR)
CXXFLAGS=$(COMMON_FLAGS)
LINKSTEP_FLAGS=-shared -fPIC

all: libs demos

libs: $(LIBMORMEGIL)

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIBMORMEGIL): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) $< -o $@

clean:
	-rm -f $(LIBMORMEGIL) $(OBJDIR)/*.o

# vim:noexpandtab:format=cq
