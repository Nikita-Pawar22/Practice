#include <stdio.h>

char board[3][3];

void initializeBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
    int count = 1;
    printf("\n\n\t  ");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%d", count++);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
            printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}

void showBoard()
{
    printf("\n\n\t  ");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%c", board[i][j]);
            if (j < 2)
            {
                printf("  |  ");
            }
        }
        if (i < 2)
            printf("\n\t----------------\n\t  ");
    }
    printf("\n\n\n");
}

int updateBoard(int cell, char playerSign)
{
    int row = (cell - 1) / 3;
    int col = (cell - 1) % 3;

    if (board[row][col] != ' ')
    {
        printf("\nInvalid: Cell is already filled!\n");
        return 0;
    }

    board[row][col] = playerSign;
    showBoard();

    return 1;
}

int checkWinner(char sg)
{
    for (int i = 0; i < 3; i++)
    {
        if ((board[i][0] == sg && board[i][1] == sg && board[i][2] == sg) || // Row
            (board[0][i] == sg && board[1][i] == sg && board[2][i] == sg)) // Column
        {
            return 1;
        }
    }
    if ((board[0][0] == sg && board[1][1] == sg && board[2][2] == sg) ||
        (board[0][2] == sg && board[1][1] == sg && board[2][0] == sg))
    {
        return 1;
    }

    return 0;
}

void playTicTacToe()
{
    int gameResult = 0;
    int cell = 0;
    int playCount = 0;
    int updationResult = 1;

    char playerSign = ' ';

    while (!gameResult && playCount < 9)
    {
        if (playCount % 2 == 0)
        {
            printf("\nPlayer 1 [ X ] : ");
            playerSign = 'X';
        }
        else
        {
            printf("\nPlayer 2 [ O ] : ");
            playerSign = 'O';
        }
        scanf("%d", &cell);
        
        if (cell == -1)
        {
            printf("\n\tGame Terminated\n");
            return;
        }

        if (cell > 0 && cell < 10)
        {
            updationResult = updateBoard(cell, playerSign);
            if (updationResult)
            {
                gameResult = checkWinner(playerSign);
                if (gameResult)
                {
                    printf("\t *** Player %d Won!! ***\n", playerSign == 'X' ? 1 : 2);
                }
                playCount++;
            }
        }
        else
        {
            printf("\nPlease Enter a valid cell number (1-9)\n");
        }
    }

    if (!gameResult && playCount == 9)
    {
        printf("\n\t *** Draw...  ***\n");
    }
    printf("\n\t --- Game Over --- \n");
}

int main()
{
    printf("--------- Tic Tac Toe ----------\n\n");

    printf("* Instructions \n\n");
    printf("\tPlayer 1 sign = X\n");
    printf("\tPlayer 2 sign = O");
    printf("\n\tTo exit the game, Enter -1\n");

    printf("\n* Cell Numbers on Board\n");
    initializeBoard();

    char start = ' ';
    printf("\n> Press Enter to start...");
    getchar(); 

    if (start)
    {
        int userChoice = 1;
        while (userChoice)
        {
            playTicTacToe();
            printf("\n* Menu\n");
            printf("\nPress 1 to Restart");
            printf("\nPress 0 to Exit");
            printf("\n\nChoice: ");
            scanf("%d", &userChoice);
            if (userChoice)
            {
                initializeBoard();
            }
            printf("\n");
        }
    }
    printf("\n :: Thanks for playing Tic Tac Toe! :: \n");
    return 0;
}
