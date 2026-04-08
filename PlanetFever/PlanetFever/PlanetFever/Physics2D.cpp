#include "Physics2D.h"
#include "Actor2D.h"
#include "CircleHitBox.h"
#include "Collision2D.h"

void Physics2D::Update()
{
	if (!m_isActive) return;

	for (auto actor : m_actorList)
	{
		CircleRigid2D& rbody = actor->m_circleRigid2d;
		CircleRigid2D::BodyType bodyType = rbody.GetBodyType();

		// 静的オブジェクトは除外
		if (bodyType == CircleRigid2D::BodyType::Static) continue;

		// 重力を与える
		if (bodyType == CircleRigid2D::BodyType::Dynamic)
		{
			Vector2 diff;
			diff = m_gravityPoint - actor->m_transform.position;

			Vector2 dir;
			dir = diff.Normalized();

			float fallSpeed = Vector2::Dot(rbody.velocity, dir);
			if (rbody.gravityLimit)
			{
				if (rbody.limitSpeedFall < fallSpeed)
				{
					rbody.velocity -= dir * (fallSpeed - rbody.limitSpeedFall);
				}
			}

			// 重力
			rbody.velocity += dir * Gravity * rbody.gravityScale;


			// 惑星に垂直な移動の減速
			Vector2 tangent = Vector2(-dir.y, dir.x);
			float horizontalSpeed = Vector2::Dot(rbody.velocity, tangent);
			rbody.velocity -= tangent * horizontalSpeed * rbody.horizontalFriction;
		}

		// 移動
		actor->m_transform.position += rbody.velocity;
	}

	// 衝突判定をするペアを作成
	std::list<Pair> pairList;
	for (auto item1 = m_actorList.begin(); item1 != m_actorList.end(); item1++)
	{
		for (auto item2 = item1; item2 != m_actorList.end(); item2++)
		{
			Actor2D* actor1 = *item1;
			Actor2D* actor2 = *item2;

			// 自分自身にぶつかることはできないのでスキップ
			if (actor1 == actor2) continue;

			// 静的オブジェクト同士はぶつかれないのでスキップ
			if (actor1->m_circleRigid2d.GetBodyType() == CircleRigid2D::BodyType::Static &&
				actor2->m_circleRigid2d.GetBodyType() == CircleRigid2D::BodyType::Static) continue;
		
			// コライダーが指定されていなと衝突すらできないのでスキップ
			if (actor1->GetCollider() == nullptr) continue;
			if (actor2->GetCollider() == nullptr) continue;

			// どちらかがIgnoreなら無視。スキップ
			if (actor1->GetCollider()->GetPhysicsBehavior(actor2->GetTag()) == PhysicsBehavior::Ignore) continue;
			if (actor2->GetCollider()->GetPhysicsBehavior(actor1->GetTag()) == PhysicsBehavior::Ignore) continue;

			// 一定以上離れているものはスキップ
			if ((actor1->GetPosition() - actor2->GetPosition()).SqrMagnitude() > LimitDistance) continue;

			// ペア登録
			pairList.push_back(Pair(actor1, actor2));
		}
	}




	// 衝突判定
	std::unordered_map<Actor2D*, std::unordered_set<Actor2D*>> callbackList;


	for (auto& pair : pairList)
	{
		auto actor1 = pair.actor1;
		auto actor2 = pair.actor2;

		// 衝突判定
		Collision2D::HitInfo hitInfo = actor1->GetCollider()->CheckHitBox(
			actor1->GetTransform(),
			actor2->GetTransform(), actor2->GetCollider()
		);

		if (!hitInfo.isHit) continue;

		// コールバック登録
		callbackList[actor1].insert(actor2);

		// どちらかがCollisionではなかったら衝突しない
		if (actor1->GetCollider()->GetPhysicsBehavior(actor2->GetTag()) != PhysicsBehavior::Collision) continue;
		if (actor2->GetCollider()->GetPhysicsBehavior(actor1->GetTag()) != PhysicsBehavior::Collision) continue;

		// 自分がStaticなら何もしない
	//	if (actor1->m_circleRigid2d.GetBodyType() == CircleRigid2D::BodyType::Static) continue;

		Vector2 diff = (actor1->GetPosition() + actor1->GetCollider()->offset) -
					   (actor2->GetPosition() + actor2->GetCollider()->offset);
		float dist = diff.Magnitude();

		float rad = actor1->GetCollider()->radius * actor1->GetTransform().scale +
					actor2->GetCollider()->radius * actor2->GetTransform().scale;

		float fixDist = rad - dist;

		if (fixDist <= 0.0001) continue;	// ０除算回避

		actor2->m_transform.position -= diff / dist * fixDist;
	}
	

	// コールバック処理
	for (auto& pair : callbackList)
	{
		auto actor1 = pair.first;
		for (auto actor2 : pair.second)
		{
			// 前回の衝突判定で、同じ組み合わせがいたか
			auto it = m_prevCallbackList.find(actor1);
			if (it != m_prevCallbackList.end() && it->second.find(actor2) != it->second.end())
			{
				// いたので「衝突中」
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);

				// 前回の衝突リストから、組み合わせを削除
				it->second.erase(actor2);
			}
			else
			{
				// いなかったので「新規の衝突」
				actor1->OnCollisionEnter(actor2);
				actor2->OnCollisionEnter(actor1);
			}
		}
	}

	// この時点で前回の衝突リストに残っているのは「衝突終了」
	for (auto& pair : m_prevCallbackList)
	{
		auto actor1 = pair.first;

		// 生存チェック
		if (std::find(m_actorList.begin(), m_actorList.end(), actor1) == m_actorList.end())continue;
		for (auto actor2 : pair.second)
		{
			// 生存チェック
			if (std::find(m_actorList.begin(), m_actorList.end(), actor2) == m_actorList.end())continue;

			actor1->OnCollisionExit(actor2);
			actor2->OnCollisionExit(actor1);
		}
	}

	// 衝突リストを覚えておく
	m_prevCallbackList = callbackList;
}
