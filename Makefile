CXXFLAGS = -g -Wall -Werror -pedantic -std=c++11

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)

all : index

index : $(obj)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean :
	rm index *~ *.o
