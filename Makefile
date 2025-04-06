CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -pthread

SRCS = src/main.cpp src/ThreadPool.cpp src/Server.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
