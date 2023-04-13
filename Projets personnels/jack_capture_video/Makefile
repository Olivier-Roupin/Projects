PREFIX ?= /usr/local
bindir = $(PREFIX)/bin

VERSION=0.9.73

CC=gcc
CPP=g++

# Needed on OSX
CFLAGS += -I/opt/local/include#-Iinclude

OPTIMIZE=-O3
#OPTIMIZE=-O0 -g

COMPILEFLAGS=$(CFLAGS) $(OPTIMIZE) -DVERSION=\"$(VERSION)\" -Wall -Wextra -Wno-unused
LINKFLAGS=$(LDFLAGS) -ljack -lsndfile -lm -lpthread -latomic

OS := $(shell uname)
ifneq ($(OS),Darwin)
	LINKFLAGS += -lrt
endif

targets = jack_capture_video

all: check_dependencies jackpp

cpp: check_dependencies jacklib jackpp

install: $(targets)
	install -d $(DESTDIR)$(bindir)
	install -m755 $(targets) $(DESTDIR)$(bindir)

uninstall:
	rm -f $(DESTDIR)$(bindir)/jack_capture_video
	-rmdir $(DESTDIR)$(bindir)

check_dependencies:
	@echo
	@echo "Checking dependencies: "
	which bash
	which tr
	which sed
	which install
	which pkg-config
	which $(CC)
	which $(CPP)
	$(CC) $(CFLAGS) -E testsndfile.c >/dev/null
	@echo "All seems good "
	@echo

dist: clean
	rm -fr /tmp/jack_capture_video-$(VERSION)
	rm -fr jack_capture_video-$(VERSION)
	mkdir /tmp/jack_capture_video-$(VERSION)
	cp -a * /tmp/jack_capture_video-$(VERSION)/
	mv /tmp/jack_capture_video-$(VERSION) .
	tar cvf jack_capture_video-$(VERSION).tar jack_capture_video-$(VERSION)
	gzip jack_capture_video-$(VERSION).tar
	marcel_upload jack_capture_video-$(VERSION).tar.gz
	ls -la jack_capture_video-$(VERSION)
	rm -fr jack_capture_video-$(VERSION)

jacklib: setformat.c libjackc.c libjackc.h Makefile das_config.h
	$(CC) -c $(COMPILEFLAGS) libjackc.c `cat config_flags` -o libjackc.o #$(LINKFLAGS)
	ar -crsv libjackc.a libjackc.o

jackpp: jack_capture_video.cpp Makefile das_config.h config_flags
	$(CC)  -c $(COMPILEFLAGS) vringbuffer.c    `cat config_flags` -o build/vringbuffer.o
	$(CC)  -c $(COMPILEFLAGS) upwaker.c 		   `cat config_flags` -o build/upwaker.o
	$(CC)  -c $(COMPILEFLAGS) libjackc.c 	     `cat config_flags` -o build/libjackc.o
	$(CPP) -c $(COMPILEFLAGS) jack_capture_video.cpp `cat config_flags` -o build/jack_capture_video.o
	$(CPP) $(COMPILEFLAGS) -o jackpp build/*.o $(LINKFLAGS) `pkg-config --cflags --libs opencv` `cat config_flags`

config_flags: Makefile das_config.h
	cat das_config.h |grep COMPILEFLAGS|sed s/\\/\\/COMPILEFLAGS//|tr '\n' ' ' >config_flags

das_config.h: gen_das_config_h.sh
	bash gen_das_config_h.sh >das_config.h
	@echo
	@echo "jack_capture_video was configured with the following options:"
	@echo "------------------------------"
	@cat das_config.h
	@echo "------------------------------"
	@echo

setformat.c: gen_setformat_c.sh
	bash gen_setformat_c.sh >setformat.c


clean:
	rm -f *~ jack_capture_video libjackc.a config_flags temp.c* setformat.c* das_config.h* a.out *.gz  *.orig "#*"
