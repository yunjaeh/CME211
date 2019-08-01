CXX := g++
CXXFLAG := -Wall -Wextra -Wconversion -std=c++11 -pedantic -ljpeg 


TARGET := main
OBJS := hw6.o image.o main.o
INCS := hw6.hpp image.hpp


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAG)

# this is a make pattern rule
%.o: %.cpp $(INCS)
	$(CXX) -c -o $@ $< $(CXXFLAG)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
