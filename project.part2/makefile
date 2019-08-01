CXX := g++
CXXFLAG := -Wall -Wextra -Wconversion -std=c++11 -pedantic -O3


TARGET := main
OBJS := COO2CSR.o CGSolver.o sparse.o heat.o main.o
INCS := sparse.hpp COO2CSR.hpp heat.hpp CGSolver.hpp

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(CXXFLAG)

# this is a make pattern rule
%.o: %.cpp $(INCS)
	$(CXX) -c -o $@ $< $(CXXFLAG)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
