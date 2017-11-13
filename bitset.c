#include <stdio.h>
#define uint unsigned int
#define maxSize 10
#define maxLength 80

typedef unsigned char bitSet[maxSize];
static unsigned int MASK = 0x80; //  = 1000 000

void set_insert(bitSet S, uint n)
{
	S[n/8] |= MASK >> (n%8);
}

void set_delete(bitSet S, uint n)
{
	S[n/8] &= ~(MASK >> (n%8));
}

int set_has(bitSet S, uint n)
{
	return n < maxLength && ( S[n/8] & (MASK >> (n%8)) );
}

void set_delete_all(bitSet S)
{
	for (int i = 0 ; i < maxSize ; S[i++] = 0);
}

int set_card(bitSet S)
{
	int cardS = 0;
	for (int i = 0 ; i <= maxLength ; ++i)
		if (set_has(S,i)) ++cardS;
	return cardS;
}

int set_is_empty(bitSet S)
{
	for (int i = 0 ; i <= maxLength ; ++i)
		if(S[i]) return 1;
	return 0;
}

void set_read(bitSet S)
{
	int n, x;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &x);
		set_insert(S,x);
	}
}

void set_print(bitSet S)
{
	int cardS = set_card(S);
	if (cardS == 0)
	{
		printf("The set is empty!\n");
		return;
	}
	printf("{ ");
	for (int i = 0 ; i <= maxLength ; ++i)
	{
		if (set_has(S,i) != 0 )
		{
			--cardS;
			printf("%d", i);
			cardS == 0 ? printf(" }\n") : printf(", ");
		}
	}
}

void set_reunion(bitSet A, bitSet B)
{
	bitSet C;
	for (int i = 0 ; i < maxSize ; ++i)
		C[i] = A[i] | B[i];
	set_print(C);
}

void set_intersection(bitSet A, bitSet B)
{
	bitSet C;
	for (int i = 0 ; i < maxSize ; ++i)
		C[i] = A[i] | B[i];
	set_print(C);
}

void set_difference(bitSet A, bitSet B)
{
	bitSet C;
	for (int i = 0 ; i < maxSize ; ++i)
		C[i] = (A[i]^B[i]) & (~B[i]);
	set_print(C);
}

int main()
{
	bitSet A, B, C;

	// Reading a set.
	set_delete_all(A);
	set_read(A);
	set_delete_all(B);
	set_read(B);

	/* #TODO
		Menu */
	
	return 0;
}
