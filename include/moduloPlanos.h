#ifndef MODULO_PLANOS_H
    #define MODULO_PLANOS_H
    #define True 1
    #define False 0
    typedef struct plano Plano;
    struct plano{
        int id;
        char nome[100];
        char preco[100];
        char periodo[20];
        int status;
        struct plano* prox; 
    };
    void telaPlano(void);
    void menuPlanos(void);
    void cadastroPlano(void);
    void checarPlanos(void);
    void exibirPlano(const Plano* plano);
    void alterarPlano(void);
    void excluirPlano(void);
    char confirmarInfoPlano(const Plano*);
    Plano* salvarPlanos();
    Plano* recuperarPlano();
    Plano* criarPlano();
    void preencherPlano(Plano* plano);
    void excluirPlanoArquivo(int);
    void alterarPlanoArquivo(int);
    void atualizarCampoPlano(int, const char*, int);
    void listarPlanos(void);
    Plano* quantidadePlanos();


#endif