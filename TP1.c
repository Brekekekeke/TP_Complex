#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef int bool;
#define true 1
#define false 0

#define TAILLETAB 4

//int DEBUG = true;
int DEBUG = false;

int KMAX;
int LMAX;
int SOMMEMAX;

void remplirTab (int * T);
void methode1 (int * T);
void methode2 (int * T);

int main(int argc, char *argv[])
{
	int T[TAILLETAB];
	remplirTab(T);
	methode1(T);
	methode2(T);
	return 0;
}

void remplirTab(int * T) {
// Remplir le tableau
	int i;
	for (i = 0; i<= TAILLETAB - 1; i++) {
		T[i] = -i+1;
	}
}

void methode1 (int * T) {
// Tester toutes les sous-séquences possibles ---- methode 1 = O(n^3)
	if(DEBUG == true){printf("METHODE 1\n");}
	int kmax = 0, lmax = 0, k = 0, l = 0, somme = T[0], sommeMax = T[0];
	for (k = 0; k <= TAILLETAB - 1; k++) {
		if (DEBUG == true) {printf("---LOOP %d-------------------------\n", k);}
		for (l = k; l <= TAILLETAB - 1; l++) {
			int m;
			for (m = k; m <= l; m++) {
				if(l == 0 && k == 0) {somme = T[0]; SOMMEMAX = T[0]; LMAX = 0; KMAX = 0;}
				else {somme = somme + T[m];}
				if(DEBUG == true){printf(">k : %d, l: %d\n", k, l); printf("T[%d] = : %d\n",m, T[m]); printf("somme : %d\n", somme);}
			}
			if (somme > sommeMax) {
				sommeMax = somme;
				kmax = k;
				lmax = l;
				if(DEBUG == true){printf("temp kmax:%d temps lmax: %d\n", kmax, lmax);}
			}
			somme = 0;
		}
	}
	KMAX = kmax;
	LMAX = lmax;
	SOMMEMAX = sommeMax;
	printf("methode 1: KMAX : %d LMAX : %d SOMMEMAX: %d\n", KMAX, LMAX, SOMMEMAX);
}

void methode2(int *T) {
// S(k, l) = S(k, l-1) + T[l] ---- methode2 = O(n^2)
	if(DEBUG == true){printf("METHODE 2\n");}
	int kmax = 0, lmax = 0, k = 0, l = 0, somme, sommeMax = T[0];
	for (k = 0; k <= TAILLETAB - 1; k++) {
		if (DEBUG == true) {printf("---LOOP %d-------------------------\n", k);}
		for (l = k; l <= TAILLETAB - 1; l++) {
			if (l == 0 && k == 0) { somme = T[0]; SOMMEMAX = T[0]; LMAX = 0; KMAX = 0; }
			else { somme = somme + T[l]; }
			if(DEBUG == true){printf(">k : %d, l: %d\n", k, l); printf("T[%d] = : %d\n",l, T[l]); printf("somme : %d\n", somme);}
			if (somme > sommeMax) {
				sommeMax = somme;
				kmax = k;
				lmax = l;
				if(DEBUG == true){printf("temp kmax:%d temps lmax: %d\n", kmax, lmax);}
			}
		}
		somme = 0;
	}
	KMAX = kmax;
	LMAX = lmax;
	SOMMEMAX = sommeMax;
	printf("methode 2: KMAX : %d LMAX : %d SOMMEMAX: %d\n", KMAX, LMAX, SOMMEMAX);
}

void methode3 (int * T) {
// diviser pour régner
	
}
