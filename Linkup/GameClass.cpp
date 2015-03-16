#include "GameClass.h"

LPDIRECTDRAWSURFACE7 lpddsoff =NULL;

GameFrame *GameFrame::p_GFP = NULL;//初始化静态成员p_GFP

GameFrame::GameFrame(int win_width,int win_heigth)
{
	p_GFP = this;
	DDraw_Init(win_width,win_heigth,32,1);

	//=======初始化位图

	for(int index=0;index<26;index++)
	{
		SpiritBMP_1[index] = NULL;
		SpiritBMP_2[index] = NULL;
	}
	MainMenuBMP = NULL;
	BackgroundBMP = NULL;
	for(int index=0;index<4;index++)
	{
		ButtonBMP_1[index] = NULL;
		ButtonBMP_2[index] = NULL;
	}

	TimerBMP = NULL;
	for(int index=0;index<10;index++)
	{
		NumberBMP[index] = NULL;
	}
	for(int index=0;index<6;index++)
	{
		Link_1BMP[index] = NULL;
		Link_2BMP[index] = NULL;
	}
	rimBMP = NULL;

	//=========初始化部分变量
	rim_pos[0].x = -1;
	rim_pos[1].x = -1;
	rim_pos[0].y = -1;
	rim_pos[1].y = -1;

	tick_count = 0;
	tickperpix = 0;
	timer_set = 0;

	for (int pindex=0;pindex<12;pindex++)
	{
		for (int index=0;index<18;index++)
		{
			Array[pindex][index] = -1;
		}
	}

	DDRAW_INIT_STRUCT(ddbltfx_black);
	ddbltfx_black.ddckSrcColorkey.dwColorSpaceHighValue = RGB(0,0,0);
	ddbltfx_black.ddckSrcColorkey.dwColorSpaceLowValue  = RGB(0,0,0);
	DDRAW_INIT_STRUCT(ddbltfx_white);
	ddbltfx_white.ddckSrcColorkey.dwColorSpaceHighValue = RGB(255,255,255);
	ddbltfx_white.ddckSrcColorkey.dwColorSpaceLowValue  = RGB(255,255,255);
	ddbltfx_white.dwFillColor = RGB(255,255,255);
}

GameFrame::~GameFrame()
{
	if(MainMenuBMP !=NULL)
	delete MainMenuBMP;

	for(int index=0;index<26;index++)
	{
		
		if(SpiritBMP_1[index] !=NULL)
			delete SpiritBMP_1[index];
		if(SpiritBMP_2[index] !=NULL)
			delete SpiritBMP_2[index];
	}

	for(int index=0;index<4;index++)
	{

		if(ButtonBMP_1[index] !=NULL)
			delete ButtonBMP_1[index];
		if(ButtonBMP_2[index] !=NULL)
			delete ButtonBMP_2[index];
	}

	if(BackgroundBMP != NULL)
	delete BackgroundBMP;

	if(rimBMP != NULL)
		delete rimBMP;

	for(int index=0;index<6;index++)
	{

		if(Link_1BMP[index] !=NULL)
			delete Link_1BMP[index];
		if(Link_2BMP[index] !=NULL)
			delete Link_2BMP[index];
	}

		if(TimerBMP !=NULL)
			delete TimerBMP;

	for(int index=0;index<10;index++)
	{

		if(NumberBMP[index] !=NULL)
			delete NumberBMP[index];
	}

}

GameFrame* GameFrame::GetGameFramePoint()
{
	return p_GFP;
}

LRESULT GameFrame::ProcEvent(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
PAINTSTRUCT		ps;		
HDC				hdc;	

if(p_GFP != NULL)
{
	Gf_msg = msg;//获取消息供框架使用
	Gf_lparam = lparam;//获取参数
}

switch(msg)
{	
case WM_CREATE: 
	{
		return(0);
	} break;

case WM_PAINT: 
	{
		hdc = BeginPaint(hwnd,&ps);	 
		EndPaint(hwnd,&ps);

		return(0);
	} break;

case WM_DESTROY: 
	{
		PostQuitMessage(0);

		return(0);
	} break;

default:break;
}

return (DefWindowProc(hwnd, msg, wparam, lparam));
}

BOOL GameFrame::MouseMove(RECT rect_temp)
{
	if(Gf_msg != WM_MOUSEMOVE) return FALSE;
	POINT point_temp = {LOWORD(Gf_lparam),HIWORD(Gf_lparam)};

	if(PtInRect(&rect_temp,point_temp))
		return TRUE;
	else 
		return FALSE;
}

BOOL GameFrame::MouseMoveInSpirit(Spirit sp_temp)
{
	if(MouseMove(sp_temp.Get_Rect()))
		return TRUE;
	else 
		return FALSE;
}

BOOL GameFrame::LButton_On_Click(RECT rect_temp)
{
	if(Gf_msg == WM_LBUTTONDOWN)
	{
		POINT point_temp = {LOWORD(Gf_lparam),HIWORD(Gf_lparam)};

		if(PtInRect(&rect_temp,point_temp))
			return TRUE;
	}
	else
		return FALSE;
}

BOOL GameFrame::LButtonClick_InSpirit(Spirit sp_temp)
{
	if(LButton_On_Click(sp_temp.Get_Rect()))
		return TRUE;
	else
		return FALSE;
}

////////////////////////////////////////////////////////////////////





int GameFrame::Init_Menu()
{
	for(int index=0;index<4;index++)
		{
			ButtonBMP_1[index] = new BitmapSur();
			ButtonBMP_2[index] = new BitmapSur();
		}

	if(!(MainMenuBMP = Load_For_BitmapSur(800,600,"Res\\Menu.bmp")))
		return 0;
	if(!(ButtonBMP_1[0] = Load_For_BitmapSur(144,35,"Res\\Single.bmp")))
		return 0;
	if(!(ButtonBMP_2[0] = Load_For_BitmapSur(144,35,"Res\\Single_Sprak.bmp")))
		return 0;
	if(!(ButtonBMP_1[1] = Load_For_BitmapSur(144,35,"Res\\Multigame.bmp")))
		return 0;
	if(!(ButtonBMP_2[1] = Load_For_BitmapSur(144,35,"Res\\Multigame_Sprak.bmp")))
		return 0;
	if(!(ButtonBMP_1[2] = Load_For_BitmapSur(144,35,"Res\\Rank.bmp")))
		return 0;
	if(!(ButtonBMP_2[2] = Load_For_BitmapSur(144,35,"Res\\Rank_Sprak.bmp")))
		return 0;
	if(!(ButtonBMP_1[3] = Load_For_BitmapSur(144,35,"Res\\Exit.bmp")))
		return 0;
	if(!(ButtonBMP_2[3] = Load_For_BitmapSur(144,35,"Res\\Exit_Sprak.bmp")))
		return 0;
		
	RECT sp_rect = {320,320,464,355};
	for(int index=0;index<4;index++)
	{
		Sp_Button[index].Create_Spirit(Button_Single + index,sp_rect);
		Sp_Button[index].Load_Look(ButtonBMP_1[index],0);
		Sp_Button[index].Create_Spirit(Button_Single + index,sp_rect);
		Sp_Button[index].Load_Look(ButtonBMP_2[index],1);
		sp_rect.top += 50;
		sp_rect.bottom += 50;
	}
	return 1;
}

int GameFrame::Draw_Menu(int draw_id)
{

	RECT menu_back = {0,0,800,600};
	

	switch(draw_id)
	{
	case Menu_ID_Background:
		{
			Draw_BmpSur(lpddsoff,menu_back,*MainMenuBMP);

		}break;
	case Menu_ID_Button:
		{
			for(int index=0;index<4;index++)
			{
				if(MouseMoveInSpirit(Sp_Button[index]))
					Sp_Button[index].Draw_Spirit(lpddsoff,ddbltfx_white.ddckSrcColorkey,0,1);
				else
					Sp_Button[index].Draw_Spirit(lpddsoff,ddbltfx_white.ddckSrcColorkey,0,0);
			}
				
		}break;
	}
	return 1;
}

int GameFrame::Single_Mode_Init()
{
	//=====位图初始化
	int gcell_x=0,gcell_y=0;
	for(int index=0;index<13;index++)
	{
		RECT block_rect = {0,0,40,40};
		SpiritBMP_1[index] = Load_For_BitmapSur(40,40,"Res\\Block.bmp",&block_rect,gcell_x,gcell_y);
		gcell_x++;
	}
	gcell_x = 0;
	gcell_y = 1;
	for(int index=0;index<13;index++)
	{
		RECT block_rect = {0,0,40,40};
		SpiritBMP_1[index+13] = Load_For_BitmapSur(40,40,"Res\\Block.bmp",&block_rect,gcell_x,gcell_y);
		gcell_x++;
	}
	gcell_x = 0;
	gcell_y = 0;
	for(int index=0;index<6;index++)
	{
		RECT block_rect = {0,0,40,40};
		Link_1BMP[index] = Load_For_BitmapSur(40,40,"Res\\line_1.bmp",&block_rect,gcell_x,gcell_y);
		Link_2BMP[index] = Load_For_BitmapSur(40,40,"Res\\line_2.bmp",&block_rect,gcell_x,gcell_y);
		gcell_x++;
	}

	srand((UINT)time(NULL));
	RECT sp_rect = {40,40,80,80};
	int block_style;

	for(int pindex=0;pindex<10;pindex++)
	{
		SetRect(&sp_rect,40,sp_rect.top+40,80,sp_rect.bottom+40);

		for(int index=0;index<16;index+=2)
		{
			block_style = rand()%26;

			SetRect(&sp_rect,sp_rect.left+40,sp_rect.top,sp_rect.right+40,sp_rect.bottom);
			Sp_Block[index+16*pindex].Create_Spirit(block_style,sp_rect);
			Sp_Block[index+16*pindex].Load_Look(SpiritBMP_1[block_style],0);

			SetRect(&sp_rect,sp_rect.left+40,sp_rect.top,sp_rect.right+40,sp_rect.bottom);
			Sp_Block[index+16*pindex+1].Create_Spirit(block_style,sp_rect);
			Sp_Block[index+16*pindex+1].Load_Look(SpiritBMP_1[block_style],0);
		}

	}

	BackgroundBMP = Load_For_BitmapSur(800,600,"Res\\Playing.bmp");
	rimBMP = Load_For_BitmapSur(40,40,"Res\\rim.bmp");

	RECT sp_rect_2 = {0,0,40,40};
	for (int index=0;index<6;index++)
	{
		Sp_Link[index].Create_Spirit(index,sp_rect_2);
		Sp_Link[index].Load_Look(Link_1BMP[index],0);
		Sp_Link[index].Load_Look(Link_2BMP[index],1);
	}

	link_surface = DDraw_Create_Surface(800,600);

	Disrupt_BlockArea();

	NumberBmp_Init();
	TimerBMP = Load_For_BitmapSur(646,13,"Res\\timer.bmp");


	//======部分数值初始化

	timer_set = 20000;

	time_out = FALSE;
	tickperpix = timer_set / TimerBMP->width;
	tick_count = GetTickCount();
	SetRect(&timer_src_len,0,0,TimerBMP->width,TimerBMP->height);
	SetRect(&timer_des_len,0,16,TimerBMP->width,TimerBMP->height+16);

	RECT exit_button = {684,555,796,593};
	Sp_Exit.Create_Spirit(0,exit_button);

	return 1;
}

int GameFrame::NumberBmp_Init()
{
	NumberBMP[0] = Load_For_BitmapSur(40,60,"Res\\num_0.bmp");
	NumberBMP[1] = Load_For_BitmapSur(40,60,"Res\\num_1.bmp");
	NumberBMP[2] = Load_For_BitmapSur(40,60,"Res\\num_2.bmp");
	NumberBMP[3] = Load_For_BitmapSur(40,60,"Res\\num_3.bmp");
	NumberBMP[4] = Load_For_BitmapSur(40,60,"Res\\num_4.bmp");
	NumberBMP[5] = Load_For_BitmapSur(40,60,"Res\\num_5.bmp");
	NumberBMP[6] = Load_For_BitmapSur(40,60,"Res\\num_6.bmp");
	NumberBMP[7] = Load_For_BitmapSur(40,60,"Res\\num_7.bmp");
	NumberBMP[8] = Load_For_BitmapSur(40,60,"Res\\num_8.bmp");
	NumberBMP[9] = Load_For_BitmapSur(40,60,"Res\\num_9.bmp");
	return 1;
}

int GameFrame::Draw_Region()
{
	RECT game_backgro = {0,0,800,600};
	Draw_BmpSur(lpddsoff,game_backgro,*BackgroundBMP);
	return 1;
}

int GameFrame::Draw_Block()
{
	for(int pindex=0;pindex<10;pindex++)
	{
		for(int index=0;index<16;index++)
		{
			if(Array[pindex+1][index+1] != -1)
			Sp_Block[index+pindex*16].Draw_Spirit(lpddsoff,0,0);
		}
	}
	return 1;
}

int GameFrame::Draw_Number(POINT pos_temp,char num_temp[])
{
	int num_len = strlen(num_temp);
	int sub_len = 8 - num_len;
	int num_index;

	RECT num_rect = {pos_temp.x,pos_temp.y,pos_temp.x+40,pos_temp.y+60};

	for (int index=0;index<sub_len;index++)
	{
		Draw_BmpSur(lpddsoff,num_rect,*NumberBMP[0],ddbltfx_white.ddckSrcColorkey);
		num_rect.left  += 40;
		num_rect.right += 40;
	}

	for(int index=0;index<num_len;index++)
	{
		num_index = (int)(num_temp[index]-'0');
		Draw_BmpSur(lpddsoff,num_rect,*NumberBMP[num_index],ddbltfx_white.ddckSrcColorkey);
		num_rect.left  += 40;
		num_rect.right += 40;
	}

	return 1;
}

int GameFrame::Draw_Timer()
{
	if(GetTickCount() - tick_count > tickperpix)
	{
		if (timer_src_len.right - timer_src_len.left != 0)
		{
			timer_src_len.right--;
			timer_des_len.right--;
			tick_count = GetTickCount();
		}
		else time_out = TRUE;
	}
	lpddsoff->Blt(&timer_des_len,TimerBMP->surface,&timer_src_len,DDBLT_WAIT,NULL);
	return 1;
}

int GameFrame::Check_Select_Null(POINT point_temp)
{
	if(Array[point_temp.y+1][point_temp.x+1] == -1)

		return TRUE;
	else 
		return FALSE;
}

int GameFrame::Draw_Rim(int rim_id)
{
	if(rim_pos[rim_id].x != -1 ||
	   rim_pos[rim_id].y != -1)
	{
		int left_temp = 80+rim_pos[rim_id].x*40,
			top_temp  = 80+rim_pos[rim_id].y*40;
		RECT rim_rect = {left_temp,top_temp,left_temp+40,top_temp+40};
		lpddsoff->Blt(&rim_rect,rimBMP->surface,NULL,DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE,&ddbltfx_black);
	}
	return 1;
}

int GameFrame::Reset_Rim()
{
	rim_pos[0].x = -1;
	rim_pos[0].y = -1;
	rim_pos[1].x = -1;
	rim_pos[1].y = -1;
	return 1;
}

int GameFrame::Draw_LinkSur()
{
	list<Port>::const_iterator port_post;
	Port pos;
	int blt_id;
	RECT link_rect;

	Fill_Surface(link_surface,&ddbltfx_white);

	for (port_post=link_list.begin();port_post!=link_list.end();port_post++)
	{
		pos = *port_post;
		if (pos.direct_from == 0)
		{
			if(pos.direct_to == Direct_Left  || pos.direct_to == Direct_Right)
				blt_id = 1;
			else blt_id = 0;
		}
		else 
		if (pos.direct_to == 0)
		{
			if(pos.direct_from == Direct_Left || pos.direct_from == Direct_Right)
				blt_id = 1;
			else blt_id = 0;
		}
		else 
		if (pos.direct_from == -pos.direct_to)
		{
			if(pos.direct_from == Direct_Left || pos.direct_to == Direct_Left)
				blt_id = 1;
			else blt_id = 0;
		}
		else 
		{
			if(pos.direct_from + pos.direct_to == Direct_Left + Direct_Up)
				blt_id = 5;
			if(pos.direct_from + pos.direct_to == Direct_Left + Direct_Down)
				blt_id = 3;
			if(pos.direct_from + pos.direct_to == Direct_Right + Direct_Up)
				blt_id = 4;
			if(pos.direct_from + pos.direct_to == Direct_Right + Direct_Down)
				blt_id = 2;
		}
		link_rect.left    = pos.p_x*40 + 80;
		link_rect.top     = pos.p_y*40 + 80;
		link_rect.right   = pos.p_x*40 + 120;
		link_rect.bottom  = pos.p_y*40 + 120;
		Sp_Link[blt_id].Change_Postion(link_rect);
		Sp_Link[blt_id].Draw_Spirit(link_surface,ddbltfx_white.ddckSrcColorkey,0,1);
	}
	return 1;
}

int GameFrame::Blt_LinkSur(LPDIRECTDRAWSURFACE7 lpdds_temp)
{
	lpdds_temp->Blt(NULL,link_surface,NULL,DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE,&ddbltfx_white);
	return 1;
}

BOOL GameFrame::Select_Pos(PPOINT point_pos)
{
	if(Gf_msg == WM_LBUTTONDOWN)
	{
		if(point_pos == NULL) return TRUE;

		POINT point_temp = {LOWORD(Gf_lparam),HIWORD(Gf_lparam)};
		if(point_temp.x<80||point_temp.y<80||point_temp.x>720||point_temp.y>480)
		{
			rim_pos[0].x = -1;rim_pos[0].y = -1;
			rim_pos[1].x = -1;rim_pos[1].y = -1;
			return FALSE;
		}
		point_temp.x -= 80;
		point_temp.y -= 80;
		point_temp.x /= 40;
		point_temp.y /= 40;
		*point_pos = point_temp;
		return TRUE;
	}
	else
		return FALSE;
}

int GameFrame::Check_Linked(Port current_node,Port src_node,Port dest_node)
{//检测方块是否可连函数
 //current_node必须初始化

	if (src_node.p_x == dest_node.p_x && src_node.p_y == dest_node.p_y)//点同一个方块是无效的
		return FALSE;
	if (Array[src_node.p_y+1][src_node.p_x+1] != Array[dest_node.p_y+1][dest_node.p_x+1])//检测方块外观是否一样
		return FALSE;

	POINT dest_point = {dest_node.p_x,dest_node.p_y};
	current_node = Arrange_Direct(current_node,dest_point);

	link_list.push_back(current_node);//将节点压入容器

	for(int index=0;index<4;index++)
	{
		if (Can_go(current_node,dest_node,current_node.direct[index]))//节点可以前进
		{
			if(current_node.direct_from != current_node.direct[index])//节点前进的方向不是本节点来源方向（节点不能回头）
			{
				Port next_node = Go_Next_Port(current_node,current_node.direct[index]);
				next_node.direct_from      = -current_node.direct[index];
				link_list.back().direct_to =  current_node.direct[index];

				if((current_node.direct_from != 0) && (current_node.direct_from != next_node.direct_from))//判断是否回折
					next_node.corner_counter++;
				if(next_node.corner_counter >= 3) //回折超过两次，返回
				{
					link_list.pop_back();
					return 0;
				}
				if (next_node.p_x == dest_node.p_x &&//终于到达目的节点？
					next_node.p_y == dest_node.p_y)
				{
					next_node.direct_to = 0;
					link_list.push_back(next_node);
					return 1;
				}
			   if(Check_Linked(next_node,src_node,dest_node))//递归
				   return 1;
			}
		}
	}
	if (current_node.p_x == src_node.p_x &&//目的节点不可达
		current_node.p_y == src_node.p_y)
		return 0;

	link_list.pop_back();
	return 0;//不能前进

}

BOOL GameFrame::Can_go(Port port_temp,Port dest_port,int direct_temp)
{
	switch(direct_temp)
	{
	case Direct_Left:
		{
			if(port_temp.p_x-1 != -2 && Array[port_temp.p_y+1][port_temp.p_x+1 - 1] == -1)
				return TRUE;
			else if (port_temp.p_y   == dest_port.p_y &&
				     port_temp.p_x-1 == dest_port.p_x)
					 return TRUE;
			else
				 return FALSE;
		}break;
	case Direct_Right:
		{
			if(port_temp.p_x+1 != 19 && Array[port_temp.p_y+1][port_temp.p_x+1 + 1] == -1)
				return TRUE;
			else if (port_temp.p_y   == dest_port.p_y &&
				     port_temp.p_x+1 == dest_port.p_x)
				return TRUE;
			else
				return FALSE;
		}break;
	case Direct_Up:
		{
			if(port_temp.p_y-1 != -2 && Array[port_temp.p_y+1 - 1][port_temp.p_x+1] == -1)
				return TRUE;
			else if (port_temp.p_y-1 == dest_port.p_y &&
				     port_temp.p_x   == dest_port.p_x)
				return TRUE;
			else 
				return FALSE;
		}break;
	case Direct_Down:
		{
			if(port_temp.p_y+1 != 13 && Array[port_temp.p_y+1 + 1][port_temp.p_x+1] == -1)
				return TRUE;
			else if (port_temp.p_y+1 == dest_port.p_y &&
				     port_temp.p_x   == dest_port.p_x)
				return TRUE;
			else
				return FALSE;
		}break;
	}
}

Port GameFrame::Go_Next_Port(Port port_temp,int direct_temp)
{
	switch(direct_temp)
	{
	case Direct_Left:
		{
			port_temp.p_x--;
			for (int index=0;index<4;index++)
			{
				port_temp.direct[index] = 0;
			}
			return port_temp;
		}break;
	case Direct_Right:
		{
			port_temp.p_x++;
			for (int index=0;index<4;index++)
			{
				port_temp.direct[index] = 0;
			}
			return port_temp;
		}break;
	case Direct_Up:
		{
			port_temp.p_y--;
			for (int index=0;index<4;index++)
			{
				port_temp.direct[index] = 0;
			}
			return port_temp;
		}break;
	case Direct_Down:
		{
			port_temp.p_y++;
			for (int index=0;index<4;index++)
			{
				port_temp.direct[index] = 0;
			}
			return port_temp;
		}break;
	default:
		return port_temp;
	}
}

Port GameFrame::Arrange_Direct(Port port_temp,POINT dest_point)
{
//此函数处理连线节点到达下一个节点最优路径选择问题
//从而达到优化目的

	int port_x = port_temp.p_x,
		port_y = port_temp.p_y,
		dest_x = dest_point.x,
		dest_y = dest_point.y;

	//开始方块在目的方块左边
	if(port_x < dest_x)
	{
		if(port_y < dest_y)//在左上边
		{

			if(dest_x - port_x <= dest_y - port_y)
			{
				port_temp.direct[0]=Direct_Right;
				port_temp.direct[1]=Direct_Down;
				port_temp.direct[2]=Direct_Left;
				port_temp.direct[3]=Direct_Up;
				return port_temp;
			}
			else
			{
				port_temp.direct[0]=Direct_Down;
				port_temp.direct[1]=Direct_Right;
				port_temp.direct[2]=Direct_Up;
				port_temp.direct[3]=Direct_Left;
				return port_temp;
			}
		}

		if(port_y == dest_y)//正左边
		{
			port_temp.direct[0]=Direct_Right;
			port_temp.direct[1]=Direct_Down;
			port_temp.direct[2]=Direct_Up;
			port_temp.direct[3]=Direct_Left;
			return port_temp;
		}

		if (port_y > dest_y)//左下边
		{
			if(dest_x - port_x <= dest_y - port_y)
			{
				port_temp.direct[0]=Direct_Right;
				port_temp.direct[1]=Direct_Up;
				port_temp.direct[2]=Direct_Left;
				port_temp.direct[3]=Direct_Down;
				return port_temp;
			}
			else
			{
				port_temp.direct[0]=Direct_Up;
				port_temp.direct[1]=Direct_Right;
				port_temp.direct[2]=Direct_Down;
				port_temp.direct[3]=Direct_Left;
				return port_temp;
			}

		}
	}

	//开始方块在目的方块右边
	if(port_x > dest_x)
	{
		if(port_y < dest_y)//右上边
		{

			if(dest_x - port_x <= dest_y - port_y)
			{
				port_temp.direct[0]=Direct_Left;
				port_temp.direct[1]=Direct_Down;
				port_temp.direct[2]=Direct_Right;
				port_temp.direct[3]=Direct_Up;
				return port_temp;
			}
			else
			{
				port_temp.direct[0]=Direct_Down;
				port_temp.direct[1]=Direct_Left;
				port_temp.direct[2]=Direct_Up;
				port_temp.direct[3]=Direct_Right;
				return port_temp;
			}
		}
		if(port_y == dest_y)//正右边
		{
			port_temp.direct[0]=Direct_Left;
			port_temp.direct[1]=Direct_Down;
			port_temp.direct[2]=Direct_Up;
			port_temp.direct[3]=Direct_Right;
			return port_temp;
		}

		if (port_y > dest_y)//右下边
		{
			if(dest_x - port_x <= dest_y - port_y)
			{
				port_temp.direct[0]=Direct_Left;
				port_temp.direct[1]=Direct_Up;
				port_temp.direct[2]=Direct_Right;
				port_temp.direct[3]=Direct_Down;
				return port_temp;
			}
			else
			{
				port_temp.direct[0]=Direct_Up;
				port_temp.direct[1]=Direct_Left;
				port_temp.direct[2]=Direct_Down;
				port_temp.direct[3]=Direct_Right;
				return port_temp;
			}

		}
	}

	if(port_x == dest_x)//开始方块左右对齐
	{
		if(port_y < dest_y)//正上方
		{
			port_temp.direct[0]=Direct_Down;
			port_temp.direct[1]=Direct_Left;
			port_temp.direct[2]=Direct_Right;
			port_temp.direct[3]=Direct_Up;
			return port_temp;
		}
		if(port_y > dest_y)//正下方
		{
			port_temp.direct[0]=Direct_Up;
			port_temp.direct[1]=Direct_Left;
			port_temp.direct[2]=Direct_Right;
			port_temp.direct[3]=Direct_Down;
			return port_temp;

		}
	}

	return port_temp;//方块重叠，不考虑并返回原值
}
void GameFrame::Set_Port(PPort port_temp,POINT point_temp)
{
	port_temp->p_x = point_temp.x;
	port_temp->p_y = point_temp.y;
	port_temp->direct_from = 0;
	port_temp->corner_counter = 0;
	for (int index=0;index<4;index++)
	{
		port_temp->direct[index] = 0;
	}
}

void GameFrame::Set_Array__(POINT point_temp,int value_temp)
{
	Array[point_temp.y+1][point_temp.x+1] = value_temp;
}

void GameFrame::Fill_Surface(LPDIRECTDRAWSURFACE7 lpdds_temp,LPDDBLTFX lpddbltfx_temp)
{
	lpdds_temp->Blt(NULL,NULL,NULL,DDBLT_COLORFILL|DDBLT_WAIT,lpddbltfx_temp);
}


void GameFrame::Disrupt_BlockArea()
{
	Spirit spirit_temp,spirit_first;
	int rank;
	srand((UINT)time(NULL));
	spirit_first = Sp_Block[0];
	for (int index=0;index<160;index++)
	{
		rank = rand()%(160 - index);
		spirit_temp = Sp_Block[index];
		Sp_Block[index] = Sp_Block[rank];
		Sp_Block[rank]  = spirit_temp;
	}
	for (int pindex=0;pindex<10;pindex++)
	{
		for (int index=0;index<16;index++)
		{
			Array[pindex+1][index+1] = Sp_Block[index+pindex*16].type;
		}
	}

	for (int pindex=0;pindex<10;pindex++)
	{
		for (int index=0;index<16;index++)
		{
			Sp_Block[index+pindex*16].posRect.left    = spirit_first.posRect.left   +(40*index);
			Sp_Block[index+pindex*16].posRect.top     = spirit_first.posRect.top    +(40*pindex);
			Sp_Block[index+pindex*16].posRect.right   = spirit_first.posRect.right  +(40*index);
			Sp_Block[index+pindex*16].posRect.bottom  = spirit_first.posRect.bottom +(40*pindex);
		}
	}
}

BOOL GameFrame::IsExit()
{
	if(Sp_Exit.Click_Spirit(Gf_msg,Gf_lparam))
		return TRUE;
	else return FALSE;
}