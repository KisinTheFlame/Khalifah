APPLICATION=khalifah

DIR_INTERFACE=interface
DIR_SERVER=server
DIR_LIBRARY=library
DIR_BUILD=build

INTERFACE_FILES=$(shell find $(DIR_INTERFACE)/src) $(shell find $(DIR_INTERFACE)/public)
INTERFACE_BUILD=build
SERVER_FILES=$(shell find $(DIR_SERVER))

TEST=$(APPLICATION)_test
TARGET=$(APPLICATION)
STATIC=static

all: build

run:
	$(MAKE) FOR=test
	cd $(DIR_BUILD) && ./$(TEST)

build:
ifeq ($(FOR), target)
	$(MAKE) $(DIR_BUILD)/$(TARGET)
else ifeq ($(FOR), test)
	$(MAKE) $(DIR_BUILD)/$(TEST)
else
	@echo Build for whom? \(FOR=target/test\)
	@exit 1
endif
	$(MAKE) $(DIR_BUILD)/$(STATIC)

$(DIR_BUILD)/$(STATIC): $(INTERFACE_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	cd $(DIR_INTERFACE) && npm run build
	mv $(DIR_INTERFACE)/build $(DIR_BUILD)/$(STATIC)

$(DIR_BUILD)/$(TEST): $(SERVER_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	go build -C $(DIR_SERVER) -o $$PWD/$(DIR_BUILD)/$(TEST)

$(DIR_BUILD)/$(TARGET): $(SERVER_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	GOARCH=arm \
	GOARM=7 \
	GOOS=linux \
	CGO_ENABLED=1 \
	CC=arm-linux-gnueabihf-gcc \
	CXX=arm-linux-gnueabihf-g++ \
	AR=arm-linux-gnueabihf-ar \
	go build -C $(DIR_SERVER) -o $$PWD/$(DIR_BUILD)/$(TARGET)

clean:
	rm -rf $(DIR_BUILD)

.PHONY: clean run build
