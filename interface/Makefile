INTERFACE_FILES=$(shell find src) $(shell find public)
INTERFACE_BUILD=build

all: build

build: $(TARGET)

$(TARGET): $(INTERFACE_FILES)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	npm run build
	cp -r $(INTERFACE_BUILD) $(TARGET)

clean:
	rm -rf $(INTERFACE_BUILD)

.PHONY: build clean
