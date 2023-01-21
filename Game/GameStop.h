#pragma once

// 操作不能用クラス
class GameStop:public IGameObject
{
public:
	bool StopFlag = false;					// 全編通しての操作を停止するフラグ
};

