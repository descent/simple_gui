CFLAGS=-g
MYCFLAGS=
MYCXXFLAGS =
LD_FLAGS=
CXX=g++
%.dpp: %.cpp
	set -e; rm -f $@ ; $(CXX) -MM $(MYCFLAGS) $< > $@.$$$$ ; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; rm -f $@.$$$$

