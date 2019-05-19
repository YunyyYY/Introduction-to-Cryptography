#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
//#include <gmp-impl.h>

#define SIZE 4096
#define REPEAT 10

void update(mpz_t a, mpz_t b, mpz_t q) {
	// update a, b
	mpz_t tmp;
	mpz_init2(tmp, SIZE);
	mpz_set(tmp, b);
	mpz_mul(b, q, b); // b = q * b
	mpz_sub (b, a, b); // update b = a - 1 * b
	mpz_set(a, tmp); // update a = (previous)b
}

void gcd(mpz_t r, mpz_t s, mpz_t t, mpz_t a, mpz_t b) {
	mpz_t r0, r1, s0, s1, t0, t1, q;
	mpz_init2(r0, SIZE);
	mpz_init2(r1, SIZE);
	mpz_init2(s0, SIZE);
	mpz_init2(s1, SIZE);
	mpz_init2(t0, SIZE);
	mpz_init2(t1, SIZE);
	mpz_init2(q, SIZE);

	mpz_set(r0, b);
	mpz_set(r1, a);
	mpz_set_ui(s1, 1);
	mpz_set_ui(t0, 1);

	while (mpz_cmp_ui(r0, 0) != 0) {
		mpz_fdiv_q(q, r1, r0);  // acquire q value
		update(r1, r0, q);
		update(s1, s0, q);
		update(t1, t0, q);
	}
	mpz_set(r, r1);
	mpz_set(s, s1);
	mpz_set(t, t1);
}

int main() {
	mpz_t a, b, r, s, t;
	mpz_init2(a, SIZE);
	mpz_init2(b, SIZE);
	mpz_init2(r, SIZE);
	mpz_init2(s, SIZE);
	mpz_init2(t, SIZE);

	gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(0)); // create two different a, b every time
	int repeat = rand() % REPEAT + 1;
	for (int i = 0; i < repeat; i++) {
		mpz_urandomb(a, state, SIZE);
		mpz_urandomb(b, state, SIZE);
	}

	// acquired a and b
	printf("a = ");
	mpz_out_str(stdout, 10, a);
	printf("\nb = ");
	mpz_out_str(stdout, 10, b);

	printf("\nUsing Extended Euclidean Algorithm, gcd(a, b) = ");
	gcd(r, s, t, a, b);
	mpz_out_str(stdout, 10, r);

	printf("\nUsing corresponding GMP function, gcd(a, b) = ");
	mpz_gcdext(r, s, t, a, b);
	mpz_out_str(stdout, 10, r);
	printf("\n");
	return 0;
}