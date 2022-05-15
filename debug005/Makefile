TARGET=debug005
SRCS=main.c
OBJS=$(SRCS:.c=.o)
CC=gcc
#CCFLAGS=-g -O0 -std=c17
CCFLAGS= -O0 -std=c17
LDFLAGS=-lpthread


$(TARGET):$(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)
	chmod +x $(TARGET)

%.o: %.c
	$(CC) $(CCFLAGS) -c $^ -o $@

clean:
	rm -rf $(TARGET) $(OBJS)
