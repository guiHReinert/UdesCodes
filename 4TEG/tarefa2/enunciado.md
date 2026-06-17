---
lang: pt-BR
---

# Tarefa 2 - TEG

**Equipes**: MÁXIMO 3 MEMBROS.

## Objetivos

Implementação de um grafo com carga primária a partir de um arquivo de base.

Construir um grafo não direcionado ponderado onde os vértices são palavras em
português de tamanho fixo (4 letras) e as arestas conectam palavras que diferem por
apenas uma letra (ex: MATA -> MALA).

## O Grafo G(V,E)

**Vértices**: palavras da base de palavras de tamanho 4 caracteres disponível no Moodle.
Arestas: sejam ‘p’ e ‘q’ ∈ V, (p,q) ∈ A se as palavras em ‘p’ e ‘q’ diferirem em apenas uma
posição de caractere.

A ideia é verificar a transformação de palavras, exemplo: "LAGO" em "CENA", LAGO ->
LOGO -> LEGO -> CEGO -> CEGA -> CENA.

## Requisitos:

1. Implementação em linguagem C;
2. O sistema tem que permitir a carga primária do grafo a partir da base de palavras
especificada.
3. O sistema deve informar:
    1. Quantos componentes conexos existem no grafo, os respectivos tamanhos de
cada componente, qual é a palavra central de cada componente (palavra com
mais conexões – vértice de grau máximo) e qual a palavra com menos conexões
(vértice de grau mínimo);
    2. Se o grafo é simples ou multigrafo. Se for multigrafo deve informar quantos laços e/ou arestas múltiplas ocorrem;
    3. Encontre e compare as sequências de arestas para ligar duas palavras de quatro letras, fornecidas pelo usuário, utilizando Dijkstra.
