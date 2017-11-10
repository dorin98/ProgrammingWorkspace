/*		Big Numbers
	Comanda de rulare: g++ bignumbers.cpp */
#include <iostream>
#define max_size 1<<10 // Numarul maxim de cifre este 2^10 - 1, pastrand in variabila ramasa dimensiunea numarului

using namespace std;

void readBigNumber(int bigNumber[])
{
	// ! Citirea se poate modifica, in functie de datele de intrare ale problemei. !
	string x;
	cin>>x;
	bigNumber[0] = x.size();
	for (int i = bigNumber[0] ; i ; --i)
		bigNumber[i] = x[bigNumber[0] - i] - '0';
}

int cmp(int A[], int B[])
{
	// Returneaza 1 daca A este mai mare, 2 daca B este mai mare, sau 0 daca sunt egale.
	if (A[0] > B[0]) return 1;
	else if (B[0] > A[0]) return 2;
	for (int i = A[0] ; i ; --i)
		if (A[i] > B[i]) return 1;
		else if (B[i] > A[i]) return 2;
	return 0;
}

void add(int A[], int B[])
{
	int R[max_size], T = 0; // T = cifra de transport. Ex. 9+7=16 -> T = 1.
	// Egalarea numarului de cifre prin adaugarea de zerouri numarului mai mic.
	if (B[0] > A[0])
		for (int i = A[0] + 1 ; i <= B[0] ; ++i)
			A[i] = 0;
	else 
		for (int i = B[0] + 1 ; i <= A[0] ; ++i)
			B[i] = 0;
	// Adunarea efectiva. #tbtclasaintai
	int N = (A[0] > B[0]) ? A[0] : B[0]; // N = numarul de cifre ale numarului mai mare.
	for (int i = 1; i <= N ; ++i)
	{
		R[i] = A[i] + B[i] + T;
		T = R[i]/10; // T va fi 0 sau 1.
		R[i] %= 10;
	}
	// Daca in final ramane transport, il adaugam. Ex. 73+31=104 -> Trebuie adaugat acel 1.
	if (T>0)
		R[A[0]+1] = T;
	//Afisarea rezultatului
	cout<<"Suma: ";
	for (int i = N + T ; i ; --i)
		cout<<R[i];
	cout<<'\n';
}

void diff(int A[], int B[])
{
	// Functia realizeaza diferenta R = A - B (vezi apelul functiei).
	int R[max_size], T = 0;
	R[0] = A[0];
	for (int i = B[0] + 1 ; i <= A[0] ; ++i)
		B[i] = 0;
	for (int i = 1 ; i <= A[0] ; ++i)
	{
		R[i] = A[i] - (B[i] + T);
       	if (R[i] < 0) T = 1; 
       	else T = 0;
       	if (T > 0) R[i] += 10;
       	// Cele 3 linii de mai sus se pot reduce la urmatoarea expresie: R[i] += ( T = (R[i] = A[i] - B[i] + T) < 0) ? 10 : 0. #justCthings
   	}
  	while (R[R[0]] <= 0) R[0]--;
  	cout<<"Modulul diferentei: ";
  	for (int i = R[0] ; i ; --i)
  		cout<<R[i];
  	cout<<'\n';
}

void mult(int A[], int B[])
{
	int R[max_size], T = 0;
	R[0] = A[0] + B[0] - 1;
	for (int i = 1 ; i <= A[0] + B[0] ; ++i) // Initializarea vectorului corespunzator rezultatului cu 0.
		R[i] = 0;
	for (int i = 1 ; i <= A[0] ; ++i)
		for (int j = 1; j <= B[0] ; ++j)
				R[i + j - 1] += A[i] * B[j];
	for (int i = 1 ; i <= R[0] ; ++i)
	{
		R[i] += T;
		T = R[i] / 10;
		R[i] %= 10;
	}
	if (T > 0) R[++R[0]] = T;
	cout<<"Produsul: ";
	for (int i = R[0] ; i ; --i)
		cout<<R[i];
	cout<<'\n';

}

int main()
{
	int A[max_size], B[max_size];
	readBigNumber(A);
	readBigNumber(B);
	add(A,B);
	if (cmp(A,B) == 1) diff(A,B);
	else if (cmp(A,B) == 2) diff(B,A);
	else cout<<"Diferenta: 0\n"; // A si B sunt egale.
	mult(A,B);
	return 0;
}