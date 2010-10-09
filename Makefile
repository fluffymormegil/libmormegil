#! /usr/bin/make -f
# Makefile - makefile for building libmormegil.so

include version.mk
LIBDIR=$(DESTDIR)lib
OBJDIR=$(DESTDIR)obj

LIBTARGET=$(LIBDIR)/libmormegil-$(MAJOR_VER).$(MINOR_VER).$(COMPAT_DEPTH).so
LIBOBJS=$(OBJDIR)/dice.o

# GCC flags
COMMON_FLAGS=-fPIC -I./include
CXXFLAGS=$(COMMON_FLAGS)
LINKSTEP_FLAGS=-shared -fPIC

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(LIBTARGET): $(LIBOBJS)
	gcc $(LINKSTEP_FLAGS) $< -o $@

clean:
	-rm -f $(LIBTARGET) $(OBJDIR)/*.o

# vim:noexpandtab:format=cq
