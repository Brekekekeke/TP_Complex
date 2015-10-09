/*
 * Utilisation:
 * Tous les paramètres sont facultatifs.
 * Sans paramètre, construit un tableau de taille TAILLETAB et exécute toutes les méthodes.
 * Le premier paramètre indique la taille du tableau souhaité et exécute toutes les méthodes.
 * Le deuxième paramètre indique le numéro de la méthode utilisée.
 * Le troisième paramètre indique le souhait d'exécuter la méthode 4 à fin de comparaison des résultats. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

#define TAILLETAB 10
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
    int methode;
};

void printRetour(retour * monRetour);
void remplirTab (int * T, int t);
void printTab (int * T, int paramk, int paraml);
void methode1 (retour * monRetour, int * T, int t, bool verb);
void methode2 (retour * monRetour, int *T, int paramk, int paraml, bool verb);
void methode3 (retour * monRetour, int * T, int paramk, int paraml, bool verb);
void methode4 (retour * monRetour, int *T, int paramk, int paraml, bool verb);
void moitie (retour * monRetour, int * T, int paramk, int paraml, bool verb);
void milieu (retour * monRetour, int * T, int paramk, int mid, int paraml, bool verb);


int main(int argc, char *argv[])
{
	bool verb = false;
	int t;
	if(DEBUG==true){printf("argc: %d, argv: %s\n", argc, argv[1]);}
	if (argc >= 2) {
		t = atoi(argv[1]);
	} else {
		t = TAILLETAB;
	}
	int T[t];
	remplirTab(T, t);
	//printTab(T, 0, t - 1);
	printf("Le tableau est de taille %s\n", argv[1]);
	if (argc == 4) {
		retour retour4; retour4.methode = 4; methode4(&retour4, T, 0, t - 1, verb); printRetour(&retour4);
	}
	if (argc >= 3) {
		if (atoi(argv[2]) == 4) {
			retour retour4; retour4.methode = 4; methode4(&retour4, T, 0, t - 1, verb); printRetour(&retour4);
		} else if (atoi(argv[2]) == 3) {
			retour retour3; retour3.methode = 3; methode3(&retour3, T, 0, t - 1, verb); printRetour(&retour3);
		} else if (atoi(argv[2]) == 2) {
			retour retour2; retour2.methode = 2; methode2(&retour2, T, 0, t - 1, verb); printRetour(&retour2);
		} else if (atoi(argv[2]) == 1) {
			retour retour1; retour1.methode = 1; methode1(&retour1, T, t, verb); printRetour(&retour1);
		} else {
			printf("Il n'y a que 4 methodes...\n");
		}
	} else {
		retour retour4; retour4.methode = 4; methode4(&retour4, T, 0, t - 1, verb); printRetour(&retour4);
		retour retour3; retour3.methode = 3; methode3(&retour3, T, 0, t - 1, verb); printRetour(&retour3);
		retour retour2; retour2.methode = 2; methode2(&retour2, T, 0, t - 1, verb); printRetour(&retour2);
		retour retour1; retour1.methode = 1; methode1(&retour1, T, t, verb); printRetour(&retour1);
	}
	return 0;
}

void printRetour(retour * monRetour) {
	printf("methode %d: k max : %d l max : %d somme : %d\n", monRetour->methode, monRetour->k, monRetour->l, monRetour->somme);
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
		printRetour(monRetour);
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
		printRetour(monRetour);
	}
}

void methode3 (retour * monRetour, int * T, int paramk, int paraml, bool verb) {
// diviser pour régner Diviser la sequence en 2, calculer la sous sequence gauche puis droite puis une qui contient l'élement du milieu puis prendre le max des 3
// implémentation du cours "Structures de données et algorithmes" de Pierre Geurts diapo 33 http://www.montefiore.ulg.ac.be/~geurts/Cours/sda/2011/06-resolution-a.pdf
// methode 3 = O(nlogn)
	bool subverb = verb;
	if(DEBUG == true){printf("METHODE 3\n");}
	moitie(monRetour, T, paramk, paraml, subverb); 
	if (verb == true) {
		printRetour(monRetour);
	}
}

void methode4 (retour * monRetour, int *T, int paramk, int paraml, bool verb) {
	// Calcul en un seul parcours. methode 4 = O(n)
	/*
	* Lire la première case dans lastSprint.
	* lire la première case dans currentSprint.
	* continuer tant que parcours < paraml
	* continuer tant que parcours < paraml && T[parcours] < T[parcours] + currentSprint.
	* 	si T[parcours] < 0 et currentSprint > lastSprint {lastSprint = currentSprint}
	* 	avancer parcours
	* si T[parcours] > lastSprint {lastSprint = T[parcours]}
	* avancer parcours
	*/
	
	if(DEBUG == true){printf("METHODE 4\n");}
	int parcours = paramk;
	retour lastSprint, currentSprint;
	lastSprint.k = paramk;
	lastSprint.l = paramk;
	lastSprint.somme = T[paramk];
	
	currentSprint.k = paramk;
	currentSprint.l = paramk;
	currentSprint.somme = T[paramk];
	
	parcours ++;
	if(DEBUG==true){printf("Avant d'entrer dans la boucle parcours vaut %d:\n lastSprint k:%d l:%d somme:%d\n currentSprint k:%d l:%d somme:%d\n", parcours, lastSprint.k, lastSprint.l, lastSprint.somme, currentSprint.k, currentSprint.l, currentSprint.somme);}
	while (parcours <= paraml) {
		if(DEBUG==true){printf("Debut grande boucle parcours vaut %d:\n lastSprint k:%d l:%d somme:%d\n currentSprint k:%d l:%d somme:%d\n", parcours, lastSprint.k, lastSprint.l, lastSprint.somme, currentSprint.k, currentSprint.l, currentSprint.somme);}
	
		while (parcours <= paraml && T[parcours] < currentSprint.somme  + T[parcours]) {
			if(DEBUG == true){printf(" >Debut PETITE boucle parcours vaut %d:\n lastSprint k:%d l:%d somme:%d\n currentSprint k:%d l:%d somme:%d\n", parcours, lastSprint.k, lastSprint.l, lastSprint.somme, currentSprint.k, currentSprint.l, currentSprint.somme);}
	
			if (T[parcours] < 0 && lastSprint.somme < currentSprint.somme) {
				lastSprint.k = currentSprint.k;
				lastSprint.l = currentSprint.l;
				lastSprint.somme = currentSprint.somme;
			}
			
			currentSprint.l = parcours;
			currentSprint.somme = currentSprint.somme + T[parcours];
			parcours ++;
		}
		if(DEBUG==true){printf("<Sortie Petite boucle> car parcours %d <= paraml %d OU T[parcours] %d < (current.somme %d + T[parcours] %d) %d\n", parcours, paraml, T[parcours], currentSprint.somme, T[parcours], currentSprint.somme+T[parcours]);}
		if (lastSprint.somme < currentSprint.somme) {
			lastSprint.k = currentSprint.k;
			lastSprint.l = currentSprint.l;
			lastSprint.somme = currentSprint.somme;
		}
		if (currentSprint.somme < T[parcours]) {
			currentSprint.k = parcours;
			currentSprint.l = parcours;
			currentSprint.somme = T[parcours];
		}
		parcours ++;
	}
	monRetour->k = lastSprint.k;
	monRetour->l = lastSprint.l;
	monRetour->somme = lastSprint.somme;

	if (verb == true) {
		printRetour(monRetour);
	}
}

void moitie (retour * monRetour, int * T, int paramk, int paraml, bool verb) {
	bool subverb = verb;
	if (paramk == paraml) {
		monRetour->k = paramk;
		monRetour->l = paraml;
		monRetour->somme = T[paramk];
	} else {
		int mid = (int) ((paramk + paraml)/2);
		retour retourGauche;
		moitie(&retourGauche, T, paramk, mid, subverb);
		retour retourDroit;
		moitie(&retourDroit, T, mid + 1, paraml, subverb);
		retour retourMid;
		milieu(&retourMid, T, paramk, mid, paraml, subverb);
		
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
		printf("Moitié ");
		printRetour(monRetour);
	}
}

void milieu (retour * monRetour, int * T, int paramk, int mid, int paraml, bool verb) {
	int sommeg = T[mid];
	int somme = 0;
	int kmax = mid;
	int lmax = mid;
	int i, j;
	for (i = mid; i >= paramk; i--) {
		somme = somme + T[i];
		if (somme > sommeg) {
			kmax = i;
			sommeg = somme;
		}
	}
	if(DEBUG == true){printf("sommeg: %d\n", sommeg);}
	
	int sommed = T[mid];
	somme = 0;
	for (j = mid; j <= paraml; j++) {
		somme = somme + T[j];
		if (somme > sommed) {
				lmax = j;
				sommed = somme;
		}
	}
	if(DEBUG == true){printf("sommed: %d\n", sommed);}
	
	monRetour->k = kmax;
	monRetour->l = lmax;
	monRetour->somme = sommeg + sommed - T[mid];
	if (verb == true) {
		printf("Milieu ");
		printRetour(monRetour);
	}
}
