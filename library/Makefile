DIR_INC=include
DIR_SRC=src
DIR_BUILD=build
DIR_TEST=test

INC=$(shell find $(DIR_INC) -name "*.h")
SRC=$(shell find $(DIR_SRC) -name "*.c")
OBJ=$(patsubst %.c, %.o, $(SRC))
TEST=$(shell find $(DIR_TEST) -name "*.c")
TEST_OBJ=$(patsubst %.c, %.o, $(TEST))

TARGET=lib.a
BUILD_TARGET=$(DIR_BUILD)/$(TARGET)

CC=gcc
CFLAGS=-Wall -I$(DIR_INC) -std=c99 -c -g

AR=ar
ARFLAGS=-rcs

all: $(BUILD_TARGET)

$(BUILD_TARGET): $(OBJ)
	if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
	$(AR) $(ARFLAGS) $(BUILD_TARGET) $(OBJ)

test: $(if $(case), $(DIR_TEST)/test-$(case).o, $(TEST_OBJ)) $(BUILD_TARGET)
	@if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
ifeq ($(origin case), undefined)
	@for test_object in $(TEST_OBJ); do \
		target=$$(echo $$test_object | sed "s/\.o$$//g" | sed "s/.*\///g"); \
		echo testing $$target \
		&& $(CC) -o $(DIR_BUILD)/$$target $$test_object -L$(DIR_BUILD) -l:$(TARGET) \
		&& $(DIR_BUILD)/$$target \
		&& echo $$target passed \
		|| echo $$target failed $$?; \
	done
	@echo all tests passed
else
	@$(CC) -o $(DIR_BUILD)/test-$(case) $(DIR_TEST)/test-$(case).o -L$(DIR_BUILD) -l:$(TARGET) \
	&& $(DIR_BUILD)/test-$(case) \
	&& echo test $(case) passed \
	|| echo test $(case) faild $$?
endif

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(DIR_BUILD)
	find . -name "*.o" | xargs rm -f

.PHONY: clean test
