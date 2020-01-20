/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int pV;
	first_setting();
	map_set();
	map_print();
	
	srand(time(NULL));
	
	while(1) {
		scanf("%d", &pV);
		getchar();
		player_move(pV);
	}
	
	system("pause");
	
	return 0;
}




