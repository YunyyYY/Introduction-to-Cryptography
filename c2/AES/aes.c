#include "aes.h"

// display result
void print_key(unsigned char *a) {
	printf("-----------\n");
	for (unsigned char *s = a; s < a + KSIZE; s+=4)
		printf("%02x %02x %02x %02x\n", *s, *(s+1), *(s+2), *(s+3));
	//	printf("%3d %3d %3d %3d\n", *s, *(s+1), *(s+2), *(s+3));
	printf("-----------\n");
}

void subBytes(unsigned char *a) {
	for (unsigned char *s = a; s < a + KSIZE; s++)
		*s = SUB(*s);
}

void invSubBytes(unsigned char *a) {
	for (unsigned char *s = a; s < a + KSIZE; s++)
		*s = INV_SBOX[*s];
}

// shift helper function
void leftShift(unsigned char* a, int shift) {
	unsigned x = a[shift] | a[(shift+1)%4]<<8u | a[(shift+2)%4]<<16u | a[(shift+3)%4]<<24u;
	a[0] = x & 0xffu;
	a[1] = x>>8u & 0xffu;
	a[2] = x>>16u & 0xffu;
	a[3] = x>>24u & 0xffu;
}

void shiftRows(unsigned char *a) {
	leftShift(a+4, 1);
	leftShift(a+8, 2);
	leftShift(a+12, 3);
}

void invShiftRows(unsigned char *a) {
	leftShift(a+4, 3);
	leftShift(a+8, 2);
	leftShift(a+12, 1);
}

void mixColumns(unsigned char *a) {
	unsigned char *copy = (unsigned char *)malloc(sizeof(unsigned char) * KSIZE);
	memcpy(copy, a, KSIZE);
	for(int c = 0; c < 4; c++) {
		a[c] = (MUL2(copy[c]))^(MUL3(copy[c+4]))^copy[c+8]^copy[c+12];
		a[c+4] = copy[c]^(MUL2(copy[c+4]))^MUL3(copy[c+8])^copy[c+12];
		a[c+8] = copy[c]^copy[c+4]^(MUL2(copy[c+8]))^(MUL3(copy[c+12]));
		a[c+12]= (MUL3(copy[c]))^copy[c+4]^copy[c+8]^(MUL2(copy[c+12]));
	}
	free(copy);
}

void invMixColumns(unsigned char *a) {
	unsigned char *copy = (unsigned char *)malloc(sizeof(unsigned char) * KSIZE);
	memcpy(copy, a, KSIZE);
	for(int c = 0; c < 4; c++) {
		a[c] = (MULe(copy[c]))^(MULb(copy[c+4]))^(MULd(copy[c+8]))^(MUL9(copy[c+12]));
		a[c+4] = (MUL9(copy[c]))^(MULe(copy[c+4]))^(MULb(copy[c+8]))^(MULd(copy[c+12]));
		a[c+8] = (MULd(copy[c]))^(MUL9(copy[c+4]))^(MULe(copy[c+8]))^(MULb(copy[c+12]));
		a[c+12]= (MULb(copy[c]))^(MULd(copy[c+4]))^(MUL9(copy[c+8]))^(MULe(copy[c+12]));
	}
	free(copy);
}

// generate round key helper function
void T(unsigned char* tmp, int i) {
	leftShift(tmp, 1);
	*tmp = SUB(*tmp);
	*(tmp+1) = SUB(*(tmp+1));
	*(tmp+2) = SUB(*(tmp+2));
	*(tmp+3) = SUB(*(tmp+3));
	*tmp = (*tmp)^r[i/4-1];
}

void genRoundKey(round_key *K, const unsigned char* a) {
	for (int i = 0; i < 4; i++)	{			// initialize
		for (int j = 0; j < 4; j++)
			K[i].c[j] = a(j, i);
	}

	unsigned char tmp[4];
	for (int i = 4; i < KROUND; i++) {
		if (i%4!=0) {
			for (int j = 0; j < 4; j++)
				K[i].c[j] = K[i-4].c[j]^K[i-1].c[j];
		} else {
			memcpy(tmp, K[i-1].c, 4);
			T(tmp, i);
			for (int j = 0; j < 4; j++)
				K[i].c[j] = K[i-4].c[j]^tmp[j];
		}
	}
}

// must initialize round keys first
void addRoundKey(round_key *K, unsigned char *a, int round) {
	for (int i = 0; i < 4; i++) {
		a(0, i) = a(0, i)^K[4*round+i].c[0];
		a(1, i) = a(1, i)^K[4*round+i].c[1];
		a(2, i) = a(2, i)^K[4*round+i].c[2];
		a(3, i) = a(3, i)^K[4*round+i].c[3];
	}
}

void invAddRoundKey(round_key *K, unsigned char *a, int round) {
	unsigned char *copy = (unsigned char *)malloc(sizeof(unsigned char) * KSIZE);
	memcpy(copy, &K[4*round], KSIZE);
	for(int c = 0; c < 4; c++) {
		a[c] = a[c]^(MULe(K[4*round+c].c[0]))^(MULb(K[4*round+c].c[1]))^(MULd(K[4*round+c].c[2]))^(MUL9(K[4*round+c].c[3]));
		a[c+4] = a[c+4]^(MUL9(K[4*round+c].c[0]))^(MULe(K[4*round+c].c[1]))^(MULb(K[4*round+c].c[2]))^(MULd(K[4*round+c].c[3]));
		a[c+8] = a[c+8]^(MULd(K[4*round+c].c[0]))^(MUL9(K[4*round+c].c[1]))^(MULe(K[4*round+c].c[2]))^(MULb(K[4*round+c].c[3]));
		a[c+12]= a[c+12]^(MULb(K[4*round+c].c[0]))^(MULd(K[4*round+c].c[1]))^(MUL9(K[4*round+c].c[2]))^(MULe(K[4*round+c].c[3]));
	}
	free(copy);

}

unsigned char mul2(unsigned char a) {
	return (a&0x80)!=0 ? ((a<<1)^0x1b)&0xff : (a<<1)&0xff;
}

void _encrypt(unsigned char* a, round_key* K) {
	addRoundKey(K, a, 0);
	for (int rd = 1; rd < 10; rd++) {
		subBytes(a);
		shiftRows(a);
		mixColumns(a);
		addRoundKey(K, a, rd);
	}

	subBytes(a);
	shiftRows(a);
	addRoundKey(K, a, 10);
}

void _decrypt(unsigned char* a, round_key* K){
	addRoundKey(K, a, 10);
	invShiftRows(a);
	invSubBytes(a);

	for (int rd = 9; rd > 0; rd--) {
		invMixColumns(a);
		invAddRoundKey(K, a, rd);
		invSubBytes(a);
		invShiftRows(a);

	}
	
	addRoundKey(K, a, 0);
}
