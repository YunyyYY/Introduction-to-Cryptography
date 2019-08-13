#include "cheat.h"

void set_key(int* P) {	// P is a random 7x7 permutation matrix
	// for (int i = 0; i < 49; i++) {
	// 	if (i%7==0)
	// 		printf("\n");
	// 	printf("%d ",P [i]);
	// }
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 7; c++) {
			hat_G[r*7 + c] = 0;
			for (int x = 0; x < 7; x++) {
				hat_G[r*7 + c] += SG[r*7 + x]*P[x*7+c];
			}
			hat_G[r*7 + c] = (hat_G[r*7 + c]&1)^0; // printf("r %d, c %d, %d\n", r, c, hat_G[r*7 + c]);
		}
	}
	// for (int i = 0; i < 28; i++) {
	// 	if (i%7==0)
	// 		printf("\n");
	// 	printf("%d ",hat_G[i]);
	// }
}

void en_crypt(int letter) { 	// printf("letter is %d\n", letter);
	int map[8];
	for (int i = 0; i < 8; i++) {
		map[i] = letter % 2;    // printf("%d ", map[i]);
		letter >>= 1;
	}

	srand((unsigned int) time(0) + getpid());
	srand(rand());
    int hi=0, lo=0, s1, s2 = rand() % 7;
	int error[7] = {0,0,0,0,0,0,0};
	// error[s2] = 1; // printf("rand %d\n", s2);

	for (int i = 0; i < 7; i++) {
		s1 = s2 = 0;
		for (int bit = 0; bit < 4; bit++) {
			s1 += hat_G[i+bit*7] * map[bit];
			s2 += hat_G[i+bit*7] * map[bit+4];
			// printf("%d ", hat_G[i+bit*7] * map[bit+4]);
		} // printf("%d ", s2);
		lo = (lo << 1) + ((s1&1)^error[i]);
		hi = (hi << 1) + ((s2&1)^error[i]);
	}
	printf("%02x%02x", lo, hi);
}

void gen_key() {
	srand((unsigned int) time(0) + getpid());
	srand(rand());

	int swap, tmp = 0, per[] = {0,1,2,3,4,5,6};
	for (int i = 0; i < 7; i++) {
		swap = rand() % 7;
		tmp = per[0];
		per[0] = per[swap];
		per[swap] = tmp;
	}
	for (int i = 0; i < 7; i++)
		printf("%c", per[i]+97);
}

void de_crypt(int* word) {					// word should gave size 14.
	int org[8], map[8], s1, s2, hi=0, lo=0;	// 2x7 -> 2x4 -> word
	for (int row = 0; row < 3; row++) {		// parity check
		s1 = s2 = 0;
		for (int c = 0; c < 7; c++) {
			s1 += H[row * 7 + c] * word[c];
			s2 += H[row * 7 + c] * word[7 + c];
		}
		lo = (lo << 1) + (s1&1);
		hi = (hi << 1) + (s2&1);
	}
	for (int i = 0; i < 7; i++) {			// parity correction
		word[i] = (word[i]&1)^(lo == parity_check[i]);
		word[i+7] = (word[i+7]&1)^(hi == parity_check[i]);
	}

	for (int r = 0; r < 4; r++) {			// decode
		s1 = s2 = 0;
		for (int c = 0; c < 7; c++) {
			s1 += R[r * 7 + c] * word[c];
			s2 += R[r * 7 + c] * word[7 + c];
		}
		map[r] = (s1&1);
		map[r+4] = (s2&1);
	}

	for (int i = 0; i < 4; i++) {			// m = \hat{M} x inv{S}
		s1 = s2 = 0;
		for (int c = 0; c < 4; c++) {
			s1 += invS[i + c * 4] * map[c];
			s2 += invS[i + c * 4] * map[4 + c];
		}
		org[i] = (s1&1);
		org[i+4] = (s2&1);
	}
	// for (int k = 0; k < 8; k++)
	// 	printf("%d \n", org[k]);
	int letter = 0;
	for (int i = 6; i > -1; i--) 
		letter = (letter << 1) | org[i];
	
	printf("%c", letter);
}



