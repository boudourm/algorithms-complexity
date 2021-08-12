#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Permuter(long *x , long *y)
{
	long temp = *x;
	*x=*y;
	*y=temp;	
}

//TriBulle
void TriBulle(long *T , long n)
{
	//Boolean
	long changement = 1;
	while(changement)
	{
		changement = 0;
		long i=0;
		for(i=0;i<n-1;i++)
		{
			if(T[i]>T[i+1])
			{
				Permuter(T+i,T+(i+1));
				changement = 1;
			}	
		}
	}
}

//TriBulleOpt
void TriBulleOpt(long *T , long n)
{
	long m = n-1;
	long changement = 1;
	while(changement)
	{
		changement = 0;
		long i=0;
		for(i=0;i<m;i++)
		{
			if(T[i]>T[i+1])
			{
				Permuter(T+i,T+(i+1));
				changement = 1;
			}	
		}
		m=m-1;
	}
}

//TriGnomme
void TriGnomme(long *T,long n)
{
	long i= 0;
	while(i<n-1)
	{
		if(T[i]>T[i+1])
		{
			Permuter(T+i,T+(i+1));
			if(i==0) i++;
			else i--;
		}
		else
			i++;	
	}
}

//TriDistribution
//cl�
long cle(long X,long i) // O(i + 2*X)
{
	long dec1 =(long) pow(10,i);
	long dec2 = dec1*10;
	return (X%(dec2) - X%(dec1))/dec1;
}
//TriAux
long *TriAux(long *T,long n,long i)// 
{
	long k,j,*Tab=(long *)malloc(n*sizeof(long)),h=0;
	for(k=0;k<=9;k++)
		for(j=0;j<n;j++)
			if(cle(T[j],i)==k)// O(i + 2*T[j]) +2
			{
				Tab[h]=T[j];
				h++;
			}
	return Tab;
}
//TriBase
long *TriBase(long  *T,long n , long k)
{
	long i;
	for(i=0;i<=k;i++)
		T=TriAux(T,n,i);
	return T;
}

//Quick Sort
//partitionner
long partitionner(long *T,long d,long f)
{
	long i,j;
	long eltPivot = T[d];
	i=d;  j=f;
	do
	{
		while(T[i]<=eltPivot && i<=j) {i++;}
		while(T[j]>eltPivot && i<=j)  {j--;}
		if(i<=j){Permuter(T+i,T+j);}
	}
	while(i<=j);
	Permuter(T+d,T+j);
	return j;	
}
//TriRapide
void TriRapide(long *T,long p, long r)
{
	long q;
	if(p<r)
	{
		q=partitionner(T,p,r);
		TriRapide(T,p,q-1);
		TriRapide(T,q+1,r);
	}
}


//TriparTas
long max (long *a, long n, long i, long j, long k) {
    long m = i;
    if (j < n && a[j] > a[m]) {
        m = j;
    }
    if (k < n && a[k] > a[m]) {
        m = k;
    }
    return m;
}

void downheap (long *a, long n, long i) {
    while (1) {
        long j = max(a, n, i, 2 * i + 1, 2 * i + 2);
        if (j == i) {
            break;
        }
        long t = a[i];
        a[i] = a[j];
        a[j] = t;
        i = j;
    }
}

void heapsort (long *a, long n) {
    long i;
    for (i = (n - 2) / 2; i >= 0; i--) {
        downheap(a, n, i);
    }
    for (i = 0; i < n; i++) {
        long t = a[n - i - 1];
        a[n - i - 1] = a[0];
        a[0] = t;
        downheap(a, n - i - 1, 0);
    }
}

void Affiche(long T[],long N)
{
	long i=0;
	printf("[");
	for(i=0;i<N-1;i++)
		printf("%d,",T[i]);
	printf("%d]\n",T[N-1]);
}

long Max(long *T,long n)
{
	long i,max=T[0];
	for(i=1;i<n;i++)
		if(T[i]>max) max=T[i];
	return max;
}


//Tableau Tri� Ordre d�croissant
long *PireCas(long n)
{
	long i,*T=(long *)malloc(n*sizeof(long));
	for(i=0;i<n;i++) T[i]=n-i;
	return T;
}
//Tableau Tri� Ordre Croissant
long *MeilleurCas(long n)
{
	long i,*T=(long *)malloc(n*sizeof(long));
	for(i=0;i<n;i++) T[i]=i;
	return T;
}


double **Calcul_des_Temps(double **tab , long algorithme)
{
		long j,position,min,max;
		for(j=0 ; j<10 ; j++)
		{
			long k;
			long *TAB = PireCas(tab[0][j]);
			if(algorithme==4){
			k = (long)log10((double)Max(TAB,tab[0][j]));
			printf("k = %d \n",k);} 
			clock_t begin = clock();
			switch(algorithme) 
			{
				case 1: TriBulle(TAB,tab[0][j]); break;
				case 2: TriBulleOpt(TAB,tab[0][j]); break;
				case 3: TriGnomme(TAB,tab[0][j]); break;
				case 4: TAB = TriBase(TAB,tab[0][j],k); break;
				case 5: TriRapide(TAB,0,tab[0][j]-1); break;
				case 6: heapsort(TAB,tab[0][j]); break;
			}
			clock_t end = clock();
			tab[1][j] = (double)(end - begin) / CLOCKS_PER_SEC;	
		}
		return tab;
}

double **Tableau_de_Valeurs(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(4*sizeof(double *));
	for(i=0 ; i<4 ; i++) tab[i] = (double *)malloc(10*sizeof(double));
	tab[0][0]=5*100;
	tab[0][1]=4000;
	tab[0][2]=8000;
	tab[0][3]=10000;
	tab[0][4]=18000;
	tab[0][5]=25000;
	tab[0][6]=36000;
	tab[0][7]=48000;
	tab[0][8]=56000;
	tab[0][9]=64000;
	for(i=0 ; i<10 ; i++)tab[1][i] = 0 ;
	return tab;
}

void Afficher_Tableau_de_Valeurs(double **tab)
{
	long j;
		for(j=0 ; j<10 ; j++)
		{
			printf("N = %f \t T= %f \t \n",tab[0][j],tab[1][j]);	
		}
}


long main(long argc, char *argv[]) 
{



  /*	printf("Execution de TriBulle :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),1));
	printf("Execution de TriBulleOpt :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),2));
	printf("Execution de TriGnomme:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),3));
*/	printf("Execution de TriBase:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),4));
/*	printf("Execution de TriRapide:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),5));
	printf("Execution de heapsort:\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),6));
*/
/*
	long i;
long *T = PireCas(10);

printf("TriBulle : \n");
Affiche(T,10);
TriBulle(T,10);
printf("=> Traitement ...");
getchar();
Affiche(T,10);
printf("\n--------------------------------------------------------\n");


T = PireCas(10);
getchar();
printf("TriBulleOpt : \n");
Affiche(T,10);
TriBulleOpt(T,10);
printf("=> Traitement ...");
getchar();
Affiche(T,10);
printf("\n--------------------------------------------------------\n");


T = PireCas(10);
getchar();
printf("TriGnome : \n");
Affiche(T,10);
TriGnomme(T,10);
printf("=> Traitement ...");
getchar();
Affiche(T,10);
printf("\n--------------------------------------------------------\n");



T = PireCas(100);
getchar();
printf("TriBase : \n");
Affiche(T,100);
T=TriBase(T,100,2	);
printf("=> Traitement ...");
getchar();
Affiche(T,100);
printf("\n--------------------------------------------------------\n");


T = PireCas(10);
getchar();
printf("QuickSort : \n");
Affiche(T,10);
TriRapide(T,0,9);
printf("=> Traitement ...");
getchar();
Affiche(T,10);
printf("\n--------------------------------------------------------\n");

T = PireCas(10);
getchar();
printf("Tri par Tas : \n");
Affiche(T,10);
heapsort(T,10);
printf("=> Traitement ...");
getchar();
Affiche(T,10);

//Affiche(T,50000);
//TriRapide(T,0,39999);
//printf("\n\n\n----------------------------------------------------------------\n\n\n");
//Affiche(T,50000);
/*	for(i=5 ; i<6 ; i++)
	{	
		long *T = PireCas(50000);	
		printf("Temps d'Execution de l'Algo %d = %lf .\n",i,Temps_Execution(T,50000,i));

	}
*/	

//	printf("cle(143,2) = %d",cle(143,1));
	/*	printf("Execution de l'Algorithme 1 :\n");
		Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),1));*/
	
	return 0;
}
