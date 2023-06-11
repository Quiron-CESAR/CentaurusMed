#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "login_cadastro.h"
#include "residentes_preceptores.h"

extern Usuario usuario_logado;

// Ao atribuir a nota, especificar qual foi o preceptor que atribuiu
// fazer pagina de feedback dos residentes para o preceptor
// Lembrar de pedir para expandir o terminal para melhor visualização do programa

void main_menu()
{
    system("cls");
    unsigned int op, id;
    printf("[1]Login\n[0]Finalizar Programa\nSelecione o que desejar: ");
    scanf("%d", &op);
    system("cls");

    switch (op)
    {
    case 1:

        switch (id=login())
        {
        case 1:
            menu_preceptor();
            break;
        
        case 2:
            menu_residente();
            break;
        
        case 3:
            menu_coordenacao();
            break;

        default:
            printf("Login Invalido! Tente novamente\n");
            main_menu();
            break;
        }
    break;

    case 0:
        system("cls");
        printf("Obrigado e ate a proxima :) \n");
        exit(0);
        break;

    default:
        system("cls");
        printf("Opcao invalida! Tente novamente\n");
        main_menu();
        break;
    }
}

void menu_coordenacao()
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};
    char *email;
    
    system("cls");
    printf("--- Coordenacao ---\n");
    printf("[1]Anestesia\n[2]Cardiologia\n[3]Cirurgia Geral\n[4]Clinica Geral\n[0]Sair da conta\nSelecione o que desejar: ");
    scanf("%d", &op);

    if (op > 0 && op <= 4)
    {
        printf("====%s====\n", residencias[op-1]);
        printf("[+]Cadastrar novo usuario[/]Voltar[?]Acessar usuario\n");

        printf("Preceptores: \n");
        printar_residentes_preceptores(op, 1);
        printf("Residentes: \n");
        printar_residentes_preceptores(op, 2);

        scanf("\n%c", &opcao);
        switch(opcao)
        {
            case '+':
                cadastrar(op);
                menu_coordenacao();
                break;

            case '/':
                menu_coordenacao();
                break;

            case '?':
                printf("Digite o nome do usuario: ");
                scanf(" %[^\n]", email);
                // dados do usuario
            default:
                printf("Opcao invalida!");
                menu_coordenacao();
        }
    }
    else if(op == 0)
    {
        main_menu();
    }
    else
    {
        printf("Opcao invalida! Tente novamente\n");
        menu_coordenacao();
    }
}


void menu_residente()
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Residentes ---\n");
    printf("%s\n", usuario_logado.email);
    printf("%s | Residentes\n", residencias[usuario_logado.idResidencia -1]);

    printf("[1]Ver atividades\n[2]Visulizar avaliacoes\n[3]Visualizar feedback\n"
    "[4]Avaliacao do feedback\n[0]Sair da conta\nSelecione qual opcao deseja visualizar: ");
    scanf("%d", &op);
    switch(op) 
    {
        case 1:
            ver_atividades_residente();
            break;
        case 2:
            printar_notas_residente(usuario_logado);
            break;
        case 3:
            ver_feedback_residente();
            break;
        case 4:
            fazer_feedback_para_preceptor();
            break;
        case 0:
            main_menu();
            break;
        default:
            printf("opçao invalida! tente novamente\n");
            menu_residente();
            break;
    }

}

void menu_preceptor()
{
    unsigned int op;
    char opcao;
    char residencias[4][15] = {"Anestesia", "Cardiologia", "Cirurgia Geral", "Clinica Geral"};


    system("cls");
    printf("--- Preceptor ---\n");
    printf("%s\n", usuario_logado.email);
    printf("%s | Preceptor", residencias[usuario_logado.idResidencia -1]);

    printf("\n\n[1]Atividades\n[2]Avisos\n[3]Residentes\n[4]Sair da Conta\nSelecione o que deseja: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        //atividades
        atividades();
        break;

    case 2:
        //avisos
        avisos_preceptor();
        break;

    case 3:
        //residentes
        lista_residentes();
        break;

    case 4:
        //sair
        main_menu();
        break;
    
    default:
        printf("Opcao invalida! Tente novamente.\n");
        menu_preceptor();
        break;
    }
}

void atividades()
{
    unsigned int op;

    system("cls");
    printf("--- Atividades ---\n");
    printf("[1]Exame\n13/06/2023  12:30\n\n"
            "[2]Cirurgia\n13/06/2023  12:30\n\n"
            "[3]Estudo de Caso\n13/06/2023  12:30\n\n"
            "[4]Sair\n\nSelecione o que desejar: ");

    scanf("%d", &op);

    switch (op)
    {
    case 1:
        //exame
        opcoes_atividade();
        break;
    case 2:
        //cirurgia
        opcoes_atividade();
        break;
    case 3:
        //estudo de caso
        opcoes_atividade();
        break;
    case 4:
        //sair
        menu_preceptor();
        break;
    default:
        printf("Opcao invalida! Tente novamente.\n");
        atividades();
        break;
    }
}

void opcoes_atividade()
{
    char opcao;

    system("cls");
    printf("\nDescricao:\n(Descricao da Atividade)\n\n[+]Avaliar\n[/]Voltar\nSelecione o que desejar: ");
    scanf("\n%c", &opcao);

    if(opcao == '+')
    {
        avaliar_residente();
    }
    else if(opcao == '/')
    {
        atividades();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n");
        atividades();
    }
}

void avaliar_residente()
{
    Usuario residente_selecionado;
    char criterio[9][50] = {"Assiduidade", "Pontualidade", "Iniciativa", "Postura Etico-Profissional", "Relacionamento em equipe",
    "Espirito Critico", "Comunicacao", "Habilidades Especificas", "Participacao nas Atividades"};
    char nota_criterio[9][50];
    char opcao;
    float media_residente = 0;

    printf("Qual o email do residente que voce deseja avaliar? ");
    scanf(" %[^\n]", residente_selecionado.email);
    
    if(residente_existe(residente_selecionado) == 0) 
    {
        printf("\nResidente nao encontrado! Tente novamente.\n");
        avaliar_residente();
    }

    system("cls");
    printf("--- Avaliacao Pratica | Exame ---\n");
    printf("%s\nTipo de Avaliacao: Pratica", residente_selecionado.email);

    for (int i = 0; i < 9; i++)
    {
        printf("\n%s: ", criterio[i]);
        scanf(" %s", nota_criterio[i]);
        int verificar = nota_criterio[i][0] - '0';
        if(verificar < 1 || strlen(nota_criterio[i]) > 1 || verificar > 5)
        {
            printf("\nNota invalida! Apenas notas entre 1 e 5.\n");
            avaliar_residente();
        }
    }

    printf("[+]Enviar: \n[/]Cancelar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+')
    {
        for (int i = 0; i < 9; i++)
        {
            media_residente += (nota_criterio[i][0] - '0') * 2;
        }
        media_residente /= 9;
        char media_char[10];
        sprintf(media_char, "%.2f", media_residente);
        salvar_nota_residente(residente_selecionado, media_char);
        printf("\nNotas atribuidas com sucesso!");
        opcoes_atividade();
    }
    else
    {
        avaliar_residente();
    }
}

void avisos_preceptor()
{
    unsigned int op;

    system("cls");
    printf("--- Avisos ---");
    printf("\nFeedback Disponivel\n(Aviso 1)\n(Aviso 2)");
    printf("\n[1]Voltar: ");

    scanf("%d", &op);
    if(op == 1)
    {
        menu_preceptor();
    }
    else
    {
        printf("\nOpcao invalida. Tente novamente.");
        avisos_preceptor();
    }
}

void salvar_nota_residente(Usuario residente_selecionado, char* nota) 
{
    FILE *fp = fopen("notas_residentes.txt", "a"); // abrir o arquivo em modo anexação
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    // escrever os detalhes no final do arquivo
    fprintf(fp, "\n%s %s %s", residente_selecionado.email, usuario_logado.email, nota);

    fclose(fp);
}

void lista_residentes()
{
    Usuario user, auth, residente_selecionado;   

    FILE *fp = fopen("cadastrados.txt", "r");

    char linha[69];
    while(fgets(linha, 70, fp) != NULL)
    {
        char* token = strtok(linha, " ");

        auth.idCargo = atoi(token);
        token = strtok(NULL, " ");
        strcpy(auth.email, token);
        token = strtok(NULL, " ");
        strcpy(auth.senha, token);
        token = strtok(NULL, " ");
        auth.idResidencia = atoi(token);

        if(auth.idCargo == 2 && auth.idResidencia == usuario_logado.idResidencia)
        {
            printf("%s\n", auth.email);
        }
    }

    printf("Selecione o residente que deseja visualizar: ");
    scanf(" %[^\n]", residente_selecionado.email);

    if(residente_existe(residente_selecionado) == 0) 
    {
        printf("\nResidente nao encontrado! Tente novamente.\n");
        strcpy(residente_selecionado.email, NULL);
        fclose(fp);
        lista_residentes();
    }
    fclose(fp);
    perfil_residente(residente_selecionado, auth);
}

void perfil_residente(Usuario residente_selecionado, Usuario auth)
{
    system("cls");
    printf("--- Avaliacao Geral ---");
    printf("\n%s", residente_selecionado.email);

    switch (auth.idResidencia)
    {
    case 0:
        // Anestesia
        printf("\nAnestesia | Residente");
        break;
    case 1:
        // Cardiologia
        printf("\nCardiologia | Residente");
        break;
    case 2:
        // Cirurgia geral
        printf("\nCirurgia geral | Residente");
        break;
    case 3:
        // Clinica Geral
        printf("\nClinica Geral | Residente");
        break;
    
    default:
        printf("\nResidentecia invalida. Tente novamente");
        lista_residentes();
        break;
    }
    printf("\n\n--- Grafico de Notas ---\n\n");
    printar_grafico();
    printf("\nAvalicoes Individuais");
    printar_notas_residente(residente_selecionado);
}

void printar_grafico() 
{

    int max = 0;
    int valores[9] = {5, 3, 5, 5, 2, 3, 4, 3, 5}; // Valores pre definidos por nos | Puramente estetico
    int tamanho = 9;

    for(int i = 0; i < tamanho; i++) 
    {
        if(valores[i] > max) 
        {
            max = valores[i];
        }
    }
    // Desenha o gráfico
    for(int i = 0; i < tamanho; i++) 
    {
        printf("%2d | ", i + 1);
        int barra = (valores[i] * 50) / max;  
        for(int j = 0; j < barra; j++) 
        {
            printf("#");
        }
        printf(" %d\n", valores[i]);
    }
    // Desenha a linha inferior
    printf("    ");
    for(int i = 0; i < 52; i++) 
    {
        printf("-");
    }
    printf("\n");
}

void printar_notas_residente(Usuario residente_selecionado)
{
    FILE *fp = fopen("notas_residentes.txt", "r");

    char linha[69];
    char nome_preceptor[69];
    char nome_residente[69];
    float nota_residente;

    while(fgets(linha, 70, fp) != NULL)
    {
        char* token = strtok(linha, " ");

        strcpy(nome_residente, token);
        token = strtok(NULL, " ");
        strcpy(nome_preceptor, token);
        token = strtok(NULL, " ");
        nota_residente = atof(token);

        if(strcmp(nome_residente, residente_selecionado.email) == 0)
        {
            printf("\n%s %0.2f", nome_preceptor, nota_residente);
        }   
    }
    fclose(fp);
}

int residente_existe(Usuario residente_selecionado) 
{
    FILE *fp = fopen("cadastrados.txt", "r");
    char linha[69];
    char email[50];

    while (fgets(linha, sizeof(linha), fp)) 
    {
        sscanf(linha, "%*d %s", email);  // ignora o primeiro campo e lê o segundo (email)
        if (strcmp(email, residente_selecionado.email) == 0) 
        {
            fclose(fp);
            return 1;  // encontrado
        }
    }

    fclose(fp);
    return 0;  // não encontrado
}

void ver_atividades_residente() 
{
    FILE *fp = fopen("atividades.txt", "r");
    if (fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo de atividades.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), fp) != NULL) 
    {
        printf("%s", linha);
    }

    fclose(fp);
}

void ver_feedback_residente() 
{
    FILE *fp = fopen("feedback.txt", "r");
    if (fp == NULL) {
        printf("Nao foi possivel abrir o arquivo de feedbacks.\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}

char* converter_avaliacao_para_texto(int avaliacao) 
{
    switch(avaliacao) {
        case 1: return "Muito Ruim";
        case 2: return "Ruim";
        case 3: return "Moderado";
        case 4: return "Bom";
        case 5: return "Muito Bom";
        default: return "Invalido";
    }
}

void fazer_feedback_para_preceptor()
{
    Usuario preceptor_selecionado;
    char criterio[7][50] = {"Relacionamento com os residentes", "Assiduidade", "Metodologia de ensino", 
                            "Nivel de conhecimento", "Pontualidade", "Esclarecimento de duvidas",
                            "Incentiva a participacao do aluno"};
    char avaliacao_criterio[7][50];
    char opcao;

    printf("Qual o email do preceptor que voce deseja avaliar? ");
    scanf(" %[^\n]", preceptor_selecionado.email);

    system("cls");
    printf("--- Avaliacao de Feedback ---\n");
    printf("%s\n", preceptor_selecionado.email);

    for (int i = 0; i < 7; i++)
    {
        printf("\n%s: ", criterio[i]);
        printf("\n[1] Muito Ruim\n[2] Ruim\n[3] Moderado\n[4] Bom\n[5] Muito Bom\nSelecione a avaliacao: ");
        scanf("%s", avaliacao_criterio[i]);
        int avaliacao = atoi(avaliacao_criterio[i]);
        if(avaliacao < 1 || avaliacao > 5)
        {
            printf("\nAvaliacao invalida! Apenas avaliacoes entre 1 e 5.");
            avaliar_feedback();
        }
    }

    char comentario[100];
    printf("\nDigite um comentario sobre o preceptor: ");
    scanf(" %[^\n]", comentario);

    printf("[+]Enviar: ");
    scanf("\n%c", &opcao);
    if(opcao == '+'){
        for (int i = 0; i < 7; i++)
        {
            salvar_avaliacao_preceptor(preceptor_selecionado, avaliacao_criterio[i]);
        }
        // Salve o comentário como uma avaliação
        salvar_avaliacao_preceptor(preceptor_selecionado, comentario);
        
        printf("\nAvaliacoes e comentario atribuidos com sucesso!");
        menu_residente();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n");
        avaliar_feedback();
    }
}


void salvar_avaliacao_preceptor(Usuario preceptor_selecionado, char* avaliacao)
{
    FILE *fp = fopen("avaliacao_preceptor.txt", "a+");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }
    fclose(fp);

    fp = fopen("avaliacao_preceptor.txt", "r");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    char linhas[100][100];
    int num_linhas = 0;
    int preceptor_found = 0;

    char linha[100];
    while(fgets(linha, sizeof(linha), fp) != NULL) 
    {
        linha[strcspn(linha, "\n")] = 0;  // remover a nova linha do final
        if(strlen(linha) == 0) 
        {
            continue;  // ignorar linhas vazias
        }

        if(strstr(linha, preceptor_selecionado.email) != NULL) 
        {
            strcat(linha, " ");
            strcat(linha, avaliacao);
            preceptor_found = 1;
        }
        strcpy(linhas[num_linhas++], linha);
    }

    if(!preceptor_found)  // se o preceptor não foi encontrado, adicione uma nova linha para ele
    {
        strcpy(linha, preceptor_selecionado.email);
        strcat(linha, " ");
        strcat(linha, avaliacao);
        strcpy(linhas[num_linhas++], linha);
    }

    fclose(fp);

    fp = fopen("avaliacao_preceptor.txt", "w");
    if(fp == NULL) 
    {
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }

    for(int i = 0; i < num_linhas; i++) 
    {
        fputs(linhas[i], fp);
        fputs("\n", fp);
    }

    fclose(fp);
}