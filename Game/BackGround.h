#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	void Stage();
	void Render(RenderContext& rc);

	//�ÓI�����I�u�W�F�N�g
	PhysicsStaticObject physicsStaticObject;
	//�����o�ϐ�
	ModelRender modelRender;
};

