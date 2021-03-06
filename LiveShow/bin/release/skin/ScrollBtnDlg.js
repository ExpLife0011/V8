
var SKIN_ON_CLICK_BTN_SCROLL = 1;
var SKIN_ON_CLICK_BTN_CLEAN = 2;

Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnScroll.AttachEvent("OnClick",OnClickBtnScroll);
btnClean.AttachEvent("OnClick",OnClickBtnClean);

function OnClickBtnScroll()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_SCROLL,0);
}

function OnClickBtnClean()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLEAN,0);
}

function OnInit()
{
	OnSize(Window.width, Window.height);
}

function OnSize(cx, cy)
{	
	imgScrollBtnDlgBk.visible = true;
	imgScrollBtnDlgBk.left = 0;
	imgScrollBtnDlgBk.top = 0;
	imgScrollBtnDlgBk.width = cx;
	imgScrollBtnDlgBk.height = cy;
	
	btnScroll.visible = true;
	btnScroll.left = imgScrollBtnDlgBk.left;
	btnScroll.top = imgScrollBtnDlgBk.top;
	btnScroll.width = 55;
	btnScroll.height = 19;
	
	btnClean.visible = true;
	btnClean.left = btnScroll.left + btnScroll.width;
	btnClean.top = btnScroll.top;
	btnClean.width = 55;
	btnClean.height = 19;
}

function OnNotify(code, code1)
{
	
}
