32258 DIALOG 13, 54, 250, 110
STYLE WS_CHILD
CAPTION ""
LANGUAGE LANG_ENGLISH, SUBLANG_ENGLISH_US
FONT 8, "MS Shell Dlg"
{
   CONTROL "Property &Name:", -1, STATIC, SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 3, 5, 61, 8 
   CONTROL "", 1000, COMBOBOX, CBS_DROPDOWNLIST | CBS_SORT | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP, 65, 3, 100, 71 
   CONTROL "&Font:", -1, STATIC, SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 3, 19, 91, 8 
   CONTROL "", 1001, COMBOBOX, CBS_SIMPLE | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_SORT | CBS_HASSTRINGS | CBS_DISABLENOSCROLL | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP, 3, 29, 91, 77 
   CONTROL "Font St&yle:", -1, STATIC, SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 102, 19, 53, 8 
   CONTROL "", 1002, COMBOBOX, CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP, 104, 29, 53, 53 
   CONTROL "&Size:", -1, STATIC, SS_LEFT | WS_CHILD | WS_VISIBLE | WS_GROUP, 167, 19, 40, 8 
   CONTROL "", 1003, COMBOBOX, CBS_DROPDOWN | CBS_SORT | CBS_DISABLENOSCROLL | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP, 167, 29, 36, 53 
   CONTROL "Effects", -1, BUTTON, BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 104, 44, 142, 24 
   CONTROL "Stri&keout", 1004, BUTTON, BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 109, 55, 65, 10 
   CONTROL "&Underline", 1005, BUTTON, BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 175, 55, 65, 10 
   CONTROL "Sample", -1, BUTTON, BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP, 104, 71, 142, 36 
   CONTROL "AaBbYyZz", 1006, STATIC, SS_CENTER | SS_NOPREFIX | WS_CHILD | WS_GROUP, 110, 80, 130, 22 
}
