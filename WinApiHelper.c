#include "WinApiHelper.h"


void EnableControl(HWND hDlg, int controlId)
{
    HWND hCtl = GetDlgItem(hDlg, controlId);
    if (hCtl)
    {
        EnableWindow(hCtl, TRUE);
    }
}

void DisableControl(HWND hDlg, int controlId)
{
    HWND hCtl = GetDlgItem(hDlg, controlId);
    if (hCtl)
    {
        EnableWindow(hCtl, FALSE);
    }
}

void SetText (HWND hDlg, int controlId, const char* text)
{
 	SendDlgItemMessageA (hDlg, controlId, WM_SETTEXT, 0, (LPARAM)text);
}

void SetTextLength(HWND hDlg, int controlId, int maxLength)
{
	SendDlgItemMessageA (hDlg, controlId, EM_SETLIMITTEXT, (WPARAM)maxLength, 0);
}

void SetUnicodeText (HWND hDlg, int controlId, const wchar_t* text)
{
	SendDlgItemMessageW (hDlg, controlId, WM_SETTEXT, 0, (LPARAM)text);
}

void SetMaxTextLength(HWND hDlg, int controlId, int maxLength)
{
    SendDlgItemMessage(hDlg, controlId, EM_LIMITTEXT, maxLength, 0);
}

void GetText (HWND hDlg, int controlId, char* buffer, int bufferSize)
{
 	SendDlgItemMessageA (hDlg, controlId, WM_GETTEXT, bufferSize, (LPARAM)buffer);
}


void ComboBox_Clear(HWND hDlg, int comboboxId)
{
    SendDlgItemMessageA (hDlg, comboboxId, CB_RESETCONTENT, 0, 0);
}

void ComboBox_AddItem(HWND hDlg, int comboboxId, const char* text)
{
    SendDlgItemMessageA (hDlg, comboboxId, CB_ADDSTRING, 0, (LPARAM)text);
}

void ComboBox_SetItemIndex(HWND hDlg, int comboboxId, int itemIndex)
{
    SendDlgItemMessageA (hDlg, comboboxId, CB_SETCURSEL, (WPARAM)itemIndex,0);   
}

int ComboBox_GetItemIndex(HWND hDlg, int comboboxId)
{
    return SendDlgItemMessageA (hDlg, comboboxId, CB_GETCURSEL, 0,0);   
}

void ComboBox_SetDropdownListHeight(HWND hDlg, int comboboxId, int height)
{
    RECT rect;
    HWND hCtl = GetDlgItem(hDlg, comboboxId);
    GetWindowRect(hCtl, &rect);
    rect.bottom = rect.top + height;

    SetWindowPos(hCtl, 0, rect.left, rect.top, rect.right-rect.left, height, SWP_NOMOVE);
}

void ListBox_Clear(HWND hDlg, int comboboxId)
{
    SendDlgItemMessage (hDlg, comboboxId, LB_RESETCONTENT, 0, 0);
}

void ListBox_AddItem(HWND hDlg, int comboboxId, const char* text)
{
    SendDlgItemMessageA (hDlg, comboboxId, LB_ADDSTRING, 0, (LPARAM)text);
}

void ListBox_SetItemIndex(HWND hDlg, int comboboxId, int itemIndex)
{
    SendDlgItemMessage (hDlg, comboboxId, LB_SETCURSEL,(WPARAM)itemIndex,0);   
}

int ListBox_GetItemIndex(HWND hDlg, int comboboxId)
{
    return SendDlgItemMessage (hDlg, comboboxId, LB_GETCURSEL,0,0);
}

int  Slider_GetPosition(HWND hDlg, int sliderId)
{
	return SendDlgItemMessage (hDlg, sliderId, TBM_GETPOS,0,0);
}

void CheckBox_SetState(HWND hDlg, int checkboxId, BOOL checked, BOOL enabled)
{
    HWND hCtl = GetDlgItem(hDlg, checkboxId);

    SendMessage(hCtl, BM_SETCHECK, enabled?(checked? BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE, 0);
    EnableWindow(hCtl, enabled);
}

BOOL CheckBox_GetState(HWND hDlg, int checkboxId)
{
    HWND hCtl = GetDlgItem(hDlg, checkboxId);
    return SendMessage(hCtl, BM_GETCHECK, 0, 0);
}

void RadioButton_SetState(HWND hDlg, int radioButtonId, BOOL checked, BOOL enabled)
{
    HWND hCtl = GetDlgItem(hDlg, radioButtonId);

    SendMessage(hCtl, BM_SETCHECK, enabled?(checked? BST_CHECKED : BST_UNCHECKED) : BST_INDETERMINATE, 0);
    EnableWindow(hCtl, enabled);
}

BOOL RadioButton_GetState(HWND hDlg, int radioButtonId)
{
    HWND hCtl = GetDlgItem(hDlg, radioButtonId);
    return SendMessage(hCtl, BM_GETCHECK, 0, 0);
}


HTREEITEM TreeView_AddNode (HWND hWnd, int treeId, HTREEITEM parent, wchar_t* caption, int icon, int selected_icon)
{
	TV_INSERTSTRUCTW tvinsert; 

	ZeroMemory (&tvinsert,sizeof(tvinsert));
	tvinsert.hParent=parent;
	tvinsert.hInsertAfter=parent?TVI_LAST:TVI_ROOT;
	tvinsert.item.mask=TVIF_TEXT;//|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText=caption;
	tvinsert.item.iImage=icon;
	tvinsert.item.iSelectedImage=selected_icon;
	return ((HTREEITEM)SendDlgItemMessage(hWnd, treeId, TVM_INSERTITEM,0,(LPARAM)&tvinsert));
}

void TreeView_ExpandNode(HWND hWnd, int treeId, HTREEITEM itemToExpand)
{
	SendDlgItemMessageA(hWnd, treeId, TVM_EXPAND, TVE_EXPAND, itemToExpand);
}