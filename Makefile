

TARGET = ./unit_test
SRCS = \
    test/fstring_test.cpp

CATCH = Catch/include/catch.hpp
DIR = $(shell pwd)

$(CATCH):
	git clone https://github.com/philsquared/Catch.git

$(TARGET):
	g++ -g -o $(TARGET) -I $(DIR) -std=c++11 $(SRCS) ; $(TARGET)

.PHONY: test

clean:
	rm $(TARGET) || true;

test: clean $(CATCH) $(TARGET)

all: test
	@echo "success"
