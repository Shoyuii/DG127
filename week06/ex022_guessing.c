#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int random_number = rand() % 100 + 1;

    int guess;
    int attempts = 0;

    printf("=== Number Guessing Game (1-100) ===\n");
    do
    {
        printf("Enter your guess (1-100): ");
        scanf("%d", &guess);
        attempts++;

        if (guess < random_number)
        {
            printf("Too low! Try again.\n");
        }
        else if (guess > random_number)
        {
            printf("Too high! Try again.\n");
        }
        else
        {
            printf("Congratulations! You guessed the number %d in %d attempts.\n", random_number, attempts);
        }
    } while (guess != random_number && attempts != 10);

    if (attempts == 10)
    {
        printf("Sorry, you've used all your attempts. The number was %d.\n", random_number);
    }

    return 0;
}