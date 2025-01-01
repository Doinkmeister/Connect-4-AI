#include <iostream>
#include <tuple>
#include <limits>
using namespace std;

int rows = 6;
int cols = 7;
int turn = 1;
int maxDepth;

int board[][7] = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},

        } ;


void printBoard(int boa[][7]) {
    for(int a = 0; a < rows; a++)
    {
        for(int b = 0; b < cols; b++)
        {
          cout << boa[a][b] << " ";
        }
        cout << endl;
    }
    cout << endl;
}



bool checkWin(int turn, int boa[][7]) {
    int checker = turn; 

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 4; col++) { 
            if (boa[row][col] == checker and
                boa[row][col + 1] == checker and
                boa[row][col + 2] == checker and
                boa[row][col + 3] == checker) {
                return true;
            }
        }
    }

    
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row < 3; row++) { 
            if (boa[row][col] == checker and
                boa[row + 1][col] == checker and
                boa[row + 2][col] == checker and
                boa[row + 3][col] == checker) {
                return true;
            }
        }
    }

    
    for (int row = 3; row < 6; row++) {
        for (int col = 0; col < 4; col++) {
            if (boa[row][col] == checker and
                boa[row - 1][col + 1] == checker and
                boa[row - 2][col + 2] == checker and
                boa[row - 3][col + 3] == checker) {
                return true;
            }
        }
    }

    
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) { 
            if (boa[row][col] == checker and
                boa[row + 1][col + 1] == checker and
                boa[row + 2][col + 2] == checker and
                boa[row + 3][col + 3] == checker) {
                return true;
            }
        }
    }

    return false;
}


void changeTurn(){
    if (turn == 1){
        turn = 2;
    }
    else {
        turn = 1;
    }
}

bool tiedBoard(int boa[][7]){
    for (int a = 0; a < 6; a++) {
        for (int b = 0; b < 7; b++) {
            if (boa[a][b] == 0) {
                return false;
            }
        }
    }
    return true;
}

int evaluateBoard(int board[][7]) {
    int score = 0;

    // Check column 3 for both players, giving higher scores for central control.
    for (int row = 0; row < rows; row++) {
        if (board[row][3] == 2) { // Player 2's piece in column 3
            score += 150;
        }
        if (board[row][3] == 1) { // Player 1's piece in column 3
            score -= 150;
        }
    }

    // Check column 4 for both players, giving slightly lower scores than column 3.
    for (int row = 0; row < rows; row++) {
        if (board[row][4] == 2) { // Player 2's piece in column 4
            score += 100;
        }
        if (board[row][4] == 1) { // Player 1's piece in column 4
            score -= 100;
        }
    }

    // Check column 2 for both players, similar scoring to column 4.
    for (int row = 0; row < rows; row++) {
        if (board[row][2] == 2) { // Player 2's piece in column 2
            score += 100;
        }
        if (board[row][2] == 1) { // Player 1's piece in column 2
            score -= 100;
        }
    }

    // Check for horizontal two-in-a-row patterns with an empty space for a potential connection.
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols - 2; col++) {
            if (board[row][col] == 2 && board[row][col + 1] == 2 && board[row][col + 2] == 0) {
                score += 300; // Player 2's potential connection
            }
            if (board[row][col] == 1 && board[row][col + 1] == 1 && board[row][col + 2] == 0) {
                score -= 300; // Player 1's potential connection
            }
        }
    }

    // Check for 2x2 squares of four connected pieces.
    for (int row = 0; row < rows - 1; row++) {
        for (int col = 0; col < cols - 1; col++) {
            if (board[row][col] == 2 && board[row][col + 1] == 2 &&
                board[row + 1][col] == 2 && board[row + 1][col + 1] == 2) {
                score += 200; // Player 2's 2x2 square
            }
            if (board[row][col] == 1 && board[row][col + 1] == 1 &&
                board[row + 1][col] == 1 && board[row + 1][col + 1] == 1) {
                score -= 200; // Player 1's 2x2 square
            }
        }
    }

    // Check for horizontal three-in-a-row patterns with an empty space for a potential connection.
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (board[row][col] == 2 && board[row][col + 1] == 2 &&
                board[row][col + 2] == 2 && board[row][col + 3] == 0) {
                score += 550; // Player 2's potential connection
            }
            if (board[row][col] == 1 && board[row][col + 1] == 1 &&
                board[row][col + 2] == 1 && board[row][col + 3] == 0) {
                score -= 550; // Player 1's potential connection
            }
        }
    }

    // Check for vertical three-in-a-row patterns with an empty space for a potential connection.
    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] == 2 && board[row + 1][col] == 2 &&
                board[row + 2][col] == 2 && board[row + 3][col] == 0) {
                score += 350; // Player 2's potential connection
            }
            if (board[row][col] == 1 && board[row + 1][col] == 1 &&
                board[row + 2][col] == 1 && board[row + 3][col] == 0) {
                score -= 350; // Player 1's potential connection
            }
        }
    }

    // Check for diagonal (bottom-left to top-right) three-in-a-row patterns with an empty space.
    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (board[row][col] == 2 && board[row + 1][col + 1] == 2 &&
                board[row + 2][col + 2] == 2 && board[row + 3][col + 3] == 0) {
                score += 850; // Player 2's potential connection
            }
            if (board[row][col] == 1 && board[row + 1][col + 1] == 1 &&
                board[row + 2][col + 2] == 1 && board[row + 3][col + 3] == 0) {
                score -= 850; // Player 1's potential connection
            }
        }
    }

    // Check for diagonal (top-left to bottom-right) three-in-a-row patterns with an empty space.
    for (int row = 3; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (board[row][col] == 2 && board[row - 1][col + 1] == 2 &&
                board[row - 2][col + 2] == 2 && board[row - 3][col + 3] == 0) {
                score += 850; // Player 2's potential connection
            }
            if (board[row][col] == 1 && board[row - 1][col + 1] == 1 &&
                board[row - 2][col + 2] == 1 && board[row - 3][col + 3] == 0) {
                score -= 850; // Player 1's potential connection
            }
        }
    }

    // Check for "7-formation" patterns
    for (int row = 0; row < rows - 2; row++) {
        for (int col = 0; col < cols - 2; col++) {

            if (board[row][col] == 2 && board[row][col + 1] == 2 && board[row][col + 2] == 2 &&
                board[row + 1][col + 1] == 2 &&
                board[row + 2][col] == 2) {
                score += 400;
            }
            if (board[row][col] == 1 && board[row][col + 1] == 1 && board[row][col + 2] == 1 &&
                board[row + 1][col + 1] == 1 &&
                board[row + 2][col] == 1) {
                score -= 400;
            }

            if (board[row][col] == 2 && board[row][col + 1] == 2 && board[row][col + 2] == 2 &&
                board[row + 1][col + 1] == 2 &&
                board[row + 2][col + 2] == 2) {
                score += 400;
            }
            if (board[row][col] == 1 && board[row][col + 1] == 1 && board[row][col + 2] == 1 &&
                board[row + 1][col + 1] == 1 &&
                board[row + 2][col + 2] == 1) {
                score -= 400;
            }
        }
    }

        return score;
}


int minimax(int minimaxBoard[][7], int depth, int alpha, int beta, bool isMaximising, int maxDepth) {

    if (checkWin(2, minimaxBoard)) {
        return 99999999;
    } else if (checkWin(1, minimaxBoard)) {
        return -999999999;
    } else if (tiedBoard(minimaxBoard)) {
        return 0;
    } else if (depth == maxDepth) {
        return evaluateBoard(minimaxBoard);
    }

    if (isMaximising) {
        int bestScore = -999999;
        alpha = -999999;
        for (int col = 0; col < 7; col++) {
            int row = -1;
            for (int r = 5; r >= 0; r--) {
                if (minimaxBoard[r][col] == 0) {
                    row = r;
                    break;
                }
            }

            
            if (row != -1) {
                minimaxBoard[row][col] = 2;
                int score = minimax(minimaxBoard, depth + 1, alpha, beta, false, maxDepth);
                minimaxBoard[row][col] = 0;
                bestScore = max(score, bestScore);
                alpha = max(alpha, score);
                if (beta <= alpha) {
                    break;
                }
            }
        }

        return bestScore;
    } else {
        int bestScore = 999999;
        beta = 999999;
        for (int col = 0; col < 7; col++) {
            int row = -1;
            
            for (int r = 5; r >= 0; r--) {
                if (minimaxBoard[r][col] == 0) {
                    row = r;
                    break;
                }
            }

            
            if (row != -1) {
                minimaxBoard[row][col] = 1; 
                int score = minimax(minimaxBoard, depth + 1, alpha, beta, true, maxDepth);  
                minimaxBoard[row][col] = 0;
                bestScore = min(score, bestScore);
                beta = min(beta, score);
                if (beta <= alpha) {
                    break;
                }
            }
        }

        return bestScore;
    }
}


bool bestMove() {
    int bestScore = -99999999;
    int alpha = -999999;
    int beta = 999999;
    tuple <int, int> moveChosen(-1, -1);

    for (int col = 0; col < 7; col++) {
        int row = -1;
        for (int r = 5; r >= 0; r--) {
            if (board[r][col] == 0) {
                row = r;
                break;
            }
        }

        if (row != -1) {

            board[row][col] = 1;
            if (checkWin(1, board)) {
                board[row][col] = 0;
                board[row][col] = 2;
                return true;
            }
            board[row][col] = 0;

            board[row][col] = 2;
            int score = minimax(board, 0, false, alpha, beta, maxDepth);
            board[row][col] = 0;
            if (score > bestScore) {
                bestScore = score;
                moveChosen = make_tuple(row, col);
            }

            else if (score == bestScore) {
                if (abs(col - 3) < abs(get<1>(moveChosen) - 3)) {
                    moveChosen = make_tuple(row, col);
                }
            }

            if (get<0>(moveChosen) == -1) {
                moveChosen = make_tuple(row, col);
            }

        }
    }   

    if (get<0>(moveChosen) != -1 and get<1>(moveChosen) != -1){
        board[get<0>(moveChosen)][get<1>(moveChosen)] = 2;
        return true;
    }
    return false;
}

int main()
{
    bool game_over = false;
    
    int answer;

    while (true) {
        cout << "Easy, medium, hard or impossible? (1, 2, 3, 4) ";
        cin >> answer;

        if (cin.fail()) {
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Please enter a valid number between 1 and 4." << endl;
            continue;
        }

        else if (answer < 1 or answer > 4) {
            cout << "Please pick a difficulty 1-4. " << endl;
        }

        else {
            break;
        }
    }
    
    switch (answer) {
        case 1:
            maxDepth = 2;
            break;
        case 2:
            maxDepth = 4;
            break;
        case 3:
            maxDepth = 6;
            break;
        case 4:
            maxDepth = 8;
            break;
    }
    
    while (!game_over) {
        printBoard(board);
        if (turn == 1){
            int move;
            
            while (true) {
                cout << "Pick a column! ";
                cin >> move;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a valid number between 0 and 6." << endl;
                    continue;
                }

                else if (move < 0 or move > 6) {
                    cout << "Invalid column. Please pick a column between 0 and 6. " << endl;
                }

                else if (board[0][move] != 0) {
                    cout << "This column is full. Please pick a different column. " << endl;
                } 

                else {
                    break;
                }
            }
            
            int row = 5;
            while (row >= 0) {
                if (board[row][move] == 0) {
                    board[row][move] = 1;

                    if (checkWin(1, board)) {
                        printBoard(board);
                        cout << "Player won. Congratulations! " << endl;
                        game_over = true;
                    }

                    changeTurn();
                    break;
                } 

                else {
                    row--;
                }
            }
        }
        
        else {
            bestMove();
            if (checkWin(2, board)) {
                printBoard(board);
                cout << "AI won. Better luck next time! " << endl;
                game_over = true;
            }
            changeTurn();
        }
        
        if (tiedBoard(board)){
            printBoard(board);
            cout << "No available moves left. DRAW! " << endl;
            game_over = true;
        }
    }
    return 0;
}
