// Proteus
// icq: 133575351  email:lawnmower-man@mail.ru 
// не тестировался !!! (хотя ошибаться в нём и негде)

#include<stdio.h>
#include<string.h>
#include <iostream>

using namespace std;


typedef unsigned char byte;


class RC4 
{
	byte S[256];
	unsigned int i, j;
	inline void Swap(int, int);
public:
	byte GetXor();
	void Init(byte* key, int len);
	void Crypt(byte* data, int size);
};

void RC4::Init(byte* key, int len)
{
	if (!len) len = strlen((char*)key);
	for (i = 0; i < 256; i++) 
		S[i] = i;
	for (i = j = 0; i < 256; i++) 
	{
		j = (j + S[i] + key[i % len]) & 255;
		Swap(i, j);
	}
	i = j = 0;
}


byte RC4::GetXor()
{
	i = (i + 1) & 255; j = (j + S[i]) & 255; Swap(i, j);
	return S[(S[i] + S[j]) & 255];
}


void RC4::Swap(int i, int j)
{
	byte t = S[i]; S[i] = S[j]; S[j] = t;
}


void RC4::Crypt(byte* data, int size)
{
	int n;
	for (n = 0; n < size; n++)
	{
		data[n] ^= GetXor();
		cout << data[n] << endl;
	}
}



void main()
{
	if (sizeof(byte) != 1) 
		printf("type error\n\a"), getchar();
	RC4 rc4;
	byte data[] = "qwerty";
	rc4.Init((byte*)"initkey", 0);
	rc4.Crypt(data, 6);
}

