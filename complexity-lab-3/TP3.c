#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Affiche(int T[],int N)
{
	int i=0;
	printf("[");
	for(i=0;i<N-1;i++)
		printf("%d,",T[i]);
	printf("%d]\n",T[N-1]);
}


int **ProduitMatriciel(int **A,int **B,int n,int m,int p)
{
	int i,j,k;
	int **C =(int **)malloc(n*sizeof(int *));
	
	for(i=0;i<n;i++)
	{	*(C+i)=(int *)malloc(p*sizeof(int));
		for(j=0;j<p;j++)
			{
				C[i][j]=0;
				for(k=0;k<m;k++)
					C[i][j]= C[i][j] + A[i][k]*B[k][j];	
			}
		
	}
	return C;
}
//T(N) = O(n*p*m) / O(n^3)
//S(n,m,p) = Mem(A)+Mem(B)+Mem(C)+Mem(i)+Mem(j)+Mem(k)

int sousMat1(int **A,int na,int ma,int **B,int nb,int mb)
{
	int i,j,k,l;
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

int rechElets_TabNonTries(int *T,int N , int x)
{
	int i;
	
	for(i=0;i<N;i++)
		if(T[i]==x) return i;
		
	return -1;
}

int sousMat2(int **A,int na,int ma,int **B,int nb,int mb)
{
	int i,j,k,l;
	for(i=0;i+(nb-1)<na;i++)
	{	
		if(B[0][0]>=A[i][0] && B[0][mb-1]<=A[i][ma-1])
		{
			Affiche(*(A+i),100);
			j = rechElets_TabNonTries(*(A+i),ma,B[0][0]);
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


void AfficherMatrice(int **M,int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			printf("%d\t",M[i][j]);
		printf("\n");	
	}	
}

int **MatrixToPointer(int *M,int rows ,int cols)
{
	int i,j,**R=(int **)malloc(rows*sizeof(int *));
	for (i = 0; i < rows; i++) {
		*(R+i)=(int *)malloc(cols*sizeof(int ));
    	for (j = 0; j < cols; j++) {
      		R[i][j]= *(M + i * cols + j);
    }
	}
    return R;
}


//Matrice Tri� Ordre d�croissant
int *PireCas(int n)
{
	int i,j,*T=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++) 
	{
		
		T[i]=n-i;	
	}
	return T;
}
//Matrice Tri� Ordre quelconque 
int *MoyenCas(int n)
{
	
	int i,*T=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++) {srand ( time(NULL) );
	T[i]= rand() % (n+1);}
	return T;
}

//Matrice Tri� Ordre Croissant
int *MeilleurCas(int n)
{
	int i,*T=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++) T[i]=i;
	return T;
}
double **Calcul_des_Temps(double **tab , int algorithme)
{
		int j,position,min,max;
		for(j=0 ; j<12 ; j++)
		{
			clock_t begin = clock();
			switch(algorithme) 
			{
				case 1: position = rechElets_TabNonTries(PireCas(tab[0][j]),tab[0][j],-1); break;
				case 2: position = rechElets_TabNTries(MeilleurCas(tab[0][j]),tab[0][j],-1); break;
				case 3: position = rechElets_Dicho(MeilleurCas(tab[0][j]),tab[0][j],-1); break;
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
	int i ;
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

void Afficher_Tableau_de_Valeurs(double **tab,int minmax)
{
	int j;
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


