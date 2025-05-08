#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

long *possiblePrimeFactors(long input); 
long *factorize(long input); 
bool isPrime(long input);
void printList(long* list);
long getFactor(long* primeList, long input);

int main() {

    long input = 0;
    
    bool validInput = false;
    while (!validInput)
    {
        printf("Enter the number you want to factorize: ");
        scanf("%ld", &input);
        if (input <= 0) {
            printf("Please enter a number greater than 0\n\n");
            continue;
        } else if(isPrime(input)) {
            printf("The input you gave is prime and can not be factorized\n\n");
        } else {
            validInput = true;
        }
    }
    printf("The factors are:\n");
    long* pFactors = factorize(input);
    printList(pFactors);
    free(pFactors);

    return 0;
}

long *factorize(long input) {
    long* pPossibleFactors = possiblePrimeFactors(input);
    long* pFactors = calloc(35, sizeof(long));

    int i = 0;
    while (!isPrime(input)) {
        long factor = getFactor(pPossibleFactors, input);
        if (factor == 0) {
            break;
        }else {
            pFactors[i] = factor;
            i++;
            input /= factor;
        }
    }
    pFactors[i] = input;
    free(pPossibleFactors);
    return pFactors;
}

bool isPrime(long n) {
    if (n < 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

long *possiblePrimeFactors(long input) {
    long numberOfPrimes = (long)sqrt(input/(log(input) - 1));
    long *pPrimes = calloc(numberOfPrimes, sizeof(long));

    if (pPrimes == NULL) {
        perror("Could not allocate memory");
        exit(1);
    }

    pPrimes[0] = 2;
    long arrayIndex = 1;

    for (int i = 3; i <= numberOfPrimes; i += 2) {
        if (isPrime(i)) {
            pPrimes[arrayIndex] = i;
            arrayIndex++;
        }
    }
    return pPrimes;
}

long getFactor(long* primeList, long input){
    if (isPrime(input)) {
        return 0;
    }

    int i = 0;
    long curr = primeList[i];
    while (curr != 0) {
        long curr = primeList[i];
        if (curr == 0) {
            break;
        }
        if (input % primeList[i] == 0) {
            return primeList[i];
        }
        i++;
    }
    return 0;
}

void printList(long* list) { 
    int i = 0;
    long curr = list[i];
    while (curr != 0) {
        long curr = list[i];
        if (curr == 0) {
            break;
        }
        printf("%d, ", curr);
        i++;
    }
}