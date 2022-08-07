#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct lista{
  char info;
  struct lista *prox;
}Tlista;

typedef Tlista *Pointer;

Pointer insere(Pointer ultimo, char caracter);
void libera(Pointer ultimo);
int busca(Pointer lista,char substring[], int num_elementos);



int main(void) {

  int tamanho, contador;
  int contador_menor = 0;
  int ciclicas = 0;
  char string_ini[50];

  Pointer Plista = NULL; // INICIALMENTE O PONTEIRO APONTA PARA NULL

  printf("Digite o tamanho do conjunto de substrings:\n");
  scanf("%d",&tamanho); // PEDINDO O TAMANHO DO CONJUNTO DAS SUBSTRINGS

  printf("Digite a string inicial(uma por linha e todas com letras minusculas):\n");
  scanf("%s",string_ini); // PEDINDO A STRING QUE SERA INSERIDA NA LISTA

    // LACO PARA INSERCAO NA LISTA CIRCULAR
  for(int i = 0; i < strlen(string_ini); i++){
    Plista = insere(Plista,string_ini[i]);
  }

  char substrings[tamanho][50]; // DECLAREI MINHA MATRIZ PARA CONTER AS SUBSTRINGS

    // LACO PARA INSERCAO DAS SUBSTRINGS NA MATRIZ
  printf("Digite, a seguir, as %d substrings (uma por linha e todas com letras minusculas):\n",tamanho);
  for(int i = 0; i < tamanho; i++){
    scanf("%s",substrings[i]);
  }

  printf("\n"); // APENAS ESTETICO

    // LACO PARA ENTRAR NA FUNCAO "busca", ONDE ACONTECERA A COMPARACAO ENTRA A LISTA CIRCULAR E AS SUBSTRINGS
  for(int i = 0; i < tamanho; i++ ){

    contador = busca(Plista,substrings[i],strlen(string_ini));
    if(contador != 0){
      ciclicas++; // CONTADOR PARA SABER QUANTAS STRINGS CICLICAS FORAM IDENTIFICADAS
      if(contador < contador_menor || contador_menor == 0){ // CONDICAO PARA SEMPRE PEGAR O NUMERO DE CARACTERES DA MENOR SUBSTRING
      contador_menor = contador;
      }
    }
  }


  printf("Numero de strings ciclicas: %d\n", ciclicas);
  printf("Menor pontuacao: %d\n",contador_menor);

  libera(Plista); // LIBERA A LISTA CIRCULAR

  return 0;
}

Pointer insere(Pointer ultimo, char caracter){ // FUNCAO PARA INSERIR NA LISTA CIRCULAR

  Pointer novo = (Pointer)malloc(sizeof(Tlista)); // ALOCANDO DINAMICAMENTE O NOVO NÓ
  novo -> info = caracter; // ADOTANDO VALOR PARA O NO

  if(ultimo == NULL){ // CASO NAO HAJA NENHUM NO
    ultimo = novo;
    novo -> prox = novo; // APONTAMENTO PARA SI
  } else {
    novo -> prox = ultimo -> prox; // O NOVO NO APONTA PARA O PRIMEIRO DA LISTA
    ultimo -> prox = novo; // O ULTIMO DA LISTA APONTA PARA O NOVO
    ultimo = novo; // NOVO NO PASSARA A SER O ULTIMO NO
  }

  return ultimo; // RETORNA A LISTA AGORA INSERIDA
}

void libera(Pointer ultimo){ // FUNCAO PARA LIBERAR A ESTRUTURA

  Pointer p = ultimo -> prox; // PONTEIRO PARA PERCORRER A PARTIR DO "INICIO"
  Pointer q = ultimo; // PONTEIRO QUE APONTA PARA O FINAL SEMPRE
  while( p!= ultimo){ // LACO PARA LIBERAR ATE O PENULTIMO NO
    q = p;
    p = p -> prox;
    free(q);
  }
  free(ultimo); // FINALIZA LIBERANDO O ULTIMO NO

}

int busca(Pointer ultimo,char substring[], int num_elementos){ // FUNCAO PARA ANALISAR SE AS SUBSTRINGS ESTAO CONTIDAS NA LISTA CIRCULAR. O PARAMETRO "num_elementos" EH O NUMERO DE ELEMENTOS DA LISTA

    // VARIAVEIS AUXILIARES
  int count = 0;
  int i;
  int j;

  Pointer p; // PONTEIRO PARA PERCORRER A MINHA LISTA CIRCULAR

    // "j" EH UMA VARIAVEL PARA PERCORRER A SUBSTRING. PERCORREREI A LISTA DUAS VEZES PARA O CASO EM QUE A SUBSTRING ESTEJA NO FINAL E NO INICIO SIMULTANEAMENTE
  for( i=0,j=0, p = ultimo -> prox ; i< 2*num_elementos; i++, p = p -> prox){

    if(p -> info == substring[j]){ // SE O ELEMENTO DA SUBSTRING FOR IGUAL AO DA LISTA
      count++; // CONTADOR PARA SABER O NUMERO DE CARACTERES IGUAIS ENCONTRADOS
      j++; // SE ENCONTRAR, PULAREI UMA CASA DA SUBSTRING PARA UMA NOVA ANALISE
    } else {
      count = 0; // SE NAO ENCONTRAR, CONTADOR ADMITIRA 0 E ANALISAREI O PRIMEIRO ELEMENTO DA SUBSTRING NOVAMENTE
      j = 0;
      }

    if(count == strlen(substring)){ // SE CONTADOR FOR IGUAL AO NUMERO DE CARACTERES DA SUBSTRING, A SUBSTRING ESTARA CONTIDA TOTALMENTE NA LISTA
      return count;
    }
  }

  if(count != strlen(substring)){ // CASO CONTADOR SEJA DIFERENTE DO NUMERO DE CARACTERES DA SUBSTRING, A SUBSTRING N FOI ENCONTRADA NA LISTA
    count = 0;
  }

  return count; // RETORNA SOMENTE O CONTADOR, NUMERO DE CARACTERES DA SUBSTRING
}
