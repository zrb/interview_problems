src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
exe = singly_linked_list_find_merge_point

CC = clang++-15
CXX = clang++-15
CXXFLAGS = --std=c++2a -I../ext/catch2/include -g -stdlib=libc++
LDFLAGS = -lc++abi -lc++ -fmodules-ts

$(exe): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY = default
default: $(exe)

.PHONY = clean
clean:
	rm -f $(obj) $(exe)

