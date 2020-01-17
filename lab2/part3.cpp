#define _CRT_DBG_MAP_ALLOC
#include <iostream>
#include <fstream>
#include <iomanip>
#include <crtdbg.h>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;

int changeIngredient(char** pStrs, int numIngredients, char* oldIngredient, char* newIngredient);
int removeIngredient(char** pStrs, int* numIngredients, char* removeIngredient);
int addIngredient(char** pStrs, int* numIngredients, char* addedIngredient);
int searchIngredients(char** pStrs, int numIngredients, char* checkIngredient);
int saveToFile(char** pStrs, int numIngredients, char* fileName);
int loadFromFile(char** pStrs, int* numIngredients, char* fileName);
int displayIngredients(char** pStrs, int numIngredients);

const int INGSIZE = 35;
const int PANTRYSIZE = 360;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char* infileName = new char[INGSIZE];
	char* outfileName = new char[INGSIZE];
	char* addIng = new char[INGSIZE];
	char* searchIng = new char[INGSIZE];
	char* changeIng = new char[INGSIZE];
	char* replaceIng = new char[INGSIZE];
	char* removeIng = new char[INGSIZE];
	char** pantry = new char* [PANTRYSIZE];
	int numIngredients;
	bool alive = true;
	strcpy_s(infileName, sizeof("food.txt"), "food.txt");
	strcpy_s(outfileName, sizeof("outfood.txt"), "outfood.txt");
	loadFromFile(pantry, &numIngredients, infileName);
	displayIngredients(pantry, numIngredients);
	cout << "Enter the ingredient to add: ";
	cin >> addIng;
	addIngredient(pantry, &numIngredients, addIng);
	cout << "Enter the ingredient to search: ";
	cin >> searchIng;
	searchIngredients(pantry, numIngredients, searchIng);
	cout << "Enter the ingredient to change: ";
	cin >> changeIng;
	cout << "Enter the ingredient to replace it with: ";
	cin >> replaceIng;
	changeIngredient(pantry, numIngredients, changeIng, replaceIng);
	cout << "Enter the ingredient to remove: ";
	cin >> removeIng;
	removeIngredient(pantry, &numIngredients, removeIng);
	cout << "Saving to file..." << endl;
	saveToFile(pantry, numIngredients, outfileName);
	for (int i = 0; i < numIngredients; ++i)
		delete[] pantry[i];
	delete[] pantry;
	delete[] infileName;
	delete[] outfileName;
	delete[] searchIng;
	delete[] addIng;
	delete[] replaceIng;

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
	++* numIngredients;
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
int changeIngredient(char** pStrs, int numIngredients, char* oldIngredient, char* newIngredient) {
	for (int i = 0; i < numIngredients; i++) {
		if (!strcmp(pStrs[i], oldIngredient))
			strcpy_s(pStrs[i], strlen(pStrs[i])+1,newIngredient);
	}
	delete[] oldIngredient;
	return 0;
}
int removeIngredient(char** pStrs, int* numIngredients, char* removeIngredient) {
	bool remove = false;
	char* currIng = new char[INGSIZE];
	for (int i = 0; i < *numIngredients; i++) {
		strcpy_s(currIng, strlen(pStrs[i])+1, pStrs[i]);
		remove = !strcmp(pStrs[i], removeIngredient);
		if (remove) {
			strcpy_s(pStrs[i], strlen(pStrs[i])+1, pStrs[i+1]);
		}
	}
	if (remove)
		--*numIngredients;
	delete[] removeIngredient;
	delete[] currIng;
	return 0;
}
