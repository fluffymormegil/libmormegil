#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include dirs.mk
include version.mk

OBJ_BUILDDIR=obj
LIB_BUILDDIR=lib
LIB_REALNAME=libmormegil.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIB_SONAME=libmormegil.so.$(MAJOR_VER)
LIBMORMEGIL=$(LIB_BUILDDIR)/$(LIB_REALNAME)
LIBOBJS=$(OBJ_BUILDDIR)/dice.o
LIBS=$(LIB_BUILDDIR)/$(LIB_REALNAME)
MANPAGES=man/dice.3

# GCC flags
COMMON_FLAGS=-fPIC -I./include
CXXFLAGS=$(COMMON_FLAGS)
LINKSTEP_FLAGS=-shared -fPIC

.PHONY: all clean install install-headers

all: $(LIBS)

$(OBJ_BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BUILDDIR)/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIBMORMEGIL): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) $< -o $@

clean:
	-rm -f $(LIBS) $(LIBOBJS)

install: install-headers
	cp $(LIBMORMEGIL_BUILT) $(DESTDIR)$(libdir)/$(LIB_REALNAME)
	(cd $(DESTDIR)$(libdir) && ln -s $(LIB_REALNAME) $(LIB_SONAME) )

ifeq ($(oldincludedir),"")
install-headers:
	mkdir -p $(DESTDIR)$(oldincludedir)/libmormegil
	cp $(INCDIR)/libmormegil/* $(DESTDIR)$(oldincludedir)/libmormegil
	mkdir -p $(DESTDIR)$(includedir)/libmormegil
	cp $(INCDIR)/libmormegil/* $(DESTDIR)$(includedir)/libmormegil
else
install-headers:
	mkdir -p $(DESTDIR)$(includedir)/libmormegil
	cp $(INCDIR)/libmormegil/* $(DESTDIR)$(includedir)/libmormegil
endif

# vim:noexpandtab:format=cq
