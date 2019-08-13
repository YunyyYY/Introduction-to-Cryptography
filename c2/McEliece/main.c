#include "cheat.h"

int main(int argc, char **argv) {
    int P[49] = {
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0
    };
    int invP[49] = {
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        0,0,0,0,0,0,0
    };
    int mode=0;
    int per[7] = {0,3,1,6,2,5,4};
    char *input = NULL;

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

            case 'd':       // printf("decrypt\n");
                if (strcmp(challenge, optarg) == 0) {
                    printf("cheater: it is forbidden to decrypt the challenge ciphertext\n");
                    return 0;
                }
                mode = 1;   // mode 1 de
                input = calloc(strlen(optarg), sizeof(char));
                strcpy(input, optarg);
            break;

            case 'e': {     // printf("encrypt\n");
                mode = 2;   // mode 2 en
                input = calloc(strlen(optarg), sizeof(char));
                strcpy(input, optarg);
                break;
            }

            case 'g':
                gen_key();
            	printf("\n");
            break;

            case 'k': {
                char next_c;
                FILE *fp = NULL;
                fp = fopen(optarg, "r");    // optarg is file name
                if (!fp) {
                    printf ("Open key file failed\n");
                    return 0;
                }
                for (int i = 0; i < 7; i++) {
                    if ((next_c = getc(fp))<0) {
                        printf ("Read key file failed\n");
                        return 0;
                    }
                    per[i] = (next_c-97) % 7;    // if key is invalid, cast to.
                }
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

    if (mode == 2) {                        // encrypt mode
        for (int row = 0; row < 7; row++)   // first set P
            P[row * 7 + per[row]] = 1;
        int size = strlen(input);
        set_key(P);
        for (int i = 0; i < size; i++)
            en_crypt((int)input[i]);
        printf("\n");
    } else if (mode == 1) {                 // decrypt mode
        for (int row = 0; row < 7; row++)   // Inverse of a permutation matrix 
            invP[per[row]*7 + row] = 1;     // is its transpose.
        // for (int i = 0; i < 49; i++) {
        //     if (i%7==0)
        //     printf("\n");
        //     printf("%d ", invP [i]);
        // }
        int word[14], hat_word[14], tmp, size = strlen(input);
        if (size & 3)
            size -= (size & 3);
        for (int i = 0; i < size; i+=4){
            tmp = (NUM(input[i]))&0xf;
            for (int bit = 2; bit >-1; bit--) {
                word[bit] = tmp & 1;        // printf("%d ", word[bit]);
                tmp >>= 1;
            }
            tmp = (NUM(input[i+1]))&0xf;
            for (int bit = 6; bit >2; bit--) {
                word[bit] = tmp & 1;        // printf("%d ", word[bit]);
                tmp >>= 1;
            }
            tmp = (NUM(input[i+2]))&0xf;
            for (int bit = 9; bit > 6; bit--) {
                word[bit] = tmp & 1;        // printf("%d ", word[bit]);
                tmp >>= 1;
            }
            tmp = (NUM(input[i+3]))&0xf;
            for (int bit = 13; bit > 9; bit--) {
                word[bit] = tmp & 1;        // printf("%d ", word[bit]);
                tmp >>= 1;
            }
            for (int bit = 0; bit < 7; bit++) {
                hat_word[bit] = hat_word[bit+7] = 0;
                for (int k = 0; k < 7; k++) {
                   hat_word[bit] += word[k] * invP[k*7 + bit]; 
                   hat_word[bit+7] += word[k+7] * invP[k*7 + bit]; 
                }
                hat_word[bit] &= 1;
                hat_word[bit+7] &= 1;
            }
            de_crypt(hat_word);
        }
        printf("\n");
    }
    if(input)
        free(input);
	return 0;
}