// PROJETO 1 - Tradutor de Código Morse
// Integrantes: Gyovanni V B De Brito - 10738595
// Turma: 02N 11

#include <stdio.h>

// Tabelas de referência (Vetores Globais)
char alfabeto[26] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

char morse[26][6] = {
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
    "..-","...-",".--","-..-","-.--","--.."
};

// --- FUNÇÃO DE BUSCA (Usa ponteiros e o índice j) ---
void buscarEImprimir(char *sequencia, int tam) {
    // Caso 1: Código Corrompido (Termina em '*')
    if (*(sequencia + tam - 1) == '*') {
        printf("[");
        for (int i = 0; i < 26; i++) {
            int igual = 1;
            // Percorre os sinais antes do '*'
            for (int j = 0; j < tam - 1; j++) {
                if (*(sequencia + j) != morse[i][j]) {
                    igual = 0;
                }
            }
            if (igual == 1) printf("%c", alfabeto[i]);
        }
        printf("]");
    } 
    // Caso 2: Tradução Normal
    else {
        for (int i = 0; i < 26; i++) {
            int igual = 1;
            int j = 0;
            // Compara sinal por sinal até o fim da string (\0)
            while (*(sequencia + j) != '\0' || morse[i][j] != '\0') {
                if (*(sequencia + j) != morse[i][j]) {
                    igual = 0;
                }
                j++;
            }
            if (igual == 1) printf("%c", alfabeto[i]);
        }
    }
}

// --- FUNÇÃO RECURSIVA (Lê o arquivo e controla o fluxo) ---
void traduzirRecursivo(FILE *arq, char *sequencia, int pos, int espacos) {
    char sinal = fgetc(arq);

    // Caso Base: Fim do arquivo
    if (sinal == EOF) {
        if (pos > 0) {
            *(sequencia + pos) = '\0';
            buscarEImprimir(sequencia, pos);
        }
        return;
    }

    // Se ler um sinal válido (. - *)
    if (sinal == '.' || sinal == '-' || sinal == '*') {
        *(sequencia + pos) = sinal; 
        traduzirRecursivo(arq, sequencia, pos + 1, 0); // Zera o contador de espaços
    } 
    // Se ler um espaço ou quebra de linha
    else if (sinal == ' ' || sinal == '\n') {
        if (pos > 0) {
            // Acabou uma letra: finaliza a string e traduz
            *(sequencia + pos) = '\0';
            buscarEImprimir(sequencia, pos);
            // Continua para o próximo caractere, agora com pos = 0
            traduzirRecursivo(arq, sequencia, 0, 1);
        } else {
            // Lógica de espaço entre palavras:
            // Se ler o 3º espaço seguido (sem ter lido sinais no meio), imprime espaço
            if (espacos == 3) {
                printf(" ");
            }
            traduzirRecursivo(arq, sequencia, 0, espacos + 1);
        }
    }
}

// --- FUNÇÃO PRINCIPAL ---
int main() {
    // Tenta abrir o arquivo para leitura
    FILE *arq = fopen("entrada.txt", "r");
    char sequencia[10]; // Buffer temporário para os sinais

    if (arq == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo 'entrada.txt'.\n");
    } else {
        // Inicia a recursão passando o endereço da sequencia
        traduzirRecursivo(arq, sequencia, 0, 0);
        fclose(arq);
        printf("\n"); // Pula linha ao final de tudo
    }

    return 0;
}