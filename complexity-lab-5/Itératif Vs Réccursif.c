#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long Fibo_Rec(long n)
{
	if(n==0) return 0;
	else
		if(n==1) return 1;
		else
			if(n>=2)
				return Fibo_Rec(n-1)+Fibo_Rec(n-2);			
}

long Fibo_iter(long n)
{
	if(n==0) return 0;
	else 
		if(n==1) return 1;
	long F1=0,F2=1,F;
	for(; n>=2 ; n--)
	{
		F  = F1 + F2;
		F1 = F2;
		F2 = F; 
	}
	return F;	
}

double Phi(long n)
{
	if(n==0) return 0;
	else 
		if(n==1) return 1;
	double F,F1=0,F2=1;
	for(; n>=2 ; n--)
	{
		F  = F1 + F2;
		F1 = F2;
		F2 = F; 
	}
	return (double) F2/F1;	
}

double **Calcul_des_Temps(double **tab , long algorithme)
{
		long j;
		double resultat;
		for(j=0 ; j<11 ; j++)
		{
			clock_t begin = clock();
			switch(algorithme) 
			{
				case 1: resultat = Fibo_Rec(tab[0][j]); break;
				case 2: resultat = Fibo_iter(tab[0][j]); break;
				case 3: resultat = Phi(tab[0][j]); break;
			}
			clock_t end = clock();
			tab[1][j] = (double)(end - begin) / CLOCKS_PER_SEC;	
			tab[2][j] = resultat;
		}
		return tab;
}


double **Tableau_de_ValeursFibRec(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(3*sizeof(double *));
	for(i=0 ; i<3 ; i++) tab[i] = (double *)malloc(11*sizeof(double));
	tab[0][0]=5;
	tab[0][1]=10;
	tab[0][2]=15;
	tab[0][3]=20;
	tab[0][4]=25;
	tab[0][5]=35;
	tab[0][6]=40;
	tab[0][7]=45;
	tab[0][8]=47;
	tab[0][9]=49;
	tab[0][10]=50;
	for(i=0 ; i<11 ; i++)tab[1][i] = 0 ;
	return tab;
}

double **Tableau_de_ValeursFibIter(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(3*sizeof(double *));
	for(i=0 ; i<3 ; i++) tab[i] = (double *)malloc(11*sizeof(double));
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
	
	for(i=0 ; i<10 ; i++)tab[1][i] = 0 ;
	return tab;
}

void Afficher_Tableau_de_Valeurs(double **tab)
{
	long j;
		for(j=0 ; j<10 ; j++)
		{
			printf("N = %lf \t T= %lf \t ,resultat = %lf \n",tab[0][j],tab[1][j],tab[2][j]);	
		}
}

int main(int argc, char *argv[]) 
{ 
	
	printf("Execution de Fibo_iter :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_ValeursFibIter(),2));

	printf("Execution de Phi:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_ValeursFibIter(),3));

	printf("Execution de Fibo_Rec :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_ValeursFibRec(),1));

	getchar();
	return 0;
}


