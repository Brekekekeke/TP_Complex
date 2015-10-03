#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

#define TAILLETAB 1000
#define INTERVAL 1000

//int DEBUG = true;
int DEBUG = false;

int KMAX;
int LMAX;
int SOMMEMAX;

typedef struct retour retour;
struct retour {
    int k;
    int l;
    int somme;
};

void remplirTab (int * T, int t);
void printTab (int * T, int paramk, int paraml);
void methode1 (retour * monRetour, int * T, int t, bool verb);
void methode2 (retour * monRetour, int *T, int paramk, int paraml, bool verb);
void methode3 (retour * monRetour, int * T, int paramk, int paraml, bool verb);
void moitie (retour * monRetour, int * T, int paramk, int paraml, bool verb);
void milieu (retour * monRetour, int * T, int paramk, int mid, int paraml, bool verb);


int main(int argc, char *argv[])
{
	int t;
	printf("argc: %d, argv: %s\n", argc, argv[1]);
	if (argc == 2) {
		t = atoi(argv[1]);
	} else {
		t = TAILLETAB;
	}
	int T[t];
	remplirTab(T, t);
	//printTab(T, 0, t - 1);
	
	retour retour1, retour2, retour3;
	methode3(&retour3, T, 0, t - 1, true);
	methode2(&retour2, T, 0, t - 1, true);
	methode1(&retour1, T, t, true);

	return 0;
}


void remplirTab(int * T, int t) {
// Remplir le tableau
	int i;
	int n;
	srand (time (NULL));
	for (i = 0; i<= t - 1; i++) {
		n = rand() % INTERVAL;
		n -= INTERVAL / 2;
		T[i] = n;
	}
}

void printTab(int * T, int paramk, int paraml) {
	int i = paramk;
	for (i = paramk; i <= paraml; i++) {
		printf("Case %d: %d\n", i, T[i]);
	}
}

void methode1 (retour * monRetour, int * T, int t, bool verb) {
// Tester toutes les sous-séquences possibles ---- methode 1 = O(n^3)
	if(DEBUG == true){printf("METHODE 1\n");}
	int kmax = 0, lmax = 0, k = 0, l = 0, somme = T[0], sommeMax = T[0];
	for (k = 0; k <= t - 1; k++) {
		if (DEBUG == true) {printf("---LOOP %d-------------------------\n", k);}
		for (l = k; l <= t - 1; l++) {
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
	monRetour->k = kmax;
	monRetour->l = lmax;
	monRetour->somme = sommeMax;
	if (verb == true) {
		printf("methode 1: k max : %d l max : %d somme : %d\n", monRetour->k, monRetour->l, monRetour->somme);
	}
}

void methode2(retour * monRetour, int *T, int paramk, int paraml, bool verb) {
// S(k, l) = S(k, l-1) + T[l] ---- methode2 = O(n^2)
	if(DEBUG == true){printf("METHODE 2\n");}
	int kmax = 0, lmax = 0, k = paramk, l = paraml, somme, sommeMax = T[paramk];
	for (k = paramk; k <= paraml; k++) {
		if (DEBUG == true) {printf("---LOOP %d-------------------------\n", k);}
		for (l = k; l <= paraml; l++) {
			if (l == paramk && k == paramk) { somme = T[paramk]; monRetour->somme = T[paramk]; monRetour->l = paramk; monRetour->k = paramk; }
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
	
	monRetour->k = kmax;
	monRetour->l = lmax;
	monRetour->somme = sommeMax;
	
	if (verb == true) {
		printf("methode 2: k max : %d l max : %d somme : %d\n", monRetour->k, monRetour->l, monRetour->somme);
	}
}

void methode3 (retour * monRetour, int * T, int paramk, int paraml, bool verb) {
// diviser pour régner Diviser la sequence en 2, calculer la sous sequence gauche puis droite puis une qui contient l'élement du milieu puis prendre le max des 3
	if(DEBUG == true){printf("METHODE 3\n");}
	moitie(monRetour, T, paramk, paraml, false); 
	if (verb == true) {
		printf("methode 3: k max : %d l max : %d somme : %d\n", monRetour->k, monRetour->l, monRetour->somme);
	}
}


void moitie (retour * monRetour, int * T, int paramk, int paraml, bool verb) {
	bool verbose = false;
	if (paramk == paraml) {
		monRetour->k = paramk;
		monRetour->l = paraml;
		monRetour->somme = T[paramk];
	} else {
		int mid = (int) ((paramk + paraml)/2);
		retour retourGauche;
		moitie(&retourGauche, T, paramk, mid, verbose);
		retour retourDroit;
		moitie(&retourDroit, T, mid + 1, paraml, verbose);
		retour retourMid;
		milieu(&retourMid, T, paramk, mid, paraml, verbose);
		
		if (retourGauche.somme >= retourDroit.somme && retourGauche.somme >= retourMid.somme) {
			monRetour->k = retourGauche.k;
			monRetour->l = retourGauche.l;
			monRetour->somme = retourGauche.somme;
			if (DEBUG == true) {printf("moitie gauche, somme : %d\n", monRetour->somme);}
		}
		else if (retourDroit.somme >= retourGauche.somme && retourDroit.somme >= retourMid.somme) {
			monRetour->k = retourDroit.k;
			monRetour->l = retourDroit.l;
			monRetour->somme = retourDroit.somme;
			if (DEBUG == true) {printf("moitie droite, somme : %d\n", monRetour->somme);}
		}
		else {
			monRetour->k = retourMid.k;
			monRetour->l = retourMid.l;
			monRetour->somme = retourMid.somme;
			if (DEBUG == true) {printf("moitie milieu, somme : %d\n", monRetour->somme);}
		}
	}
	if (verb == true) {
		printf("moitie: k max : %d l max : %d somme : %d\n", monRetour->k, monRetour->l, monRetour->somme);
	}
}

void milieu (retour * monRetour, int * T, int paramk, int mid, int paraml, bool verb) {
	int sommeg = T[mid];
	int somme = 0;
	int kmax = paramk;
	int lmax = paraml;
	int i, j;
	for (i = mid; i >= paramk; i--) {
		somme = somme + T[i];
		if (somme > sommeg) {
			kmax = i;
			sommeg = somme;
		}
	}
	if(DEBUG == true){printf("sommeg: %d\n", sommeg);}
	
	int sommed = T[mid + 1];
	somme = 0;
	for (j = mid + 1; j <= paraml; j++) {
		somme = somme + T[j];
		if (somme > sommed) {
				lmax = j;
				sommed = somme;
		}
	}
	if(DEBUG == true){printf("sommed: %d\n", sommed);}
	
	monRetour->k = kmax;
	monRetour->l = lmax;
	monRetour->somme = sommeg + sommed;
	if (verb == true) {
		printf("milieu : k max : %d l max : %d somme : %d\n", monRetour->k, monRetour->l, monRetour->somme);
	}
}
