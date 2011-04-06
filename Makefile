#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include dirs.mk
include version.mk

OBJ_BUILDDIR=obj
LIB_BUILDDIR=lib
# By default, install as current user and group.
LIBMORMEGIL_OWNERSHIP=
LIBMORMEGIL_DATA_OWNERSHIP=
# For direct system-wide installation, comment previous line and uncomment this:
# LIBMORMEGIL_OWNERSHIP=-o root -g bin
# LIBMORMEGIL_DATA_OWNERSHIP=-o root -g bin

# LIB_REALNAME is exact name of the library
# LIB_SONAME is majorversioned name of the library
# LIB_SHORTNAME is unversioned name of the library
LIB_REALNAME=libmormegil.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIB_SONAME=libmormegil.so.$(MAJOR_VER)
LIB_SHORTNAME=libmormegil.so
LIBMORMEGIL_BUILT=$(LIB_BUILDDIR)/$(LIB_REALNAME)
LIBOBJS=$(OBJ_BUILDDIR)/stlprintf.o $(OBJ_BUILDDIR)/stlfgets.o $(OBJ_BUILDDIR)/points.o $(OBJ_BUILDDIR)/Appcfg.o

LIB_REALNAME_C=libmormegil_c.so.$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH)
LIB_SONAME_C=libmormegil_c.so.$(MAJOR_VER)
LIB_SHORTNAME_C=libmormegil_c.so
LIBMORMEGIL_BUILT_C=$(LIB_BUILDDIR)/$(LIB_REALNAME_C)
LIBOBJS_C=$(OBJ_BUILDDIR)/dice.o

LIBS=$(LIB_BUILDDIR)/$(LIB_REALNAME) $(LIB_BUILDDIR)/$(LIB_REALNAME_C)
ALL_LIBOBJS=$(LIBOBJS) $(LIBOBJS_C)

MANPAGES=man/dice.3 man/libmormegil.3 man/libmormegil::Appcfg.3 man/libmormegil::Coord.3 man/libmormegil::S20prng.3 man/libmormegil::abs.3 man/libmormegil::divup.3 man/libmormegil::isotime.3 man/libmormegil::serialize.3 man/libmormegil::stlfgets.3 man/libmormegil::stlprintf.3

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

.PHONY: all clean install install-headers install-libs srcarchive

all: $(LIBS)

$(OBJ_BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BUILDDIR)/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIBMORMEGIL_BUILT): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) $^ -o $@

$(LIBMORMEGIL_BUILT_C): $(LIBOBJS_C)
	gcc $(LINKSTEP_FLAGS) $^ -o $@

clean:
	-rm -f $(LIBS) $(ALL_LIBOBJS)
	-rm -rf $(SRCARCH_NAME) $(SRCARCH_NAME).tar.gz

install: install-headers install-libs install-docs

install-libs: $(LIBMORMEGIL_BUILT) $(LIBMORMEGIL_BUILT_C)
	install -m 0755 $(LIBMORMEGIL_BUILT) $(DESTDIR)$(libdir)/$(LIB_REALNAME)
	(cd $(DESTDIR)$(libdir) && ln -sf $(LIB_REALNAME) $(LIB_SONAME) && ln -sf $(LIB_SONAME) $(LIB_SHORTNAME) )
	install -m 0755 $(LIBMORMEGIL_BUILT_C) $(DESTDIR)$(libdir)/$(LIB_REALNAME_C)
	(cd $(DESTDIR)$(libdir) && ln -sf $(LIB_REALNAME_C) $(LIB_SONAME_C) && ln -sf $(LIB_SONAME_C) $(LIB_SHORTNAME_C) )

install-docs:
	install -t $(DESTDIR)$(man3dir) -m 0644 $(LIBMORMEGIL_DATA_OWNERSHIP) $(MANPAGES)

srcarchive: clean
	mkdir $(SRCARCH_NAME)
	cp -R include lib man obj src Makefile version.mk configure $(SRCARCH_NAME)
	tar cvf $(SRCARCH_NAME).tar.gz $(SRCARCH_NAME)
	rm -rf $(SRCARCH_NAME)

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
