# LAB-trabalho_final
espaço para o desenvolvimento do trabalho final de laboratório de programação

->  Este codigo define e manipula um banco de dados de **REFERENCIAS BIBLIOGRAFICAS!** O programa deve atender aos seguinte requisitos:

# REFERENCIA BIBLIOGRAFICA
    Nome da publicação;
    Tipo de publicação (livro, artigo cientifico, artigo de jornal, etc.);
    Autores;
        Nome próprio;
        Apelido;
    Ano de publicação;
    Local de publicação
    Número de páginas
    Endereço http
    Palavras-chave
        Palavra-chave 1
        Palavra-chave 2
        (....)
        Palavra-chave n

# Efetuar as seguintes operações:
    Inserir, mostrar, alterar, eliminar
        referências bibliográficas.
        autores de uma referência bibliográfica
        palavras-chave de uma referência bibliográfica
    Listar:
        Autores (sem mostrar repetidos)
        Todas as publicações de um autor (Dado o nome completo ou só o Apelido)
        Todas as publicações de um certo tipo
        Todas as publicações que contenham uma combinação de palavras-chave (1 ou mais palavras-chave)
        Todas as publicações de um ano
        Todas as palavras-chave existentes na base de dados (sem mostrar repetidas)
    Mostrar alguma estatística:
        Total de publicações (sem repetidos)
        Total de autores (sem repetidos)
        Total de palavras-chave (sem repetidos)
        Total de páginas na base de dados
        Média de páginas por publicação

============================================================

# ESPLICAÇÃO DO CÓDIGO ATUAL

**1. Definições de Constantes e Estruturas**

-> Constantes:
    tamanho_maximo_string: Define o tamanho máximo para strings, como nomes e IDs. O valor é 100.
    maximo_palavras_chave: Número máximo de palavras-chave permitido. Valor: 10.
    falha_saida: Código de erro para indicar uma falha de execução. Valor: -1.
    verdadeiro/falso: Constantes booleanas para facilitar a legibilidade do código, com 1 para verdadeiro e 0 para falso.

-> Estruturas:
    Autor: Estrutura que armazena informações sobre um autor, incluindo id, nome, e apelido.

    typedef struct {
        char id[tamanho_maximo_string];
        char nome[tamanho_maximo_string];
        char apelido[tamanho_maximo_string];
    } Autor;

-> Referencia: Estrutura para armazenar informações sobre uma referência acadêmica. Ela inclui atributos como id, nome, tipo, ano de publicação, autores associados, palavras-chave e um endereço HTTP.

    typedef struct {
        char id[tamanho_maximo_string];
        char nome[tamanho_maximo_string];
        char tipo[tamanho_maximo_string];
        Autor *autores;
        int numero_autores;
        int ano;
        char local_publicacao[tamanho_maximo_string];
        int numero_paginas;
        char endereco_http[tamanho_maximo_string];
        char **palavras_chave;
        int numero_palavras_chave;
    } Referencia;

->BancoDeDados: Estrutura que representa o banco de dados, armazenando as referências e os autores de forma separada.
    typedef struct {
        Referencia *referencias;
        int numero_referencias;
        Autor *autores;
        int numero_autores;
    } BancoDeDados;

**2. Funções Auxiliares**
-> ler_string
Esta função lê uma string de entrada do usuário, removendo o caractere de nova linha (\n) no final. Ela é usada para capturar as entradas de texto do usuário.

    void ler_string(char *buffer, int tamanho) {
        if (fgets(buffer, tamanho, stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
        }
    }

-> endereco_http_valido
Valida se o endereço HTTP fornecido começa com "http://" ou "https://". Se for válido, retorna verdadeiro, caso contrário, falso.

    int endereco_http_valido(const char *url) {
        return (strstr(url, "http://") == url || strstr(url, "https://") == url);
    }

-> palavra_chave_duplicada
Verifica se uma palavra-chave já foi inserida. Se for duplicada, retorna verdadeiro.

    int palavra_chave_duplicada(char **palavras_chave, int numero_palavras_chave, const char *palavra_chave) {
        for (int i = 0; i < numero_palavras_chave; i++) {
            if (strcmp(palavras_chave[i], palavra_chave) == 0) {
                return verdadeiro;
            }
        }
        return falso;
    }

**3. Funções de Manipulação de Autores**

-> exibir_autores
Exibe a tabela de autores com suas informações: ID, Nome, e Apelido.

void exibir_autores(BancoDeDados *bd) {
    printf("\nTabela de Autores:\n");
    // Tabela formatada
    for (int i = 0; i < bd->numero_autores; i++) {
        printf("| %-20s | %-20s | %-20s |\n", bd->autores[i].id, bd->autores[i].nome, bd->autores[i].apelido);
    }
}

-> inserir_autor
Permite inserir um novo autor no banco de dados. Verifica se o ID do autor já existe para evitar duplicações. Se for inserido com sucesso, exibe a tabela de autores atualizada.

    'void inserir_autor(BancoDeDados *bd) {
        bd->autores = realloc(bd->autores, (bd->numero_autores + 1) * sizeof(Autor));
        // Recebe os dados do autor e insere no banco
        bd->numero_autores++;
        exibir_autores(bd);
    }

**4. Funções de Manipulação de Referências**

-> exibir_referencias
Exibe a lista de todas as referências com seus respectivos atributos: ID, nome, autores, ano, palavras-chave, entre outros.

    void exibir_referencias(BancoDeDados *bd) {
        for (int i = 0; i < bd->numero_referencias; i++) {
            // Exibe a referência com autores e palavras-chave
        }
    }

-> validar_referencia
Valida se os campos de uma referência foram preenchidos corretamente (nome, tipo, autores, ano, local de publicação, páginas, e endereço HTTP).

    int validar_referencia(Referencia *ref) {
        // Checa se os campos obrigatórios estão preenchidos corretamente
    }

-> inserir_referencia
Permite inserir uma nova referência. O processo inclui a leitura dos dados, a validação da referência e o armazenamento, evitando duplicações. As palavras-chave também são verificadas para evitar duplicatas.

    void inserir_referencia(BancoDeDados *bd) {
        // Lê os dados da referência
        // Verifica se já existe uma referência com o mesmo ID
        // Verifica palavras-chave duplicadas
        if (validar_referencia(nova_ref)) {
            bd->numero_referencias++;
            exibir_referencias(bd);
        }
    }

-> liberar_referencia e liberar_banco_de_dados
Essas funções liberam a memória alocada dinamicamente para autores, palavras-chave e referências, evitando vazamentos de memória.

    void liberar_referencia(Referencia *ref) {
        free(ref->autores);
        for (int i = 0; i < ref->numero_palavras_chave; i++) {
            free(ref->palavras_chave[i]);
        }
        free(ref->palavras_chave);
    }

    void liberar_banco_de_dados(BancoDeDados *bd) {
        // Libera todas as referências e autores
    }

**5. Função main**
A função principal inicializa o banco de dados, permite a inserção de autores e referências, e ao final libera os recursos alocados dinamicamente.

    int main() {
        BancoDeDados bd;
        bd.referencias = NULL;
        bd.numero_referencias = 0;
        bd.autores = NULL;
        bd.numero_autores = 0;

        inserir_autor(&bd);
        inserir_referencia(&bd);

        liberar_banco_de_dados(&bd);
        return 0;
    }

# Resumo Geral:
-> BancoDeDados contém autores e referências.
-> As referências incluem várias informações, como autores, ano e palavras-chave.
-> Autores e Referências podem ser inseridos, exibidos e validados.
-> Memória alocada dinamicamente é usada para autores e palavras-chave.
-> Ao final, a memória é liberada para evitar vazamentos.