#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include "aes.h"
#define NUM(x) (x<58)?(x-48):(x-87)

const char hex[] = "0123456789abcdef";
const char cannotdecrypt[] = "b13dc6eec80a0ed858a60c83861bb0969bc18b0e27a3f3420c6d423bdc95704121ea3958ae803c527d3220e78b4dd95dd8a8aa608258369236658e3ad724ccedf3a7c834f0cc04896eaa57f23e8b880f";
const char alphabet[] = "QWERTYUIOPASDFGHJKLZXCVBNM,.;?!()1234567890zxcvbnmasdfghjklqwertyuiop";

unsigned char *pad(char* argv, int* argc) {
	int raw = strlen(argv);
	unsigned char *align;
	if (raw%KSIZE) {
		int size = *argc  = (raw/KSIZE+1)* KSIZE * sizeof(unsigned char);
		align = (unsigned char *)malloc(size);
		for (int i = raw; i < size; i++)
			align[i] = 0xff;
	} else {
		*argc = raw;
		align = (unsigned char *)malloc(raw * sizeof(unsigned char));
	}
	for (int i = 0; i < raw; i++)
		align[i] = argv[i];
	return align;
}

unsigned char *group(char* argv, int* argc) { // since it's key or cipher must multiples of 32
	int raw = strlen(argv);
	if (raw%32) {
		printf("Invalid ciphertext\n");
		return 0;
	}
	*argc = raw>>1;
	unsigned char *block = (unsigned char *)malloc((raw>>1)*sizeof(unsigned char));
	for (int i = 0; i < raw; i+=2) {
		int hb = argv[i];
		int lb = argv[i+1];
		block[i>>1] = (NUM(hb)) * KSIZE + (NUM(lb));
	} // print_key(block);
	return block;	
}

int main(int argc, char **argv) {

	unsigned char *input = NULL;
    int size, mode = 0;
	unsigned char key[KSIZE] =
	{
		0xf0, 0x0f, 0xf0, 0x0f,
		0x0f, 0xf0, 0x0f, 0xf0,
		0x0f, 0xf0, 0x0f, 0xf0,
		0xf0, 0x0f, 0xf0, 0x0f,
	}; // default key

	while (1) {
        static struct option long_options[] = {
            {"decrypt",  required_argument, 0, 'd'},
            {"encrypt",  required_argument, 0, 'e'},
            {"generate", no_argument,       0, 'g'},
            {"key",      required_argument, 0, 'k'},
            {0, 0, 0, 0}
        };
        int option_index =  0; 
        int optc = getopt_long (argc, argv, "d:e:gk:", long_options, &option_index);

        if (optc == -1) {
            break;
        }
        switch (optc) {
            case 0:
            break;

            case 'd': // printf("decrypt\n");
            	if (strcmp(cannotdecrypt, optarg) == 0) {
            		printf("cheater: it is forbidden to decrypt the challenge ciphertext\n");
            		return 0;
            	}
            	mode = 1; // need to first group in blocks of 16
            	input = group(optarg, &size);
            	if (input == 0)
            		return 0;
            break;

            case 'e': // printf("encrypt\n");
            	mode = 2;
            	input = pad(optarg, &size);
            break;

            case 'g':
            	srand((unsigned int) time(0) + getpid());
            	for (int i = 0; i < 32; i++)
            		putchar(hex[rand() % 16]);
            	printf("\n");
            break;

            case 'k': {
            	char *line = NULL;
           		size_t len = 0;
            	FILE *fp = NULL;
            	fp = fopen(optarg, "r");	// optarg is file name
            	if (!fp) {
        			printf ("Open key file failed\n");
        			return 0;
    			}
    			if (getline(&line, &len, fp) == -1) {
    				printf ("Read key file failed\n");
        			return 0;
    			}
    			if (strlen(line) < 32) {
    				printf ("Invalid key file\n");
        			return 0;
    			}
            	for (int i = 0; i < 32; i+=2) {
					int hb = line[i];
					int lb = line[i+1];
					key[i>>1] = (NUM(hb)) * KSIZE + (NUM(lb));
				}	 // print_key(key);
            	fclose (fp);
            	free(line);
            	break; 
            }

            case ':':
            	printf("missing args\n");
            break;

            case '?':  
            break;

            default:
            	abort();
        }
    }

    round_key *K = (round_key *)calloc(KROUND, sizeof(round_key));
	genRoundKey(K, key);

    if (mode == 1) {
    	// decrypt
    	for (int i = 0; i < size; i+=KSIZE) 
			_decrypt(&input[i], K);

		for (int i = 0; i < size; i++) {
            if ((input[i] > 96 && input[i] < 123) || (input[i] > 64 && input[i] < 91) 
                || (input[i] > 47 && input[i] < 58)) // {a-zA-Z0-9}
                printf("%c", input[i]);
            else {
                switch (input[i]) {
                    case 255:
                    break;
                    case 44:
                    case 46:
                    case 59:
                    case 63:
                    case 33:
                    case 40:
                    case 41:
                        printf("%c", input[i]);
                    break;
                    default: {
                        int shuffle = input[i] % 69;
                        shuffle = (shuffle * 67) % 69;
                        printf("%c", alphabet[shuffle]);
                    }
                }
            }
			// if (input[i]==255)
			// 	break;
			// printf("%c", input[i]);
		}
		printf("\n");
    } else if (mode == 2){
    	// encrypt
		for (int i = 0; i < size; i+=KSIZE) // { 
			_encrypt(&input[i], K);
		
		for (int i = 0; i < size; i++)
			printf("%02x", input[i]);
		printf("\n");
    }

	if (input)
		free(input);
	return 0;
}