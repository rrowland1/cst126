#include <iostream>
#include <fstream>
#include <iomanip>

using std::ifstream;
using std::cout;
using std::cin;
using std::endl;

int loadFromFile(char** pStrs, int* numIngredients, char* fileName);
int displayIngredients(char** pStrs, int numIngredients);
const int INGSIZE = 35;
const int PANTRYSIZE = 360;
int main() {
	char* fileName = new char[INGSIZE];
	int numIngredients;
	cout << "How many ingredients are there? ";
	cin >> numIngredients;
	strcpy_s(fileName, sizeof("food.txt"), "food.txt");
	char** pantry = new char* [PANTRYSIZE];


	loadFromFile(pantry, &numIngredients, fileName);
	displayIngredients(pantry, numIngredients);


	for (int i = 0; i < numIngredients; ++i)
		delete[] pantry[i];
	delete[] pantry;
	delete[] fileName;

	return 0;
}
int loadFromFile(char** pStrs, int* numIngredients, char* fileName) {
	int counter = 0;
	char buffer[INGSIZE];
	ifstream fin(fileName);

	while (!fin.eof() && (counter < *numIngredients)) {
		fin >> buffer;

		pStrs[counter] = new char[strlen(buffer) + 1];
		strcpy_s(pStrs[counter], strlen(buffer) + 1, buffer);

		counter++;
	}
	return 0;
}
int displayIngredients(char** pStrs, int numIngredients) {
	for (int i = 0; i < numIngredients; i++) {
		cout << pStrs[i] << endl;
	}
	return 0;
}
