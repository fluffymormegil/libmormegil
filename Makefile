#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include dirs.mk
include version.mk

# If your default shell is not sufficiently POSIXesque, you may need to set
# the SHELL makefile variable.

# SHELL=/path/to/posixesque/shell

OBJ_BUILDDIR=obj
LIB_BUILDDIR=lib
INC_DIR=include/libmormegil

# LIB_REALNAME is exact name of the library
# LIB_SONAME is majorversioned name of the library
# LIB_SHORTNAME is unversioned name of the library
LIBMORMEGIL_STATIC:=libmormegil.a
LIBMORMEGIL_REALNAME:=libmormegil.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIBMORMEGIL_SONAME:=libmormegil.so.$(MAJOR_VER)
LIBMORMEGIL_SHORTNAME=libmormegil.so
LIBMORMEGIL_STATIC_BUILT:=$(LIB_BUILDDIR)/$(LIBMORMEGIL_STATIC)
LIBMORMEGIL_SHARED_BUILT:=$(LIB_BUILDDIR)/$(LIBMORMEGIL_REALNAME)
LIBOBJS:=$(OBJ_BUILDDIR)/stlprintf.o $(OBJ_BUILDDIR)/stlwprintf.o $(OBJ_BUILDDIR)/stlfgets.o $(OBJ_BUILDDIR)/points.o $(OBJ_BUILDDIR)/Appcfg.o $(OBJ_BUILDDIR)/ordinaldate.o $(OBJ_BUILDDIR)/dice.o

LIBS:=$(LIBMORMEGIL_SHARED_BUILT) $(LIBMORMEGIL_STATIC_BUILT)
ALL_LIBOBJS:=$(LIBOBJS) $(LIBOBJS_C)

MANPAGES=man/dice.3 man/libmormegil.3 man/libmormegil::Appcfg.3 man/libmormegil::Coord.3 man/libmormegil::S20prng.3 man/libmormegil::abs.3 man/libmormegil::divup.3 man/libmormegil::isotime.3 man/libmormegil::serialize.3 man/libmormegil::stlfgets.3 man/libmormegil::stlprintf.3

SRCARCH_NAME:=libmormegil-$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
# The list of what goes in the deliverable source archive. Only subsystems
# which I deem "ready" get put into the deliverable archive.
SRCARCH_SRC:=src/Appcfg.cc src/dice.cc src/points.cc src/stlfgets.cc src/ordinaldate.cc src/stlprintf.cc src/stlwprintf.cc
SRCARCH_INC:=$(INC_DIR)/dice.h $(INC_DIR)/isotime.h $(INC_DIR)/Appcfg.hh $(INC_DIR)/Coord.hh $(INC_DIR)/Points.hh $(INC_DIR)/S20prng.hh $(INC_DIR)/abs.hh $(INC_DIR)/divup.hh $(INC_DIR)/serial.hh $(INC_DIR)/sign.hh $(INC_DIR)/stlfgets.hh $(INC_DIR)/stlprintf.hh $(INC_DIR)/stlwprintf.hh
SRCARCH_MAN=man/libmormegil.3 man/dice.3 man/libmormegil::Appcfg.3 man/libmormegil::Coord.3 man/libmormegil::Points.3 man/libmormegil::S20prng.3 man/libmormegil::abs.3 man/libmormegil::divup.3 man/libmormegil::isotime.3 man/libmormegil::serialize.3 man/libmormegil::sign.3 man/libmormegil::stlfgets.3 man/libmormegil::stlprintf.3
SRCARCH_LIC=CC0 BSD-lite COPYING Copyright
SRCARCH_EXA=examples/dice-test.c examples/coord-test.cc
SRCARCH_TOP:=$(SRCARCH_LIC) README changelog configure version.mk Makefile Bugs

# GCC flags
#  1. This is a shared library, so we need -fPIC (position-independent code)
#     when building each of the modules.
#  2. We need THIS version's headers to take precedence over the system
#     headers.
#  3. CFLAGS and CXXFLAGS are for the user!
COMMON_FLAGS:=-fPIC -I./include -DLIBMORMEGIL_MAJVER=$(MAJOR_VER) -DLIBMORMEGIL_MINVER=$(MINOR_VER) -DLIBMORMEGIL_COMPAT_DEPTH=$(COMPAT_DEPTH)
CXXFLAGS=
#  3. For linking, we have to specify that the output should be a shared
#     object and, as before, that we want position-independent code.
LINKSTEP_FLAGS=-shared -fPIC
CFLAGS=

.PHONY: all clean install install-headers install-libs srcarchive

all: $(LIBS)

$(OBJ_BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(COMMON_FLAGS) -c $< -o $@

$(OBJ_BUILDDIR)/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) $(COMMON_FLAGS) -c $< -o $@

$(LIBMORMEGIL_SHARED): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) -Wl,-soname,$(LIBMORMEGIL_SONAME) $^ -o $@

$(LIBMORMEGIL_STATIC): $(LIBOBJS)
	ar rcs $@ $^

clean:
	-rm -f $(LIBS) $(ALL_LIBOBJS)
	-rm -rf $(SRCARCH_NAME) $(SRCARCH_NAME).tar.gz

distclean: clean
	-rm -f dirs.mk

install: install-headers install-libs install-docs

# Note that this does _not_ create symlinks. That's ldconfig's job.
install-libs: $(LIBMORMEGIL_SHARED_BUILT)
	mkdir -p $(DESTDIR)$(libdir)
	install -m 0755 $(LIBMORMEGIL_STATIC_BUILT) $(DESTDIR)$(libdir)/$(LIBMORMEGIL_STATIC)
	install -m 0755 $(LIBMORMEGIL_SHARED_BUILT) $(DESTDIR)$(libdir)/$(LIBMORMEGIL_REALNAME)

install-docs:
	mkdir -p $(DESTDIR)$(man3dir)
	install -t $(DESTDIR)$(man3dir) -m 0644 $(MANPAGES)

srcarchive: clean
	mkdir -p ./$(SRCARCH_NAME)
	cp $(SRCARCH_TOP) ./$(SRCARCH_NAME)
	mkdir -p ./$(SRCARCH_NAME)/src
	cp $(SRCARCH_SRC) ./$(SRCARCH_NAME)/src
	mkdir -p ./$(SRCARCH_NAME)/include/libmormegil
	cp $(SRCARCH_INC) ./$(SRCARCH_NAME)/include/libmormegil
	mkdir -p ./$(SRCARCH_NAME)/man
	cp $(SRCARCH_MAN) ./$(SRCARCH_NAME)/man
	mkdir -p ./$(SRCARCH_NAME)/examples
	cp $(SRCARCH_EXA) ./$(SRCARCH_NAME)/examples
	mkdir -p ./$(SRCARCH_NAME)/obj
	touch ./$(SRCARCH_NAME)/obj/placeholder.txt
	mkdir -p ./$(SRCARCH_NAME)/lib
	touch ./$(SRCARCH_NAME)/lib/placeholder.txt
	tar cvzf ./$(SRCARCH_NAME).tar.gz ./$(SRCARCH_NAME)
	rm -rf ./$(SRCARCH_NAME)

ifeq ($(oldincludedir),"")
install-headers:
	mkdir -p $(DESTDIR)$(oldincludedir)/libmormegil
	install -t $(DESTDIR)$(oldincludedir)/libmormegil include/libmormegil/*
	mkdir -p $(DESTDIR)$(includedir)/libmormegil
	install -t $(DESTDIR)$(includedir)/libmormegil include/libmormegil/*
else
install-headers:
	mkdir -p $(DESTDIR)$(includedir)/libmormegil
	install -t $(DESTDIR)$(includedir)/libmormegil include/libmormegil/* 
endif

# vim:noexpandtab:fo=croq
