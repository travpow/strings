

TARGET = ./unit_test
SRCS = \
    test/test_main.cpp \
    test/fstring_test.cpp \
    test/sstring_test.cpp \

CATCH = Catch/include/catch.hpp
DIR = $(shell pwd)
BIN = bin/

$(CATCH):
	git clone https://github.com/philsquared/Catch.git

$(BIN):
	@mkdir $(BIN)

$(TARGET): $(BIN)
	@g++ -g -o $(BIN)/$(TARGET) -I $(DIR) -std=c++11 $(SRCS) ; $(BIN)/$(TARGET)

.PHONY: test

clean:
	@rm -r $(DIR)/$(BIN) || true ;

test: clean $(CATCH) $(TARGET)

all: test
	@echo "success"
