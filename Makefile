CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET := vigenere
SRCS := main.cpp vigenere.cpp

$(TARGET): $(SRCS) vigenere.h
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

clean:
	rm -f $(TARGET)

.PHONY: clean
