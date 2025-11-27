#include "moduloAssinantes.h"
#include "moduloProdutos.h"
#ifndef MODULO_RELATORIOS_H
    #define MODULO_RELATORIOS_H
    void telaRelatorios();
    void menuRelatorios();
    void relatorioAssinantesFaixaEtaria();
    void relatorioAssinaturasPeriodo();
    void relatorioPlanosFaixaPreco();
    void relatorioProdutosPorMarca();
    void relatorioPlanosPorProduto();
    void relatorioAssinaturasPorCPF();
    void relatorioPlanosPorPeriodo();
    void relatorioProdutosPorAno();
    void assinantesOrdemAlfabetica(Assinante **);
    void telaAssinantesOrdemAlfabetica(Assinante* );
    void apagarLista(Assinante**);
#endif