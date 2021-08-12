#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Type Matrice
typedef struct Matrice Matrice ;
struct Matrice 
{
	long **Pointer;            
	long n,m;      
};

//Type Instanciation Liste Lin�aire Chain�e
typedef struct Instanciation Instanciation ;
struct Instanciation 
{
	long valeur;            
	Instanciation *suiv;      
};

void Affichage(Instanciation *tete)
{
	Instanciation *P;
	long i;
	if(tete==NULL)
	{
		//printf("LA LISTE EST VIDE !");
	}
	else
	{
		P=tete;
		//printf("[");
		while(P!=NULL)
		{
		//printf("%d,",P->valeur);
			P=P->suiv;
		}
		//printf("end]\n");
	}
}
void Affiche(long T[],long N)
{
	long i=0;
	//printf("[");
	for(i=0;i<N-1;i++)
		//printf("%d,",T[i]);
	//printf("%d]\n",T[N-1]);
	;
}




//Primitives de Manipulation des Instanciations
Instanciation *Ajouter(Instanciation *I,long valeur) //O(4)
{
	Instanciation *P=(Instanciation *)malloc(sizeof(Instanciation ));
	P->valeur=valeur; P->suiv=I;
	return P;
}

//Verifier : V�rifie si une Clause est vrai pour une instance Donn�e
long VerifierClause(long *Clause,long nbLiterraux,long instance) // O(1+nbLiterraux)
{
	//printf("\n\t\tV�rification : Clause = ");Affiche(Clause,nbLiterraux);
	//printf("\n\t\tpour instanciation = %d.",instance);
	
	long j,bit = instance;
	for(j=nbLiterraux-1;j>=0;j--)
	{
		if(Clause[j] == bit%2)
		{
			//printf("\n\t\t\tVRAI pour instanciation = %d.",instance);
			return 1;
		}
		bit=bit/2;
	}
	//printf("\n\t\t\tFAUSSE pour instanciation = %d.",instance);
	return 0;
}

//Solutions :  retournes les instanciations pour lesquelles une Clause est vrai 
//Parmi les instanciations donn�es en param�tre
Instanciation *Solutions(long *Clause,long nbLiterraux ,Instanciation *Instances) // O(m*2^m)
{
	//printf("\n\tRecherche de Solutions: pour Clause = ");Affiche(Clause,nbLiterraux);
	//printf("\n\tparmi les instanciations = "); Affichage(Instances);
	
	long i,bit, j;
	Instanciation *solutions =NULL ,*P,*Q;
	if(Instances==NULL) //Pas d'instances en Entr�e
	{//Tester pour toute la Table de V�rit� 2^m
		long tailleTV = (long)pow(2,nbLiterraux);
		for(i=0 ; i<tailleTV ; i++) //O(2^nbLitterraux * (5+nbLitterraux))
		{
			if(VerifierClause(Clause,nbLiterraux,i))//O(1+nbLiterraux)
			{solutions = Ajouter(solutions,i); }// O(4)
			Affichage(solutions);
		}
				
	}
	else // Instances != NULL il ya des valeurs � Tester
	{	//Parcours de la Liste des instanciations
		for(P=Instances; P != NULL;) //au pire cas O(2^nbLitterraux * (5+nbLitterraux))
		{
			if(VerifierClause(Clause,nbLiterraux,P->valeur)) //O(1+nbLiterraux)
			{	solutions = Ajouter(solutions,P->valeur); }// O(4)
				
			Q=P ; P=P->suiv ; free(Q); //Lib�rer la cellue lu de Instances
		}
	}
	//retourner la Liste des instances pour lesquelle Clause est VRAI
		//printf("\n\tLes Solutions touvees = ");Affichage(solutions);
	return solutions;
}

long Validation1(long **Conjonction ,long nbClauses, long nbLiterraux,long valeur) //O(n*m) - Omega(1)
{
	long i;
	Instanciation *P; P=NULL; 
	Instanciation *instances = Ajouter(P,valeur);
	if(instances==NULL) return 0;
	else
		for(i=1;i<nbClauses;i++) //O(nbClauses*nbLitterraux*2^nbLitterraux)
		{
			instances = Solutions(Conjonction[i],nbLiterraux,instances); //O(nbLitterraux)
			if(instances==NULL) return 0;
		}
	return 1;
}

long Validation2(long **Conjonction ,long nbClauses, long nbLiterraux) //O(n*m*2^m) - Omega(2^m)
{
	long i;
	Instanciation *instances = Solutions(Conjonction[0],nbLiterraux,NULL);
	if(instances==NULL) return 0;
	else
		for(i=1;i<nbClauses;i++) //O(nbClauses*nbLitterraux*2^nbLitterraux)
		{
			instances = Solutions(Conjonction[i],nbLiterraux,instances); //O(nbLitterraux*2^nbLitterraux)
			if(instances==NULL) return 0;
		}
	return 1;
}

Instanciation *Validation3(long **Conjonction ,long nbClauses, long nbLiterraux) //O(n*m*2^m) - Omega(2^m)
{
	long i;
	Instanciation *instances = Solutions(Conjonction[0],nbLiterraux,NULL);
	if(instances==NULL) return NULL;
	else
		for(i=1;i<nbClauses;i++) //O(nbClauses*nbLitterraux*2^nbLitterraux)
		{
			instances = Solutions(Conjonction[i],nbLiterraux,instances); //O(nbLitterraux*2^nbLitterraux)
			if(instances==NULL) return NULL;
		}
			//printf("\nLa Solution Finale = ");Affichage(instances);
	return instances;
}

//Matrice Triï¿½ Ordre dï¿½croissant
long **Conjonction(long n)
{
	long i,j,**T=(long **)malloc(n*sizeof(long *));
	for(i=0;i<n;i++) 
	{
		T[i] = (long *)malloc(n*sizeof(long ));
		for(j=0;j<n;j++)
		{T[i][j]= rand() % 2;}		
	}
	return T;
}

double **Calcul_des_Temps(double **tab , long algorithme)
{
		Instanciation *P=NULL;
		long j,verdict,**M;
		for(j=0 ; j<8 ; j++)
		{
			long **Conj = Conjonction((long)tab[0][j]);
			clock_t begin = clock();
			switch(algorithme) 
			{
				
				case 1:  verdict = Validation1(Conj,(long)tab[0][j],(long)tab[0][j],15); break;
				case 2:  verdict = Validation2(Conj,(long)tab[0][j],(long)tab[0][j]); break;
				case 3:  P = Validation3(Conj,(long)tab[0][j],(long)tab[0][j]); break;
			}
			clock_t end = clock();
			tab[1][j] = (double)(end - begin) / CLOCKS_PER_SEC;	
			if(P!=NULL)	
			tab[2][j] = 1;
			else tab[2][j]=verdict;

		}
		return tab;
}

double **Tableau_de_Valeurs23(void)
{
	long i ;
	double **tab;
	tab = (double **)malloc(4*sizeof(double *));
	for(i=0 ; i<3 ; i++) tab[i] = (double *)malloc(8*sizeof(double));
	tab[0][0]=10;
	tab[0][1]=11;
	tab[0][2]=12;
	tab[0][3]=13;
	tab[0][4]=14;
	tab[0][5]=15;
	tab[0][6]=16;
	tab[0][7]=17;
	for(i=0 ; i<8 ; i++)tab[1][i] = 0 ;
	return tab;
}


void Afficher_Tableau_de_Valeurs(double **tab)
{
	long j,verdict;
		for(j=0 ; j<10 ; j++)
		{
			verdict = (int)tab[2][j];
			printf("N = %f \t T= %f \t , Satisfiable = %d  \n",tab[0][j],tab[1][j],tab[2][j]);	
		}
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
/*
Matrice LectureConjonction(void)
{
	int n,m,i,j;
	printf("Lecture de la Conjonction:\n");
	printf("Entrez le nombre de clauses : ");
	scanf("%d",&n); getchar();
	printf("Entrez le nombre de litteraux des clauses : ");
	scanf("%d",&m); getchar();
	int **Conjonction=(int **)malloc(n*sizeof(int *));
	for(i=0;i<n;i++) Conjonction[i]=(int *)malloc(m*sizeof(int));
	printf("Remplir la matrice :\n");
	for(i=0;i<n;i++)
	{
		printf("Saisie de la clause %d :\n",(i+1));
		for(j=0;j<m;j++)
		{
			printf("\t%c = ",(j+97));
			scanf("%d",&(Conjonction[i][j]));
			getchar();
		}
	}	
	Matrice Mat; 
	Mat.m=m;
	Mat.n=n;
	Mat.Pointer=Conjonction;
	return Mat;
}
*/
int main(int argc, char *argv[]) 
{ 


	
	printf("Execution de Validation2 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs23(),2));
	
	printf("Execution de Validation3 :\n");
	Afficher_Tableau_de_Valeurs(Calcul_des_Temps(Tableau_de_Valeurs23(),3));


/*	int C[4][4] ={
            {1 ,0 ,1 ,0 },
            {0 ,0 ,0 ,1 },
            {1 ,1 ,0 ,0 },
            {0 ,0 ,1 ,1 }
            };
	
	//Affichage(Validation(MatrixToPointer(&C[0][0],4,4),4,4));
	//Version 1
	printf("Version 1 :\n");
	Matrice Conj = LectureConjonction();
	printf("\nLa conjontion = \n");
	AfficherMatrice(Conj.Pointer,Conj.n,Conj.m);
	printf("\nEntrez l'instanciation : ");
	int instance ; scanf("%d",&instance); getchar();
	if(Validation1(Conj.Pointer,Conj.n,Conj.m,instance)) printf("\nLinstance %d est Solution.",instance);
	else printf("\nLinstance %d n'est pas Solution.",instance);
	
	
	//Version 1
	printf("\nVersion 2 :\n");
	 Conj = LectureConjonction();
	printf("\nLa conjontion = \n");
	AfficherMatrice(Conj.Pointer,Conj.n,Conj.m);
	if(Validation2(Conj.Pointer,Conj.n,Conj.m)) printf("\nLa Conjonction est Satisfiable.");
	else printf("\nLa Conjonction n'est pas Satisfiable.");
	
	//Version3
	printf("\nVersion 2 :\n");
	Conj = LectureConjonction();
	printf("\nLa conjontion = \n");
	AfficherMatrice(Conj.Pointer,Conj.n,Conj.m);
	Affichage(Validation3(Conj.Pointer,Conj.n,Conj.m));
*/	
	getchar();
	return 0;
}


