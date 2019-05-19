# README

`gmp.c` implements the extended Euclidean algorithm and compare its result with the gcd function `mpz_gcdext` provided by GMP library.

The program generates two random numbers every time, and computes their gcd with two methods and compares the results. Since the random state algorithm initialize `state` with the same value each time, `time()` is introduced to enable randomness of the two large numbers.

Using `make` for compilation and `make test` to run the program.