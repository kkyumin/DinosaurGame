#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define DINOSAUR_DISTANCE_FROM_TOP_Y 12
#define TREE_DISTANCE_FROM_TOP_Y 20
#define TREE_DISTANCE_FROM_RIGHT_X 45

void InitConsoleConfig();
void GotoXY(int, int);
int GetKeyDown(void);
void DrawDinosaur(int);
void DrawTree(int);
void showScore(int);
int askRestart(void);

static int live =true;

int main(int argc, char* argv[]) {
	InitConsoleConfig();

	bool jumping =false;
	bool walking = true;
	static const int gravity = 3;

	int score = 0;
	int dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y;
	int treeX = TREE_DISTANCE_FROM_RIGHT_X;

	// 게임 Over Flag  true일경우 게임진행, fasle 일경우 게임 OVer 
		
	live =true;

	// 사용자가 Return 하지 않는한 계속 진행
	 
	while (true){
	
		if (32 == GetKeyDown() && walking) {
			jumping = true;
			walking = false;
		}
		if (jumping) {
			dinosaurY -= gravity;
		}
		else {
			dinosaurY += gravity;
		}
		if (dinosaurY<= 0) {
			jumping = false;
		}
		if (DINOSAUR_DISTANCE_FROM_TOP_Y <= dinosaurY) {
			dinosaurY = DINOSAUR_DISTANCE_FROM_TOP_Y;
			walking = true;
		}
		// live flag이 true인 이상 나무가 움직인다. 
		if(live){
			treeX -= 2;
		}
		// 무사히 tree가 공룡 위치를 넘기면, 스코어가 올라간다. 
		if (0 >= treeX) {
			treeX = TREE_DISTANCE_FROM_RIGHT_X;
			score += 10;
		}
		

		// 나무 위치가 공룡의 x위치+ 공룡의 가로크기 보다 작으면서, 공룡이 점프를 하지 않는다면, live =0 
		if (treeX < 6 && dinosaurY > 8) {
			live = 0;
		}

		DrawDinosaur(dinosaurY);
		DrawTree(treeX);
		showScore(score);
		
		// live 가 0이 되어서 게임Over가 되면 재시작 여부를 묻는다. 115번 라인 참조 yes 일 경우 다시 처음세팅으로, no일 경우 return 0를 통해 while문 탈출 
		if(!live){
			int answer= askRestart();
			if(answer == 0){
				treeX = TREE_DISTANCE_FROM_RIGHT_X;
				live = 1;
				score = 0;
			}
			else{
				return 0;
			}
		}
		Sleep(60);
		system("cls");		
	}
	return 0;
}

void GotoXY(int x,int y){
	COORD position;
	position.X = x * 2;
	position.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void InitConsoleConfig(void) {
	system("mode con:cols=100 lines=25");
}
int GetKeyDown() {
	if (0!= _kbhit()) {
		return _getch();
	}
	return 0;
}

int askRestart(void){
	GotoXY(20,5);
	printf("Wanna Restart? Press Y to Yes, N to No for the seconds");
	
	//Y y가 눌릴경우 0 반환 , N n가 눌릴경우 -1 반환.
	while(true){
	if(GetKeyDown() == 78 || GetKeyDown() == 110){
		return -1;
	}
	if( GetKeyDown() == 89 || GetKeyDown() == 121){
		return 0;
		}
	}
}

void DrawTree(int treeX) {
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y);
	printf("$  $");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y+1);
	printf("$$$$");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y+2);
	printf(" $$ ");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y+3);
	printf( " $$ ");
	GotoXY(treeX, TREE_DISTANCE_FROM_TOP_Y+4);
	printf(" $$ ");
}
void showScore(int score) {
	GotoXY(40,3);
	printf("Score : %d",score);
}

void DrawDinosaur(int dinosaurY) {
	static int legDraw = true;
	
	if(live){
	GotoXY(0, dinosaurY);
	printf("        &&&&&&&& \n");
	printf("       && &$&&&&\n");
	printf("       &&&&&&&&&\n");
	printf("&      &&&      \n");
	printf("&&     &&&&&&&& \n");
	printf("&&&   &&&&&     \n");
	printf(" &&  &&&&&&&&&& \n");
	printf(" &&&&&&&&&&&    \n");
	printf("  &&&&&&&&&&    \n");
	printf("    &&&&&&&&    \n");
	printf("     &&&&&&     \n");

	if (legDraw) {
		printf("     &    &&&     \n");
		printf("     &&           ");
		legDraw = false;
	}
	else {
		printf("     &&&  &       \n");
		printf("          &&      ");
		legDraw = true;
	}
	
	}
	///만약 live가 0이면 공룡 위치 조정 및 고정. 
	else{
	GotoXY(0, 0);
	printf("  Game Over      \n");		
	printf("        &&&&&&&& \n");
	printf("       &   &&&&&\n");
	printf("       & &&&&&&&\n");
	printf("&      &&&      \n");
	printf("&&     &&&&&&&& \n");
	printf("&&&   &&&&&     \n");
	printf(" &&  &&&&&&&&&& \n");
	printf(" &&&&&&&&&&&    \n");
	printf("  &&&&&&&&&&    \n");
	printf("    &&&&&&&&    \n");
	printf("     &&&&&&     \n");
	}

}
