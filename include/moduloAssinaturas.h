#ifndef MODULO_ASSINATURAS_H
    #define MODULO_ASSINATURAS_H
    #define True 1
    #define False 0
    typedef struct assinatura Assinatura;
    struct assinatura{
        int id;
        char idAssinante[20];
        char dataAssinatura[20];
        char periodoVencimento[20];
        int status;
    };
    void telaAssinaturas();
    void menuAssinaturas();
    void cadastroAssinatura();
    void checarAssinaturas();
    void exibirAssinatura(const Assinatura* assinatura);
    void alterarAssinatura();
    void excluirAssinatura();
    char confirmarInfoAssinatura(const Assinatura*);
    Assinatura* salvarAssinaturas();
    Assinatura* recuperarAssinatura(int);
    Assinatura* criarAssinatura();
    void preencherAssinatura(Assinatura* assinatura);
    void excluirAssinaturaArquivo(int);
    void alterarAssinaturaArquivo(int);
    void atualizarCampoAssinatura(int, const char*, int);
    void listarAssinaturas();

#endif