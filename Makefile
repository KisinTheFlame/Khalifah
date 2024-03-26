APPLICATION=khalifah

DIR_INTERFACE=$(PWD)/interface
DIR_SERVER=$(PWD)/server
DIR_LIBRARY=$(PWD)/library
DIR_DATABASE=$(PWD)/database
DIR_BUILD=$(PWD)/build

SERVER_FILES=$(shell find $(DIR_SERVER))

WEBROOT=webroot
DB=data.db

# local platform
LOCAL_TAG=LOCAL
LOCAL_ARCH=amd64
LOCAL_OS=linux
LOCAL_CC=gcc
LOCAL_CXX=g++
LOCAL_AR=ar
LOCAL_EXECUTABLE=$(APPLICATION)_test

# target platform
TARGET_TAG=TARGET
TARGET_ARCH=arm
TARGET_OS=linux
TARGET_CC=arm-linux-gnueabihf-gcc
TARGET_CXX=arm-linux-gnueabihf-g++
TARGET_AR=arm-linux-gnueabihf-ar
TARGET_EXECUTABLE=$(APPLICATION)

ifneq (PLATFORM, TARGET_TAG)
override PLATFORM=LOCAL
endif

export ARCH=$($(PLATFORM)_ARCH)
export OS=$($(PLATFORM)_OS)
export CC=$($(PLATFORM)_CC)
export CXX=$($(PLATFORM)_CXX)
export AR=$($(PLATFORM)_AR)
export EXECUTABLE=$($(PLATFORM)_EXECUTABLE)

all: build

run:
ifneq ($(PLATFORM), LOCAL)
	$(MAKE) run PLATFORM=LOCAL
else
	$(MAKE) build PLATFORM=$(PLATFORM)
	cd $(DIR_BUILD) && ./$(EXECUTABLE)
endif

build: build_interface build_server build_db

build_interface: $(DIR_BUILD)/$(WEBROOT)

$(DIR_BUILD)/$(WEBROOT): $(INTERFACE_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_INTERFACE) && $(MAKE) TARGET=$(DIR_BUILD)/$(WEBROOT)

build_server: $(DIR_BUILD)/$(EXECUTABLE)

$(DIR_BUILD)/$(EXECUTABLE): $(SERVER_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_SERVER) && $(MAKE) TARGET=$(DIR_BUILD)/$(EXECUTABLE)

build_db: $(DIR_BUILD)/$(DB)

$(DIR_BUILD)/$(DB):
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_DATABASE) && $(MAKE) TARGET=$(DIR_BUILD)/$(DB)

clean:
	rm -rf $(DIR_BUILD)
	cd $(DIR_INTERFACE) && $(MAKE) clean
	cd $(DIR_DATABASE) && $(MAKE) clean

.PHONY: clean run build db
