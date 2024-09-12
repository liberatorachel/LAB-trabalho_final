#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100
#define MAX_KEYWORDS 10

typedef struct
{
    char id[MAX_STRING_LENGTH];
    char firstName[MAX_STRING_LENGTH];
    char lastName[MAX_STRING_LENGTH];
} Author;

typedef struct
{
    char id[MAX_STRING_LENGTH]; // Identificador único
    char name[MAX_STRING_LENGTH];
    char type[MAX_STRING_LENGTH];
    Author *authors;
    int numAuthors;
    int year;
    char publicationLocation[MAX_STRING_LENGTH];
    int numPages;
    char httpAddress[MAX_STRING_LENGTH];
    char **keywords;
    int numKeywords;
} Reference;

typedef struct
{
    Reference *references;
    int numReferences;
    Author *authors;
    int numAuthors;
} Database;

// Declarações das funções
bool isValidURL(const char *url);
bool isDuplicateKeyword(char **keywords, int numKeywords, const char *keyword);
void showAuthors(Database *db);
void insertAuthor(Database *db);
void showReferences(Database *db);
bool validateReference(Reference *ref);
void insertReference(Database *db);
void freeReference(Reference *ref);
void freeDatabase(Database *db);

// Função para validar se um URL está no formato correto
bool isValidURL(const char *url)
{
    return (strstr(url, "http://") == url || strstr(url, "https://") == url);
}

// Função para verificar se uma palavra-chave já existe
bool isDuplicateKeyword(char **keywords, int numKeywords, const char *keyword)
{
    for (int i = 0; i < numKeywords; i++)
    {
        if (strcmp(keywords[i], keyword) == 0)
        {
            return true;
        }
    }
    return false;
}

// Função para exibir a tabela de autores
void showAuthors(Database *db)
{
    printf("\nTabela de Autores:\n");
    printf("+----------------------+----------------------+----------------------+\n");
    printf("| ID                   | Nome                 | Apelido              |\n");
    printf("+----------------------+----------------------+----------------------+\n");
    for (int i = 0; i < db->numAuthors; i++)
    {
        printf("| %-20s | %-20s | %-20s |\n", db->authors[i].id, db->authors[i].firstName, db->authors[i].lastName);
    }
    printf("+----------------------+----------------------+----------------------+\n");
}

// Função para inserir um novo autor
void insertAuthor(Database *db)
{
    db->authors = realloc(db->authors, (db->numAuthors + 1) * sizeof(Author));
    if (db->authors == NULL)
    {
        printf("Erro ao alocar memória para novos autores.\n");
        exit(EXIT_FAILURE);
    }

    Author *newAuthor = &db->authors[db->numAuthors];
    printf("Digite o ID do autor: ");
    fgets(newAuthor->id, MAX_STRING_LENGTH, stdin);
    newAuthor->id[strcspn(newAuthor->id, "\n")] = '\0';

    // Verificar se o autor já existe
    for (int i = 0; i < db->numAuthors; i++)
    {
        if (strcmp(db->authors[i].id, newAuthor->id) == 0)
        {
            printf("Autor já existe.\n");
            return;
        }
    }

    printf("Digite o nome do autor: ");
    fgets(newAuthor->firstName, MAX_STRING_LENGTH, stdin);
    newAuthor->firstName[strcspn(newAuthor->firstName, "\n")] = '\0';

    printf("Digite o apelido do autor: ");
    fgets(newAuthor->lastName, MAX_STRING_LENGTH, stdin);
    newAuthor->lastName[strcspn(newAuthor->lastName, "\n")] = '\0';

    db->numAuthors++;
    showAuthors(db);
}

// Função para exibir a tabela de referências
void showReferences(Database *db)
{ // >>> ALTERAR A TABELA !!! <<<
    printf("\nTabela de Referências:\n");
    printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
    printf("| %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n",
           "ID", "Nome", "Tipo", "Ano", "Local", "Páginas", "HTTP", "Autores", "Palavras-chave", " ");
    printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");

    for (int i = 0; i < db->numReferences; i++)
    {
        Reference *ref = &db->references[i];

        // Exibir ID
        printf("| %-20s ", ref->id);

        // Exibir Nome
        printf("| %-20s ", ref->name);

        // Exibir Tipo
        printf("| %-20s ", ref->type);

        // Exibir Ano
        printf("| %-20d ", ref->year);

        // Exibir Local
        printf("| %-20s ", ref->publicationLocation);

        // Exibir Páginas
        printf("| %-20d ", ref->numPages);

        // Exibir HTTP
        printf("| %-20s ", ref->httpAddress);

        // Exibir Autores
        printf("| ");
        for (int j = 0; j < ref->numAuthors; j++)
        {
            printf("%s %s", ref->authors[j].firstName, ref->authors[j].lastName);
            if (j < ref->numAuthors - 1)
            {
                printf(", ");
            }
        }
        int length = 20 - (strlen(ref->httpAddress) / 2);
        for (int k = 0; k < length; k++)
        {
            printf(" ");
        }
        printf(" |");

        // Exibir Palavras-chave
        printf(" ");
        for (int k = 0; k < ref->numKeywords; k++)
        {
            printf("%s", ref->keywords[k]);
            if (k < ref->numKeywords - 1)
            {
                printf(", ");
            }
        }
        printf(" |\n");
        printf("+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+----------------------+\n");
    }
}

// Função para validar campos obrigatórios ao inserir uma referência
bool validateReference(Reference *ref)
{
    bool valid = true;

    if (strlen(ref->name) == 0)
    {
        printf("Nome da publicação não pode estar vazio.\n");
        valid = false;
    }

    if (strlen(ref->type) == 0)
    {
        printf("Tipo de publicação não pode estar vazio.\n");
        valid = false;
    }

    if (ref->numAuthors <= 0)
    {
        printf("Número de autores deve ser maior que zero.\n");
        valid = false;
    }

    if (ref->year <= 0)
    {
        printf("Ano de publicação deve ser um valor positivo.\n");
        valid = false;
    }

    if (strlen(ref->publicationLocation) == 0)
    {
        printf("Local de publicação não pode estar vazio.\n");
        valid = false;
    }

    if (ref->numPages <= 0)
    {
        printf("Número de páginas deve ser maior que zero.\n");
        valid = false;
    }

    if (!isValidURL(ref->httpAddress))
    {
        printf("Endereço HTTP inválido. Deve começar com http:// ou https://.\n");
        valid = false;
    }

    if (ref->numKeywords <= 0)
    {
        printf("Número de palavras-chave deve ser maior que zero.\n");
        valid = false;
    }

    return valid;
}

// Função para inserir uma nova referência
void insertReference(Database *db)
{
    db->references = realloc(db->references, (db->numReferences + 1) * sizeof(Reference));
    if (db->references == NULL)
    {
        printf("Erro ao alocar memória para novas referências.\n");
        exit(EXIT_FAILURE);
    }

    Reference *newRef = &db->references[db->numReferences];

    printf("Digite o ID da referência: ");
    fgets(newRef->id, MAX_STRING_LENGTH, stdin);
    newRef->id[strcspn(newRef->id, "\n")] = '\0';

    // Verificar unicidade do ID da referência
    for (int i = 0; i < db->numReferences; i++)
    {
        if (strcmp(db->references[i].id, newRef->id) == 0)
        {
            printf("Referência com este ID já existe.\n");
            return;
        }
    }

    printf("Digite o nome da publicação: ");
    fgets(newRef->name, MAX_STRING_LENGTH, stdin);
    newRef->name[strcspn(newRef->name, "\n")] = '\0';

    printf("Digite o tipo de publicação: ");
    fgets(newRef->type, MAX_STRING_LENGTH, stdin);
    newRef->type[strcspn(newRef->type, "\n")] = '\0';

    printf("Digite o número de autores: ");
    scanf("%d", &newRef->numAuthors);
    getchar(); // Limpar o caractere de nova linha deixado pelo scanf

    newRef->authors = malloc(newRef->numAuthors * sizeof(Author));
    if (newRef->authors == NULL)
    {
        printf("Erro ao alocar memória para autores.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < newRef->numAuthors; i++)
    {
        printf("Digite o ID do autor %d: ", i + 1);
        fgets(newRef->authors[i].id, MAX_STRING_LENGTH, stdin);
        newRef->authors[i].id[strcspn(newRef->authors[i].id, "\n")] = '\0';

        printf("Digite o nome do autor %d: ", i + 1);
        fgets(newRef->authors[i].firstName, MAX_STRING_LENGTH, stdin);
        newRef->authors[i].firstName[strcspn(newRef->authors[i].firstName, "\n")] = '\0';

        printf("Digite o apelido do autor %d: ", i + 1);
        fgets(newRef->authors[i].lastName, MAX_STRING_LENGTH, stdin);
        newRef->authors[i].lastName[strcspn(newRef->authors[i].lastName, "\n")] = '\0';
    }

    printf("Digite o ano de publicação: ");
    scanf("%d", &newRef->year);
    getchar();

    printf("Digite o local de publicação: ");
    fgets(newRef->publicationLocation, MAX_STRING_LENGTH, stdin);
    newRef->publicationLocation[strcspn(newRef->publicationLocation, "\n")] = '\0';

    printf("Digite o número de páginas: ");
    scanf("%d", &newRef->numPages);
    getchar();

    printf("Digite o endereço HTTP: ");
    fgets(newRef->httpAddress, MAX_STRING_LENGTH, stdin);
    newRef->httpAddress[strcspn(newRef->httpAddress, "\n")] = '\0';

    printf("Digite o número de palavras-chave: ");
    scanf("%d", &newRef->numKeywords);
    getchar();

    newRef->keywords = malloc(newRef->numKeywords * sizeof(char *));
    if (newRef->keywords == NULL)
    {
        printf("Erro ao alocar memória para palavras-chave.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < newRef->numKeywords; i++)
    {
        newRef->keywords[i] = malloc(MAX_STRING_LENGTH * sizeof(char));
        if (newRef->keywords[i] == NULL)
        {
            printf("Erro ao alocar memória para uma palavra-chave.\n");
            exit(EXIT_FAILURE);
        }

        printf("Digite a palavra-chave %d: ", i + 1);
        fgets(newRef->keywords[i], MAX_STRING_LENGTH, stdin);
        newRef->keywords[i][strcspn(newRef->keywords[i], "\n")] = '\0';

        // Verificar duplicidade de palavras-chave
        if (isDuplicateKeyword(newRef->keywords, i, newRef->keywords[i]))
        {
            printf("Palavra-chave duplicada, não adicionada.\n");
            free(newRef->keywords[i]);
            i--; // Reduzir o índice para reentrar na iteração
        }
    }

    if (validateReference(newRef))
    {
        db->numReferences++;
        showReferences(db); // Exibir a tabela de referências após inserção
    }
    else
    {
        // Liberar memória em caso de referência inválida
        for (int i = 0; i < newRef->numKeywords; i++)
        {
            free(newRef->keywords[i]);
        }
        free(newRef->keywords);
        free(newRef->authors);
    }
}

// Função para liberar a memória alocada para uma referência
void freeReference(Reference *ref)
{
    if (ref)
    {
        free(ref->authors);
        for (int i = 0; i < ref->numKeywords; i++)
        {
            free(ref->keywords[i]);
        }
        free(ref->keywords);
    }
}

// Função para liberar a memória do banco de dados
void freeDatabase(Database *db)
{
    if (db)
    {
        for (int i = 0; i < db->numReferences; i++)
        {
            freeReference(&db->references[i]);
        }
        free(db->references);
        free(db->authors);
    }
}

int main()
{
    Database db = {NULL, 0, NULL, 0};

    // Exemplo de uso
    insertAuthor(&db);
    insertReference(&db);

    // Liberação de memória antes de encerrar o programa
    freeDatabase(&db);

    return 0;
}

// SALVAR ARQUIVO APÓS ALTERAÇÃO (MUITO PARECIDO DO QUE FOI FEITO EM FUP)