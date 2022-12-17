//C���α׷��� ���� �����, �����, �ڽ���

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>


#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45
#define PTEROSAUR_BOTTOM_Y 11
#define PTEROSAUR_BOTTOM_X 45


//�ܼ�â�� ũ��� ������ �����ϴ� �Լ��� ���ÿ� Ŀ��ǥ�ø� ����� �Լ�
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Cprograming TeamProject.");
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

//Ŀ���� �ű�� �Լ�
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x; 
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//Ű�� �Է¹����� �׿� �´� �ƽ�Ű �ڵ带 ��ȯ�ϴ� �Լ�
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

//�÷��̾��� ������ �׸��� �Լ�
void Dino(int dinoY, bool crouching)
{
    GotoXY(0, dinoY);
    static bool legFlag = true;

    if (crouching == true)  //���帮�� �ִ� ��Ȳ�̶�� ���帮�� ������� �׸�
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
    else  //���ִ� ��Ȳ�̶�� ���ִ� ������� �׸�
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

//������ �׸��� �Լ�
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

//�ͷ��� �׸��� �Լ�
void Pterosaur(int pterosaurX)
{
    GotoXY(pterosaurX, PTEROSAUR_BOTTOM_Y);
    printf(" ##");
    GotoXY(pterosaurX, PTEROSAUR_BOTTOM_Y + 1);
    printf("####");
    GotoXY(pterosaurX, PTEROSAUR_BOTTOM_Y + 2);
    printf(" ##");
}

//���ӿ��� 
void GameOver(const int score)
{
    system("cls");
    int x = 18;
    int y = 5;
    GotoXY(x, y - 3);
    printf("                  SCORE : %d", score);
    GotoXY(x, y + 3);
    printf("�ˢˢˢˢˢˢˢˢˢˢˢˢˢ�");
    GotoXY(x, y + 4);
    printf("�ˢˢˢ�  ���ӿ���  �ˢˢˢ�");
    GotoXY(x, y + 5);
    printf("�ˢˢˢˢˢˢˢˢˢˢˢˢˢ�");


    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

//�浹�� �����ϴ� �Լ�
bool isCollision(int treeX, int dinoY, int pterosaurX, bool isCrouching, int changePut)
{
    if (isCrouching == true)
        dinoY = 6;

    GotoXY(0, 0);
    
    if (changePut == 0) //changePut�� 0�ϰ�� ������ ��ġ�� ǥ��
    {
        printf("treeX : %d, dinoY : %d", treeX, dinoY);
    }
    else if (changePut == 1) //changePut�� 1�ϰ�� �ͷ��� ��ġ�� ǥ��
    {
        printf("pterosaurX : %d, dinoY : %d", pterosaurX, dinoY);
    }
     
    if (treeX <= 8 && treeX >= 4 && //������ ��ġ�� �÷��̾��� ��ġ�� �����߰� �����ϴ� ���°� �ƴϸ� ���� ����
        dinoY > 8)
    {
        return true;
    }
    if (pterosaurX <= 8 && pterosaurX >= 4 && //�ͷ��� ��ġ�� �÷��̾� ��ġ�� �����߰� ��ũ���� �ִ� ���°� �ƴϸ� ���� ����
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
        //���� ���۽� ���� ���� �ʱ�ȭ
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

            if (keyCode == 72 && isBottom) //���� ����Ű�� ������ ��� ����
            {
                isJumping = true;
                isBottom = false;
            }
            crouchCount -= 1;
            
            if (keyCode ==  80 && isBottom) //�Ʒ��� ����Ű�� ������ ��� ����
            {
                isCrouching = true;
                crouchCount = 8;
            }
            else if (crouchCount <= 0) //�Ʒ��� ����Ű�� �����ٰ� ���� ��õڿ� �ٽ� �Ͼ
            {
                isCrouching = false;
            }

            if (isJumping) //�����ϰ� �ִ� ��Ȳ�̸� ���� �÷��̾ �ø�
            {
                dinoY -= gravity;
            }
            else    //�� �ö󰡸� �ٽ� �������� ����
            {
                dinoY += gravity;
            }
           
            if (dinoY >= DINO_BOTTOM_Y) //��� �ٴ� ������ �������� ���� �����ϱ� ���� �ٴ��� ������
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            if (changePut == 0) //changePut�� 0�ϰ�쿡�� ������ ������
            {
                treeX -= trapMoveSpeed;
            }
            else if (changePut == 1) //changePut�� 1�ϰ�쿡�� �ͷ��� ������
            {
                pterosaurX -= trapMoveSpeed;
            }

            if (treeX <= 0) //������ ������ ���� changePut�� 1�� ����� �������� �ͷ��� ��ġ�Ǿ� ������ �� �ֵ��� ��
            {
                treeX = TREE_BOTTOM_X;
                changePut = 1;
            }

            if (pterosaurX <= 0) //�ͷ��� ������ ���� changePut�� 0���� ����� �������� ������ ��ġ�Ǿ� ������ �� �ֵ��� ��
            {
                pterosaurX = PTEROSAUR_BOTTOM_X;
                changePut = 0;
            }

            if (dinoY <= 3) //�����ؼ� �ö󰡴ٰ� �������� ������ ����
            {
                isJumping = false;
            }

            if (score == 15) //���ھ 15���� �����ϰ� �Ǹ�
                trapMoveSpeed = 3; //��ֹ����� �ӵ��� ���� ���� ���̵� ���

            Dino(dinoY, isCrouching);      
            if (changePut == 0) //������ ���鼭 ���� ��ֹ��� ���ƴٴϴ� �ͷ� ��ֹ��� ��ġ��
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
            Sleep(30); //�ݺ� ������
            system("cls");  //ȭ���� ���� �������� �ٽ� �׸� �� �ֵ��� ����
            GotoXY(22, 0);    
            printf("Score : %d ", score);    //���ھ� ǥ��
        }

        GameOver(score); //���� ������ ���� ���ھ� ǥ��
    }
    return 0;
}