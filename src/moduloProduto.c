#include <stdlib.h>
#include <stdio.h>
#include "moduloProdutos.h"
#include "moduloPlanos.h"
#include "util.h"
#include <string.h>

#define VERMELHO "\033[1;31m"
#define CIANO    "\033[1;36m"
#define RESET    "\033[0m"
#define CINZA     "\033[1;37m"
#define BRANCO    "\033[0;97m"
#define AMARELO   "\033[1;33m"

void menuProdutos(){
    char opcao[10];
    int crtlProduto = 1;
    do {
        telaProdutos();
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
        switch (opcao[0]){
        case '1':
            cadastroProduto();
        break;
        case '2':
            checarProdutos();
        break;
        case '3':
            alterarProduto();
        break;
        case '4':
            excluirProduto();
        break;
        case '5':
            listarProdutos();
        break;
        case '6':
            crtlProduto = 0;
        break; 
       default:
            printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
            printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
            while (getchar() != '\n');
        break;
       }
    }   
    while (crtlProduto == 1);
}

void telaProdutos(){
    system("clear||cls");
    printf(BRANCO);
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                  ║\n");
    printf("║                 " AMARELO "M Ó D U L O   D E   P R O D U T O S" BRANCO "              ║\n");
    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");

    printf("║   " AMARELO "1." BRANCO " Cadastrar Produtos                            " BRANCO "              ║\n");
    printf("║   " AMARELO "2." BRANCO " Checar Produtos                                 " BRANCO "            ║\n");
    printf("║   " AMARELO "3." BRANCO " Alterar Produtos                                " BRANCO "            ║\n");
    printf("║   " AMARELO "4." BRANCO " Excluir Produtos                                " BRANCO "            ║\n");
    printf("║   " AMARELO "5." BRANCO " Listar Produtos                                  " BRANCO "           ║\n");
    printf("║   " AMARELO "6." BRANCO " Voltar                                           " BRANCO "           ║\n");

    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");

    printf(BRANCO "Digite sua escolha: \n" RESET);
}


void cadastroProduto(){
    system("clear||cls");
    Produto* produto;
    FILE* arqProduto;
    produto = salvarProdutos();
    int confirmador = confirmarInfoProd(produto);
    if ( confirmador == 1){
        arqProduto = fopen("./dados/dadosProdutos.dat", "ab");
        if (arqProduto == NULL){
            printf(VERMELHO "Erro em abrir o arquivo" RESET);
            getchar();
            return;
        }
        fwrite(produto,sizeof(Produto), 1,arqProduto);
        fclose(arqProduto);
        free(produto);
        printf(CIANO "Cadastro realizado com sucesso!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();  
    } else if (confirmador == 2){
        printf(VERMELHO "Cadastro cancelado!\n" RESET); 
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();
    }  
}


void checarProdutos() {
    system("clear||cls");
    int idCom;
    Produto* produto;

    printf(BRANCO "Insira o id do produto: \n" RESET);
    scanf("%d", &idCom);
    getchar();

    produto = recuperarProduto(idCom);

    if (produto != NULL) {
        exibirProduto(produto);
        printf(CINZA "\nPressione Enter para voltar ao módulo de produto\n" RESET);
        getchar();
    } else {
        printf(VERMELHO "Produto não encontrado.\n" RESET);
    }
}


void exibirProduto(const Produto* produto) {
    system("clear||cls");
    printf(BRANCO); 
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║              " AMARELO "D A D O S   D O   P R O D U T O" BRANCO "                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    printf(CINZA "║ Id: %-60d ║\n" RESET, produto->id);
    printf(BRANCO "║ Nome: %-58s ║\n" RESET, produto->nome);
    printf(BRANCO "║ Tipo: %-58s ║\n" RESET, produto->tipo);
    printf(BRANCO "║ Marca: %-57s ║\n" RESET, produto->marca);
    printf(BRANCO "║ Ano de Produção: %-47s ║\n" RESET, produto->anoProducao);

    printf(BRANCO);
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
}


void alterarProduto(){
    system("clear||cls");
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Produto* produto;

    printf(BRANCO "Insira o id do produto que você deseja alterar: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);

    if (!(validarId(idCom, 3))){
        return;
    }

    produto = recuperarProduto(atoi(idCom));

    do {
        if (produto != NULL){
            exibirProduto(produto);
            printf(BRANCO "\nDeseja realmente alterar esse produto?\n" RESET);
            printf(AMARELO "1. Sim\n" RESET);
            printf(VERMELHO "2. Não\n" RESET);
            fgets(opcao, 10, stdin);
            if (opcao[1] != '\n'){
                opcao[0] = 'l';
            }
            switch (opcao[0]){
                case '1':
                    alterarProdutoArquivo(atoi(idCom));
                    controle = 0;
                    break;
                case '2':
                    printf(CINZA "Alteração cancelada.\n" RESET);
                    controle = 0;
                    break;
                default:
                    printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
                    printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
                    getchar();
                    break;
            }
        } else {
            controle = 0;
        }
    } while (controle == 1);
}


void excluirProduto(){
    system("clear||cls");
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Produto* produto;
    printf(BRANCO "Insira o id do produto que você deseja excluir: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);
    if (!(validarId(idCom,3))){
        return;
    }
    produto = recuperarProduto(atoi(idCom));
    do {
        if (produto != NULL){
            exibirProduto(produto);
            
            printf(BRANCO "\nDeseja realmente apagar esse produto?\n" RESET);
            printf(VERMELHO "1. Sim\n" RESET);
            printf(AMARELO "2. Não\n" RESET);
            fgets(opcao,10,stdin);
            if (opcao[1] != '\n'){
                opcao[0] = 'l';
            };
            switch (opcao[0]){
                case '1':
                    excluirProdutoArquivo(atoi(idCom));
                    controle = 0;
                break;
                case '2':
                    printf(CINZA "Exclusão cancelada.\n" RESET);
                    controle = 0;
                break;
                default:
                    printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
                    printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
                    getchar();
                break;
            }
        }else{
            controle = 0;
        }
    }
    while (controle == 1);
}

char confirmarInfoProd(const Produto* produto){
    char opcao[10];
    int controleCI = 1;
    do {
        printf("╔═════════════════════════════╗\n");
        printf("║          " AMARELO "Confirmação" RESET "        ║\n");
        printf("╠═════════════════════════════╝\n");
        printf(BRANCO "║ Id: %d \n" RESET, produto->id);
        printf(BRANCO "║ Nome: %s \n" RESET, produto->nome);
        printf(BRANCO "║ Tipo: %s \n" RESET, produto->tipo);
        printf(BRANCO "║ Marca: %s \n" RESET, produto->marca);
        printf(BRANCO "║ Ano de Produção: %s \n" RESET, produto->anoProducao);
        printf( "╠═════════════════════════════╗\n" RESET);
        printf("║ Deseja manter essas infos?  ║\n");
        printf("║ " AMARELO "1. Sim" RESET "                      ║\n");
        printf("║ " VERMELHO "2. Não" RESET "                      ║\n");
        printf("╚═════════════════════════════╝\n");
        fgets(opcao,10, stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
        switch (opcao[0]) {
            case '1':
                controleCI = 0;
                return 1;
                break;
            case '2':
                controleCI = 0;
                return 2;
                break;
            default:
                printf(VERMELHO "Opção inválida.\n" RESET);
                printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
                getchar();
                break;        
        }
    }
    while (controleCI == 1);
    return 1;
}

Produto* recuperarProduto(int idCom){
    FILE *arqProdutos;
    Produto* produto;
    arqProdutos = fopen("./dados/dadosProdutos.dat", "rt");
    if (arqProdutos == NULL){
        printf(VERMELHO "Erro em Abrir o arquivo" RESET);
        getchar();
        return NULL;
    }
    produto = (Produto*) malloc(sizeof(Produto));
    while (fread(produto,sizeof(Produto),1,arqProdutos)){
        if((idCom == produto->id) && (produto->status == True)){
            fclose(arqProdutos);
            return produto;
        }
    }
    fclose(arqProdutos);
    printf(VERMELHO "O produto com o ID %d não foi encontrado\n" RESET, idCom);
    getchar();
    free(produto);
    return NULL;
}

void excluirProdutoArquivo(int idCom){
    FILE *arqProdutos;
    Produto* produto;
    arqProdutos = fopen("./dados/dadosProdutos.dat", "r+b");
    if (arqProdutos == NULL){
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    produto = (Produto*) malloc(sizeof(Produto));
    while (fread(produto,sizeof(Produto),1,arqProdutos)){

        if((idCom == produto->id) && (produto->status == True)){
            produto->status = False;
            fseek(arqProdutos, -1*sizeof(Produto), SEEK_CUR);
            fwrite(produto,sizeof(Produto),1,arqProdutos);
            fclose(arqProdutos);
            free(produto);

            printf(VERMELHO "Produto excluído com sucesso.\n" RESET);
            printf(CINZA "Aperte Enter para voltar ao menu.\n" RESET);
            getchar();
            return;  
        }
    }

    fclose(arqProdutos);
    free(produto);
}

Produto* salvarProdutos() {
    Produto* produto;
    produto = (Produto*) malloc(sizeof(Produto));
    if (!produto) {
        return NULL;
    }

    produto->id = recuperarIdProdutos();

    do {
        printf(BRANCO "Insira o nome:\n" RESET);
        fgets(produto->nome, 20, stdin);
        tratarString(produto->nome);

        if (!validarNomeObjeto(produto->nome)) {
            printf(VERMELHO "❌ Nome inválido! Digite novamente.\n" RESET);
        }
    } while (!validarNomeObjeto(produto->nome));

    do {
        printf(BRANCO "Insira o tipo:\n" RESET);
        fgets(produto->tipo, 20, stdin);
        tratarString(produto->tipo);
        if (!validarTipo(produto->tipo)) {
            printf(VERMELHO "❌ Tipo inválido! Use apenas letras e espaços.\n" RESET);
        }
    } while (!validarTipo(produto->tipo));


    do {
        printf(BRANCO "Insira a marca:\n" RESET);
        fgets(produto->marca, 20, stdin);
        tratarString(produto->marca);
        if (!validarMarca(produto->marca)) {
            printf(VERMELHO "❌ Marca inválida! Use apenas letras, números e espaços.\n" RESET);
        }
    } while (!validarMarca(produto->marca));

    do {
        printf(BRANCO "Insira o ano de produção (ex: 2023):\n" RESET);
        fgets(produto->anoProducao, 20, stdin);
        tratarString(produto->anoProducao);

        if (!validarAnoProducao(produto->anoProducao)) {
            printf(VERMELHO "❌ Ano inválido! Digite um ano entre 1900 e 2025.\n" RESET);
        }
    } while (!validarAnoProducao(produto->anoProducao));

    produto->status = True;
    return produto;
}

void alterarProdutoArquivo(int idCom){
    char opcao[10];
    int controle = 1;
    system("clear||cls");
    do {
        printf(CIANO "║Qual campo você quer alterar?\n" RESET);
        printf(BRANCO "║1. Nome\n║2. Tipo\n║3. Marca\n║4. Ano de Produção\n" RESET);
        printf(AMARELO "║5. Sair\n" RESET);
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
       switch (opcao[0]){     
        case '1':
            char nomeNovo[100];
            do {
                printf(BRANCO "Insira o nome:\n" RESET);
                fgets(nomeNovo, 20, stdin);
                tratarString(nomeNovo);
                if (!validarNomeObjeto(nomeNovo)) {
                    printf(VERMELHO "❌ Nome inválido! Digite novamente.\n" RESET);
                }
            } while (!validarNomeObjeto(nomeNovo));
            atualizarCampoProduto(idCom, nomeNovo, 1);
            controle = 0;
        break;
        case '2':
            char tipoNovo[20];
            do {
                printf(BRANCO "Insira o tipo:\n" RESET);
                fgets(tipoNovo, 20, stdin);
                tratarString(tipoNovo);
                if (!validarTipo(tipoNovo)) {
                    printf(VERMELHO "❌ Tipo inválido! Use apenas letras e espaços.\n" RESET);
                }
            } while (!validarTipo(tipoNovo));
            atualizarCampoProduto(idCom, tipoNovo, 2);
            controle = 0;
        break;
        case '3':
            char marcaNovo[20];
            do {
                printf(BRANCO "Insira a marca:\n" RESET);
                fgets(marcaNovo, 20, stdin);
                tratarString(marcaNovo);
                if (!validarMarca(marcaNovo)) {
                    printf(VERMELHO "❌ Marca inválida! Use apenas letras, números e espaços.\n" RESET);
                }
            } while (!validarMarca(marcaNovo));
            atualizarCampoProduto(idCom, marcaNovo, 3);
            controle = 0;
        break;
        case '4':
            char anoProdNovo[20];
            do {
                printf(BRANCO "Insira o ano de produção (ex: 2023):\n" RESET);
                fgets(anoProdNovo, 20, stdin);
                tratarString(anoProdNovo);

                if (!validarAnoProducao(anoProdNovo)) {
                    printf(VERMELHO "❌ Ano inválido! Digite um ano entre 1900 e 2025.\n" RESET);
                }
            } while (!validarAnoProducao(anoProdNovo));
            atualizarCampoProduto(idCom, anoProdNovo, 4); 
            controle = 0;
        break;
        case '5':
            controle = 0;
        break; 
       default:
            printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
            printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
            getchar();
        break;
       }
    }
    while (controle == 1);
}

void atualizarCampoProduto(int idCom, const char* novoValor, int tipoCampo) {
    FILE *arqProdutos = fopen("./dados/dadosProdutos.dat", "r+b");
    if (arqProdutos == NULL) {
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    Produto* produto = (Produto*) malloc(sizeof(Produto));
    while (fread(produto, sizeof(Produto), 1, arqProdutos)) {
        if ((idCom == produto->id) && (produto->status == True)) {
            switch (tipoCampo) {
                case 1: 
                    strcpy(produto->nome, novoValor);
                    break;
                case 2: 
                    strcpy(produto->tipo, novoValor);
                    break;
                case 3: 
                    strcpy(produto->marca, novoValor);
                    break;
                case 4:
                    strcpy(produto->anoProducao, novoValor);
                    break;
                default:
                    break;
            }  
            fseek(arqProdutos, -1 * sizeof(Produto), SEEK_CUR);
            fwrite(produto, sizeof(Produto), 1, arqProdutos);        
            printf(CIANO "Produto alterado com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();    
            free(produto);
            fclose(arqProdutos);
            return;
        }
    }
    
    printf(VERMELHO "Produto não encontrado!\n" RESET);
    free(produto);
    fclose(arqProdutos);
}


void listarProdutos(void) {
    FILE *arqProduto;
    Produto* produto;

    system("clear||cls");

    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                        " AMARELO "L I S T A G E M   D E   P R O D U T O S" BRANCO "                                         ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    arqProduto = fopen("./dados/dadosProdutos.dat", "rb");
    if (arqProduto == NULL) {
        printf(VERMELHO "❌ Erro ao abrir o arquivo de produtos!\n" RESET);
        printf(CINZA "Pressione Enter para voltar.\n" RESET);
        getchar();
        return;
    }

    produto = (Produto*) malloc(sizeof(Produto));
    int encontrou = 0;

    printf(BRANCO "┌────────┬────────────────────────────┬────────────────────────────┬────────────────────────────┬────────────────────────┐\n" RESET);
    printf("│  "AMARELO "ID" RESET
       "    │ " AMARELO "Nome" RESET "                       │ "
       AMARELO "Tipo" RESET "                       │ "
       AMARELO "Marca" RESET "                      │ "
       AMARELO "Ano de Produção" RESET "        │\n");

    printf(BRANCO "├────────┼────────────────────────────┼────────────────────────────┼────────────────────────────┼────────────────────────┤\n" RESET);

   
    while (fread(produto, sizeof(Produto), 1, arqProduto)) {
        if (produto->status == True) {
            encontrou = 1;
            printf(BRANCO "│ " CIANO "%-6d" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │ " BRANCO "%-22.22s" BRANCO " │\n" RESET,
                   produto->id,
                   produto->nome,
                   produto->tipo,
                   produto->marca,
                   produto->anoProducao);
        }
    }

    if (encontrou) {
        printf(CINZA "└────────┴────────────────────────────┴────────────────────────────┴────────────────────────────┴────────────────────────┘\n" RESET);
    } else {
        printf(BRANCO "│ " VERMELHO "%-118s" BRANCO " │\n" RESET, "Nenhum produto encontrado.");
        printf(CINZA "└────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n" RESET);
    }

    fclose(arqProduto);
    free(produto);

    printf(CINZA "\nPressione Enter para voltar ao menu.\n" RESET);
    getchar();
}