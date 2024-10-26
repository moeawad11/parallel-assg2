#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void sieve(int n, char *primes) {
    for (int i=0;i<=n;i++) {
        primes[i]=1;
    }
    primes[0] = 0;
    primes[1] = 0;

    int sqrt_n = (int)sqrt(n);
    for (int i=2;i<=(int)sqrt(n);i++) {
        if(primes[i]){
            for (int j=i*i;j<=n;j+=i){
                primes[j]=0;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d",&n);

    char *primes = (char *)malloc((n+1)*sizeof(char));

    clock_t start_time=clock();
    sieve(n, primes);
    clock_t end_time=clock();

    double execution_time=(double)(end_time-start_time)/CLOCKS_PER_SEC;

    printf("Execution Time: %f seconds\n", execution_time);

    free(primes);
    return 0;
}
//gcc -o seqSieve seqSieve.c -lm
