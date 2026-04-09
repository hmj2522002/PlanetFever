#pragma once
#include "Node.h"
#include "PlanetInfo.h"
#include "Vector2.h"
#include "GameInfo.h"
#include "SmallText.h"
#include "DrawNumber.h"
#include <vector>

class ResultUI : public Node
{
private:
	static constexpr Vector2 NumberGlid = Vector2(30, 50);
	static constexpr Vector2 OperatorGlid = Vector2(30, 30);
	static constexpr Vector2 OreGlid = Vector2(16, 16);
	static constexpr float OreScale = 3.0f;
	static constexpr int MinDist = 100;

	enum class DrawNum
	{
		Left,
		Center,
		Right,

		Length,
	};
	static constexpr int DrawNumPosX[static_cast<int>(DrawNum::Length)]
	{
		Screen::WidthCenter - 160,
		Screen::WidthCenter,
		Screen::WidthCenter + 250
	};

	// UI•Ï”
	class UIvalue
	{
	public:
		static constexpr int SeDurationFrame = 6;

		float m_drawNumber;
		float m_prevDrawNum;
		int m_number;
		int m_seCount;
		int m_duration;
		bool m_isPlaySE;
		DrawNumber* m_UI;

		UIvalue(int num, bool isStatic = false, bool isPlaySE = false) :
			m_drawNumber(0),
			m_prevDrawNum(0),
			m_number(num),
			m_seCount(0),
			m_duration(0),
			m_isPlaySE(isPlaySE),
			m_UI(nullptr)
		{
			// m_drawNumber‚Ì”’l‚ğ“®‚©‚È‚­‚³‚¹‚é
			if (isStatic) m_drawNumber = static_cast<float>(m_number);

			m_UI = new DrawNumber();

			m_seCount = LoadSoundMem("Sounds/se_count02.mp3");
			ChangeVolumeSoundMem(120, m_seCount);
		}

		void Update();
	};

	UIvalue* m_getNumUI;
	UIvalue* m_priceNumUI;
	UIvalue* m_totalNumUI;
	UIvalue* m_finalResultNumUI;

	std::list<std::pair<SmallText*, Vector2>> m_texts;
	PlanetInfo::OreType m_oreType;
	int m_numberHandle;
	int m_operatorHandle;
	int m_oreHandle;
	int m_textHandle;
	int m_priceValue;
	int m_getValue;
	int m_totalValue;
	int m_listIndex;
	int m_drawPosY;
	bool m_isFinalResult;

	enum class OperatorImage
	{
		Plus,		// {
		Minus,		// |
		Times,		// ~
		DevidedBy,	// €
		Equals		// 
	};

	// numOrType... num‚Íˆê”Ô–ÚAtype‚Í“ñ”Ô–Ú‚Æ‚·‚é
	void DrawResult(int handle, Vector2 numOrType, Vector2 position, Vector2 glidSize, float scale = 1.0f);

public:
	ResultUI(int listIndex, int drawPosY, bool isFinalResult = false);

	void Release();
	void Update();
	void Draw();
};
