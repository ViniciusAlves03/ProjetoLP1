#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef struct NO
{

    char cpf[12];
    char nome[30];
    char endereco[80];
    char telefone[12];
    int idade;
    int tempEspera;
    int qntExames;
    int conPar;
    int gPrioridade;
    char dataEntr[10];
    char hora[10];

    struct NO *prox;
} NO, Atendimento;

FILE *ptrArquivo; // Ponteiro responsável pelo arquivo
short int ordemcadastro = 0;


NO paciente;
NO atend[30];
NO atend2[30];
NO *vetorUm;
NO *vetorDois;
int tempEspera = 0;
int contadorGlobal = 0;

typedef struct FILA
{
    NO *ini;
    NO *fim;
} FILA;


void inicializaFila(FILA *f)
{
    f->ini = NULL;
    f->fim = NULL;
}

void enfileira(char cpf[], int idade, int tempEspera, FILA *f)
{

    NO *ptr = (NO *)malloc(sizeof(NO));
    if (ptr == NULL)
    {
        printf("Erro de alocação.\n");
        return;
    }
    else
    {

        strcpy(ptr->cpf, cpf);
        ptr->idade = idade;
        ptr->tempEspera = tempEspera;
        ptr->prox = NULL;
        if (f->ini == NULL)
        {
            f->ini = ptr;
        }
        else
        {
            f->fim->prox = ptr;
        }
        f->fim = ptr;
        return;
    }
}

void enfileira2(FILA *f, int tempEspera, int qntExames, int conPar, char dataEntr[], char hora[], FILA *f2)
{

    //NO *ptr = (NO *)malloc(sizeof(NO));
    NO *ptr = f->ini;
    NO *ptr2 = (NO *)malloc(sizeof(NO));

    if (ptr2 == NULL)
    {
        printf("Erro de alocação.\n");
        return;
    }
    else
    {

        strcpy(ptr2->cpf, ptr->cpf);
        ptr2->idade = ptr->idade;
        ptr2->tempEspera = tempEspera;
        ptr2->qntExames = qntExames;
        ptr2->conPar = conPar;
        strcpy(ptr2->dataEntr, dataEntr);
        strcpy(ptr2->hora, hora);
        ptr2->prox = NULL;
        if (f2->ini == NULL)
        {
            f2->ini = ptr2;
        }
        else
        {
            f2->fim->prox = ptr2;
        }
        f2->fim = ptr2;
        return;
    }
}

int desenfileira(FILA *f)
{

    NO *ptr = f->ini;
    char cpf;
    int idade;
    int tempEspera;
    if (ptr != NULL)
    {
        f->ini = ptr->prox;
        ptr->prox = NULL;

        cpf = *ptr->cpf;
        idade = ptr->idade;
        tempEspera = ptr->tempEspera;

        free(ptr);
        if (f->ini == NULL)
        {
            f->fim = NULL;
        }
        return cpf, idade, tempEspera;
    }
    else
    {
        printf("Fila vazia.\n");
        return printf("erro1");
    }
}

int desenfileira2(FILA *f2)
{

    NO *ptr2 = f2->ini;
    char cpf;
    int idade;
    int tempEspera;
    int qntExames;
    int conPar;
    char dataEntr;
    char hora;

    if (ptr2 != NULL)
    {
        f2->ini = ptr2->prox;
        ptr2->prox = NULL;

        cpf = *ptr2->cpf;
        idade = ptr2->idade;
        tempEspera = ptr2->tempEspera;
        qntExames = ptr2->qntExames;
        conPar = ptr2->conPar;
        dataEntr = *ptr2->dataEntr;
        hora = *ptr2->hora;

        free(ptr2);
        if (f2->ini == NULL)
        {
            f2->fim = NULL;
        }
        return cpf, idade, tempEspera, qntExames, conPar, dataEntr, hora;
    }
    else
    {
        printf("Fila vazia.\n");
        return printf("erro1");
    }
}

void imprimeFila(FILA *f)
{

    NO *ptr = f->ini;
    if (ptr != NULL)
    {
        printf("\n-------------------FILA 01------------------\n");
        printf("\n");
        while (ptr != NULL)
        {
            printf("cpf = %s idade = %i tempo de espera = %i\n", ptr->cpf, ptr->idade, ptr->tempEspera);
            printf("\n");
            ptr = ptr->prox;
        }
        printf("\n--------------------------------------------\n");
    }

    else
    {
        printf("\nfila vazia.\n\n");
        return;
    }
}

void imprimeFila2(FILA *f2)
{

    NO *ptr2 = f2->ini;
    if (ptr2 == NULL)
    {
        printf("fila inexistente\n");
    }
    printf("\n-------------------FILA 02------------------\n");
    printf("\n");
    do
    {
        printf("cpf =>> %s\n", ptr2->cpf);
        printf("idade =>> %i\n", ptr2->idade);
        printf("tempo => %i\n", ptr2->tempEspera);
        printf("quantidade de exames => %i\n", ptr2->qntExames);
        printf("convenio ou particular => %i\n", ptr2->conPar);
        printf("data de entrega => %s\n", ptr2->dataEntr);
        printf("hora => %s\n", ptr2->hora);
        printf("\n");

        ptr2 = ptr2->prox;
    } while (ptr2 != NULL);
    printf("\n--------------------------------------------\n");
}

NO* fila_p_fVetor(FILA *f, NO *vetor){

    NO *ptr = f->ini;
    if (ptr == NULL)
    {
         printf("fila inexistente\n");
    }
    int contador = 0;
    do
    {
        strcpy(vetor[contador].cpf , ptr->cpf);
        vetor[contador].idade = ptr->idade;
        vetor[contador].tempEspera = contador;

        ptr = ptr->prox;
        contador++;

        contadorGlobal = contador;
      
    }while (ptr != NULL);
  return vetor;
}

NO* fila_p_fVetor2(FILA *f2, NO *vetor){

    NO *ptr2 = f2->ini;
    if (ptr2 == NULL)
    {
         printf("fila inexistente\n");
    }
    int contador =0;
    do
    {
        strcpy(vetor[contador].cpf , ptr2->cpf);
        vetor[contador].idade = ptr2->idade;
        vetor[contador].tempEspera = contador;
        vetor[contador].conPar = ptr2->conPar;
        vetor[contador].qntExames = ptr2->qntExames;
        strcpy(vetor[contador].hora, ptr2->hora);
        strcpy(vetor[contador].dataEntr, ptr2->dataEntr);

        ptr2 = ptr2->prox;
        contador++;
      
    }while (ptr2 != NULL);
  return vetor;
}

void vetor_p_fila(FILA*f, NO *vetor){

  int cont =0;
  NO *ptr = f->ini;
  if (ptr == NULL)
    {
        printf("fila inexistente\n");
    }
    do
    {
      strcpy(ptr->cpf , vetor[cont].cpf);
      ptr->idade = vetor[cont].idade;
      ptr->tempEspera = vetor[cont].tempEspera;
        /* transformção de vetor para a fila 
      printf("---------- vetor pra fila ----------\n");
      
  
      printf("posição[%d] ->> cpf = %s\n",cont, ptr->cpf );
      printf("posição[%d] ->> idade = %i\n",cont,ptr->idade);
      printf("posição[%d] ->> tempo = %i\n", cont, ptr->tempEspera);
      printf("\n");
        */
      ptr = ptr->prox;
      cont ++;
      
    }while (ptr != NULL);  
}

void vetor_p_fila2(FILA *f2, NO *vetor)
{

    int cont = 0;
    NO *ptr2 = f2->ini;
    if (ptr2 == NULL)
    {
        printf("fila inexistente\n");
    }
    do
    {

        strcpy(ptr2->cpf, vetor[cont].cpf);
        ptr2->idade = vetor[cont].idade;
        ptr2->tempEspera = vetor[cont].tempEspera;
        ptr2->qntExames = vetor[cont].qntExames;
        ptr2->conPar = vetor[cont].conPar;
        strcpy(ptr2->hora, vetor[cont].hora);
        strcpy(ptr2->dataEntr, vetor[cont].dataEntr);

        ptr2 = ptr2->prox;
        cont++;

    } while (ptr2 != NULL);
}

void fila_p_fila(FILA *f, FILA *f2){

  NO *ptr = f->ini;
  NO *ptr2 = f2->ini;
  if (ptr2 == NULL)
    {
         printf("fila inexistente\n");
    }
    //printf("\n\t PASSANDO DE UMA PARA OUTRA \t\t\n");
    do
    {
      strcpy(ptr2->cpf , ptr->cpf);
      ptr2->idade = ptr->idade;
      ptr2->qntExames;
      ptr2->conPar;
      ptr2->dataEntr;
      ptr2->tempEspera;
      ptr2->hora;
    
      ptr = ptr->prox;
      ptr2 = ptr2->prox;
    }while (ptr2 != NULL);  
}

int ordenarVetor (NO * vetorDois){

    if(contadorGlobal != 1){
        //printf("O vetor tem %i termos\n", contadorGlobal);
        int i;
        int j;
        for ( i = 0; i < contadorGlobal; i++){
            vetorDois[i].gPrioridade = vetorDois[i].idade * vetorDois[i].tempEspera;
        }

        for ( i = 0; i < contadorGlobal; i++){
            for ( j = 0 ; j < contadorGlobal; j++){

                if (vetorDois[i].gPrioridade > vetorDois[j].gPrioridade){
                    
                    int k = vetorDois[i].gPrioridade;
                    vetorDois[i].gPrioridade = vetorDois[j].gPrioridade;
                    vetorDois[j].gPrioridade = k;

                    int a = vetorDois[i].idade;
                    vetorDois[i].idade = vetorDois[j].idade;
                    vetorDois[j].idade = a;

                    int b = vetorDois[i].tempEspera;
                    vetorDois[i].tempEspera = vetorDois[j].tempEspera;
                    vetorDois[j].tempEspera = b;

                    char c[12];

                    strcpy(c , vetorDois[i].cpf);
                    strcpy(vetorDois[i].cpf , vetorDois[j].cpf);
                    strcpy(vetorDois[j].cpf , c);
                    
                    int d = vetorDois[i].qntExames;
                    vetorDois[i].qntExames = vetorDois[j].qntExames;
                    vetorDois[j].qntExames = d;

            

                } 
                    /*
                    printf("------------Ordenação------------\n");
                    printf(" cpf = %s\n",vetorDois[j].cpf);
                    printf(" idade = %i\n", vetorDois[j].idade);
                    printf(" tempo = %i\n", vetorDois[j].tempEspera);
                    printf(" Prioridade = %i\n", vetorDois[j].gPrioridade);*/
            }
                
        }

        return  vetorUm;
    }
    else{
        return vetorUm;
    }  
}

int ordenarVetor2(NO *vetorDois)
{

    for (int i = 0; i < contadorGlobal; i++)
    {
        for (int j = 0; j < contadorGlobal; j++)
        {

            if (vetorDois[i].qntExames > vetorDois[j].qntExames)
            {

                int k = vetorDois[i].gPrioridade;
                vetorDois[i].gPrioridade = vetorDois[j].gPrioridade;
                vetorDois[j].gPrioridade = k;

                int a = vetorDois[i].idade;
                vetorDois[i].idade = vetorDois[j].idade;
                vetorDois[j].idade = a;

                int b = vetorDois[i].tempEspera;
                vetorDois[i].tempEspera = vetorDois[j].tempEspera;
                vetorDois[j].tempEspera = b;

                char c[12];

                strcpy(c, vetorDois[j].cpf);
                strcpy(vetorDois[i].cpf, vetorDois[j].cpf);
                strcpy(vetorDois[j].cpf, c);

                int d = vetorDois[i].qntExames;
                vetorDois[i].qntExames = vetorDois[j].qntExames;
                vetorDois[j].qntExames = d;
            }
        }
    }

    return vetorUm;
}

void printar_Menu(void)
{

    printf("1. Cadastar paciente\n");
    printf("2. Atendimento inicial\n");
    printf("3. Chamar para atendimento\n");
    printf("4. Chamar para coleta\n");
    printf("5. Mostrar fila para atendimento\n");
    printf("6. Mostrar fila para coleta\n");
    printf("7. Mostrar atendimento do dia\n");
    printf("8. Finalizar o programa\n");
    printf("\n");
}

bool verificarCPF(char cpf[])
{
    char y[12];
    bool x = false;

    FILE *file;
    file = fopen("dados.txt", "r");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo!");
        getchar();
        exit(1);
    }
    while (fgets(y, 12, file) != NULL)
    {
        if (strcmp(cpf, y) == 0)
        {
            x = true;
        }
    }
    if (x == true)
    {
        return true;
    }
    else
    {
        return false;
    }
    fclose(file);
}
void criar_arquivo(){
    FILE *arq;
    arq = fopen("dados.txt", "w");
}
// Funções de validação:
// Retorno: [1] - Se for válido | [0] - Se for inválido
void iniciar_arquivo()
{
    ptrArquivo = fopen("dados.txt", "a");

    if (ptrArquivo == NULL)
    {
        printf("Erro ao abrir arquivo!");
        getchar();
        exit(1);
    }
}

void excluir_arquivo()
{
    fopen("dados.txt", "w");
}

int validar_CPF(char *cpf)
{

    int i, j, digito1 = 0, digito2 = 0;
    if (strlen(cpf) != 11)
        return 0;

    else if ((strcmp(cpf, "00000000000") == 0) || (strcmp(cpf, "11111111111") == 0) || (strcmp(cpf, "22222222222") == 0) ||
             (strcmp(cpf, "33333333333") == 0) || (strcmp(cpf, "44444444444") == 0) || (strcmp(cpf, "55555555555") == 0) ||
             (strcmp(cpf, "66666666666") == 0) || (strcmp(cpf, "77777777777") == 0) || (strcmp(cpf, "88888888888") == 0) ||
             (strcmp(cpf, "99999999999") == 0))
        return 0; // se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        // digito 1---------------------------------------------------
        for (i = 0, j = 10; i < strlen(cpf) - 2; i++, j--) // multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i] - 48) * j;
        digito1 %= 11;
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if ((cpf[9] - 48) != digito1)
            return 0; // se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        // digito 2--------------------------------------------------
        {
            for (i = 0, j = 11; i < strlen(cpf) - 1; i++, j--) /// multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                digito2 += (cpf[i] - 48) * j;
            digito2 %= 11;
            if (digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if ((cpf[10] - 48) != digito2)
                return 0; // se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}

int validar_nome(char *nome)
{

    // verifica se o nome é totalmente alfabético:
    for (register short int i = 0; i < strlen(nome); i++)
    {
        while (nome[i] == ' ')
        {
            i++;
        }
        if (!isalpha(nome[i]))
        {
            return 0;
        }
    }

    return 1;
}

int validar_telefone(char *telefone)
{

    // Verificar a quantidade de caracteres e o préfixo 9:
    if (strlen(telefone) != 11 || telefone[2] != '9')
    {
        return 0;
    }

    else
    {
        // Verificar se o telefone tem alguma letra:
        for (register short int i = 0; i < strlen(telefone); i++)
        {
            if (!isdigit(telefone[i]))
            {
                return 0;
            }
        }
        return 1;
    }
}

int validar_idade(short int idade)
{

    if (idade < 0 || idade > 130)
    {
        return 0;
    }

    return 1;
}


void cadastro(){
    char idadeStr[3];
    iniciar_arquivo();

        
    printf("Digite o seu nome completo: ");
    gets(paciente.nome);
    while (validar_nome(paciente.nome) == 0){
        printf("NOME EM FORMATO INCORRETO!\nDigite um nome valido: ");
        gets(paciente.nome);
    }
    fflush(stdin);
    printf("\n");

    printf("Digite o seu endereco: ");
    gets(paciente.endereco);
    fflush(stdin);
    printf("\n");

    printf("Digite seu telefone no formato (DDD912345678): ");
    gets(paciente.telefone);
    while (validar_telefone(paciente.telefone) == 0){
        printf("TELEFONE INCORRETO!\nDigite um telefone valido: ");
        gets(paciente.telefone);
    }
    fflush(stdin);
    printf("\n");

    printf("Digite a sua idade: ");
    scanf("%hd",&paciente.idade);
    sprintf(idadeStr, "%hd", paciente.idade); //Converter idade para str

    while(validar_idade(paciente.idade) == 0){
        printf("IDADE INCORRETA!\nDigite uma idade valida: ");
        scanf("%hd",&paciente.idade);
    }

    fflush(stdin);
    printf("\n");

    //Salvar informa��es no arquivo:
    fprintf(ptrArquivo,"%s\n", paciente.cpf);
    fprintf(ptrArquivo,"%s\n", paciente.nome);
    fprintf(ptrArquivo,"%s\n", paciente.endereco);
    fprintf(ptrArquivo,"%s\n", paciente.telefone);
    fprintf(ptrArquivo,"%s\n\n", idadeStr);
    fclose(ptrArquivo);
    
        
}

void mostrarAtendimentoDia()
{
    char dadoArquivo[100];
    FILE *file;
    file = fopen("dados.txt", "r");

    if (file == NULL)
    {
        printf("Nao existe arquivo.");
    }

    while (fgets(dadoArquivo, 100, file) != NULL)
    {
        printf("%s", dadoArquivo);
    }

    fclose(file);
}

int main()
{
    FILA *f1 = (FILA *)malloc(sizeof(FILA));
    FILA *f2 = (FILA *)malloc(sizeof(FILA));
    setlocale(LC_ALL, "");
    int contadorPessoasFila1 = 0;
    int contadorPessoasFila2 = 0;
    criar_arquivo();
    if (f1 == NULL)
    {
        printf("Erro de alocação.\n");
        exit(-1);
    }
    else

    {
        inicializaFila(f1);
        inicializaFila(f2);
    }

    short int escolha;
    printar_Menu();
    printf("Digite uma opção: ");
    scanf("%hd", &escolha);

    while (escolha != 8)
    {
        switch (escolha)
        {

        case 1:
            fflush(stdin);
            printf("Digite o seu CPF (apenas numeros): ");
            gets(paciente.cpf);
            while (validar_CPF(paciente.cpf) == 0){
                printf("CPF INCORRETO!\nDigite um CPF valido: ");
                gets(paciente.cpf);
            }
            fflush(stdin);
            printf("\n");
            if (verificarCPF(paciente.cpf) == true){
                printf("Cpf já cadastrado!\n");
            }
            else{
                cadastro();
                enfileira(paciente.cpf, paciente.idade, 0, f1);
                contadorPessoasFila1++;
                printf("Adicionando na fila de atendimento!\n\n");
            }
            break;
        case 2:
            fflush(stdin);
            printf("Digite o seu CPF (apenas numeros): ");
            gets(paciente.cpf);
            while (validar_CPF(paciente.cpf) == 0){
                printf("CPF INCORRETO!\nDigite um CPF valido: ");
                gets(paciente.cpf);
            }
            fflush(stdin);
            printf("\n");
            if (verificarCPF(paciente.cpf) == true){
                printf("Cpf já cadastrado!\n");
            }
            else
            {
                printf("Cpf não encontrado.\n");
                printf("Vamos realizar o cadastro!\n");
                cadastro();
                enfileira(paciente.cpf, paciente.idade, 0, f1);
                contadorPessoasFila1++;
                printf("Adicionado na fila de atendimento!\n\n");
            }

            break;

        case 3://chamar para atendimento
            if (contadorPessoasFila1 == 0){
                printf("Não tem ninguem na fila\n");
            }
            else{
                fflush(stdin);
                printf("Digite a quatidade de exames: ");
                scanf("%i", &paciente.qntExames);
                printf("\n");
                printf("Digite 0 para convênio e 1 para particular: ");
                scanf("%i", &paciente.conPar);
                fflush(stdin);
                printf("\n");
                printf("Digite a hora do atendimento: ");
                gets(paciente.hora);
                fflush(stdin);
                printf("\n");
                printf("Digite a data de entrega do exame: ");
                gets(paciente.dataEntr);
                fflush(stdin);
                printf("\n");
                enfileira2(f1, 0, paciente.qntExames, paciente.conPar, paciente.dataEntr, paciente.hora, f2);
                desenfileira(f1);
                contadorPessoasFila1--;
                contadorPessoasFila2++;//professor, caso queira avaliar a ordenação, retire o comentário abaixo, porém o código em alguns casos quebra, fora isso, tudo funciona 100%
                /*vetorUm = fila_p_fVetor(f1, atend);
                vetorUm = ordenarVetor(vetorUm);
                vetor_p_fila(f1, vetorUm);*/
                printf("Adicionado na fila de coleta!\n\n");
            }
            break;

        case 4:
            if(contadorPessoasFila2 == 0){
                printf("\nNão tem ninguém na fila de coleta\n\n");
            }
            else{
                contadorPessoasFila2--;//professor, caso queira avaliar a ordenação, retire o comentário abaixo, porém o código em alguns casos quebra, fora isso, tudo funciona 100%
                /*vetorDois = fila_p_fVetor2(f2, atend2);
                vetorDois = ordenarVetor2(vetorDois);
                vetor_p_fila2(f2, vetorDois);*/
                desenfileira2(f2);
                printf("chamado para coleta...\n");
            }
            break;

        case 5:
            
            if (contadorPessoasFila1 == 0)
            {
                printf("Não tem ninguem na fila de atendimento\n");
            }
            else
            {
                imprimeFila(f1);
            }
            break;

        case 6:
            if (contadorPessoasFila2 == 0)
            {
                printf("\nNão tem ninguem na fila de coleta\n\n");
            }
            else
            {
                imprimeFila2(f2);
            }
            break;

        case 7:
            mostrarAtendimentoDia();
            break;

        default:
            printf("Digite uma opção correta:");
            break;
        }
        printar_Menu();
        printf("Digite uma opção: ");
        scanf("%hd", &escolha);
    }

    excluir_arquivo();
    return 0;
}