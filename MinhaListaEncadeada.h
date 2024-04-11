#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada(){
        while (!this->vazia()) {
            this->removerDoInicio();
        }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        if (this->vazia()) {
            return 0;
        }

        return this->_tamanho;
    };
    
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const 
    {
        std::size_t tamanho;
        tamanho = this->_tamanho;

        if (tamanho == 0) {
            return true;
        }

        return false;

    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const 
    {
        std::size_t posicao = 0;
        Elemento<T>* elemento_atual = this->_primeiro;

        if (this->vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        if (!this->contem(dado)) {
            throw ExcecaoDadoInexistente();
        }

        while (true) {

            if (elemento_atual->dado == dado) {
                return posicao;
            }

            posicao++;
            elemento_atual = elemento_atual->proximo;
        }
        
    };
    
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        Elemento<T>* elemento_atual = this->_primeiro;

        if (elemento_atual == nullptr) {
            return false;
        }

        while (elemento_atual != nullptr) {

            if (elemento_atual->dado == dado) {
                return true;
            }

            elemento_atual = elemento_atual->proximo;
        }

        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) 
    {
        Elemento<T>* novo_elemento = new Elemento<T>(dado, this->_primeiro);
        this->_primeiro = novo_elemento;
        this->_tamanho++;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        Elemento<T>* elemento_atual = this->_primeiro;
        std::size_t tamanho = this->_tamanho;
        std::size_t i;

        if (posicao > tamanho) {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0) {
            this->inserirNoInicio(dado);
        }

        else if (posicao == tamanho) {
            this->inserirNoFim(dado);
        }

        else {

            for (i = 0; i < posicao - 1; i++) {
                elemento_atual = elemento_atual->proximo;
            }

            Elemento<T>* novo_elemento = new Elemento<T>(dado, elemento_atual->proximo);
            elemento_atual->proximo = novo_elemento;

            this->_tamanho++;
        }

    };


    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        Elemento<T>* novo_elemento = new Elemento<T>(dado, nullptr);
        Elemento<T>* elemento_atual = this->_primeiro;

        if (this->vazia()) {
            this->inserirNoInicio(dado);
        }

        else {
            while (elemento_atual->proximo != nullptr) {
                elemento_atual = elemento_atual->proximo;
            }

            elemento_atual->proximo = novo_elemento;

            this->_tamanho++;
        }

    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if (this->vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T>* elemento = this->_primeiro;
        T dado = elemento->dado;
        this->_primeiro = elemento->proximo;
        delete elemento;
        this->_tamanho--;

        return dado;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        if (posicao >= this->_tamanho) {
            throw ExcecaoPosicaoInvalida();
        }

        else if (posicao == 0) {
            return this->removerDoInicio();
        }

        else if (posicao == this->_tamanho-1) {
            return this->removerDoFim();
        }

        else {
            Elemento<T>* elemento_anterior = this->_primeiro;
            Elemento<T>* elemento_proximo;
            Elemento<T>* elemento_removido;
            T dado;
            size_t i;
            
            for (i = 0; i < posicao-1; i++) {
                elemento_anterior = elemento_anterior->proximo;
            }

            elemento_removido = elemento_anterior->proximo;
            elemento_proximo = elemento_removido->proximo;
            dado = elemento_removido->dado;
            elemento_anterior->proximo = elemento_proximo;
            delete elemento_removido;
            this->_tamanho--;

            return dado;
        }

    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        if (this->vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        else if (this->_tamanho == 1) {
            return this->removerDoInicio();
        }

        else {
            Elemento<T>* elemento_atual = this->_primeiro;
            Elemento<T>* elemento_removido;
            T valor_elemento_removido;
            std::size_t i;
            size_t tamanho = this->_tamanho;

            for (i = 0; i < tamanho - 2; i++) {
                elemento_atual = elemento_atual->proximo;
            }

            elemento_removido = elemento_atual->proximo;
            valor_elemento_removido = elemento_removido->dado;
            elemento_atual->proximo = nullptr;
            this->_tamanho--;
            delete elemento_removido;

            return valor_elemento_removido;
        }

    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        if (this->vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        else if (!this->contem(dado)) {
            throw ExcecaoDadoInexistente();
        }

        else {
            Elemento<T>* elemento_anterior = this->_primeiro;
            Elemento<T>* elemento_atual;
            Elemento<T>* elemento_proximo;
            size_t posicao = this->posicao(dado);
            size_t i;

            if (posicao == 0) {
                this->removerDoInicio();
            }

            else if (posicao == this->_tamanho - 1) {
                this->removerDoFim();
            }

            else {
                for (i = 0; i < posicao - 1; i++) {
                    elemento_anterior = elemento_anterior->proximo;
                }

                elemento_atual = elemento_anterior->proximo;
                elemento_proximo = elemento_atual->proximo;
                elemento_anterior->proximo = elemento_proximo;

                delete elemento_atual;
                this->_tamanho--;
            }
        }
    };
};

#endif