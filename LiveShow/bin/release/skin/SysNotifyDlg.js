
var SKIN_ON_CLICK_BTN_CLOSE = 1;
var SKIN_ON_CLICK_BTN_JOIN  = 2;
var SKIN_ON_CLICK_BTN_PREPAGE = 3;
var SKIN_ON_CLICK_BTN_NEXTPAGE = 4;


Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

btnSysClose.AttachEvent("OnClick", btnCloseOnClick);

btnJoin.AttachEvent("OnClick",OnClickBtnJoin);
btnPrePage.AttachEvent("OnClick",OnClickBtnPrePage);
btnNextPage.AttachEvent("OnClick",OnClickBtnNextPage);

function OnClickBtnJoin()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_JOIN,0);
}

function OnClickBtnPrePage()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_PREPAGE,0);
}

function OnClickBtnNextPage()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_NEXTPAGE,0);
}

function btnCloseOnClick()
{
    Window.PostSkinMessage(SKIN_ON_CLICK_BTN_CLOSE,0);
}

function OnInit()
{
    textTitle.text = "系统消息";
    textTitle.visible = false;
    // textTitle.fontWeight = 500;
	// textTitle.fontSize = 11;
    // textTitle.normalColor = 0xffffff;
    // textTitle.colorTransform = true;
	
	// textTitle.width = textTitle.textWidth;
	// textTitle.height = textTitle.textHeight;
	// textTitle.left = imgTitleIcon.left + imgTitleIcon.width + 10;
	// textTitle.top = 0 + (32 - textTitle.height)/2 ;	
	imgTitleIcon.visible = false;
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	imgTopBk.left = 2;
	imgTopBk.top = 2;
	imgTopBk.width = cx - 4;
	imgTopBk.height = 32;

	imgMidBk.left = 2;
	imgMidBk.top = imgTopBk.top + imgTopBk.height;
	imgMidBk.width = cx - 4;
	imgMidBk.height = cy - 2 - imgMidBk.top;

	textTheTitle.left = 10;
	textTheTitle.top = 8;
	textTheTitle.width = 150;
	textTheTitle.height = 20;
	
	//////////////////////////////////////
	textNotify.visible = true;
	textNotify.left = 17;
	textNotify.top = 32;
	textNotify.width = 220;
	textNotify.height = 80;
	
	btnJoin.visible = true;
	btnJoin.width = 80;
	btnJoin.height = 20;
	btnJoin.left = textNotify.left + textNotify.width - btnJoin.width;
	btnJoin.top = textNotify.top + textNotify.height + 2;
	
	btnPrePage.visible = true;
	btnPrePage.width = 40;
	btnPrePage.height = 20;
	btnPrePage.left = textNotify.left;
	btnPrePage.top = cy - 8 - btnPrePage.height;
	
	textPage.visible = true;
	textPage.width = textPage.textWidth;
	textPage.height = textPage.textHeight;
	textPage.left = (cx - textPage.width)/2;
	textPage.top = btnPrePage.top;
	
	btnNextPage.visible = true;
	btnNextPage.width = btnPrePage.width;
	btnNextPage.height = btnPrePage.height;
	btnNextPage.left = cx - 8 - btnNextPage.width;
	btnNextPage.top = btnPrePage.top;
	
	
	
}

function OnNotify(code, code1)
{
  switch(code)
  {

  default:
    break;
  }
}
