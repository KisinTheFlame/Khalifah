RPCGEN=rpcgen
# newstyle rpcgen, MT safe
RPCFLAGS= -N -M

SHARED_CSRC = \
	ex1629_xdr.c \
	ex1629_clnt.c \
	ex1629_svc.c \
	ex1629_errors.c

SHARED_HDRS = ex1629.h

ifndef CLIENT_DISTRIB
SHARED_CSRC += pdr.c
SHARED_HDRS += pdr.h
endif

SHARED_OBJS = $(patsubst %.c,%.o, $(SHARED_CSRC))

VERSION_FILE = version
PDR = pdr.a
PDR_OBJS = pdr.o

ALL_OBJS = $(SHARED_OBJS)

ifndef CLIENT_DISTRIB
ALL_OBJS += $(PDR_OBJS)
endif

# turn off unused variable warnings on the RPC code
# since there are many unused buf variables and building with -Werror
# causes these to kill the build
CFLAGS += -I/usr/include/tirpc -I$(DRIVER_DIR)/ -Wno-unused-variable -ltirpc

ifdef CLIENT_DISTRIB
all: $(SHARED_CSRC) $(SHARED_HDRS) $(SHARED_OBJS)
else
all: $(SHARED_CSRC) $(SHARED_HDRS) $(SHARED_OBJS) $(PDR) $(VERSION_FILE)
endif

# EX1629 auto-dependency generation
-include $(EX1629_ROOT)/AutoDep
-include $(ALL_OBJS:.o=.P)

$(PDR): $(PDR_OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(VERSION_FILE): ex1629_version.h
ifdef CONFIG_USER_EX1629_BUILDING_RECOVERY
	echo "Making recovery image"
	sleep 5
	./make_version_file.sh RECOVERY
else
	./make_version_file.sh
endif

# RPC files
# these need to be generated one at a time to control the server
# creation properly
ex1629_clnt.c: ex1629.x Makefile
	$(RM) -f $@
	$(RPCGEN) $(RPCFLAGS) -l -o $@ ex1629.x
ex1629_svc.c: ex1629.x Makefile
	$(RM) -f $@
	$(RPCGEN) $(RPCFLAGS) -m -o $@ ex1629.x
ex1629.h: ex1629.x Makefile
	$(RM) -f $@
	$(RPCGEN) $(RPCFLAGS) -h -o $@ ex1629.x
ex1629_xdr.c: ex1629.x Makefile
	$(RM) -f $@
	$(RPCGEN) $(RPCFLAGS) -c -o $@ ex1629.x

clean:
	rm -f ex1629_clnt.c ex1629_svc.c ex1629.h ex1629_xdr.c *.o *.P
	rm -f $(PDR)
	rm -f TAGS tags
	rm -f $(VERSION_FILE)

.PHONY: tags
tags: $(CURDIR)/tags

.PHONY: TAGS
TAGS: $(CURDIR)/TAGS

$(CURDIR)/tags: *.[ch]
	ctags $^

$(CURDIR)/TAGS: *.[ch]
	etags $^
