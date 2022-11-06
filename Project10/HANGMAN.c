#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
int lifes, i, j, m, z, flag=0;
char start;
int gameover=0, difficulty, restart, win;

void input() {
pas1:
	if (kbhit()) {
		switch (getch())
		{
		case 'x':
			break;
		case 'X':
			break;
		default:
			goto pas1;
		}

	}
	else {
		goto pas1;
	}

}
void game(FILE* words) 
{
	
	int n, WLen;
	char word[30], word2[30], *showword;
	char input;
	
	start:
	n = rand() % 15;
	if (n == 0) { goto start; };


	for (int i = 0; i < n; i++)
	{
		fscanf(words, "%s", word);
	}


	WLen = strlen(word);

	printf("THE WORD IS :                                       ");
	for (i = 0; i < WLen; i++)
	{
		printf("_ ");
	}
	
	
	while (lifes > 0) 
	{
		win = 0;
		int k = 0;
		printf("\nTRY TO GUESS ! LIFES: %d\nCH:", lifes);
		scanf(" %c", &input);
		
		for (i = 0; i < WLen; i++)
		{		
			if (word[i] == input) 
			{
				printf("%c", input);
				k++;
				word2[i] = word[i];
			}
			else
			{
				printf("_ ");
			}
			
		}
		if (k == 0)
		{
			lifes--;
			printf("Wrong, TRY AGAIN !");
		}
		printf("\nTHE WORD SO FAR:                                    ");
		for (m = 0; m < WLen; m++)
		{
			if (word2[m] < 97 || word2[m] > 122) 
			{
				printf("_ ");
			}
			else
			{
				printf("%c ", word2[m]);
			}
		}

		flag = 0;

		for (z = 0; z < WLen; z++)
		{
			
			if (word[z] == word2[z])
			{
				flag++;
			}
		}
		
		if (flag == WLen) {
			printf("\nCONGRATS! YOU WON ! ");
			win = 1;
			lifes = 0;
			break;
		}
		
	}
	




	if (lifes == 0)
	{
		if (win == 1) 
		{
			printf(" \nPress Y to try again or N to quit ");
		}
		else 
		{
			
			printf("\nGame Over ! The word was: %s \nPress Y to try again or N to quit ", word);
		}
		scanf(" %c", &input);
		switch (toupper(input)) {
		case 'Y':
			restart = 1;
			break;
		case 'N':
			restart = 0;
			break;
		}
		printf("\n\n\n\n\n");
	}

	
}
void diff() {
	
	printf("---CHOOSE GAME DIFICULTY\N ---\n1. EASY \n2. MEDIUM\n3. HARD\n4. LIFE SIM\n");
	printf("OPTION: ");
	scanf("%d", &difficulty);
	switch (difficulty) {
	case 1:
		lifes = 8;
		break;
	case 2:
		lifes = 5;
		break;
	case 3:
		lifes = 3;
		break;
	case 4:
		lifes = 1;
		break;
	}

}
// Driver Code
void main()
{
	FILE* words;
	words = fopen("words.txt", "r"); if (words == NULL) { printf("Dynamic allocation error"); }
	start:
	printf("<---------HANGMAN---------->\n");
	printf("    PRESS X TO START     \n");
	input();
	diff();
	game(words);
	if (restart == 1) { goto start; };
	fclose(words);

	return 1;
}