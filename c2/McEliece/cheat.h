#ifndef CHEAT_H
#define CHEAT_H
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#define NUM(x) (x<58)?(x-48):(x-87)

static const char alphabet[] = "QWERTYUIOPASDFGHJKLZXCVBNM,.;?!()1234567890zxcvbnmasdfghjklqwertyuiop";
static const char hex[] = "0123456789abcdef";

static const char challenge[] = "703c256655703c7055704c66193c25706970337016702\
5700f705570706625705a7033703c3c55705a663c66557025662a7070665a666970256666664c6\
655703c662a705a3c4c66257019702a70167043703c70002a2a66437025705a66337019702a704\
3703c66167043703c703c2a33702a704c3c4c6655703c6633702a704c665a66693c16704c66167\
0197016707f6655707066";

static const int S[] = {
	1,	1,	1,	0,
    0,	1,	0,	0,
    1,	1,	0,	0,
    1,	0,	1,	1
};

static const int invS[] = {
	0,	1,	1,	0,
    0,	1,	0,	0,
    1,	0,	1,	0,
    1,	1,	0,	1
};

static const int H[] = {
	1,	0,	1,	0,	1,	0,	1,
    0,	1,	1,	0,	0,	1,	1,
    0,	0,	0,	1,	1,	1,	1
}; // 4, 2, 6, 1, 5, 3, 7

static const int parity_check[] = {4, 2, 6, 1, 5, 3, 7};

static const int G[] = {
	1,     1,    1,     0,     0,     0,     0,
    1,     0,    0,     1,     1,     0,     0,
    0,     1,    0,     1,     0,     1,     0,
    1,     1,    0,     1,     0,     0,     1
	// 1,     1,     0,     1,
 //    1,     0,     1,     1,
 //    1,     0,     0,     0,
 //    0,     1,     1,     1,
 //    0,     1,     0,     0,
 //    0,     0,     1,     0,
 //    0,     0,     0,     1
};

static const int R[] = {
	0,	0,	1,	0,	0,	0,	0,
    0,	0,	0,	0,	1,	0,	0,
    0,	0,	0,	0,	0,	1,	0,
    0,	0,	0,	0,	0,	0,	1
};

static const int SG[] = {

     0,     0,     1,     0,     1,     1,     0,
     1,     0,     0,     1,     1,     0,     0,
     0,     1,     1,     1,     1,     0,     0,
     0,     1,     1,     0,     0,     1,     1
	// 0,     1,     0,     0,
 //    0,     0,     1,     1,
 //    1,     0,     1,     1,
 //    0,     1,     1,     0,
 //    1,     1,     1,     0,
 //    1,     0,     0,     1,
 //    0,     0,     0,     1
};

static int hat_G[28]; 

void en_crypt(int letter);
void de_crypt(int* word);
void set_key(int* P);
void gen_key();

#endif