#include <stdlib.h>
#include <stdio.h>
#include "moduloPlanos.h"
#include "moduloProdutos.h"
#include "util.h"
#include <string.h>
#include <ctype.h>
#define RESET     "\033[0m"
#define VERMELHO  "\033[1;31m"
#define CINZA     "\033[1;37m"
#define BRANCO    "\033[0;97m"
#define AMARELO   "\033[1;33m"
#define CIANO    "\033[1;36m"

void menuPlanos(){
    char opcao[10];
    int crtlPlano = 1;
    do {
        telaPlano();
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
        switch (opcao[0]){
        case '1':
            cadastroPlano();
        break;
        case '2':
            checarPlanos();
        break;
        case '3':
            alterarPlano();
        break;
        case '4':
            excluirPlano();
        break;
        case '5':
            listarPlanos();
        break;
        case '6':
            crtlPlano = 0;
        break; 
       default:
            printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
            printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
            getchar();
        break;
       }
    }   
    while (crtlPlano == 1);
}

void telaPlano(){
    system("clear||cls");
    printf(BRANCO);
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                  ║\n");
    printf("║                " AMARELO "M Ó D U L O   D E   P L A N O S" BRANCO "                   ║\n");
    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");

    printf("║   " AMARELO "1." BRANCO " Cadastrar Plano                                " BRANCO "             ║\n");
    printf("║   " AMARELO "2." BRANCO " Checar Planos                                  " BRANCO "             ║\n");
    printf("║   " AMARELO "3." BRANCO " Alterar Plano                                   " BRANCO "            ║\n");
    printf("║   " AMARELO "4." BRANCO " Excluir Plano                                   " BRANCO "            ║\n");
    printf("║   " AMARELO "5." BRANCO " Listar Planos                                    " BRANCO "           ║\n");
    printf("║   " AMARELO "6." BRANCO " Voltar                                           " BRANCO "           ║\n");

    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");

    printf(BRANCO "Digite sua escolha: \n" RESET);
}

void cadastroPlano(){
    Plano* plano;
    FILE* arqPlano;
    plano = salvarPlanos();
    int confirmador = confirmarInfoPlano(plano);
    if ( confirmador == 1){
        arqPlano = fopen("./dados/dadosPlanos.dat", "ab");
        if (arqPlano == NULL){
            printf(VERMELHO "Erro em abrir o arquivo" RESET);
            getchar();
            return;
        }
        fwrite(plano,sizeof(Plano), 1,arqPlano);
        fclose(arqPlano);
        free(plano);
        printf(CIANO "Cadastro realizado com sucesso!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();  
    } else if (confirmador == 2){
        printf(VERMELHO "Cadastro cancelado!\n" RESET); 
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();
    }  
}


void checarPlanos() {
    int idCom;
    Plano* plano;

    printf(BRANCO "Insira o id do plano: \n" RESET);
    scanf("%d", &idCom);
    getchar();

    plano = recuperarPlano(idCom);

    if (plano != NULL) {
        exibirPlano(plano);
        printf(CINZA "\nPressione Enter para voltar ao módulo de plano\n" RESET);
        getchar();
    } else {
        printf(VERMELHO "Plano não encontrado.\n" RESET);
    }
}


void exibirPlano(const Plano* plano) {
    system("clear||cls");
    printf(BRANCO); 
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║               " AMARELO "   D A D O S   D O   P L A N O" BRANCO "                     ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    printf(CINZA "║ Id: %-60d ║\n" RESET, plano->id);
    printf(BRANCO "║ Nome: %-58s ║\n" RESET, plano->nome);
    printf(BRANCO "║ Preço: %-57s ║\n" RESET, plano->preco);
    printf(BRANCO "║ Período: %-55s ║\n" RESET, plano->periodo);
    printf(BRANCO "║ Id do Produto: %-49s ║\n" RESET, plano->idProduto);

    printf(BRANCO);
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);

    printf(CINZA "\n>>> Tecle <ENTER> para continuar...\n" RESET);
    getchar();
}


void alterarPlano() {
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Plano* plano;

    printf(BRANCO "Insira o id do plano que você deseja alterar: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);

    if (!(validarId(idCom, 3))) {
        return;
    }

    plano = recuperarPlano(atoi(idCom));

    do {
        if (plano != NULL) {
            exibirPlano(plano);

            printf(BRANCO "\nDeseja realmente alterar esse plano?\n" RESET);
            printf(AMARELO "1. Sim\n" RESET);
            printf(VERMELHO "2. Não\n" RESET);
            fgets(opcao, 10, stdin);

            if (opcao[1] != '\n') {
                opcao[0] = 'l'; 
            }

            switch (opcao[0]) {
                case '1':
                    alterarPlanoArquivo(atoi(idCom));
                    controle = 0;
                    break;
                case '2':
                    printf(CINZA "Alteração cancelada.\n" RESET);
                    controle = 0;
                    break;
                default:
                    printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
                    printf(CINZA "\nPressione Enter para tentar novamente\n" RESET);
                    getchar();
                    break;
            }
        } else {
            printf(VERMELHO "Plano não encontrado.\n" RESET);
            controle = 0;
        }
    } while (controle == 1);
}


void excluirPlano(){
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Plano* plano;
    printf(BRANCO "Insira o id do plano que você excluir: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);
    if (!(validarId(idCom,3))){
        return;
    }
    plano = recuperarPlano(atoi(idCom));
    do {
        if (plano != NULL){
            exibirPlano(plano);
            printf(BRANCO "\nDeseja realmente apagar esse plano?\n" RESET);
            printf(VERMELHO "1. Sim\n" RESET);
            printf(AMARELO "2. Não\n" RESET);
            fgets(opcao,10,stdin);
            if (opcao[1] != '\n'){
                opcao[0] = 'l';
            };
            switch (opcao[0]){
                case '1':
                    excluirPlanoArquivo(atoi(idCom));
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
char confirmarInfoPlano(const Plano* plano){
    char opcao[10];
    int controleCI = 1;
    do {
        printf(CIANO "╔═════════════════════════════╗\n" RESET);
        printf(CIANO "║          " AMARELO "Confirmação" CIANO "        ║\n" RESET);
        printf(CIANO "╠═════════════════════════════╝\n" RESET);
        printf(BRANCO "║ Id: %d \n" RESET, plano->id);
        printf(BRANCO "║ Nome: %s \n" RESET, plano->nome);
        printf(BRANCO "║ Preço: %s \n" RESET, plano->preco);
        printf(BRANCO "║ Período: %s \n" RESET, plano->periodo);
        printf(BRANCO "║ Id do produto: %s \n" RESET, plano->idProduto);
        printf(CIANO "╠═════════════════════════════╗\n" RESET);
        printf(BRANCO "║ Deseja manter essas infos?  ║\n" RESET);
        printf(AMARELO "║ 1. Sim                      ║\n" RESET);
        printf(VERMELHO "║ 2. Não                      ║\n" RESET);
        printf(CIANO "╚═════════════════════════════╝\n" RESET);
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

Plano* recuperarPlano(int idCom){
    FILE *arqPlanos;
    Plano* plano;
    
    arqPlanos = fopen("./dados/dadosPlanos.dat", "rb");
    if (arqPlanos == NULL){
        printf(VERMELHO "Erro em Abrir o arquivo\n" RESET);
        getchar();
        return NULL;
    }
    
    plano = (Plano*) malloc(sizeof(Plano));
    if (plano == NULL) {
        printf(VERMELHO "Erro de alocação de memória.\n" RESET);
        fclose(arqPlanos);
        getchar();
        return NULL;
    }

    while (fread(plano, sizeof(Plano), 1, arqPlanos)){
        if((idCom == plano->id) && (plano->status == True)){
            fclose(arqPlanos);
            return plano; 
        }
    }

    fclose(arqPlanos);
    printf(VERMELHO "O plano com o ID %d não foi encontrado\n" RESET, idCom);
    getchar();
    
    free(plano); 
    return NULL;
}

Plano* quantidadePlanos(void) {
    FILE *arqPlanos;
    Plano *planoLido;
    Plano *lista = NULL; 
    Plano *ultimo = NULL; 

    arqPlanos = fopen("./dados/dadosPlanos.dat", "rb");
    if (arqPlanos == NULL) {
        return NULL;
    }

    planoLido = (Plano*) malloc(sizeof(Plano));
    if (planoLido == NULL) {
        fclose(arqPlanos);
        return NULL;
    }

    while (fread(planoLido, sizeof(Plano), 1, arqPlanos)) {
        if (planoLido->status == 1) { 
            
            Plano *novoPlano = (Plano*) malloc(sizeof(Plano));
            if (novoPlano == NULL) {
                free(planoLido);
                fclose(arqPlanos);
                
                Plano *atual = lista;
                while (atual != NULL) {
                    Plano *temp = atual->prox;
                    free(atual);
                    atual = temp;
                }
                return NULL;
            }
            
            memcpy(novoPlano, planoLido, sizeof(Plano));
            novoPlano->prox = NULL; 

            if (lista == NULL) {
                lista = novoPlano;
            } else {
                ultimo->prox = novoPlano;
            }
            ultimo = novoPlano;
        }
    }
    
    free(planoLido);
    fclose(arqPlanos);
    return lista;
}

void excluirPlanoArquivo(int idCom){
    FILE *arqPlanos;
    Plano* plano;
    arqPlanos = fopen("./dados/dadosPlanos.dat", "r+b");
    if (arqPlanos == NULL){
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    plano = (Plano*) malloc(sizeof(Plano));
    while (fread(plano,sizeof(Plano),1,arqPlanos)){
        if((idCom == plano->id) && (plano->status == True)){
            plano->status = False;
            fseek(arqPlanos,-1*sizeof(Plano), SEEK_CUR);
            fwrite(plano,sizeof(Plano),1,arqPlanos);
            printf(VERMELHO "Plano Excluído com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();
            fclose(arqPlanos);
            free(plano);
            return;  
        }
    }
}

Plano* salvarPlanos() {
    Plano* plano = criarPlano();
    if(!plano) {
        fprintf(stderr, VERMELHO "Erro ao alocar memória!\n" RESET);
        return NULL;
    }
    preencherPlano(plano);
    plano->status = True;
    return plano;
}

Plano* criarPlano() {
    Plano* plano = (Plano*) malloc(sizeof(Plano));
    if(!plano) return NULL;

    plano->id = recuperarIdPlanos();
    return plano;
}
void preencherPlano(Plano* plano) {
    lerCampo(BRANCO "Insira o nome:" RESET, plano->nome, 20, validarNomeObjeto, VERMELHO "❌ Nome de produto inválido! Digite novamente." RESET);
    lerCampo(BRANCO "Insira o preço (ex: 49.90 ou 49,90):" RESET, plano->preco, 20, validarPreco, VERMELHO "❌ Preço inválido! Digite novamente." RESET);

    lerCampo(BRANCO "Insira o período (M - Mensal, T - Trimestral, S - Semestral, A - Anual):" RESET,
             plano->periodo, 20, validarPeriodoVencimento,
             VERMELHO "❌ Período inválido! Digite apenas M, T, S ou A." RESET);
    char letra = toupper(plano->periodo[0]);
    switch (letra) {
        case 'M': strcpy(plano->periodo, "Mensal"); break;
        case 'T': strcpy(plano->periodo, "Trimestral"); break;
        case 'S': strcpy(plano->periodo, "Semestral"); break;
        case 'A': strcpy(plano->periodo, "Anual"); break;
        default:  strcpy(plano->periodo, "Desconhecido");
    }

     int idProd;

    do {
        lerCampo(BRANCO "Insira o ID do produto:" RESET, plano->idProduto, 20, NULL, "");

        idProd = atoi(plano->idProduto);

        if (!existeProduto(idProd))
            printf(VERMELHO "❌ Esse produto NÃO existe! Digite novamente.\n" RESET);

    } while (!existeProduto(idProd));
}

void alterarPlanoArquivo(int idCom){
    char opcao[10];
    int controle = 1;
    system("clear||cls");
    do {
        printf(CIANO "║Qual campo você quer alterar?\n" RESET);
        printf(BRANCO "║1. Nome\n║2. Preço\n║3. Período\n║4.Id do Produto\n" RESET);
        printf(AMARELO "║5. Sair\n" RESET);
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
       switch (opcao[0]){
        
        case '1':
            char nomeNovo[20];
            do {
                printf(BRANCO "Insira o nome:\n" RESET);
                fgets(nomeNovo, 20, stdin);
                tratarString(nomeNovo);
                if (!validarNomeObjeto(nomeNovo)) {
                    printf(VERMELHO "❌ Nome de produto inválido! Digite novamente.\n" RESET);
                }
            } while (!validarNomeObjeto(nomeNovo));
            atualizarCampoPlano(idCom, nomeNovo, 1);
            controle = 0;
        break;
        case '2':
            char precoNovo[20];
            do {
                printf(BRANCO "Insira o preço (ex: 49.90 ou 49,90):\n" RESET);
                fgets(precoNovo, 20, stdin);
                tratarString(precoNovo);
                if (!validarPreco(precoNovo)) {
                    printf(VERMELHO "❌ Preço inválido! Digite apenas números e no máximo um separador decimal (',' ou '.').\n" RESET);
                }
            } while (!validarPreco(precoNovo));
            atualizarCampoPlano(idCom, precoNovo, 2);
            controle = 0;
        break;
        case '3':
            char periodoNovo[20];
            do {
                printf(BRANCO "Insira o período (M - Mensal, T - Trimestral, S - Semestral, A - Anual):\n" RESET);
                fgets(periodoNovo, 20, stdin);
                tratarString(periodoNovo);
                if (!validarPeriodoVencimento(periodoNovo)) {
                    printf(VERMELHO "❌ Período inválido! Digite apenas M, T, S ou A (ou o nome completo, ex: Mensal).\n" RESET);
                }
            } while (!validarPeriodoVencimento(periodoNovo));
            atualizarCampoPlano(idCom, periodoNovo, 3);
            controle = 0;
        break;
        case '4':
            char idProdNovo[20];
            int idProd;
            do {
                printf(BRANCO "Insira o novo ID do produto:\n" RESET);
                fgets(idProdNovo,20,stdin);
                tratarString(idProdNovo);
                idProd = atoi(idProdNovo);
                if (!(validarId(idProdNovo, 2))) {
                    printf(VERMELHO "❌ ID inválido! Digite novamente.\n" RESET);
                } else if (!existeProduto(idProd)) {
                    printf(VERMELHO "❌ Esse produto NÃO existe! Digite novamente.\n" RESET);
                }
            } while (!(validarId(idProdNovo, 2) && existeProduto(idProd)));  
            atualizarCampoPlano(idCom, idProdNovo, 4);
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

void atualizarCampoPlano(int idCom, const char* novoValor, int campo) {
    FILE *arqPlanos = fopen("./dados/dadosPlanos.dat", "r+b");
    if (arqPlanos == NULL) {
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }   
    Plano* plano = (Plano*) malloc(sizeof(Plano));
    
    while (fread(plano, sizeof(Plano), 1, arqPlanos)) {
        if ((idCom == plano->id) && (plano->status == True)) {
            switch (campo) {
                case 1: 
                    strcpy(plano->nome, novoValor);
                    break;
                case 2: 
                    strcpy(plano->preco, novoValor);
                    break;
                case 3: 
                    // Se for período, atualiza o valor completo (Mensal, Anual, etc.)
                    if (validarPeriodoVencimento(novoValor)) {
                        char letra = toupper(novoValor[0]);
                        switch (letra) {
                            case 'M': strcpy(plano->periodo, "Mensal"); break;
                            case 'T': strcpy(plano->periodo, "Trimestral"); break;
                            case 'S': strcpy(plano->periodo, "Semestral"); break;
                            case 'A': strcpy(plano->periodo, "Anual"); break;
                            default:  strcpy(plano->periodo, novoValor); // Mantém o valor se for o nome completo
                        }
                    } else {
                        strcpy(plano->periodo, novoValor);
                    }
                    break;
                case 4: 
                    strcpy(plano->idProduto, novoValor);
                    break;
                default:
                    break;
            }
            
            fseek(arqPlanos, -1 * sizeof(Plano), SEEK_CUR);
            fwrite(plano, sizeof(Plano), 1, arqPlanos);
            
            printf(CIANO "Plano alterado com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();
            
            free(plano);
            fclose(arqPlanos);
            return;
        }
    }
    printf(VERMELHO "Plano não encontrado!\n" RESET);
    free(plano);
    fclose(arqPlanos);
}

void listarPlanos(void) {
    FILE *arqPlano;
    Plano* plano;

    system("clear||cls");

    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                                        " AMARELO "L I S T A G E M   D E   P L A N O S" BRANCO "                                             ║\n");
    printf("╠════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    arqPlano = fopen("./dados/dadosPlanos.dat", "rb");
    if (arqPlano == NULL) {
        printf(VERMELHO "❌ Erro ao abrir o arquivo de planos!\n" RESET);
        printf(CINZA "Pressione Enter para voltar.\n" RESET);
        getchar();
        return;
    }

    plano = (Plano*) malloc(sizeof(Plano));
    int encontrou = 0;

    printf(BRANCO "┌────────┬────────────────────────────┬────────────────────────────┬────────────────────────────┬────────────────────────┐\n" RESET);
    printf(AMARELO "│   ID   │ Nome                       │ Preço                      │ Período                    │ ID Produto             │\n" RESET);
    printf(BRANCO "├────────┼────────────────────────────┼────────────────────────────┼────────────────────────────┼────────────────────────┤\n" RESET);

    while (fread(plano, sizeof(Plano), 1, arqPlano)) {
        if (plano->status == True) {
            encontrou = 1;
            printf(BRANCO "│ " CIANO "%-6d" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │ " CIANO "%-26.26s" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │ " CIANO "%-22.22s" BRANCO " │\n" RESET,
                   plano->id,
                   plano->nome,
                   plano->preco,
                   plano->periodo,
                   plano->idProduto);
        }
    }

    if (encontrou) {
        printf(CINZA "└────────┴────────────────────────────┴────────────────────────────┴────────────────────────────┴────────────────────────┘\n" RESET);
    } else {
        printf(BRANCO "│ " VERMELHO "%-108s" BRANCO " │\n" RESET, "Nenhum plano encontrado.");
        printf(CINZA "└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n" RESET);
    }

    fclose(arqPlano);
    free(plano);

    printf(CINZA "\nPressione Enter para voltar ao menu.\n" RESET);
    getchar();
}