CXXFLAGS := -g -Wall -std=c++11 -lm
CXX=g++
SRC=main.cpp dataloader.cpp knn.cpp radiomap.cpp

all: build

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o positioning

clean:
	rm -f positioning *.o