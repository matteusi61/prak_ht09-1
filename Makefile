CC = gcc

LD = gcc

CFLAGS = -O2 -std=gnu2x -Wall -Werror -Wno-pointer-sign -Werror=vla

LDFLAGS = -lm

.PHONY: all, clean

all: random.o linear.o main.o
	$(LD) $(LDFLAGS) -rdynamic -fPIC $^ -o printrandom

random.o: random.c
	$(CC) $(CFLAGS) -fPIC -DPIC -c $< -o $@

linear.o: linear.c
	$(CC) $(CFLAGS) -fPIC -DPIC -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -fPIC -DPIC -c $< -o $@

clean:
	rm -rf *.o printrandom