# Computação Gráfica - Trabalho Prático I

Este é um trabalho prático da disciplina de **Computação Gráfica**, desenvolvido por *Victor Cabral* para o semestre de 2025/2.  
A aplicação foi construída em **C++** utilizando o framework **Qt6** e demonstra a implementação de algoritmos fundamentais de rasterização, transformações geométricas 2D e recorte de retas.

---

## Sobre o Projeto
O objetivo deste trabalho é aplicar conceitos teóricos de computação gráfica em uma aplicação interativa.  
O usuário pode desenhar formas primitivas, selecionar esses objetos e aplicar diversas transformações ou definir uma janela de recorte para visualizar o funcionamento dos algoritmos de recorte.

---

## Sumário
- [Computação Gráfica - Trabalho Prático I](#computação-gráfica---trabalho-prático-i)  
- [Sobre o Projeto](#sobre-o-projeto)  
- [Funcionalidades Implementadas](#funcionalidades-implementadas)  
- [Pré-requisitos](#pré-requisitos)  
- [Como Compilar e Executar](#como-compilar-e-executar)  
- [Como Usar a Aplicação](#como-usar-a-aplicação)  
  - [Desenhando Formas](#1-desenhando-formas-rasterização)  
  - [Aplicando Transformações Geométricas](#2-aplicando-transformações-geométricas)  
  - [Usando Algoritmos de Recorte](#3-usando-algoritmos-de-recorte)  
  - [Limpar a Tela](#4-limpar-a-tela) 
---
## Funcionalidades Implementadas

### Rasterização
- Desenho de Retas com os algoritmos **DDA** e **Bresenham**.  
- Desenho de Circunferências com o algoritmo de **Bresenham**.

### Transformações Geométricas 2D
- **Translação**: Move objetos pela tela.  
- **Rotação**: Gira objetos em torno de um ponto pivô.  
- **Escala**: Aumenta ou diminui o tamanho dos objetos a partir de um ponto fixo.  
- **Reflexão**: Espelha os objetos em relação a um eixo (X, Y ou ambos).  

### Recorte (Clipping)
- Recorte de retas utilizando o algoritmo de **Cohen-Sutherland**.  
- Recorte de retas utilizando o algoritmo de **Liang-Barsky**.

---

## Pré-requisitos
Para compilar e executar este projeto, é necessário ter o seguinte software instalado em seu sistema:
- **Qt6**: Framework principal utilizado para a interface gráfica e estruturas de dados.  
- **CMake (3.16+)**: Utilizado para gerenciar o processo de compilação.  
- **Compilador C++**: Suporte a **C++17** (ex: `g++` no Linux).  

Este projeto foi desenvolvido e testado primariamente no sistema operacional **Linux (Ubuntu)**.

---

## Como Compilar e Executar

```bash
# 1. Crie uma pasta de build
mkdir build
cd build

# 2. Execute o CMake para configurar o projeto
cmake ..

# 3. Compile o código-fonte com o Make
make

# 4. Execute a aplicação
./TrabalhoCG
```

---

## Como Usar a Aplicação

A interface é dividida em duas partes principais:  
- Um **painel de controle** à esquerda com os botões de ação.  
- Uma **área de desenho** branca à direita.  

### 1. Desenhando Formas (Rasterização)
1. Clique em um dos botões de desenho: *Reta - DDA*, *Reta - Bresenham* ou *Circunferência - Bresenham*.  
2. Para **Retas**: clique uma vez na área de desenho para marcar o ponto inicial e uma segunda vez para marcar o ponto final.  
3. Para **Circunferências**: clique na área de desenho para definir o centro. Uma caixa de diálogo aparecerá para que você insira o raio.  

### 2. Aplicando Transformações Geométricas
1. Clique no botão da transformação desejada (ex: *Rotação*).  
2. Clique duas vezes na área de desenho para definir uma janela de seleção retangular.  
   - O primeiro clique define um canto.  
   - O segundo clique define o canto oposto.  
3. Todos os objetos que estiverem total ou parcialmente dentro dessa janela serão selecionados.  
4. Uma caixa de diálogo aparecerá para inserir os parâmetros da transformação.  
5. A transformação será aplicada a todos os objetos selecionados, usando o centro da janela de seleção como pivô.  

### 3. Usando Algoritmos de Recorte
1. Desenhe algumas retas na tela.  
2. Clique em *Cohen Sutherland* ou *Liang Barsky*.  
3. Clique duas vezes na área de desenho para definir a janela de recorte.  
4. Apenas os segmentos dentro da janela serão visíveis.  
   - A janela será mostrada com uma linha cinza tracejada.  

### 4. Limpar a Tela
- Clique no botão **Limpar Tela** para apagar todos os objetos e recomeçar.  

---
