TARGET = serialize
SRCS = *.cpp
HPP = *.h
CFLAGS = -std=c++11
FILE = data error.txt
$(TARGET):$(SRCS) $(HPP) 
	g++ $(SRCS) -o $(TARGET) $(CFLAGS)
clean:
	rm -rf $(FILE) $(TARGET)
all:clean $(TARGET)
