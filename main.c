#include <stdlib.h>
#include <stdio.h>

#include "primeTest.h"

void testFromFile(const char* path, unsigned long int k, int verbose)
{
    FILE* file = NULL;
    file = fopen(path, "r");

    if(file)
    {
        char buffer[1024];
        unsigned long int inputUI = 0, i = 0;

        mpz_t input;
        mpz_init(input);

        while(fscanf(file, "%s\n", buffer) != EOF)
        {
            mpz_set_str(input, buffer, 10);
            inputUI = mpz_get_ui(input);

            if(inputUI == 2 || inputUI == 1 || soloStra(input, k, verbose) != 0)
            {
                printf("The number %lu is probably prime\n", ++i);
            }
            else
            {
                printf("The number %lu is composed\n", ++i);
            }
        }

        mpz_clear(input);
    }
    else
    {
        printf("Error in loading the file %s", path);
    }

    fclose(file);
}

void testFromConsole(int verbose)
{
    unsigned long int inputUI, k;
    mpz_t input;

    printf("Insert n: ");
    gmp_scanf("%Zd", input);
    printf("\n");

    printf("Insert k: ");
    scanf("%lu", &k);
    printf("\n");

    inputUI = mpz_get_ui(input);

    if(inputUI == 2 || inputUI == 1 || soloStra(input, k, verbose) != 0)
    {
        printf("The number is probably prime\n");
    }
    else
    {
        printf("The number is composed\n");
    }

    mpz_clear(input);
}

int main(int argc, char const *argv[])
{
    unsigned long int k = 0;
    int stop = 0, verbose = 0;

    //TODO: overhaul cleaning of fonctions

    printf("Verbose execution ? (1 = YES, 0 = NO)   CAUTION: it slows the execution\n");
    scanf("%d", &verbose);
    printf("\n");

    if(argc == 1)
    {
        while (!stop)
        {
            testFromConsole(verbose);

            printf("Stop ? (1 -> YES  0 -> NO)\n");
            scanf("%d", &stop);
        }
    }
    else
    {
        printf("Insert the number of tries: ");
        scanf("%lu", &k);
        printf("\n");

        testFromFile(argv[1], k, verbose);
    }

    return 0;
}
