DIR_SRC=sqlite3_src
SRC=$(shell find $(DIR_SRC) -name "*.c")

ifeq ($(origin CC), default)
CC=gcc
CXX=g++
endif

SQLITE3=./sqlite3
CFLAGS=-lpthread -ldl -lm

SQL_FILE=init.sql

all: build

build: $(TARGET)

$(TARGET): $(SQLITE3) init.sql
	$(SQLITE3) $(TARGET) < $(SQL_FILE)

$(SQLITE3): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(SQLITE3)

clean:
	rm -f sqlite3

.PHONY: build clean
