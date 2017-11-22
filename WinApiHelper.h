#ifndef WINAPIHELPER___H
#define WINAPIHELPER___H

#include <windows.h>
#include <CommCtrl.h>

#ifdef __cplusplus
extern "C" {
#endif

void EnableControl(HWND hDlg, int controlId);
void DisableControl(HWND hDlg, int controlId);

void SetText (HWND hDlg, int controlId, const char* text);
void SetTextLength(HWND hDlg, int controlId, int maxLength);
void SetUnicodeText (HWND hDlg, int controlId, const wchar_t* text);
void SetMaxTextLength(HWND hDlg, int controlId, int maxLength);
void GetText (HWND hDlg, int controlId, char* buffer, int bufferSize);

void ComboBox_Clear(HWND hDlg, int comboboxId);
void ComboBox_AddItem(HWND hDlg, int comboboxId, const char* text);
void ComboBox_SetItemIndex(HWND hDlg, int comboboxId, int itemIndex);
int  ComboBox_GetItemIndex(HWND hDlg, int comboboxId);
void ComboBox_SetDropdownListHeight(HWND hDlg, int comboboxId, int height);

void ListBox_Clear(HWND hDlg, int comboboxId);
void ListBox_AddItem(HWND hDlg, int comboboxId, const char* text);
void ListBox_SetItemIndex(HWND hDlg, int comboboxId, int itemIndex);
int  ListBox_GetItemIndex(HWND hDlg, int comboboxId);

int  Slider_GetPosition(HWND hDlg, int sliderId);

void CheckBox_SetState(HWND hDlg, int checkboxId, BOOL checked, BOOL enabled);
BOOL CheckBox_GetState(HWND hDlg, int checkboxId);

void RadioButton_SetState(HWND hDlg, int radioButtonId, BOOL checked, BOOL enabled);
BOOL RadioButton_GetState(HWND hDlg, int radioButtonId);

HTREEITEM TreeView_AddNode (HWND hWnd, int treeId, HTREEITEM parent, wchar_t* caption, int icon, int selected_icon);

void TreeView_ExpandNode(HWND hWnd, int treeId, HTREEITEM itemToExpand);

#ifdef __cplusplus
}
#endif

#endif