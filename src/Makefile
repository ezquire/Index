CXX=g++
CXXFLAGS= -g -std=c++11 -Wall -Werror -pedantic
DEPS = bst.h ttt.h main.cpp bst.cpp ttt.cpp

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

index: $(DEPS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm index *~

.PHONY: all clean
