#include <iostream>
#include "head.h"
using namespace std;
extern int gesunkenesplayerboot;
extern int gesunkenesenemyboot;

extern char oneAttack[10][10];
extern char enemyAttack[10][10];

extern char N[10][10];
extern char enemy[10][10];

extern int playeroneMemory[10][10];
extern int playertwoMemory[10][10];

int boatsizecounter = 0;
int enemysizecounter = 0;
void feld(int);

void feldReset(int selection) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (selection) {
			case 1: N[i][j] = ' '; break;
			case 2: enemy[i][j] = ' '; break;
			case 3: oneAttack[i][j] = ' '; break;
			case 4: enemyAttack[i][j] = ' '; break;
			case 5: playeroneMemory[i][j] = 0;  break;
			case 6: playertwoMemory[i][j] = 0;  break;
			default: break;
			}
		}
	}
}

void feld(int feldNummer) {
	cout << "    A | B | C | D | E | F | G | H | I | J \n";
	for (int i = 0; i < 10; i++) {
		cout << i << " | ";
		for (int k = 0; k < 10; k++) {
			switch (feldNummer) {
			case 1: cout << N[i][k] << " | "; break;
			case 2: cout << enemy[i][k] << " | "; break;
			case 3: cout << oneAttack[i][k] << " | "; break;
			case 4: cout << enemyAttack[i][k] << " | "; break;
			default: break;
			}
		}
		cout << endl;

	}
}

void enemyBoot() {
	int r, charInt = 0, size = 1;
	char c;
	feldReset(2);
	//4 schiffe eingeben je 1 quadrat
	for (int i = 0; i < 4; i++) {
		feld(2);
		cout << "\nEnter warship of size " << size << "\nInput the column letter\n";
		cin >> c;
		charInt = (int)c - 65;
		while (charInt > 9) {
			cout << "Error please insert a letter between A and J\n";
			cin >> c;
			charInt = (int)c - 65;
		}
		cout << "Input the row number\n";
		cin >> r;
		while (r < 0 || r>10) {
			cout << "The entered number is too big\n";
			cin >> r;
		}
		enemy[r][charInt] = 'O';
		//2 zeigt das enemy feld an wo der player zwei die boote posizioniert
		playertwoMemory[r][charInt] = 1;
		feld(2);
		system("pause");
		system("cls");
	}
}

void enemywharship() {
	int size, charCOnverter = 0, row;
	char column;
	string direction;
	for (int i = 0; i < 6; i++) {
		feld(2);
		if (i <= 2) {
			size = 2;
		}
		else if (i > 2 and i <= 4) {
			size = 3;
		}
		else if (i == 5) {
			size = 4;
		}
		cout << "\nEnter warship of size " << size << " \nEnter only the first coordinates of your boat\n";
		cin >> column;
		charCOnverter = (int)column - 65;
		while (charCOnverter > 9) {
			cout << "Error please insert a letter between A and J\n";
			cin >> column;
			charCOnverter = (int)column - 65;
		}
		cout << "Input the row number\n";
		cin >> row;
		while (row < 0 || row>10) {
			cout << "The entered number is too big\n";
			cin >> row;
		}
		if (enemy[row][charCOnverter] != ' ') {
			cout << "Already occupied\n";
			enemywharship();
		}
		cout << "Enter direction, horizontal or vertical\n";
		cin >> direction;
		while (direction != "horizontal" and direction != "vertical") {
			cin >> direction;
		}
		enemy[row][charCOnverter] = 'O';
		playertwoMemory[row][charCOnverter] = size;
		if (direction == "horizontal") {
			//horizontal gebe j den wert von der column +1 und dan sage ich das j solange weiter machen soll bis j kleiner als column+die groesse ist 
			for (int j = charCOnverter + 1; j < charCOnverter + size; j++) {
				//programm setzt die restlichen boote   | es geht nur ++ und nicht +1
				if (enemy[row][j] == 'O') {
					cout << "Schon belegt" << endl;
					enemywharship();
				}
				else if (charCOnverter + size > 10) {
					cout << "Error boot geht üvber die grenze\n";
					enemywharship();
				}
				else {
					playertwoMemory[row][j] = size;
					enemy[row][j] = 'O';
					
				}

			}
		}
		else {
			//vertikal
			for (int k = row + 1; k < row + size; k++) {

				if (enemy[k][charCOnverter] == 'O') {
					cout << "Already occupied" << endl;
					enemywharship();
				}
				else {
					playertwoMemory[k][charCOnverter] = size;
					enemy[k][charCOnverter] = 'O';
				}
			}
		}
		//2 zeigt das enemy feld an wo der player zwei die boote posizioniert
		feld(2);
		system("pause");
		system("cls");
	}
}

//player 1
void affondataocolpita(int r, int c, int boatgroesse) {
	//funktioniert| boat counter ist global weil wen sich die funzion schlisst speichert er nicht mehr den wert und wen es global ist bleibt es gespecher| er wird nur resetet wen das boat gekillt worden ist
	if(playertwoMemory[r+1][c] ==boatgroesse){
    
  }
  boatsizecounter++;
  
	if (boatsizecounter < boatgroesse) {
		cout << "Nave colpita\n\n";
		oneAttack[r][c] = 'X';
	}
	else if (boatsizecounter < boatgroesse + 1) {
		gesunkenesplayerboot++;
		cout << "Nave Affondata \t " << "|" << gesunkenesplayerboot << "|10|\n\n";
		oneAttack[r][c] = 'X';
		boatsizecounter = 0;
	}
	playertwoMemory[r][c] = 0;
	feld(3);
}

//player 2

void affondataocolpitaEnemy(int r, int c, int boatgroesse) {
	
	enemysizecounter++;
	if (enemysizecounter < boatgroesse) {
		cout << "Nave colpita\n\n";
		enemyAttack[r][c] = 'X';
	}
	else if (enemysizecounter < boatgroesse + 1) {
		gesunkenesenemyboot++;
		cout << "Nave Affondata \t " << "|" << gesunkenesenemyboot << "|10|\n\n";
		enemyAttack[r][c] = 'X';
		enemysizecounter = 0;
	}
	playeroneMemory[r][c] = 0;
	feld(4);
}