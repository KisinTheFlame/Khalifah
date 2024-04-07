DIR_INC=$(PWD)/include
DIR_SRC=$(PWD)/src
DIR_BUILD=$(PWD)/build
DIR_TEST=$(PWD)/test
DIR_APP=$(PWD)/application
DIR_DRIVER=$(PWD)/driver

INC=$(shell find $(DIR_INC) -name "*.h")
SRC=$(shell find $(DIR_SRC) -name "*.c")
OBJ=$(patsubst %.c, %.o, $(SRC))
TEST=$(shell find $(DIR_TEST) -name "*.c")
TEST_OBJ=$(patsubst %.c, %.o, $(TEST))

APP_TARGET=main

CFLAGS= -Wall -std=c11 -c -g -I$(DIR_INC) -I$(DIR_DRIVER)/shared -I$(DIR_DRIVER)/libex1629
LDFLAGS= -lm -L$(DIR_DRIVER)/libex1629 -lex1629 -lpthread

all: $(TARGET)

$(TARGET): $(DIR_APP)/$(APP_TARGET).o $(OBJ)
	$(CC) $(DIR_APP)/$(APP_TARGET).o $(OBJ) -o $@ $(LDFLAGS)

.PHONY: test
test: $(if $(case), $(DIR_TEST)/test-$(case).o, $(TEST_OBJ)) $(OBJ)
	@if [ ! -d $(DIR_BUILD) ]; then mkdir $(DIR_BUILD); fi
ifeq ($(origin case), undefined)
	@for test_object in $(TEST_OBJ); do \
		target=$$(echo $$test_object | sed "s/\.o$$//g" | sed "s/.*\///g"); \
		echo testing $$target \
		&& $(CC) $$test_object $(OBJ) -o $(DIR_BUILD)/$$target \
		&& $(DIR_BUILD)/$$target \
		&& echo $$target passed \
		|| echo $$target failed $$?; \
	done
	@echo all tests passed
else
	@$(CC) $(DIR_TEST)/test-$(case).o $(OBJ) -o $(DIR_BUILD)/test-$(case) \
	&& $(DIR_BUILD)/test-$(case) \
	&& echo test $(case) passed \
	|| echo test $(case) faild $$?
endif

%.o: %.c $(INC) $(LIBPATH)/lib$(LIBNAME).a
	$(CC) $(LDFLAGS) $(CFLAGS) $< -o $@

$(LIBPATH)/lib$(LIBNAME).a:
	cd $(DIR_DRIVER) && $(MAKE)

.PHONY: clean
clean:
	rm -rf $(DIR_BUILD)
	find $(DIR_SRC) -name "*.o" | xargs rm -f
	find $(DIR_APP) -name "*.o" | xargs rm -f
	find $(DIR_TEST) -name "*.o" | xargs rm -f
	cd $(DIR_DRIVER) && $(MAKE) clean
