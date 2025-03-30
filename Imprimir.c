//////////////////////////////////////////////////
// INÍCIO DA BIBLIOTECA

#include <windows.h>  // Função SetConsoleOutputCP() para configurar o código da página do console (UTF-8)
#include  <stdarg.h>  // Funções para manipulação de argumentos variáveis (vsnprintf, va_list)
#include  <locale.h>  // Função setlocale() para definir as configurações de localidade do programa
#include  <stdlib.h>  // Funções de alocação de memória (malloc, free)
#include   <wchar.h>  // Funções para manipulação de caracteres largos (wprintf, wchar_t)
#include   <stdio.h>  // Funções padrão de entrada e saída (printf, vsnprintf)

/**   Para imprimir simbolos especiais no terminal, vamos usar as funções das bibliotecas acima.
 *    O código abaixo converte strings simples para um formato que essas bibliotecas conseguem ler.
 *    Primeiro ele lê a string de entrada para construir uma string-grande de saída com o tamanho
 * nessessário, depois de mallocar o espaço, ele só converte a string e retorna.
 */
wchar_t* converterParaWide (const char* str)
{
    int tamanho = MultiByteToWideChar (CP_UTF8, 0, str, -1, NULL, 0);
    wchar_t* wstr = malloc (tamanho * sizeof (wchar_t));

    if (wstr != NULL)
    {
        MultiByteToWideChar (CP_UTF8, 0, str, -1, wstr, tamanho);
    }

    return wstr;
}

/**  Recebe argumentos de mesma forma que o print (para commoditie).
 *   Compila todos os argumentos em um único valor "Buffer".
 *   Converte o buffer para string-grande e imprime, antes de limpar (necessário pelo malloc).
 */
void imprimir (const char* formato, ...)
{
    char buffer[4096]; // Buffer temporário para a string formatada (pode ser alterado)
    va_list args;

    va_start (args, formato);
    vsnprintf (buffer, sizeof (buffer), formato, args);
    va_end (args);

    wchar_t* wideStr = converterParaWide (buffer);

    if (wideStr != NULL) 
    {
        wprintf (L"%s", wideStr);
        free (wideStr);
    }
}

/**  --  CONSTRUTOR
 *    Inicia seu código com alguns valores necessários.
 */
void __attribute__((constructor)) construtor()
{
    setlocale(LC_ALL, "");  // Define a localidade para permitir o uso de caracteres especiais
    SetConsoleOutputCP(65001);  // Configura o console para usar UTF-8
}

// FIM DA BIBLIOTECA
//////////////////////////////////////////////////

int main ()
{
    imprimir ("Caracteres especiais:\n");
    imprimir ("á é í ó ú\n");
    imprimir ("Ç ç\n");      
    imprimir ("α β\n");
    imprimir ("Número: %d, String: %s\n", 42, "Exemplo");

    return 0;
}
