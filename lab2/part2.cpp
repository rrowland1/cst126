#include <iostream>
#include <fstream>
#include <iomanip>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;

int addIngredient(char** pStrs, int* numIngredients, char* addedIngredient);

int searchIngredients(char** pStrs, int numIngredients, char* checkIngredient);

int saveToFile(char** pStrs, int numIngredients, char* fileName);

int loadFromFile(char** pStrs, int* numIngredients, char* fileName);

int displayIngredients(char** pStrs, int numIngredients);

const int INGSIZE = 35;
const int PANTRYSIZE = 360;
int main() {
	char* infileName = new char[INGSIZE];
	char* outfileName = new char[INGSIZE];
	char* checkIng = new char[INGSIZE];
	char* newIng = new char[INGSIZE];
	char** pantry = new char* [PANTRYSIZE];
	int numIngredients, addIng;
	strcpy_s(infileName, sizeof("food.txt"), "food.txt");
	strcpy_s(outfileName, sizeof("outfood.txt"), "outfood.txt");
	strcpy_s(newIng, sizeof("cabbage"), "cabbage");
	loadFromFile(pantry, &numIngredients, infileName);
	cout << "Enter the amount of ingredients do you want to add: ";
	cin >> addIng;
	for (int i = 0; i < addIng; i++) {
		cout << "Enter the ingredient you want to add: ";
		cin >> newIng;
		addIngredient(pantry, &numIngredients, newIng);
	}
	cout << "Enter the ingredient to search: ";
	cin >> checkIng;
	searchIngredients(pantry, numIngredients, checkIng);


	displayIngredients(pantry, numIngredients);
	cout << "Saving to file..." << endl;
	saveToFile(pantry, numIngredients, outfileName);

	for (int i = 0; i < numIngredients; ++i)
		delete[] pantry[i];
	delete[] pantry;
	delete[] infileName;
	delete[] outfileName;
	delete[] newIng;
	delete[] checkIng;

	return 0;
}
int loadFromFile(char** pStrs, int* numIngredients, char* fileName) {
	int counter = 0;
	char buffer[INGSIZE];
	ifstream fin(fileName);

	while (!fin.eof()) {
		fin >> buffer;
		pStrs[counter] = new char[strlen(buffer) + 1];
		strcpy_s(pStrs[counter], strlen(buffer) + 1, buffer);
		counter++;
	}
	*numIngredients = counter;
	fin.close();
	return 0;
}
int displayIngredients(char** pStrs, int numIngredients) {
	for (int i = 0; i < numIngredients; i++) {
		cout << pStrs[i] << endl;
	}
	return 0;
}
int addIngredient(char** pStrs, int* numIngredients, char* addedIngredient) {
	pStrs[*numIngredients] = new char[strlen(addedIngredient) + 1];
	strcpy_s(pStrs[*numIngredients], strlen(addedIngredient) + 1, addedIngredient);
	++*numIngredients;
	return 0;
}
int searchIngredients(char** pStrs, int numIngredients, char* checkIngredient) {
	bool found = false;
	int index;
	for (int i = 0; i < numIngredients; i++) {
		if (!strcmp(pStrs[i], checkIngredient)) {
			found = true; index = i; break;
		}
	}
	if (found)
		cout << "Found: " << checkIngredient << " at pantry index: " << index << endl;
	else
		cout << "Not found: " << checkIngredient << endl;
	return 0;
}
int saveToFile(char** pStrs, int numIngredients, char* fileName) {
	ofstream fout(fileName);
	for (int i = 0; i < numIngredients; i++) {
		fout << pStrs[i] << endl;
	}
	fout.close();
	return 0;
}
