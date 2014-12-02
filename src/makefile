include rule.mk


CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS)

test2: box.o desktop.o   lview.o view.o color_pair.o event.o model.o test2.o controller.o geometry.o  port.o timer.o controller_item.o  keyboard.o  shadow_view.o  
	$(CXX) -o $@ $^ -lcurses



sources = box.cpp              desktop.cpp   lview.cpp        test1.cpp       view.cpp color_pair.cpp       event.cpp     model.cpp        test2.cpp controller.cpp       geometry.cpp  port.cpp         timer.cpp controller_item.cpp  keyboard.cpp  shadow_view.cpp  use_shadow.cpp


include $(sources:.cpp=.dpp)
	
clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean: clean
	find . -type l -exec rm -f {} \;
