/*
*	Knihovna pro generovani pseudonahodnych cisel
*	podle rozlozeni:
*		a. rovnomerne
*		b. exponencialni
*		c. normalni
*		d. Rayleighovo
*		e. Obecne Paretovo
*		f. Poissonovo
*	Vytvorili: Petr Kuncar (xkunca04), Radim Kubis (xkubis03)
*	v ramci projektu do predmetu IMS (Modelovani a simulace)
*/

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

const double IMS_PI = 3.14159265358979323846;  // PI - Ludolfovo cislo
const double IMS_E  = 2.71828182845904523536;  // e - Eulerovo cislo

static unsigned ix = 0;  // Promenna pro seminko a dalsi vypocty

double myRandom(void){
/*
*	Rovnomerne rozlozeni
*	x = (ax + b) / m
*	a = 69069
*	b = 1
*	m = 2 na 32
*/

  double ret = 0;  // Promenna pro mezivypocet
  unsigned long a = 69069L;  // Inicializase parametru a
  double b = 1;  // Inicializace parametru b
  
  ix = time(0)+clock()+ix;  // Inicializuji seminko
    
  ret = (a * ix + b);  // Vypocet nahodneho cisla, ktery jeste vydelim m

  return (ret / ((double)ULONG_MAX + 1));  // m = 4294967295 + 1
}

double myRandoms(double a, double b){
/*
*	Rovnomerne rozlozeni v urcitem intervalu
*	a - od hodnoty
*	b - do hodnoty
*/

  if(a > b) {  // Pokud je dolni hranice vetsi nez horni hranice
	  fprintf(stderr, "myRandoms: Parametr a je vetsi nez parametr b!\n");
	  return 0;  // Chyba
	}

  return  a + (b - a) * myRandom();  // Vracim vysledek vypoctu
}

double myExpo(double lambda, double gama){
/*
*	Exponencialni rozlozeni
*	lambda - zkoseni
*	gama - posun
*	
*/

  double ret = 0;  // Promenna pro vysledek

  if(lambda <= 0) {  // Pokud je lambda mensi nebo rovna nule
    fprintf(stderr, "myExpo: Parametr lambda musi byt vetsi nez nula!\n");
	  return 0;  // Chyba
  }

  ret = gama - lambda * log(1 - myRandom());  // Vypocet vysledku

  return ret;  // Vracim vysledek vypoctu
}

double myNormal(double str_hod, double odchylka){
/*
*	Normalni rozlozeni
*	str_hod - median
*	odchylka - smerodatna odchylka
*/

  double x, y;  // Promenne pro vygenerovane hodnoty
  
  if(str_hod <= 0) {  // Pokud je median mensi nebo roven nule
    fprintf(stderr, "myNormal: Parametr str_hod musi byt vetsi nez nula!\n");
	  return 0;  // Chyba
  }

  while(1){
    // Pravidlo tri sigma
    x = myRandoms((str_hod - 3 * odchylka), (str_hod + 3 * odchylka));
    y = myRandom();
    
    // Vzorec hustoty
    double y_hustota = (1 / (odchylka * sqrt(2 * IMS_PI))) * pow(IMS_E, - ((pow((x - str_hod), 2)) / (2 * pow(odchylka, 2))));
    
    if(y <= y_hustota)  // Kdyz je y vetsi nez hustota
      return x;  // Vracim x jako vysledek
  }
}

double myNormal2(double odchylka, double str_hod){
/*
*	Normalni rozdeleni - ridici se centralni limitni vetou
*	str_hod - median
*	odchylka - smerodatna odchylka
*/

  int i;  // Promenna pro cyklus
  double x = 0;  // Promenna pro mezivysledek
  
  if(str_hod <= 0) {  // Pokud je median mensi nebo roven nule
    fprintf(stderr, "myNormal2: Parametr str_hod musi byt vetsi nez nula!\n");
	  return 0;  // Chyba
  }

  for(i = 0; i < 12; i++)  // Cyklus pro soucet 12ti nahodnych cisel
	  x += myRandom();  // Pricitani

  return ((x - 6) * odchylka + str_hod);  // Vracim vysledek vypoctu
}


double myRayleigh(double sigma) {
/*
* Rayleighovo rozlozeni
* 
* sigma - modul rozlozeni
*/

	double X = 0;  // Promenna pro vysledek vypoctu
	
	if(sigma <= 0) {  // Pokud je sigma mensi nebo rovna nule
	  fprintf(stderr, "myRayleigh: Parametr sigma musi byt vetsi nez nula!\n");
	  return 0;  // Chyba
	}

	X = sigma * sqrt(- 2 * log(1 - myRandom()));  // Vypocet

	return X;  // Vracim vysledek vypoctu
}

double myPareto(double my, double sigma, double ksi) {
/*
* Obecne Paretovo rozlozeni
* my - dolni hranice generovanych cisel
* sigma - meritko rozlozeni
* ksi
*/

	double X = 0;  // Promenna pro vysledek vypoctu
	
	if(sigma <= 0) {  // Pokud je sigma mensi nebo rovna nule
	  fprintf(stderr, "myPareto: Parametr sigma musi byt vetsi nez nula!\n");
	  return 0;  // Chyba
	}

	X = my + ((sigma * (pow(myRandom(), (- 1 * ksi)) - 1)) / ksi);  // Vypocet
	
	return X;  // Vracim vysledek vypoctu
}

int myPoisson(double lambda) {
/*
* Poissonovo rozlozeni
* lambda - bod maxima
*/

  int k = 0;  // Vysledne cislo rozlozeni
  const int max_k = 1000;  // Maximalni pocet opakovani cyklu
  double p = myRandom();  // Vygenerovane nahodne cislo
  double P;  // Pravdepodobnost
  double sum;  // Promenna pro soucet pravdepodobnosti
  
  if(lambda <= 0) {  // Pokud je lambda mensi nebo rovna nule
	  fprintf(stderr, "myPoisson: Parametr lambda musi byt vetsi nez nula!\n");
	  return 0;  // Chyba
	}
	
	P = exp(-lambda);  // Vypocet pravdepodobnosti
	sum = P;  // Inicializase souctu
 
  if(sum >= p)  // Pokud uz je soucet vetsi nebo roven vygenerovanemu cislu
    return 0;  // Vracim 0
  
  for(k = 1; k < max_k; ++k) {  // Cyklus pro scitani
    P = P * lambda / (double)k;  // Vypocet nove pravdepodobnosti
    sum = sum + P;  // Scitani pravdepodobnosti
    if(sum >= p) // Pokud uz je soucet vetsi nebo roven vygenerovanemu cislu
      break;  // Cyklus konci
  }

  return k;  // Vracim cislo z Poissonova rozlozeni
}
