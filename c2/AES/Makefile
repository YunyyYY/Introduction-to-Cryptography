CP = gcc
LDFLAGS = -O3 -Wall

c2: main.c aes.c
	$(CP) $(LDFLAGS) -o c2 main.c  aes.c

test:
	./c2

# clean
clean:
	rm -f c2

