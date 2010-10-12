#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include dirs.mk
include version.mk

OBJ_BUILDDIR=obj
LIB_BUILDDIR=lib
LIB_REALNAME=libmormegil.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIB_SONAME=libmormegil.so.$(MAJOR_VER)
LIBMORMEGIL_BUILT=$(LIB_BUILDDIR)/$(LIB_REALNAME)
LIBOBJS=$(OBJ_BUILDDIR)/dice.o
LIBS=$(LIB_BUILDDIR)/$(LIB_REALNAME)
MANPAGES=man/dice.3
SRCARCH_NAME=libmormegil-$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)

# GCC flags
COMMON_FLAGS=-fPIC -I./include
CXXFLAGS=$(COMMON_FLAGS)
LINKSTEP_FLAGS=-shared -fPIC

.PHONY: all clean install install-headers srcarchive

all: $(LIBS)

$(OBJ_BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BUILDDIR)/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIBMORMEGIL_BUILT): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) $< -o $@

clean:
	-rm -f $(LIBS) $(LIBOBJS)
	-rm -rf $(SRCARCH_NAME) $(SRCARCH_NAME).tar.gz

install: install-headers
	cp $(LIBMORMEGIL_BUILT) $(DESTDIR)$(libdir)/$(LIB_REALNAME)
	(cd $(DESTDIR)$(libdir) && ln -s $(LIB_REALNAME) $(LIB_SONAME) )

srcarchive: clean
	mkdir $(SRCARCH_NAME)
	cp -R include lib man obj src Makefile version.mk configure $(SRCARCH_NAME)
	tar cvf $(SRCARCH_NAME).tar.gz $(SRCARCH_NAME)

ifeq ($(oldincludedir),"")
install-headers:
	mkdir -p $(DESTDIR)$(oldincludedir)/libmormegil
	cp include/libmormegil/* $(DESTDIR)$(oldincludedir)/libmormegil
	mkdir -p $(DESTDIR)$(includedir)/libmormegil
	cp include/libmormegil/* $(DESTDIR)$(includedir)/libmormegil
else
install-headers:
	mkdir -p $(DESTDIR)$(includedir)/libmormegil
	cp include/libmormegil/* $(DESTDIR)$(includedir)/libmormegil
endif

# vim:noexpandtab:format=cq
