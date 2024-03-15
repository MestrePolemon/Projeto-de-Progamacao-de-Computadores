#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct
{
    int dia;
    int mes;
    int ano;
} data;
typedef struct
{
    int id;
    char nome[100];
    data dataNascimento;
    char endereco[100];
    char email[50];
    char telefone[15];
    char cpf[11];
    char plano[20];
    char line[256];
} socio;
int menu()
{
    int opcao;
    fflush(stdin);
    printf("**************************************************\n");
    printf("Bem vindo ao sistema de cadastro de socios!\n");
    printf("1 - Cadastrar socio\n");
    printf("2 - Listar socios\n");
    printf("3 - Buscar socio\n");
    printf("4 - Desativar socio\n");
    printf("5 - Reativar socio\n");
    printf("6 - Remover socio\n");
    printf("7 - Planos\n");
    printf("8 - Sair\n");
    printf("**************************************************\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    return opcao;
};
int ID()
{
    FILE *geral;
    int id = 0;
    char linha[] = "Basico R$60,00\tPremium R$180,00\tVIP R$ 330,00\n";
    geral = fopen("geral.txt", "r");
    if (geral == NULL)
    {
        id = 1;
    }
    else
    {
        fscanf(geral, "ID = %d", &id);
        fclose(geral);
        id++;
    }
    geral = fopen("geral.txt", "w");
    if (geral == NULL)
    {
        printf("Problema ao abrir o arquivo de ID");
        return 1;
    }
    fprintf(geral, "ID = %d\n", id);
    fprintf(geral, "Planos:\n");
    fprintf(geral, "%s", linha);
    fclose(geral);
    return id;
}
void cadastro(socio **s, int *n)
{
    FILE *arquivo;
    *n += 1;
    *s = (socio *)realloc(*s, *n * sizeof(socio));
    (*s)[*n - 1].id = ID();
    fflush(stdin);
    printf("Digite o nome do socio: ");
    gets((*s)[*n - 1].nome);
    printf("Digite o dia de nascimento do socio: ");
    scanf("%d", &(*s)[*n - 1].dataNascimento.dia);
    printf("Digite o mes de nascimento do socio: ");
    scanf("%d", &(*s)[*n - 1].dataNascimento.mes);
    printf("Digite o ano de nascimento do socio: ");
    scanf("%d", &(*s)[*n - 1].dataNascimento.ano);
    fflush(stdin);
    printf("Digite o endereco do socio: ");
    gets((*s)[*n - 1].endereco);
    printf("Digite o email do socio: ");
    gets((*s)[*n - 1].email);
    printf("Digite o telefone do socio: ");
    gets((*s)[*n - 1].telefone);
    printf("Digite o cpf do socio(sem pontos ou traco): ");
    gets((*s)[*n - 1].cpf);
    system("cls");
    arquivo = fopen("socios.txt", "a");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    fprintf(arquivo, "%d\t", (*s)[*n - 1].id);
    fprintf(arquivo, "%s\t", (*s)[*n - 1].nome);
    fprintf(arquivo, " %d", (*s)[*n - 1].dataNascimento.dia);
    fprintf(arquivo, "/%d", (*s)[*n - 1].dataNascimento.mes);
    fprintf(arquivo, "/%d\t", (*s)[*n - 1].dataNascimento.ano);
    fprintf(arquivo, "%s\t", (*s)[*n - 1].endereco);
    fprintf(arquivo, "%s\t", (*s)[*n - 1].email);
    fprintf(arquivo, "%s\t", (*s)[*n - 1].telefone);
    fprintf(arquivo, "%s\n", (*s)[*n - 1].cpf);
    fclose(arquivo);
    printf("Socio cadastrado com sucesso!\n");
}
int comparaNome(const void *a, const void *b)
{
    socio *socioA = (socio *)a;
    socio *socioB = (socio *)b;
    return strcmp(socioA->nome, socioB->nome);
}
int comparaCPF(const void *a, const void *b)
{
    socio *socioA = (socio *)a;
    socio *socioB = (socio *)b;
    return strcmp(socioA->cpf, socioB->cpf);
}
void lista()
{
    int opcao;
    printf("Como deseja listar os socios?\n");
    printf("1 - Listar por numero\n");
    printf("2 - Listar socios por nome\n");
    printf("3 - Listar socios por CPF\n");
    scanf("%d", &opcao);
    system("cls");
    switch (opcao)
    {
    case 1:
        listaNumero();
        break;
    case 2:
        listaNome();
        break;
    case 3:
        listaCPF();
        break;
    default:
        printf("Opcao invalida!\n");
        break;
    }
}
void listaNumero()
{
    FILE *arquivo;
    char linha[256];
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        printf("%s", linha);
    }
    fclose(arquivo);
}
void listaNome()
{
    socio *s = NULL;
    int numSocios = 0;
    FILE *arquivo;
    char linha[256];
    char *nome;
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        numSocios++;
        s = realloc(s, numSocios * sizeof(socio));
        strcpy(s[numSocios - 1].line, linha);
        nome = strtok(linha, "\t");
        nome = strtok(NULL, "\t");
        if (nome != NULL)
        {
            strcpy(s[numSocios - 1].nome, nome);
        }
    }
    fclose(arquivo);
    qsort(s, numSocios, sizeof(socio), comparaNome);
    for (int i = 0; i < numSocios; i++)
    {
        printf("%s", s[i].line);
    }
    free(s);
    return 0;
}
void listaCPF()
{
    FILE *arquivo;
    char linha[256];
    socio *s = NULL;
    int numSocios = 0;
    char *campo;
    int i;
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        numSocios++;
        s = realloc(s, numSocios * sizeof(socio));
        strcpy(s[numSocios - 1].line, linha);
        campo = strtok(linha, "\t");
        for (i = 0; i < 6 && campo != NULL; i++)
        {
            campo = strtok(NULL, "\t");
        }
        if (campo != NULL)
        {
            strcpy(s[numSocios - 1].cpf, campo);
        }
    }
    qsort(s, numSocios, sizeof(socio), comparaCPF);
    for (int i = 0; i < numSocios; i++)
    {
        printf("%s", s[i].line);
    }
    free(s);
    fclose(arquivo);
}
void consulta()
{
    FILE *arquivo;
    char linha[256];
    char cpf[12];
    printf("Digite o cpf do socio que deseja buscar: ");
    scanf("%s", cpf);
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, cpf) != NULL)
        {
            printf("Socio encontrado:\n %s\n", linha);
            fclose(arquivo);
            return 0;
        }
    }
    printf("Socio nao encontrado.\n");
    fclose(arquivo);
}
void desativar()
{
    FILE *arquivo;
    FILE *arquivoTemp;
    char linha[256];
    char dados[256];
    fflush(stdin);
    printf("Digite o cpf ou nome do socio que deseja desativar: ");
    gets(dados);
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    arquivoTemp = fopen("sociosTemp.txt", "w");
    if (arquivoTemp == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, dados) != NULL)
        {
            fprintf(arquivoTemp, "(DESATIVADO)\t%s", linha);
            printf("Socio desativado com sucesso!\n");
        }
        else
        {
            fprintf(arquivoTemp, "%s", linha);
        }
    }
    fclose(arquivo);
    fclose(arquivoTemp);
    remove("socios.txt");
    rename("sociosTemp.txt", "socios.txt");
}
void reativar()
{
    FILE *arquivo;
    FILE *arquivoTemp;
    char linha[256];
    char dados[256];
    fflush(stdin);
    printf("Digite o cpf ou nome do socio que deseja reativar: ");
    gets(dados);
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    arquivoTemp = fopen("sociosTemp.txt", "w");
    if (arquivoTemp == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, dados) != NULL)
        {
            if (strstr(linha, "(DESATIVADO)") != NULL)
            {
                fprintf(arquivoTemp, "%s", linha + 13);
                printf("Socio reativado com sucesso!\n");
            }
        }
        else
        {
            fprintf(arquivoTemp, "%s", linha);
        }
    }
    fclose(arquivo);
    fclose(arquivoTemp);
    remove("socios.txt");
    rename("sociosTemp.txt", "socios.txt");
}
void remover()
{
    socio *s = NULL;
    int numSocios = 0;
    FILE *arquivo;
    FILE *arquivoTemp;
    char linha[256];
    char dados[256];
    fflush(stdin);
    printf("Digite o cpf ou nome do socio que deseja remover: ");
    gets(dados);
    arquivo = fopen("socios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    arquivoTemp = fopen("sociosTemp.txt", "w");
    if (arquivoTemp == NULL)
    {
        printf("Problema ao abrir o arquivo");
        return 1;
    }
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (strstr(linha, dados) == NULL)
        {
            fprintf(arquivoTemp, "%s", linha);
            numSocios++;
        }
    }
    s = realloc(s, numSocios * sizeof(socio));
    printf("Sentiremos sua falta! %s\n", strtok(dados, "\t"));
    printf("Socio removido com sucesso!\n");
    fclose(arquivo);
    fclose(arquivoTemp);
    remove("socios.txt");
    rename("sociosTemp.txt", "socios.txt");
}
void plano(char escolha)
{
    socio *s = NULL;
    int numSocios = 0;
    FILE *arquivo, *arquivoTemp;
    char linha[256];
    char cpf[12];
    char plano[20];
    fflush(stdin);
    if (escolha == 'S' || escolha == 's')
    {
        printf("Digite o cpf do socio que deseja aderir a um plano: ");
        scanf("%s", cpf);
        printf("Digite o plano que deseja aderir: ");
        scanf("%s", plano);
        arquivo = fopen("socios.txt", "r");
        if (arquivo == NULL)
        {
            printf("Problema ao abrir o arquivo");
            return 1;
        }
        arquivoTemp = fopen("sociosTemp.txt", "w");
        if (arquivoTemp == NULL)
        {
            printf("Problema ao abrir o arquivo");
            return 1;
        }
        while (fgets(linha, sizeof(linha), arquivo))
        {
            numSocios++;
            s = realloc(s, numSocios * sizeof(socio));
            if (strstr(linha, cpf) != NULL)
            {
                printf("Socio encontrado:\n %s\n", linha);
                linha[strlen(linha) - 1] = '\0';
                fprintf(arquivoTemp, "%s\t Plano: %s\n", linha, plano);
                printf("Plano aderido com sucesso!\n");
                strcpy(s[numSocios - 1].plano, plano);
            }
            else
            {
                fprintf(arquivoTemp, "%s", linha);
            }
        }
        fclose(arquivo);
        fclose(arquivoTemp);
        remove("socios.txt");
        rename("sociosTemp.txt", "socios.txt");
    }
}
int main()
{
    socio *s = NULL;
    int opcao = 0, n = 0;
    char escolha;
    s = (socio *)malloc(n * sizeof(socio));
    while (opcao != 8)
    {
        opcao = menu();
        system("cls");
        switch (opcao)
        {
        case 1:
            cadastro(&s, &n);
            break;
        case 2:
            lista();
            break;
        case 3:
            consulta();
            break;
        case 4:
            desativar();
            break;
        case 5:
            reativar();
            break;
        case 6:
            remover();
            break;
        case 7:
            fflush(stdin);
            printf("Temos os seguintes planos mensais:\n");
            printf("1 - Plano basico = R$60,00\n");
            printf("2 - Plano Premium R$180,00\n");
            printf("3 - Plano VIP R$ 330,00\n");
            printf("Gostaria de aderir a algum plano? (S/N): ");
            scanf("%c", &escolha);
            plano(escolha);
            break;
        case 8:
            printf("Obrigado por utilizar nosso sistema!\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
    free(s);
    return 0;
}