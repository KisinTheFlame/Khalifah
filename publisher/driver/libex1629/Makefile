CFLAGS += -I/usr/include/tirpc -I$(SHARED_DIR) -I$(DRIVER_DIR) -Wno-unused-variable -ltirpc

LIBEX1629 = libex1629.a

# separate group for RPC objects to allow us to disable the
# compilers unused variable warning
LIBEX1629_RPC_OBJS = \
	$(SHARED_DIR)/ex1629_clnt.o \
	$(SHARED_DIR)/ex1629_xdr.o

LIBEX1629_OBJS = \
	cal.o \
	dio.o \
	reg_iface.o \
	main.o  \
	version.o \
	scanlist.o \
	config.o \
	trigger.o \
	excitation.o \
	conf.o \
	gain.o \
	filter.o \
	lock.o \
	fifo.o \
	streaming.o \
	euconv.o \
	compres.o \
	inputmux.o \
	shunt.o \
	teds.o \
	exreset.o \
	serialnum.o \
	selfcal.o \
	selftest.o \
	profiling.o \
	timestamp.o \
	leds.o \
	corevolt.o \
	limits.o \
	leadwire.o

ALL_OBJS = $(LIBEX1629_OBJS) $(LIBEX1629_RPC_OBJS)

all:	$(LIBEX1629)

# EX1629 auto-dependency generation
-include $(EX1629_ROOT)/AutoDep
-include $(ALL_OBJS:.o=.P)

$(LIBEX1629): $(LIBEX1629_OBJS) $(LIBEX1629_RPC_OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(LIBEX1629) $(ALL_OBJS)
	rm -f TAGS tags
	rm -f *.o *.P

install:

.PHONY: tags
tags: $(CURDIR)/tags

.PHONY: TAGS
TAGS: $(CURDIR)/TAGS

$(CURDIR)/tags: *.[ch]
	ctags $^

$(CURDIR)/TAGS: *.[ch]
	etags $^
