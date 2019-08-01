CXX := g++
CXXFLAG := -Wall -Wextra -Wconversion -std=c++11


TARGET := main
OBJS := main.o Inventory.o CashRegister.cpp
INCS := Inventory.hpp CashRegister.hpp

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAG)

# this is a make pattern rule
%.o: %.cpp $(INCS)
	$(CXX) -c -o $@ $< $(CXXFLAG)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
