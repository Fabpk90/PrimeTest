#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

unsigned int gcd(mpz_t a, mpz_t b)
{
    mpz_t tmp;
    mpz_init(tmp);

    printf("%lu\n", mpz_get_ui(a));
    printf("%lu\n", mpz_get_ui(b));

    while(mpz_get_ui(b) != 0 && mpz_get_ui(b) != 1)
    {
        mpz_set(tmp, b);
        mpz_mod(b, a, b);
        mpz_set(a, tmp);
    }

    mpz_clear(tmp);

    printf("b %lu\n", mpz_get_ui(b));

    return mpz_get_ui(b);
}


//sets res to jacobi(a/b)
void getJacobi(mpz_t res, mpz_t a, mpz_t b)
{
    mpz_t tmp;

    //if greater or equal
    if(mpz_cmp(a, b) >= 0)
    {
        mpz_mod(a, a, b);
    }
    else
    {
        
    }
    

    mpz_clear(tmp);
}

// sets n to n^ex    TODO: mod
void squareAndMultiply(mpz_t n, mpz_t modulo, mpz_t ex)
{
    //gets the size in bit of the exposant
    unsigned long exSize = mpz_sizeinbase(ex, 2);
    //allocates a string which will contain the exposant binary representation
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

    mpz_t a, b;

    mpz_init_set_ui(a, 17);
    mpz_init_set_ui(b, 7);

    gcd(a, b);

//    gmp_scanf("%Zd", test);

   /* if(mpz_get_ui(test) & 1)
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
    }*/

    mpz_clear(test);
    return 0;
}
