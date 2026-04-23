#include "ResultUI.h"
#include "SmallText.h"
#include "DrawNumber.h"

ResultUI::ResultUI(int listIndex, int drawPosY, bool isFinalResult) :
	m_oreType(PlanetInfo::OreType::Coal),
	m_numberHandle(0),
	m_operatorHandle(0),
	m_oreHandle(0),
	m_textHandle(0),
	m_priceValue(0),
	m_getValue(0),
	m_totalValue(0),
	m_listIndex(listIndex),
	m_drawPosY(drawPosY),
	m_isFinalResult(isFinalResult)
{
	m_numberHandle = LoadGraph("Resource/number.png");
	m_operatorHandle = LoadGraph("Resource/operator.png");
	m_oreHandle = LoadGraph("Resource/ores.png");
	m_textHandle = LoadGraph("Resource/smallText.png");

	m_oreType = GameInfo::GetInstance()->getOreTypes[m_listIndex];
	m_getValue = GameInfo::GetInstance()->getOreAmount[m_oreType];
	m_priceValue = PlanetInfo::OrePrice[static_cast<int>(m_oreType)];
	m_totalValue = m_getValue * m_priceValue;

	// 総合スコアは除外
	if (!m_isFinalResult)
	{
		GameInfo::GetInstance()->AddScore(m_totalValue);
	}

	// 詳細の数値（下の説明と同じようなつくりをしたかったが複雑になってしまうので断念）
	m_getNumUI = new UIvalue(m_getValue);
	m_priceNumUI = new UIvalue(m_priceValue, true);
	m_totalNumUI = new UIvalue(m_totalValue);
	m_finalResultNumUI = new UIvalue(GameInfo::GetInstance()->GetScore(), false, true);

	// 詳細の説明
	if (m_listIndex == 0 && !m_isFinalResult)
	{
		m_texts.push_back({
			new SmallText(SmallText::Text::Ore),
			Vector2(
				DrawNumPosX[static_cast<int>(DrawNum::Left)],
				m_drawPosY - MinDist
				)
			});

		m_texts.push_back({
			new SmallText(SmallText::Text::Amount),
				Vector2(
					DrawNumPosX[static_cast<int>(DrawNum::Center)],
					m_drawPosY - MinDist
				)
			});

		m_texts.push_back({
			new SmallText(SmallText::Text::Total),
				Vector2(
					DrawNumPosX[static_cast<int>(DrawNum::Right)],
					m_drawPosY - MinDist
				)
			});
	}
	if (m_isFinalResult)
	{
		m_texts.push_back({
			new SmallText(SmallText::Text::FinalResult),
				Vector2(
					DrawNumPosX[static_cast<int>(DrawNum::Center)],
					m_drawPosY - MinDist / 2.0f
				)
			});
	}

	for (auto& list : m_texts)
	{
		AddChild(list.first);
	}
}

void ResultUI::Release()
{
	delete m_getNumUI;
	delete m_priceNumUI;
	delete m_totalNumUI;
	delete m_finalResultNumUI;

	m_getNumUI = nullptr;
	m_priceNumUI = nullptr;
	m_totalNumUI = nullptr;
	m_finalResultNumUI;

	for (auto& list : m_texts)
	{
		delete list.first;
		list.first = nullptr;
	}
	m_texts.clear();
}

void ResultUI::Update()
{
	m_getNumUI->Update();
	m_priceNumUI->Update();
	m_totalNumUI->Update();
	m_finalResultNumUI->Update();
}

void ResultUI::UIvalue::Update()
{
	// 描画時にゆっくりと本来の数値に変える
	m_drawNumber += (m_number - m_drawNumber) * 0.05f;

	if (0 < m_duration)
	{
		m_duration--;
	}

	if (static_cast<int>(m_prevDrawNum) != static_cast<int>(m_drawNumber)
		&& m_duration <= 0
		&& m_isPlaySE)
	{
		PlaySoundMem(m_seCount, DX_PLAYTYPE_BACK);
		m_duration = SeDurationFrame;
	}

	m_prevDrawNum = m_drawNumber;
}

void ResultUI::Draw()
{
	if (!m_isFinalResult)
	{
		// 取得した鉱石の種類
		DrawResult(m_oreHandle,
			Vector2(0, static_cast<int>(m_oreType)),
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Left)] - MinDist, m_drawPosY),
			OreGlid,
			OreScale
		);

		// 取得した鉱石の価値
		m_priceNumUI->m_UI->Draw(m_priceNumUI->m_drawNumber,
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Left)] + MinDist / 2, m_drawPosY),
			false,
			1.0f,
			false
		);

		// オペレーター（×）
		DrawResult(m_operatorHandle,
			Vector2(0, static_cast<int>(OperatorImage::Times)),
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Center)] - MinDist, m_drawPosY),
			OperatorGlid
		);

		// 取得した鉱石の数
		m_getNumUI->m_UI->Draw(m_getNumUI->m_drawNumber,
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Center)] + MinDist / 2, m_drawPosY),
			false,
			1.0f,
			false
		);

		// オペレーター（＝）
		DrawResult(m_operatorHandle,
			Vector2(0, static_cast<int>(OperatorImage::Equals)),
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Right)] - MinDist * 2, m_drawPosY),
			OperatorGlid
		);

		// 取得した鉱石の合計スコア
		m_totalNumUI->m_UI->Draw(m_totalNumUI->m_drawNumber,
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Right)] + MinDist / 2, m_drawPosY),
			false,
			1.0f,
			false
		);
	}
	else if (m_isFinalResult)
	{
		// 総合スコア
		m_finalResultNumUI->m_UI->Draw(m_finalResultNumUI->m_drawNumber,
			Vector2(DrawNumPosX[static_cast<int>(DrawNum::Center)], m_drawPosY)
		);
	}

	for (auto& list : m_texts)
	{
		list.first->Draw(list.second);
	}
}

// UI表示やスコア表示の処理、もっと分かりやすいプログラムにできないだろうか...
void ResultUI::DrawResult(int handle, Vector2 numOrType, Vector2 position, Vector2 glidSize, float scale)
{
	int value = static_cast<int>(std::round(numOrType.x));
	int type = static_cast<int>(numOrType.y);
	float drawX = 0;

	do
	{
		int drawNum = value % 10;

		DrawRectRotaGraph(
			static_cast<int>(position.x - drawX),
			static_cast<int>(position.y),
			static_cast<int>(drawNum * glidSize.x),
			static_cast<int>(type * glidSize.y),
			static_cast<int>(glidSize.x),
			static_cast<int>(glidSize.y),
			scale,
			0.0,
			handle,
			true
		);
		drawX += glidSize.x * scale;


		value /= 10;
	} while (0 < value);
}
