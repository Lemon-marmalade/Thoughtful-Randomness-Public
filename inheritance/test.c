#include <stdio.h>

typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

int main(void)
{
    person test;
    printf("%lu\n", sizeof(test.parents)/sizeof(test.parents[0]));
}
