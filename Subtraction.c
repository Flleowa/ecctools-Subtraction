/*
Developed by Luis Alberto
email: alberto.bsd@gmail.com
gcc -O3 -o Subtraction Subtraction.c -march=native -mtune=native gmpecc.c util.o -lgmp
Modification FlleOWA Admin@flleowa.ru
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <gmp.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "util.h"

#include "gmpecc.h"

#define STRLEN 132

struct Elliptic_Curve EC;
struct Point G;
struct Point DoublingG[256];

const char *EC_constant_N = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141";
const char *EC_constant_P = "fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f";
const char *EC_constant_Gx = "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798";
const char *EC_constant_Gy = "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";

const char *formats[3] = {"publickey"};
const char *looks[2] = {"compress","uncompress"};

void set_publickey(char *param,struct Point *publickey);
void generate_strpublickey(struct Point *publickey,bool compress,char *dst);

char str_publickey[132];

struct Point A,B,C;

int FLAG_NUMBER = 1;
int FLAG_P = 0;
int FLAG_O = 0;

mpz_t number;

int main(int argc, char **argv)  {
	int i = 0;
	char c = '\0';
	int number_of_iterations = 1; //default is one
	char key_str[STRLEN];//*key_str = NULL;
	size_t len = STRLEN;//0;
	char *input_file_name = NULL, *output_file_name = NULL;
	FILE *INPUT = stdin, *OUTPUT = stdout;
	
	char buffer_input[1024];
	mpz_init_set_str(EC.p,	EC_constant_P,	16);
	mpz_init_set_str(EC.n,	EC_constant_N,	16);
	mpz_init_set_str(G.x,	EC_constant_Gx,	16);
	mpz_init_set_str(G.y,	EC_constant_Gy,	16);
	
	init_doublingG(&G);
	mpz_init(number);

	mpz_init_set_ui(B.x, 0);
	mpz_init_set_ui(B.y, 0);
	
	//len = strlen(argv[1]);
	//key_str = (char *)malloc(len+1);
	strcpy(key_str, argv[1]);

	while ((c = getopt(argc, argv, "p:i:o::s:n:")) != -1) {
		switch(c) {
			case 'p': //key
				//len = strlen(optarg);
				//key_str = (char *)realloc(key_str, len+1);
				strcpy(key_str, optarg);
				FLAG_P = 1;
			break;
			case 's': //subtractor
				len = strlen(optarg);
				if (len == 66)
					FLAG_NUMBER = optarg[0] == '0' && optarg[1] == 'x';
				else if (len == 130)
					FLAG_NUMBER = 0;

				if (FLAG_NUMBER) 
					mpz_set_str(number, optarg, 0);
				else 
					set_publickey(optarg, &B);
			break;
			case 'n': //number of iterations
				number_of_iterations = strtol((char *)optarg, NULL, 10);
				if (number_of_iterations < 1) {
					fprintf(stderr, "[E] invalid number of iteration %s, setting default N = 1\n", optarg);
					number_of_iterations = 1;
				}
			break;
			case 'i': //input file
				input_file_name = optarg;
				if ((INPUT = fopen(input_file_name, "r")) == NULL) {
					fprintf(stderr, "[E] can't open a file %s\n", input_file_name);
					exit (1);
				}
				if (fgets(key_str, STRLEN, INPUT) == NULL)//getline(&key_str, &len, INPUT) == -1)
					exit(0);
			break;
			case 'o': //output file
				output_file_name = argv[optind];
				if (output_file_name != NULL && output_file_name[0] != '-')
					if ((OUTPUT = fopen(output_file_name, "w")) == NULL) {
						fprintf(stderr, "[E] can't open/create a file '%s' redirecting output to standart output\n", output_file_name);
						output_file_name = NULL;
						OUTPUT = stdout;
					}
				FLAG_O = 1;
			break;
		}
	}
		
	mpz_mod(number, number, EC.n);
	
	mpz_init_set_ui(C.x, 0);
	mpz_init_set_ui(C.x, 0);

	if(FLAG_NUMBER)
		Scalar_Multiplication(G, &B, number);
	
	Point_Negation(&B, &C);
	mpz_set(B.x, C.x);
	mpz_set(B.y, C.y);
	
	do {
		len = strlen(key_str);
		if (key_str[len-1] == '\n')
			key_str[--len] = '\0';
		
		switch (len) {
			case 66:
			case 130:
				mpz_init_set_ui(A.x, 0);
				mpz_init_set_ui(A.y, 0);
				set_publickey(key_str, &A);
			break;
			default:
				if (key_str[0] != '\0')
					fprintf (stderr, "[E] unknown public key %s of length %ld\n", key_str, len);
				if (input_file_name != NULL)
					continue;
				else
					exit (0);
		}

		if (FLAG_O && output_file_name == NULL) {
			output_file_name = key_str;
			
			if ((OUTPUT = fopen(output_file_name, "w")) == NULL) {
				fprintf(stderr, "[E] can't open/create a file '%s' redirecting output to standart output\n", output_file_name);
				output_file_name = NULL;
				OUTPUT = stdout;
			}
		}
		
		for (i = 0; i < number_of_iterations; i++) {
			Point_Addition(&A, &B, &C);
			
			generate_strpublickey(&C, true, str_publickey);
			fprintf(OUTPUT, "%s\n", str_publickey);
			
			mpz_set(A.x, C.x);
			mpz_set(A.y, C.y);
		}
		
		fprintf(OUTPUT, "\n");
		
		if (output_file_name == key_str) {
			fclose (OUTPUT);
			output_file_name = NULL;
		}
	} while (input_file_name && fgets(key_str, STRLEN, INPUT) != NULL);//getline(&key_str, &len, INPUT) != -1);
	
	if (output_file_name != NULL)
		fclose (OUTPUT);
	//free (key_str);
	return 0;
}

void generate_strpublickey(struct Point *publickey,bool compress,char *dst)	{
	memset(dst,0,131);
	if(compress)	{
		if(mpz_tstbit(publickey->y, 0) == 0)	{	// Even
			gmp_snprintf (dst,67,"02%0.64Zx",publickey->x);
		}
		else	{
			gmp_snprintf(dst,67,"03%0.64Zx",publickey->x);
		}
	}
	else	{
		gmp_snprintf(dst,131,"04%0.64Zx%0.64Zx",publickey->x,publickey->y);
	}
}

void set_publickey(char *param,struct Point *publickey)	{
	char hexvalue[65];
	char *dest;
	int len;
	len = strlen(param);
	dest = (char*) calloc(len+1,1);
	if(dest == NULL)	{
		fprintf(stderr,"[E] Error calloc\n");
		exit(0);
	}
	memset(hexvalue,0,65);
	memcpy(dest,param,len);
	trim(dest," \t\n\r");
	len = strlen(dest);
	switch(len)	{
		case 66:
			mpz_set_str(publickey->x,dest+2,16);
		break;
		case 130:
			memcpy(hexvalue,dest+2,64);
			mpz_set_str(publickey->x,hexvalue,16);
			memcpy(hexvalue,dest+66,64);
			mpz_set_str(publickey->y,hexvalue,16);
		break;
	}
	if(mpz_cmp_ui(publickey->y,0) == 0)	{
		mpz_t mpz_aux,mpz_aux2,Ysquared;
		mpz_init(mpz_aux);
		mpz_init(mpz_aux2);
		mpz_init(Ysquared);
		mpz_pow_ui(mpz_aux,publickey->x,3);
		mpz_add_ui(mpz_aux2,mpz_aux,7);
		mpz_mod(Ysquared,mpz_aux2,EC.p);
		mpz_add_ui(mpz_aux,EC.p,1);
		mpz_fdiv_q_ui(mpz_aux2,mpz_aux,4);
		mpz_powm(publickey->y,Ysquared,mpz_aux2,EC.p);
		mpz_sub(mpz_aux, EC.p,publickey->y);
		switch(dest[1])	{
			case '2':
				if(mpz_tstbit(publickey->y, 0) == 1)	{
					mpz_set(publickey->y,mpz_aux);
				}
			break;
			case '3':
				if(mpz_tstbit(publickey->y, 0) == 0)	{
					mpz_set(publickey->y,mpz_aux);
				}
			break;
			default:
				fprintf(stderr,"[E] Some invalid bit in the publickey: %s\n",dest);
				exit(0);
			break;
		}
		mpz_clear(mpz_aux);
		mpz_clear(mpz_aux2);
		mpz_clear(Ysquared);
	}
	free(dest);
}
