#include "GameClass.h"
/////Status Define

#define MENU_INIT		   0x01
#define MENU_LOOP	       0x02
#define SINGLE_MODE_INIT   0x03
#define SINGLE_MODE_LOOP   0x04
#define SINGLE_MODE_FAILED 0x05
#define SLEEP_MODE         0x06
#define EXIT_GAME          0x07

#define MULTI_MODE         0x08

#define WIDTH  800
#define HEIGH  600
//////Global

USHORT Status;
GameFrame* MainFrame;//主程序框架
RECT Win_Rect = {0,0,800,600};
RECT Cell_Rect = {0,0,40,40};
Port Src_Port,Dest_Port;
POINT Select_Point = {0,0};
POINT pos_1,pos_2;
POINT Num_Point = {100,490};
int Mouse_Status = 1;
int int_x,int_y;
int score;
char * num_str;
DWORD start_tick;

RECT Convert_WinRect(RECT rect_temp);

int Game_Main(void *parms = NULL, int num_parms = 0)
{
	if (KEY_DOWN(VK_ESCAPE))
		SendMessage(hwnd_app,WM_CLOSE,0,0);

	int rimid = 0;

	switch(Status)
	{
	case MENU_INIT:
		{
			MainFrame->Init_Menu();
			Status = MENU_LOOP;
		}break;

	case MENU_LOOP:
		{
			MainFrame->Draw_Menu(Menu_ID_Background);
			MainFrame->Draw_Menu(Menu_ID_Button);

			lpddsprimary->Blt(&Convert_WinRect(Win_Rect),lpddsoff,NULL,DDBLT_WAIT,NULL);

			if(MainFrame->LButtonClick_InSpirit(MainFrame->Sp_Button[0]))
				Status = SINGLE_MODE_INIT;
			if(MainFrame->LButtonClick_InSpirit(MainFrame->Sp_Button[1]))
				Status = SINGLE_MODE_INIT;
			if(MainFrame->LButtonClick_InSpirit(MainFrame->Sp_Button[2]))
				Status = SINGLE_MODE_INIT;
			if(MainFrame->LButtonClick_InSpirit(MainFrame->Sp_Button[3]))
				Status = EXIT_GAME;
		}break;

	case SINGLE_MODE_INIT:
		{
			MainFrame->Single_Mode_Init();
			Status = SINGLE_MODE_LOOP;
			score = 0;
			num_str = new char[9];
			strcpy(num_str,"00000000");
		}break;

	case SINGLE_MODE_LOOP:
		{
			if (MainFrame->IsExit()) 
			{
				Status = MENU_LOOP;
				break;
			}
			MainFrame->Draw_Region();
			MainFrame->Draw_Block();
			MainFrame->Draw_Number(Num_Point,num_str);
			MainFrame->Draw_Timer();

			if(Mouse_Status == 1)
			MainFrame->Draw_Rim(0);
			else 
			MainFrame->Draw_Rim(1);

			if(MainFrame->dolink == TRUE && GetTickCount() - start_tick < 330)
				MainFrame->Blt_LinkSur(lpddsoff);
			else MainFrame->Stop_Link();

			if(MainFrame->Select_Pos(&Select_Point))
			{
				if(Mouse_Status == 1 && !MainFrame->Check_Select_Null(Select_Point))//第一下点击鼠标
				{
					MainFrame->rim_pos[0] = Select_Point;
					MainFrame->Set_Port(&Src_Port,MainFrame->rim_pos[0]);
					Mouse_Status = -Mouse_Status;
				}
				else if(Mouse_Status == -1 && !MainFrame->Check_Select_Null(Select_Point))//第二下
				{
					MainFrame->rim_pos[1] = Select_Point;
					MainFrame->Set_Port(&Dest_Port,MainFrame->rim_pos[1]);
					Mouse_Status = -Mouse_Status;
				}
				else
				{
					MainFrame->Reset_Rim();
				}
			}
			lpddsprimary->Blt(&Convert_WinRect(Win_Rect),lpddsoff,NULL,DDBLT_WAIT,NULL);


			//方块的消去事件
			if(MainFrame->Select_Pos(NULL))
			{
				if(MainFrame->rim_pos[0].x != -1 && MainFrame->rim_pos[0].y != -1 &&
				   MainFrame->rim_pos[1].x != -1 && MainFrame->rim_pos[1].y != -1 &&
				   MainFrame->Check_Linked(Src_Port,Src_Port,Dest_Port))//检测可连
				{
					pos_1.x = MainFrame->rim_pos[0].x;
					pos_1.y = MainFrame->rim_pos[0].y;
					pos_2.x = MainFrame->rim_pos[1].x;
					pos_2.y = MainFrame->rim_pos[1].y;

					MainFrame->Set_Array__(pos_1,-1);//重写数组
					MainFrame->Set_Array__(pos_2,-1);
					MainFrame->Draw_LinkSur();
					MainFrame->Start_Link();
					start_tick = GetTickCount();

					score += 15;
					_itoa(score,num_str,10);

					for (int index=0;index<MainFrame->link_list.size();index++)
					{
						int_x = MainFrame->link_list.back().p_x;
						int_y = MainFrame->link_list.back().p_y;
					}
					MainFrame->Reset_Rim();
				}
				MainFrame->link_list.clear();
			}

		}break;

	case SINGLE_MODE_FAILED:
		{

		}break;
	case SLEEP_MODE:
		{

		}break;
	case EXIT_GAME:
		{
			SendMessage(hwnd_app,WM_CLOSE,0,0);
		}
	default:break;
	}
	//Sleep(33);

	return(1);

} // end Game_Main

////////////////////////////////////////////////////////////

int Game_Init(void *parms = NULL, int num_parms = 0)
{
	Status = MENU_INIT;
	MainFrame = new GameFrame(800,600);
	Window_Adjust(800,600,0,0);
	lpddsoff = DDraw_Create_Surface(800,600);

	return(1);

} // end Game_Init

/////////////////////////////////////////////////////////////



int Game_Shutdown(void *parms = NULL, int num_parms = 0)
{
	DDraw_Shutdown();
	delete MainFrame;
	delete num_str;
	return(1);

} // end Game_Shutdown

RECT Convert_WinRect(RECT rect_temp)
{
	int width_temp = rect_temp.right - rect_temp.left,
		height_temp = rect_temp.bottom - rect_temp.top;

	POINT point_temp={rect_temp.left,rect_temp.top};
	ClientToScreen(hwnd_app,&point_temp);

	SetRect(&rect_temp,point_temp.x,point_temp.y,point_temp.x+width_temp,point_temp.y+height_temp);
	return rect_temp;
}