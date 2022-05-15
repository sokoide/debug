TARGET=debug001
SRCS=main.c
OBJS=$(SRCS:.c=.o)
CC=gcc
CCFLAGS=-g -O0 -m32
LDFLAGS=


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
