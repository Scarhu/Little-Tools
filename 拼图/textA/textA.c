#include <windows.h> 
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h> 

const int VHNUMS = 3;  
const int CELLNUM = 9;  
int     nGameMap[9];      // ������Ϸ����  
int     nBlack;                 // ����հ׿�λ��  
int     cxBitmap, cyBitmap;     // bmp�Ŀ���  
int     cxCell, cyCell;         // ÿ����Ŀ��� 
int		bIsWin = 0;				//��ʤ�ı�־λ��ʤ����ֵΪ1
int  iLength;
static int  N = 0 ;
        
TCHAR szBuffer [40] ;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);  
  
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,  
                    PSTR szCmdLine, int iCmdShow)  
{  
    static TCHAR szAppName[] = TEXT("Bricks1");  
    HWND         hwnd;  
    MSG          msg;  
    WNDCLASS     wndclass;  
  
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;  
    wndclass.lpfnWndProc   = WndProc;  
    wndclass.cbClsExtra    = 0;  
    wndclass.cbWndExtra    = 0;  
    wndclass.hInstance     = hInstance;  
    wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);  
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);  
    wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH);  
    wndclass.lpszMenuName  = NULL;  
    wndclass.lpszClassName = szAppName;  
  
    if (!RegisterClass (&wndclass))  
    {  
    MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);  
    return 0 ;  
    }  
  
	hwnd = CreateWindow(szAppName,   
                        TEXT ("ƴͼ��Ϸ"),  
                        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,  
                        CW_USEDEFAULT,   
                        CW_USEDEFAULT,  
                        CW_USEDEFAULT,   
                        CW_USEDEFAULT,  
                        NULL,   
                        NULL,   
                        hInstance,   
                        NULL);  
  
  
    ShowWindow(hwnd, iCmdShow);  
    UpdateWindow(hwnd);  
  
    while (GetMessage(&msg, NULL, 0, 0))  
    {  
        TranslateMessage(&msg);  
        DispatchMessage(&msg);  
    }  
    return msg.wParam;  
}  
  

/***********************************************/
void InitGameMap()  
{  
	int i;
    for (i = 0; i < CELLNUM; i++)  
        nGameMap[i] = i;  
  
    srand((unsigned int)(time(0)));  
    for (i = CELLNUM-1; i > 0; i--)  
    {  
        int randIndex = rand() % i;  
        int tmp = nGameMap[i];  
        nGameMap[i] = nGameMap[randIndex];  
        nGameMap[randIndex] = tmp;  
    }  
  
    // �հ׷���  
	nBlack = 8;
    nGameMap[nBlack] = -1;  
}  
/*************************************************/
int DrawGameMap(HDC hdc, HDC hdcMem)  
{  
 
	int i,j,nRow,nCol;
    // ����ͼƬ��  
    for (i = 0; i < VHNUMS; i++)  
        for (j = 0; j < VHNUMS; j++)  
        {  
            int nCell = nGameMap[j*VHNUMS + i];  
  
            if (nCell == -1)    // �հ׷���  
            {  
                Rectangle(hdc, i*cxCell, j*cyCell, i*cxCell+cxCell, j*cyCell+cyCell);  
                continue;  
            }  
  
            nRow = nCell / VHNUMS;  
            nCol = nCell % VHNUMS;  
  
            BitBlt(hdc, i*cxCell, j*cyCell, cxCell, cyCell, hdcMem, nCol*cxCell, nRow*cyCell, SRCCOPY);  
        }  
  
    // ���Ʒ��񣬷ָ�����ͼ���  
    for (i = 0; i <= VHNUMS; i++)  
    {  
        MoveToEx(hdc, i*cxCell, 0, NULL);  
        LineTo(hdc, i*cxCell, cyBitmap);  
    }  
  
    for (i = 0; i <= VHNUMS; i++)  
    {  
        MoveToEx(hdc, 0, i*cyCell, NULL);  
        LineTo(hdc, cxBitmap, i*cyCell);  
    } 
	
	return 1;
}  

/***************************************/
// ������Ϸ�����ϵ�����λ�ã���ʵ���ƶ�  
void Swap(int indexa, int indexb)  
{  
    int tmp = nGameMap[indexa];  
    nGameMap[indexa] = nGameMap[indexb];  
    nGameMap[indexb] = tmp;  
}  
  
void MoveRight()  
{  
    if (nBlack % VHNUMS == 0)           // ����ߵĿ�  
        return;  
  
    // �ƶ���  
    Swap(nBlack-1, nBlack);  
    nBlack = nBlack-1;  
}  
  
void MoveLeft()  
{  
    if (nBlack % VHNUMS == VHNUMS-1)    // ���ұߵĿ�  
        return;  
  
    // �ƶ���  
    Swap(nBlack+1, nBlack);  
    nBlack = nBlack+1;  
}  
  
void MoveUp()  
{  
    if (nBlack >= CELLNUM-VHNUMS)        // ���±ߵĿ�  
        return;  
  
    // �ƶ���  
    Swap(nBlack+VHNUMS, nBlack);  
    nBlack = nBlack+VHNUMS;  
}  
  
void MoveDown()  
{  
    if (nBlack < VHNUMS)             // ���ϱߵĿ�  
        return;  
  
    // �ƶ���  
    Swap(nBlack-VHNUMS, nBlack);  
    nBlack = nBlack-VHNUMS;  
}  

// ����Ƿ��ʤ������ʤ���򽫿հ׿鲹��  
int CheckIsWin()  
{  
	int i;
    for (i = 0; i < CELLNUM-1; i++)  
    {  
        if (nGameMap[i] != i)  
            return 0;  
    }  
  
    bIsWin = 1;  
    nGameMap[nBlack] = 8;  
    return 1;  
}  

// �ػ����Ϊindex�Ŀ�  
void RedrawRect(HWND hwnd, int index)  
{  
    RECT    rcCur;  
    int     xPos, yPos;  
  
    xPos = index % VHNUMS;  
    yPos = index / VHNUMS;  
  
    // ���õ�ǰ��RECT  
    rcCur.left  = xPos*cxCell;  
    rcCur.right = rcCur.left + cxCell;  
    rcCur.top   = yPos*cyCell;  
    rcCur.bottom= rcCur.top + cyCell;  
  
    // �ػ������  
    InvalidateRect(hwnd, &rcCur, FALSE);  
}  

void WMKeyDown(HWND hwnd, LPARAM lParam, WPARAM wParam)  
{  
    int nBlackSave = nBlack; 

	
  
    // ����Ѿ���ʤ������Ӧ��Ϣ  
    if (bIsWin == 1)  
        return;  
  
    switch (wParam)  
    {  
    case VK_RIGHT:   MoveLeft(); break;  
    case VK_LEFT:  MoveRight();break;  
    case VK_DOWN:     MoveUp();   break;  
    case VK_UP:   MoveDown(); break;  
    default:        break;  
    }  
  
    // ���������ƶ����ػ���������  
    if (nBlackSave != nBlack)  
    {  
		N = N + 1;
        RedrawRect(hwnd, nBlackSave);  
        RedrawRect(hwnd, nBlack);  
  
  
        // ����Ƿ��ʤ������ʤ���򽫿հ׿鲹��  
        CheckIsWin();  
 //       if (bIsWin)  
//        {  
 //           MessageBox(hwnd, TEXT("��ϲ��Ӯ��"), TEXT("ƴͼ"), MB_ICONINFORMATION);  
 //       }  
  
    }  
}  



///////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)  
{  
    static HBITMAP      hBitmap;  
    static int          cxClient, cyClient, cxSource, cySource;  
    BITMAP              bitmap;  
    HDC                 hdc, hdcMem;  
    PAINTSTRUCT         ps;  
    int                 x, y;  
    HINSTANCE           hInstance;  

    

    switch (message)  
    {  
    case WM_CREATE:  
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;  
   
        hBitmap = (HBITMAP)LoadImage(NULL, "matthew6.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        GetObject(hBitmap, sizeof(BITMAP), &bitmap);  
  
        cxSource = bitmap.bmWidth;  
        cySource = bitmap.bmHeight;  


	    cxCell = cxSource / VHNUMS;  
        cyCell = cySource / VHNUMS;  

		x = GetSystemMetrics(SM_CXSCREEN)/2 - cxSource/2;  
	    y = GetSystemMetrics(SM_CYSCREEN)/2 - cySource/2;  

		MoveWindow(hwnd, x, y,cxSource*2+45,  cySource+25, TRUE); 

		InitGameMap();

		
        return 0;  
  
    case WM_SIZE:  
        cxClient = LOWORD(lParam);  
        cyClient = HIWORD(lParam);  
          
        return 0;  

	case WM_KEYDOWN:  
		
        WMKeyDown(hwnd, lParam, wParam);  
	//	hdc = GetDC(hwnd);
	//	iLength = wsprintf (szBuffer, TEXT (" %d "), N) ;
	//	TextOut (hdc, cxSource+5, 20, szBuffer, iLength) ;
	//	ReleaseDC(hwnd,hdc);
        return 0; 
  
    case WM_PAINT:  
        hdc = BeginPaint(hwnd, &ps);  
        hdcMem = CreateCompatibleDC(hdc);  
        SelectObject(hdcMem, hBitmap);  
		DrawGameMap(hdc, hdcMem);
		/******************/  //����ԭͼ
		for (y = 0; y < cyClient; y += cySource)  
            for (x = 0; x < cxClient; x += cxSource)  
            {  
                BitBlt(hdc, x+cxSource+40, y, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);  
            }  	



	//if(DrawGameMap(hdc, hdcMem)==0)
	//	{
	//		MessageBox(hwnd,TEXT("��������ʧ��"),TEXT("ʧ��"),MB_OKCANCEL);
	//	}
		
        DeleteDC(hdcMem);  
        EndPaint(hwnd, &ps);  
        return 0;  
  
    case WM_DESTROY:  
        DeleteObject(hBitmap);  
        PostQuitMessage(0);  
        return 0;  

    } 


    return DefWindowProc(hwnd, message, wParam, lParam);  
} 