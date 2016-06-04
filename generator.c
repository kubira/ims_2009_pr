#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include "generator.h"

main(){
/*
*	Funkce s vypsanim jednotlivych testu
*/
  FILE *fd;  // Ukazatel souboru
  int pocetExp = 1000;	// Pocet vzorku
  int i;  // Promenna pro cyklus

  if((fd = fopen("data.dat", "w")) == NULL) {  // Chyba otevreni souboru
    fprintf(stderr, "Nelze otevrit soubor!\n");
    return 0;
  }

  fprintf(fd, "Rovnomerne rozlozeni na intervalu <2,3>:\n");
  for(i = 0; i < pocetExp; i++){
    fprintf(fd, "%lf\n", myRandoms(2,3));
  }

  fprintf(fd, "Exponencialni rozlozeni s lambdou 1 a gamou 3:\n");

  for(i = 0; i < pocetExp; i++){
    fprintf(fd, "%lf\n", myExpo(1.0,3.0));
  }

  fprintf(fd, "Normalni rozlozeni se stredni hodnotou 3 odchylkou 1:\n");

  for(i = 0; i < pocetExp; i++){
    fprintf(fd, "%lf\n", myNormal(3,1));
  }

  fprintf(fd, "Rayleighovo rozlozeni se sigmou 3:\n");

  for(i = 0; i < pocetExp; i++){
    fprintf(fd, "%lf\n", myRayleigh(3.0));
  }

  fprintf(fd, "Obecne Paretovo rozlozeni s my 0, sigmou 3 a ksi 2:\n");

  for(i = 0; i < pocetExp; i++){
    fprintf(fd, "%lf\n", myPareto(0.0, 3.0, 2.0));
  }

  fprintf(fd,"Poissonovo rozlozeni s lambdou 3:\n");

  for(i = 0; i < pocetExp; i++){
    fprintf(fd, "%d\n", myPoisson(3.0));
  }

  return EXIT_SUCCESS;
}