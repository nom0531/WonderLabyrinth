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
	//�ǂݍ���
	modelRender.Init("Assets/modelData/model/stage/backGround.tkm");
}

void BackGround::Render(RenderContext& rc)
{
	//�`��
	modelRender.Draw(rc);
}