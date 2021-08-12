#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int Algorithme1(int N)
{	
    int i;
    for(i=2 ; i<= N-1 ; i++)
    {
        if(N%i == 0) return 0;
    }
    return 1;
}


int Algorithme2(int N)
{
    int i;
    for(i=2 ; i<= N/2 ; i++)
    {
        if(N%i == 0) return 0;
    }
    return 1;
} 


int Algorithme3(int N)
{
	int i=2;
    while(i<= sqrt(N))
    {
        if(N%i == 0) return 0;
	   i++;
    }
    return 1;
}


int Algorithme4(int N)
{
    int i;
    if(N%2 == 0)  return 0;
    i=3;
    while(i<= sqrt(N))
    {
        if(N%i == 0) return 0;
        i=i+2;
    }
    return 1;
}



double **Calcul_des_Temps(double **tab , int algorithme)
{
		int j,premier;
		for(j=0 ; j<12 ; j++)
		{
			clock_t begin = clock();
			switch(algorithme) 
			{
				case 1: premier = Algorithme1(tab[0][j]); break;
				case 2: premier = Algorithme2(tab[0][j]); break;
				case 3: premier = Algorithme3(tab[0][j]); break;
				case 4: premier = Algorithme4(tab[0][j]); break;
			}
			clock_t end = clock();
			tab[1][j] = (double)(end - begin) / CLOCKS_PER_SEC;	
			tab[2][j] = premier;
		}
		return tab;
}

double **Tableau_de_Valeurs(void)
{
	int i ;
	double **tab;
	tab = (double **)malloc(3*sizeof(double *));
	for(i=0 ; i<3 ; i++) tab[i] = (double *)malloc(12*sizeof(double));
	tab[0][0]=1000003;
	tab[0][1]=2000003;
	tab[0][2]=4000037;
	tab[0][3]=8000009;
	tab[0][4]=16000057;
	tab[0][5]=32000011;
	tab[0][6]=64000031;
	tab[0][7]=128000003;
	tab[0][8]=256000001;
	tab[0][9]=512000009;
	tab[0][10]=1024000009;
	tab[0][11]=2048000011;
	for(i=0 ; i<12 ; i++)tab[1][i] = 0 ;
	return tab;
}

void Afficher_Tableau_de_Valeurs(double **tab)
{
	int j;
		for(j=0 ; j<12 ; j++)
		{
			printf("N = %f \t T= %f \t ,premier= %d \n",tab[0][j],tab[1][j],(int)tab[2][j]);	
		}
}
int main(int argc, char *argv[]) 
{
	printf("Execution de l'Algorithme 1 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),1));
	
	printf("Execution de l'Algorithme 2 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),2));

	printf("Execution de l'Algorithme 3 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),3));

	printf("Execution de l'Algorithme 4 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),4));
		
	
	getchar();
	return 0;
}

