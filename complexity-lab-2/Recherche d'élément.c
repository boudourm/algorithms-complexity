#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Affiche(long T[],long N)
{
	long i=0;
	printf("[");
	for(i=0;i<N-1;i++)
		printf("%d,",T[i]);
	printf("%d]\n",T[N-1]);
}

long rechElets_TabNonTries(long *T,long N , long x)
{
	long i;
	
	for(i=0;i<N;i++)
		if(T[i]==x) return i;
		
	return -1;
}
// Best : T(N) =  1 , Worst = T(N) = N
long rechElets_TabNTries(long *T,long N , long x)
{
	long i;
	
	for(i=0;i<N;i++)
		if(T[i]==x) return i;
		else if(T[i]>x) return -1;
		
	return -1;
}
// Best : T(N) =  1 , Worst = T(N) = N
long rechElets_Dicho(long *T,long N , long x)
{
	if(T[0]==x) return 0;
	else if(T[N-1]==x) return N-1;
		else if(x<T[0] || x>T[N-1]) return -1;
	
	long d=1,f=N-1,m;
		
	for(;d<f;m=(d+f)/2)
	{
		if(T[m]==x) return m;
		else 
			if(x<T[m]) f=m;
			else d=m;
	}	
	return -1;
}
//T(N) = O(log(N) 

void MinMaxA(long *T,long n,long *min,long*max)
{
	long i; *min=T[0]; *max=T[0];
	for(i=1;i<n;i++)
	{
		if(T[i]<*min) *min=T[i];
		else
			if(T[i]>*max) *max=T[i];
	}	
}

//Tableau Trié Ordre décroissant
long *PireCas(long n)
{
	long i,*T=(long *)malloc(n*sizeof(long));
	for(i=0;i<n;i++) T[i]=n-i;
	return T;
}
//Tableau Trié Ordre quelconque 
long *MoyenCas(long n)
{
	
	long i,*T=(long *)malloc(n*sizeof(long));
	for(i=0;i<n;i++) {srand ( time(NULL) );
	T[i]= rand() % (n+1);}
	return T;
}

//Tableau Trié Ordre Croissant
long *MeilleurCas(long n)
{
	long i,*T=(long *)malloc(n*sizeof(long));
	for(i=0;i<n;i++) T[i]=i;
	return T;
}
double **Calcul_des_Temps(double **tab , long algorithme)
{
		long j,position,min,max;
		for(j=0 ; j<12 ; j++)
		{
			clock_t begin = clock();
			switch(algorithme) 
			{
				case 1: position = rechElets_TabNonTries(PireCas(tab[0][j]),tab[0][j],-1); break;
				case 2: position = rechElets_TabNTries(MeilleurCas(tab[0][j]),tab[0][j],-1); break;
				case 3: position = rechElets_Dicho(MeilleurCas(tab[0][j]),tab[0][j],-1); break;
				case 4: MinMaxA(PireCas(tab[0][j]),tab[0][j],&min,&max);break;
			}
			clock_t end = clock();
			tab[1][j] = (double)(end - begin) / CLOCKS_PER_SEC;	
			if(algorithme==4)
			{tab[2][j]=min;tab[3][j]=max;}
			else tab[2][j] = position;
			min=0;max=0;
		}
		return tab;
}

double **Tableau_de_Valeurs(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(4*sizeof(double *));
	for(i=0 ; i<4 ; i++) tab[i] = (double *)malloc(10*sizeof(double));
	tab[0][0]=100000;
	tab[0][1]=200000;
	tab[0][2]=400000;
	tab[0][3]=600000;
	tab[0][4]=800000;
	tab[0][5]=1000000;
	tab[0][6]=1200000;
	tab[0][7]=1400000;
	tab[0][8]=1600000;
	tab[0][9]=1800000;
	for(i=0 ; i<10 ; i++)tab[1][i] = 0 ;
	return tab;
}

void Afficher_Tableau_de_Valeurs(double **tab,long minmax)
{
	long j;
		if(!minmax)
		for(j=0 ; j<10 ; j++)
		{
			printf("N = %f \t T= %f \t ,position= %d \n",tab[0][j],tab[1][j],(int)tab[2][j]);	
		}
		else
		for(j=0 ; j<10 ; j++)
		{
			printf("N = %f \t T= %f \t ,min= %d,max=%d \n",tab[0][j],tab[1][j],(int)tab[2][j],(int)tab[3][j]);	
		}
}

int main(int argc, char *argv[]) 
{ 
	printf("Execution de rechElets_TabNonTries :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),1),0);
	printf("Execution de rechElets_TabNTries :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),2),0);
	printf("Execution de rechElets_Dicho:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),3),0);
	printf("Execution de MinMaxA:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),4),1);
	getchar();
	return 0;
}

