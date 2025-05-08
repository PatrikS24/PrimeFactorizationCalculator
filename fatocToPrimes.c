#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

unsigned long *possiblePrimeFactors(unsigned long input); 
unsigned long *factorize(unsigned long input); 
bool isPrime(unsigned long input);
void printList(unsigned long* list);
unsigned long getFactor(unsigned long* primeList, unsigned long input);

int main() {

    unsigned long input = 0;
    bool validInput = false;
    while (!validInput)
    {
        printf("Enter a positive integer between 1 and %lu that you want to factorize: ", ULONG_MAX);
        scanf("%lu", &input);
        if(isPrime(input)) {
            printf("The input you gave is prime and can not be factorized\n\n");
        } else {
            validInput = true;
        }
    }
    printf("The factors are:\n");
    unsigned long* pFactors = factorize(input);
    printList(pFactors);
    free(pFactors);
    pFactors = NULL;

    return 0;
}


// Function that takes an input and returns a pointer to an array with the primes that make up the composite number
unsigned long *factorize(unsigned long input) {
    unsigned long* pPossibleFactors = possiblePrimeFactors(input);
    unsigned long* pFactors = calloc(35, sizeof(unsigned long));

    int i = 0;
    while (!isPrime(input)) {
        unsigned long factor = getFactor(pPossibleFactors, input);
        if (factor == 0) {
            break;
        }else {
            // Add the factor to the array of known factors and divide the current number by the factor for the next iteration
            pFactors[i] = factor;
            i++;
            input /= factor;
        }
    }
    pFactors[i] = input; // Get the final factor
    unsigned long* temp = realloc(pFactors, (i + 1) * sizeof(unsigned long*));
    pFactors = temp;
    temp = NULL;
    free(pPossibleFactors);
    return pFactors;
}

bool isPrime(unsigned long n) {
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


// Returns a pointer to an array of all possible prime factors that the input number can have
unsigned long *possiblePrimeFactors(unsigned long input) {
    unsigned long numberOfPrimes = (unsigned long)sqrt(input/(log(input) - 1));
    unsigned long *pPrimes = calloc(numberOfPrimes + 1, sizeof(unsigned long));

    if (pPrimes == NULL) {
        perror("Could not allocate memory");
        exit(1);
    }

    pPrimes[0] = 2;
    int arrayIndex = 1;

    for (int i = 3; arrayIndex <= numberOfPrimes; i += 2) {
        if (isPrime(i)) {
            pPrimes[arrayIndex] = i;
            arrayIndex++;
        }
    }
    return pPrimes;
}

// Returns 0 if input is a prime number otherwise it returns a factor of the input number
unsigned long getFactor(unsigned long* primeList, unsigned long input){
    if (isPrime(input)) {
        return 0;
    }
    int i = 0;
    // Loops through the list of prime numbers to check what prime number the input can be evenly divided by
    while (primeList[i] != 0) {
        if (primeList[i] == 5 && input == 5555555555) printf("it is five    ");
        if (input % primeList[i] == 0) {
            return primeList[i];
        }
        i++;
    }
    return 0;
}

void printList(unsigned long* list) { 
    int i = 0;
    while (list[i] != 0) {
        if (list[i] == 0) {
            break;
        }
        printf("%lu, ", list[i]);
        i++;
    }
}