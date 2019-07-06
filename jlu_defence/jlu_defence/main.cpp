#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;/*不要忘了写这句话*/

#define HEIGHT  36
#define WIDTH  76

//char map[HEIGHT  * 20][WIDTH  * 20];
char map[HEIGHT * 20][WIDTH * 20];
int player_x = WIDTH * 2 - 4, player_y = HEIGHT;			//用（10*player_x, 10*player_y）做为玩家输出的坐标
int bomb_array[HEIGHT * 20][WIDTH * 20] = { 0 };					// 用于记录炸弹
int bomb_x = 0, bomb_y = 0;						//用（20*bomb_x, 20*bomb_y) 作为炸弹的坐标
int bullet_x, bullet_y;
int fire_x, fire_y;
int bombs = 1, bullets = 0, eyes = 0, carrys = 1, glass = 0, sharingan = 1,enemy_rebirth=1;
int face_x, face_y,dany_face_x,dany_face_y;
int direction;                                                                                                   //1: up	2:down	3:left	4:right
int forest_fire_direction;                                                                                //1: up	2:down	3:left	4:right
int player_life = 1, dany_life=1;							//人物生命
int dany_x, dany_y;			//用（10*player_x, 10*player_y）做为玩家输出的坐标
char move_player;
int flame_x, flame_y;
int eye_x, eye_y;
int carry_x, carry_y, carry_x_temp, carry_y_temp;
int player_face;
int win_fail = 0,generated=0;
clock_t start, finish=0;
int countdown = 60 * 7;

int enemy_1_life, enemy_2_life, enemy_3_life, enemy_4_life, enemy_5_life,
	enemy_6_life, enemy_7_life, enemy_8_life, enemy_9_life, enemy_10_life;
int enemy_1x, enemy_2x, enemy_3x, enemy_4x, enemy_5x, enemy_6x, enemy_7x, enemy_8x, enemy_9x, enemy_10x;					//用（10*enemy1_x, 10*enemy1_y) 作为enemy1的坐标
int enemy_1y, enemy_2y, enemy_3y, enemy_4y, enemy_5y, enemy_6y, enemy_7y, enemy_8y, enemy_9y, enemy_10y;				//用（10*enemy1_x, 10*enemy1_y) 作为enemy1的坐标
int direction_enemy_1, direction_enemy_2, direction_enemy_3, direction_enemy_4, direction_enemy_5, \
	direction_enemy_6, direction_enemy_7, direction_enemy_8, direction_enemy_9, direction_enemy_10;

double enemy_1_dead_time = 0, enemy_2_dead_time = 0, enemy_3_dead_time = 0, enemy_4_dead_time = 0, enemy_5_dead_time = 0;
double enemy_6_dead_time = 0, enemy_7_dead_time = 0, enemy_8_dead_time = 0, enemy_9_dead_time = 0, enemy_10_dead_time = 0;
double sharingan_sleep = 0;
double reborn_clock = 0;

int mapTemp1[HEIGHT ][WIDTH ], mapTemp2[HEIGHT ][WIDTH ];
int mapTemp3[HEIGHT ][WIDTH ], mapTemp4[HEIGHT ][WIDTH ];
int mapTemp5[HEIGHT ][WIDTH ], mapTemp6[HEIGHT ][WIDTH ];
int mapTemp7[HEIGHT ][WIDTH ], mapTemp8[HEIGHT ][WIDTH ];
int mapTemp9[HEIGHT ][WIDTH ], mapTemp10[HEIGHT ][WIDTH ];

int shortcut1[50],shortcut2[50];
int shortcut3[50],shortcut4[50];
int shortcut5[50],shortcut6[50];
int shortcut7[50],shortcut8[50];
int shortcut9[50],shortcut10[50];

DWORD sleep_enemy = 20;
DWORD _SLEEP_ENEMY = 20;
DWORD sleep_player = 30;
DWORD sleep_dany = 30;
DWORD sleep_bullet = 40;
DWORD dead_sleep = 15;

IMAGE background, stone, brick , brown , door, trees, water ,orange;		// 定义 IMAGE 对象
IMAGE player_s1, player_s2, player_s3, player_w1, player_w2, player_w3;
IMAGE player_a1, player_a2, player_a3, player_d1, player_d2, player_d3;					// 定义 IMAGE 对象
IMAGE bomb_burning1, bomb_burning2, bomb_burning3;
IMAGE bomb_mid_1, bomb_mid_2, bomb_mid_3, bomb_mid_4, bomb_mid_5;
IMAGE bomb_side_a_1, bomb_side_a_2, bomb_side_a_3, bomb_side_a_4, bomb_side_a_5;
IMAGE bomb_side_w_1, bomb_side_w_2, bomb_side_w_3, bomb_side_w_4, bomb_side_w_5;
IMAGE bomb_side_s_1, bomb_side_s_2, bomb_side_s_3, bomb_side_s_4, bomb_side_s_5;
IMAGE bomb_side_d_1, bomb_side_d_2, bomb_side_d_3, bomb_side_d_4, bomb_side_d_5;
IMAGE dany_s1, dany_s2, dany_s3, dany_w1, dany_w2, dany_w3;
IMAGE dany_a1, dany_a2, dany_a3, dany_d1, dany_d2, dany_d3;
IMAGE enemy_s1, enemy_s2, enemy_s3,enemy_w1, enemy_w2, enemy_w3;
IMAGE enemy_a1, enemy_a2, enemy_a3, enemy_d1, enemy_d2, enemy_d3;
IMAGE flame1,flame2,flame3;
IMAGE jlu, physics,daenerys,edward;
IMAGE eye1,eye2,eye3,eye4;

//建立5个子线程
static HANDLE hthread1;			//用于显示炸弹的爆炸	
static HANDLE hthread2;			//用于显示第一个敌人的移动
static HANDLE hthread3;			//用于显示第二个敌人的移动
static HANDLE hthread4;			//用于显示第二个敌人的移动
static HANDLE hthread5;			//用于显示第二个敌人的移动
static HANDLE hthread6;			//用于显示第二个敌人的移动
static HANDLE hthread7;			//用于显示第二个敌人的移动
static HANDLE hthread8;			//用于显示第二个敌人的移动
static HANDLE hthread9;			//用于显示第二个敌人的移动
static HANDLE hthread10;		//用于显示第二个敌人的移动
static HANDLE hthread11;		//用于显示第二个敌人的移动
static HANDLE hthread12;     //used to display the move of the bullet
static HANDLE hthread13;      //to show the forest being fired
static HANDLE hthread14;      //to show dany
static HANDLE hthread15;      //to show flame
static HANDLE hthread16;      //to show eye
static HANDLE hthread17;	  //to show brick_power
static HANDLE hthread18;      //to show eyes
static HANDLE hthread19;      //to show countDown

DWORD ThreadID = NULL;

////////////////////////// coded by Zilong Yuan///////////////////////////////
/*
#include <stdio.h>
#define MAX_ROW 40
#define MAX_COL 10//地图尺寸
int player_x = 9, player_y = 28;
int enemy_x = 2, enemy_y = 28;
注意:
1.该算法会修改数组地图,故需要单独提供实况地图
2.由于结果输出是从终点开始,故须将终点坐标设置为al起始坐标,起点为玩家坐标
3.地图大小为60*35,故最多有1820个点入列,结构体的长度足够
4.由于加上需拷贝方向到数组,运行一次大概需要9-10s左右的时间(但相同或类似地图的运行速度会快很多)
5.有任何其他问题自己debug即可,也可用我写好的printf打印结果查看
6.结果数组直接调用即可
*/

struct point { int row, col, predecessor; } queue[204800];//结构体数组(长度为2048个结构体之和)
int head = 0, tail = 0;//队列前的序号(即结构体数组的编号)
void enqueue(struct point p,point* queueTemp)
{
	queueTemp[tail++] = p;//将p编入结构体数组尾巴的最后
}
struct point dequeue(point* queueTemp)
{
	return queueTemp[head++];//跳到结构体数组队列编号的下一个结构点
}
int queueisempty(void)
{
	return head == tail;//判断结构体数组是否为空
}
/*
void initializeMapTemp(int** mapTemp)
{
	for (int i = 0; i < HEIGHT ; i++)
	{
		for (int j = 0; j < WIDTH ; j++)
		{
			if (map[i * 20][j * 20] == 0)
				*(*(mapTemp + i) + j) = 0;
			else
				*(*(mapTemp + i) + j) = 1;
		}
	}
}
*/

void visit(int row, int col, int mapTemp[HEIGHT ][WIDTH ],point* queueTemp)//
{
	struct point visit_point = { row, col, head - 1 };
	//mapTemp[row][col] = 2;
	*(*(mapTemp + row) + col) = 2;//标记此寻访点(该点不再能被行走)
	enqueue(visit_point,queueTemp);//将寻访点入列
}
void findShortCut(int enemy_x, int enemy_y,int position_x,int position_y,int mapTemp[HEIGHT ][WIDTH ], int* shortcut)
{
	//int mapTemp[HEIGHT ][WIDTH ];
	//initializeMapTemp(mapTemp);
	point* queueTemp;
	queueTemp = (point*)malloc(sizeof(point) * 204800);
	queueTemp = &queue[0];//结构体数组(长度为2048个结构体之和)

	for (int i = 0; i < HEIGHT ; i++)
	{
		for (int j = 0; j < WIDTH ; j++)
		{
			if (map[i * 20][j * 20] == '0')
				*(*(mapTemp + i) + j) = 0;
			else
				*(*(mapTemp + i) + j) = 1;
		}
	}

	struct point p = { position_y/2, position_x /2, -1 };//起点坐标设置处(-1为起点的特殊标记),player
	mapTemp[p.row][p.col] = 2;//标记起点坐标(该点不再能被行走)
	enqueue(p,queueTemp);//入队

	while (!queueisempty())
	{
		p = dequeue(queueTemp);
		if (p.row == enemy_y/2 /* 判断p是否寻到终点 */
			&& p.col == enemy_x/2)//ai
			break;//找到终点就跳出循环(此时p储存的坐标为终点坐标)
		if (p.col + 1 < WIDTH  /* right */
			&& (mapTemp)[p.row][p.col + 1] == 0)
			visit(p.row, p.col + 1, mapTemp,queueTemp);//将p右边的节点标记并加入队列
		if (p.row+1 < HEIGHT * 20/20 /* down */
			&& (mapTemp)[p.row + 1][p.col] == 0)
			visit(p.row + 1, p.col, mapTemp, queueTemp);
		if (p.col-1 >= 0 /* left */
			&& (mapTemp)[p.row][p.col - 1] == 0)
			visit(p.row, p.col - 1, mapTemp, queueTemp);
		if (p.row-1 >= 0 /* up */
			&& (mapTemp)[p.row - 1][p.col] == 0)
			visit(p.row - 1, p.col, mapTemp, queueTemp);
	}
	if (p.row == enemy_y/2 && p.col == enemy_x/2)//判断p是否是终点
	{
		int i;
		int  ROWS[55], COLS[55];
		ROWS[0] = p.row;
		COLS[0] = p.col;//拷贝终点坐标
		//printf("(%d, %d)\n", p.row, p.col);//测试

		//将最短路径坐标从终点开始拷贝54步至位置数组中
		for (i = 1; p.predecessor != -1 && i < 55; i++)
		{
			p = queueTemp[p.predecessor];//从p不断往回找上一个坐标的迭代
			ROWS[i] = p.row;
			COLS[i] = p.col;
			//printf("(%d, %d)\n", p.row, p.col);//测试
		}
		//将相邻位置数组的数值变换转换成从终点开始的50步行动方位(分别用0,1,2,3表示)并用shortcut记录
		for (i = 0; i < 50; i++)
		{
			if (ROWS[i + 1] - ROWS[i] == 1 && COLS[i + 1] - COLS[i] == 0)
				*(shortcut + i) = 0;//down

			else if (ROWS[i + 1] - ROWS[i] == -1 && COLS[i + 1] - COLS[i] == 0)
				*(shortcut + i) = 1;//up

			else if (ROWS[i + 1] - ROWS[i] == 0 && COLS[i + 1] - COLS[i] == -1)
				*(shortcut + i) = 2;//left

			else if (ROWS[i + 1] - ROWS[i] == 0 && COLS[i + 1] - COLS[i] == 1)
				*(shortcut + i) = 3;//right
			else
				*(shortcut + i) = -1;//小于50步时把数组中剩余位置赋成-1
		}
		//return 1;//主函数返回值
	}
	else
	{
		for (int i = 0; i < 50; i++)
			*(shortcut + i) = -1;
		//printf("No way!\n");//测试
		//return 0;//主函数返回值
	}
	//free(queueTemp);
	head = 0, tail = 0;//重置头尾，以便重新寻找路径
	/*
	for (int i = 0; i < 50; i++)
	{
		printf("%d\n", shortcut[i]);//测试
	}
	*/
	return;
}
//////////////////////////////////////////////////////////////////////////////

DWORD _stdcall enemy1_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_1x * 10, enemy_1y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_1x * 10, enemy_1y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_1x * 10, enemy_1y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_1x * 10, enemy_1y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_1_life&& (player_life+dany_life))
	{
		srand((unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_1x, enemy_1y, player_x,player_y,mapTemp1, shortcut1);

		for (int step = 0;(player_life+dany_life) && enemy_1_life && step < 20; step++)
		{
			if (shortcut1[step] == -1)
				direction_enemy_1 = rand() % 4;
			else
				direction_enemy_1 = shortcut1[step];

			for (int i = 1; i <= 2&& enemy_1_life; i++)
			{
				switch (direction_enemy_1)
				{
				case 0:
					if (map[enemy_1y * 10 + 20][enemy_1x * 10] == '-' || 
						map[enemy_1y * 10 + 20][enemy_1x * 10] == '0' && 
						map[enemy_1y * 10 + 20][enemy_1x * 10 - 10] == '0'&& 
						map[enemy_1y * 10 + 20][enemy_1x * 10 + 10] == '0'||
						(map[enemy_1y * 10 + 20][enemy_1x * 10] == '9' || 
						map[enemy_1y * 10 + 20][enemy_1x * 10 - 10] == '9' ||
						map[enemy_1y * 10 + 20][enemy_1x * 10 + 10] == '9'))										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_1y++;
						putimage(enemy_1x * 10, enemy_1y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_1_life)
						return 0;
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_1y * 10 - 20][enemy_1x * 10] == '9' ||
						map[enemy_1y * 10 - 20][enemy_1x * 10 - 10] == '9' ||
						map[enemy_1y * 10 - 20][enemy_1x * 10 + 10] == '9')||
						map[enemy_1y * 10 - 20][enemy_1x * 10] == '0' && 
						map[enemy_1y * 10 - 20][enemy_1x * 10 - 10] == '0' && 
						map[enemy_1y * 10 - 20][enemy_1x * 10 + 10] == '0' || 
						map[enemy_1y * 10 - 20][enemy_1x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_1y--;
						putimage(enemy_1x * 10, enemy_1y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_1_life)
						return 0;
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_1x > 0 &&
						(map[enemy_1y * 10][enemy_1x * 10 - 20] == '-' ||
						map[enemy_1y * 10][enemy_1x * 10 - 20] == '0' &&
						map[enemy_1y * 10 + 10][enemy_1x * 10 - 20] == '0' &&
						map[enemy_1y * 10 - 10][enemy_1x * 10 - 20] == '0' ||
						map[enemy_1y * 10][enemy_1x * 10 - 20] == '9' ||
						map[enemy_1y * 10 + 10][enemy_1x * 10 - 20] == '9' ||
						map[enemy_1y * 10 - 10][enemy_1x * 10 - 20] == '9'))										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_1x--;
						putimage(enemy_1x * 10 + 10, enemy_1y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_1_life)
						return 0;
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_1y * 10][enemy_1x * 10 + 20] == '9' ||
						map[enemy_1y * 10 + 10][enemy_1x * 10 + 20] == '9' ||
						map[enemy_1y * 10 - 10][enemy_1x * 10 + 20] == '9'||
						map[enemy_1y * 10][enemy_1x * 10 + 20] == '-' || 
						enemy_1x/2<= WIDTH-1.5 &&
						map[enemy_1y * 10][enemy_1x * 10 + 20] == '0' && 
						map[enemy_1y * 10 + 10][enemy_1x * 10 + 20] == '0' && 
						map[enemy_1y * 10 - 10][enemy_1x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_1x++;
						putimage(enemy_1x * 10 - 10, enemy_1y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_1_life)
						return 0;
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_1x * 10, enemy_1y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
		//free(shortcut1);
	}
	return 0;
}
DWORD _stdcall enemy2_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_2x * 10, enemy_2y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_2x * 10, enemy_2y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_2x * 10, enemy_2y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_2x * 10, enemy_2y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_2_life&& (player_life+dany_life))
	{
		srand(1+direction_enemy_1+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_2x, enemy_2y, player_x, player_y, mapTemp2, shortcut2);

		for (int step = 0;  (player_life+dany_life)&&enemy_2_life && step < 20; step++)
		{
			if (shortcut2[step] == -1)
				direction_enemy_2 = rand() % 4;
			else
				direction_enemy_2 = shortcut2[step];

			for (int i = 1; i <= 2&& enemy_2_life; i++)
			{
				switch (direction_enemy_2)
				{
				case 0:
					if (map[enemy_2y * 10 + 20][enemy_2x * 10] == '-' ||
					(map[enemy_2y * 10 + 20][enemy_2x * 10] == '9' ||
					map[enemy_2y * 10 + 20][enemy_2x * 10 - 10] == '9' ||
					map[enemy_2y * 10 + 20][enemy_2x * 10 + 10] == '9') ||
					map[enemy_2y * 10 + 20][enemy_2x * 10] == '0' && map[enemy_2y * 10 + 20][enemy_2x * 10 - 10] == '0' && map[enemy_2y * 10 + 20][enemy_2x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_2y++;
						putimage(enemy_2x * 10, enemy_2y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_2_life)
						return 0;
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_2y * 10 - 20][enemy_2x * 10] == '9' ||
						map[enemy_2y * 10 - 20][enemy_2x * 10 - 10] == '9' ||
						map[enemy_2y * 10 - 20][enemy_2x * 10 + 10] == '9') || 
						map[enemy_2y * 10 - 20][enemy_2x * 10] == '0' && map[enemy_2y * 10 - 20][enemy_2x * 10 - 10] == '0' && map[enemy_2y * 10 - 20][enemy_2x * 10 + 10] == '0' || map[enemy_2y * 10 - 20][enemy_2x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_2y--;
						putimage(enemy_2x * 10, enemy_2y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_2_life)
						return 0;
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_2x > 0 &&
						(map[enemy_2y * 10][enemy_2x * 10 - 20] == '9' ||
						map[enemy_2y * 10 + 10][enemy_2x * 10 - 20] == '9' ||
						map[enemy_2y * 10 - 10][enemy_2x * 10 - 20] == '9' || 
						map[enemy_2y * 10][enemy_2x * 10 - 20] == '-' || map[enemy_2y * 10][enemy_2x * 10 - 20] == '0' && map[enemy_2y * 10 + 10][enemy_2x * 10 - 20] == '0' && map[enemy_2y * 10 - 10][enemy_2x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_2x--;
						putimage(enemy_2x * 10 + 10, enemy_2y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_2_life)
						return 0;
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_2y * 10][enemy_2x * 10 + 20] == '9' ||
						map[enemy_2y * 10 + 10][enemy_2x * 10 + 20] == '9' ||
						map[enemy_2y * 10 - 10][enemy_2x * 10 + 20] == '9' || 
						map[enemy_2y * 10][enemy_2x * 10 + 20] == '-' ||
						enemy_2x / 2 <= WIDTH-1.5 && 
						map[enemy_2y * 10][enemy_2x * 10 + 20] == '0' && 
						map[enemy_2y * 10 + 10][enemy_2x * 10 + 20] == '0' && 
						map[enemy_2y * 10 - 10][enemy_2x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_2x++;
						putimage(enemy_2x * 10 - 10, enemy_2y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_2_life)
						return 0;
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_2x * 10, enemy_2y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy3_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_3x * 10, enemy_3y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_3x * 10, enemy_3y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_3x * 10, enemy_3y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_3x * 10, enemy_3y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_3_life&& (player_life+dany_life))
	{
		srand(2+direction_enemy_2+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_3x, enemy_3y, player_x, player_y, mapTemp3, shortcut3);

		for (int step = 0; (player_life+dany_life)&&enemy_3_life && step < 20; step++)
		{
			if (shortcut3[step] == -1)
				direction_enemy_3 = rand() % 4;
			else
				direction_enemy_3 = shortcut3[step];

			for (int i = 1; i <= 2&& enemy_3_life; i++)
			{
				switch (direction_enemy_3)
				{
				case 0:
					if ((map[enemy_3y * 10 + 20][enemy_3x * 10] == '9' ||map[enemy_3y * 10 + 20][enemy_3x * 10 - 10] == '9' || map[enemy_3y * 10 + 20][enemy_3x * 10 + 10] == '9')||map[enemy_3y * 10 + 20][enemy_3x * 10] == '-' || map[enemy_3y * 10 + 20][enemy_3x * 10] == '0' && map[enemy_3y * 10 + 20][enemy_3x * 10 - 10] == '0' && map[enemy_3y * 10 + 20][enemy_3x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_3y++;
						putimage(enemy_3x * 10, enemy_3y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_3_life)
						return 0;
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_3y * 10 - 20][enemy_3x * 10] == '9' ||
						map[enemy_3y * 10 - 20][enemy_3x * 10 - 10] == '9' ||
						map[enemy_3y * 10 - 20][enemy_3x * 10 + 10] == '9') || 
						map[enemy_3y * 10 - 20][enemy_3x * 10] == '0' && map[enemy_3y * 10 - 20][enemy_3x * 10 - 10] == '0' && map[enemy_3y * 10 - 20][enemy_3x * 10 + 10] == '0' || map[enemy_3y * 10 - 20][enemy_3x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_3y--;
						putimage(enemy_3x * 10, enemy_3y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_3_life)
						return 0;
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_3x > 0 &&
						(map[enemy_3y * 10][enemy_3x * 10 - 20] == '9' ||
						map[enemy_3y * 10 + 10][enemy_3x * 10 - 20] == '9' ||
						map[enemy_3y * 10 - 10][enemy_3x * 10 - 20] == '9' || 
						map[enemy_3y * 10][enemy_3x * 10 - 20] == '-' || map[enemy_3y * 10][enemy_3x * 10 - 20] == '0' && map[enemy_3y * 10 + 10][enemy_3x * 10 - 20] == '0' && map[enemy_3y * 10 - 10][enemy_3x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_3x--;
						putimage(enemy_3x * 10 + 10, enemy_3y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_3_life)
						return 0;
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_3y * 10][enemy_3x * 10 + 20] == '9' ||
						map[enemy_3y * 10 + 10][enemy_3x * 10 + 20] == '9' ||
						map[enemy_3y * 10 - 10][enemy_3x * 10 + 20] == '9' ||
						map[enemy_3y * 10][enemy_3x * 10 + 20] == '-' ||
						enemy_3x / 2 <= WIDTH-1.5 && 
						map[enemy_3y * 10][enemy_3x * 10 + 20] == '0' && 
						map[enemy_3y * 10 + 10][enemy_3x * 10 + 20] == '0' && 
						map[enemy_3y * 10 - 10][enemy_3x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_3x++;
						putimage(enemy_3x * 10 - 10, enemy_3y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_3_life)
						return 0;
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_3x * 10, enemy_3y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy4_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_4x * 10, enemy_4y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_4x * 10, enemy_4y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_4x * 10, enemy_4y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_4x * 10, enemy_4y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_4_life&& (player_life+dany_life))
	{
		srand(3+direction_enemy_3+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_4x, enemy_4y, player_x, player_y, mapTemp4, shortcut4);

		for (int step = 0;  (player_life+dany_life)&&enemy_4_life && step < 20; step++)
		{
			if (shortcut4[step] == -1)
				direction_enemy_4 = rand() % 4;
			else
				direction_enemy_4 = shortcut4[step];

			for (int i = 1; i <= 2 && enemy_4_life; i++)
			{
				switch (direction_enemy_4)
				{
				case 0:
					if ((map[enemy_4y * 10 + 20][enemy_4x * 10] == '9' ||map[enemy_4y * 10 + 20][enemy_4x * 10 - 10] == '9' || map[enemy_4y * 10 + 20][enemy_4x * 10 + 10] == '9') || map[enemy_4y * 10 + 20][enemy_4x * 10] == '-' || map[enemy_4y * 10 + 20][enemy_4x * 10] == '0' && map[enemy_4y * 10 + 20][enemy_4x * 10 - 10] == '0' && map[enemy_4y * 10 + 20][enemy_4x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_4y++;
						putimage(enemy_4x * 10, enemy_4y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_4_life)
						return 0;
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_4y * 10 - 20][enemy_4x * 10] == '9' ||
						map[enemy_4y * 10 - 20][enemy_4x * 10 - 10] == '9' ||
						map[enemy_4y * 10 - 20][enemy_4x * 10 + 10] == '9') || 
						map[enemy_4y * 10 - 20][enemy_4x * 10] == '0' && map[enemy_4y * 10 - 20][enemy_4x * 10 - 10] == '0' && map[enemy_4y * 10 - 20][enemy_4x * 10 + 10] == '0' || map[enemy_4y * 10 - 20][enemy_4x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_4y--;
						putimage(enemy_4x * 10, enemy_4y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_4_life)
						return 0;
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_4x > 0 &&
						(map[enemy_4y * 10][enemy_4x * 10 - 20] == '9' ||
						map[enemy_4y * 10 + 10][enemy_4x * 10 - 20] == '9' ||
						map[enemy_4y * 10 - 10][enemy_4x * 10 - 20] == '9' || 
						map[enemy_4y * 10][enemy_4x * 10 - 20] == '-' || map[enemy_4y * 10][enemy_4x * 10 - 20] == '0' && map[enemy_4y * 10 + 10][enemy_4x * 10 - 20] == '0' && map[enemy_4y * 10 - 10][enemy_4x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_4x--;
						putimage(enemy_4x * 10 + 10, enemy_4y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_4_life)
						return 0;
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_4y * 10][enemy_4x * 10 + 20] == '9' ||
						map[enemy_4y * 10 + 10][enemy_4x * 10 + 20] == '9' ||
						map[enemy_4y * 10 - 10][enemy_4x * 10 + 20] == '9' ||
						map[enemy_4y * 10][enemy_4x * 10 + 20] == '-' ||
						enemy_4x / 2 <= WIDTH-1.5 &&
						map[enemy_4y * 10][enemy_4x * 10 + 20] == '0' && 
						map[enemy_4y * 10 + 10][enemy_4x * 10 + 20] == '0' && 
						map[enemy_4y * 10 - 10][enemy_4x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_4x++;
						putimage(enemy_4x * 10 - 10, enemy_4y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_4_life)
						return 0;
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_4x * 10, enemy_4y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy5_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_5x * 10, enemy_5y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_5x * 10, enemy_5y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_5x * 10, enemy_5y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_5x * 10, enemy_5y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_5_life&& (player_life+dany_life))
	{
		srand(4+direction_enemy_4+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_5x, enemy_5y, player_x, player_y, mapTemp5, shortcut5);

		for (int step = 0;  (player_life+dany_life)&&enemy_5_life && step < 20; step++)
		{
			if (shortcut5[step] == -1)
				direction_enemy_5 = rand() % 4;
			else
				direction_enemy_5 = shortcut5[step];

			for (int i = 1; i <= 2 && enemy_5_life; i++)
			{
				switch (direction_enemy_5)
				{
				case 0:
					if ((map[enemy_5y * 10 + 20][enemy_5x * 10] == '9' ||map[enemy_5y * 10 + 20][enemy_5x * 10 - 10] == '9' || map[enemy_5y * 10 + 20][enemy_5x * 10 + 10] == '9') || map[enemy_5y * 10 + 20][enemy_5x * 10] == '-' || map[enemy_5y * 10 + 20][enemy_5x * 10] == '0' && map[enemy_5y * 10 + 20][enemy_5x * 10 - 10] == '0' && map[enemy_5y * 10 + 20][enemy_5x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_5y++;
						putimage(enemy_5x * 10, enemy_5y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_5_life)
						return 0;
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_5y * 10 - 20][enemy_5x * 10] == '9' ||
						map[enemy_5y * 10 - 20][enemy_5x * 10 - 10] == '9' ||
						map[enemy_5y * 10 - 20][enemy_5x * 10 + 10] == '9') || map[enemy_5y * 10 - 20][enemy_5x * 10] == '0' && map[enemy_5y * 10 - 20][enemy_5x * 10 - 10] == '0' && map[enemy_5y * 10 - 20][enemy_5x * 10 + 10] == '0' || map[enemy_5y * 10 - 20][enemy_5x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_5y--;
						putimage(enemy_5x * 10, enemy_5y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_5_life)
						return 0;
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_5x > 0 &&
						(map[enemy_5y * 10][enemy_5x * 10 - 20] == '9' ||
						map[enemy_5y * 10 + 10][enemy_5x * 10 - 20] == '9' ||
						map[enemy_5y * 10 - 10][enemy_5x * 10 - 20] == '9' || 
						map[enemy_5y * 10][enemy_5x * 10 - 20] == '-' || map[enemy_5y * 10][enemy_5x * 10 - 20] == '0' && map[enemy_5y * 10 + 10][enemy_5x * 10 - 20] == '0' && map[enemy_5y * 10 - 10][enemy_5x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_5x--;
						putimage(enemy_5x * 10 + 10, enemy_5y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_5_life)
						return 0;
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_5y * 10][enemy_5x * 10 + 20] == '9' ||
						map[enemy_5y * 10 + 10][enemy_5x * 10 + 20] == '9' ||
						map[enemy_5y * 10 - 10][enemy_5x * 10 + 20] == '9' ||
						map[enemy_5y * 10][enemy_5x * 10 + 20] == '-' ||
						enemy_5x / 2 <= WIDTH-1.5 && 
						map[enemy_5y * 10][enemy_5x * 10 + 20] == '0' && 
						map[enemy_5y * 10 + 10][enemy_5x * 10 + 20] == '0' && 
						map[enemy_5y * 10 - 10][enemy_5x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_5x++;
						putimage(enemy_5x * 10 - 10, enemy_5y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_5_life)
						return 0;
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_5x * 10, enemy_5y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy6_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_6x * 10, enemy_6y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_6x * 10, enemy_6y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_6x * 10, enemy_6y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_6x * 10, enemy_6y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_6_life&& (player_life+dany_life))
	{
		srand(5+direction_enemy_5+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_6x, enemy_6y, dany_x, dany_y, mapTemp6, shortcut6);

		for (int step = 0;  (player_life+dany_life)&&enemy_6_life && step < 20; step++)
		{
			if (shortcut6[step] == -1)
				direction_enemy_6 = rand() % 4;
			else
				direction_enemy_6 = shortcut6[step];

			for (int i = 1; i <= 2 && enemy_6_life; i++)
			{
				switch (direction_enemy_6)
				{
				case 0:
					if ((map[enemy_6y * 10 + 20][enemy_6x * 10] == '9' ||map[enemy_6y * 10 + 20][enemy_6x * 10 - 10] == '9' || map[enemy_6y * 10 + 20][enemy_6x * 10 + 10] == '9') || map[enemy_6y * 10 + 20][enemy_6x * 10] == '-' || map[enemy_6y * 10 + 20][enemy_6x * 10] == '0' && map[enemy_6y * 10 + 20][enemy_6x * 10 - 10] == '0' && map[enemy_6y * 10 + 20][enemy_6x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_6y++;
						putimage(enemy_6x * 10, enemy_6y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_6_life)
						return 0;
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_6y * 10 - 20][enemy_6x * 10] == '9' ||
						map[enemy_6y * 10 - 20][enemy_6x * 10 - 10] == '9' ||
						map[enemy_6y * 10 - 20][enemy_6x * 10 + 10] == '9') || 
						map[enemy_6y * 10 - 20][enemy_6x * 10] == '0' && map[enemy_6y * 10 - 20][enemy_6x * 10 - 10] == '0' && map[enemy_6y * 10 - 20][enemy_6x * 10 + 10] == '0' || map[enemy_6y * 10 - 20][enemy_6x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_6y--;
						putimage(enemy_6x * 10, enemy_6y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_6_life)
						return 0;
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_6x > 0 &&
						(map[enemy_6y * 10][enemy_6x * 10 - 20] == '9' ||
						map[enemy_6y * 10 + 10][enemy_6x * 10 - 20] == '9' ||
						map[enemy_6y * 10 - 10][enemy_6x * 10 - 20] == '9' || 
						map[enemy_6y * 10][enemy_6x * 10 - 20] == '-' || map[enemy_6y * 10][enemy_6x * 10 - 20] == '0' && map[enemy_6y * 10 + 10][enemy_6x * 10 - 20] == '0' && map[enemy_6y * 10 - 10][enemy_6x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_6x--;
						putimage(enemy_6x * 10 + 10, enemy_6y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_6_life)
						return 0;
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_6y * 10][enemy_6x * 10 + 20] == '9' ||
						map[enemy_6y * 10 + 10][enemy_6x * 10 + 20] == '9' ||
						map[enemy_6y * 10 - 10][enemy_6x * 10 + 20] == '9' ||
						map[enemy_6y * 10][enemy_6x * 10 + 20] == '-' ||
						enemy_6x / 2 <= WIDTH-1.5 && 
						map[enemy_6y * 10][enemy_6x * 10 + 20] == '0' && 
						map[enemy_6y * 10 + 10][enemy_6x * 10 + 20] == '0' 
						&& map[enemy_6y * 10 - 10][enemy_6x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_6x++;
						putimage(enemy_6x * 10 - 10, enemy_6y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_6_life)
						return 0;
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_6x * 10, enemy_6y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy7_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_7x * 10, enemy_7y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_7x * 10, enemy_7y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_7x * 10, enemy_7y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_7x * 10, enemy_7y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_7_life&& (player_life+dany_life))
	{
		srand(6+direction_enemy_6+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_7x, enemy_7y, dany_x, dany_y, mapTemp7, shortcut7);

		for (int step = 0;  (player_life+dany_life)&&enemy_7_life && step < 20; step++)
		{
			if (shortcut7[step] == -1)
				direction_enemy_7 = rand() % 4;
			else
				direction_enemy_7 = shortcut7[step];

			for (int i = 1; i <= 2 && enemy_7_life; i++)
			{
				switch (direction_enemy_7)
				{
				case 0:
					if ((map[enemy_7y * 10 + 20][enemy_7x * 10] == '9' ||map[enemy_7y * 10 + 20][enemy_7x * 10 - 10] == '9' || map[enemy_7y * 10 + 20][enemy_7x * 10 + 10] == '9') || map[enemy_7y * 10 + 20][enemy_7x * 10] == '-' || map[enemy_7y * 10 + 20][enemy_7x * 10] == '0' && map[enemy_7y * 10 + 20][enemy_7x * 10 - 10] == '0' && map[enemy_7y * 10 + 20][enemy_7x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_7y++;
						putimage(enemy_7x * 10, enemy_7y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_7_life)
						return 0;
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_7y * 10 - 20][enemy_7x * 10] == '9' ||
						map[enemy_7y * 10 - 20][enemy_7x * 10 - 10] == '9' ||
						map[enemy_7y * 10 - 20][enemy_7x * 10 + 10] == '9') || 
						map[enemy_7y * 10 - 20][enemy_7x * 10] == '0' && map[enemy_7y * 10 - 20][enemy_7x * 10 - 10] == '0' && map[enemy_7y * 10 - 20][enemy_7x * 10 + 10] == '0' || map[enemy_7y * 10 - 20][enemy_7x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_7y--;
						putimage(enemy_7x * 10, enemy_7y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_7_life)
						return 0;
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_7x > 0 &&
						(map[enemy_7y * 10][enemy_7x * 10 - 20] == '9' ||
						map[enemy_7y * 10 + 10][enemy_7x * 10 - 20] == '9' ||
						map[enemy_7y * 10 - 10][enemy_7x * 10 - 20] == '9' || 
						map[enemy_7y * 10][enemy_7x * 10 - 20] == '-' || map[enemy_7y * 10][enemy_7x * 10 - 20] == '0' && map[enemy_7y * 10 + 10][enemy_7x * 10 - 20] == '0' && map[enemy_7y * 10 - 10][enemy_7x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_7x--;
						putimage(enemy_7x * 10 + 10, enemy_7y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_7_life)
						return 0;
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_7y * 10][enemy_7x * 10 + 20] == '9' ||
						map[enemy_7y * 10 + 10][enemy_7x * 10 + 20] == '9' ||
						map[enemy_7y * 10 - 10][enemy_7x * 10 + 20] == '9' ||
						map[enemy_7y * 10][enemy_7x * 10 + 20] == '-' ||
						enemy_7x / 2 <= WIDTH-1.5 && 
						map[enemy_7y * 10][enemy_7x * 10 + 20] == '0' && 
						map[enemy_7y * 10 + 10][enemy_7x * 10 + 20] == '0' && 
						map[enemy_7y * 10 - 10][enemy_7x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_7x++;
						putimage(enemy_7x * 10 - 10, enemy_7y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_7_life)
						return 0;
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_7x * 10, enemy_7y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy8_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_8x * 10, enemy_8y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_8x * 10, enemy_8y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_8x * 10, enemy_8y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_8x * 10, enemy_8y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_8_life&& (player_life+dany_life))
	{
		srand(7+direction_enemy_7+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_8x, enemy_8y, dany_x, dany_y, mapTemp8, shortcut8);

		for (int step = 0;  (player_life+dany_life)&&enemy_8_life && step < 20; step++)
		{
			if (shortcut8[step] == -1)
				direction_enemy_8 = rand() % 4;
			else
				direction_enemy_8 = shortcut8[step];

			for (int i = 1; i <= 2 && enemy_8_life; i++)
			{
				switch (direction_enemy_8)
				{
				case 0:
					if ((map[enemy_8y * 10 + 20][enemy_8x * 10] == '9' ||map[enemy_8y * 10 + 20][enemy_8x * 10 - 10] == '9' || map[enemy_8y * 10 + 20][enemy_8x * 10 + 10] == '9') || map[enemy_8y * 10 + 20][enemy_8x * 10] == '-' || map[enemy_8y * 10 + 20][enemy_8x * 10] == '0' && map[enemy_8y * 10 + 20][enemy_8x * 10 - 10] == '0' && map[enemy_8y * 10 + 20][enemy_8x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_8y++;
						putimage(enemy_8x * 10, enemy_8y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_8_life)
						return 0;
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_8y * 10 - 20][enemy_8x * 10] == '9' ||
						map[enemy_8y * 10 - 20][enemy_8x * 10 - 10] == '9' ||
						map[enemy_8y * 10 - 20][enemy_8x * 10 + 10] == '9') || 
						map[enemy_8y * 10 - 20][enemy_8x * 10] == '0' && map[enemy_8y * 10 - 20][enemy_8x * 10 - 10] == '0' && map[enemy_8y * 10 - 20][enemy_8x * 10 + 10] == '0' || map[enemy_8y * 10 - 20][enemy_8x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_8y--;
						putimage(enemy_8x * 10, enemy_8y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_8_life)
						return 0;
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_8x > 0 &&
						(map[enemy_8y * 10][enemy_8x * 10 - 20] == '9' ||
						map[enemy_8y * 10 + 10][enemy_8x * 10 - 20] == '9' ||
						map[enemy_8y * 10 - 10][enemy_8x * 10 - 20] == '9' || 
						map[enemy_8y * 10][enemy_8x * 10 - 20] == '-' || map[enemy_8y * 10][enemy_8x * 10 - 20] == '0' && map[enemy_8y * 10 + 10][enemy_8x * 10 - 20] == '0' && map[enemy_8y * 10 - 10][enemy_8x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_8x--;
						putimage(enemy_8x * 10 + 10, enemy_8y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_8_life)
						return 0;
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_8y * 10][enemy_8x * 10 + 20] == '9' ||
						map[enemy_8y * 10 + 10][enemy_8x * 10 + 20] == '9' ||
						map[enemy_8y * 10 - 10][enemy_8x * 10 + 20] == '9' ||
						map[enemy_8y * 10][enemy_8x * 10 + 20] == '-' ||
						enemy_8x / 2 <= WIDTH-1.5 && 
						map[enemy_8y * 10][enemy_8x * 10 + 20] == '0' && 
						map[enemy_8y * 10 + 10][enemy_8x * 10 + 20] == '0' && 
						map[enemy_8y * 10 - 10][enemy_8x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_8x++;
						putimage(enemy_8x * 10 - 10, enemy_8y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_8_life)
						return 0;
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_8x * 10, enemy_8y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy9_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_9x * 10, enemy_9y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_9x * 10, enemy_9y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_9x * 10, enemy_9y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_9x * 10, enemy_9y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_9_life&& (player_life+dany_life))
	{
		srand(8+direction_enemy_8+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_9x, enemy_9y, dany_x, dany_y, mapTemp9, shortcut9);

		for (int step = 0;  (player_life+dany_life)&&enemy_9_life && step < 20; step++)
		{
			if (shortcut9[step] == -1)
				direction_enemy_9 = rand() % 4;
			else
				direction_enemy_9 = shortcut9[step];

			for (int i = 1; i <= 2 && enemy_9_life; i++)
			{
				switch (direction_enemy_9)
				{
				case 0:
					if ((map[enemy_9y * 10 + 20][enemy_9x * 10] == '9' ||map[enemy_9y * 10 + 20][enemy_9x * 10 - 10] == '9' || map[enemy_9y * 10 + 20][enemy_9x * 10 + 10] == '9') || map[enemy_9y * 10 + 20][enemy_9x * 10] == '-' || map[enemy_9y * 10 + 20][enemy_9x * 10] == '0' && map[enemy_9y * 10 + 20][enemy_9x * 10 - 10] == '0' && map[enemy_9y * 10 + 20][enemy_9x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_9y++;
						putimage(enemy_9x * 10, enemy_9y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_9_life)
						return 0;
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_9y * 10 - 20][enemy_9x * 10] == '9' ||
						map[enemy_9y * 10 - 20][enemy_9x * 10 - 10] == '9' ||
						map[enemy_9y * 10 - 20][enemy_9x * 10 + 10] == '9') || 
						map[enemy_9y * 10 - 20][enemy_9x * 10] == '0' && map[enemy_9y * 10 - 20][enemy_9x * 10 - 10] == '0' && map[enemy_9y * 10 - 20][enemy_9x * 10 + 10] == '0' || map[enemy_9y * 10 - 20][enemy_9x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_9y--;
						putimage(enemy_9x * 10, enemy_9y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_9_life)
						return 0;
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_9x > 0 &&
						(map[enemy_9y * 10][enemy_9x * 10 - 20] == '9' ||
						map[enemy_9y * 10 + 10][enemy_9x * 10 - 20] == '9' ||
						map[enemy_9y * 10 - 10][enemy_9x * 10 - 20] == '9' || 
						map[enemy_9y * 10][enemy_9x * 10 - 20] == '-' ||
						map[enemy_9y * 10][enemy_9x * 10 - 20] == '0' && 
						map[enemy_9y * 10 + 10][enemy_9x * 10 - 20] == '0' && 
						map[enemy_9y * 10 - 10][enemy_9x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_9x--;
						putimage(enemy_9x * 10 + 10, enemy_9y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_9_life)
						return 0;
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_9y * 10][enemy_9x * 10 + 20] == '9' ||
						map[enemy_9y * 10 + 10][enemy_9x * 10 + 20] == '9' ||
						map[enemy_9y * 10 - 10][enemy_9x * 10 + 20] == '9' ||
						map[enemy_9y * 10][enemy_9x * 10 + 20] == '-' ||
						enemy_9x / 2 <= WIDTH - 1.5 && 
						map[enemy_9y * 10][enemy_9x * 10 + 20] == '0' && 
						map[enemy_9y * 10 + 10][enemy_9x * 10 + 20] == '0' && 
						map[enemy_9y * 10 - 10][enemy_9x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_9x++;
						putimage(enemy_9x * 10 - 10, enemy_9y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_9_life)
						return 0;
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_9x * 10, enemy_9y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}
DWORD _stdcall enemy10_move(LPVOID lpParameter)
{
	if (generated)
	{
		int i;
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						//炸弹被盖住而使用此循环
			putimage(enemy_10x * 10, enemy_10y * 10, &eye4);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(enemy_10x * 10, enemy_10y * 10, &eye3);
			Sleep(25);
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_10x * 10, enemy_10y * 10, &eye2);
			Sleep(25);
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(enemy_10x * 10, enemy_10y * 10, &eye1);
			Sleep(75);
		}
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);
	}

	while (enemy_10_life&& (player_life+dany_life))
	{
		srand(9+direction_enemy_9+(unsigned)time(NULL));
		//int mapTemp[HEIGHT ][WIDTH ];
		findShortCut(enemy_10x, enemy_10y, dany_x, dany_y, mapTemp10, shortcut10);

		for (int step = 0;  (player_life+dany_life)&&enemy_10_life && step < 20; step++)
		{
			if (shortcut10[step] == -1)
				direction_enemy_10 = rand() % 4;
			else
				direction_enemy_10 = shortcut10[step];

			for (int i = 1; i <= 2 && enemy_10_life; i++)
			{
				switch (direction_enemy_10)
				{
				case 0:
					if ((map[enemy_10y * 10 + 20][enemy_10x * 10] == '9' ||map[enemy_10y * 10 + 20][enemy_10x * 10 - 10] == '9' || map[enemy_10y * 10 + 20][enemy_10x * 10 + 10] == '9') || 
						map[enemy_10y * 10 + 20][enemy_10x * 10] == '-' ||
						map[enemy_10y * 10 + 20][enemy_10x * 10] == '0' && 
						map[enemy_10y * 10 + 20][enemy_10x * 10 - 10] == '0' && 
						map[enemy_10y * 10 + 20][enemy_10x * 10 + 10] == '0')										//若玩家撞到内部的石头，则在原地行走
					{
						enemy_10y++;
						putimage(enemy_10x * 10, enemy_10y * 10 - 10, &background);										// 在坐标 (m, n) 位置显示 enemy_w2
					}
					if (!enemy_10_life)
						return 0;
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_s2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_s3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_s1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				case 1:
					if ((map[enemy_10y * 10 - 20][enemy_10x * 10] == '9' ||
						map[enemy_10y * 10 - 20][enemy_10x * 10 - 10] == '9' ||
						map[enemy_10y * 10 - 20][enemy_10x * 10 + 10] == '9') || 
						map[enemy_10y * 10 - 20][enemy_10x * 10] == '0' && map[enemy_10y * 10 - 20][enemy_10x * 10 - 10] == '0' && map[enemy_10y * 10 - 20][enemy_10x * 10 + 10] == '0' || map[enemy_10y * 10 - 20][enemy_10x * 10] == '-')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_10y--;
						putimage(enemy_10x * 10, enemy_10y * 10 + 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_10_life)
						return 0;
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_w2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_w3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_w1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 2:
					if (enemy_10x > 0 &&
						(map[enemy_10y * 10][enemy_10x * 10 - 20] == '9' ||
						map[enemy_10y * 10 + 10][enemy_10x * 10 - 20] == '9' ||
						map[enemy_10y * 10 - 10][enemy_10x * 10 - 20] == '9'||
						map[enemy_10y * 10][enemy_10x * 10 - 20] == '-' ||
						map[enemy_10y * 10][enemy_10x * 10 - 20] == '0' && 
						map[enemy_10y * 10 + 10][enemy_10x * 10 - 20] == '0' &&
						map[enemy_10y * 10 - 10][enemy_10x * 10 - 20] == '0'))											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_10x--;
						putimage(enemy_10x * 10 + 10, enemy_10y * 10, &background);									// 在坐标 (m, n'-'0) 位置显示 background
					}
					if (!enemy_10_life)
						return 0;
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_a2);											// 在坐标 (m, n) 位置显示 enemy_w2
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_a3);											// 在坐标 (m, n) 位置显示 enemy_w3
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_a1);											// 在坐标 (m, n) 位置显示 enemy_w1 
					Sleep(sleep_enemy * 2);
					break;
				case 3:
					if (map[enemy_10y * 10][enemy_10x * 10 + 20] == '9' ||
						map[enemy_10y * 10 + 10][enemy_10x * 10 + 20] == '9' ||
						map[enemy_10y * 10 - 10][enemy_10x * 10 + 20] == '9' ||
						map[enemy_10y * 10][enemy_10x * 10 + 20] == '-' ||
						enemy_10x / 2 <= WIDTH-1.5 && 
						map[enemy_10y * 10][enemy_10x * 10 + 20] == '0' && 
						map[enemy_10y * 10 + 10][enemy_10x * 10 + 20] == '0' && 
						map[enemy_10y * 10 - 10][enemy_10x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
					{
						enemy_10x++;
						putimage(enemy_10x * 10 - 10, enemy_10y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
					}
					if (!enemy_10_life)
						return 0;
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_d2);											// 在坐标 (m, n) 位置显示 enemy_s2
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_d3);											// 在坐标 (m, n) 位置显示 enemy_enemy_s3
					Sleep(sleep_enemy * 2);
					putimage(enemy_10x * 10, enemy_10y * 10, &enemy_d1);											// 在坐标 (m, n) 位置显示 enemy_s1 
					Sleep(sleep_enemy * 2);
					break;
				}
			}
		}
	}
	return 0;
}

void dany_brick_death(void)
{
	if (abs(10 * dany_x - 20 * carry_x) <= 10 && abs(10 * dany_y - 20 * carry_y) <= 10)
		dany_life = 0;
}
void enemy_brick_death(int* enemy_x, int* enemy_y, int* enemy_life, double* enemy_dead_time)
{
	if (*enemy_life&&abs(10 * *enemy_x - 20 * carry_x) <= 10 && abs(10 * *enemy_y - 20 * carry_y) <= 10)
	{
		*enemy_life = 0;
		*enemy_dead_time = clock();
		//Sleep(3 * sleep_player);
		putimage(10 * *enemy_x, 10 * *enemy_y, &background);
	}
}

void dany_flame_power()
{
	if (abs(10 * dany_x - 20 * flame_x) <= 10 && abs(10 * dany_y - 20 * flame_y) <= 10)
	{
		bullets = 1;
		putimage(20 * flame_x, 20 * flame_y, &background);
	}
}
void enemy_fire_death(int* enemy_x, int* enemy_y, int* enemy_life, double* enemy_dead_time)
{
	if (*enemy_life&&abs(10 * *enemy_x - 20 * bullet_x) <= 10 && abs(10 * *enemy_y - 20 * bullet_y) <= 10)
	{
		*enemy_life = 0;
		*enemy_dead_time = clock();
		putimage(10 * *enemy_x, 10 * *enemy_y, &background);
	}
}
void player_fire_death(void)
{
	if ((abs(10 * player_x - 20 * bullet_x) <= 10) && (abs(10 * player_y - 20 * bullet_y) <= 10))
		player_life = 0;
}
DWORD _stdcall fire(LPVOID lpParameter)
{
	mciSendString("close dracarys.wav", NULL, 0, 0);
	mciSendString("open dracarys.wav", NULL, 0, 0);
	mciSendString("play dracarys.wav", NULL, 0, 0);
	switch (direction)
	{
	case 1://up
		do
		{
			bullet_y--;
			if (map[bullet_y * 20][bullet_x * 20] == '1')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_w_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '5')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_w_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if ( map[bullet_y * 20][bullet_x * 20] == '6')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_w_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '7')
			{
				bullets = 1;
				return 0;// 7;
			}
			//else if (map[bullet_y * 20][bullet_x * 20] == '6')
			//{
			//	bullets = 1;
			//	return 0;// 6;
			//}
			else if (map[bullet_y * 20][bullet_x * 20] == '4')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_w_1);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &water);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '0')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_w_1);
				player_fire_death();
				enemy_fire_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
				enemy_fire_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
				enemy_fire_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
				enemy_fire_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
				enemy_fire_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
				enemy_fire_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
				enemy_fire_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
				enemy_fire_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
				enemy_fire_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
				enemy_fire_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);


				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}
		} while (bullet_y > 0);
		break;
	case 2:
		do
		{
			bullet_y++;
			if (map[bullet_y * 20][bullet_x * 20] == '1')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_s_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '5')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_s_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '7')
			{
				bullets = 1;
				return 0;// 7;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '6')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_s_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '4')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_s_1);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &water);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '0')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_s_1);
				player_fire_death();
				enemy_fire_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
				enemy_fire_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
				enemy_fire_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
				enemy_fire_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
				enemy_fire_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
				enemy_fire_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
				enemy_fire_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
				enemy_fire_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
				enemy_fire_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
				enemy_fire_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}

		} while (bullet_y < HEIGHT - 1);
		break;
	case 3:
		do
		{
			bullet_x--;
			if (map[bullet_y * 20][bullet_x * 20] == '1')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_a_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '5')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_a_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '7')
			{
				bullets = 1;
				return 0;// 7;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '6')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_a_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '4')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_a_1);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &water);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '0')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_a_1);
				player_fire_death();
				enemy_fire_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
				enemy_fire_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
				enemy_fire_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
				enemy_fire_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
				enemy_fire_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
				enemy_fire_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
				enemy_fire_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
				enemy_fire_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
				enemy_fire_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
				enemy_fire_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}

		} while (bullet_x > 0);
		break;
	case 4://right
		do
		{
			bullet_x++;
			if (map[bullet_y * 20][bullet_x * 20] == '1')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_d_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			if (map[bullet_y * 20][bullet_x * 20] == '5')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_d_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
				break;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '7')
			{
				bullets = 1;
				return 0;// 7;
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '6')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_d_1);
				Sleep(sleep_bullet);
				map[bullet_y * 20][bullet_x * 20] = '0';
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '4')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_d_1);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &water);
			}
			else if (map[bullet_y * 20][bullet_x * 20] == '0')
			{
				putimage(20 * bullet_x, 20 * bullet_y, &bomb_side_d_1);
				player_fire_death();
				enemy_fire_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
				enemy_fire_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
				enemy_fire_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
				enemy_fire_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
				enemy_fire_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
				enemy_fire_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
				enemy_fire_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
				enemy_fire_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
				enemy_fire_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
				enemy_fire_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
				Sleep(sleep_bullet);
				putimage(20 * bullet_x, 20 * bullet_y, &background);
			}
		} while (bullet_x < WIDTH - 1);
		break;
	}
	bullets = 1;
	return 0;// 1;
}
DWORD _stdcall dany_move(LPVOID lpParameter)
{
	while (dany_life && win_fail == 0)
	{////////////////////dany////////////////////
		if (GetKeyState(40) < 0)//0x53
		{
			direction = 2;                                                                                                      //down
			if (map[dany_y * 10 + 20][dany_x * 10] == '-' ||
				dany_y <= HEIGHT * 2 &&
				map[dany_y * 10 + 20][dany_x * 10] == '0' &&
				map[dany_y * 10 + 20][dany_x * 10 - 10] == '0' &&
				map[dany_y * 10 + 20][dany_x * 10 + 10] == '0')	//map[dany_y * 10 + 20][dany_x * 10] == '-'若玩家撞到内部的石头，则在原地行走
			{
				dany_y++;
				putimage(dany_x * 10, dany_y * 10 - 10, &background);									// 在坐标 (m, n-10) 位置显示 background
			}

			//if (map[dany_y * 10 + 20][dany_x * 10] == '4')
				//dany_life--;
			putimage(dany_x * 10, dany_y * 10, &dany_s2);											// 在坐标 (m, n) 位置显示 dany_s2
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_s3);											// 在坐标 (m, n) 位置显示 dany_dany_s3
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_s1);											// 在坐标 (m, n) 位置显示 dany_s1 
			Sleep(sleep_dany);
			dany_face_y = 1;
		}
		if (GetKeyState(38) < 0)//0x530x57
		{
			direction = 1;                                                                                                       //left
			if (map[dany_y * 10 - 20][dany_x * 10] == '-' ||
				dany_y > 0 &&
				map[dany_y * 10 - 20][dany_x * 10] == '0' &&
				map[dany_y * 10 - 20][dany_x * 10 + 10] == '0' &&
				map[dany_y * 10 - 20][dany_x * 10 - 10] == '0')							//若玩家撞到内部的石头，则在原地行走
			{
				dany_y--;
				putimage(dany_x * 10, dany_y * 10 + 10, &background);								// 在坐标 (m, n-10) 位置显示 background
			}
			//if (map[dany_y * 10][dany_x * 10 - 20] == '4')
				//dany_life--;
			putimage(dany_x * 10, dany_y * 10, &dany_w2);											// 在坐标 (m, n) 位置显示 dany_w2
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_w3);											// 在坐标 (m, n) 位置显示 dany_w3
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_w1);											// 在坐标 (m, n) 位置显示 dany_w1 
			Sleep(sleep_dany);
			dany_face_y = -1;
		}
		if (GetKeyState(37) < 0)//0x530x570x41
		{
			direction = 3;                                                                                                       //left
			if (map[dany_y * 10][dany_x * 10 - 20] == '-' ||
				dany_x > 0 &&
				map[dany_y * 10][dany_x * 10 - 20] == '0' &&
				map[dany_y * 10 + 10][dany_x * 10 - 20] == '0' &&
				map[dany_y * 10 - 10][dany_x * 10 - 20] == '0')										//若玩家撞到内部的石头，则在原地行走
			{
				dany_x--;
				putimage(dany_x * 10 + 10, dany_y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
			}
			//if (map[dany_y * 10][dany_x * 10 - 20] == '4')
				//dany_life--;
			putimage(dany_x * 10, dany_y * 10, &dany_a2);											// 在坐标 (m, n) 位置显示 dany_w2
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_a3);											// 在坐标 (m, n) 位置显示 dany_w3
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_a1);											// 在坐标 (m, n) 位置显示 dany_w1 
			Sleep(sleep_dany);
			dany_face_x = -1;
		}
		if (GetKeyState(39) < 0)//0x530x570x410x44
		{
			direction = 4;                                                                                                           //right
			if (map[dany_y * 10][dany_x * 10 + 20] == '-' ||
				dany_x <= WIDTH * 2 - 3 &&
				map[dany_y * 10][dany_x * 10 + 20] == '0' &&
				map[dany_y * 10 + 10][dany_x * 10 + 20] == '0' &&
				map[dany_y * 10 - 10][dany_x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
			{
				dany_x++;
				putimage(dany_x * 10 - 10, dany_y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
			}
			//if (map[dany_y * 10][dany_x * 10 + 20] == '4')
				//dany_life--;
			putimage(dany_x * 10, dany_y * 10, &dany_d2);											// 在坐标 (m, n) 位置显示 dany_s2
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_d3);											// 在坐标 (m, n) 位置显示 dany_dany_s3
			Sleep(sleep_dany);
			putimage(dany_x * 10, dany_y * 10, &dany_d1);											// 在坐标 (m, n) 位置显示 dany_s1 
			Sleep(sleep_dany);
			dany_face_x = 1;
		}
		if (GetKeyState(101) < 0)//0x530x570x410x440x20
		{
			start = clock();

			if ((start - finish) / CLOCKS_PER_SEC > 0.5 && bullets > 0)
			{
				if (dany_x % 2)
					bullet_x = (dany_x + dany_face_x) / 2;
				else
					bullet_x = dany_x / 2;
				if (dany_y % 2)
					bullet_y = (dany_y + dany_face_y) / 2;
				else
					bullet_y = dany_y / 2;
				bullets = 0;
				finish = clock();
				hthread12 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)fire, NULL, 0, &ThreadID);
			}
		}
	}
	return 0;
}

void sharingan_power()
{
	if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '5'&&
		map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '5' &&
		map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '5' &&
		map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '5')
	{
		mciSendString("close dragon_glass.mp3", NULL, 0, 0);
		mciSendString("open dragon_glass.mp3", NULL, 0, 0);
		mciSendString("play dragon_glass.mp3", NULL, 0, 0);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_1);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_1);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_1);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_1);
		Sleep(100);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_2);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_2);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_2);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_2);
		Sleep(100);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_3);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_3);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_3);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_3);
		Sleep(100);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_4);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_4);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_4);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_4);
		Sleep(100);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_5);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_5);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_5);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_5);

		map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
		map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
		map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
		map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';

		sleep_enemy = _SLEEP_ENEMY /2;
		sharingan = 0;
		enemy_rebirth = 0;
		sharingan_sleep = clock();
		if (dany_life == 0)
		{
			dany_life = 1;
			hthread14 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dany_move, NULL, 0, &ThreadID);
		}
	}
	Sleep(75);
}
DWORD _stdcall brick_show(LPVOID lpParameter)
{
	if (map[carry_y * 20][carry_x * 20] == '0'&&(glass == 0))
	{
		map[carry_y * 20][carry_x * 20] = '1';
	}
	else if (map[carry_y * 20][carry_x * 20] == '0'&&(glass == 1))
	{
		map[carry_y * 20][carry_x * 20] = '5';
		sleep_player = sleep_player * 2;
		glass = 0;
		sharingan_power();
	}
	else if (map[carry_y * 20][carry_x * 20] == '1')
	{
		map[carry_y * 20][carry_x * 20] = '0';
	}
	else if (map[carry_y * 20][carry_x * 20] == '5'&&(glass == 0))
	{
		map[carry_y * 20][carry_x * 20] = '0';
		glass = 1;
		sleep_player = sleep_player / 2;
	}

	enemy_brick_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
	enemy_brick_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
	enemy_brick_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
	enemy_brick_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
	enemy_brick_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
	enemy_brick_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
	enemy_brick_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
	enemy_brick_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
	enemy_brick_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
	enemy_brick_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
	dany_brick_death();



	if (map[carry_y * 20][carry_x * 20] == '0')
	{
		mciSendString("close bomb.mp3", NULL, 0, 0);
		mciSendString("open bomb.mp3", NULL, 0, 0);
		mciSendString("play bomb.mp3", NULL, 0, 0);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_1);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_2);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_3);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_4);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_5);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &background);
	}
	else if (map[carry_y * 20][carry_x * 20] == '1')
	{
		//mciSendString("open bomb.mp3", NULL, 0, 0);
		mciSendString("close bomb.mp3", NULL, 0, 0);
		mciSendString("open bomb.mp3", NULL, 0, 0);
		mciSendString("play bomb.mp3", NULL, 0, 0);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_1);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_2);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_3);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &brick);
	}
	else if (map[carry_y * 20][carry_x * 20] == '5')
	{
		//mciSendString("open bomb.mp3", NULL, 0, 0);
		mciSendString("close bomb.mp3", NULL, 0, 0);
		mciSendString("open bomb.mp3", NULL, 0, 0);
		mciSendString("play bomb.mp3", NULL, 0, 0);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_1);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_2);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &bomb_mid_3);
		Sleep(100);
		putimage(carry_x * 20, carry_y * 20, &brown);
	}

	carrys++;
	return 0;
}

DWORD _stdcall eyes_show(LPVOID lpParameter)
{
	if (!sharingan && ((clock() - sharingan_sleep) / CLOCKS_PER_SEC > dead_sleep))
	{
		sharingan = 1;
		sleep_enemy = _SLEEP_ENEMY;
	}

	int i;
	while (eyes==1)
	{
		for (i = 1; i <= 8; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{														//炸弹被盖住而使用此循环
			if (map[20 * (flame_y + 4)][ 20 * (flame_x + 4)]=='0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye1);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye1);
			}
			if (map[20 * (flame_y -3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye1);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye1);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye1);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye1);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye1);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye1);
			}
			Sleep(75);
			//player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye2);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye2);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye2);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye2);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye2);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye2);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye2);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye2);
			}
			Sleep(25);
			//player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye3);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye3);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye3);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye3);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye3);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye3);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye3);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye3);
			}
			Sleep(25);
			//player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{														//炸弹被盖住而使用此循环
			if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye4);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye4);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye4);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye4);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye4);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye4);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye4);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye4);
			}
			Sleep(25);
			//player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye3);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye3);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye3);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye3);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye3);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye3);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye3);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye3);
			}
			Sleep(25);
			//player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye2);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye2);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye2);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye2);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye2);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye2);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye2);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye2);
			}
			Sleep(25);
			//player_eye_power();
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '0')
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye1);
			else if (map[20 * (flame_y + 4)][20 * (flame_x + 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x + 4)] = '0';
				putimage(20 * (flame_x + 4), 20 * (flame_y + 4), &eye1);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '0')
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye1);
			else if (map[20 * (flame_y - 3)][20 * (flame_x + 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x + 7)] = '0';
				putimage(20 * (flame_x + 7), 20 * (flame_y - 3), &eye1);
			}
			if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '0')
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye1);
			else if (map[20 * (flame_y - 3)][20 * (flame_x - 7)] == '1')
			{
				map[20 * (flame_y - 3)][20 * (flame_x - 7)] = '0';
				putimage(20 * (flame_x - 7), 20 * (flame_y - 3), &eye1);
			}
			if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '0')
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye1);
			else if (map[20 * (flame_y + 4)][20 * (flame_x - 4)] == '1')
			{
				map[20 * (flame_y + 4)][20 * (flame_x - 4)] = '0';
				putimage(20 * (flame_x - 4), 20 * (flame_y + 4), &eye1);
			}
			Sleep(75);
			//player_eye_power();
		}
		//player_eye_power();
	}
	return 0;
}
void player_eye_power()
{
	if (eyes == 0 && abs(10 * player_x - 20 * eye_x) <= 10 && abs(10 * player_y - 20 * eye_y) <= 10)
	{
		bombs = 0;
		eyes = 1;
		mciSendString("close dragon_glass.mp3", NULL, 0, 0);
		mciSendString("open dragon_glass.mp3", NULL, 0, 0);
		mciSendString("play dragon_glass.mp3", NULL, 0, 0);
		
		putimage(eye_x * 20, eye_y * 20, &bomb_mid_1);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_1);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_1);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_1);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_1);
		Sleep(100);
		putimage(eye_x * 20, eye_y * 20, &bomb_mid_2);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_2);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_2);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_2);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_2);
		Sleep(100);
		putimage(eye_x * 20, eye_y * 20, &bomb_mid_3);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_3);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_3);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_3);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_3);
		Sleep(100);
		putimage(eye_x * 20, eye_y * 20, &bomb_mid_4);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_4);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_4);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_4);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_4);
		Sleep(100);
		putimage(eye_x * 20, eye_y * 20, &bomb_mid_5);
		putimage((flame_x + 4) * 20, (flame_y + 4) * 20, &bomb_mid_5);
		putimage((flame_x + 7) * 20, (flame_y - 3) * 20, &bomb_mid_5);
		putimage((flame_x - 7) * 20, (flame_y - 3) * 20, &bomb_mid_5);
		putimage((flame_x - 4) * 20, (flame_y + 4) * 20, &bomb_mid_5);
		Sleep(100);

		hthread18 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)eyes_show, NULL, 0, &ThreadID);
		putimage(eye_x * 20, eye_y * 20, &background);
	}
}
DWORD _stdcall eye_show(LPVOID lpParameter)
{
	int i;
	while (eyes==0)
	{
		for (i = 1; i <= 8; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{	
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}													//炸弹被盖住而使用此循环
			putimage(20 * eye_x, 20 * eye_y, &eye1);
			Sleep(75);
			player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}
			putimage(20 * eye_x, 20 * eye_y, &eye2);
			Sleep(25);
			player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}
			putimage(20 * eye_x, 20 * eye_y, &eye3);
			Sleep(25);
			player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{						
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}								//炸弹被盖住而使用此循环
			putimage(20 * eye_x, 20 * eye_y, &eye4);
			Sleep(25);
			player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第二张炸弹图片一秒，
		{
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}
			putimage(20 * eye_x, 20 * eye_y, &eye3);
			Sleep(25);
			player_eye_power();
		}
		for (i = 1; i <= 2; i++)										//循环播放第三张炸弹图片一秒，
		{
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}
			putimage(20 * eye_x, 20 * eye_y, &eye2);
			Sleep(25);
			player_eye_power();
		}
		for (i = 1; i <= 8; i++)										//循环播放第三张炸弹图片一秒，
		{
			if (eyes)
			{
				putimage(20 * eye_x, 20 * eye_y, &background);
				break;
				break;
			}
			putimage(20 * eye_x, 20 * eye_y, &eye1);
			Sleep(75);
			player_eye_power();
		}
	}
	return 0;
}

/*
void enemyGenerate(void* enemy_generate)
{
	void EnemyGenerate();
	EnemyGenerate = enemy_generate;
	&(enemy_generate)(&enemy_1x, &enemy_1y, &enemy_1_life);
	*enemy_generate(&enemy_2x, &enemy_2y, &enemy_2_life);
}
*/

int genmap()
{
	PlaySound(TEXT("crisis3.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	srand((unsigned int)(time(NULL)));
	char trash;
	initgraph(WIDTH * 20, HEIGHT * 20);

	putimage(0, 0, &jlu);
	setbkmode(TRANSPARENT);

	setcolor(BLACK);
	settextstyle(35, 0, _T("Times New Roman"));
	outtextxy(13 * 20, 1 * 17, "The wights have just occupied JiLin university.");
	outtextxy(13 * 20, 3 * 17, "In order to win the battle with the dead,");
	outtextxy(13 * 20, 5 * 17, "Daenerys and Edward must kill all wights in 7mins.");
	outtextxy(13 * 20, 7 * 17, "Be careful not to touch any wights!");

	settextstyle(70, 0,_T("Times New Roman"));
	int color = 255;
	while (1)
	{
		setcolor(RGB(color, 0, 0));
		outtextxy((WIDTH-28) * 10, (HEIGHT-3) * 20, "click on enter to continue");
		color -= 8;
		if (color < 0)
			color = 255;
		Sleep(25);
		if (_kbhit() && _getch() == '\r')
		{
			//PlaySound(TEXT("big_background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		}
	}

	putimage(0, 0, &physics);
	putimage(64*20, 28*20, &daenerys);
	putimage(1*20, 30*20, &edward);

	while (1)
	{
		setcolor(RGB(color, 0, 0));
		outtextxy((WIDTH - 25) * 10, (HEIGHT - 3) * 20, "click on enter to start");
		color -= 8;
		if (color < 0)
			color = 255;
		Sleep(25);
		if (_kbhit() && _getch() == '\r')
		{
			//PlaySound(TEXT("big_background.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		}
	}

	for (int i = 0; i < HEIGHT * 20; i++)
	{
		for (int j = 0; j < WIDTH * 20; j++)
		{
			map[i][j] = '0';
		}
	}
	FILE *fpRead;
	fopen_s(&fpRead,"map.txt", "r");
	if (fpRead == NULL)
	{
		return 0;
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			fscanf_s(fpRead, "%c", &map[i * 20][j * 20]);
			char ch = map[i * 20][j * 20];
			switch (ch)
			{
			case '0':
				putimage(j * 20, i * 20, &background);
				break;
			case '7':
				putimage(j * 20, i * 20, &stone);
				break;
			case '1':
				putimage(j * 20, i * 20, &brick);
				break;
				//case'h':
					//putimage(j * 20, i * 20, &red);
					//break;
			case '3':
				putimage(j * 20, i * 20, &door);
				break;
			case '6':
				putimage(j * 20, i * 20, &trees);
				break;
			case '9':
				map[i * 20][j * 20] = '0';								// 在坐标 (i, j) 位置放置 brick
				dany_x = j * 2, dany_y = i * 2;
				putimage(dany_x * 10, dany_y * 10, &dany_s1);
				break;
			case '8':
				map[i * 20][j * 20] = '0';								// 在坐标 (i, j) 位置放置 brick
				flame_x = j, flame_y = i;
				putimage(flame_x * 20, flame_y * 20, &flame1);
				break;
			case '2':
				map[i * 20][j * 20] = '0';								// 在坐标 (i, j) 位置放置 brick
				eye_x = j, eye_y = i;
				putimage(eye_x * 20, eye_y * 20, &eye1);
				break;
			case '4':
				putimage(j * 20, i * 20, &water);
				break;
			}
			if ((ch == '0' || ch == '6') && rand() % 100 >= 98 && j < WIDTH/2 - 5)
			{
				map[i * 20][j * 20] = '5';								// 在坐标 (i, j) 位置放置 brick
				putimage(j * 20, i * 20, &brown);
			}
			if ((ch == '0' || ch == '6') && rand() % 100 >= 90 && j < WIDTH - 2)
			{
				map[i * 20][j * 20] = '1';								// 在坐标 (i, j) 位置放置 brick
				putimage(j * 20, i * 20, &brick);
			}
		}
		fscanf_s(fpRead, "%c", &trash);
	}
	putimage(player_x * 10, player_y * 10, &player_s1);													// 在坐标 (m, n) 位置显示 player_s1 对象
	putimage(44 * 20, 30 * 20, &door);													// 在坐标 (m, n) 位置显示 door 对象
	return 1;
}

DWORD _stdcall forest(LPVOID lpParameter)
{
	fire_x = bomb_x;
	fire_y = bomb_y;
	switch (forest_fire_direction)
	{
	case 1:
		do
		{
			fire_y--;
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_1);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_2);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_3);
			Sleep(20);
			map[fire_y * 20][fire_x * 20] = '3';
			putimage(20 * fire_x, 20 * fire_y, &orange);
		} while (map[fire_y * 20 - 20][fire_x * 20] == '6');
		break;
	case 2:
		do
		{
			fire_y++;
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_1);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_2);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_3);
			Sleep(20);
			map[fire_y * 20][fire_x * 20] = '3';
			putimage(20 * fire_x, 20 * fire_y, &orange);
		} while (map[fire_y * 20 + 20][fire_x * 20] == '6');
		break;
	case 3:
		do
		{
			fire_x--;
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_1);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_2);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_3);
			Sleep(20);
			map[fire_y * 20][fire_x * 20] = '3';
			putimage(20 * fire_x, 20 * fire_y, &orange);
		} while (map[fire_y * 20][fire_x * 20 - 20] == '6');
		break;
	case 4:
		do
		{
			fire_x++;
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_1);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_2);
			Sleep(20);
			putimage(20 * fire_x, 20 * fire_y, &bomb_side_w_3);
			Sleep(20);
			map[fire_y * 20][fire_x * 20] = '3';
			putimage(20 * fire_x, 20 * fire_y, &orange);
		} while (map[fire_y * 20][fire_x * 20 + 20] == '6');
		break;
	default:
		break;
	}
	return 1;
}

void enemy_bomb_death(int* enemy_x,int* enemy_y,int* enemy_life,double* enemy_dead_time)
{
	if (*enemy_life&&(abs(10 * *enemy_x - 20 * bomb_x) + abs(10 * *enemy_y - 20 * bomb_y)) <= 30)
	{
		*enemy_life = 0;
		*enemy_dead_time = clock();
		putimage(10 * *enemy_x, 10 * *enemy_y, &background);
	}
}

void enemy_generate(int* enemy_x, int* enemy_y, int* enemy_life)
{
	//srand((unsigned int)(time(NULL)));
	*enemy_x =  2 * (rand() % (WIDTH - 4));
	*enemy_y =  2 * (rand() % (HEIGHT - 1));
	
	if (map[*enemy_y * 10][*enemy_x * 10] != '0' || *enemy_x==dany_x)
		enemy_generate(enemy_x, enemy_y, enemy_life);
	else
	{
		*enemy_life = 1;
	}
}

void win(void)
{
	PlaySound(0, NULL, 0);
	PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	win_fail = 1;

	setbkmode(TRANSPARENT);
	settextstyle(70, 0, _T("Times New Roman"));

	int color = 255;
	while (1)
	{
		setcolor(RGB(color, 0, 0));
		outtextxy((WIDTH - 25) * 10, (HEIGHT) * 10, "click on enter to leave");
		color -= 8;
		if (color < 0)
			color = 255;
		Sleep(25);
		if (_kbhit() && _getch() == '\r')
			break;
	}
}

void fail(void)
{
	//mciSendString("close big_background.mp3", NULL, 0, 0);
	PlaySound(0, NULL, 0);
	Sleep(2000);
	PlaySound(TEXT("failed.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	win_fail = 1;

	setbkmode(TRANSPARENT);
	settextstyle(70, 0, _T("Times New Roman"));

	int color = 255;
	while (1)
	{
		setcolor(RGB(color, 0, 0));
		outtextxy((WIDTH - 25) * 10, (HEIGHT) * 10, "click on enter to leave");
		color -= 8;
		if (color < 0)
			color = 255;
		Sleep(25);
		if (_kbhit()&&_getch() == '\r')
			break;
	}
	//Sleep(700);
}

void players_enemy_death(int enemy_x, int enemy_y)
{
	if (abs(player_x - enemy_x) <= 1 && abs(player_y - enemy_y) <= 1)
	{
		player_life = 0;
		mciSendString("close enemy_kill.wav", NULL, 0, 0);
		mciSendString("open enemy_kill.wav", NULL, 0, 0);
		mciSendString("play enemy_kill.wav", NULL, 0, 0);
	}
	if (abs(dany_x - enemy_x) <= 1 && abs(dany_y - enemy_y) <= 1)
	{
		dany_life = 0;
		mciSendString("close enemy_kill.wav", NULL, 0, 0);
		mciSendString("open enemy_kill.wav", NULL, 0, 0);
		mciSendString("play enemy_kill.wav", NULL, 0, 0);
	}
}

void enemy_reborn()
{
	reborn_clock = clock();

	if (enemy_1_life)
		players_enemy_death(enemy_1x, enemy_1y);
	else if (enemy_rebirth&&enemy_1_dead_time&&((reborn_clock - enemy_1_dead_time) / CLOCKS_PER_SEC > 15.0))
	{
		enemy_generate(&enemy_1x, &enemy_1y, &enemy_1_life);
		hthread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy1_move, NULL, 0, &ThreadID);
		enemy_1_dead_time = 0;
	}

	if (enemy_2_life)
		players_enemy_death(enemy_2x, enemy_2y);
	else if (enemy_rebirth&&enemy_2_dead_time&&((reborn_clock - enemy_2_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_2x, &enemy_2y, &enemy_2_life);
		hthread3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy2_move, NULL, 0, &ThreadID);
		enemy_2_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_3_life)
		players_enemy_death(enemy_3x, enemy_3y);
	else if (enemy_rebirth&&enemy_3_dead_time&&((reborn_clock - enemy_3_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_3x, &enemy_3y, &enemy_3_life);
		hthread4 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy3_move, NULL, 0, &ThreadID);
		enemy_3_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_4_life)
		players_enemy_death(enemy_4x, enemy_4y);
	else if (enemy_rebirth&&enemy_4_dead_time&&((reborn_clock - enemy_4_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_4x, &enemy_4y, &enemy_4_life);
		hthread5 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy4_move, NULL, 0, &ThreadID);
		enemy_4_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_5_life)
		players_enemy_death(enemy_5x, enemy_5y);
	else if (enemy_rebirth&&enemy_5_dead_time&&((reborn_clock - enemy_5_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_5x, &enemy_5y, &enemy_5_life);
		hthread6 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy5_move, NULL, 0, &ThreadID);
		enemy_5_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_6_life)
		players_enemy_death(enemy_6x, enemy_6y);
	else if (enemy_rebirth&&enemy_6_dead_time&&((reborn_clock - enemy_6_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_6x, &enemy_6y, &enemy_6_life);
		hthread7 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy6_move, NULL, 0, &ThreadID);
		enemy_6_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_7_life)
		players_enemy_death(enemy_7x, enemy_7y);
	else if (enemy_rebirth&&enemy_7_dead_time&&((reborn_clock - enemy_7_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_7x, &enemy_7y, &enemy_7_life);
		hthread8 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy7_move, NULL, 0, &ThreadID);
		enemy_7_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_8_life)
		players_enemy_death(enemy_8x, enemy_8y);
	else if (enemy_rebirth&&enemy_8_dead_time&&((reborn_clock - enemy_8_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_8x, &enemy_8y, &enemy_8_life);
		hthread9 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy8_move, NULL, 0, &ThreadID);
		enemy_8_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_9_life)
		players_enemy_death(enemy_9x, enemy_9y);
	else if (enemy_rebirth&&enemy_9_dead_time&&((reborn_clock - enemy_9_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_9x, &enemy_9y, &enemy_9_life);
		hthread10 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy9_move, NULL, 0, &ThreadID);
		enemy_9_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}

	if (enemy_10_life)
		players_enemy_death(enemy_10x, enemy_10y);
	else if (enemy_rebirth&&enemy_10_dead_time && ((reborn_clock - enemy_10_dead_time) / CLOCKS_PER_SEC > dead_sleep))
	{
		enemy_generate(&enemy_10x, &enemy_10y, &enemy_10_life);
		hthread11 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy10_move, NULL, 0, &ThreadID);
		enemy_10_dead_time = 0;/*
		mciSendString("close dead_reborn.wav", NULL, 0, 0);
		mciSendString("open dead_reborn.wav", NULL, 0, 0);
		mciSendString("play dead_reborn.wav", NULL, 0, 0);*/
	}
}

/////////////////////////////////////////////////////
void player_bomb_death(void)
{
	if ((abs(10 * player_x - 20 * bomb_x) + abs(10 * player_y - 20 * bomb_y)) <= 30)
		player_life = 0;	
	if ((abs(10 * dany_x - 20 * bomb_x) + abs(10 * dany_y - 20 * bomb_y)) <= 30)
		dany_life = 0;
}
/////////////////////////////////////////////////////
void player_flame_death(void)
{
	if (abs(10 * player_x - 20 * flame_x) <= 10 && abs(10 * player_y - 20 * flame_y) <= 10)
		player_life = 0;
}

void enemy_flame_death(int* enemy_x, int* enemy_y, int* enemy_life, double* enemy_dead_time)
{
	if (*enemy_life&&abs(10 * *enemy_x - 20 * flame_x) <= 10 && abs(10 * *enemy_y - 20 * flame_y) <= 10)
	{
		*enemy_life = 0;
		*enemy_dead_time = clock();
		putimage(10 * *enemy_x, 10 * *enemy_y, &background);
	}
}

DWORD _stdcall bomb_show(LPVOID lpParameter)
{
	map[20 * bomb_y][20 * bomb_x] = '2';//炸弹的存在阻碍人物行走
	//map[20 * bomb_y+10][20 * bomb_x] = 2;//炸弹的存在阻碍人物向下行走
	//map[20 * bomb_y-10][20 * bomb_x] = 2;//炸弹的存在阻碍人物向上行走
	//map[20 * bomb_y][20 * bomb_x+10] = 2;//炸弹的存在阻碍人物向右行走
	//map[20 * bomb_y][20 * bomb_x-10] = 2;//炸弹的存在阻碍人物向左行走
	//the existence of 
	int i;
	for (i = 1; i <= 10; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
	{														//炸弹被盖住而使用此循环
		putimage(20 * bomb_x, 20 * bomb_y, &bomb_burning1);
		Sleep(50);
	}
	for (i = 1; i <= 10; i++)										//循环播放第二张炸弹图片一秒，
	{
		putimage(20 * bomb_x, 20 * bomb_y, &bomb_burning2);
		Sleep(50);
	}
	for (i = 1; i <= 11; i++)										//循环播放第三张炸弹图片一秒，
	{
		putimage(20 * bomb_x, 20 * bomb_y, &bomb_burning3);
		Sleep(50);
	}
	//mciSendString("open bomb.mp3", NULL, 0, 0);
	mciSendString("close bomb.mp3", NULL, 0, 0);
	mciSendString("open bomb.mp3", NULL, 0, 0);
	mciSendString("play bomb.mp3", NULL, 0, 0);
	putimage(20 * bomb_x, 20 * bomb_y, &bomb_burning3);
	Sleep(100);
	

	//map[20 * bomb_y + 10][20 * bomb_x] = 0;//炸弹的消失允许人物行走
	//map[20 * bomb_y - 10][20 * bomb_x] = 0;
	//map[20 * bomb_y][20 * bomb_x + 10] = 0;
	//map[20 * bomb_y][20 * bomb_x - 10] = 0;

	//炸弹范围赋值
	map[20 * bomb_y][20 * bomb_x] = '-';
	if (map[20 * bomb_y - 20][20 * bomb_x] == '1' ||
		map[20 * bomb_y - 20][20 * bomb_x] == '0' ||
		map[20 * bomb_y - 20][20 * bomb_x] == '5' ||
		map[20 * bomb_y - 20][20 * bomb_x] == '6')
		map[20 * bomb_y - 20][20 * bomb_x] = '-';
	if (map[20 * bomb_y + 20][20 * bomb_x] == '1' ||
		map[20 * bomb_y + 20][20 * bomb_x] == '0' ||
		map[20 * bomb_y + 20][20 * bomb_x] == '5' ||
		map[20 * bomb_y + 20][20 * bomb_x] == '6')
		map[20 * bomb_y + 20][20 * bomb_x] = '-';
	if (map[20 * bomb_y][20 * bomb_x - 20] == '1' ||
		map[20 * bomb_y][20 * bomb_x - 20] == '0' ||
		map[20 * bomb_y][20 * bomb_x - 20] == '5' ||
		map[20 * bomb_y][20 * bomb_x - 20] == '6')
		map[20 * bomb_y][20 * bomb_x - 20] = '-';
	if (map[20 * bomb_y][20 * bomb_x + 20] == '1' ||
		map[20 * bomb_y][20 * bomb_x + 20] == '0' ||
		map[20 * bomb_y][20 * bomb_x + 20] == '5' ||
		map[20 * bomb_y][20 * bomb_x + 20] == '6')
		map[20 * bomb_y][20 * bomb_x + 20] = '-';
/*
	if (map[20 * bomb_y - 20][20 * bomb_x] == '6')
	{
		forest_fire_direction = 1;
		hthread13 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)forest, NULL, 0, &ThreadID);	
	}
	if (map[20 * bomb_y + 20][20 * bomb_x] == '6')
	{
		forest_fire_direction = 2;
		hthread13 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)forest, NULL, 0, &ThreadID);
	}
	if (map[20 * bomb_y][20 * bomb_x - 20] == '6')
	{
		forest_fire_direction = 3;
		hthread13 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)forest, NULL, 0, &ThreadID);
	}
	if (map[20 * bomb_y][20 * bomb_x + 20] == '6')
	{
		forest_fire_direction = 4;
		hthread13 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)forest, NULL, 0, &ThreadID);
	}*/


	//炸弹第一批图
	putimage(20 * bomb_x, 20 * bomb_y, &bomb_mid_1);
	if (map[20 * bomb_y - 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y - 20, &bomb_side_w_1);
	if (map[20 * bomb_y + 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y + 20, &bomb_side_s_1);
	if (map[20 * bomb_y][20 * bomb_x - 20] == '-')
		putimage(20 * bomb_x - 20, 20 * bomb_y, &bomb_side_a_1);
	if (map[20 * bomb_y][20 * bomb_x + 20] == '-')
		putimage(20 * bomb_x + 20, 20 * bomb_y, &bomb_side_d_1);
	player_bomb_death();
	enemy_bomb_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
	enemy_bomb_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
	enemy_bomb_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
	enemy_bomb_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
	enemy_bomb_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
	enemy_bomb_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
	enemy_bomb_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
	enemy_bomb_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
	enemy_bomb_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
	enemy_bomb_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
	Sleep(100);

	//炸弹第二批图
	putimage(20 * bomb_x, 20 * bomb_y, &bomb_mid_2);
	if (map[20 * bomb_y - 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y - 20, &bomb_side_w_2);
	if (map[20 * bomb_y + 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y + 20, &bomb_side_s_2);
	if (map[20 * bomb_y][20 * bomb_x - 20] == '-')
		putimage(20 * bomb_x - 20, 20 * bomb_y, &bomb_side_a_2);
	if (map[20 * bomb_y][20 * bomb_x + 20] == '-')
		putimage(20 * bomb_x + 20, 20 * bomb_y, &bomb_side_d_2);
	player_bomb_death();
	enemy_bomb_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
	enemy_bomb_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
	enemy_bomb_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
	enemy_bomb_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
	enemy_bomb_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
	enemy_bomb_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
	enemy_bomb_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
	enemy_bomb_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
	enemy_bomb_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
	enemy_bomb_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
	Sleep(100);

	//炸弹第三批图
	putimage(20 * bomb_x, 20 * bomb_y, &bomb_mid_3);
	if (map[20 * bomb_y - 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y - 20, &bomb_side_w_3);
	if (map[20 * bomb_y + 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y + 20, &bomb_side_s_3);
	if (map[20 * bomb_y][20 * bomb_x - 20] == '-')
		putimage(20 * bomb_x - 20, 20 * bomb_y, &bomb_side_a_3);
	if (map[20 * bomb_y][20 * bomb_x + 20] == '-')
		putimage(20 * bomb_x + 20, 20 * bomb_y, &bomb_side_d_3);
	player_bomb_death();
	enemy_bomb_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
	enemy_bomb_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
	enemy_bomb_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
	enemy_bomb_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
	enemy_bomb_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
	enemy_bomb_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
	enemy_bomb_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
	enemy_bomb_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
	enemy_bomb_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
	enemy_bomb_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
	Sleep(100);

	//炸弹第四批图
	putimage(20 * bomb_x, 20 * bomb_y, &bomb_mid_4);
	if (map[20 * bomb_y - 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y - 20, &bomb_side_w_4);
	if (map[20 * bomb_y + 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y + 20, &bomb_side_s_4);
	if (map[20 * bomb_y][20 * bomb_x - 20] == '-')
		putimage(20 * bomb_x - 20, 20 * bomb_y, &bomb_side_a_4);
	if (map[20 * bomb_y][20 * bomb_x + 20] == '-')
		putimage(20 * bomb_x + 20, 20 * bomb_y, &bomb_side_d_4);
	player_bomb_death();
	enemy_bomb_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
	enemy_bomb_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
	enemy_bomb_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
	enemy_bomb_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
	enemy_bomb_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
	enemy_bomb_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
	enemy_bomb_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
	enemy_bomb_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
	enemy_bomb_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
	enemy_bomb_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
	Sleep(100);

	//炸弹第五批图
	putimage(20 * bomb_x, 20 * bomb_y, &bomb_mid_5);
	if (map[20 * bomb_y - 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y - 20, &bomb_side_w_5);
	if (map[20 * bomb_y + 20][20 * bomb_x] == '-')
		putimage(20 * bomb_x, 20 * bomb_y + 20, &bomb_side_s_5);
	if (map[20 * bomb_y][20 * bomb_x - 20] == '-')
		putimage(20 * bomb_x - 20, 20 * bomb_y, &bomb_side_a_5);
	if (map[20 * bomb_y][20 * bomb_x + 20] == '-')
		putimage(20 * bomb_x + 20, 20 * bomb_y, &bomb_side_d_5);
	player_bomb_death();
	enemy_bomb_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
	enemy_bomb_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
	enemy_bomb_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
	enemy_bomb_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
	enemy_bomb_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
	enemy_bomb_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
	enemy_bomb_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
	enemy_bomb_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
	enemy_bomb_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
	enemy_bomb_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
	Sleep(100);

	//炸弹结束重置废墟
	putimage(20 * bomb_x, 20 * bomb_y, &background);
	map[20 * bomb_y][20 * bomb_x] = '0';
	if (map[20 * bomb_y - 20][20 * bomb_x] == '-')
	{
		putimage(20 * bomb_x, 20 * bomb_y - 20, &background);
		map[20 * bomb_y - 20][20 * bomb_x] = '0';
	}
	if (map[20 * bomb_y + 20][20 * bomb_x] == '-')
	{
		putimage(20 * bomb_x, 20 * bomb_y + 20, &background);
		map[20 * bomb_y + 20][20 * bomb_x] = '0';
	}
	if (map[20 * bomb_y][20 * bomb_x - 20] == '-')
	{
		putimage(20 * bomb_x - 20, 20 * bomb_y, &background);
		map[20 * bomb_y][20 * bomb_x - 20] = '0';
	}
	if (map[20 * bomb_y][20 * bomb_x + 20] == '-')
	{
		putimage(20 * bomb_x + 20, 20 * bomb_y, &background);
		map[20 * bomb_y][20 * bomb_x + 20] = '0';
	}

	bombs++;
	generated = 1;
	return 0;
}

DWORD _stdcall flame_show(LPVOID lpParameter)
{
	int i;
	while (!bullets)
	{
		for (i = 1; i <= 4; i++)										//循环播放第一张炸弹图片一秒，为了使玩家放置炸弹后移动时，
		{														//炸弹被盖住而使用此循环
			putimage(20 * flame_x, 20 * flame_y, &flame1);
			if (map[20 * flame_y][20 * flame_x] == 1)
				map[20 * flame_y][20 * flame_x] = 0;
			Sleep(30);
			player_flame_death();
			enemy_flame_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
			enemy_flame_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
			enemy_flame_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
			enemy_flame_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
			enemy_flame_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
			enemy_flame_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
			enemy_flame_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
			enemy_flame_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
			enemy_flame_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
			enemy_flame_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
			dany_flame_power();
		}
		for (i = 1; i <= 4; i++)										//循环播放第二张炸弹图片一秒，
		{
			putimage(20 * flame_x, 20 * flame_y, &flame2);
			if (map[20 * flame_y][20 * flame_x] == 1)
				map[20 * flame_y][20 * flame_x] = 0;
			Sleep(30);
			player_flame_death();
			enemy_flame_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
			enemy_flame_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
			enemy_flame_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
			enemy_flame_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
			enemy_flame_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
			enemy_flame_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
			enemy_flame_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
			enemy_flame_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
			enemy_flame_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
			enemy_flame_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
			dany_flame_power();
		}
		for (i = 1; i <= 4; i++)										//循环播放第三张炸弹图片一秒，
		{
			putimage(20 * flame_x, 20 * flame_y, &flame3);
			if (map[20 * flame_y][20 * flame_x] == 1)
				map[20 * flame_y][20 * flame_x] = 0;
			Sleep(30);
			player_flame_death();
			enemy_flame_death(&enemy_1x, &enemy_1y, &enemy_1_life, &enemy_1_dead_time);
			enemy_flame_death(&enemy_2x, &enemy_2y, &enemy_2_life, &enemy_2_dead_time);
			enemy_flame_death(&enemy_3x, &enemy_3y, &enemy_3_life, &enemy_3_dead_time);
			enemy_flame_death(&enemy_4x, &enemy_4y, &enemy_4_life, &enemy_4_dead_time);
			enemy_flame_death(&enemy_5x, &enemy_5y, &enemy_5_life, &enemy_5_dead_time);
			enemy_flame_death(&enemy_6x, &enemy_6y, &enemy_6_life, &enemy_6_dead_time);
			enemy_flame_death(&enemy_7x, &enemy_7y, &enemy_7_life, &enemy_7_dead_time);
			enemy_flame_death(&enemy_8x, &enemy_8y, &enemy_8_life, &enemy_8_dead_time);
			enemy_flame_death(&enemy_9x, &enemy_9y, &enemy_9_life, &enemy_9_dead_time);
			enemy_flame_death(&enemy_10x, &enemy_10y, &enemy_10_life, &enemy_10_dead_time);
			dany_flame_power();
		}
	}

	mciSendString("close dracarys.wav", NULL, 0, 0);
	mciSendString("open dracarys.wav", NULL, 0, 0);
	mciSendString("play dracarys.wav", NULL, 0, 0);
	return 0;
}

void operate()
{	///////////////////player///////////////////
	if (GetKeyState(0x53) < 0)//down
	{
		player_face = 0;
		if (map[player_y * 10 + 20][player_x * 10] == '-' ||
			player_y <= HEIGHT * 2 &&
			map[player_y * 10 + 20][player_x * 10] == '0' &&
			map[player_y * 10 + 20][player_x * 10 - 10] == '0' &&
			map[player_y * 10 + 20][player_x * 10 + 10] == '0')	//map[player_y * 10 + 20][player_x * 10] == '-'若玩家撞到内部的石头，则在原地行走
		{
			player_y++;
			putimage(player_x * 10, player_y * 10 - 10, &background);									// 在坐标 (m, n-10) 位置显示 background
		}
		//if (map[player_y * 10 + 20][player_x * 10] == '4')
			//player_life--;
		putimage(player_x * 10, player_y * 10, &player_s2);											// 在坐标 (m, n) 位置显示 player_s2
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_s3);											// 在坐标 (m, n) 位置显示 player_player_s3
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_s1);											// 在坐标 (m, n) 位置显示 player_s1 
		Sleep(sleep_player);
		face_y = 1;
	}
	if (GetKeyState(0x57) < 0)//left
	{
		player_face =1;
		if (map[player_y * 10 - 20][player_x * 10] == '-' ||
			player_y > 0 &&
			map[player_y * 10 - 20][player_x * 10] == '0' &&
			map[player_y * 10 - 20][player_x * 10 + 10] == '0' &&
			map[player_y * 10 - 20][player_x * 10 - 10] == '0')							//若玩家撞到内部的石头，则在原地行走
		{
			player_y--;
			putimage(player_x * 10, player_y * 10 + 10, &background);								// 在坐标 (m, n-10) 位置显示 background
		}
		//if (map[player_y * 10][player_x * 10 - 20] == '4')
			//player_life--;
		putimage(player_x * 10, player_y * 10, &player_w2);											// 在坐标 (m, n) 位置显示 player_w2
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_w3);											// 在坐标 (m, n) 位置显示 player_w3
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_w1);											// 在坐标 (m, n) 位置显示 player_w1 
		Sleep(sleep_player);
		face_y = -1;
	}
	if (GetKeyState(0x41) < 0)//left
	{
		player_face = 2;
		if (map[player_y * 10][player_x * 10 - 20] == '-' ||
			player_x > 0 &&
			map[player_y * 10][player_x * 10 - 20] == '0' &&
			map[player_y * 10 + 10][player_x * 10 - 20] == '0' &&
			map[player_y * 10 - 10][player_x * 10 - 20] == '0')										//若玩家撞到内部的石头，则在原地行走
		{
			player_x--;
			putimage(player_x * 10 + 10, player_y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
		}
		//if (map[player_y * 10][player_x * 10 - 20] == '4')
			//player_life--;
		putimage(player_x * 10, player_y * 10, &player_a2);											// 在坐标 (m, n) 位置显示 player_w2
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_a3);											// 在坐标 (m, n) 位置显示 player_w3
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_a1);											// 在坐标 (m, n) 位置显示 player_w1 
		Sleep(sleep_player);
		face_x = -1;
	}
	if (GetKeyState(0x44) < 0)//right
	{
		player_face = 3;
		if (map[player_y * 10][player_x * 10 + 20] == '-' ||
			player_x <= WIDTH * 2 - 3 &&
			map[player_y * 10][player_x * 10 + 20] == '0' &&
			map[player_y * 10 + 10][player_x * 10 + 20] == '0' &&
			map[player_y * 10 - 10][player_x * 10 + 20] == '0')											//若玩家撞到内部的石头，则在原地行走
		{
			player_x++;
			putimage(player_x * 10 - 10, player_y * 10, &background);									// 在坐标 (m, n-10) 位置显示 background
		}
		//if (map[player_y * 10][player_x * 10 + 20] == '4')
			//player_life--;
		putimage(player_x * 10, player_y * 10, &player_d2);											// 在坐标 (m, n) 位置显示 player_s2
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_d3);											// 在坐标 (m, n) 位置显示 player_player_s3
		Sleep(sleep_player);
		putimage(player_x * 10, player_y * 10, &player_d1);											// 在坐标 (m, n) 位置显示 player_s1 
		Sleep(sleep_player);
		face_x = 1;
	}
	if (GetKeyState(0x20) < 0)
	{
		switch (eyes)
		{
		case 0:
			if (bombs > 0)
			{
				bombs--;
				if (player_x % 2)
					bomb_x = (player_x + face_x) / 2;
				else
					bomb_x = player_x / 2;
				if (player_y % 2)
					bomb_y = (player_y + face_y) / 2;
				else
					bomb_y = player_y / 2;
				hthread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)bomb_show, NULL, 0, &ThreadID);
				//执行线程1
			}
			break;
		case 1:
			if (carrys > 0)
			{
				carrys--;
				if (player_x % 2)
					carry_x_temp = (player_x + face_x) / 2;
				else
					carry_x_temp = player_x / 2;

				if (player_y % 2)
					carry_y_temp = (player_y + face_y) / 2;
				else
					carry_y_temp = player_y / 2;

				switch (player_face)
				{
				case 0:
				{
					carry_x = carry_x_temp;
					carry_y = carry_y_temp + 1;
					break;
				}
				case 1:
				{
					carry_x = carry_x_temp;
					carry_y = carry_y_temp - 1;
					break;
				}
				case 2:
				{
					carry_x = carry_x_temp - 1;
					carry_y = carry_y_temp;
					break;
				}
				case 3:
				{
					carry_x = carry_x_temp + 1;
					carry_y = carry_y_temp;
					break;
				}
				}
				hthread17= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)brick_show, NULL, 0, &ThreadID);
			}
			break;
		}
	}
}

DWORD _stdcall countDown(LPVOID lpParameter)
{
	setcolor(WHITE);
	settextstyle(20, 0, _T("Times Nes Roman"));

	int game_end = time(NULL)+countdown;
	char countdown_char[5];//声明数组，用来存放字符串

	while (!win_fail)
	{
		if (countdown <= 0)
		{
			dany_life = 0;
			player_life = 0;
		}
		if ((game_end != (time(NULL) + countdown))&&(countdown>0))
		{
			countdown = game_end - time(NULL);
			sprintf_s(countdown_char, "%d", countdown);//将整形a转换成字符串
			setbkmode(OPAQUE);
			outtextxy((WIDTH - 2) * 20, 0, countdown_char);
		}
	}
	return 0;
}

void load_image()
{
	loadimage(&background, "background.jpg");			    // 读取图片到 stone 对象中
	loadimage(&stone, "stone.jpg");				            // 读取图片到 stone 对象中
	loadimage(&brick, "brick.jpg");				            // 读取图片到 brick对象中
	loadimage(&door, "door_t.jpg");
	loadimage(&water, "water.jpg");
	//loadimage(&red, "red.jpg");
	loadimage(&brown, "brown_03.jpg");
	loadimage(&trees, "trees.jpg");
	loadimage(&orange, "orange.jpg");


	loadimage(&player_s1, "player_s1.jpg");					// 读取图片到 player_s1 对象中
	loadimage(&player_s2, "player_s2.jpg");					// 读取图片到 player_s2 对象中
	loadimage(&player_s3, "player_s3.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&player_w1, "player_w1.jpg");					// 读取图片到 player_w1 对象中
	loadimage(&player_w2, "player_w2.jpg");					// 读取图片到 player_w2 对象中
	loadimage(&player_w3, "player_w3.jpg");					// 读取图片到 player_w3 对象中
	loadimage(&player_a1, "player_a1.jpg");					// 读取图片到 player_w1 对象中
	loadimage(&player_a2, "player_a2.jpg");					// 读取图片到 player_w2 对象中
	loadimage(&player_a3, "player_a3.jpg");					// 读取图片到 player_w3 对象中
	loadimage(&player_d1, "player_d1.jpg");					// 读取图片到 player_s1 对象中
	loadimage(&player_d2, "player_d2.jpg");					// 读取图片到 player_s2 对象中
	loadimage(&player_d3, "player_d3.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&bomb_burning1, "bomb_burning1.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_burning2, "bomb_burning2.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_burning3, "bomb_burning3.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&bomb_mid_1, "bomb_mid_1.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_mid_2, "bomb_mid_2.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_mid_3, "bomb_mid_3.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_mid_4, "bomb_mid_4.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_mid_5, "bomb_mid_5.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&bomb_side_a_1, "bomb_side_a_1.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_a_2, "bomb_side_a_2.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_a_3, "bomb_side_a_3.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_a_4, "bomb_side_a_4.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_a_5, "bomb_side_a_5.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&bomb_side_w_1, "bomb_side_w_1.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_w_2, "bomb_side_w_2.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_w_3, "bomb_side_w_3.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_w_4, "bomb_side_w_4.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_w_5, "bomb_side_w_5.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&bomb_side_d_1, "bomb_side_d_1.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_d_2, "bomb_side_d_2.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_d_3, "bomb_side_d_3.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_d_4, "bomb_side_d_4.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_d_5, "bomb_side_d_5.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&bomb_side_s_1, "bomb_side_s_1.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_s_2, "bomb_side_s_2.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_s_3, "bomb_side_s_3.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_s_4, "bomb_side_s_4.jpg");					// 读取图片到 player_s3 对象中
	loadimage(&bomb_side_s_5, "bomb_side_s_5.jpg");					// 读取图片到 player_s3 对象中

	loadimage(&enemy_s1, "enemy_s1.jpg");
	loadimage(&enemy_s2, "enemy_s2.jpg");
	loadimage(&enemy_s3, "enemy_s3.jpg");
	loadimage(&enemy_w1, "enemy_w1.jpg");
	loadimage(&enemy_w2, "enemy_w2.jpg");
	loadimage(&enemy_w3, "enemy_w3.jpg");
	loadimage(&enemy_a1, "enemy_a1.jpg");
	loadimage(&enemy_a2, "enemy_a2.jpg");
	loadimage(&enemy_a3, "enemy_a3.jpg");
	loadimage(&enemy_d1, "enemy_d1.jpg");
	loadimage(&enemy_d2, "enemy_d2.jpg");
	loadimage(&enemy_d3, "enemy_d3.jpg");

	loadimage(&dany_s1, "dany_s1.jpg");
	loadimage(&dany_s2, "dany_s2.jpg");
	loadimage(&dany_s3, "dany_s3.jpg");
	loadimage(&dany_w1, "dany_w1.jpg");
	loadimage(&dany_w2, "dany_w2.jpg");
	loadimage(&dany_w3, "dany_w3.jpg");
	loadimage(&dany_a1, "dany_a1.jpg");
	loadimage(&dany_a2, "dany_a2.jpg");
	loadimage(&dany_a3, "dany_a3.jpg");
	loadimage(&dany_d1, "dany_d1.jpg");
	loadimage(&dany_d2, "dany_d2.jpg");
	loadimage(&dany_d3, "dany_d3.jpg");

	loadimage(&flame1, "flame1.jpg");
	loadimage(&flame2, "flame2.jpg");
	loadimage(&flame3, "flame3.jpg");

	loadimage(&jlu, "jlu.jpg");
	loadimage(&physics, "physics1.jpg");
	loadimage(&daenerys, "daenerys.jpg");
	loadimage(&edward, "edward.jpg");

	loadimage(&eye1, "eye1.jpg");
	loadimage(&eye2, "eye2.jpg");
	loadimage(&eye3, "eye3.jpg");
	loadimage(&eye4, "eye4.jpg");
}

int main()
{
	load_image();
	//InitializeMap();
	genmap();
	//enemyGenerate();
	enemy_generate(&enemy_1x, &enemy_1y, &enemy_1_life);
	enemy_generate(&enemy_2x, &enemy_2y, &enemy_2_life);
	enemy_generate(&enemy_3x, &enemy_3y, &enemy_3_life);
	enemy_generate(&enemy_4x, &enemy_4y, &enemy_4_life);
	enemy_generate(&enemy_5x, &enemy_5y, &enemy_5_life);
	enemy_generate(&enemy_6x, &enemy_6y, &enemy_6_life);
	enemy_generate(&enemy_7x, &enemy_7y, &enemy_7_life);
	enemy_generate(&enemy_8x, &enemy_8y, &enemy_8_life);
	enemy_generate(&enemy_9x, &enemy_9y, &enemy_9_life);
	enemy_generate(&enemy_10x, &enemy_10y, &enemy_10_life);
	hthread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy1_move, NULL, 0, &ThreadID);
	hthread3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy2_move, NULL, 0, &ThreadID);
	hthread4 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy3_move, NULL, 0, &ThreadID);
	hthread5 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy4_move, NULL, 0, &ThreadID);
	hthread6 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy5_move, NULL, 0, &ThreadID);
	hthread7 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy6_move, NULL, 0, &ThreadID);
	hthread8 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy7_move, NULL, 0, &ThreadID);
	hthread9 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy8_move, NULL, 0, &ThreadID);
	hthread10 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy9_move, NULL, 0, &ThreadID);
	hthread11 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)enemy10_move, NULL, 0, &ThreadID);

	hthread15 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)flame_show, NULL, 0, &ThreadID);

	hthread14 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dany_move, NULL, 0, &ThreadID);

	hthread16 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)eye_show, NULL, 0, &ThreadID);

	hthread19 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)countDown, NULL, 0, &ThreadID);

	while (1)//(player_life)
	{
		enemy_reborn();
		
		if (player_life)
			operate();
		else
		{
			player_x = dany_x;
			player_y = dany_y;
		}
		if (!dany_life)
		{
			dany_x = player_x;
			dany_y = player_y;
		}

		if (dany_life+player_life==0)
		{
			fail();
			break;
		}
		if (enemy_1_life + enemy_2_life + enemy_3_life + enemy_4_life + enemy_5_life + \
			enemy_6_life + enemy_7_life + enemy_8_life + enemy_9_life + enemy_10_life == 0)
		{
			win();
			break;
		}
	}
	//CloseHandle(hthread1);

	//_getch();
}