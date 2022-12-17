//C프로그래밍 팀플 고득찬, 박재용, 박신형

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>


#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45
#define PTEROSAUR_BOTTOM_Y 11
#define PTEROSAUR_BOTTOM_X 45


//콘솔창의 크기와 제목을 지정하는 함수와 동시에 커서표시를 지우는 함수
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Cprograming TeamProject.");
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

//커서를 옮기는 함수
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x; 
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키를 입력받으면 그에 맞는 아스키 코드를 반환하는 함수
int GetKey()
{   
    if (_kbhit() != 0)
    {
        int key;
        key = _getch();
        if (key == 224)
        {
            key = _getch();
        }
        return key;
    }
    return 0;
}

//플레이어인 공룡을 그리는 함수
void Dino(int dinoY, bool crouching)
{
    GotoXY(0, dinoY);
    static bool legFlag = true;

    if (crouching == true)  //업드리고 있는 상황이라면 업드리는 모양으로 그림
    {
        printf("                \n");
        printf("                \n");
        printf("                \n");
        printf("                \n");
        printf("         ###### \n");
        printf("#####   ### ####\n");
        printf("####  ########  \n");
        printf(" ##  ########   \n");
        printf(" $############# \n");
        printf("    #######     \n");
        printf("     ######     \n");
    }
    else  //서있는 상황이라면 서있는 모양으로 그림
    {
        printf("        ####### \n");
        printf("       ## ######\n");
        printf("#      #######  \n");
        printf("##     ###      \n");
        printf("##     ####     \n");
        printf("##    #####     \n");
        printf(" ##  ########## \n");
        printf(" $##########    \n");
        printf("   #########    \n");
        printf("    #######     \n");
        printf("     ######     \n");
    }

    if (legFlag)
    {
        printf("    #     #    \n");
        printf("   ##     ##       ");
        legFlag = false;
    }
    else
    {
        printf("     #  #    \n");
        printf("    ##  ##       ");
        legFlag = true;
    }
}

//나무를 그리는 함수
void Tree(int treeX)
{
    GotoXY(treeX, TREE_BOTTOM_Y);
    printf("#");
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    printf("### ");
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    printf(" ## ");
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    printf("###");
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    printf("## ");
}

//익룡을 그리는 함수
void Pterosaur(int pterosaurX)
{
    GotoXY(pterosaurX, PTEROSAUR_BOTTOM_Y);
    printf(" ##");
    GotoXY(pterosaurX, PTEROSAUR_BOTTOM_Y + 1);
    printf("####");
    GotoXY(pterosaurX, PTEROSAUR_BOTTOM_Y + 2);
    printf(" ##");
}

//게임오버 
void GameOver(const int score)
{
    system("cls");
    int x = 18;
    int y = 5;
    GotoXY(x, y - 3);
    printf("                  SCORE : %d", score);
    GotoXY(x, y + 3);
    printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦");
    GotoXY(x, y + 4);
    printf("▦▦▦▦  게임오버  ▦▦▦▦");
    GotoXY(x, y + 5);
    printf("▦▦▦▦▦▦▦▦▦▦▦▦▦▦");


    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

//충돌을 감지하는 함수
bool isCollision(int treeX, int dinoY, int pterosaurX, bool isCrouching, int changePut)
{
    if (isCrouching == true)
        dinoY = 6;

    GotoXY(0, 0);
    
    if (changePut == 0) //changePut이 0일경우 나무의 위치를 표시
    {
        printf("treeX : %d, dinoY : %d", treeX, dinoY);
    }
    else if (changePut == 1) //changePut이 1일경우 익룡의 위치를 표시
    {
        printf("pterosaurX : %d, dinoY : %d", pterosaurX, dinoY);
    }
     
    if (treeX <= 8 && treeX >= 4 && //나무의 위치가 플레이어의 위치에 도달했고 점프하는 상태가 아니면 게임 오버
        dinoY > 8)
    {
        return true;
    }
    if (pterosaurX <= 8 && pterosaurX >= 4 && //익룡의 위치가 플레이어 위치에 도달했고 웅크리고 있는 상태가 아니면 게임 오버
        isCrouching == false)
    {
        return true;
    }

    return false;
}

int main() 
{
    SetConsoleView();

    while (true)        
    {
        //게임 시작시 각종 값들 초기화
        bool isCrouching = false;
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 2;

        int changePut = 0;
        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;
        int pterosaurX = PTEROSAUR_BOTTOM_X;

        int trapMoveSpeed = 2;
        int crouchCount = 0;
        int keyCode = 0;
        int score = 0;
        clock_t start, curr;    
        start = clock();        

        while (true)    
        {

            if (isCollision(treeX, dinoY, pterosaurX, isCrouching, changePut))
                break;

            keyCode = GetKey();

            if (keyCode == 72 && isBottom) //위쪽 방향키를 눌렀을 경우 점프
            {
                isJumping = true;
                isBottom = false;
            }
            crouchCount -= 1;
            
            if (keyCode ==  80 && isBottom) //아래쪽 방향키를 눌렀을 경우 숙임
            {
                isCrouching = true;
                crouchCount = 8;
            }
            else if (crouchCount <= 0) //아래쪽 방향키를 누르다가 때면 잠시뒤에 다시 일어남
            {
                isCrouching = false;
            }

            if (isJumping) //점프하고 있는 상황이면 위로 플레이어를 올림
            {
                dinoY -= gravity;
            }
            else    //다 올라가면 다시 내려오게 만듦
            {
                dinoY += gravity;
            }
           
            if (dinoY >= DINO_BOTTOM_Y) //계속 바닥 밑으로 내려가는 것을 방지하기 위해 바닥을 지정함
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            if (changePut == 0) //changePut이 0일경우에는 나무를 움직임
            {
                treeX -= trapMoveSpeed;
            }
            else if (changePut == 1) //changePut이 1일경우에는 익룡을 움직임
            {
                pterosaurX -= trapMoveSpeed;
            }

            if (treeX <= 0) //나무가 끝까지 가면 changePut을 1로 만들어 다음에는 익룡이 배치되어 움직일 수 있도록 함
            {
                treeX = TREE_BOTTOM_X;
                changePut = 1;
            }

            if (pterosaurX <= 0) //익룡이 끝까지 가면 changePut을 0으로 만들어 다음에는 나무가 배치되어 움직일 수 있도록 함
            {
                pterosaurX = PTEROSAUR_BOTTOM_X;
                changePut = 0;
            }

            if (dinoY <= 3) //점프해서 올라가다가 내려가는 지점을 지정
            {
                isJumping = false;
            }

            if (score == 15) //스코어가 15점에 도달하게 되면
                trapMoveSpeed = 3; //장애물들의 속도를 높여 게임 난이도 상승

            Dino(dinoY, isCrouching);      
            if (changePut == 0) //번갈아 가면서 나무 장애물과 날아다니는 익룡 장애물을 배치함
            {
                Tree(treeX);
            }
            else if (changePut == 1)
            {
                Pterosaur(pterosaurX);
            }
            
            curr = clock();            
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)    
            {
                score++;   
                start = clock();
            }
            Sleep(30); //반복 딜레이
            system("cls");  //화면을 전부 다지워서 다시 그릴 수 있도록 만듦
            GotoXY(22, 0);    
            printf("Score : %d ", score);    //스코어 표시
        }

        GameOver(score); //게임 오버후 최종 스코어 표시
    }
    return 0;
}