src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = inplace_string_reversal

CC = clang++-15
CXX = clang++-15
CXXFLAGS = --std=c++20 -I../ext/catch2/include -g -stdlib=libc++
LDFLAGS = -lc++abi -lc++

$(exe): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY = clean
clean:
	rm -f $(obj) $(exe)

