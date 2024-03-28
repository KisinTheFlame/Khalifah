APPLICATION=khalifah

DIR_INTERFACE=$(PWD)/interface
DIR_SERVER=$(PWD)/server
DIR_LIBRARY=$(PWD)/library
DIR_DATABASE=$(PWD)/database
DIR_PUBLISHER=$(PWD)/publisher
DIR_BUILD=$(PWD)/build

SERVER_FILES=$(shell find $(DIR_SERVER))

WEBROOT=webroot
DB=data.db
PUBLISHER=publisher

# local platform
export LOCAL_TAG=LOCAL
export LOCAL_ARCH=amd64
export LOCAL_OS=linux
export LOCAL_CC=gcc
export LOCAL_CXX=g++
export LOCAL_AR=ar
export LOCAL_EXECUTABLE=$(APPLICATION)_test

# arm platform
export ARM_TAG=ARM
export ARM_ARCH=arm
export ARM_OS=linux
export ARM_CC=arm-linux-gnueabihf-gcc
export ARM_CXX=arm-linux-gnueabihf-g++
export ARM_AR=arm-linux-gnueabihf-ar
export ARM_EXECUTABLE=$(APPLICATION)

ifneq ($(PLATFORM), $(ARM_TAG))
override PLATFORM=$(LOCAL_TAG)
endif

export ARCH=$($(PLATFORM)_ARCH)
export OS=$($(PLATFORM)_OS)
export CC=$($(PLATFORM)_CC)
export CXX=$($(PLATFORM)_CXX)
export AR=$($(PLATFORM)_AR)
export EXECUTABLE=$($(PLATFORM)_EXECUTABLE)

all: build

.PHONY: run
run:
ifneq ($(PLATFORM), $(LOCAL_TAG))
	$(MAKE) run PLATFORM=$(LOCAL_TAG)
else
	$(MAKE) build PLATFORM=$(PLATFORM)
	cd $(DIR_BUILD) && ./$(EXECUTABLE)
endif

.PHONY: build
build: build_interface build_server build_db build_publisher

.PHONY: build_interface
build_interface: $(DIR_BUILD)/$(WEBROOT)

$(DIR_BUILD)/$(WEBROOT): $(INTERFACE_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_INTERFACE) && $(MAKE) TARGET=$@

.PHONY: build_server
build_server: $(DIR_BUILD)/$(EXECUTABLE)

$(DIR_BUILD)/$(EXECUTABLE): $(SERVER_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_SERVER) && $(MAKE) TARGET=$@

.PHONY: build_db
build_db: $(DIR_BUILD)/$(DB)

$(DIR_BUILD)/$(DB):
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_DATABASE) && $(MAKE) TARGET=$@

.PHONY: build_publisher
build_publisher: $(DIR_BUILD)/$(PUBLISHER)

$(DIR_BUILD)/$(PUBLISHER):
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_PUBLISHER) && $(MAKE) TARGET=$@

.PHONY: clean
clean:
	rm -rf $(DIR_BUILD)
	cd $(DIR_INTERFACE) && $(MAKE) clean
	cd $(DIR_DATABASE) && $(MAKE) clean
	cd $(DIR_PUBLISHER) && $(MAKE) clean
