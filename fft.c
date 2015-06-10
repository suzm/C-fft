/*
 * This file contains codes realize Fast Fourier Transform; 
 * Created By Suzm 2015.06.10.
 * Finised 2015.06.10.
 * Copyright reserved.
 * Compiled with gcc `gcc fft.c -std=c99 -lm -o fft`.
 * 
 */
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.1415926
#define FORWARD 1
#define BACKWARD 0


unsigned reversebit(unsigned a,unsigned char );

void fft(double _Complex *in, double _Complex *out, unsigned char N,short sign);
void cdprintf(double _Complex *, unsigned );

int main(int argc, char const *argv[])
{
	double _Complex *in, *out;
	double real,imag;
	unsigned short N;

	printf("Please input sequence lenth: ");
	scanf("%hu",&N);
	unsigned listlenth = pow(2,N);
	in = (double _Complex *)malloc(sizeof(double _Complex)*pow(2,N));
	for(int i=0;i<pow(2,N);i++){
		scanf("%lf %lf",&real,&imag);
		in[i]=real+imag*I;
	}

	out = (double _Complex *)malloc(sizeof(double _Complex)*pow(2,N));
	
	printf("\nFORWARD fft"); 
	fft(in, out, N,FORWARD);
	cdprintf(out,listlenth);

	printf("\nBACKWARD fft"); 
	fft(out,in,N,BACKWARD);
	cdprintf(in,listlenth);

	putchar('\n');
	free(out);
	free(in);
	return 0;
}

void fft(double _Complex *in, double _Complex *out,unsigned char N, short sign)
{
	double _Complex *mid;
	unsigned temp, temp1,rank;
	unsigned listlenth = pow(2,N);

	mid=(double _Complex *)malloc(sizeof(double _Complex)*listlenth);
	for(unsigned i=0;i<listlenth;i++)
		mid[i]=in[reversebit(i,(unsigned char)N)];

	unsigned j, t, interval;
	double _Complex exponent, exponent_unit;

	interval = 1;
	for(unsigned i=1;i<=N;i++){
		j=0;
		while(j<listlenth){
			exponent_unit = (sign<=0)? cexp(I*PI/interval):cexp(-I*PI/interval);
			exponent= 1;
			for(t=0;t<interval*2;t++){
				out[t+j]=mid[t%interval+j]+exponent*mid[t%interval+interval+ j];
				exponent *= exponent_unit;
			}
			j=j+interval*2;
		}
		interval *= 2;
		memcpy(mid,out,listlenth*sizeof(double _Complex));
	}

	if (sign <=0){
		for(j = 0;j <listlenth;j++)
			out[j] /= listlenth;
	}
	free(mid);
}

unsigned  reversebit(unsigned a, unsigned char N)
{
	/*
		This function is used to reverse number bit:
		For Example : 6 in binary is 110, it's reverse bit is 011 which is 3(Oct) .
		so, 3=reversebit(6, 3); 
	*/
	unsigned b=0, c=1;
	for(unsigned char  i=1;i<=N;i++)
	{
		b=b<<1;
		b = b+(c&a) ;
		a=a>>1;
	}
	return b;
}
void cdprintf(double _Complex * in,unsigned N)
{
	putchar('\n');
	for(unsigned i=0;i<N;i++)
		printf("%lf%+lf*I%c",creal(in[i]),cimag(in[i]),i%5==4?'\n':'\t' );
}
