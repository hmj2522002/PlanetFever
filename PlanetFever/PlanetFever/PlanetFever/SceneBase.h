#pragma once
#include "SceneManager.h"

// シーンの基底クラス
class SceneBase
{
public:
	virtual ~SceneBase() {}

	virtual void Initialize() = 0;	// 初期化
	virtual void Finalize() = 0;	// 終了
	virtual void Update() = 0;		// 更新
	virtual void Draw() = 0;		// 描画
	virtual void LateDraw() {};		// Drawが一巡終わったら行われる描画
};
