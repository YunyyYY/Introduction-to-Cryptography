CP = gcc
LDFLAGS = -O3 -Wall \
        -lglib-2.0   \
        -Wl,-rpath /usr/local/lib -lgmp \
        -lcrypto -lcrypto \
        -lgmp

gmp: gmp.c
	$(CP) $(LDFLAGS) -o gmp gmp.c

test:
	./gmp

# clean
clean:
	rm -f gmp