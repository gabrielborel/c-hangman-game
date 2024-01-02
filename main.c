#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int checked = 0, guesses_amount = 0;
char guesses[26], secret_word[20];

void main()
{
	generate_secret_word();
	print_header();

	while (!check_win() && !check_hanged())
	{
		print_secret_word();
		capture_guess();
		printf("\n\n");
	}
}

void print_header()
{
	printf("*******************************\n");
	printf("* Welcome to the Hangman Game *\n");
	printf("*******************************\n\n");

	printf("What is the secret word?\n");
}

void capture_guess()
{
	char guess;
	scanf(" %c", &guess);

	guesses[guesses_amount] = guess;
	guesses_amount++;
}

void print_secret_word()
{
	for (int i = 0; i < strlen(secret_word); i++)
	{
		int found = check_guess(secret_word[i]);

		if (found)
		{
			printf("%c ", secret_word[i]);
		}
		else
		{
			printf("_ ");
		}
	}
}

void generate_secret_word()
{
	FILE *f;
	f = fopen("words.txt", "r");

	if (f == 0)
	{
		printf("database connection failed \n\n");
		exit(1);
	}

	int words_quantity;
	fscanf(f, "%d", &words_quantity);

	srand(time(0));

	int random_number = rand() & words_quantity;

	for (int i = 0; i <= random_number; i++)
	{
		fscanf(f, "%s", secret_word);
	}

	fclose(f);
}

int check_guess(char letter)
{
	int found = 0;
	for (int j = 0; j < guesses_amount; j++)
	{
		if (guesses[j] == letter)
		{
			found = 1;
			break;
		}
	}
	return found;
}

int check_hanged()
{
	int errors = 0;

	for (int i = 0; i < guesses_amount; i++)
	{
		int exists = 0;

		for (int j = 0; j < strlen(secret_word); j++)
		{
			if (guesses[i] == secret_word[j])
			{
				exists = 1;
				break;
			}
		}

		if (!exists)
		{
			errors++;
		}
	}

	if (errors >= 5)
	{
		printf("You lost the game =(\n");
		return 1;
	}

	return 0;
}

int check_win()
{
	for (int i = 0; i < strlen(secret_word); i++)
	{
		if (!check_guess(secret_word[i]))
		{
			return 0;
		}
	}

	printf("You won the game!\n");
	return 1;
}
