#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamanho_maximo_string 100
#define maximo_palavras_chave 10
#define falha_saida -1
#define verdadeiro 1
#define falso 0

typedef struct
{
    char id[tamanho_maximo_string];
    char nome[tamanho_maximo_string];
    char apelido[tamanho_maximo_string];
} Autor;

typedef struct
{
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

typedef struct
{
    Referencia *referencias;
    int numero_referencias;
    Autor *autores;
    int numero_autores;
} BancoDeDados;

int endereco_http_valido(const char *url);
int palavra_chave_duplicada(char **palavras_chave, int numero_palavras_chave, const char *palavra_chave);
void exibir_autores(BancoDeDados *bd);
void inserir_autor(BancoDeDados *bd);
void exibir_referencias(BancoDeDados *bd);
int validar_referencia(Referencia *ref);
void inserir_referencia(BancoDeDados *bd);
void liberar_referencia(Referencia *ref);
void liberar_banco_de_dados(BancoDeDados *bd);
void ler_string(char *buffer, int tamanho);

void ler_string(char *buffer, int tamanho)
{
    if (fgets(buffer, tamanho, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void ler_inteiro(int *num)
{
    scanf("%d", num);
    while (getchar() != '\n')
        ;
}

int endereco_http_valido(const char *url)
{
    return (strstr(url, "http://") == url || strstr(url, "https://") == url);
}

int palavra_chave_duplicada(char **palavras_chave, int numero_palavras_chave, const char *palavra_chave)
{
    for (int i = 0; i < numero_palavras_chave; i++)
    {
        if (strcmp(palavras_chave[i], palavra_chave) == 0)
        {
            return verdadeiro;
        }
    }
    return falso;
}

void exibir_autores(BancoDeDados *bd)
{
    printf("\nTabela de Autores:\n");
    printf("+----------------------+----------------------+----------------------+\n");
    printf("| ID                   | Nome                 | Apelido              |\n");
    printf("+----------------------+----------------------+----------------------+\n");
    for (int i = 0; i < bd->numero_autores; i++)
    {
        printf("| %-20s | %-20s | %-20s |\n", bd->autores[i].id, bd->autores[i].nome, bd->autores[i].apelido);
    }
    printf("+----------------------+----------------------+----------------------+\n");
}

void inserir_autor(BancoDeDados *bd)
{
    bd->autores = realloc(bd->autores, (bd->numero_autores + 1) * sizeof(Autor));
    if (bd->autores == NULL)
    {
        printf("Erro ao alocar memória para novos autores.\n");
        exit(falha_saida);
    }

    Autor *novo_autor = &bd->autores[bd->numero_autores];
    printf("Digite o ID do autor: ");
    ler_string(novo_autor->id, tamanho_maximo_string);

    for (int i = 0; i < bd->numero_autores; i++)
    {
        if (strcmp(bd->autores[i].id, novo_autor->id) == 0)
        {
            printf("Autor já existe.\n");
            return;
        }
    }

    printf("Digite o nome do autor: ");
    ler_string(novo_autor->nome, tamanho_maximo_string);

    printf("Digite o apelido do autor: ");
    ler_string(novo_autor->apelido, tamanho_maximo_string);

    bd->numero_autores++;
}

void exibir_referencias(BancoDeDados *bd)
{
    printf("\nTabela de Referências:\n");

    for (int i = 0; i < bd->numero_referencias; i++)
    {
        Referencia *ref = &bd->referencias[i];

        printf("\nReferência %d:\n", i + 1);
        printf("+---------------------------+\n");
        printf("| Campo                     |\n");
        printf("+---------------------------+\n");
        printf("| ID: %s\n", ref->id);
        printf("| Nome: %s\n", ref->nome);
        printf("| Tipo: %s\n", ref->tipo);
        printf("| Ano: %d\n", ref->ano);
        printf("| Local de Publicação: %s\n", ref->local_publicacao);
        printf("| Número de Páginas: %d\n", ref->numero_paginas);
        printf("| Endereço HTTP: %s\n", ref->endereco_http);

        printf("| Autores:\n");
        for (int j = 0; j < ref->numero_autores; j++)
        {
            printf("|   %s %s\n", ref->autores[j].nome, ref->autores[j].apelido);
        }

        printf("| Palavras-chave:\n");
        for (int k = 0; k < ref->numero_palavras_chave; k++)
        {
            printf("|   %s\n", ref->palavras_chave[k]);
        }

        printf("+---------------------------+\n");
    }
}

int validar_referencia(Referencia *ref)
{
    int valido = verdadeiro;

    if (strlen(ref->nome) == 0)
    {
        printf("Nome da publicação não pode estar vazio.\n");
        valido = falso;
    }

    if (strlen(ref->tipo) == 0)
    {
        printf("Tipo de publicação não pode estar vazio.\n");
        valido = falso;
    }

    if (ref->numero_autores <= 0)
    {
        printf("Número de autores deve ser maior que zero.\n");
        valido = falso;
    }

    if (ref->ano <= 0)
    {
        printf("Ano de publicação deve ser um valor positivo.\n");
        valido = falso;
    }

    if (strlen(ref->local_publicacao) == 0)
    {
        printf("Local de publicação não pode estar vazio.\n");
        valido = falso;
    }

    if (ref->numero_paginas <= 0)
    {
        printf("Número de páginas deve ser maior que zero.\n");
        valido = falso;
    }

    if (!endereco_http_valido(ref->endereco_http))
    {
        printf("Endereço HTTP inválido. Deve começar com http:// ou https://.\n");
        valido = falso;
    }

    if (ref->numero_palavras_chave <= 0)
    {
        printf("Número de palavras-chave deve ser maior que zero.\n");
        valido = falso;
    }

    return valido;
}

void inserir_referencia(BancoDeDados *bd)
{
    bd->referencias = realloc(bd->referencias, (bd->numero_referencias + 1) * sizeof(Referencia));
    if (bd->referencias == NULL)
    {
        printf("Erro ao alocar memória para novas referências.\n");
        exit(falha_saida);
    }

    Referencia *nova_ref = &bd->referencias[bd->numero_referencias];

    printf("Digite o ID da referência: ");
    ler_string(nova_ref->id, tamanho_maximo_string);

    for (int i = 0; i < bd->numero_referencias; i++)
    {
        if (strcmp(bd->referencias[i].id, nova_ref->id) == 0)
        {
            printf("Referência com este ID já existe.\n");
            return;
        }
    }

    printf("Digite o nome da publicação: ");
    ler_string(nova_ref->nome, tamanho_maximo_string);

    printf("Digite o tipo de publicação: ");
    ler_string(nova_ref->tipo, tamanho_maximo_string);

    printf("Digite o número de autores: ");
    scanf("%d", &nova_ref->numero_autores);

    while (getchar() != '\n')
        ;

    nova_ref->autores = malloc(nova_ref->numero_autores * sizeof(Autor));
    if (nova_ref->autores == NULL)
    {
        printf("Erro ao alocar memória para autores.\n");
        exit(falha_saida);
    }

    for (int i = 0; i < nova_ref->numero_autores; i++)
    {
        char nome_autor[tamanho_maximo_string];
        printf("Digite o nome do autor %d: ", i + 1);
        ler_string(nome_autor, tamanho_maximo_string);

        // Verifica se o autor ja existe
        int autor_encontrado = falso;
        for (int j = 0; j < bd->numero_autores; j++)
        {
            if (strcasecmp(bd->autores[j].nome, nome_autor) == 0)
            {
                nova_ref->autores[i] = bd->autores[j];
                autor_encontrado = verdadeiro;
                break;
            }
        }

        if (!autor_encontrado)
        {
            printf("Autor nao encontrado. Cadastrando novo autor...\n");
            bd->autores = realloc(bd->autores, (bd->numero_autores + 1) * sizeof(Autor));
            if (bd->autores == NULL)
            {
                printf("Erro ao alocar memoria para novos autores.\n");
                exit(falha_saida);
            }
            Autor *novo_autor = &bd->autores[bd->numero_autores];
            strcpy(novo_autor->nome, nome_autor);
            printf("Digite o ID do autor: ");
            ler_string(novo_autor->id, tamanho_maximo_string);
            printf("Digite o apelido do autor: ");
            ler_string(novo_autor->apelido, tamanho_maximo_string);
            nova_ref->autores[i] = *novo_autor;
            bd->numero_autores++;
        }
    }

    printf("Digite o ano da publicação: ");
    scanf("%d", &nova_ref->ano);
    while (getchar() != '\n')
        ; // Limpar o buffer

    printf("Digite o local de publicação: ");
    ler_string(nova_ref->local_publicacao, tamanho_maximo_string);

    printf("Digite o número de páginas: ");
    scanf("%d", &nova_ref->numero_paginas);
    while (getchar() != '\n')
        ; // Limpar o buffer

    printf("Digite o endereço HTTP: ");
    ler_string(nova_ref->endereco_http, tamanho_maximo_string);

    printf("Digite o número de palavras-chave: ");
    scanf("%d", &nova_ref->numero_palavras_chave);
    while (getchar() != '\n')
        ; // Limpar o buffer

    nova_ref->palavras_chave = malloc(nova_ref->numero_palavras_chave * sizeof(char *));
    if (nova_ref->palavras_chave == NULL)
    {
        printf("Erro ao alocar memória para palavras-chave.\n");
        exit(falha_saida);
    }

    for (int i = 0; i < nova_ref->numero_palavras_chave; i++)
    {
        nova_ref->palavras_chave[i] = malloc(tamanho_maximo_string * sizeof(char));
        printf("Digite a palavra-chave %d: ", i + 1);
        ler_string(nova_ref->palavras_chave[i], tamanho_maximo_string);

        if (palavra_chave_duplicada(nova_ref->palavras_chave, i, nova_ref->palavras_chave[i]))
        {
            printf("Palavra-chave duplicada. Por favor, insira novamente.\n");
            i--;
        }
    }

    if (validar_referencia(nova_ref))
    {
        bd->numero_referencias++;
        exibir_referencias(bd);
    }
    else
    {
        printf("Dados da referência inválidos. Não foi possível inserir a referência.\n");
        liberar_referencia(nova_ref);
    }
}

void liberar_referencia(Referencia *ref)
{
    free(ref->autores);
    for (int i = 0; i < ref->numero_palavras_chave; i++)
    {
        free(ref->palavras_chave[i]);
    }
    free(ref->palavras_chave);
}

void liberar_banco_de_dados(BancoDeDados *bd)
{
    for (int i = 0; i < bd->numero_referencias; i++)
    {
        liberar_referencia(&bd->referencias[i]);
    }
    free(bd->referencias);
    free(bd->autores);
}

void salvar_banco_de_dados(BancoDeDados *bd)
{
    FILE *file = fopen("banco_de_dados.txt", "w");
    if (!file)
    {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Salvar autores
    fprintf(file, "%d\n", bd->numero_autores);
    for (int i = 0; i < bd->numero_autores; i++)
    {
        fprintf(file, "%s;%s;%s\n", bd->autores[i].id, bd->autores[i].nome, bd->autores[i].apelido);
    }

    // Salvar referencias
    fprintf(file, "%d\n", bd->numero_referencias);
    for (int i = 0; i < bd->numero_referencias; i++)
    {
        Referencia *ref = &bd->referencias[i];
        fprintf(file, "%s;%s;%s;%d;%s;%d;%s;%d\n", ref->id, ref->nome, ref->tipo, ref->numero_autores, ref->local_publicacao, ref->numero_paginas, ref->endereco_http, ref->numero_palavras_chave);
        for (int j = 0; j < ref->numero_autores; j++)
        {
            fprintf(file, "%s;%s;%s\n", ref->autores[j].id, ref->autores[j].nome, ref->autores[j].apelido);
        }
        for (int k = 0; k < ref->numero_palavras_chave; k++)
        {
            fprintf(file, "%s\n", ref->palavras_chave[k]);
        }
    }

    fclose(file);
    printf("Banco de dados salvo com sucesso!\n");
}

void carregar_banco_de_dados(BancoDeDados *bd)
{
    FILE *file = fopen("banco_de_dados.txt", "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo para carregar.\n");
        return;
    }

    // Carregar autores
    fscanf(file, "%d\n", &bd->numero_autores);
    bd->autores = malloc(bd->numero_autores * sizeof(Autor));
    for (int i = 0; i < bd->numero_autores; i++)
    {
        fscanf(file, "%[^;];%[^;];%[^\n]\n", bd->autores[i].id, bd->autores[i].nome, bd->autores[i].apelido);
    }

    // Carregar referencias
    fscanf(file, "%d\n", &bd->numero_referencias);
    bd->referencias = malloc(bd->numero_referencias * sizeof(Referencia));
    for (int i = 0; i < bd->numero_referencias; i++)
    {
        Referencia *ref = &bd->referencias[i];
        fscanf(file, "%[^;];%[^;];%[^;];%d;%[^;];%d;%[^;];%d\n", ref->id, ref->nome, ref->tipo, &ref->numero_autores, ref->local_publicacao, &ref->numero_paginas, ref->endereco_http, &ref->numero_palavras_chave);
        ref->autores = malloc(ref->numero_autores * sizeof(Autor));
        for (int j = 0; j < ref->numero_autores; j++)
        {
            fscanf(file, "%[^;];%[^;];%[^\n]\n", ref->autores[j].id, ref->autores[j].nome, ref->autores[j].apelido);
        }
        ref->palavras_chave = malloc(ref->numero_palavras_chave * sizeof(char *));
        for (int k = 0; k < ref->numero_palavras_chave; k++)
        {
            ref->palavras_chave[k] = malloc(tamanho_maximo_string * sizeof(char));
            fscanf(file, "%[^\n]\n", ref->palavras_chave[k]);
        }
    }

    fclose(file);
    printf("Banco de dados carregado com sucesso!\n");
}

void alterar_referencia()
{
    // FALTA !!!
}

void excluir_referencia()
{
    // FALTA !!!
}

void exibir_estatisticas()
{
    // FALTA !!!
}

int main()
{
    BancoDeDados bd;
    bd.numero_autores = 0;
    bd.autores = NULL;
    bd.numero_referencias = 0;
    bd.referencias = NULL;

    carregar_banco_de_dados(&bd);

    int opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir Referencia\n");
        printf("2. Inserir Autor\n");
        printf("3. Exibir Referencias\n");
        printf("4. Exibir Autores\n");
        printf("5. Alterar Referencia\n");
        printf("6. Excluir Referencia\n");
        printf("7. Exibir Estatisticas\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");
        ler_inteiro(&opcao);

        switch (opcao)
        {
        case 1:
            inserir_referencia(&bd);
            break;
        case 2:
            inserir_autor(&bd);
            break;
        case 3:
            exibir_referencias(&bd);
            break;
        case 4:
            exibir_autores(&bd);
            break;
        case 5:
            alterar_referencia();
            break;
        case 6:
            excluir_referencia();
            break;
        case 7:
            exibir_estatisticas();
        case 8:
            salvar_banco_de_dados(&bd);
            liberar_banco_de_dados(&bd);
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 8);

    return 0;
}