#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

const int CIRCUITO = 130;

void exibirCorredores(char *corredores[], int quant);
void iniciarCorrida(char *corredores[], int posicoes[], int quant, size_t escape);
void exibirCorredor(char *corredor, int posicao, size_t escape);
void gerarNovasPosicoes(int posicoes[], int quant);
void limparTela();
int checarVencedor(int posicoes[], int quant);
size_t definir_escape(char *nomes[], int quant);

int main (int argc, char **argv) {
    int quantCorredores = argc - 1;
    int posicoes[quantCorredores];
    char *corredores[quantCorredores];
    for (int i = 0; i < quantCorredores; i++) {
	    corredores[i] = argv[i+1];
	    posicoes[i] = 0;
    }
    size_t escape = definir_escape(corredores, quantCorredores);
    iniciarCorrida(corredores, posicoes, quantCorredores, escape);
    return 0;
}

void iniciarCorrida(char *corredores[], int posicoes[], int quant, size_t escape)
{
    while(checarVencedor(posicoes, quant) == 0)
    {
	system("clear");
	limparTela();
        for(int i = 0; i < quant; i++)
        {
            exibirCorredor(corredores[i], posicoes[i], escape);
        }
	gerarNovasPosicoes(posicoes, quant);
	usleep(250000);
    }
    int pos_vencedor = checarVencedor(posicoes, quant) - 1;
    posicoes[pos_vencedor] = CIRCUITO;
    system("clear");
    for(int i = 0; i < quant; i++)
    {
	    exibirCorredor(corredores[i], posicoes[i], escape);
    }
    printf("\n");
    printf("PARABÉNS PELA VITÓRIA, %s!\n", corredores[pos_vencedor]);
}

int checarVencedor(int posicoes[], int quant)
{
    for(int i = 0; i < quant; i++)
    {
        if(posicoes[i] == CIRCUITO)
        {
            return i + 1;
        }
    }
    return 0;
}

void gerarNovasPosicoes(int posicoes[], int quant)
{
	srand(time(0));
	for(int i = 0; i < quant; i++)
	{
		int mov = (rand() % 100) + 1;
		switch(mov)
		{
			case 1 ... 15:
				posicoes[i] += 3;
				break;
			case 16 ... 30:
				posicoes[i] -= 3;
				break;
			case 31 ... 40:
				posicoes[i] += 4;
				break;
			case 41 ... 50:
				posicoes[i] -= 4;
				break;
			case 51 ... 62:
				posicoes[i] += 2;
				break;
			case 63 ... 74:
				posicoes[i] -= 2;
				break;
			case 75 ... 80:
				posicoes[i] += 6;
				break;
			case 81 ... 84:
				posicoes[i] -= 5;
				break;
			case 85 ... 89:
				posicoes[i] += 0;
				break;
			case 90 ... 94:
				posicoes[i] += 1;
				break;
			case 95 ... 99:
				posicoes[i] -= 1;
				break;
			case 100:
				posicoes[i] = -10;
				break;
		}
		if(posicoes[i] < 0)
		{
			posicoes[i] = 0;
		}
		else if(posicoes[i] > CIRCUITO)
		{
			posicoes[i] = CIRCUITO;
		}			
	}
}

void exibirCorredor(char *corredor, int posicao, size_t escape)
{
    printf("%s", corredor);
    for(int i = 0; i < escape - strlen(corredor); i++)
    {
        printf(" ");
    }
    printf("|");
    for(int i =0; i < CIRCUITO; i++)
    {
        i == posicao ? printf(">") : printf("-");
    }
    printf("|\n");
}

size_t definir_escape(char *nomes[], int quant)
{
    size_t escape = 0;
    for(int i = 0; i < quant; i++)
    {
        if(strlen(nomes[i]) > escape)
        {
            escape = strlen(nomes[i]);
        }
    }
    return escape + 1;
}

void limparTela()
{
	for(int i = 0; i < 16; i++)
	{
		printf("\n");
	}
}
