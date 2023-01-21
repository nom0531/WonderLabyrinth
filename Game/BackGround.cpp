#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	Stage();
}

BackGround::~BackGround()
{
}

void BackGround::Stage()
{
	//ì«Ç›çûÇ›
	modelRender.Init("Assets/modelData/model/stage/backGround.tkm");
}

void BackGround::Render(RenderContext& rc)
{
	//ï`âÊ
	modelRender.Draw(rc);
}