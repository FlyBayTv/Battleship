// 4x motoscafo   3x Nave d'assalto   2x crociera   1x corazzata
//       1                 2               3              4
//219
#include "head.h"
#include <iostream>
using namespace std;

char N[10][10];
char enemy[10][10];

// angriffspositionen
char oneAttack[10][10];
char enemyAttack[10][10];
// Größe vom boot speichern
int playeroneMemory[10][10];
int playertwoMemory[10][10];
int gesunkenesplayerboot = 0;
int gesunkenesenemyboot = 0;

void multiplayer();
void otherwharship();
int column(bool);
int rowInput();
void menu(); 

void singelBoot() {
    int r, charInt = 0, size = 1;
    char c;
    feldReset(1);
    // 4 schiffe eingeben je 1 quadrat
    for (int i = 0; i < 4; i++) {
        feld(1);
        cout << "\nBoat of the size " << size << " \n\nInput the column letter\n";
        cin >> c;
        charInt = (int)c - 65;
        while (charInt > 9) {
            cout << "Error please insert a letter between A and J\n";
            cin >> c;
            charInt = (int)c - 65;
        }
        cout << "Input the row number\n";
        cin >> r;
        while (r < 0 || r > 10) {
            cout << "The entered number is too big\n";
            cin >> r;
        }
        N[r][charInt] = 'O';
        //Ich speicher in einer matrix die grössen von dem boot speichern, so erkenne ich was für ein typ boot gespeichert ist | boot der grösse 1
        playeroneMemory[r][charInt] = 1;
        feld(1);
        system("pause");
        system("cls");
    }
}

void otherwharship() {
    int size, charCOnverter = 0, row;
    char column;
    string direction;
    for (int i = 0; i < 6; i++) {
        feld(1);
        if (i <= 2) {
            size = 2;
        }
        else if (i > 2 and i <= 4) {
            size = 3;
        }
        else if (i == 5) {
            size = 4;
        }
        cout << "Boat of the size " << size
            << ": \nEnter only the first coordinates of your boat, Column: \n";
        cin >> column;
        charCOnverter = (int)column - 65;
        while (charCOnverter > 9) {
            cout << "Error please insert a letter between A and J\n";
            cin >> column;
            charCOnverter = (int)column - 65;
        }
        cout << "Input the row number\n";
        cin >> row;
        while (row < 0 || row > 10) {
            cout << "The entered number is too big\n";
            cin >> row;
        }
        if (N[row][charCOnverter] != ' ') {
            cout << "Already occupied\n";
            otherwharship();
        }
        cout << "Please enter the direction of the boat, horizontal or vertical\n";
        cin >> direction;
        while (direction != "horizontal" and direction != "vertical") {
            cin >> direction;
        }
        N[row][charCOnverter] = 'O';
        playeroneMemory[row][charCOnverter] = size;
        if (direction == "horizontal") {
            //gebe jeden wert von der säule + 1 und dann sage ich das j solange weiter machen soll bis j kleiner als die säule +die groesse ist
            for (int j = charCOnverter + 1; j < charCOnverter + size; j++) {
                // programm setzt die restlichen boote   | es geht nur ++ und nicht +1
                if (N[row][j] == 'O') {
                    cout << "Already occupied" << endl;
                    otherwharship();
                }
                else if (charCOnverter + size > 10) {
                    cout << "Error boot goes over the edge\n";
                    otherwharship();
                }
                else {
                    playeroneMemory[row][j] = size;
                    N[row][j] = 'O';
                }
            }
        }
        else {
            // vertikal
            for (int k = row + 1; k < row + size; k++) {

                if (N[k][charCOnverter] == 'O') {
                    cout << "Already occupied" << endl;
                    otherwharship();
                }
                else if (row + size > 10) {
                    cout << "Error boot goes over the edge\n";
                    otherwharship();
                }
                else {
                    playeroneMemory[k][charCOnverter] = size;
                    N[k][charCOnverter] = 'O';
                }
            }
        }
        // 1 zeigt das feld an vom player one an, wo er seine boote posizioniert hat
        feld(1);
        system("pause");
        system("cls");
    }
}

int column(bool player) {
    int converter, playerturn;
    char inputColumn = ' ';
    // wahr --> player one runde |  falsch--> player zwei runde
    if (player == true) {
        playerturn = 1;
    }
    else {
        playerturn = 2;
    }
    system("cls");
    cout << "\n          | ------------------------- |\n";
    cout << "          | Player " << playerturn << " Attack the enemy |\n";
    cout << "          | ------------------------- |\n\n\n";
    if (player==true) {
        feld(3);
    }
    else {
        feld(4);
    }
    cout << "\nInput column: \n";
    cin >> inputColumn;
    converter = (int)inputColumn - 65;
    while (converter > 9) {
        cout << "Error please insert a letter between A and J\n";
        cin >> inputColumn;
        converter = (int)inputColumn - 65;
    }
    return converter;
}

int rowInput() {
    int reihe;
    cout << "Please enter the row: " << endl;
    cin >> reihe;
    while (reihe < 0 || reihe > 10) {
        cout << "The entered number is too big\n";
        cin >> reihe;
    }
    return reihe;
}

void multiplayer() {
    bool playerone = true;
    
    feldReset(1);
    // memory feld der boot grösse wird resettet bei jedem neustart
    feldReset(5);
    feldReset(6);
    cout << "\n          | -------------------- |\n";
    cout << "          |    Player 1 Input    |\n";
    cout << "          | -------------------- |\n\n\n";
    singelBoot();
    otherwharship();
    //enemy input
    cout << "\n          | -------------------- |\n";
    cout << "          |    Player 2 Input    |\n";
    cout << "          | -------------------- |\n\n\n";
    feldReset(2);
    enemyBoot();
    enemywharship();
    feldReset(3);
    feldReset(4);
    //system("pause");
    //system("cls");
    int columNumber, reihe, hitcounter = 0, doublecounter = 0, othercounter = 0, viercouter = 0;
    //Alternativer input
    while (true) {
        columNumber = column(playerone);
        reihe = rowInput();
        //player 1
        if (playerone == true) {
            //suchen ob er ein boot angegriffen hatt indem ich die reihe und die zeile in der ememy matrix eingebe und wen an der posizion ein boot ist dan gebe ich es aus
            if (enemy[reihe][columNumber] == 'O') {                //kontrollieren was für eine grösse das boot hat
                if (playertwoMemory[reihe][columNumber] == 1) {
                    gesunkenesplayerboot++;
                    cout << "Motoscafo affondato |" << gesunkenesplayerboot << "|10| " << endl<<endl;
                    oneAttack[reihe][columNumber] = 'X';

                    feld(3);
                }
                //boot der grösse zwei
                else if (playertwoMemory[reihe][columNumber] == 2) {
                    affondataocolpita(reihe, columNumber, 2);
                }
                else if (playertwoMemory[reihe][columNumber] == 3) {
                    affondataocolpita(reihe, columNumber, 3);
                }
                else if (playertwoMemory[reihe][columNumber] == 4) {
                    affondataocolpita(reihe, columNumber, 4);
                }
                if(gesunkenesplayerboot == 10) {
                    cout << "\n| --------------------------- |\n";
                    cout << "| Player One has won the game |\n";
                    cout << "| --------------------------- |\n\n\n";
                    menu();
                }
            }
            else {
                cout << "No ships hit\n";
                oneAttack[reihe][columNumber] = '-';
                //3 zeigt die attack posizionen dan vom ersten player
                feld(3);
            }
        }
        //player 2
        else if (playerone == false) {
            //suchen ob an der posizion wo der enemy eingegeben hat ein bot beim player one das ist 
            if (N[reihe][columNumber] == 'O') {
                //suchen ob das boot wo getroffen wurde ein singelboot ist oder nicht und dan output ausgeben
                if (playeroneMemory[reihe][columNumber] == 1) { // das ist boot ein singelboot dank memorymatrix wo an der posizion di grösse gespeichert ist 2693
                    gesunkenesenemyboot++;
                    cout << "Nave Affondata |"<< gesunkenesenemyboot <<"|10| " <<endl;
                    enemyAttack[reihe][columNumber] = 'X';
                    feld(4);
                }
                else if (playeroneMemory[reihe][columNumber] == 2) {
                    affondataocolpitaEnemy(reihe, columNumber, 2);
                }
                else if (playeroneMemory[reihe][columNumber] == 3) {
                    affondataocolpitaEnemy(reihe, columNumber, 3);
                }
                else if (playeroneMemory[reihe][columNumber] == 4) {
                    affondataocolpitaEnemy(reihe, columNumber, 4);
                }
                if (gesunkenesenemyboot == 10) {
                    cout << "\n| --------------------------- |\n";
                    cout << "| Player Two has won the game |\n";
                    cout << "| --------------------------- |\n\n\n";
                    menu();
                }
            }
            else {
                enemyAttack[reihe][columNumber] = '-';
                //4 zeigt die enemy posizionen an vom enemy palyer
                cout << "No ships hit\n";
                feld(4);
            }
        }
        playerone = !playerone;
        system("pause");
        system("cls");
    }
}

void singelplayer() {
    cout << "Single Player Gamemode is in progress\n\n";
    menu();
}

void menu() {
    cout << "                     | BATTLESHIP |\n"
         << "                 | Hello and welcome |\n\n" 
         << " | You play with 10 warships of 1, 2, 3 and 4 squares | \n"<< endl;
    cout << "--------------------------------------------------------\n\n";
    cout << "Enter [1] to play against a boat, or [2] to play against a friend, or enter any number or letter to end the game" << endl;
    int select;
    cout << "Choose: " << endl;
    cin >> select;
    while (select < 1 and select > 2) {
        cout << "Please insert a number between 1 and 2: " << endl;
        cin >> select;
    }
    switch (select) {
    case 1:
        singelplayer(); break;
    case 2:
        multiplayer(); break;

    default: return; break;
    }
}

int main() {
    int n = 223;
   
    menu();
    system("pause");
    return 0;
}