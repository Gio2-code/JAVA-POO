#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrixFill(int **mat, int r, int c);
void riempiColonne(int **mat, int r, int c);
void riempiColonne1(int **mat, int r, int c, int x, int y, int z, int t);
void printMatrix(int **mat, int r, int c);
void safePath(char *safepath, int **mat);
void printMatrixInFile(char *floar,int **mat, int r, int c);
void readMatrixInFile(char *floar,int **mat, int r, int c);
void pathControll(int **mat, int rig, int col);
int returnFirstElemenFile(char *floar);

int main(){
	int x, y, i, r, c, repeat = -1, repeat1 = -1;
	char yf_newElement, yf_printMatrix, yf_matryxByFile, f;
	
	while(repeat1 < 0){// quessto ciclo si ripete fino a quando "repeat1" non viene incrementato
		printf("Se si vuole prendere le dimensioni da file inserire 1 altrimenti inserire 2:\t");
		scanf(" %c",&f);
		if(f == '1'){
			FILE *fp_dim = fopen("dim.txt","r");
			
			if(fp_dim){// questo if controlla se il file "fp_dim" è stato aperto correttamente
				for(i=0;i<1;i++){// questo for prende le dimensioni della matrice da file "dim.txt"
					fscanf(fp_dim,"%d %d",&r,&c);
				}
				fclose(fp_dim);
			}
			else{
				printf("Errore nell'apertura de file 'dimensioni.txt'\n");
				exit(1);
			}
			repeat1++;
		}
		else if(f == '2'){// questo if in caso si è scelto di inserire le dimensioni della matrice, poi aggiorna "repeat1" uscendo dal ciclo
			printf("\nInserire il numero di righe della matrice:\t");
			scanf("%d",&r);
			printf("\nInserire il numero di colonne della matrice:\t");
			scanf("%d",&c);
			printf("\n");
			repeat1++;
		}
		else// si entra in questo else quando non si è inserito un carattere accettabile, stampa un messaggio di errore e non aggiorna "repeat1" facendo ripartire il ciclo se non si soddisfa il requisito del valore accettabile il ciclo è infinito
			printf("\nIl numero inserito non e' corretto riprovare\n");
}
	
	int **floor=(int **)malloc(r*sizeof(int));// dichiarazione della matrice "floor"
    for(i=0;i<c;i++)
        floor[i]=(int *)malloc(c*sizeof(int));// fine dichiarazione matrice
	
	while(repeat < 0){// il while cicla fino a quando repeat non viene incrementato
		if(returnFirstElemenFile("floar.txt") == 0){// controlla se il primo elemento del file è pari a 0
			printf("Vuoi prendere la matrice precedentemente inserita nel file?: Y/N\n");
			scanf(" %c", &yf_matryxByFile);
			if(yf_matryxByFile == 'y' || yf_matryxByFile == 'Y'){// in caso affermativo rispetto alla condizione iniziale e avendo inserito "y" legge la matrice all'intreno del file
				readMatrixInFile("floar.txt",floor,r,c);
				repeat++;
			}
			else if(yf_matryxByFile == 'n' || yf_matryxByFile == 'N'){// in caso affermativo rispetto alla condizione iniziale e avendo inserito "n" incrementa "repeat" uscendo dal ciclo
				matrixFill(floor,r,c);// viene riempita la matrice "floor" usando le funzioni di seguito
				riempiColonne(floor,r,c);
				safePath("safepath.txt",floor);
				repeat++;
			}
			else if(yf_matryxByFile == 'k' || yf_matryxByFile == 'K')// controlla se il carattere inserito e "k" uscendo se questo è vero
				exit(1);
			else{// permette di inserire una carattere accettabile nel caso si fosse commesso un errore o uscire dal programma inserendo il carattere "k"
				printf("\nIl carattere inserito non e' presente, se si vuole uscire inserire il carattere: K\n");
				scanf(" %c", &yf_matryxByFile);
				if(yf_matryxByFile == 'k' || yf_matryxByFile == 'K')
					exit(1);
			}
		}
		else{
			matrixFill(floor,r,c);// viene riempita la matrice "floor" usando le funzioni di seguito
			riempiColonne(floor,r,c);
			safePath("safepath.txt",floor);
			printf("\n");
			repeat++;
		}
	}
	
	do{// il do-While controlla il carattere assegnato alla variabile "yf_newElement" dall'utente in caso sia "y" il ciclo si ripete per 5 volte prima di richiedere nuovamente una valorizzazione di "ch"
		i = 0;
		while(i != 5){// questo while fa inserire all'utente 5 punti prendendo prima la "x" e poi la "y"
			x = 100;
			y = 100;
			while(x > r){// controlla se la x inserita è compresa nella matrice prenendo come massimo il numero delle righe
				printf("\nInserisci la x: ");
				scanf("%d", &x);
			}
			while(y > c){// controlla se la y inserita è compresa nella matrice prenendo come massimo il numero delle colonne
				printf("Inserisci la y: ");
				scanf("%d", &y);
			}
			pathControll(floor,x,y);
			printMatrixInFile("floar.txt",floor,r,c);
			i++;
		}
		printf("Vuoi continuare: Y/N\t");
		scanf(" %c", &yf_newElement);
		printf("Vuoi stampare la matrice: Y/N\t");
		scanf(" %c", &yf_printMatrix);
		printf("\n");
		if(yf_printMatrix == 'y' || yf_printMatrix == 'Y'){
			printMatrix(floor,r,c);
			printf("\n");
		}
	} while(yf_newElement == 'y' || yf_newElement == 'Y');
	return 0;
}

void matrixFill(int **mat, int r, int c){// riempie automaticamente l'intera matrice con -1
	int i,j;
	
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			mat[i][j]=-1;
		}
	}
}

void riempiColonne(int **mat, int r, int c){//riempie le prime 2 e le ultime 2 colonne della matrie con 0
	int i,j;
	
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			mat[i][0]=0;
			mat[i][1]=0;
			mat[i][c-2]=0;
			mat[i][c-1]=0;
		}
	}
}

void riempiColonne1(int **mat, int r, int c, int x, int y, int z, int t){//riempie le colonne, date nella funzione, della matrie con 0
	int i,j;
	
	for(i=0;i<r;i++){ 
		for(j=0;j<c;j++){
			mat[i][x]=0;
			mat[i][y]=0;
			mat[i][z]=0;
			mat[i][t]=0;
		}
	}
}

void printMatrix(int **mat, int r, int c){// stampa la matrice
	int i,j;
	
	for(i=0;i<r;i++){
       for(j=0;j<c;j++){
			printf("[%d]\t",mat[i][j]);
		}
	printf("\n");
	}
}

void safePath(char *safepath, int **mat){// inserisce 0 nella matrice in corrispondenza delle coordinate prese da file
	FILE *fp_path = fopen(safepath,"r");
	int ele2=0, ele1=0;
	
	if(fp_path){// questo if controlla se il file è stato aperto correttamente
		while(!feof(fp_path)){// il while legge riga per riga il file fino alla fine
		fscanf(fp_path,"%d %d",&ele1,&ele2);// fscanf legge gli elementi nella riga e li mette rispettivamente in ele1 ed ele2
		mat[ele1-1][ele2-1] = 0;// questa stringa prendendo le coordinate di un punto della matrice inserisce lì 0 
		}
		fclose(fp_path);
	}
	else{
		printf("Errore nell'apertura de file 'safepath.txt'\n");
		exit(1);
	}
}

void printMatrixInFile(char *floar,int **mat, int r, int c){// inserisce la matrice nel file "floar.txt"
	FILE *fp_flo = fopen(floar,"w");
	int i,j;

	if(fp_flo){// questo if controlla se il file è stato aperto correttamente
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				fprintf(fp_flo,"%d\t",mat[i][j]);
			}
			fprintf(fp_flo,"\n");
		}
		fclose(fp_flo);
	}
	else{
		printf("Errore nell'apertura de file 'floar.txt'\n");
		exit(1);
	}
}

void readMatrixInFile(char *floar,int **mat, int r, int c){// legge la matrice nel file e ne implementa i dati nella stessa
	FILE *fp_flo = fopen(floar,"r");
	int i,j;

	if(fp_flo){// questo if controlla se il file è stato aperto correttamente
		for(i=0;i<r;i++){
			for(j=0;j<c;j++){
				fscanf(fp_flo,"%d",&mat[i][j]);
			}
		}
		fclose(fp_flo);
	}
	else{
		printf("Errore nell'apertura de file 'floar.txt'\n");
		exit(1);
	}
}

void pathControll(int **mat, int rig, int col){// controlla il valore della cella indicata dalle cordinate nella matrice, stampa sul termilae l'eventuale trappola innescata
	int i = mat[rig-1][col-1];
	
	srand(time(0));
	if(i < 0){
		i = 1+rand()%10;
	}
	switch(i){
		case 0:
			printf("Percorso sicuro\n\n");
			break;
		case 1:
			printf("Un bocchettone sul tetto spruzza del veleno, l'avventuriero deve fare un tiro salvezza per evitare di essere avvelenato. \nSe l'avventuriero fallisce, e' avvelenato. Mentre e' avvelenato, tutti i test saranno eseguiti con svantaggio. \nL'effetto del veleno dura finche' l'avventuriero non effettua con successo un test salvezza.\n\n");
			mat[rig-1][col-1] = 1;
			break;
		case 2:
			printf("Dardi a forma di cheliceri vengono sparati dalla parete a destra colpendo tutto quello che incontrano, \nl'avventuriero deve fare un tiro salvezza per evitare la trappola, se fallisce l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 2;
			break;
		case 3:
			printf("Dardi a forma di cheliceri vengono sparati dalla parete a sinistra colpendo tutto quello che incontrano, \nl'avventuriero deve fare un tiro salvezza per evitare la trappola, se fallisce l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 3;
			break;
		case 4:
			printf("Dal tetto viene versato dell'acido trasparente, l'avventuriero deve fare un tiro salvezza per evitare la trappola, \nse fallisce l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 4;
			break;
		case 5:
			printf("Dal pavimento delle zampe di ragno si chiudono come una tagliola, l'avventuriero deve fare un tiro salvezza per evitare la trappola, \nse fallisce l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 5;
			break;
		case 6:
			printf("Dal tetto delle lace simili a zampe di ragno cadono, l'avventuriero deve fare un tiro salvezza per evitare la trappola, \nse fallisce l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 6;
			break;
		case 7:
			printf("Un bozzolo si crea attorno all'avventuriero bloccandolo, l'avventuriero deve fare un tiro salvezza per evitare la trappola, \nse fallisce resta bloccato nel bozzolo fino a quando qualcuno non lo libera, \noppure puo' provare a liberarsi con un successo su una prova con svantaggio. Ogni minuto passato nel bozzolo l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 7;
			break;
		case 8:
			printf("Nella stanza 8 occhi appaiono fluttuando, questi scatenano un senso di angoscia, disagio e paura, \nl'avventuriero deve fare un tiro salvezza per evitare gli effetti della trappola, se fallisce tutti i test saranno eseguiti con svantaggio. \nQuesto effetto dura finche' l'avventuriero non effettua con successo un test.\n\n");
			mat[rig-1][col-1] = 8;
			break;
		case 9:
			printf("Un ragno cade dal soffitto sull'avventuriero, l'avventuriero deve fare un tiro salvezza per evitare il ragno, \nse fallisce il ragno morde l'avventuriero che subisce 1 danno. Il ragno non scompare rimanendo come nemico sul campo, \nquesto però non conosce qual e' il percorso corretto per cui può cadere lui stesso nelle trappole.\n\n");
			mat[rig-1][col-1] = 9;
			break;
		case 10:
			printf("Il pavimento si apre rivelando un buco alto 3m con cheliceri sul fondo, \nl'avventuriero deve fare un tiro salvezza per evitare la trappola, se fallisce l'avventuriero subisce 1 danno.\n\n");
			mat[rig-1][col-1] = 10;
			break;
		}
}

int returnFirstElemenFile(char *floar){// restituisce il primo elemento contenuto nel file
	FILE *fp_flo = fopen(floar,"r");
	int q;
	
	if(fp_flo){// questo if controlla se il file è stato aperto correttamente
		fscanf(fp_flo,"%d",&q);
		return q;
		fclose(fp_flo);
	}
	else{
		printf("Errore nell'apertura de file 'floar.txt'\n");
		exit(1);
	}
}