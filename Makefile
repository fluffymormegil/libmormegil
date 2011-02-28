#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include dirs.mk
include version.mk

OBJ_BUILDDIR=obj
LIB_BUILDDIR=lib
# LIB_REALNAME = exact name of the library
# LIB_SONAME = name of the library from the linker's point of view
# LIB_SHORTNAME = unversioned name of the library
LIB_REALNAME=libmormegil.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIB_SONAME=libmormegil.so.$(MAJOR_VER)
LIB_SHORTNAME=libmormegil.so
LIBMORMEGIL_BUILT=$(LIB_BUILDDIR)/$(LIB_REALNAME)
LIBOBJS=$(OBJ_BUILDDIR)/dice.o $(OBJ_BUILDDIR)/stlprintf.o $(OBJ_BUILDDIR)/stlfgets.o
LIBS=$(LIB_BUILDDIR)/$(LIB_REALNAME)
MANPAGES=man/dice.3
SRCARCH_NAME=libmormegil-$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)

# GCC flags
#  1. This is a shared library, so we need -fPIC (position-independent code)
#     when building each of the modules.
#  2. We need THIS version's headers to take precedence over the system
#     headers.
COMMON_FLAGS=-fPIC -I./include -DLIBMORMEGIL_MAJVER=$(MAJOR_VER) -DLIBMORMEGIL_MINVER=$(MINOR_VER) -DLIBMORMEGIL_COMPAT_DEPTH=$(COMPAT_DEPTH)
CXXFLAGS=$(COMMON_FLAGS)
#  3. For linking, we have to specify that the output should be a shared
#     object and, as before, that we want position-independent code.
LINKSTEP_FLAGS=-shared -fPIC
CFLAGS=$(COMMON_FLAGS)

.PHONY: all clean install install-headers srcarchive

all: $(LIBS)

$(OBJ_BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BUILDDIR)/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIBMORMEGIL_BUILT): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) $^ -o $@

clean:
	-rm -f $(LIBS) $(LIBOBJS)
	-rm -rf $(SRCARCH_NAME) $(SRCARCH_NAME).tar.gz

install: install-headers
	cp $(LIBMORMEGIL_BUILT) $(DESTDIR)$(libdir)/$(LIB_REALNAME)
	(cd $(DESTDIR)$(libdir) && ln -sf $(LIB_REALNAME) $(LIB_SONAME) && ln -sf $(LIB_SONAME) $(LIB_SHORTNAME) )

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

# vim:noexpandtab:fo=c
