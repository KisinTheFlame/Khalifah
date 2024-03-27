EX1629_SRC_DIR = $(PWD)
export SHARED_DIR = $(EX1629_SRC_DIR)/shared
export LIBEX1629_DIR = $(EX1629_SRC_DIR)/libex1629
export CLIENT_DIR = $(EX1629_SRC_DIR)/client

export LIBEX1629_LIB = $(LIBEX1629_DIR)/libex1629.a

export CLIENT_DISTRIB = y

export CFLAGS += -Wall -O3 -I$(SHARED_DIR) 
export SHARED_DIR = $(EX1629_SRC_DIR)/shared

# update VPATH so make can find everything it needs
export VPATH += $(SHARED_DIR)

all:
	cd shared && $(MAKE)
	cd libex1629 && $(MAKE)

clean:
	cd shared && $(MAKE) clean
	cd libex1629 && $(MAKE) clean
