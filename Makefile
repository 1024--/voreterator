CPPFLAGS = -O3 -Wall -Wpedantic

all:
	$(CXX) example.cc $(CPPFLAGS) -o example

clean:
	$(RM) example