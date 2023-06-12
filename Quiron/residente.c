#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login_cadastro.h"
#include "residente.h"
#include "preceptor.h"
#include "residentes_preceptores.h"
#include "interface.h"

// Coisas do Residente
// colocar opcao de cancelar o envio das notas do feedback na funcao fazer_feedback_para_preceptor
// mudar o conteudo da variavel criterio para ficar de acordo com o figma na função fazer_feedback_para_preceptor
// mudar printf na função fazer_feedback_para_preceptor para ficar de acordo com o figma
// mudar nome das variaveis na funcao fazer_feedback_para_preceptor. Atualmente esta vago/confuso o que cada variavel faz e é
// mudar printf dentro do if de checagem 1 < || > 5 para numero, visto que usuario nao digita a avaliacao e sim o numero que deseja
// mudar printf de fazer comentario sobre o preceptor na funcao fazer_feedback_para_preceptor para ficar de acordo com o figma 
// Verificar se peu colocou as #include dos arquivos .h na ordem correta, com suas dependencias verificadas para estar na ordem de quem depende de quem
// trocar nome do arquivo "avaliacao_preceptor.txt" na funcao fazer_feedback_para_preceptor e salvar_feedback_preceptor para "feedback_residentes.txt" para ficar igual aos outros arquivos
// verificar ortografia nos prints | alguns prints estao com "ç" ou acentou ou "~"
// ajustar a formatação da funcao ver_feedback_residente() para que fique no lugar dos numeros, as palavras que estao na funcao converter_feedback_para_texto() | esta localizada no arquivo resisdentes_preceptores.c
// ajustar a formatação na funcao ver_feedback_resisdente() para que fique um em baixo do outro

extern Usuario usuario_logado;

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
    FILE *fp = fopen("feedbacks_residentes.txt", "r");
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
            fazer_feedback_para_preceptor();
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
            salvar_feedback_preceptor(preceptor_selecionado, avaliacao_criterio[i]);
        }
        // Salve o comentário como uma avaliação
        salvar_feedback_preceptor(preceptor_selecionado, comentario);
        
        printf("\nAvaliacoes e comentario atribuidos com sucesso!");
        menu_residente();
    }
    else
    {
        printf("Opcao invalida. Tente novamente.\n");
        fazer_feedback_para_preceptor();
    }
}


void salvar_feedback_preceptor(Usuario preceptor_selecionado, char* avaliacao)
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