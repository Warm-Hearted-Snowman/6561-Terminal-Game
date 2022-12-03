#include <iostream> //library for input and output from code
#include <bits/stdc++.h> //library for (power & time) function
#include <conio.h> //library for (getch) function
#include <unistd.h> //library for (sleep) function
#include <cstdlib> //library for  (srand & rand) function

using namespace std;

int l, r, c, o; //in order for (level select-set row-set column-display option)
char ch; //user input
bool win = false; //winCheck flag
int **table, **temp; //make table and temp matrix to check can 'up, down, left, right' functions call

void display(); //func to show table and members of matrix
void upMove();

void downMove();

void leftMove();

void rightMove();

void addBlock(); //adds random numbers to random place after 'up, down, left, right' functions
void addCheck(); //checks addBlock func. can call
void gameOverCheck(); //checks that is game over or not!
void opening(); //shows group information
void level(); //lets user enter his desired level
void selectOpening();

void
tableMaking(); //makes (temp and table) matrix, enters 0 for all matrix members and put 2 random number in random places in (table) matrix
void sync(); //equals matrix 'table' to matrix 'temp' (syncing)
void input(); //inputs user entry value for calling 'up, down, left, right' functions
void winCheck(); //check does player reach 6165 number or no!
void hint(); //shows how to control the game

int main() {
    selectOpening();
    tableMaking();
    while (1) {
        sync();
        input();
        addCheck();
        display();
        gameOverCheck();
        winCheck();
    }
}

void display() {
    int i, j;
    cout << "\n\n\n";
    for (i = 0; i < r; i++) {
        cout << "\t\t\t\t---";
        for (int k = 0; k < c; ++k) {//print ---
            cout << "---";
        }
        cout << "\n\t\t\t\t";
        for (j = 0; j < c; j++) {//print member ha
            if (table[i][j] == 0)
                cout << "|   ";
            else
                cout << "| " << table[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "\t\t\t\t---";
    for (int k = 0; k < c; ++k) {//print last line of ---
        cout << "---";
    }
    cout << "\n\t\t\t\t";
    hint();
}

void upMove() {
    //in this function we compare second row and first column place with its above and if we could we upMove
    int i, j, li, ri;
    for (j = 0; j < c; j++) {
        li = 0, ri = j;
        for (i = 1; i < r; i++) {
            if (table[i][j] != 0) {
                if (table[i - 1][j] == 0 || table[i - 1][j] == table[i][j]) {
                    if (table[li][ri] == table[i][j]) {
                        table[li][ri] *= 3;
                        table[i][j] = 0;
                    } else {
                        if (table[li][ri] == 0) {
                            table[li][ri] = table[i][j];
                            table[i][j] = 0;
                        } else {//if first and third matrix member wasn't equal this part of code will run
                            table[++li][ri] = table[i][j];
                            table[i][j] = 0;
                        }
                    }
                } else li++;
            }
        }
    }
}

void downMove() {
    //in this function we compare last row with its above and if we could we downMove
    int i, j, li, ri;
    for (j = 0; j < c; j++) {
        li = r - 1, ri = j;
        for (i = r - 2; i >= 0; i--) {
            if (table[i][j] != 0) {
                if (table[i + 1][j] == 0 || table[i + 1][j] == table[i][j]) {
                    if (table[li][ri] == table[i][j]) {
                        table[li][ri] *= 3;
                        table[i][j] = 0;
                    } else {
                        if (table[li][ri] == 0) {
                            table[li][ri] = table[i][j];
                            table[i][j] = 0;
                        } else {//if last and two left to the last matrix member wasn't equal this part of code will run
                            table[--li][ri] = table[i][j];
                            table[i][j] = 0;
                        }
                    }
                } else
                    li--;
            }
        }
    }
}

void leftMove() {
    //in this function we compare second member of first row with its left member and if we could we leftMove
    int i, j, li, ri;
    for (i = 0; i < r; i++) {
        li = i, ri = 0;
        for (j = 1; j < c; j++) {
            if (table[i][j] != 0) {
                if (table[i][j - 1] == 0 || table[i][j - 1] == table[i][j]) {
                    if (table[li][ri] == table[i][j]) {
                        table[li][ri] *= 3;
                        table[i][j] = 0;
                    } else {
                        if (table[li][ri] == 0) {
                            table[li][ri] = table[i][j];
                            table[i][j] = 0;
                        } else {//if first member of left and two left to the first member wasn't equal this part of code will run
                            table[li][++ri] = table[i][j];
                            table[i][j] = 0;
                        }
                    }
                } else
                    ri++;
            }
        }
    }
}

void rightMove() {
    //in this function we compare two left to the last matrix member of first row with its first row member and if we could we leftMove
    int i, j, li, ri;
    for (i = 0; i < r; i++) {
        li = i, ri = c - 1;
        for (j = c - 2; j >= 0; j--) {
            if (table[i][j] != 0) {
                if (table[i][j + 1] == 0 || table[i][j + 1] == table[i][j]) {
                    if (table[li][ri] == table[i][j]) {
                        table[li][ri] *= 3;
                        table[i][j] = 0;
                    } else {
                        if (table[li][ri] == 0) {
                            table[li][ri] = table[i][j];
                            table[i][j] = 0;
                        } else {//if last member of right and two left to the last right member wasn't equal this part of code will run
                            table[li][--ri] = table[i][j];
                            table[i][j] = 0;
                        }
                    }
                } else
                    ri--;
            }
        }
    }
}

void addBlock() {
    int li, ri;
    srand(time(0));
    while (1) {
        li = rand() % r;
        ri = rand() % c;
        if (table[li][ri] == 0) {
            table[li][ri] = pow(3, li % 2 + 1);
            break;
        }
    }
}

void addCheck() {
    int fl = 1, i, j;
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            if (temp[i][j] != table[i][j]) {
                fl = 0;
                break;
            }
    if (fl == 0)addBlock();
}

void gameOverCheck() {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (table[i][j] == 0)
                return;
        }
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if ((j + 1 < c && table[i][j] == table[i][j + 1]) || (i + 1 < r && table[i][j] == table[i + 1][j]))
                return;
        }
    }
    cout << "\n\n\t\t\tYOU LOOSE\n\n\t\t\tGAME OVER!!\n\n\n";
    getch();
    exit(0);
}

void opening() {
    cout << "\n\n\t\tWELCOME\t\t\n\n";
    cout
            << "Developer :\nAmirHousein HedayatPour Toupkanlou ( Warm-Hearted-Snowman )\namirhtpt.a@gmail.com\ngithub.com/Warm-Hearted-Snowman\n\n";
    cout << "Press Enter to continue ...";
    getch();
    system("CLS");
}

void selectOpening() {
    cout << "\n\n\t===((WELCOME))===\t\n\n";
    cout << "\n\n\n1.Start the Game\n2.Credits and Developer\n\n\nChoose your Option :\n";
    cin >> o;
    system("CLS");
    switch (o) {
        case 1:
            level();
            break;
        case 2:
            opening();
            selectOpening();
            break;
        default:
            cout << "Choose correct Option.";
            break;
    }
    system("CLS");
}

void level() {
    cout << "\n\n\n1.Small\n2.Normal\n3.Big\n\n\nEnter your level :\n";
    cin >> l;
    system("CLS");
    switch (l) {
        case 1:
            r = 3, c = 2;
            break;
        case 2:
            r = 5, c = 4;
            break;
        case 3:
            r = 7, c = 6;
            break;
    }
}

void tableMaking() {
    table = new int *[r];
    for (int i = 0; i < r; i++) {
        table[i] = new int[c];
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            table[i][j] = 0;
        }
    }
    temp = new int *[r];
    for (int i = 0; i < r; i++) {
        temp[i] = new int[c];
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            temp[i][j] = 0;
        }
    }
    int i1, i2, i3, i4;
    srand(time(0));
    i1 = rand() % r;
    i2 = rand() % c;
    while (1) {
        i3 = rand() % r;
        i4 = rand() % c;
        if (i3 != i1 && i4 != i2) break;
    }
    table[i1][i2] = 3;
    table[i3][i4] = 9;
    display();
}

void sync() {
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            temp[i][j] = table[i][j];
        }
    }
}

void input() {
    ch = getch();
    system("cls");
    if (ch == 'w' || ch == 72)
        upMove();
    else if (ch == 's' || ch == 80)
        downMove();
    else if (ch == 'a' || ch == 75)
        leftMove();
    else if (ch == 'd' || ch == 77)
        rightMove();
    else if (ch == 27)
        selectOpening();
    else if (ch == '0')
        exit(0);
}

void winCheck() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!win && table[i][j] == 6561) {
                cout << "\n\n\nYou've just reached to the end, do you wanna continue ?\n\n1.Finish\n2.Continue\n";
                int f;
                cin >> f;
                switch (f) {
                    case 1:
                        cout << "\nYou chose to finish, Press Enter to close the program.";
                        getch();
                        exit(0);
                    case 2:
                        cout << "\nYou chose to continue, press Enter to continue.";
                        getch();
                }
                win = true;
            }
        }
    }
}

void hint() {
    cout << "\n\n\t\tUse below hotkeys to play game ( or play with arrow keys )\n\n\n"
         << "\t\t\t\tw\n\n\n\t\t\ta\ts\td\n";
    cout << "\n\nClose the game : press 0\nGo to main menu : press 'ESC'\n";
}