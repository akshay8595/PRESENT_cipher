#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "key_generation.cpp"
using namespace std;

int main()
{
	int test[64]={0X0000000000000000};
	int test_copy[64]={0X0000000000000000};
	int count=0;
	int flag=0;
	key_generation key;		//object of key_generation. All keys have been generated in initialized
	key.in_it();		//key_schedule has been initialized for shared keys

	//	cout<<"\nText Generated\n";
	for(int round=0; round<31; ++round)
	{
		flag=0;
		cout<<"\n Round "<<round<<"\n";
		for(int step=0;step<64;++step)		//XOR keys
		{
			test[step] ^= key.key_schedule[round][step];
			test_copy[step]	= test[step];		
			cout<<test[step];
		}
		cout<<"\n";
		for(int step=0;step<64;++step)		//SBOX layer
		{
			count+=pow(2,flag-1)*test[step];
			flag++;
			if(flag!=0 && (flag%4)==0)
			{
				test[step] = key.sbox[count][4];
				test[step-1] = key.sbox[count][3];
				test[step-2] = key.sbox[count][2];
				test[step-3] = key.sbox[count][1];
				test_copy[step]	= test[step];
				test_copy[step-1]	= test[step-1];
				test_copy[step-2]	= test[step-2];
				test_copy[step-3]	= test[step-3];
				flag=0;
				count=0;
			}
		}

		for(int step=0;step<63;++step)		//LINEAR PERMUTATION OF KEYS
		{
			test[step]	= test_copy[(step*16)%63];
		}
		
		for(int step=0; step<63;++step)		//update text
		{
			test_copy[step]	= test[step];
		}
//	cout<<"\n round"<<round;
	}
			
	for(int step=0;step<64;++step)		//post whitening round
		{
			test[step] ^= key.key_schedule[31][step];
			test_copy[step]	= test[step];
		}
	cout<<"\n The Cipher Text Is \n";
	for(int step=0;step<64;++step)
	{
		cout<<test[step];
	}
	
	return 0;
}
