#pragma once

//���ڴ洴��Icon��iconSizeΪҪ��ȡ��icon�Ĵ�С��-1Ϊ��һ��������Ҳ�����Ҫ�Ĵ�С����ȡ��һ��
HICON MakeIconFromBuf(LPBYTE pBuf, LONG lSize, LONG iconSize = -1);

//���ڴ洴��Cursor
HCURSOR MakeCursorFromBuf(LPBYTE pBuf, LONG lSize);
