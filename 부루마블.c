#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX_Y 45
#define MAX_X 45
#define RED SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), 12);
#define BLUE SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), 9);
#define GREEN SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), 10);
#define YELLOW SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), 14);
#define WHITE SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE), 7);
#define L 1 // LeftDown ( 왼쪽아래 ) 
#define U 2 // LeftUp ( 왼쪽 위 ) 
#define R 3 // RightDown ( 오른쪽 아래 ) 
#define D 4 // RightUp ( 오른쪽 위 ) 
#define TRUE 1
#define FALSE 0

int map[MAX_Y][MAX_X] = {0};

struct player_stat{
	int value;
	int pos_x;
	int pos_y;
}Player[4];
// 구조체로 각 플레이어 선언. 

void first_setting() {
	int i, temp_x, temp_y;
	for(i=0; i<4; i++) {
		Player[i].value=i+2;
		if(i==0) {
			temp_x=1;
			temp_y=43;
		}
		else if(i==1) temp_y=41;
		else if(i==2) temp_x=3;
		else if(i==3) temp_y=43;
		Player[i].pos_x=temp_x;
		Player[i].pos_y=temp_y;
	}
	
}
// 각 플레이어들 초반 좌표, 구분 값 설정 

void map_set() { 
	int i, j;
	map[43][1]=Player[0].value;
	map[41][1]=Player[1].value;
	map[41][3]=Player[2].value;
	map[43][3]=Player[3].value;
	for(i=0; i<MAX_Y; i++) {
		for(j=0; j<MAX_X; j++) {
			if(i==0 || i==MAX_Y-1 || i==4 || i==40) map[i][j]=1;	
			else if(i<4 || i>40) {
				if(j==0 || j==MAX_X-1 || j%4==0) map[i][j]=1;			
			}
			else if(i%4==0) {
				if(j<=4 || j>=40) map[i][j]=1;				
			}
			else {
				if((j==0 || j==MAX_X-1 || j==4 || j==40)) map[i][j]=1;			
			}	
		}		
	}
}
// 맵 틀 그리기
 
void map_print() {
	int i, j ,sw=0;	
	
	for(i=0; i<MAX_Y; i++) {
		for(j=0; j<MAX_X; j++) {
			switch(map[i][j]) {
				case 1: {
					WHITE;
					
					break;
				}
				case 2: {
					RED;
					
					break;
				}
				case 3: {
					BLUE;
					
					break;
				}
				case 4: {
					GREEN;
					
					break;
				}
				case 5: {
					YELLOW;
					
					break;
				}
				default: {
					sw=1;
					break;
				}
			}
			if(sw) {
				printf("  ");
				sw=0;	
			}
			else printf("■");
		}
		putchar('\n');
	}
}
// 각 플레이어 변수 등등 비교하여 맵을 그리기

int scan_dr(int x, int y) {
	if(x<4 && y>4) return L;
	else if(x<40 && y<4) return U;
	else if(x>40 && y>40) return D;
} 

void move_after(int pV) {
	map[Player[pV].pos_y][Player[pV].pos_x]=Player[pV].value;
}
void move_before(int pV, char xy, char updown) {
	if(xy=='x') {
		if(updown=='u') map[Player[pV].pos_y][Player[pV].pos_x-4]=0;
		else map[Player[pV].pos_y][Player[pV].pos_x+4]=0;
	}
	else {
		if(updown=='u') map[Player[pV].pos_y-4][Player[pV].pos_x]=0;
		else map[Player[pV].pos_y+4][Player[pV].pos_x]=0;
	}
}
void move(int pV, char xy, char updown) {
	move_after(pV);
	move_before(pV, xy, updown);
}

void player_move(int pV) {
	pV-=1;
	int movePoint;
	int x, y;
	int i;
	movePoint=1+rand()%6;
	
	
	
	for(i=0; i<movePoint; i++) {
		x=Player[pV].pos_x;
		y=Player[pV].pos_y;
		Sleep(500);
		system("cls");
		if(scan_dr(x, y)==L) 
		{
			Player[pV].pos_y-=4;
			move(pV, 'y', 'd');
		} 
		else if(scan_dr(x, y)==U) 
		{
			Player[pV].pos_x+=4;
			move(pV, 'x', 'u');
		}
		else if(scan_dr(x, y)==R) 
		{
			Player[pV].pos_y+=4;
			move(pV, 'y', 'u');		
		}
		else if(scan_dr(x, y)==D) 
		{
			Player[pV].pos_x-=4;
			move(pV, 'x', 'd');	
		}
		map_print();
	}
	

		
	
}
// 각 플레이어가 움직이게 하고 움직일 때마다 맵 변수 값 변경. 

int main() {
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



void gotoxy(int x,int y)
{

COORD pos={x,y};

SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 

}
