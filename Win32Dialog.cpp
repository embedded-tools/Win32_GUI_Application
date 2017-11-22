#include <Windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#include <tchar.h>
#include <WinUser.h>
#include "resource.h"
#include "WinApiHelper.h"

HWND hMainDialog;
HINSTANCE hInst;

BOOL nameCleared = FALSE;

BOOL CALLBACK EmptyDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int control;

    switch(uMsg)
    {
        case WM_INITDIALOG:            
        {    
			//init controls here
        }
        return TRUE;

        case WM_COMMAND:
        {
            if (HIWORD(wParam)==BN_CLICKED)
            {
                control = LOWORD(wParam);
                switch (control)
                {
  				    case IDOK: SendMessage(hDlg, WM_CLOSE, 0, 0); break;
                    case IDCANCEL: SendMessage(hDlg, WM_CLOSE, 0, 0); break;
                }
            }
        }
        return TRUE;

        case WM_CLOSE:
            {
                DestroyWindow(hDlg);
            }
            return TRUE;

		/*
		//main dialog must call postquitmessage,
		//other helper dialogs must not!!!
		//(because postquitmessage ends whole application)
        case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            return TRUE;
		*/
        
        default:
			return FALSE;
    }
    return FALSE;
}



BOOL CALLBACK MainDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int control = 0;
	int n;
	static char name[100];
	static char text[100];
    

    switch(uMsg)
    {
        case WM_INITDIALOG:            
        {    
			ComboBox_Clear(hDlg, IDC_COMBO1);
			ComboBox_AddItem(hDlg, IDC_COMBO1, "First choice");
			ComboBox_AddItem(hDlg, IDC_COMBO1, "Second choice");
			ComboBox_AddItem(hDlg, IDC_COMBO1, "Third choice");
			ComboBox_SetItemIndex(hDlg, IDC_COMBO1, 0);    
			ComboBox_SetDropdownListHeight(hDlg, IDC_COMBO1, 120);

			SetUnicodeText(hDlg, IDC_EDIT1, L"Write name here");
			SetTextLength(hDlg, IDC_EDIT1, 10);

			ListBox_Clear(hDlg, IDC_LIST1);
			ListBox_AddItem(hDlg, IDC_LIST1, "ABCD");
			ListBox_AddItem(hDlg, IDC_LIST1, "EFGH");
			ListBox_AddItem(hDlg, IDC_LIST1, "IJKL");
			ListBox_AddItem(hDlg, IDC_LIST1, "MNOP");
			ListBox_AddItem(hDlg, IDC_LIST1, "QRST");

			HTREEITEM root  = TreeView_AddNode(hDlg, IDC_TREE1, 0, L"Root 1234", -1, -1);
			HTREEITEM item1 = TreeView_AddNode(hDlg, IDC_TREE1, root, L"Item 1", -1, -1);
			HTREEITEM item2 = TreeView_AddNode(hDlg, IDC_TREE1, root, L"Item 2", -1, -1);
			HTREEITEM item3 = TreeView_AddNode(hDlg, IDC_TREE1, root, L"Item 3", -1, -1);
			HTREEITEM item4 = TreeView_AddNode(hDlg, IDC_TREE1, root, L"Item 4", -1, -1);
			TreeView_ExpandNode(hDlg, IDC_TREE1, root);
			nameCleared = FALSE;

			SetText(hDlg, IDC_EDIT2, "Hello\r\nThis way you can\r\ninsert multiple lines.\r\n\r\nVery easy.\r\n");
        }
        return TRUE;

        case WM_COMMAND:
        {
            if (HIWORD(wParam)==CBN_DROPDOWN) //Combobox Notification - Drop down list shown
            {
                control = LOWORD(wParam);

            }
            if (HIWORD(wParam)==CBN_SELCHANGE) //Combobox Notification - Selection Changed
            {
                control = LOWORD(wParam);
                switch(control)
                {

                }
            }
            if (HIWORD(wParam)==BN_CLICKED)
            {
                control = LOWORD(wParam);
                switch (control)
                {
					case IDC_BUTTON1: 
						n = ComboBox_GetItemIndex(hDlg, IDC_COMBO1);
						sprintf(text, "You selected %i. item", n+1);
						MessageBoxA(hDlg, text, "Button clicked", 0);
						break;

					case IDC_BUTTON2:
					{
						GetText(hDlg, IDC_EDIT1, name, sizeof(name));
						sprintf(text, "You entered: %s", name);
						MessageBoxA(hDlg, text, "Name entered", 0);
					}
					break;
						
					case IDC_BUTTON3:
						{
							BOOL b = CheckBox_GetState(hDlg, IDC_CHECK1);
							if (b)
							{
								MessageBoxA(hDlg, "Checkbox checked", "Button pressed", 0);
							} else {
								MessageBoxA(hDlg, "Checkbox unchecked", "Button pressed", 0);
							}
						}
						break;

					case IDC_CHECK1:
						{
							MessageBoxA(hDlg, "Checkbox state changed", "Checkbox", 0);
						}
						break;

					case IDC_BUTTON4:
						{
							n = ListBox_GetItemIndex(hDlg, IDC_LIST1);
							sprintf(text, "You selected %i. item", n+1);
							MessageBoxA(hDlg, text, "Button clicked", 0);							
						}
						break;

					case IDC_BUTTON5:
						{
							DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, EmptyDialogProc);			
						}
						break;

  				    case IDOK: SendMessage(hDlg, WM_CLOSE, 0, 0); break;
                    case IDCANCEL: SendMessage(hDlg, WM_CLOSE, 0, 0); break;
                }
            }
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				control = LOWORD(wParam);
				switch(control)
				{
					case IDC_EDIT1: SetText(hDlg, IDC_EDIT1, ""); break;
				}
			}
        }
        return TRUE;

		case WM_HSCROLL:
		{
			control = LOWORD(wParam);

			n = Slider_GetPosition(hDlg, IDC_SLIDER1);
			sprintf(text, "%i", n);
			SetText(hDlg, IDC_STATIC, text);

		}
		break;

        case WM_CLOSE:
            {
                DestroyWindow(hDlg);
            }
            return TRUE;

        case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            return TRUE;
        
        default:
			return FALSE;

            //return DefWindowProc(hDlg, uMsg, wParam, lParam);

    }

    return FALSE;
}




int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    BOOL ret;
    MSG msg;
	int err;

	hInst = hInstance;

    InitCommonControls();

	hMainDialog = CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, MainDialogProc, 1234L);

	ShowWindow(hMainDialog, nCmdShow);

	//center window
	RECT desktopRect;
	RECT windowRect;
	GetClientRect(GetDesktopWindow(), &desktopRect);
	GetClientRect(hMainDialog, &windowRect);
	windowRect.left = desktopRect.right / 2 - windowRect.right / 2;
	windowRect.top  = desktopRect.bottom / 2 - windowRect.bottom / 2;
	SetWindowPos(hMainDialog, 0, windowRect.left, windowRect.top, 0, 0, SWP_NOSIZE);
	

    while((ret = GetMessage(&msg, 0, 0, 0)) != 0) 
    {
        if (ret == -1)
        { 
            return -1;
        }

        if(!IsDialogMessage(hMainDialog, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); 
        }
    }
    return 0;
}