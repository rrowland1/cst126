#define _CRT_DBG_MAP_ALLOC
#include <iostream>
#include <fstream>
#include "lab3header.h"

using std::cout;
using std::cin;
void compareauth(AuthorStats** authorInfo, int numAuthors, char file[20]);
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	const int MAX = 100;
	int numauthors = 0;
	char file[6][20] = { 
		"mystery0.txt",
		"mystery1.txt",
		"mystery2.txt",
		"mystery3.txt",
		"mystery4.txt",
		"mystery5.txt" };
	AuthorStats** authorstats = new AuthorStats * [MAX];
	loadAuthorStats(authorstats, &numauthors);
	compareauth(authorstats, numauthors, file[0]);
	compareauth(authorstats, numauthors, file[1]);
	compareauth(authorstats, numauthors, file[2]);
	compareauth(authorstats, numauthors, file[3]);
	compareauth(authorstats, numauthors, file[4]);
	compareauth(authorstats, numauthors, file[5]);
	for (int i = 0; i < numauthors; i++) {
		delete[] authorstats[i];
	}
	delete[] authorstats;
	return 0;
}
