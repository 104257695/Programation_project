CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

GINAC_FLAGS = `pkg-config --cflags --libs ginac`

SRC = main.cpp functions.cpp utils.cpp

TARGET = exam

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GINAC_FLAGS)

clean:
	rm -f $(TARGET)
