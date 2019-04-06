#include <stdlib.h>

#include <gmp.h>

// set n to n^ex    TODO: mod
void squareAndMultiply(mpz_t n, mpz_t modulo, mpz_t ex)
{
    //gets the size in bit of the exposant
    unsigned long exSize = mpz_sizeinbase(ex, 2);
    //allocate a string which will contain the exposant binary representation
    char* str = mpz_get_str(NULL, 2, ex);

    mpz_t nTemp;

    mpz_init_set(nTemp, n);

    printf("%s\n", str);

    for(unsigned long i = 0; i < exSize - 1; i++)
    {
        mpz_mul(nTemp, nTemp, nTemp);
        //mpz_mod(nTemp, nTemp, modulo);
        if(str[i] == '1')
        {
            mpz_mul(nTemp, nTemp, n);
            //mpz_mod(nTemp, nTemp, modulo);
        }
    }

    gmp_printf("%Zd", nTemp);

    mpz_clear(nTemp);

    free(str);   
}

int main()
{
    mpz_t test;

    mpz_init(test);

    printf("Enter N: ");
    gmp_scanf("%Zd", test);

    if(mpz_get_ui(test) & 1)
    {
        mpz_t n, ex;

        mpz_init(n);
        mpz_init(ex);

        mpz_set_ui(n, 2);
        mpz_set_ui(ex, 5);

        squareAndMultiply(n, NULL, ex);

        mpz_clear(n);
        mpz_clear(ex);
    }
    else
    {
        printf("even number typed, try again\n");
    }

    mpz_clear(test);
    return 0;
}
