#include <stdlib.h>
#include <stdio.h>

//teste

typedef struct {
    char nome[128];
    char telefone[32];
} tcontato;

// PROTÓTIPOS CORRIGIDOS
int leitura(tcontato agenda[]); 
void contatos(tcontato agenda[], int *total); // Adicionado []
void exibir(tcontato agenda[], int total);
void salvar(tcontato agenda[], int total);

int main() {
    tcontato agenda[100];
    int opcao, a;
    // CORREÇÃO: Passando apenas agenda, o retorno vai para a variável total
    int total = leitura(agenda); 
    
    do {
        printf("\nMenu:\n 1-novo contato\n 2-exibir contato\n 3-salvar contatos\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                contatos(agenda, &total);
                break;
            case 2:
                exibir(agenda, total);
                break;
            case 3:
                salvar(agenda, total);
                break;
        }
        printf("Deseja repetir o processo? (1-sim / 2-nao)\n");
        scanf("%d", &a);
    } while(a != 2);

    return 0;
}

int leitura(tcontato agenda[]) {
    FILE *arquivo = fopen("agenda.csv", "r"); // "r" para ler
    if(arquivo == NULL) return 0;

    int i = 0;
    // Lógica correta de leitura CSV com != EOF
    while(i < 100 && fscanf(arquivo, " %[^;];%[^\n]\n", agenda[i].nome, agenda[i].telefone) != EOF) {
        i = i + 1;
    }
    fclose(arquivo);
    return i;
}

void contatos(tcontato agenda[], int *total) {
    if(*total >= 100) {
        printf("Agenda cheia!\n");
        return;
    }
    
    printf("Digite o nome: ");
    scanf(" %[^\n]", agenda[*total].nome); // %[^\n] para ler nomes com espaços
    printf("Digite o telefone: ");
    scanf(" %[^\n]", agenda[*total].telefone);
    
    *total = *total + 1;
    printf("Contato salvo na RAM\n");
}

void exibir(tcontato agenda[], int total) {
    for(int i = 0; i < total; i++) {
        printf("%d. %s | %s\n", i + 1, agenda[i].nome, agenda[i].telefone);
    }
}

void salvar(tcontato agenda[], int total) {
    FILE *arq_salvar = fopen("arquivo.csv", "w"); // "w" para escrever
    if(arq_salvar == NULL) {
        printf("Erro ao criar arquivo\n");
        return;
    }
    for(int i = 0; i < total; i++) {
        fprintf(arq_salvar, "%s;%s\n", agenda[i].nome, agenda[i].telefone);
    }
    fclose(arq_salvar);
    printf("Arquivo salvo com sucesso!\n");
}
