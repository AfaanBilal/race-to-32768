/*
    Race to 32768
    (c) Afaan Bilal
*/
#include <iostream>
#include <stdio.h>

using namespace std;

const int PLAYER_A = 1;
const int PLAYER_B = 2;

int curPlayer = PLAYER_A;

int board[3][3] = {
    {2, 4, 8},
    {16, 32, 64},
    {128, 256, 512}
};

int takenByA[3];
int takenByB[3];

int iA = 0;
int iB = 0;

bool hasWon = false;

void displayBoard();
bool inBoard(int);
int  take(int);
bool checkIfWon();

int main()
{
    for (int i = 0; i < 3; i++)
    {
        takenByA[i] = 0;
        takenByB[i] = 0;
    }

    cout << "\t\t\tRace to 32768" << endl;
    cout << "\thttps://github.com/AfaanBilal/race-to-32768" << endl;
    cout << endl;
    cout << "\tRules:\n\t1. Each player takes one number from the board on every turn." << endl;
    cout << "\t2. First player to have 3 numbers with product equal to 32768 wins." << endl;
    cout << endl;

    int choice = 0;
    while (!hasWon && (iA < 3 || iB < 3))
    {
        displayBoard();
        switch (curPlayer)
        {
            case PLAYER_A:
                cout << endl;
                cout << "\tPLAYER A" << endl;
                cout << "\tEnter your choice: ";
                cin >> choice;
                if (!inBoard(choice))
                {
                    cout << "\tSorry, that choice is not available." << endl;
                    break;
                }
                takenByA[iA++] = take(choice);
                curPlayer = PLAYER_B;
                break;
            case PLAYER_B:
                cout << endl;
                cout << "\tPLAYER B" << endl;
                cout << "\tEnter your choice: ";
                cin >> choice;
                if (!inBoard(choice))
                {
                    cout << "\tSorry, that choice is not available." << endl;
                    break;
                }
                takenByB[iB++] = take(choice);
                curPlayer = PLAYER_A;
                break;
        }

        checkIfWon();
    }

    if (!hasWon && iA == 3 && iB == 3)
    {
        displayBoard();
        cout << endl << "\tThis game is a draw!" << endl;
    }
}

void displayBoard()
{
    cout << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\t    |";
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
                cout << "     | ";
            else
                printf(" %3d | ", board[i][j]);
        }

        cout << endl << endl;
    }

    cout << "\tA has ";
    for (int i = 0; i < iA; i++)
        cout << takenByA[i] << " ";
    if (takenByA[0] == 0) cout << "nothing.";

    cout << endl << "\tB has ";
    for (int i = 0; i < iB; i++)
        cout << takenByB[i] << " ";
    if (takenByB[0] == 0) cout << "nothing.";

    cout << endl << endl;
}

bool inBoard(int c)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == c)
                return true;
    return false;
}

int take(int c)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == c)
            {
                board[i][j] = 0;
                return c;
            }
}

bool checkIfWon()
{
    int prodA = takenByA[0] * takenByA[1] * takenByA[2];
    int prodB = takenByB[0] * takenByB[1] * takenByB[2];

    if (prodA == 32768)
    {
        displayBoard();
        hasWon = true;
        cout << endl << "\t\t\tPlayer A has won!" << endl;
    }

    if (prodB == 32768)
    {
        displayBoard();
        hasWon = true;
        cout << endl << "\t\t\tPlayer B has won!" << endl;
    }
}