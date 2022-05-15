TARGET=debug003
SRCS=main.c
OBJS=$(SRCS:.c=.o)
CC=gcc
CCFLAGS=-g -O0 -std=c17
LDFLAGS=-lpthread


$(TARGET):$(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $^ -o $@

run: $(TARGET)
	chmod +x $(TARGET)
	$(PWD)/$(TARGET)

debug: $(TARGET)
	chmod +x $(TARGET)
	gdb $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)
