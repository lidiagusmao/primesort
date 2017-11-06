#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //Para usar a função popen

#define primo 0
#define nao_primo 1


//Fũnção que checa se o número é primo. Ela já seleciona só os não pares, porque os pares já não são primos.
int funcao_primo(int num){
int i, n;

if(num == 1){
	return nao_primo;
}else if(num == 2 || num == 3){
		return primo;
	}else if(num%2 != 0){ //É impar, só checar se é primo se for ímpar. Os pares já não são
			for(i=3; i<num/2; i++){ //Checar apenas até o número qué a metade de num
				if(i%2 != 0){ //Se i for ímpar
					n = num%i;
					if(n==0){ //É divisível por i (i nem pode assumir os valores 1 ou num, por causa da condição do for)
						return nao_primo;
					}
				}
			}
			return primo;
		}else{
			return nao_primo;
		}
}



int main(){

int i, num, n, pos=0, vetor[200000], retorno, vetornaoprimos[200000], p=0, j;
FILE *ordenador;

//Lê todos os números da entrada e colca em "vetor"
scanf("%d", &vetor[pos]); //Checar a primeira posição do vetor

while(vetor[pos] != -1){
	pos++;
	scanf("%d", &vetor[pos]);
}

for(i=0; i<=pos-1; i++){ //Lê até a penúltima posição do "vetor" porque a última é o próprio -1 e não quero chechar se ele é primo ou não
	retorno = funcao_primo(vetor[i]); //Recebe o que sai da funcao_primo
		if(retorno == nao_primo){
			vetornaoprimos[p] = vetor[i]; //Se não for primo ele sava dentro do veotor dos não primos
			p++;
		}
}

//Função do pipe que permite utilizar o "sort" para ordenar
if((ordenador = popen("sort -n -r", "w")) == NULL){
	perror("popen");
	exit(1);
}

//Coloca todos os numeros das posições do "vetornaoprimos" dentro do file ordenador
for(j=0; j<p; j++){
	fprintf(ordenador, "%d\n", vetornaoprimos[j]);
}

pclose(ordenador); //Fechar o arquivo file ordenador

return 0;

}