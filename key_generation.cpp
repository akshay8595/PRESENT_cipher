#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
using namespace std;
//generate round keys

class key_generation
{
	int key[80];	//initial key of 80 bits
	int key_up[80];	//required to generate round keys
	int k[32][80]; 	//round key set
	int s_box[16][4];	//s_box
	int place;	//required for final step of key generation
	int num;
	
	public:
	int sbox[16][4];	
	int key_schedule[32][80];	//variable to share round keys
	key_generation()	//constructor to initialize keys as soon as the object is created
	{
	//	cout<<"class initialised";
		int s_box[16][4]={ {1,1,0,0}, {0,1,0,1}, {0,1,1,0}, {1,0,1,1}, {1,0,0,1}, {0,0,0,0}, {1,0,1,0}, {1,1,0,1}, {0,0,1,1}, {1,1,1,0}, {1,1,1,1}, {1,0,0,0}, {0,1,0,0}, {0,1,1,1}, {0,0,0,1}, {0,0,1,0}};
		int sbox[16][4]={ {1,1,0,0}, {0,1,0,1}, {0,1,1,0}, {1,0,1,1}, {1,0,0,1}, {0,0,0,0}, {1,0,1,0}, {1,1,0,1}, {0,0,1,1}, {1,1,1,0}, {1,1,1,1}, {1,0,0,0}, {0,1,0,0}, {0,1,1,1}, {0,0,0,1}, {0,0,1,0}};
	
		for(int i=0; i<80; ++i)		//initial key generation K
			{
			key[i]=rand()%2;
			key_up[i]=key[i];
			k[0][i] = key[i];		//first round key is same
			}
		for(int j=1; j<32; ++j)		//key update for next 31 rounds
		{			
			for(int i=0; i<80; ++i)		//linear shift by 61 bits to left
			{
				k[j][i] = key_up[(i+19)%80];	
			}
			
			place = k[j][76]*1 + k[j][77]*2 + k[j][78]*4 + k[j][79]*8;		//s box permutation
			for(int i=76;i<80;++i)
			{
				k[j][i] = s_box[place][i-76];
			}
			num = j;
			
			while(num>0)		//round counter xor
			{
				place = 15;
				k[j][place] = k[j][place]^(num%2); //bitwise XOR with k15,k16,k17,k18,k19 with round counter
				place++;
				num/=2;
			}
			
			for(int i=0;i<80;++i)	//key stored for subsequent update
			{
				key_up[i] = k[j][i];
			}
	//	cout<<"\nround key "<<j;
		}
	//	cout<<"keys generated";
	}
	void in_it()	//key_schedule[][] has been initialized to share the keys
		{
		for(int j=0;j<32;++j)
		{
			for(int i=0;i<80;++i)
			{
				key_schedule[j][i]=k[j][i];
			}
		}
	}
};
