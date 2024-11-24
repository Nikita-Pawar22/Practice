#include <stdio.h>

char board[3][3];

void initializeBoard() {
   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
   
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

int checkWinner() {

    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0] == 'X' ? 1 : -1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i] == 'X' ? 1 : -1;
    }
   
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0] == 'X' ? 1 : -1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2] == 'X' ? 1 : -1;
    return 0;
}

int isMovesLeft() {
   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 1;
        }
    }
    return 0;
}

void playGame() {
    
    int row, col, turn = 1; // 1 for player X, -1 for player O
    initializeBoard();

    while (1) {
        printBoard();
        printf("Player %c, enter your move (row and column): ", (turn == 1) ? 'X' : 'O');
        scanf("%d %d", &row, &col);

        if (board[row][col] == ' ') {
            board[row][col] = (turn == 1) ? 'X' : 'O';
            int winner = checkWinner();
            if (winner != 0) {
                printBoard();
                printf("Player %c wins!\n", (winner == 1) ? 'X' : 'O');
                break;
            }
            if (!isMovesLeft()) {
                printBoard();
                printf("It's a draw!\n");
                break;
            }
            turn = -turn; // Switch turns
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

int main() {
    playGame();
    return 0;
}
