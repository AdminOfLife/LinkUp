#include "Spirit.h"

Spirit::Spirit()
{
	flag = FALSE;
	for (int index=0;index<2;index++)
	{
		look[index] = NULL;
	}
}

Spirit::Spirit(USHORT ustype,RECT pos)
{
	type = ustype;
	posRect = pos;
	Sp_Width = posRect.right - posRect.left;
	Sp_Height = posRect.bottom - posRect.top;
	flag = FALSE;
	for (int index=0;index<2;index++)
	{
		look[index] = NULL;
	}
}

Spirit::~Spirit()
{

}

RECT Spirit::Window_Rect()
{
	RECT win_rect_temp = posRect;
	int x_temp = posRect.left,
		y_temp = posRect.top;

	POINT win_point_temp = {x_temp,y_temp};
	ClientToScreen(hwnd_app,&win_point_temp);
	x_temp = win_point_temp.x;
	y_temp = win_point_temp.y;
	SetRect(&win_rect_temp,x_temp,y_temp,x_temp+Sp_Width,y_temp+Sp_Height);
	return win_rect_temp;
}

void Spirit::Updata_WH()
{	
	Sp_Width = posRect.right - posRect.left;
	Sp_Height = posRect.bottom - posRect.top;
}

int Spirit::Create_Spirit(USHORT ustype,RECT pos)
{
	type = ustype;
	posRect = pos;
	Sp_Width = posRect.right - posRect.left;
	Sp_Height = posRect.bottom - posRect.top;
	return 1;
}

int Spirit::Load_Look(char *file_name_temp,int look_id)
{
	look[look_id] = Load_For_BitmapSur(Sp_Width,Sp_Height,file_name_temp);
	return 1;
}

int Spirit::Load_Look(char *file_name_temp,int look_id,LPRECT size_temp,int cell_x,int cell_y)
{
	look[look_id] = Load_For_BitmapSur(Sp_Width,Sp_Height,file_name_temp,size_temp,cell_x,cell_y);
	return 1;
}

int Spirit::Load_Look(BitmapSur_PTR bmsp_temp,int look_id)
{
	look[look_id] = bmsp_temp;
	return 1;
}

BOOL Spirit::Mouse_Move(UINT msg_temp,LPARAM lparam_temp)
{
	if(msg_temp != WM_MOUSEMOVE) return FALSE;
	POINT point_temp = {(int)LOWORD(lparam_temp),(int)HIWORD(lparam_temp)};

	if(PtInRect(&posRect,point_temp))//检测鼠标是否点击精灵
	{
		return TRUE;
	}
	else return FALSE;
}

BOOL Spirit::Click_Spirit(UINT msg_temp,LPARAM lparam_temp)
{
	if(msg_temp != WM_LBUTTONDOWN) return FALSE;

	POINT point_temp = {(int)LOWORD(lparam_temp),(int)HIWORD(lparam_temp)};

	if(PtInRect(&posRect,point_temp))//检测鼠标是否点击精灵
	{
		flag = TRUE;
		return TRUE;
	}
	else return FALSE;
	
}

int Spirit::Draw_Spirit(LPDIRECTDRAWSURFACE7 surface_temp,int window_mode,int look_id)
{
	if(window_mode == 0)
		surface_temp->Blt(&posRect,look[look_id]->surface,NULL,DDBLT_WAIT,NULL);
	else
		surface_temp->Blt(&Window_Rect(),look[look_id]->surface,NULL,DDBLT_WAIT,NULL);
	return 1;
}

int Spirit::Draw_Spirit(LPDIRECTDRAWSURFACE7 surface_temp,DDCOLORKEY srcKey_temp,int window_mode,int look_id)
{
	DDBLTFX ddbltfx_temp;
	DDRAW_INIT_STRUCT(ddbltfx_temp);
	ddbltfx_temp.ddckSrcColorkey = srcKey_temp;
	if(window_mode == 0)
		surface_temp->Blt(&posRect,look[look_id]->surface,NULL,DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE,&ddbltfx_temp);
	else
		surface_temp->Blt(&Window_Rect(),look[look_id]->surface,NULL,DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE,&ddbltfx_temp);
	return 1;
}



//==============================================
//==============================================
//其他函数体

BitmapSur_PTR Load_For_BitmapSur(int width_temp,int heigth_temp,char *file_name_temp)
{
	BitmapSur_PTR bsp_temp = new BitmapSur();
	bsp_temp->width  = width_temp; 
	bsp_temp->height = heigth_temp;
	BITMAP_FILE bitmap_temp;

	bsp_temp->surface = DDraw_Create_Surface(width_temp,heigth_temp);//创建离屏表面

	Load_Bitmap_File_32(&bitmap_temp,file_name_temp);

	DDRAW_INIT_STRUCT(ddsd);

	if(FAILED(bsp_temp->surface->Lock(NULL,&ddsd,DDLOCK_WAIT|DDLOCK_SURFACEMEMORYPTR,NULL)))
		return 0;

	int pitch_temp = ddsd.lPitch;
	DWORD *sur_buff  = (DWORD *)ddsd.lpSurface;

	Draw_Bitmap32(&bitmap_temp,sur_buff,0,0,pitch_temp,0,NULL);//将位图画在表面
	bsp_temp->surface->Unlock(NULL);

	return bsp_temp;
}

BitmapSur_PTR Load_For_BitmapSur(int width_temp,int heigth_temp,char *file_name_temp,
					   LPRECT size_temp,int cell_x,int cell_y)
{
	//单元格模式读取，无单元黑边

	BitmapSur_PTR bsp_temp = new BitmapSur();
	bsp_temp->width  = width_temp; 
	bsp_temp->height = heigth_temp;
	BITMAP_FILE bitmap_temp;

	bsp_temp->surface = DDraw_Create_Surface(width_temp,heigth_temp);//创建离屏表面

	Load_Bitmap_File_32(&bitmap_temp,file_name_temp);

	DDRAW_INIT_STRUCT(ddsd);

	if(FAILED(bsp_temp->surface->Lock(NULL,&ddsd,DDLOCK_WAIT|DDLOCK_SURFACEMEMORYPTR,NULL)))
		return 0;

	int pitch_temp = ddsd.lPitch;
	DWORD *sur_buff  = (DWORD *)ddsd.lpSurface;

	Draw_Bitmap32(&bitmap_temp,sur_buff,0,0,pitch_temp,1,size_temp,cell_x,cell_y);//将位图画在表面
	bsp_temp->surface->Unlock(NULL);

	return bsp_temp;
}

int Draw_BmpSur(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp)
{
	surface_temp->Blt(&rect_temp,bmps_temp.surface,NULL,DDBLT_WAIT,NULL);
	return 1;
}

int Draw_BmpSur(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp,DDCOLORKEY srcKey_temp)
{
	DDBLTFX ddbltfx_temp;
	DDRAW_INIT_STRUCT(ddbltfx_temp);
	ddbltfx_temp.ddckSrcColorkey = srcKey_temp;
	surface_temp->Blt(&rect_temp,bmps_temp.surface,NULL,DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE,&ddbltfx_temp);
	return 1;
}

int Draw_BmpSur_Win(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp)
{
	int width_temp = rect_temp.right - rect_temp.left,
	    height_temp = rect_temp.bottom - rect_temp.top;

	POINT point_temp={rect_temp.left,rect_temp.top};
	ClientToScreen(hwnd_app,&point_temp);

	SetRect(&rect_temp,point_temp.x,point_temp.y,point_temp.x+width_temp,point_temp.y+height_temp);
	surface_temp->Blt(&rect_temp,bmps_temp.surface,NULL,DDBLT_WAIT,NULL);

	return 1;
}

int Draw_BmpSur_Win(LPDIRECTDRAWSURFACE7 surface_temp,RECT rect_temp,BitmapSur bmps_temp,DDCOLORKEY srcKey_temp)
{
	int width_temp = rect_temp.right - rect_temp.left,
		height_temp = rect_temp.bottom - rect_temp.top;

	DDBLTFX ddbltfx_temp;
	DDRAW_INIT_STRUCT(ddbltfx_temp);
	ddbltfx_temp.ddckSrcColorkey = srcKey_temp;

	POINT point_temp={rect_temp.left,rect_temp.top};
	ClientToScreen(hwnd_app,&point_temp);

	SetRect(&rect_temp,point_temp.x,point_temp.y,point_temp.x+width_temp,point_temp.y+height_temp);
	surface_temp->Blt(&rect_temp,bmps_temp.surface,NULL,DDBLT_WAIT|DDBLT_KEYSRCOVERRIDE,&ddbltfx_temp);
	
	return 1;
}