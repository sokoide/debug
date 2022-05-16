TARGET=debug006
SRCS=main.c
OBJS=$(SRCS:.c=.o)
CC=gcc
CCFLAGS=-g -O0 -std=c17
LDFLAGS=-lpthread


$(TARGET):$(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)
	chmod +x $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $^ -o $@

run: $(TARGET)
	$(PWD)/$(TARGET)

debug: $(TARGET)
	gdb $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)
