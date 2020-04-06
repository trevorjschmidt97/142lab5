#include <iostream>

#include <iomanip>
#include <fstream>

using namespace std;

int main() {

	double oldValues[10][10];
	double newValues[10][10];
	double furtherValues[10][10];
	double inputValues[10][10];
	double newInputValues[10][10];
	double largestChange = .5;
	ofstream outFS;
	ifstream inFS;


	// Array will be managed using [h][v], first horizontal position then vertical.

	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			if (h > 0 && h < 9 && (v == 0 || v == 9)) {
				oldValues[h][v] = 100;
			}
			else {
				oldValues[h][v] = 0;
			}
		}
	}

	// Priniting Initial Plate...
	cout << "Hotplate simulator" << endl << endl;
	cout << "Printing initial plate..." << endl;
	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			cout << fixed << setw(9) << setprecision(3);
			if (h == 9) {
				cout << oldValues[h][v] << endl;
			}
			else {
				cout << oldValues[h][v] << ",";
			}
		}
	}
	cout << endl << endl;


	// One iteration of Hot Plate
	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			if ((h == 0) && (v == 0)) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h+1][v] + oldValues[h][v+1]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
			}
			else if ((h == 0) && (v == 9)) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h][v-1] + oldValues[h+1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
			}
			else if ((h == 9) && (v == 0)) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h][v+1] + oldValues[h-1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
			}
			else if ((h == 9) && (v == 9)) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h][v-1] + oldValues[h-1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
			}
			else if (h == 0) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h][v-1] + oldValues[h][v+1] + oldValues[h+1][v]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
			}
			else if (h == 9) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h][v-1] + oldValues[h][v+1] + oldValues[h-1][v]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
			}
			else if (v == 0) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h-1][v] + oldValues[h+1][v] + oldValues[h][v+1]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
			}
			else if (v == 9) {
				newValues[h][v] = oldValues[h][v]; //(oldValues[h-1][v] + oldValues[h+1][v] + oldValues[h][v-1]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
			}
			else {
				newValues[h][v] = (oldValues[h][v + 1] + oldValues[h][v - 1] + oldValues[h - 1][v] + oldValues[h + 1][v]) / 4;
			}
		}
	}

	//Printing first iteration
	cout << "Printing plate after one iteration..." << endl;
	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			cout << fixed << setprecision(3);
			cout << setw(9);
			if (h == 9) {
				cout << newValues[h][v] << endl;
			}
			else {
				cout << setw(9);
				cout << newValues[h][v] << ", ";
			}
		}
	}
	cout << endl << endl;

	//Computing following iterations
	while (largestChange > 0.1) {
		largestChange = 0;
		for (int v = 0; v < 10; ++v) {
			for (int h = 0; h < 10; ++h) {
				if ((h == 0) && (v == 0)) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h+1][v] + oldValues[h][v+1]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if ((h == 0) && (v == 9)) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h][v-1] + oldValues[h+1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if ((h == 9) && (v == 0)) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h][v+1] + oldValues[h-1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if ((h == 9) && (v == 9)) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h][v-1] + oldValues[h-1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if (h == 0) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h][v-1] + oldValues[h][v+1] + oldValues[h+1][v]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else if (h == 9) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h][v-1] + oldValues[h][v+1] + oldValues[h-1][v]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else if (v == 0) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h-1][v] + oldValues[h+1][v] + oldValues[h][v+1]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else if (v == 9) {
					furtherValues[h][v] = newValues[h][v]; //(oldValues[h-1][v] + oldValues[h+1][v] + oldValues[h][v-1]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else {
					furtherValues[h][v] = (newValues[h][v + 1] + newValues[h][v - 1] + newValues[h - 1][v] + newValues[h + 1][v]) / 4;
				}
			}
			for (int v = 0; v < 10; ++v) {
				for (int h = 0; h < 10; ++h) {
					if ((furtherValues[h][v] - newValues[h][v]) > largestChange) {
						largestChange = (furtherValues[h][v] - newValues[h][v]);
					}
				}
			}
		}
		for (int v = 0; v < 10; ++v) {
			for (int h = 0; h < 10; ++h) {
				newValues[h][v] = furtherValues[h][v];
			}
		}
	}

	//Printing final plate
	cout << "Printing final plate..." << endl;
	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			cout << fixed << setprecision(3);
			cout << setw(9);
			if (h == 9) {
				cout << furtherValues[h][v] << endl;
			}
			else {
				cout << setw(9);
				cout << furtherValues[h][v] << ", ";
			}
		}
	}

	//Outputing Hotplate
	outFS.open("Hotplate.csv");
	if (!outFS.is_open()) {
		cout << "Could not open file Hotplate.csv." << endl;
		return 1; // 1 indicates error
	}
	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			outFS << fixed << setprecision(3);
			outFS << setw(9);
			if (h == 9) {
				outFS << furtherValues[h][v] << endl;
			}
			else {
				outFS << setw(9);
				outFS << furtherValues[h][v] << ", ";
			}
		}
	}
	outFS.close();

	//Inputting Hotplate
	inFS.open("Inputplate.txt");
	if (!inFS.is_open()) {
		cout << "Could not open file Hotplate.csv." << endl;
		return 1; // 1 indicates error
	}

	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			inFS >> inputValues[h][v];
		}
	}
	inFS.close();

	// Iterating input plate 3 times
	for (int i = 0; i < 3; ++i) {
		for (int v = 0; v < 10; ++v) {
			for (int h = 0; h < 10; ++h) {
				if ((h == 0) && (v == 0)) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h+1][v] + inputValues[h][v+1]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if ((h == 0) && (v == 9)) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h][v-1] + inputValues[h+1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if ((h == 9) && (v == 0)) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h][v+1] + inputValues[h-1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if ((h == 9) && (v == 9)) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h][v-1] + inputValues[h-1][v]) / 2; //INPUTS CHANGED CORNER PIECES IF NEEDED
				}
				else if (h == 0) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h][v-1] + inputValues[h][v+1] + inputValues[h+1][v]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else if (h == 9) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h][v-1] + inputValues[h][v+1] + inputValues[h-1][v]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else if (v == 0) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h-1][v] + inputValues[h+1][v] + inputValues[h][v+1]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else if (v == 9) {
					newInputValues[h][v] = inputValues[h][v]; //(inputValues[h-1][v] + inputValues[h+1][v] + inputValues[h][v-1]) / 3; //INPUTS CHANGED EDGE PIECES IF NEEDED
				}
				else {
					newInputValues[h][v] = (inputValues[h][v + 1] + inputValues[h][v - 1] + inputValues[h - 1][v] + inputValues[h + 1][v]) / 4;
				}
			}
		}
		for (int v = 0; v < 10; ++v) {
			for (int h = 0; h < 10; ++h) {
				inputValues[h][v] = newInputValues[h][v];
			}
		}
	}
	cout << endl;

	//Printing Final Input Plate
	cout << "Printing final input..." << endl;
	for (int v = 0; v < 10; ++v) {
		for (int h = 0; h < 10; ++h) {
			cout << fixed << setprecision(3);
			cout << setw(9);
			if (h == 9) {
				cout << newInputValues[h][v] << endl;
			}
			else {
				cout << setw(9);
				cout << newInputValues[h][v] << ", ";
			}
		}
	}

	system("pause");

	return 0;
}