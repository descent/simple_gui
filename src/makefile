CXX=/gcc-3.2-i686/bin/g++
CXX=g++
#CXXFLAGS=-g -DDEBUG
CXXFLAGS=-g 
LIBS=

DEP_H=desktop.h geometry.h view.h lview.h shadow_view.h box.h port.h model.h event.h controller.h controller_item.h keyboard.h timer.h
DEP_OBJS=desktop.o geometry.o view.o lview.o color_pair.o shadow_view.o box.o port.o model.o event.o controller.o controller_item.o keyboard.o timer.o

test2:test2.o ${DEP_OBJS}
	$(CXX) ${CXXFLAGS} -o $@ $@.o ${DEP_OBJS} -lcurses
test2.o:test2.cpp ${DEP_H}
	$(CXX) ${CXXFLAGS} -c $*.cpp

test1:test1.o ${DEP_OBJS}
	$(CXX) ${CXXFLAGS} -o $@ $@.o ${DEP_OBJS} -lcurses
test1.o:test1.cpp ${DEP_H}
	$(CXX) ${CXXFLAGS} -c $*.cpp
model.o:model.h model.cpp view.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
controller.o:controller.h controller.cpp
	$(CXX) ${CXXFLAGS} -c $*.cpp
controller_item.o:controller_item.h controller_item.cpp
	$(CXX) ${CXXFLAGS} -c $*.cpp
keyboard.o:keyboard.cpp keyboard.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
event.o:event.cpp event.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
timer.o:timer.cpp timer.h
	$(CXX) ${CXXFLAGS} -c $*.cpp

use_shadow:use_shadow.o ${DEP_OBJS}
	$(CXX) ${CXXFLAGS} -o $@ $@.o ${DEP_OBJS} -lcurses
use_shadow.o:use_shadow.cpp ${DEP_H}
	$(CXX) ${CXXFLAGS} -c $*.cpp

desktop.o:desktop.cpp desktop.h geometry.h view.h
	$(CXX) ${CXXFLAGS} -c $*.cpp

port.o:port.cpp port.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
geometry.o:geometry.cpp geometry.h
	$(CXX) ${CXXFLAGS} -c $*.cpp

view.o:view.cpp view.h color_pair.h port.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
lview.o:lview.cpp lview.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
shadow_view.o:shadow_view.cpp shadow_view.h lview.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
box.o:box.cpp box.h shadow_view.h lview.h
	$(CXX) ${CXXFLAGS} -c $*.cpp
color_pair.o:color_pair.cpp color_pair.h
	$(CXX) ${CXXFLAGS} -c $*.cpp


clean:
	rm -f *.o
