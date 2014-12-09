CFLAGS=-g
MYCFLAGS=
MYCXXFLAGS =
LD_FLAGS=
CXX=g++

# make CH=1 will use ccache
ifdef CH
CXX=ccache g++
endif

%.dpp: %.cpp
	set -e; rm -f $@ ; $(CXX) -MM $(MYCFLAGS) $< > $@.$$$$ ; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; rm -f $@.$$$$

