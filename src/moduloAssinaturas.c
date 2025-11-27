#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define VERMELHO "\033[1;31m"
#define CIANO    "\033[1;36m"
#define RESET    "\033[0m"
#define CINZA     "\033[1;37m"
#define BRANCO    "\033[0;97m"
#define AMARELO   "\033[1;33m"
#include "moduloAssinaturas.h"
#include "moduloAssinantes.h"
#include "moduloPlanos.h"
#include "util.h"

void menuAssinaturas(){
    char opcao[10];
    int crtlAssinatura = 1;
    do {
        telaAssinaturas();
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
        switch (opcao[0]){
        case '1':
            cadastroAssinatura();
        break;
        case '2':
            checarAssinaturas();
        break;
        case '3':
            alterarAssinatura();
        break;
        case '4':
            excluirAssinatura();
        break;
        case '5':
            listarAssinaturas();
        break;
        case '6':
            crtlAssinatura = 0;
        break; 
       default:
            printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
            printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
            getchar();
        break;
       }
    }    
    while (crtlAssinatura == 1);
}

void telaAssinaturas(){
    system("clear||cls");
    printf(BRANCO);
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                  ║\n");
    printf("║             " AMARELO "M Ó D U L O   D E   A S S I N A T U R A S" BRANCO "            ║\n");
    printf("║                                                                  ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");

    printf("║   " AMARELO "1." BRANCO " Cadastrar Assinaturas                        " BRANCO "               ║\n");
    printf("║   " AMARELO "2." BRANCO " Checar Assinaturas                             " BRANCO "             ║\n");
    printf("║   " AMARELO "3." BRANCO " Alterar Assinaturas                            " BRANCO "             ║\n");
    printf("║   " AMARELO "4." BRANCO " Excluir Assinaturas                            " BRANCO "             ║\n");
    printf("║   " AMARELO "5." BRANCO " Listar Assinaturas                            " BRANCO "              ║\n");
    printf("║   " AMARELO "6." BRANCO " Voltar                                         " BRANCO "             ║\n");

    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");

    printf(BRANCO "Digite sua escolha: \n" RESET);
}

void cadastroAssinatura(){
    Assinatura* assinatura;
    FILE* arqAssinaturas;
    assinatura = salvarAssinaturas();
    int confirmador = confirmarInfoAssinatura(assinatura);
    if ( confirmador == 1){
        arqAssinaturas = fopen("./dados/dadosAssinaturas.dat", "ab");
        if (arqAssinaturas == NULL){
            printf(VERMELHO "Erro em abrir o arquivo" RESET);
            getchar();
            return;
        }
        fwrite(assinatura,sizeof(Assinatura), 1,arqAssinaturas);
        fclose(arqAssinaturas);
        free(assinatura);
        printf(CIANO "Cadastro realizado com sucesso!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();  
    } else if (confirmador == 2){
        printf(VERMELHO "Cadastro cancelado!\n" RESET); 
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();
    }  
}

void checarAssinaturas() {
    int idCom;
    Assinatura* assinatura;

    printf(BRANCO "Insira o id da assinatura: \n" RESET);
    scanf("%d", &idCom);
    getchar();

    assinatura = recuperarAssinatura(idCom);

    if (assinatura != NULL) {
        exibirAssinatura(assinatura);
        printf(CINZA "\nPressione Enter para voltar ao módulo de assinatura\n" RESET);
        getchar();
    } else {
        printf(VERMELHO "Assinatura não encontrada.\n" RESET);
    }
}


void exibirAssinatura(const Assinatura* assinatura) {
 system("clear||cls");

    printf(BRANCO); 
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║             " AMARELO "D A D O S   D A   A S S I N A T U R A" BRANCO "                ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    printf(CINZA "║ Id: %-60d ║\n" RESET, assinatura->id);
    printf(BRANCO "║ Id do Assinante: %-47s ║\n" RESET, assinatura->idAssinante);
    printf(BRANCO "║ Id do Plano: %-51s ║\n" RESET, assinatura->idPlano);
    printf(BRANCO "║ Data da Assinatura: %-44s ║\n" RESET, assinatura->dataAssinatura);
    printf(BRANCO "║ Período de Vencimento: %-41s ║\n" RESET, assinatura->periodoVencimento);

    printf(BRANCO);
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);

    printf(CINZA "\n>>> Tecle <ENTER> para continuar...\n" RESET);
    getchar();
}



void alterarAssinatura() {
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Assinatura* assinatura;

    printf(BRANCO "Insira o id da assinatura que você quer alterar: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);

    if (!(validarId(idCom, 3))) {
        return;
    }

    assinatura = recuperarAssinatura(atoi(idCom));

    do {
        if (assinatura != NULL) {
            exibirAssinatura(assinatura);

            printf(BRANCO "\nDeseja realmente alterar essa assinatura?\n" RESET);
            printf(AMARELO "1. Sim\n" RESET);
            printf(VERMELHO "2. Não\n" RESET);
            fgets(opcao, 10, stdin);

            if (opcao[1] != '\n') {
                opcao[0] = 'l'; 
            }

            switch (opcao[0]) {
                case '1':
                    alterarAssinaturaArquivo(atoi(idCom));
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
            printf(VERMELHO "Assinatura não encontrada.\n" RESET);
            controle = 0;
        }
    } while (controle == 1);
}


void excluirAssinatura(){
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Assinatura* assinatura;
    printf(BRANCO "Insira o id da assinatura que você quer excluir: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);
    if (!(validarId(idCom,3))){
        return;
    }
    assinatura = recuperarAssinatura(atoi(idCom));
    do {
        if (assinatura != NULL){
            exibirAssinatura(assinatura);
            printf(BRANCO "\nDeseja realmente excluir essa assinatura?\n" RESET);
            printf(VERMELHO "1. Sim\n" RESET);
            printf(AMARELO "2. Não\n" RESET);
            fgets(opcao,10,stdin);
            if (opcao[1] != '\n'){
                opcao[0] = 'l';
            };
            switch (opcao[0]){
                case '1':
                    excluirAssinaturaArquivo(atoi(idCom));
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

char confirmarInfoAssinatura(const Assinatura* assinatura){
    char opcao[10];
    int controleCI = 1;
    do {
        printf(CIANO "╔═════════════════════════════╗\n" RESET);
        printf(CIANO "║          " AMARELO "Confirmação" CIANO "        ║\n" RESET);
        printf(CIANO "╠═════════════════════════════╝\n" RESET);
        printf(BRANCO "║ ID do Assinante: %s \n" RESET, assinatura->idAssinante);
        printf(BRANCO "║ ID do Plano: %s \n" RESET, assinatura->idPlano);
        printf(BRANCO "║ Data da Assinatura: %s \n" RESET, assinatura->dataAssinatura);
        printf(BRANCO "║ Período de Vencimento: %s \n" RESET, assinatura->periodoVencimento);
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

Assinatura* recuperarAssinatura(int idCom){
    FILE *arqAssinaturas;
    Assinatura* assinatura;
    arqAssinaturas = fopen("./dados/dadosAssinaturas.dat", "rt");
    if (arqAssinaturas == NULL){
        printf(VERMELHO "Erro em Abrir o arquivo" RESET);
        getchar();
        return NULL;
    }
    assinatura = (Assinatura*) malloc(sizeof(Assinatura));
    while (fread(assinatura,sizeof(Assinatura),1,arqAssinaturas)){
        if((idCom == assinatura->id) && (assinatura->status == True)){
            fclose(arqAssinaturas);
            return assinatura;
        }
    }
    fclose(arqAssinaturas);
    printf(VERMELHO "A assinatura com o ID %d não foi encontrado\n" RESET, idCom);
    getchar();
    free(assinatura);
    return NULL;
}

void excluirAssinaturaArquivo(int idCom){
    FILE *arqAssinaturas;
    Assinatura* assinatura;
    arqAssinaturas = fopen("./dados/dadosAssinaturas.dat", "r+b");
    if (arqAssinaturas == NULL){
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    assinatura = (Assinatura*) malloc(sizeof(Assinatura));
    while (fread(assinatura,sizeof(Assinatura),1,arqAssinaturas)){
        if((idCom == assinatura->id) && (assinatura->status == True)){
            assinatura->status = False;
            fseek(arqAssinaturas,-1*sizeof(Assinatura), SEEK_CUR);
            fwrite(assinatura,sizeof(Assinatura),1,arqAssinaturas);
            printf(VERMELHO "Assinatura Excluída com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();
            fclose(arqAssinaturas);
            free(assinatura);
            return;  
        }
    }
}
Assinatura* salvarAssinaturas() {
    Assinatura* assinatura = criarAssinatura();
    if (!assinatura) {
        fprintf(stderr, VERMELHO "Erro ao alocar memória!\n" RESET);
        return NULL;
    }

    preencherAssinatura(assinatura);
    assinatura->status = True;
    return assinatura;
}

Assinatura* criarAssinatura() {
    Assinatura* assinatura = (Assinatura*) malloc(sizeof(Assinatura));
    if (!assinatura) return NULL;

    assinatura->id = recuperarIdAssinaturas();
    return assinatura;
}

void preencherAssinatura(Assinatura* assinatura) {
    int idAss, idPlan;

    do {
        lerCampo(BRANCO "Insira o id do assinante:" RESET, assinatura->idAssinante, 20, validarIdAssinante, VERMELHO "❌ ID inválido!" RESET);
        idAss = atoi(assinatura->idAssinante);

        if (!existeAssinante(idAss)) {
            printf(VERMELHO "❌ Esse assinante NÃO existe! Digite novamente.\n" RESET);
        }
    } while (!existeAssinante(idAss));

    do {
        lerCampo(BRANCO "Insira o id do plano:" RESET, assinatura->idPlano, 20, validarIdPlano, VERMELHO "❌ ID inválido!" RESET);
        idPlan = atoi(assinatura->idPlano);

        if (!existePlano(idPlan)) {
            printf(VERMELHO "❌ Esse plano NÃO existe! Digite novamente.\n" RESET);
        }
    } while (!existePlano(idPlan));

    lerCampo(BRANCO "Insira a data da assinatura (dd/mm/aaaa):" RESET, assinatura->dataAssinatura,
             20, validarDataAssinatura, VERMELHO "❌ Data inválida!" RESET);

    lerCampo(BRANCO "Insira o período de vencimento (M/T/S/A):" RESET, assinatura->periodoVencimento,
             20, validarPeriodoVencimento, VERMELHO "❌ Período inválido!" RESET);
}

void alterarAssinaturaArquivo(int idCom){
    char opcao[10];
    int controle = 1;
    system("clear||cls");
    do {
        printf(CIANO "║Qual campo você quer alterar?\n" RESET);
        printf(BRANCO "║1. Id do Assinante\n║2. Id do Plano\n║3. Data da assinatura\n" RESET);
        printf(BRANCO "║4. Período de vencimento\n" RESET);
        printf(AMARELO "║5. Sair\n" RESET);
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
       switch (opcao[0]){
        case '1':
            char idAssNovo[20];
            int idAss;
            do {
                printf(BRANCO "Insira o novo ID do assinante:\n" RESET);
                fgets(idAssNovo,20,stdin);
                tratarString(idAssNovo); 
                idAss = atoi(idAssNovo);
                if (!(validarId(idAssNovo, 2))) {
                    printf(VERMELHO "❌ ID inválido! Digite novamente.\n" RESET);
                } else if (!existeAssinante(idAss)) {
                    printf(VERMELHO "❌ Esse assinante NÃO existe! Digite novamente.\n" RESET);
                }
            } while (!(validarId(idAssNovo, 2) && existeAssinante(idAss)));  
            atualizarCampoAssinatura(idCom, idAssNovo, 1);
            controle = 0;
        break;
        case '2':
            char idPlanNovo[20];
            int idPlan;
            do {
                printf(BRANCO "Insira o id do plano:\n" RESET);
                fgets(idPlanNovo, 20, stdin);
                tratarString(idPlanNovo);
                idPlan = atoi(idPlanNovo);
                if (!validarId(idPlanNovo, 1)) {
                    printf(VERMELHO "❌ ID inválido! Digite novamente.\n" RESET);
                } else if (!existePlano(idPlan)) {
                    printf(VERMELHO "❌ Esse plano NÃO existe! Digite novamente.\n" RESET);
                }
            } while (!(validarId(idPlanNovo, 1) && existePlano(idPlan)));
            atualizarCampoAssinatura(idCom, idPlanNovo, 2);
            controle = 0;
        break;
        case '3':
            char dataNascNovo[20];
            do {
                printf(BRANCO "Insira a data da assinatura (dd/mm/aaaa):\n" RESET);
                fgets(dataNascNovo, 20, stdin);
                tratarString(dataNascNovo);
                if (!validarDataAssinatura(dataNascNovo)) {
                    printf(VERMELHO "❌ Data inválida! Digite novamente no formato dd/mm/aaaa.\n" RESET);
                }
            } while (!validarDataAssinatura(dataNascNovo));
            atualizarCampoAssinatura(idCom, dataNascNovo,3);
            controle = 0;
        break;
        case '4':
            char periodoVenciNovo[20];
            do {
                printf(BRANCO "Insira o período de vencimento (M - Mensal, T - Trimestral, S - Semestral, A - Anual):\n" RESET);
                fgets(periodoVenciNovo, 20, stdin);
                tratarString(periodoVenciNovo);
                if (!validarPeriodoVencimento(periodoVenciNovo)) {
                    printf(VERMELHO "❌ Período inválido! Digite apenas M, T, S ou A.\n" RESET);
                }
            } while (!validarPeriodoVencimento(periodoVenciNovo));
            atualizarCampoAssinatura(idCom, periodoVenciNovo,4);
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

void atualizarCampoAssinatura(int idCom, const char* novoValor, int campo) {
    FILE *arqAssinaturas = fopen("./dados/dadosAssinaturas.dat", "r+b");
    if (arqAssinaturas == NULL) {
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    
    Assinatura* assinatura = (Assinatura*) malloc(sizeof(Assinatura));
    
    while (fread(assinatura, sizeof(Assinatura), 1, arqAssinaturas)) {
        if ((idCom == assinatura->id) && (assinatura->status == True)) {
            switch (campo) {
                case 1: 
                    strcpy(assinatura->idAssinante, novoValor);
                    break;
                case 2: 
                    strcpy(assinatura->idPlano, novoValor);
                    break;
                case 3: 
                    strcpy(assinatura->dataAssinatura, novoValor);
                    break;
                case 4:
                    strcpy(assinatura->periodoVencimento, novoValor);
                    break;
                case 5: 
                    strcpy(assinatura->periodoVencimento, novoValor);
                    break;
                default:
                    break;
            }
            
            fseek(arqAssinaturas, -1 * sizeof(Assinatura), SEEK_CUR);
            fwrite(assinatura, sizeof(Assinatura), 1, arqAssinaturas);
            
            printf(CIANO "Assinatura alterada com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();
            
            free(assinatura);
            fclose(arqAssinaturas);
            return;
        }
    }
    
    printf(VERMELHO "Assinatura não encontrada!\n" RESET);
    free(assinatura);
    fclose(arqAssinaturas);
}
void listarAssinaturas(void) {
    FILE *arqAssinaturas;
    Assinatura* assinatura;

    system("clear||cls");

    printf(BRANCO);
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║            " AMARELO "L I S T A G E M   D E   A S S I N A T U R A S" BRANCO "         ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    arqAssinaturas = fopen("./dados/dadosAssinaturas.dat", "rb");
    if (arqAssinaturas == NULL) {
        printf(VERMELHO "❌ Erro ao abrir o arquivo de assinaturas!\n" RESET);
        printf(CINZA "Pressione Enter para voltar.\n" RESET);
        getchar();
        return;
    }

    assinatura = (Assinatura*) malloc(sizeof(Assinatura));
    int encontrou = 0;

    printf(BRANCO "┌────────┬──────────────┬──────────────┬───────────────────────────┐\n" RESET);
    printf(AMARELO "│  ID    │ ID Assinante │ ID Plano     │ Data Assinatura           │\n" RESET);
    printf(BRANCO "├────────┼──────────────┼──────────────┼───────────────────────────┤\n" RESET);

    while (fread(assinatura, sizeof(Assinatura), 1, arqAssinaturas)) {
        if (assinatura->status == True) {
            encontrou = 1;
            printf(BRANCO "│ " CIANO "%-6d" BRANCO " │ " CIANO "%-12s" BRANCO " │ " CIANO "%-12s" BRANCO " │ " BRANCO "%-25s" BRANCO " │\n" RESET,
                   assinatura->id,
                   assinatura->idAssinante,
                   assinatura->idPlano,
                   assinatura->dataAssinatura);
        }
    }
    if (encontrou) {
        printf(CINZA "└────────┴──────────────┴──────────────┴───────────────────────────┘\n" RESET);
    } else {
        printf(BRANCO "│ " VERMELHO "%-56s" BRANCO " │\n" RESET, "Nenhuma assinatura encontrada.");
        printf(CINZA "└──────────────────────────────────────────────────────────┘\n" RESET);
    }

    fclose(arqAssinaturas);
    free(assinatura);

    printf(CINZA "\nPressione Enter para voltar ao menu.\n" RESET);
    getchar();
}