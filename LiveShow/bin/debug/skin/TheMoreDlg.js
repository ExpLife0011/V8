
var SKIN_ON_CLICK_BTN_CLEANSCREEN = 1;
var SKIN_ON_CLICK_BTN_STAMP = 2;
var SKIN_ON_CLICK_BTN_COPYURL = 3;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnCleanScreen.AttachEvent("OnClick",OnClickBtnCleanScreen);
btnStamp.AttachEvent("OnClick",OnClickBtnStamp);
btnCopyUrl.AttachEvent("OnClick",OnClickBtnCopyUrl);


function OnClickBtnCleanScreen()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLEANSCREEN ,0);
}

function OnClickBtnStamp()
{
   Window.PostSkinMessage(SKIN_ON_CLICK_BTN_STAMP ,0);
}

function OnClickBtnCopyUrl()
{
	Window.PostSkinMessage(SKIN_ON_CLICK_BTN_COPYURL, 0);
}


function OnInit()
{
	textTitle.text = "";
	textTitle.visible = false;
	btnSysClose.visible = false;
	btnSysMinimize.visible = false;
	btnSysMaximize.visible = false;
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	imgTheMordDlgBk.left = 0;
	imgTheMordDlgBk.top = 0;
	imgTheMordDlgBk.width = cx;
	imgTheMordDlgBk.height = cy;
		
	btnStamp.left = 22;
	btnStamp.top = (imgTheMordDlgBk.height - btnStamp.height)/2;
	
	btnCleanScreen.left = btnStamp.left + btnStamp.width + 5;
	btnCleanScreen.top = btnStamp.top;
	
	btnCopyUrl.left = btnCleanScreen.left + btnCleanScreen.width + 5;
	btnCopyUrl.top = btnCleanScreen.top;
}

function OnNotify(code, code1)
{
	
}
