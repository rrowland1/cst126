#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;
using std::string;
using std::endl;

struct AuthorStats {
	char fname[16];
	char lname[16];
	float avgwordlength;
	float typetokratio;
	float hapaxlegomana;
};
int loadAuthorStats(AuthorStats** authorInfo, int* numAuthors) {
	ifstream fin;
	char authorfile[20] = "authorstats.txt";
	fin.open(authorfile);
	if (fin.is_open()) {
		while (!fin.eof()) {
			authorInfo[*numAuthors] = new AuthorStats;
			fin >> authorInfo[*numAuthors]->fname;
			fin >> authorInfo[*numAuthors]->lname;
			fin >> authorInfo[*numAuthors]->avgwordlength;
			fin >> authorInfo[*numAuthors]->typetokratio;
			fin >> authorInfo[*numAuthors]->hapaxlegomana;
			++* numAuthors;
		}
	}
	return 0;
}

void fileanalyze(AuthorStats *currauthor, char filename[]) {
	ifstream fin;
	fin.open(filename);
	const int SIZE = 34;
	const int MAX = 10000;
	char** words = new char*[MAX];
	int wordscount[MAX] = {0};
	char word[SIZE];
	int NWindex = 0;
	float long averagelength = 0;
	int totalwords = 0;
	float hapaxlegomana = 0;
	float typetokrat;
	if (fin.is_open()) {
		while (!fin.eof()) {
			fin >> word;
			totalwords++;
			averagelength += strlen(word);
			for (int i = 0; i < strlen(word); i++) {
				word[i] = tolower(word[i]);
			}
			for (int i = 0; i <=NWindex; i++) {
				if (i == NWindex) {
					words[i] = new char[strlen(word) + 1];
					strcpy_s(words[i],strlen(word)+1, word);
					++wordscount[i]; NWindex++; break;
				}
				else if (strcmp(word, words[i]) == 0) {
					++wordscount[i]; break;
				}
			}
		}
	}
	fin.close();
	for (int i = 0; i < NWindex; i++) {
		if (wordscount[i] == 1) {
			hapaxlegomana++;
		}
	}
	typetokrat = ((float)NWindex / (float)totalwords);
	hapaxlegomana /= totalwords;
	averagelength /= totalwords;
	currauthor->hapaxlegomana = hapaxlegomana;
	currauthor->typetokratio = typetokrat;
	currauthor->avgwordlength = averagelength;
	for (int i = 0; i < NWindex; i++) {
		delete[] words[i];
	}
	delete[] words;
}
void compareauth(AuthorStats** authorInfo, int numAuthors, char file[20]) {
	AuthorStats* currauthor = new AuthorStats;
	float pastdiff;
	float currdiff;
	int similarauthindex = 0;
	for (int i = 0; i < numAuthors; i++) {
		fileanalyze(currauthor, file);
		pastdiff =
			abs(((currauthor->avgwordlength - authorInfo[i]->avgwordlength) * 11) +
			((currauthor->typetokratio - authorInfo[i]->typetokratio) * 33) +
			((currauthor->hapaxlegomana - authorInfo[i]->hapaxlegomana) * 50));
		if (i == 0)
			currdiff = pastdiff;
		else if (currdiff > pastdiff)
			similarauthindex = i;
		/*cout 
			<< authorInfo[i]->fname << " "
			<< authorInfo[i]->lname
			<< "'s score is: "
			<< pastdiff << endl;*/
	}
	cout
		<< "This text; " << file << " was most likely written by "
		<< authorInfo[similarauthindex]->fname << " "
		<< authorInfo[similarauthindex]->lname << endl;
	delete currauthor;
}
