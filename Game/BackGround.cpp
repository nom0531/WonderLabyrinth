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
	//読み込み
	modelRender.Init("Assets/modelData/model/stage/backGround.tkm");
}

void BackGround::Render(RenderContext& rc)
{
	//描画
	modelRender.Draw(rc);
}