#pragma once
#include <list>

class SceneBase;

class SceneManager
{
private:
	// シーン繊維のフェーズ
	enum class Phase
	{
		Run,		// 実行中
		SetUp,		// 起動・遷移
		Loading,	// ローディング
		Transition,	// 遷移
	};

	Phase m_phase;
	std::list<SceneBase*> m_sceneList;	// 実行中シーン

	SceneBase* m_nextScene;	// 遷移先のシーン

	SceneBase* m_loadingScene;	//ローディングシーン

	SceneManager() :
		m_phase(Phase::SetUp),
		m_nextScene(nullptr),
		m_loadingScene(nullptr) {}

public:
	// シングルトン
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	// 初期シーンの設定
	void SetUp(SceneBase* initScene, SceneBase* loadingScene = nullptr);

	// リソースの開放
	void Dispose();

	// シーンのロード
	void LoadScene(SceneBase* scene);

	// シーンの追加
	void PushScene(SceneBase* scene) { m_sceneList.push_back(scene); }

	// 最後に追加したシーンを削除
	void PopScene() { m_sceneList.pop_back(); }

	// 指定したシーンを削除
	void RemoveScene(SceneBase* scene) { m_sceneList.remove(scene); };

	void Update();
	void Draw();
	void LateDraw();
};
