// PROJETO 1 - Tradutor de Código Morse
// Integrantes: Gyovanni V B De Brito - 10738595
// Turma: 02N 11

#include <stdio.h>

// Lista Alfabeto
char alfabeto[26] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

// Lista código
// matriz 26 elementos - 6 representa os espaços
char morse[26][6] = {
    ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
    "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
    "..-","...-",".--","-..-","-.--","--.."
};

// Função para buscar
void buscarEImprimir(char *sequencia, int tam) {            // ponteiro para o primeiro caractere + tamanho do cod
    // Se o código estiver corrompido
    if (*(sequencia + tam - 1) == '*') {                    // verifica se existe o *, se existir o programa entra no loop guardando todas as possíveis letras
        printf("[");
        for (int i = 0; i < 26; i++) {
            int igual = 1;
            // Percorre os sinais antes do '*'
            for (int j = 0; j < tam - 1; j++) {                          // vetor percorre até a posição anterior ao asterisco
                if (*(sequencia + j) != morse[i][j]) {                   // Se a sequencia da letra for diferente da guardada, esta descartada
                    igual = 0;
                }
            }
            if (igual == 1) printf("%c", alfabeto[i]);                  // imprime as possíveis letras
        }
        printf("]");
    } 
    // Tradução Normal
    else {
        for (int i = 0; i < 26; i++) {                    // Se nao tiver *, percorre o a lista alfabeto
            int igual = 1;
            int j = 0;
            
            while (*(sequencia + j) != '\0' && morse[i][j] != '\0') {              // compara sinal por sinal até encontrar a letra correspondente
                if (*(sequencia + j) != morse[i][j]) {                             // Se o sinal for diferente, a letra é descartada e vai pra próxima
                    igual = 0;
                }
                j++;
            }
            if (igual == 1) printf("%c", alfabeto[i]);                            // imprime a letra que teve sinal igual
        }
    }
}

// Função Recursiva
// Função para ler a entrada do código morse
void traduzirRecursivo(FILE *arq, char *sequencia, int pos, int espacos) {
    char sinal = fgetc(arq);                  // fgetc() - usada para pular o caractere

    // Caso Base
    if (sinal == EOF) {               // Se encontrar EOF, o arquivo acabou
        if (pos > 0) {                // Verifica se ainda há algum sinal
            *(sequencia + pos) = '\0';
            buscarEImprimir(sequencia, pos);
        }
        return;             // encerra
    }

    // Se ler um sinal válido (. - *)
    if (sinal == '.' || sinal == '-' || sinal == '*') {           // confirma se o sinal é válido, se sim aumenta a posição
        *(sequencia + pos) = sinal; 
        traduzirRecursivo(arq, sequencia, pos + 1, 0);            // zera o contador de espaços
    } 

    // Se ler um espaço ou quebra de linha
    else if (sinal == ' ' || sinal == '\n') {                    // se for espaço ou quebra de linhas a sequência dos sinais parou
        if (pos > 0) {                                  // se posição for maior que zero, leu uma letra inteira

            // Acabou uma letra -  finaliza a string e traduz
            *(sequencia + pos) = '\0';
            buscarEImprimir(sequencia, pos);

            // Continua para o próximo caractere
            // zera o pos
            traduzirRecursivo(arq, sequencia, 0, 1);
        } else {
            // Lógica de espaço entre palavras
            // Se ler o 3º espaço seguido, imprime espaço
            if (espacos == 3) {
                printf(" ");
            }
            traduzirRecursivo(arq, sequencia, 0, espacos + 1);
        }
    }
}

// Função Principal
int main() {
    // Abre o arquivo para leitura
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
