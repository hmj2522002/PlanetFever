#pragma once

enum class Layer
{
	BackGround,	// そのまま背景、画面揺れ対応（小さめ）、スクロール非対応
	Object,		// プレイヤーや隕石等、画面揺れ対応（大きめ）、スクロール対応
	UI			// そのままUI、画面揺れ非対応、スクロール非対応
};
