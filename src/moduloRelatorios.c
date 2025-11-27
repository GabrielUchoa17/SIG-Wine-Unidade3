#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>


#include "moduloRelatorios.h"
#include "moduloAssinantes.h"
#include "moduloAssinaturas.h"
#include "moduloPlanos.h"
#include "moduloProdutos.h"
#include "util.h"

#define VERMELHO "\033[1;31m"
#define CIANO    "\033[1;36m"
#define RESET    "\033[0m"
#define CINZA     "\033[1;37m"
#define BRANCO    "\033[0;97m"
#define AMARELO   "\033[1;33m"


void menuRelatorios(){
    char opcao[10];
    Assinante *lista;
    lista = NULL;
    int crtlRelatorio = 1;
    do {
        telaRelatorios();
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
        switch (opcao[0]){
        case '1':
            relatorioAssinantesFaixaEtaria();
        break;
        case '2':
            relatorioAssinaturasPeriodo();
        break;
        case '3':
            relatorioPlanosFaixaPreco();
        break;
        case '4':
            relatorioProdutosPorMarca();
        break;
        case '5':
            relatorioPlanosPorProduto();
        break;
        case '6':
            relatorioAssinaturasPorCPF();
        break;
        case '7':
            relatorioPlanosPorPeriodo();
        break;
        case '8':
            relatorioProdutosPorAno();
            break;
        case '9':
            assinantesOrdemAlfabetica(&lista);
            telaAssinantesOrdemAlfabetica(lista);
            break;
        case '0':
            crtlRelatorio = 0;
        break; 
       default:
            printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
            printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
            getchar();
        break;
       }
    }    
    while (crtlRelatorio == 1);
}

void telaRelatorios(){
    system("clear||cls");
    printf(BRANCO);
    printf("╔═════════════════════════════════════════╗\n");
    printf("║             " AMARELO "R E L A T Ó R I O S" BRANCO "             ║\n");
    printf("╠═════════════════════════════════════════╣\n");
    printf("║ " CIANO "1." BRANCO " Assinantes(Faixa Etária)             ║\n");
    printf("║ " CIANO "2." BRANCO " Assinaturas(Período)                 ║\n");
    printf("║ " CIANO "3." BRANCO " Planos (Faixa de Preço)              ║\n");
    printf("║ " CIANO "4." BRANCO " Produtos por Marca                   ║\n");
    printf("║ " CIANO "5." BRANCO " Planos por Produtos                  ║\n");
    printf("║ " CIANO "6." BRANCO " Assinaturas por CPF                  ║\n");
    printf("║ " CIANO "7." BRANCO " Planos por Período(Direta)           ║\n");
    printf("║ " CIANO "8." BRANCO " Produtos por Ano de produção(Inversa)║\n");
    printf("║ " CIANO "9." BRANCO " Assinantes(Ordem Alfabética)         ║\n");
    printf("║ " AMARELO "0." BRANCO " Sair                                 ║\n");
    printf("╚═════════════════════════════════════════╝\n");
    printf(BRANCO "Digite sua escolha: \n" RESET);
}

void relatorioAssinantesFaixaEtaria(){
    FILE *arqAssinantes;
    Assinante* assinante;
    char opcao[10];
    int encontrou = 0;
    int idadeMin = 0; 
    int idadeMax = 150; 

    system("clear||cls");
    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║      " AMARELO "      RELATÓRIO DE ASSINANTES POR FAIXA ETÁRIA" BRANCO "        ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf(BRANCO "Escolha a faixa etária:\n" RESET);
    printf(BRANCO "1. 0 - 17 anos\n" RESET);
    printf(BRANCO "2. 18 - 30 anos\n" RESET);
    printf(BRANCO "3. 31 - 50 anos\n" RESET);
    printf(BRANCO "4. 51 anos ou mais\n" RESET);
    printf(BRANCO "\nDigite sua opção: " RESET);
    fgets(opcao, 10, stdin);


    if (opcao[1] != '\n')
        opcao[0] = 'x';

    switch(opcao[0]) {
        case '1':
            idadeMin = 0;
            idadeMax = 17;
        break;
        case '2':
            idadeMin = 18;
            idadeMax = 30;
        break;
        case '3':
            idadeMin = 31;
            idadeMax = 50;
        break;
        case '4':
            idadeMin = 51;
            idadeMax = 150;
        break;
        default:
            printf(VERMELHO "\n❌ Opção inválida!\n" RESET);
            printf(CINZA "\nPressione Enter para voltar...\n" RESET);
            getchar();
            return;
    }

    arqAssinantes = fopen("./dados/dadosAssinantes.dat", "rb");
    if(arqAssinantes == NULL) {
        printf(VERMELHO "\n❌ Erro ao abrir o arquivo de assinantes!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    assinante = (Assinante*) malloc(sizeof(Assinante));
    if (assinante == NULL) {
        printf(VERMELHO "\nErro de memória!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        fclose(arqAssinantes);
        getchar();
        return;
    }


    printf(BRANCO "\n┌──────┬────────────────────────────┬──────────────┐\n" RESET);
    printf(AMARELO "│  ID  │ Nome                       │ Idade        │\n" RESET);
    printf(BRANCO "├──────┼────────────────────────────┼──────────────┤\n" RESET);

    while(fread(assinante, sizeof(Assinante), 1, arqAssinantes)) {
        if(assinante->status == True) {
            int idade = calcularIdade(assinante->dataNascimento);
            if(idade >= idadeMin && idade <= idadeMax){
                encontrou = 1;
                printf(BRANCO "│ " CIANO "%-4d" BRANCO " │ %-26s │ %-12d │\n" RESET,    
                    assinante->id,
                    assinante->nome,
                    idade);    
            }
        }
    }
    if (encontrou){
        printf(CINZA "└──────┴────────────────────────────┴──────────────┘\n" RESET);
    
    } else{
        printf(BRANCO "│       " VERMELHO "Nenhum assinante encontrado nessa faixa." BRANCO "   │\n" RESET);
        printf(CINZA "└──────────────────────────────────────────────────┘\n" RESET);
    }
    fclose(arqAssinantes);
    free(assinante);

    printf(CINZA "\nPressione Enter para voltar ao menu...\n" RESET);
    getchar();
}   

void relatorioAssinaturasPeriodo(){
    FILE *arqAssinaturas;
    Assinatura* assinatura;
    char opcao[10];
    int encontrou = 0;
    
    system("clear||cls");
    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          " AMARELO "RELATÓRIO DE ASSINATURAS POR PERÍODO" BRANCO "              ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf(BRANCO "Escolha o Período:\n" RESET);
    printf(BRANCO "M - Mensal\n" RESET);
    printf(BRANCO "T - Trimestral\n" RESET);
    printf(BRANCO "S - Semestral\n" RESET);
    printf(BRANCO "A - Anual\n" RESET);
    printf(BRANCO "\nDigite sua opção: " RESET);
    fgets(opcao, 10, stdin);

    if (opcao[1] != '\n')
        opcao[0] = 'x';
    
    opcao[0] = toupper(opcao[0]);

    switch(opcao[0]) {
        case 'M':
            printf(CIANO "\nVocê escolheu M - Mensal\n" RESET);
        break;
        case 'T':
            printf(CIANO "\nVocê escolheu T - Trimestral\n" RESET);
        break;
        case 'S':
            printf(CIANO "\nVocê escolheu S - Semestral\n" RESET);
        break;
        case 'A':
            printf(CIANO "\nVocê escolheu A - Anual\n" RESET);
        break;
        default:
            printf(VERMELHO "\n❌ Opção inválida!\n" RESET);
            printf(CINZA "\nPressione Enter para voltar...\n" RESET);
            getchar();
            return;
    }

    arqAssinaturas = fopen("./dados/dadosAssinaturas.dat", "rb");
    if(arqAssinaturas == NULL) {
        printf(VERMELHO "\n❌ Erro ao abrir o arquivo de assinaturas!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    assinatura = (Assinatura*) malloc(sizeof(Assinatura));
    if (assinatura == NULL) {
        printf(VERMELHO "\nErro de memória!\n" RESET);
        fclose(arqAssinaturas);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }
    system("clear||cls");
    printf(BRANCO "╔════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BRANCO "║              " AMARELO "LISTAGEM DE ASSINATURAS - PERÍODO: %c" BRANCO "              ║\n" RESET, toupper(opcao[0]));
    printf(BRANCO "╠════════════════════════════════════════════════════════════════╣\n" RESET);

    printf(BRANCO "┌──────┬──────────────┬───────────────────────────┬──────────────┐\n" RESET);
    printf(AMARELO "│  ID  │ ID Assinante │ Data Assinatura           │ Período      │\n" RESET);
    printf(BRANCO "├──────┼──────────────┼───────────────────────────┼──────────────┤\n" RESET);
   

    while (fread(assinatura, sizeof(Assinatura), 1, arqAssinaturas)) {
        if (assinatura->status == True && 
            toupper(assinatura->periodoVencimento[0]) == toupper(opcao[0])) {

            encontrou = 1;
            printf(BRANCO "│ " CIANO "%-4d" BRANCO " │ %-12s │ %-25s │ %-12s │\n" RESET,
                assinatura->id,
                assinatura->idAssinante,
                assinatura->dataAssinatura,  
                assinatura->periodoVencimento);
        }
    }
    if (encontrou){
        printf(CINZA "└──────┴──────────────┴───────────────────────────┴──────────────┘\n" RESET);
    
    } else {
        printf(BRANCO "│ " VERMELHO "%-63s" BRANCO " │\n" RESET, "        Nenhuma assinatura encontrada nesse período.");
        printf(CINZA "└────────────────────────────────────────────────────────────────┘\n" RESET);
    }
    fclose(arqAssinaturas);
    free(assinatura);
    printf(CINZA "\nPressione Enter para voltar ao menu...\n" RESET);
    getchar();
}





void relatorioPlanosFaixaPreco() {
    FILE *arqPlanos;
    Plano* plano;
    char opcao[10];
    int encontrou = 0;

    float precoMin = 0.0;
    float precoMax = 999999.0;

    system("clear||cls");
    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║               " AMARELO "RELATÓRIO DE PLANOS POR PREÇO" BRANCO "                ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf(BRANCO "Escolha a faixa de preço:\n" RESET);
    printf(BRANCO "1. Até R$ 49,99\n" RESET);
    printf(BRANCO "2. R$ 50,00 a R$ 99,99\n" RESET);
    printf(BRANCO "3. R$ 100,00 a R$ 199,99\n" RESET);
    printf(BRANCO "4. R$ 200,00 ou mais\n" RESET);
    printf(BRANCO "\nDigite sua opção: " RESET);
    fgets(opcao, 10, stdin);

    if (opcao[1] != '\n')
        opcao[0] = 'x';

    switch(opcao[0]) {
        case '1':
            precoMin = 0.0;
            precoMax = 49.99;
        break;
        case '2':
            precoMin = 50.00;
            precoMax = 99.99;
        break;
        case '3':
            precoMin = 100.00;
            precoMax = 199.99;
        break;
        case '4':
            precoMin = 200.00;
            precoMax = 999999.0;
        break;
        default:
            printf(VERMELHO "\n❌ Opção inválida!\n" RESET);
            printf(CINZA "\nPressione Enter para voltar...\n" RESET);
            getchar();
            return;
    }

    arqPlanos = fopen("./dados/dadosPlanos.dat", "rb");
    if(arqPlanos == NULL) {
        printf(VERMELHO "\n❌ Erro ao abrir o arquivo de planos!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    plano = (Plano*) malloc(sizeof(Plano));
    if (plano == NULL) {
        printf(VERMELHO "\nErro de memória!\n" RESET);
        fclose(arqPlanos);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    printf(BRANCO "\n┌──────┬────────────────────────────┬──────────────┐\n" RESET);
    printf(AMARELO "│  ID  │ Nome                       │ Preço (R$)   │\n" RESET);
    printf(BRANCO "├──────┼────────────────────────────┼──────────────┤\n" RESET);

    while(fread(plano, sizeof(Plano), 1, arqPlanos)) {
        if(plano->status == True) {
            float precoFloat = atof(plano->preco);

            if(precoFloat >= precoMin && precoFloat <= precoMax) {
                encontrou = 1;
                printf(BRANCO "│ " CIANO "%-4d" BRANCO " │ %-26s │ %-12.2f │\n" RESET,
                    plano->id,
                    plano->nome,
                    precoFloat
                );
            }
        }
    }

    if (encontrou) {
        printf(CINZA "└──────┴────────────────────────────┴──────────────┘\n" RESET);
    } else {
        printf(BRANCO "│ " VERMELHO "Nenhum plano encontrado nesse intervalo de preço" BRANCO " │\n" RESET);
        printf(CINZA "└──────────────────────────────────────────────────┘\n" RESET);
    }

    fclose(arqPlanos);
    free(plano);

    printf(CINZA "\nPressione Enter para voltar ao menu...\n" RESET);
    getchar();
}



void relatorioProdutosPorMarca() {
    FILE *arqProdutos;
    Produto* produto;
    char marcaFiltro[30];
    int encontrou = 0;

    system("clear||cls");
    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                " AMARELO "RELATÓRIO DE PRODUTOS POR MARCA" BRANCO "             ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");

    printf(BRANCO "Digite a marca que deseja filtrar: " RESET);
    fgets(marcaFiltro, 30, stdin);
    tratarString(marcaFiltro);

    if (!validarMarca(marcaFiltro)) {
        printf(VERMELHO "\n❌ Marca inválida! Use apenas letras, números e espaços.\n" RESET);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    arqProdutos = fopen("./dados/dadosProdutos.dat", "rb");
    if (arqProdutos == NULL) {
        printf(VERMELHO "\n❌ Erro ao abrir o arquivo de produtos!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    produto = (Produto*) malloc(sizeof(Produto));
    if (!produto) {
        printf(VERMELHO "\n❌ Erro de memória!\n" RESET);
        fclose(arqProdutos);
        printf(CINZA "\nPressione Enter para voltar...\n" RESET);
        getchar();
        return;
    }

    printf(BRANCO "\n┌──────┬────────────────────────────┬─────────────────────────┐\n" RESET);
    printf(AMARELO "│  ID  │ Nome                       │ Marca                   │\n" RESET);
    printf(BRANCO "├──────┼────────────────────────────┼─────────────────────────┤\n" RESET);

    while (fread(produto, sizeof(Produto), 1, arqProdutos)) {
        if (produto->status == True) {
            if (strcasecmp(produto->marca, marcaFiltro) == 0) {
                encontrou = 1;
                printf(BRANCO "│ " CIANO "%-4d" BRANCO " │ %-26s │ %-23s │\n" RESET,
                    produto->id,
                    produto->nome,
                    produto->marca
                );
            }
        }
    }

    if (encontrou) {
        printf(CINZA "└──────┴────────────────────────────┴─────────────────────────┘\n" RESET);
    } else {
        printf(BRANCO "│      " VERMELHO "Nenhum produto encontrado para essa marca." BRANCO "             │\n" RESET);
        printf(CINZA "└─────────────────────────────────────────────────────────────┘\n" RESET);
    }

    fclose(arqProdutos);
    free(produto);

    printf(CINZA "\nPressione Enter para voltar ao menu...\n" RESET);
    getchar();
}

void relatorioPlanosPorProduto(void) {
    FILE* fp = fopen("./dados/dadosPlanos.dat", "rb");
    if (fp == NULL) {
        printf(VERMELHO "❌ Erro ao abrir o arquivo de planos!\n" RESET);
        printf(CINZA "\nPressione ENTER para continuar...\n" RESET);
        getchar();
        return;
    }

    Plano plano;

    system("clear||cls");

    printf(BRANCO "╔═════════════════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BRANCO "║                        " AMARELO "RELATÓRIO: PLANOS AGRUPADOS POR PRODUTO" BRANCO "                   ║\n" RESET);
    printf(BRANCO "╠═════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(AMARELO "║ %-25s | %-10s | %-15s | %-10s | %-15s   ║\n" RESET, 
        "Nome do Produto", "ID Plano", "Nome do Plano", "Preço", "Período");
    printf(BRANCO "╠═════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);

    while (fread(&plano, sizeof(Plano), 1, fp)) {
        if (plano.status == True) {

            Produto* prod = buscarProdutoPorID(plano.idProduto);

            char nomeProduto[100];
            if (prod != NULL) {
                strcpy(nomeProduto, prod->nome);
                free(prod);
            } else {
                strcpy(nomeProduto, VERMELHO "Produto não encontrado" RESET);
            }
            printf(BRANCO "║ %-25s | " CIANO "%-10d" BRANCO " | %-15s | %-10s | %-15s ║\n" RESET,
                nomeProduto,
                plano.id,
                plano.nome,
                plano.preco,
                plano.periodo
            );
        }
    }

    printf(CINZA "╚═════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);

    fclose(fp);

    printf(CINZA "\nPressione ENTER para continuar..." RESET);
    getchar();
}

void relatorioAssinaturasPorCPF(void) {
    system("clear||cls");

    char cpfBusca[20];
    int idAssinanteEncontrado;

    printf(BRANCO "╔══════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BRANCO "║                            " AMARELO "RELATÓRIO: ASSINATURAS POR CPF" BRANCO "                ║\n" RESET);
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(BRANCO "Digite o CPF do assinante: " RESET);
    fgets(cpfBusca, 20, stdin);
    tratarString(cpfBusca); 

    Assinante* assinanteAlvo = buscarAssinantePorCPF(cpfBusca); 
    
    if (assinanteAlvo == NULL) {
        printf(VERMELHO "❌ Assinante não encontrado com o CPF fornecido ou inativo.\n" RESET);
        printf(BRANCO "╚══════════════════════════════════════════════════════════════════════════════╝\n" RESET);
        printf(CINZA "\nPressione ENTER para continuar..." RESET);
        getchar();
        return;
    }

    idAssinanteEncontrado = assinanteAlvo->id;
    char nomeAssinante[100];
    strcpy(nomeAssinante, assinanteAlvo->nome);
    free(assinanteAlvo);

    FILE* fp = fopen("./dados/dadosAssinaturas.dat", "rb");
    if (fp == NULL) {
        printf(VERMELHO "❌ Erro ao abrir o arquivo de assinaturas!\n" RESET);
        printf(CINZA "\nPressione ENTER para continuar..." RESET);
        getchar();
        return;
    }

    Assinatura assinatura;
    int encontrouAssinatura = 0;

    printf(BRANCO "\n>>> Assinante: **" CIANO "%-50s" BRANCO "** (ID: " CIANO "%d" BRANCO ") \n" RESET, nomeAssinante, idAssinanteEncontrado);
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(AMARELO "║ %-10s | %-15s | %-15s | %-15s ║\n" RESET,
             "ID Ass", "Plano", "Data Assin.", "Período");
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════╣\n" RESET);

    while (fread(&assinatura, sizeof(Assinatura), 1, fp)) {
        
        int idAssinaturaNaStruct = atoi(assinatura.idAssinante); 

        if (assinatura.status == True && idAssinaturaNaStruct == idAssinanteEncontrado) {
            
            int idPlano = atoi(assinatura.idPlano);
            Plano* pl = buscarPlanoPorID(idPlano);
            char nomePlano[100];
            if (pl != NULL) {
                strcpy(nomePlano, pl->nome);
                free(pl);
            } else {
                strcpy(nomePlano, VERMELHO "ID do Plano" RESET);
            }

            encontrouAssinatura = 1;

            printf(BRANCO "║ " CIANO "%-10d" BRANCO " | %-15s | %-15s | %-14s ║\n" RESET,
                    assinatura.id,
                    nomePlano,
                    assinatura.dataAssinatura,
                    assinatura.periodoVencimento);
        }
    }

    if (!encontrouAssinatura) {
        printf(BRANCO "║ " VERMELHO "Nenhuma assinatura ativa encontrada para este assinante." BRANCO "                      ║\n" RESET);
    }

    printf(CINZA "╚══════════════════════════════════════════════════════════════════════════════╝\n" RESET);

    fclose(fp);

    printf(CINZA "\nPressione ENTER para continuar..." RESET);
    getchar();
}

void relatorioPlanosPorPeriodo(void){
    system("clear||cls");

    Plano* lista = quantidadePlanos();
    Plano* pl = lista;

    if (lista == NULL) {
        printf(VERMELHO "Nenhum plano ativo encontrado ou erro ao ler o arquivo!\n" RESET);
        printf(CINZA "\nPressione ENTER para voltar ao menu...\n" RESET);
        getchar(); 
        return; 
    }

    int quantidadeMensal = 0;
    int quantidadeTrimestral = 0;
    int quantidadeSemestral = 0;
    int quantidadeAnual = 0;

    while( pl != NULL){
        char letra = toupper(pl->periodo[0]);

        if(letra == 'M'){
            quantidadeMensal++;
        } else if(letra == 'T') {
            quantidadeTrimestral++;
        } else if(letra == 'S'){
            quantidadeSemestral++;
        } else if(letra == 'A'){
            quantidadeAnual++;
        }
        pl = pl->prox;
    }
    
    printf(BRANCO "╔══════════════════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BRANCO "║                             " AMARELO "RELATÓRIO: PLANOS POR PERÍODO" BRANCO "                                ║\n" RESET);
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(AMARELO "║ %-15s │ %-10s │ %-12s │ %-12s │ %-10s ║\n" RESET, 
        "Categoria", "Mensal", "Trimestral", "Semestral", "Anual");
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(BRANCO "║ %-15s │ " CIANO "%-10d" BRANCO " │ " CIANO "%-12d" BRANCO " │ " CIANO "%-12d" BRANCO " │ " CIANO "%-10d" BRANCO " ║\n" RESET,
        "Quantidade",
        quantidadeMensal,
        quantidadeTrimestral,
        quantidadeSemestral,
        quantidadeAnual);
    printf(CINZA "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);

    pl = lista;
    while(pl != NULL){
        Plano* temp = pl->prox;
        free(pl);
        pl = temp;
    }
    printf(CINZA "\nPressione ENTER para voltar ao menu..." RESET);
    getchar();
}

void relatorioProdutosPorAno(void) {
    FILE *fp = fopen("./dados/dadosProdutos.dat", "rb");
    if (!fp) {
        printf(VERMELHO "❌ Erro: não foi possível abrir './dados/dadosProdutos.dat'\n" RESET);
        printf(CINZA "\nPressione ENTER para voltar...\n" RESET);
        getchar();
        return;
    }

    Produto tmp;
    Produto *lista = NULL;

    
    while (fread(&tmp, sizeof(Produto), 1, fp) == 1) {
        if (tmp.status != True) continue;
        Produto *novo = (Produto*) malloc(sizeof(Produto));
        if (!novo) {
            fclose(fp);
            printf(VERMELHO "❌ Erro de memória!\n" RESET);
            printf(CINZA "\nPressione ENTER para voltar...\n" RESET);
            getchar();
            return;
        }
        *novo = tmp;
        novo->prox = lista;
        lista = novo;
    }
    fclose(fp);

    if (lista == NULL) {
        system("clear||cls");
        printf(BRANCO "╔══════════════════════════════════════════════════════════════╗\n" RESET);
        printf(BRANCO "║                 " AMARELO "RELATÓRIO: PRODUTOS POR FAIXA DE ANO" BRANCO "         ║\n" RESET);
        printf(BRANCO "╠══════════════════════════════════════════════════════════════╣\n" RESET);
        printf(BRANCO "║ " VERMELHO "Nenhum produto cadastrado." BRANCO "                                   ║\n" RESET);
        printf(CINZA "╚══════════════════════════════════════════════════════════════╝\n" RESET);
        printf(CINZA "\nPressione ENTER para voltar...\n" RESET);
        getchar();
        return;
    }

    struct { int ini, fim; const char *titulo; } faixas[5] = {
        {1900, 1950, "1900 - 1950"},
        {1951, 1980, "1951 - 1980"},
        {1981, 2000, "1981 - 2000"},
        {2001, 2010, "2001 - 2010"},
        {2011, 2025, "2011 - 2025"}
    };

    system("clear||cls");
    printf(BRANCO "╔══════════════════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BRANCO "║              " AMARELO "RELATÓRIO: PRODUTOS POR FAIXAS DE ANO (ORDEM INVERSA)" BRANCO "             ║\n" RESET);
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);

    
    for (int f = 0; f < 5; f++) {
        printf(BRANCO "║ Faixa: " CIANO "%-81s" BRANCO " ║\n" RESET, faixas[f].titulo);
        printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);
        printf(AMARELO "║ %-5s │ %-25s │ %-15s │ %-15s │ %-16s ║\n" RESET, "ID", "Nome", "Tipo", "Marca", "Ano");
        printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);

        int encontrou = 0;
        Produto *aux = lista;
        while (aux != NULL) {
            
            char *s = aux->anoProducao;
            while (*s == ' ' || *s == '\t') s++; 
            if (*s == '\0') { aux = aux->prox; continue; }
            int ano = atoi(aux->anoProducao);
            if (ano >= faixas[f].ini && ano <= faixas[f].fim) {
                encontrou = 1;
                printf(BRANCO "║ " CIANO "%-5d" BRANCO " │ %-25s │ %-15s │ %-15s │ %-8s ║\n" RESET,
                    aux->id,
                    aux->nome,
                    aux->tipo,
                    aux->marca,
                    aux->anoProducao);
            }
            aux = aux->prox;
        }

        if (!encontrou) {
            printf(BRANCO "║ " VERMELHO "%-88s" BRANCO " ║\n" RESET, "Nenhum produto encontrado nessa faixa.");
        }

        printf(BRANCO "╠══════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    }

    printf(CINZA "╚══════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);

    
    while (lista != NULL) {
        Produto *tmpNode = lista;
        lista = lista->prox;
        free(tmpNode);
    }

    printf(CINZA "\nPressione ENTER para voltar...\n" RESET);
    getchar();
}

void apagarLista(Assinante **lista){ 
    Assinante *assinante;
    
    while (*lista != NULL){
        assinante = *lista;
        *lista = (*lista)->prox;
        free(assinante);
    }
       
}

void assinantesOrdemAlfabetica(Assinante **lista) {
    FILE *fp;
    Assinante *assinante;


    apagarLista(lista);
    *lista = NULL;

    fp = fopen("./dados/dadosAssinantes.dat", "rb");
    if (fp == NULL) {
        printf(VERMELHO "Erro ao abrir o arquivo de assinantes!\n" RESET);
        exit(1);
    }



    assinante = (Assinante*) malloc(sizeof(Assinante));

    while (fread(assinante, sizeof(Assinante), 1, fp)) {

        if ((*lista == NULL) || (strcmp(assinante->nome, (*lista)->nome) < 0)) {
            assinante->prox = *lista;
            *lista = assinante;
        } else {
            Assinante *ant = *lista;
            Assinante *atu = (*lista)->prox;

            while (atu != NULL && strcmp(atu->nome, assinante->nome) < 0) {
                ant = atu;
                atu = atu->prox;
            }

            ant->prox = assinante;
            assinante->prox = atu;
        }

        assinante = (Assinante*) malloc(sizeof(Assinante));
    }

    free(assinante);
    fclose(fp);
}

void telaAssinantesOrdemAlfabetica(Assinante *aux) {
    int count = 0;
    int encontrou = 0;

    system("clear||cls");

    printf(BRANCO "╔══════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BRANCO "║           " AMARELO "LISTA DE ASSINANTES - ORDEM ALFABÉTICA" BRANCO "                 ║\n" RESET);
    printf(BRANCO "╠══════════════════════════════════════════════════════════════════╣\n" RESET);

    printf(BRANCO "┌────┬────────────────────────────┬────────────────────────────────┐\n" RESET);
    printf(AMARELO "│ Nº │ Nome                       │ CPF                            │\n" RESET);
    printf(BRANCO "├────┼────────────────────────────┼────────────────────────────────┤\n" RESET);

    while (aux != NULL) {
        if (aux->status == True) {
            encontrou = 1;
            count++;
            printf(BRANCO "│ " CIANO "%-2d" BRANCO " │ %-26.26s │ %-30.30s │\n" RESET,
                   count, aux->nome, aux->cpf);
        }
        aux = aux->prox;
    }

    if (!encontrou) {
        printf(BRANCO "│ " VERMELHO "%-63s" BRANCO " │\n" RESET, "Nenhum assinante encontrado.");
    }

    printf(CINZA "└────┴────────────────────────────┴────────────────────────────────┘\n" RESET);

    printf(CINZA "\nPressione ENTER para continuar..." RESET);
    getchar();
}