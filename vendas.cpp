#include<stdio.h>
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<locale.h>
//#include<windows.h> 
//#include<time.h>

struct VENDAS
{
  int id;
	char produto [20];
	float preco;
	float preco_custo;
};

VENDAS venda;

int tamanho_bin(FILE *);
void cadastrar_venda(FILE *);
void consultar_venda(FILE *);
void gerar_txt(FILE *);
void cancelar_venda(FILE *);
int obter_id(FILE *);


int main()
{
	int op;
	setlocale(LC_ALL,"Portuguese");
	
	FILE *arquivo;
	
	if((arquivo = fopen("dados.dat","rb+"))==NULL)
	{
		if((arquivo = fopen("dados.dat","wb+"))==NULL)
		{
			printf("Erro na abertura do arquivo.\n");
			printf("\n");
			system("pause");
		}			
	}

do
  {
    system("cls");
    printf("\n=*=*=*=Menu=*=*=*=\n");
    printf("1 - Cadastrar venda.\n");
    printf("2 - Consultar venda.\n");
    printf("3 - Gerar arquivo.\n");
    printf("4 - Cancelar venda.\n");
    printf("5 - Sair.");
    printf("\n=*=*=*=*=*=*=*=*=*=\n");
    printf("\nSua opção: ");
  	scanf("%i",&op);
	
	    switch (op)
    	{
    		case 1:
    			cadastrar_venda(arquivo);
    		break;
        case 2:
          consultar_venda(arquivo);
        break;
        case 3:
          gerar_txt(arquivo);
        break;
        case 4:
          cancelar_venda(arquivo);
        break;
    	}
        
  }while (op!=5);
  
	return 0;
}



void cadastrar_venda(FILE *arquivo)
{
  int i = obter_id(arquivo);
  venda.id = i;
	system("cls");
	printf("Digite o nome do produto: ");
	fflush(stdin);
	scanf("%s",&venda.produto);
	printf("Digite o preço da venda: ");
	scanf("%f",&venda.preco);
	printf("Digite o preço de custo do produto: ");
	scanf("%f",&venda.preco_custo);
  printf("O id da sua venda é: %i",venda.id);
	fseek(arquivo,0,SEEK_END);
	fwrite(&venda,sizeof(VENDAS),1,arquivo);
  memset(venda.produto,0,20);
  i++;
  printf("\n");
  system("pause");
}

void consultar_venda(FILE *arquivo)
{
  int pesquisa_id;
  system("cls");
  printf("Pesquise a venda pelo id:");
  scanf("%i",&pesquisa_id);
  if (pesquisa_id>=0)
  {
      fseek(arquivo, pesquisa_id * sizeof(VENDAS), SEEK_SET);
      fread(&venda, sizeof(VENDAS),1,arquivo);
      if (venda.id >= 0)
      {
        printf("id: %i\n",venda.id);
        printf("Produto: %s\n",venda.produto);
        printf("Preço do produto: %.2f\n", venda.preco);
        printf("Preço de custo: %.2f\n", venda.preco_custo);
      }    
      else
        printf("Id não encontrado.");
  }
  printf("\n");
  system("pause");
}

void gerar_txt(FILE *arquivo)
{
  system("cls");
  char nome_arquivo[20];
  printf("Digite o nome do arquivo: ");
  scanf("%s", &nome_arquivo);
  strcat(nome_arquivo, ".txt");
  printf("Criando arquivo");
  FILE *arquivo_txt = fopen(nome_arquivo, "w");
  if(!arquivo_txt)
  {
  	printf("Não foi possível criar esse arquivo!\n");
  	printf("\n");
  	system("pause");
  }
	printf("\nO arquivo texto foi criado.");
	
  int nr;
  for (nr = 0; nr < tamanho_bin(arquivo); nr++)
	{
		fseek(arquivo, nr * sizeof(VENDAS), SEEK_SET);
		fread(&venda, sizeof(VENDAS), 1, arquivo);
    if (venda.id >= 0)
    {
      fprintf(arquivo_txt,"=================================\n");
		  fprintf(arquivo_txt, "id: %i\n", venda.id);
		  fprintf(arquivo_txt, "Produto: %s\n", venda.produto);
		  fprintf(arquivo_txt, "Preço do produto: R$%.2f\n", venda.preco);
		  fprintf(arquivo_txt, "Preço de custo: R$%.2f\n", venda.preco_custo);
		  fprintf(arquivo_txt, "=================================");
    }
	}
	fclose(arquivo_txt);
	printf("\n");
  	system("pause");
}


int tamanho_bin(FILE *arquivo)
{
  fseek(arquivo, 0, SEEK_END);
  return ftell(arquivo) / sizeof(VENDAS);
}


void cancelar_venda(FILE *arquivo)
{
	char confirma;
	int nr;
	system("cls");
	printf("\nInforme o id da venda a ser cancelada:");
	scanf("%d",&nr);
	if ((nr <= tamanho_bin(arquivo)) && (nr>=0))
	{
		fseek(arquivo, (nr) * sizeof(VENDAS), SEEK_SET);
		fread(&venda, sizeof(VENDAS), 1, arquivo);
		if (venda.id == nr)
		{
			printf("\nNome do produto:%s", venda.produto);
			printf("\nPreço de venda:%f", venda.preco);
			printf("\nPreço de custo:%f", venda.preco_custo);
			printf("\nId:%i\n",venda.id);
			printf("\nConfirma o cancelamento: <s/n>\n");
			getchar();
			scanf("%c", &confirma);
				if (toupper(confirma) == 'S')
					{
						fseek(arquivo, (nr) * sizeof(VENDAS), SEEK_SET);
						venda.id= -1;
						fwrite(&venda, sizeof(VENDAS), 1, arquivo);
						printf("\nA venda foi cancelada.\n");
					}
		}
	else
	{
		printf("Essa Venda não existe. \n");
	}	
	}
	printf("\n");
  	system("pause");
}


int obter_id(FILE *arquivo)
{
  int posicao;
  fseek(arquivo, 0, SEEK_END);
  posicao = ftell(arquivo) / sizeof(venda);
  return posicao;
}

