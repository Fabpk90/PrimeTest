#include <stdlib.h>
#include <stdio.h>

#include <gmp.h>

void getTwoFactors(mpz_t a, mpz_t result)
{
    mpz_t tmp;
    mpz_set_ui(result, 0);
    mpz_init_set(tmp, a);

   // printf("%lu\n", mpz_get_ui(tmp));

    while (!(mpz_get_ui(tmp) & 1))
    {
        //printf("%lu", mpz_get_ui(tmp));
        mpz_add_ui(result, result, 1);
        mpz_div_ui(tmp, tmp, 2);
    }

    mpz_clear(tmp);
}

void powOfTwo(mpz_t a, mpz_t times)
{
    unsigned long int j = mpz_get_ui(times) - 1;
    for (unsigned long int i = 0; i < j; i++)
    {
        mpz_mul_ui(a, a, 2);
    }
}

unsigned int gcd(mpz_t a, mpz_t b)
{
    mpz_t tmpA, tmpB, tmp;
    mpz_init(tmp);
    mpz_init(tmpA);
    mpz_init(tmpB);

    mpz_set(tmpA, a);
    mpz_set(tmpB, b);

    while (mpz_get_ui(tmpB) != 0 && mpz_get_ui(tmpB) != 1)
    {
        mpz_set(tmp, tmpB);
        mpz_mod(tmpB, tmpA, tmpB);
        mpz_set(tmpA, tmp);
    }

    mpz_clear(tmpA);
    unsigned int res = mpz_get_ui(tmpB);
    mpz_clear(tmpB);
    mpz_clear(tmp);

    return res;
}

//sets res to jacobi(a/b)
void getJacobi(mpz_t res, mpz_t a, mpz_t n)
{
    char sign = 0;  //0 -> + 1 -> -
    mpz_t pow, two; // not really useful cause when test the parity of the pow
    //to neg or not the val
    mpz_set_ui(res, 0);
    mpz_init(pow);
    mpz_init(two);

    int ok = 1; // to be set when the algo ends

    //gmp_printf("0  %Zd\n", a);
    //gmp_printf("0  %Zd\n", n);

    while (ok)
    {
        mpz_set_ui(pow, 0);
        mpz_set_ui(two, 2);

        //gmp_printf("0.1  %Zd\n", a);
        //gmp_printf("0.1  %Zd\n", n);

        //(1) -> 1
        mpz_mod(a, a, n);

        //gmp_printf("1  %Zd\n", a);
        //gmp_printf("1  %Zd\n", n);

        //(2) -> 3 5
        //degrouping pow of two
        //we need to divide a to 2^pow
        //now see if 2^pow = 1 or -1 (see n mod 8)
        //if -1 see pow to know if even
        getTwoFactors(a, pow);

        //gmp_printf("2  %Zd\n", a);
        //gmp_printf("2  %Zd\n", n);

        if (mpz_get_ui(pow) != 0)
        {
            //n mod 8
            mpz_t modRes;
            mpz_init(modRes);

            powOfTwo(two, pow);

            mpz_div(a, a, two);

            //gmp_printf("3  %Zd\n", a);
            //gmp_printf("3  %Zd\n", n);

            mpz_mod_ui(modRes, n, 8);

            if (mpz_get_ui(modRes) == 3 || mpz_get_ui(modRes) == 5)
            {
                //odd (-1)^pow where pow is odd
                if (!(mpz_get_ui(pow) & 1))
                    sign = (sign == 1) ? 0 : 1;
            }

            //gmp_printf("4  %Zd\n", a);
            //gmp_printf("4  %Zd\n", n);

            mpz_clear(modRes);
        }

        if (mpz_get_ui(a) == 1)
        {
            ok = 0;
            mpz_set_ui(res, 1);
        }
        else
        {
            if (gcd(a, n) != 1)
            {
                ok = 0;
                mpz_set_ui(res, 0);
            }
            else
            {
                mpz_t modA, modN;

                mpz_init(modA);
                mpz_init(modN);

                mpz_mod_ui(modA, a, 4);
                mpz_mod_ui(modN, n, 4);

                if (mpz_get_ui(modA) == 1 || mpz_get_ui(modN) == 1)
                {
                    // -*- == +
                    sign = (sign == 1) ? 0 : 1;
                }

                mpz_swap(a, n);

                mpz_clear(modA);
                mpz_clear(modN);
            }
        }
    }

    if (sign)
        mpz_neg(res, res);

    mpz_clear(pow);
    mpz_clear(two);
}

// sets n to n^ex mod modulo
void squareAndMultiply(mpz_t n, mpz_t modulo, mpz_t ex)
{
    //gets the size in bit of the exposant
    unsigned long exSize = mpz_sizeinbase(ex, 2);
    //allocates a string which will contain the exposant binary representation
    char *str = mpz_get_str(NULL, 2, ex);

    mpz_t nTemp;

    mpz_init_set(nTemp, n);

    for (unsigned long i = 0; i < exSize - 1; i++)
    {
        mpz_mul(nTemp, nTemp, nTemp);
        mpz_mod(nTemp, nTemp, modulo);
        if (str[i] == '1')
        {
            mpz_mul(nTemp, nTemp, n);
            mpz_mod(nTemp, nTemp, modulo);
        }
    }

    gmp_printf("SQ %Zd\n", nTemp);

    mpz_set(n, nTemp);

    mpz_clear(nTemp);

    free(str);
}

//returns 0 if composed 1 otherwise
int soloStra(mpz_t n, unsigned int k)
{
    mpz_t a, r;
    mpz_init(a);
    mpz_init(r);

    //used to generate a randomly
    gmp_randstate_t state;
    gmp_randinit_mt(state);

    mpz_t aPow, tmpN, tmpA;
    
    mpz_init(tmpA);
    mpz_init(aPow);//init the exponent of a

    mpz_init(tmpN);

    for (unsigned int i = 0; i < k; i++)
    {
        printf("YESSS %d", i);
        mpz_urandomm(a, state, n);
        mpz_add_ui(a, a, 2); //because we want {2 .. n-1}

        //resetting back the temporary vals
        mpz_set(tmpA, a);
        mpz_set(tmpN, n);

        gmp_printf("a is %Zd\n", a);
        gmp_printf("N is %Zd\n", tmpN);

        getJacobi(r, tmpA, tmpN);

        gmp_printf("R is %Zd\n", r);

        if (mpz_get_ui(r) == 0)
        {
            printf("NO \n");
            mpz_clear(aPow);
            mpz_clear(tmpN);
            gmp_randclear(state);
            mpz_clear(a);
            mpz_clear(r);
            mpz_clear(tmpA);

            return 0;
        }
        else
        {
            /*if(mpz_get_ui(r) == -1)
            {
                mpz_set(r, )
            }*/

            printf("WUT\n");

            mpz_sub_ui(aPow, n, 1);
            mpz_div_ui(aPow, aPow, 2);

            gmp_printf("pow is %Zd\n", aPow);
            gmp_printf("A is %Zd\n", a);
            

            squareAndMultiply(a, n, aPow);
            if (!mpz_cmp(a, r))
            {
                //clean up
                mpz_clear(aPow);
                mpz_clear(tmpN);
                gmp_randclear(state);
                mpz_clear(a);
                mpz_clear(r);
                mpz_clear(tmpA);

                return 0;
            }
        }
    }

    mpz_clear(aPow);
    mpz_clear(tmpN);
    gmp_randclear(state);
    mpz_clear(a);
    mpz_clear(r);
    mpz_clear(tmpA);

    return 1;
}

int main(int argc, char const *argv[])
{
    mpz_t test;
    mpz_init(test);
    unsigned int k;
    int stop = 0;

    //TODO: add exit if n == 2

    while (!stop)
    {
        printf("Insert n: ");
        gmp_scanf("%Zd", test);
        printf("\n");

        printf("Insert k: ");
        scanf("%u", &k);
        printf("\n");

        if(soloStra(test, k) == 0)
        {
            printf("The number is composed\n");
        }
        else
        {
            printf("The number is probably prime\n");
        }

        printf("Stop ? (1 -> YES  0 -> NO)\n");
        scanf("%d", &stop);
    }

    mpz_clear(test);

    return 0;
}
