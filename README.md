# Lista Encadeada em C++

Este repositório contém a implementação de uma **lista encadeada em C++**, desenvolvida como parte de um trabalho da disciplina de Estrutura de Dados.

A estrutura foi organizada de forma modular, separando responsabilidades em diferentes arquivos `.h`, e conta com uma **função `main` que executa testes automatizados** para validar o funcionamento dos métodos implementados. Também foram realizadas verificações para garantir que **não há vazamentos de memória** durante a execução.

## 📄 Arquivos principais

- `Elemento.h`: define a estrutura dos nós da lista.
- `ListaEncadeadaAbstrata.h`: define uma interface abstrata para listas encadeadas.
- `MinhaListaEncadeada.h`: implementação concreta da lista encadeada.
- `excecoes.h`: define exceções personalizadas utilizadas no projeto.
- `main.cpp`: contém os testes automatizados.
- `CMakeLists.txt`: script para facilitar a compilação com CMake.

## 🔧 Como compilar e executar

### Utilizando CMake

1. Gere os arquivos de build:

```bash
cmake -S . -B build
