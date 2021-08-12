#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

long **ProduitMatriciel(long **A,long **B,long n,long m,long p)
{
	long i,j,k;
	long **C =(long **)malloc(n*sizeof(long *));
	
	for(i=0;i<n;i++)
	{	*(C+i)=(long *)malloc(p*sizeof(long));
		for(j=0;j<p;j++)
			{
				C[i][j]=0;
				for(k=0;k<m;k++){C[i][j]= C[i][j] + A[i][k]*B[k][j];	
				}
					
			}
		
	}
	return C;
}
//T(N) = O(n*p*m) / O(n^3)
//S(n,m,p) = Mem(A)+Mem(B)+Mem(C)+Mem(i)+Mem(j)+Mem(k)

long sousMat1(long **A,long na,long ma,long **B,long nb,long mb)
{
	long i,j,k,l;
	for(i=0;i+(nb-1)<na;i++)
	{
		for(j=0;j+(mb-1)<ma;j++)
		{  
			if(B[0][0] == A[i][j])
			{ 
				for(k=0;k<nb;k++)
					for(l=0;l<mb;l++)
					{
				    	if(B[k][l]!=A[i+k][j+l]) 
						{
							/*sortie des 2 boucles*/k=nb; break;
						}
						else if(k== nb-1 && l== mb-1 ) return 1;
					}
			}
		}
	}
	return 0;
}

long sousMat2(long **A,long na,long ma,long **B,long nb,long mb)
{
	long i,j,k,l;
	for(i=0;i+(nb-1)<na;i++)
	{	
		if(B[0][0]>=A[i][0] && B[0][mb-1]<=A[i][ma-1])
		{
			j = rechElets_Dicho(*(A+i),ma,B[0][0]);
			if(j>=0)
			{
				for(k=0;k<nb;k++)
					for(l=0;l<mb;l++)
					{
					  	if(B[k][l]!=A[i+k][j+l]) 
						{
							/*sortie des 2 boucles*/k=nb; break;
						}
						else if(k== nb-1 && l== mb-1 ) return j;
					}
			}	
		}	
	}
	return 0;	
}


void AfficherMatrice(long **M,long n,long m)
{
	long i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			printf("%d\t",M[i][j]);
		printf("\n");	
	}	
}

long **MatrixToPolonger(long *M,long rows ,long cols)
{
	long i,j,**R=(long **)malloc(rows*sizeof(long *));
	for (i = 0; i < rows; i++) {
		*(R+i)=(long *)malloc(cols*sizeof(long ));
    	for (j = 0; j < cols; j++) {
      		R[i][j]= *(M + i * cols + j);
    }
	}
    return R;
}


//Matrice Triï¿½ Ordre dï¿½croissant
long **PireCas(long n)
{
	long num=n*n;
	long i,j,**T=(long **)malloc(n*sizeof(long *));
	for(i=0;i<n;i++) 
	{
		T[i] = (long *)malloc(n*sizeof(long ));
		for(j=0;j<n;j++)
		{T[i][j]=num; num =num-1;}		
	}
	return T;
}


//Matrice Triï¿½ Ordre Croissant
long **MeilleurCas(long n)
{
	long num=1;
	long i,j,**T=(long **)malloc(n*sizeof(long *));
	for(i=0;i<n;i++) 
	{
		T[i] = (long *)malloc(n*sizeof(long ));
		for(j=0;j<n;j++)
		{T[i][j]=num; num++;}		
	}
	return T;
}

double **Calcul_des_Temps(double **tab , long algorithme)
{
		long j,verdict,**M;
		for(j=0 ; j<12 ; j++)
		{
			clock_t begin = clock();
			switch(algorithme) 
			{
				case 1:  ProduitMatriciel(PireCas(tab[0][j]),MeilleurCas(tab[0][j]),tab[0][j],tab[0][j],tab[0][j]); break;
				case 2:  verdict = sousMat1(PireCas(tab[0][j]),tab[0][j],tab[0][j],MeilleurCas(1),1,1); break;
				case 3:  M = MeilleurCas(1) ; M[0][0]=(long) (tab[0][j]*(tab[0][j] - 1) +tab[0][j]/2) ;
						 verdict = sousMat2(MeilleurCas(tab[0][j]),tab[0][j],tab[0][j],M,1,1); break;
			}
			clock_t end = clock();
			tab[1][j] = (double)(end - begin) / CLOCKS_PER_SEC;	
			tab[2][j] = verdict;

		}
		return tab;
}

double **Tableau_de_ValeursPoduit(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(4*sizeof(double *));
	for(i=0 ; i<4 ; i++) tab[i] = (double *)malloc(10*sizeof(double));
	tab[0][0]=10;
	tab[0][1]=15;
	tab[0][2]=20;
	tab[0][3]=25;
	tab[0][4]=30;
	tab[0][5]=35;
	tab[0][6]=40;
	tab[0][7]=45;
	tab[0][8]=50;
	tab[0][9]=55;
	for(i=0 ; i<10 ; i++)tab[1][i] = 0 ;
	return tab;
}

double **Tableau_de_ValeursSousMat(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(4*sizeof(double *));
	for(i=0 ; i<4 ; i++) tab[i] = (double *)malloc(10*sizeof(double));
	tab[0][0]=500;
	tab[0][1]=1000;
	tab[0][2]=2000;
	tab[0][3]=3000;
	tab[0][4]=4000;
	tab[0][5]=5000;
	tab[0][6]=6000;
	tab[0][7]=7000;
	tab[0][8]=8000;
	tab[0][9]=9000;
	for(i=0 ; i<10 ; i++)tab[1][i] = 0 ;
	return tab;
}
void Afficher_Tableau_de_Valeurs(double **tab)
{
	long j,verdict;
		for(j=0 ; j<10 ; j++)
		{
			verdict = (int)tab[2][j];
			if(verdict) printf("N = %f \t T= %f \t , B est sous-Matrice de A  \n",tab[0][j],tab[1][j]);
			else printf("N = %f \t T= %f \t , B n'est pas sous-Matrice de A  \n",tab[0][j],tab[1][j]);	
		}
}


int main(int argc, char *argv[]) 
{ 


	//printf("Execution de ProduitMatriciel :\n");
	//Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs(),1));
	
	printf("Execution de sousMat1 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_ValeursSousMat(),2));
	
	printf("Execution de sousMat2 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_ValeursSousMat(),3));
	
/*	int a[5][4] ={
            {0 ,1 ,2 ,3 },
            {4 ,5 ,6 ,7 },
            {8 ,9 ,10,11},
            {12,13,14,15},
            {16,17,18,19}
            },
		b[2][2]={
				{9 ,10},
            	{13,14}
			 	};
	int **A=MatrixToPointer(&a[0][0],5,4),
		**B=MatrixToPointer(&b[0][0],2,2);
			printf("A = \n");
	AfficherMatrice(A,5,4);
	printf("B = \n");
	AfficherMatrice(B,2,2);
	printf("Resultat = %d",sousMat2(A,5,4,B,2,2));
*/

/*
	int Mat1[2][3] = {{1,2,0},{4,3,-1}},Mat2[3][2] = {{5,1},{2,3},{3,4}};

	int **A=MatrixToPointer(&Mat2[0][0],3,2),
		**B=MatrixToPointer(&Mat1[0][0],2,3);
	printf("A = \n");
	AfficherMatrice(A,3,2);
	printf("B = \n");
	AfficherMatrice(B,2,3);
	printf("C = \n");
	AfficherMatrice(ProduitMatriciel(A,B,3,2,3),3,3);
*/	
	getchar();
	return 0;
}

