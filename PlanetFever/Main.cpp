#include "DxLib.h"
#include "GameMain.h"

#pragma warning(push)
#pragma warning(disable:4100)
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ゲーム起動
	GameMain game;
	game.Run();

	return 0;		//ソフトの終了
}
#pragma warning(pop)
