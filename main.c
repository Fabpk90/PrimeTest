#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

void getTwoFactors(mpz_t a, mpz_t result)
{
    mpz_t tmp;
    mpz_init_set_ui(result, 0);
    mpz_init(tmp);

    mpz_set(tmp, a);

    while(!(mpz_get_ui(tmp) & 1))
    {
        //printf("%Lu", mpz_get_ui(tmp));
        mpz_add_ui(result, result, 1);
        mpz_div_ui(tmp, tmp, 2);
    }

    mpz_clear(tmp);
}


void powOfTwo(mpz_t a, mpz_t times)
{
    unsigned long int j = mpz_get_ui(times) - 1;
    for(unsigned long int i = 0; i < j; i++)
    {
        mpz_mul_ui(a, a, 2);
    }
    
}

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
void getJacobi(mpz_t res, mpz_t a, mpz_t n)
{
    mpz_t pow, tmp;// not really useful cause when test the parity of the pow
    //to neg or not the val
    mpz_set_ui(res, 0);

    int ok = 1; // to be set when the algo ends

    while(ok)
    {
        mpz_set_ui(pow, 0);
        mpz_set_ui(tmp, 0);
        //(1) -> 1
        mpz_mod(a, a, n);

        //(2) -> 3 5
        getTwoFactors(a, pow);

        if(mpz_get_ui(pow) != 0)
        {
            //degrouping pow of two
            //we need to divide a to 2^pow
            //now see if 2^pow = 1 or -1 (see n mod 8)
            //if -1 see pow to know if even
        }
    }
    
    mpz_clear(pow);
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

    mpz_t a, b, twoP;

    mpz_init_set_ui(a, 541);
    mpz_init_set_ui(b, 7);
    


    mpz_clear(test);
    mpz_clear(a);
    mpz_clear(b);
    return 0;
}
