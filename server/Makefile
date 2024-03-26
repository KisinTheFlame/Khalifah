SERVER_FILES=$(shell find .)

all: build

build: $(TARGET)

$(TARGET): $(SERVER_FILES)
	GOARCH=$(ARCH) \
	GOARM=7 \
	GOOS=$(OS) \
	CGO_ENABLED=1 \
	CC=$(CC) \
	CXX=$(CXX) \
	AR=$(AR) \
	go build -o $(TARGET)

clean:
	rm -rf $(INTERFACE_BUILD)

.PHONY: build clean
