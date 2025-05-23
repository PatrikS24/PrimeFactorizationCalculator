#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

unsigned long long *possiblePrimeFactors(unsigned long long input); 
unsigned long long *factorize(unsigned long long input); 
bool isPrime(unsigned long long input);
void printList(unsigned long long* list);
unsigned long long getFactor(unsigned long long* primeList, unsigned long long input);

int main() {

    unsigned long long input = 0;
    bool validInput = false;
    while (!validInput)
    {
        printf("Enter a positive integer between 1 and 140737488355328 that you want to factorize: ");
        scanf("%llu", &input);
        if(isPrime(input)) {
            printf("The input you gave is prime and can not be factorized\n\n");
        } else if (input > 140737488355328) {
            printf("Please enter a number smaller than 140737488355328\n\n");
        } else {
            validInput = true;
        }
        while ((getchar()) != '\n'); // Clears the scanf buffer to avoid infinite loop
    }
    printf("The prime factors are:\n");
    unsigned long long* pFactors = factorize(input);
    printList(pFactors);
    free(pFactors);
    pFactors = NULL;

    return 0;
}


// Function that takes an input and returns a pointer to an array with the primes that make up the composite number
unsigned long long *factorize(unsigned long long input) {
    unsigned long long* pPossibleFactors = possiblePrimeFactors(input);
    //printList(pPossibleFactors);
    unsigned long long* pFactors = calloc(48, sizeof(unsigned long long));
    if (pFactors == NULL) {
        printf("Failed to allocate memory");
        exit(1);
    }

    long i = 0;
    while (true) {
        unsigned long long factor = getFactor(pPossibleFactors, input);
        if (factor == 0) {
            pFactors[i] = input; // Get the final factor
            break;
        }else {
            // Add the factor to the array of known factors and divide the current number by the factor for the next iteration
            pFactors[i] = factor;
            i++;
            input /= factor;
        }
    }    
    // Reallocate memory for the correct numbers of factors
    unsigned long long* temp = realloc(pFactors, (i + 1) * sizeof(unsigned long long));
    if (temp == NULL) {
        printf("Failed to reallocate memory.");
    } else {
        pFactors = temp;
        temp = NULL;
    }
    free(pPossibleFactors);
    return pFactors;
}

bool isPrime(unsigned long long n) {
    if (n < 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


// Returns a pointer to an array of all possible prime factors that the input number can have
unsigned long long *possiblePrimeFactors(unsigned long long input) {
    unsigned long long numberOfPrimes = (unsigned long long)sqrt(input/(log(input) - 1));
    unsigned long long *pPrimes = malloc((numberOfPrimes + 2) * sizeof(unsigned long long));

    if (pPrimes == NULL) {
        perror("Could not allocate memory");
        exit(1);
    }

    pPrimes[0] = 2;
    long arrayIndex = 1;
    for (long i = 3; arrayIndex <= numberOfPrimes; i += 2) {
        if (isPrime(i)) {
            pPrimes[arrayIndex] = i;
            arrayIndex++;
        }
    }
    pPrimes[arrayIndex] = 0;
    return pPrimes;
}

// Returns 0 if input is a prime number otherwise it returns a factor of the input number
unsigned long long getFactor(unsigned long long* primeList, unsigned long long input){
    if (isPrime(input)) return 0;
    if (input == 0) return 0;
    // Loops through the list of prime numbers to check what prime number the input can be evenly divided by
    long i = 0;
    while (primeList[i] != 0) {
        if (input % primeList[i] == 0) {
            return primeList[i];
        }
        i++;
    }
    return 0;
}

void printList(unsigned long long* list) { 
    long i = 0;
    while (list[i] != 0) {
        printf("%llu, ", list[i]);
        i++;
    }
}