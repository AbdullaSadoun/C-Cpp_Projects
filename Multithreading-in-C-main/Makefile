CC=gcc
CFLAGS=-Wall
TARGET=main

# Target to build your program
$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

# Target to clean the build
.PHONY: clean
clean:
	rm -f $(TARGET)

# Target to run your program
.PHONY: run
run: $(TARGET)
	./$(TARGET) IntegerList.txt
