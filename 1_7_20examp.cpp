#pragma warning(disable:4996)
#include <iostream>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using std::cout;
using std::cin;
using std::strcat;

int main() {
	const int size = 5000;
	char fortnite[size] = "abcabcacbabacaca";
	int prev;
	int curr;
	char prevch;
	char currch;
	bool swapped=false;
	bool sorted = false;
	int count=0;
	cout << fortnite << "\n";
	while (!sorted) {
		count++;
		for (int i = 1; i <= size; i++) {
			if (i == size) {
				if (!swapped||count==20) {
					sorted = true;
				}
			}
			else {
				prev = fortnite[i - 1];
				curr = fortnite[i];
				prevch = prev;
				currch = curr;
				//cout << prevch << " " << currch << " " << i <<" " << swapped <<"\n";
				if (prev < curr) {
					fortnite[i - 1] = currch;
					fortnite[i] = prevch;
					swapped = true;
				}
			}
		}
	}
	cout << fortnite << "\n";
}
