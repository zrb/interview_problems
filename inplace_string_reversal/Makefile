src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = inplace_string_reversal

CC = clang++-11
CXX = clang++-11
CXXFLAGS = --std=c++2a -I../ext/catch2/include -g -stdlib=libc++
LDFLAGS = -lc++abi -lc++

$(exe): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY = clean
clean:
	rm -f $(obj) $(exe)

