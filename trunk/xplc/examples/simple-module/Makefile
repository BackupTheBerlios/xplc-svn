
.PHONY: default clean

# the UNSTABLE flag is there because we agree to use interfaces that
# have not been frozen yet.
CPPFLAGS+=-DUNSTABLE -I../../include
LDFLAGS+=-L../..

default: example.so

clean:
	rm -f example.so *~ *.o

%.so:
	$(LINK.cc) -shared $^ -lxplc-cxx -o $@

example.so: $(patsubst %.cpp,%.o,$(wildcard *.cpp))

