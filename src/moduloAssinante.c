#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "moduloAssinantes.h"
#include "util.h"
#define RESET     "\033[0m"
#define VERMELHO  "\033[1;31m"
#define CINZA     "\033[1;37m"
#define CIANO    "\033[1;36m"
#define BRANCO    "\033[0;97m"
#define AMARELO   "\033[1;33m"

void menuAssinante(){
    char opcao[10];
    int crtlAssinante = 1;
    do {
        telaAssinante();
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
       switch (opcao[0]){
        case '1':
            cadastrarAssinante();
        break;
        case '2':
            checarAssinantes();
        break;
        case '3':
            alterarAssinante();
        break;
        case '4':
            excluirAssinante();
        break;
        case '5':
            listarAssinantes();
        break;
        case '6':
            crtlAssinante = 0;
        break; 
       default:
            printf(VERMELHO "Você inseriu uma opção inválida\n" RESET);
            printf(CINZA "\nPressione Enter para tentar novamente \n" RESET);
            getchar();
        break;
       }
    }
    while (crtlAssinante == 1);
}

void telaAssinante() {
    system("clear||cls");

    printf(BRANCO);
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                                                        ║\n");
    printf("║         " AMARELO "M Ó D U L O   D E   A S S I N A N T E S" BRANCO "        ║\n"); // Título em Amarelo
    printf("║                                                        ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");

    printf("║   " AMARELO "1." BRANCO " Cadastrar Assinantes                           " BRANCO "   ║\n");
    printf("║   " AMARELO "2." BRANCO " Checar Assinantes                              " BRANCO "   ║\n");
    printf("║   " AMARELO "3." BRANCO " Alterar Assinantes                             " BRANCO "   ║\n");
    printf("║   " AMARELO "4." BRANCO " Excluir Assinantes                             " BRANCO "   ║\n");
    printf("║   " AMARELO "5." BRANCO " Listar Assinantes                              " BRANCO "   ║\n");
    printf("║   " AMARELO "6." BRANCO " Voltar                                         " BRANCO "   ║\n");

    printf("╚════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");

    printf(BRANCO "Digite sua escolha: " RESET);
}

void cadastrarAssinante(){
    system("clear||cls");
    Assinante* assinante;
    FILE* arqAssinante;
    assinante = salvarAssinantes();
    int confirmador = confirmarInfoAss(assinante);
    if ( confirmador == 1){
        arqAssinante = fopen("./dados/dadosAssinantes.dat", "ab");
        if (arqAssinante == NULL){
            printf(VERMELHO "Erro em abrir o arquivo" RESET);
            getchar();
            return;
        }
        fwrite(assinante,sizeof(Assinante), 1,arqAssinante);
        fclose(arqAssinante);
        free(assinante);
        printf(CIANO "Cadastro realizado com sucesso!\n" RESET);
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();  
    } else if (confirmador == 2){
        printf(VERMELHO "Cadastro cancelado!\n" RESET); 
        printf(CINZA "\nPressione Enter para voltar \n" RESET);
        getchar();
    }  
}


void checarAssinantes() {
    system("clear||cls");
    int idCom;
    Assinante* assinante;
    printf(BRANCO "Insira o id do assinante: \n" RESET);
    scanf("%d", &idCom);
    getchar(); 
    assinante = recuperarAssinante(idCom);
    if (assinante != NULL) {
        exibirAssinante(assinante);
        printf(CINZA "\nPressione Enter para voltar ao módulo de assinantes\n" RESET);
        getchar();
    } else {
        printf(VERMELHO "Assinante não encontrado.\n" RESET);
    }
}



void exibirAssinante(const Assinante* assinante) {
    system("clear||cls");
    printf(BRANCO); 
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                   " AMARELO "D A D O S   D O   A S S I N A N T E" BRANCO "            ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf(RESET); 
    printf(CINZA "║ Id: %-60d ║\n" RESET, assinante->id);                      
    printf(BRANCO "║ Nome: %-58s ║\n" RESET, assinante->nome);
    printf(BRANCO "║ Email: %-57s ║\n" RESET, assinante->email);
    printf(BRANCO "║ CPF: %-59s ║\n" RESET, assinante->cpf);
    printf(BRANCO "║ Data de Nascimento: %-44s ║\n" RESET, assinante->dataNascimento);
    printf(BRANCO "║ Endereço: %-54s ║\n" RESET, assinante->endereco );
    printf(RESET); 
    printf(BRANCO); 
    printf("╚══════════════════════════════════════════════════════════════════╝\n");
    printf(RESET);
    printf(CINZA "\n>>> Tecle <ENTER> para continuar...\n" RESET);
    getchar();
}

void alterarAssinante() {
    system("clear||cls");
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Assinante* assinante;
    printf(BRANCO "Insira o id do assinante que você deseja alterar: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);
    if (!(validarId(idCom, 3))) {
        return;
    }
    assinante = recuperarAssinante(atoi(idCom));
    do {
        if (assinante != NULL) {
            exibirAssinante(assinante);
            printf(BRANCO "\nDeseja realmente alterar esse assinante?\n" RESET);
            printf(AMARELO "1. Sim\n" RESET);
            printf(VERMELHO "2. Não\n" RESET);
            fgets(opcao, 10, stdin);

            if (opcao[1] != '\n') {
                opcao[0] = 'l';
            }
            switch (opcao[0]) {
                case '1':
                    alterarAssinanteArquivo(atoi(idCom));
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
            printf(VERMELHO "Assinante não encontrado.\n" RESET);
            controle = 0;
        }
    } while (controle == 1);
}

void excluirAssinante(){
    system("clear||cls");
    char opcao[10];
    int controle = 1;
    char idCom[10];
    Assinante* assinante;
    printf(BRANCO "Insira o id do assinante que você excluir: \n" RESET);
    fgets(idCom, 10, stdin);
    tratarString(idCom);
    if (!(validarId(idCom,3))){
        return;
    }
    assinante = recuperarAssinante(atoi(idCom));
    do {
        if (assinante != NULL){
            exibirAssinante(assinante);
            printf(BRANCO "\nDeseja realmente apagar esse assinante?\n" RESET);
            printf(VERMELHO "1. Sim\n" RESET);
            printf(AMARELO "2. Não\n" RESET);
            fgets(opcao,10,stdin);
            if (opcao[1] != '\n'){
                opcao[0] = 'l';
            };
            switch (opcao[0]){
                case '1':
                    excluirAssinanteArquivo(atoi(idCom));
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

int confirmarInfoAss(const Assinante* assinante){
    char opcao[10];
    int controleCI = 1;
    do {
        printf("╔═════════════════════════════╗\n");
        printf("║          " AMARELO "Confirmação" RESET "        ║\n");
        printf("╠═════════════════════════════╝\n");
        printf("║ Nome: %s\n", assinante->nome);
        printf("║ Email: %s\n", assinante->email);
        printf("║ CPF: %s\n", assinante->cpf);
        printf("║ Data: %s\n", assinante->dataNascimento);
        printf("║ Endereço: %s\n", assinante->endereco);
        printf("╠═════════════════════════════╗\n");
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

Assinante* salvarAssinantes() {
    Assinante* a = criarAssinante();
    if (!a) {
        fprintf(stderr, VERMELHO "Erro ao alocar memória!\n" RESET);
        return NULL;
    }

    preencherAssinante(a);  
    a->status = True;
    return a;
}

Assinante* criarAssinante() {
    Assinante* a = (Assinante*) malloc(sizeof(Assinante));
    if (!a) {
        return NULL;
    }

    a->id = recuperarIdAssinantes();
    return a;
}

void preencherAssinante(Assinante* a) {
    lerCampo(BRANCO "Insira o nome do Assinante:" RESET, a->nome, 100, validarNome, VERMELHO "❌ Nome inválido! Digite novamente." RESET);
    lerCampo(BRANCO "Insira o email:" RESET, a->email, 100, validarEmail, VERMELHO "❌ Email inválido! Digite novamente." RESET);
    lerCampo(BRANCO "Insira o CPF:" RESET, a->cpf, 20, validar_cpf, VERMELHO "❌ CPF inválido! Digite novamente." RESET);
    lerCampo(BRANCO "Insira a data de nascimento (dd/mm/aaaa):" RESET, a->dataNascimento, 20, validarDataNascimento, VERMELHO "❌ Data inválida! Digite novamente." RESET);
    lerCampo(BRANCO "Insira o endereço (Cidade, Bairro, Rua, Número):" RESET, a->endereco, 100, validarEndereco, VERMELHO "❌ Endereço inválido! Digite novamente." RESET);
}


Assinante* recuperarAssinante(int idCom){
    FILE *arqAssinantes;
    Assinante* assinante;
    arqAssinantes = fopen("./dados/dadosAssinantes.dat", "rb");
    if (arqAssinantes == NULL){
        printf(VERMELHO "Erro em Abrir o arquivo" RESET);
        getchar();
        return NULL;
    }
    assinante = (Assinante*) malloc(sizeof(Assinante));
    while (fread(assinante,sizeof(Assinante),1,arqAssinantes)){ // ponteiro do arquivo, tamanho do bloco, numero de blocos, arquivo, lê os dados do arquivo 
        if((idCom == assinante->id) && (assinante->status == True)){
            fclose(arqAssinantes);
            return assinante;
        }
    }
    fclose(arqAssinantes);
    printf(VERMELHO "O assinante com o ID %d não foi encontrado\n" RESET, idCom);
    getchar();
    free(assinante);
    return NULL;
}

void excluirAssinanteArquivo(int idCom){
    FILE *arqAssinantes;
    Assinante* assinante;
    arqAssinantes = fopen("./dados/dadosAssinantes.dat", "r+b");
    if (arqAssinantes == NULL){
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    assinante = (Assinante*) malloc(sizeof(Assinante));
    while (fread(assinante,sizeof(Assinante),1,arqAssinantes)){
        if((idCom == assinante->id) && (assinante->status == True)){
            assinante->status = False;
            fseek(arqAssinantes,-1*sizeof(Assinante), SEEK_CUR);
            fwrite(assinante,sizeof(Assinante),1,arqAssinantes);
            printf(VERMELHO "Assinante Excluído com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();
            fclose(arqAssinantes);
            free(assinante);
            return;  
        }
    }
}

void alterarAssinanteArquivo(int idCom){
    char opcao[10];
    int controle = 1;
    system("clear||cls");
    do {
        printf(CIANO "║Qual campo você quer alterar?\n" RESET);
        printf(BRANCO "║1. Nome\n║2. Email\n║3. CPF\n║4. Data de nascimento\n║5. Endereço\n" RESET);
        printf(AMARELO "║6. Voltar\n" RESET);
        fgets(opcao,10,stdin);
        if (opcao[1] != '\n'){
            opcao[0] = 'l';
        };
       switch (opcao[0]){
        case '1':
            char nomeNovo[100];
            do {
                printf(BRANCO "Insira o nome do Assinante:\n" RESET);
                fgets(nomeNovo, 100, stdin);
                tratarString(nomeNovo); 
                if (!validarNome(nomeNovo)) {
                    printf(VERMELHO "❌ Nome inválido! Digite novamente.\n" RESET);
                }
            } while (!validarNome(nomeNovo));
            atualizarCampoAssinante(idCom, nomeNovo, 1);
            controle = 0;
        break;
        case '2':
            char emailNovo[100];
            do {
                printf(BRANCO "Insira o email:\n" RESET);
                fgets(emailNovo, 100, stdin);
                tratarString(emailNovo);
                if (!validarEmail(emailNovo)) {
                    printf(VERMELHO "❌ Email inválido! Digite novamente.\n" RESET);
                }
            } while (!validarEmail(emailNovo));
            atualizarCampoAssinante(idCom, emailNovo,2);
            controle = 0;
        break;
        case '3':
            char cpfNovo[20];
            do {
                printf(BRANCO "Insira o CPF:\n" RESET);
                fgets(cpfNovo, 20, stdin);
                tratarString(cpfNovo);
                if (!validar_cpf(cpfNovo)) {
                    printf(VERMELHO "❌ CPF inválido! Digite novamente.\n" RESET);
                }
            } while (!validar_cpf(cpfNovo));
            atualizarCampoAssinante(idCom, cpfNovo, 3);
            controle = 0;
        break;
        case '4':
            char dataNascimentoNovo[20];
            do {
                printf(BRANCO "Insira a data de nascimento (dd/mm/aaaa):\n" RESET);
                fgets(dataNascimentoNovo, 20, stdin);
                tratarString(dataNascimentoNovo);
                if (!validarDataNascimento(dataNascimentoNovo)) {
                    printf(VERMELHO "❌ Data inválida! Digite novamente no formato dd/mm/aaaa.\n" RESET);
                }
            } while (!validarDataNascimento(dataNascimentoNovo));
            atualizarCampoAssinante(idCom, dataNascimentoNovo, 4);
            controle = 0;
        break;
        case '5':
            char enderecoNovo[100];
            do {
                printf(BRANCO "Insira o endereço (Cidade, Bairro, Rua, Número):\n" RESET);
                fgets(enderecoNovo, 100, stdin);
                tratarString(enderecoNovo);
                if (!validarEndereco(enderecoNovo)) {
                    printf(VERMELHO "❌ Endereço inválido! Digite novamente.\n" RESET);
                }
            } while (!validarEndereco(enderecoNovo));
            atualizarCampoAssinante(idCom, enderecoNovo, 5);
            controle = 0;
        break; 
        case '6':
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

void atualizarCampoAssinante(int idCom, const char* novoValor, int campo) {
    FILE *arqAssinantes = fopen("./dados/dadosAssinantes.dat", "r+b");
    if (arqAssinantes == NULL) {
        printf(VERMELHO "Falha na manipulação dos arquivos" RESET);
        getchar();
        return;
    }
    
    Assinante* assinante = (Assinante*) malloc(sizeof(Assinante));
    
    while (fread(assinante, sizeof(Assinante), 1, arqAssinantes)) {
        if ((idCom == assinante->id) && (assinante->status == True)) {
            switch (campo){
            case 1:
                strcpy(assinante->nome, novoValor); // copia o novo valor para o campo nome
                break;
            case 2:
                strcpy(assinante->email, novoValor);;
                break;
            case 3:
                strcpy(assinante->cpf, novoValor);;
                break;
            case 4:
                strcpy(assinante->dataNascimento, novoValor);
                break;
            case 5:
                strcpy(assinante->endereco, novoValor);
                break;
            default:
                break;      
            }
            fseek(arqAssinantes, -1 * sizeof(Assinante), SEEK_CUR);
            fwrite(assinante, sizeof(Assinante), 1, arqAssinantes);
            
            printf(CIANO "Assinante alterado com sucesso\n" RESET);
            printf(CINZA "Aperte enter para voltar ao menu\n" RESET);
            getchar();
            
            free(assinante);
            fclose(arqAssinantes);
            return;
        }
    }

    printf(VERMELHO "Assinante não encontrado!\n" RESET);
    free(assinante);
    fclose(arqAssinantes);
}

void listarAssinantes(void) {
    FILE *arqAssinantes;
    Assinante* assinante;

    system("clear||cls");

    printf(BRANCO);
    printf("╔══════════════════════════════════════════════════════════════════╗\n");
    printf("║                " AMARELO "L I S T A G E M   D E   A S S I N A N T E S" BRANCO "       ║\n");
    printf("╠══════════════════════════════════════════════════════════════════╣\n");
    printf(RESET);

    arqAssinantes = fopen("./dados/dadosAssinantes.dat", "rb");
    if (arqAssinantes == NULL) {
        printf(VERMELHO "❌ Erro ao abrir o arquivo de assinantes!\n" RESET);
        printf(CINZA "Pressione Enter para voltar.\n" RESET);
        getchar();
        return;
    }

    assinante = (Assinante*) malloc(sizeof(Assinante));
    int encontrou = 0;
    
    printf(BRANCO "┌────────┬────────────────────────────┬────────────────────────────┐\n" RESET);
    printf("│ " AMARELO "ID" RESET "     │ " AMARELO "Nome" RESET "                       │ " AMARELO "CPF" RESET "                        │\n");
    printf(BRANCO "├────────┼────────────────────────────┼────────────────────────────┤\n" RESET);

    while (fread(assinante, sizeof(Assinante), 1, arqAssinantes)) {
        if (assinante->status == True) {
            encontrou = 1;
            printf(BRANCO "│ " CIANO "%-6d" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │ " BRANCO "%-26.26s" BRANCO " │\n" RESET,
                   assinante->id,
                   assinante->nome,
                   assinante->cpf);
        }
    }

    if (encontrou) {
        printf(CINZA "└────────┴────────────────────────────┴────────────────────────────┘\n" RESET);
    } else {
        printf(BRANCO "│ " VERMELHO "%-66s" BRANCO " │\n" RESET, "Nenhum assinante encontrado.");
        printf(CINZA "└──────────────────────────────────────────────────────────────────┘\n" RESET);
    }

    fclose(arqAssinantes);
    free(assinante);

    printf(CINZA "\nPressione Enter para voltar ao menu.\n" RESET);
    getchar();
}