#ifndef PRIMETEST
#define PRIMETEST

#include <gmp.h>

void getTwoFactors(mpz_t a, mpz_t result);
void powOfTwo(mpz_t a, mpz_t times);
unsigned int gcd(mpz_t a, mpz_t b);
void getJacobi(mpz_t res, mpz_t a, mpz_t n);
void squareAndMultiply(mpz_t n, mpz_t modulo, mpz_t ex);
int soloStra(mpz_t n, unsigned int k, char verbose);

#endif