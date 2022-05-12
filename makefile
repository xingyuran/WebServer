CXX ?= g++
DEBUG ?=1
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g
else
	CXXFLAGS += -02
endif

server: Main.cpp Server.cpp
	$(CXX) -o server $^ $(CXXFLAGS)

clean:
	rm -f server
