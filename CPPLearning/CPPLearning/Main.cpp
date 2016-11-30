#include <stdio.h>


int main(int length, char* args[]) {
	for (int i = 0; i < length; i++) {
		printf(args[i]);
	}
	return 0;
}