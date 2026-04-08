#pragma once
#include <list>

class Node
{
private:
	Node* m_parent;
	std::list<Node*> m_children;
	std::list<Node*> m_removeChildren;
	bool m_isLoaded;
	bool m_isDestroyed;
	void (Node::* m_updateFunc)();

	void Start_();

protected:
	virtual void Load() {}
	virtual void Release() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void LateDraw() {}

	// 自身の削除
	void Destroy();

	// 親を設定
	void SetParent(Node* node) { m_parent = node; }

	// 親を取得
	Node* GetParent() { return m_parent; }

public:
	Node() :
		m_parent(nullptr),
		m_isLoaded(false),
		m_isDestroyed(false),
		m_updateFunc(&Node::Start_) {}

	virtual ~Node();

	virtual void TreeLoad();
	virtual void TreeRelease();
	virtual void TreeUpdate();
	virtual void TreeDraw();
	virtual void TreeLateDraw();

	// 子ノードの追加
	void AddChild(Node* node);

	// 子ノードの削除
	void RemoveChild(Node* node);
};
