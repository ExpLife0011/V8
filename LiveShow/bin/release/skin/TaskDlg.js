
Window.AttachEvent("OnInit", OnInit);
Window.AttachEvent("OnSize", OnSize);
Window.AttachEvent("OnNotify", OnNotify);

function OnInit()
{
    textTitle.text = "";
    textTitle.visible = false;

	imgTitleIcon.visible = false;
	OnSize(Window.width, Window.height);
}


function OnSize(cx, cy)
{
	//////////////////////////////////////
	itemHtmlTask.left = 2;
	itemHtmlTask.top = 2;
	itemHtmlTask.width = cx - 4;
	itemHtmlTask.height = cy - 4;
}

function OnNotify(code, code1)
{
  switch(code)
  {

  default:
    break;
  }
}
