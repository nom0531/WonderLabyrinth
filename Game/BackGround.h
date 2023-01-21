#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Stage();
	void Render(RenderContext& rc);

	//静的物理オブジェクト
	PhysicsStaticObject physicsStaticObject;
	//メンバ変数
	ModelRender modelRender;
};

