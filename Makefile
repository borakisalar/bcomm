CXX = g++
CXXFLAGS = -O3 -Wall -Wextra
CC = gcc
CFLAGS = -O3 -Wall -Wextra

TARGET = bcomm
SRCS = bcomm.cpp BloomFilter.cpp murmur3.c
OBJS = bcomm.o BloomFilter.o murmur3.o
PREFIX = /usr/local/bin

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

bcomm.o: bcomm.cpp BloomFilter.h
	$(CXX) $(CXXFLAGS) -c bcomm.cpp

BloomFilter.o: BloomFilter.cpp BloomFilter.h murmur3.h
	$(CXX) $(CXXFLAGS) -c BloomFilter.cpp

murmur3.o: murmur3.c murmur3.h
	$(CC) $(CFLAGS) -c murmur3.c

install: $(TARGET)
	sudo cp $(TARGET) $(PREFIX)/$(TARGET)
	@echo "Installed $(TARGET) to $(PREFIX)"

uninstall:
	sudo rm -f $(PREFIX)/$(TARGET)
	@echo "Uninstalled $(TARGET) from $(PREFIX)"

clean:
	rm -f $(TARGET) $(OBJS)
	@echo "Cleaned up build artifacts"