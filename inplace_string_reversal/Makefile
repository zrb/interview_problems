src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = inplace_string_reversal

CC = g++
CXXFLAGS = --std=c++2a -I../ext/catch2/include -g

$(exe): $(obj)
	$(CC) -o $@ $^

.PHONY = clean
clean:
	rm -f $(obj) $(exe)

