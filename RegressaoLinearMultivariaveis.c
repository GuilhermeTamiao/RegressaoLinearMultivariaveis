/*
 * Regressão Linear Multivariável
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 6     // Tamanho do vetor de características
#define M 1338 // Número de exemplos de treinamento 


double x[M][N + 1]; // Entradas
double y[M];       // Saídas verdadeiras

double theta[N + 1]; // Parâmetros do modelo linear 

int ciclos_cont; // Contador de ciclos de treinamento


/* Gera o arquivo .csv de saída e o atualiza */
void atualiza_output(int turno, double custo){
	FILE *f_out;
    
    f_out = fopen("output.csv", "a");
    
    fprintf(f_out,"%d,%lf \n",turno,custo);
    
    fclose(f_out);	
}


/* Calcula a saída do modelo linear */
double h(int indiceExemplo){
	double valor = 0;
	int z;
	for ( z=0;z < N+1; z++){
		valor = valor + ( x[indiceExemplo][z] * theta[z] );
	}
	return valor;
}


/* Função de custo do modelo linear */
double J(void){
	double custo = 0;
	int z;
	for ( z=0;z < M; z++){
		custo = custo + ( (h(z) - y[z]) * (h(z) - y[z]) ) ;
	}
	return ( custo /  ( 2 * M ) );
}


/* Função que calcula a derivada parcial do custo com relação a um parâmetro */
double dJdTheta(int indiceParametro){
	double derivada = 0;
	int z;
	for (z=0;z < M; z++){
		derivada = derivada + ( ( h(z) - y[z] ) * x[z][indiceParametro] );
	}
	return ( derivada / M );
}


/* Função de treinamento do modelo linear */
int treinamento(double limiarConvergencia, double taxaAprendizagem){
   
   double custo_old = J();	
   
   if (ciclos_cont == 0)
     atualiza_output(ciclos_cont,custo_old);
   	int z;
   for (z=0;z < N + 1;z++){
   	 theta[z] = theta[z] - (taxaAprendizagem * dJdTheta(z));
   }
   
   double custo_new = J();
   
   ciclos_cont++;
   atualiza_output(ciclos_cont,custo_new);
   
   if ( (custo_old - custo_new) < limiarConvergencia )
   	 return 0;
   else 
     return 1;   
}


/* Função para ler o arquivo .csv e carregar os parâmetros */
void carrega_input(void){
   FILE *f_file;

    f_file = fopen("input.csv", "r");
    if (f_file == NULL) {
        fprintf(stderr, "Erro na abertura do arquivo!\n");
    }
 
    char line[1024];
    char *p;
    int cont = -1, i = -1;
    
    // Carrega os parâmetros 'x' e 'y', lendo linha por linha do arquivo e utilizando 'i' e 'cont' como contadores
    while (fgets(line, 1024, f_file)){
    	i = -1;
    	if (cont > -1 && cont < M){		
    	  x[cont][++i] = 1;
			
    	  p = strtok(line,",");
       	  x[cont][++i] = atof(p);
    		
    	  p = strtok (NULL, ",");
    	  if (strcmp(p, "male") == 0)
    		x[cont][++i] = 1;
    	  else
    	    x[cont][++i] = 2;
    		
          p = strtok (NULL, ",");
          x[cont][++i] = atof(p);
          
          p = strtok (NULL, ",");
          x[cont][++i] = atof(p);
          
          p = strtok (NULL, ",");
          if (strcmp(p, "yes") == 0)
    		x[cont][++i] = 1;
    	  else
    	    x[cont][++i] = 2;
    	    
    	  p = strtok (NULL, ",");
    	  if (strcmp(p, "southwest") == 0)
    		x[cont][++i] = 1;
    	  else if (strcmp(p, "southeast") == 0)
    	    x[cont][++i] = 2;
    	  else if (strcmp(p, "northwest") == 0)
    	    x[cont][++i] = 3;
    	  else 
    	    x[cont][++i] = 4;
    	    
    	  p = strtok (NULL, ",");
    	  y[cont] = atof(p);
		}
        cont++;     
    }
    
    fclose(f_file);
} 


int main(void){
	
	// 1. Abre arquivo e carrega 'x' e 'y'
	
	carrega_input();
	
/*	Descomentar para checar leitura da entrada... 
	for (int q=0;q<50;q++){
    	for (int w=0;w<N+1;w++){
    		printf("%lf -",x[q][w]);
		}
		printf(" %lf\n",y[q]);
	}*/

	
	// 2. Inicia o vetor theta e starta o contador de ciclos
	
	ciclos_cont = 0;
	int z;
	for (z=0;z < N + 1;z++){
	  theta[z] = 1;	
	}
	
	// 3. Processo de treinamento:
	
	double taxa, limiar;
	int convergencia = 1;
	
	printf("Insira o valor desejado para taxa de aprendizagem:");
	scanf("%lf", &taxa);
	printf("\nInsira o valor desejado para limiar de convergencia:");
	scanf("%lf", &limiar);
	
	while (convergencia != 0){
		convergencia = treinamento(limiar,taxa);
	}
	printf("%d\n",ciclos_cont);
	
	// 4. Gera arquivo de saída (com número de ciclos de treinamento e valor da função de custo)
	
	
	
}

