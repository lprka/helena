#include <stdio.h>
#include <stdlib.h>

const char *invalidOption = "Neispravan odabir '%d'.\n";
const int errorResult = -1;
const int successResult = 0;

int readLine(char *buffer)
{
    buffer[0] = '\0';                                 //postavi buffer na string duljine nula
    char *eof = fgets(buffer, sizeof(buffer), stdin); //procitaj liniju s konzole
    if (eof == NULL)
    {
        printf(invalidOption, eof);
        return errorResult;
    }
    else
    {
        return successResult;
    }
}

int readInt(const char *message, int min, int max, int *result) //ovdje predajemo adresu na rezultat jer cemo ga promijeniti unutar funkcije
{
    printf(message);

    char buffer[256]; //ovo je char array statički alociran tako da ne treba malloc ni free
    if (readLine(buffer) < 0)
    {
        return errorResult;
    }

    *result = atoi(buffer);             //ovdje dereferenciramo pointer jer mijenjamo vrijednost varijable, a ne adresu
    if (*result < min || *result > max) //ovdje dereferenciramo pointer jer čitamo vrijednost varijable, a ne adresu
    {
        printf(invalidOption, *result);
        return errorResult;
    }
    else
    {
        return successResult;
    }
}

int doTask1()
{
    int m, n, k;
    if (readInt("Unesite broj redaka m (2-10): ", 2, 10, &m) < 0)
    {
        return errorResult;
    }
    if (readInt("Unesite broj stupaca n (2-10): ", 2, 10, &n) < 0)
    {
        return errorResult;
    }

    int **matrix = (int **)malloc(m * sizeof(int *)); //alociraj dvodimanzionalni array za matricu
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int)); //alociraj array za svaki redak
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int element;
            char buffer[256];
            sprintf(buffer, "Unesite element matrice [%d,%d]: ", i, j);
            if (readInt(buffer, INT_MIN, INT_MAX, &element) < 0)
            {
                return errorResult;
            }
            else
            {                
                matrix[i][j] = element;
            }
        }
    }

    if (readInt("Unesite cijeli broj k: ", INT_MIN, INT_MAX, &k) < 0)
    {
        return errorResult;
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] *= k;
        }        
    }
    

    printf("Rezultat:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return successResult;
}

int main()
{
    printf("1. Napravite funkciju koja ce omoguciti mnozenje matrice cijelih brojeva i cijelog broja k te vratiti pokazivac na matricu umnoska. "
           "U glavnom dijelu programa treba unijeti matricu reda nxm (2<=n<=10,2<=m<=10) i jedan cijeli broj k. Ispisati dobivenu matricu po redcima u formatu \"%%d\"\n");

    int option;
    if (readInt("Unesite broj zadatka (1-4): ", 1, 4, &option) < 0)
    {
        return errorResult;
    }

    switch (option)
    {
    case 1:
        return doTask1();
        break;
    }
}
