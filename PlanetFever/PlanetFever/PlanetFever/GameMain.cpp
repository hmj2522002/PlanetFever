#include "GameMain.h"
#include "GameConfig.h"
#include "SceneTitle.h"
#include "SceneLoading.h"
#include "Screen.h"
#include "Physics2D.h"
#include "Fade.h"
#include "Input.h"
#include "Scroll.h"
#include "DxLib.h"

GameMain::~GameMain()
{
	// 自作スクリーンの破棄
	DeleteGraph(m_screen);

	DxLib_End();
}

// メインループの実行
void GameMain::Run()
{
	// DxLib前処理
	ChangeWindowMode(GameConfig::WindowMode);	   // ウィンドウモード
	SetMainWindowText(GameConfig::Title);		   // ウィンドウタイトル
	SetGraphMode(Screen::Width, Screen::Height, GameConfig::ColorBit);  // ウィンドウサイズ
	SetWaitVSyncFlag(false);

	if (DxLib_Init() == -1)
	{
		throw - 1;
	}

	// シーン起動
	SceneManager::GetInstance()->SetUp(new SceneTitle(), new SceneLoading());

	// スクリーン作成
	m_screen = MakeScreen(Screen::Width, Screen::Height);

	LONGLONG frameStartTime;

	while (true)
	{
		// フレームの開始時間を取得（単位　マイクロ秒）
		frameStartTime = GetNowHiPerformanceCount();

		if (ProcessMessage())
		{
			break;
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// 入力デバイスの更新
		Input::Update();

		// シーンの更新
		SceneManager::GetInstance()->Update();

		// 物理演算
		Physics2D::GetInstance()->Update();

		// 自作スクリーンに描画
		SetDrawScreen(m_screen);
		ClearDrawScreen();

		// スクロール
		Scroll::GetInstance()->Update();

		// シーンの描画
		SceneManager::GetInstance()->Draw();
		SceneManager::GetInstance()->LateDraw();

		Scroll::GetInstance()->Draw();

		// フェード
		Fade::GetInstance()->Update();

		// 自作スクリーンを裏画面に描画
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, m_screen, false);

		// 裏画面と表画面をひっくり返す
		ScreenFlip();

		// フレーム内の経過時間が指定したFPSに到達するまで待つ
		while (GetNowHiPerformanceCount() - frameStartTime < 1000000 / GameConfig::FPS);
	}

	// シーンの破棄
	SceneManager::GetInstance()->Dispose();
}
