CFLAGS=-g
MYCFLAGS=
MYCXXFLAGS = -std=c++11 
LD_FLAGS=
CXX=g++
#CXX=clang++-3.8

# make CH=1 will use ccache
ifdef CH
CXX=ccache g++
endif

%.dpp: %.cpp
	set -e; rm -f $@ ; $(CXX) -MM $(MYCFLAGS) $< > $@.$$$$ ; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; rm -f $@.$$$$

