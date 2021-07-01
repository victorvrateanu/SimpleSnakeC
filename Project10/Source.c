#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

typedef struct sc 
{
    char nume[20];
    int score;
}sc;


int i, j, height = 20, width = 20;
int gameover, score, highscore;
int x, y, fruitx, fruity, flag;
char snake = '^';
char body = '*';
int len = 0;
char buf[20];

// Function to generate the fruit
// within the boundary
void setup()
{
    gameover = 0;

    // Stores height and width
    x = height / 2;
    y = width / 2;
label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
        goto label1;
label2:
    fruity = rand() % 20;
    if (fruity == 0)
        goto label2;
    score = 0;
}

// Function to draw the boundaries
void draw()
{
    int k;
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1) 
            {
                printf("#");
            }
            else {
                if (i == x && j == y) {
                    printf("%c", snake);
                }
                    
                else if (i == fruitx
                    && j == fruity)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

    // Print the score after the
    // game ends
    printf("score = %d", score);
    printf("\n");
    printf("press X to quit the game");
}

// Function to take the input
void input()
{
    if (kbhit()) {
        switch (getch()) {
        case 'a':
            flag = 1;
            snake = '<';
            break;
        case 's':
            flag = 2;
            snake = '%';
            break;
        case 'd':
            flag = 3;
            snake = '>';
            break;
        case 'w':
            flag = 4;
            snake = '^';
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

// Function for the logic behind
// each movement
void logic()
{
   Sleep(0.01);
    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    // If the game is over
    if (x < 0 || x > height
        || y < 0 || y > width)
        gameover = 1;

    // If snake reaches the fruit
    // then update the score
    if (x == fruitx && y == fruity) {
    label3:
        fruitx = rand() % 20;
        if (fruitx == 0)
            goto label3;

        // After eating the above fruit
        // generate new fruit
    label4:
        fruity = rand() % 20;
        if (fruity == 0)
            goto label4;
        score += 10;
        
    }
}

void scoreboard(int n, sc tab[20], FILE* scorebd)
{
    int puncte = 0;
    while (!feof(scorebd))
    {

        fscanf(scorebd, "%s %d", buf, &puncte);
        strcpy(tab[n].nume, buf);
        tab[n].score = puncte;

        n++;

    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            sc aux;
            if (tab[i].score < tab[j].score)
            {
                aux = tab[i];
                tab[i] = tab[j];
                tab[j] = aux;
            }
        }
    }
    highscore = tab[0].score;
    if (score > highscore) {
        printf("------------NEW HIGHSCORE, CONGRATS !!!!!-----------");
    }
    printf("------------------SCORE---------------------\n");
    for (i = 0; i < n; i++)
    {
        if (i == 0) {
            printf("#1  - %s %d", tab[i].nume, tab[i].score);
            printf("\n");
           
        }
        else if (i == 1) {
            printf("#2  - %s %d", tab[i].nume, tab[i].score);
            printf("\n");
        }
        else if (i == 2) {
            printf("#3  - %s %d", tab[i].nume, tab[i].score);
            printf("\n");
        }
        else {
            printf("%s %d", tab[i].nume, tab[i].score);
            printf("\n");
        }

    }
    if (score > highscore) {
        printf("------------NEW HIGHSCORE, CONGRATS !!!!!-----------");
    }
}

// Driver Code
void main()
{
    int n=0;
    sc tab[20];
    char buf[20];
    char* nume;
    char restart;
    FILE* scorebd;
    scorebd = fopen("f1.txt", "r+");
    if (scorebd == NULL) { printf("Scoreboard file not found"); }
pas0:

    setup();

    // Until the game is over
    while (!gameover) {

        // Function Call
        draw();
        input();
        logic();
    }
  

    printf("\nName: ");
    scanf("%s", buf);
    nume = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
    if (nume == NULL) { printf("Dynamic allocation error"); }
    strcpy(nume, buf);
    fseek(scorebd, 0, SEEK_END);
    fprintf(scorebd, "\n%s %d", nume, score);
    fseek(scorebd, 0, SEEK_SET);
    scoreboard(n, tab, scorebd);
    printf("\nPress Y for restart N for exit: ");
    scanf(" %c", &restart);

    if (toupper(restart) == 'Y')
    {
        goto pas0;
    }
   
    free(nume);
    fclose(scorebd);
}