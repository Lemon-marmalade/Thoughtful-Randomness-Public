#include <stdio.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

int main(void)
{
    printf("%lu\n", sizeof());
}
