#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Screen.h"

class SceneLoading : public SceneBase
{
private:
	Node* m_rootNode;

public:
	SceneLoading() :
		m_rootNode(nullptr) { }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};
