#pragma once
#include "Node.h"
#include "Transform2D.h"
#include "CircleRigid2D.h"
#include "Screen.h"
#include "Tag.h"
#include "Layer.h"
#include "Animation2D.h"

class Physics2D;
class ColliderBase2D;
class CircleHitBox;
class Animation2D;

class Actor2D : public Node
{
	friend Physics2D;

protected:
	Tag m_tag;					// タグ
	Layer m_layer;				// レイヤー
	Transform2D m_transform;	// 姿勢情報
	CircleRigid2D m_circleRigid2d;	// 物理演算情報
	Animation2D* m_sprite;			// 2D画像
	CircleHitBox* m_collider;	// 衝突判定の形状

	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	Actor2D(
		const char* handle,
		Tag tag = Tag::None,
		Layer layer = Layer::BackGround,
		const Transform2D& transform = Transform2D(Vector2()),
		int tiles = 1,
		int speed = 1,
		bool loopFlag = true
	);

	virtual void TreeUpdate() override;

	// 姿勢情報の取得
	const Transform2D& GetTransform() const { return m_transform; }

	// 座標の取得
	const Vector2& GetPosition() const { return m_transform.position; }

	// 座標の設定
	void SetPisition(const Vector2& pos) { m_transform.position = pos; }

	// 拡縮の設定
	void SetScale(float scale) { m_transform.scale = scale; }

	// タグの取得
	const Tag GetTag() const { return m_tag; }

	// 衝突判定の形状を取得
	const CircleHitBox* GetCollider() const { return m_collider; }

#pragma warning(push)
#pragma warning(disable:4100)
	// 衝突イベント
	virtual void OnCollisionEnter(const Actor2D* other) {}
	virtual void OnCollision(const Actor2D* other) {}
	virtual void OnCollisionExit(const Actor2D* other) {}
#pragma warning(pop)
};
