#include "GameOverScene.h"

#include "../../Input/XInput.h"
#include "../../Input/DInput.h"
#include "../../Image/Image.h"
#include "../../Screen/Screen.h"

GameOverScene::GameOverScene()
	: Scene()
{

}

GameOverScene::~GameOverScene()
{
	Image::Delete();
}

void GameOverScene::Init()
{
	nextSceneID = SceneID::Title; // 次のシーンはタイトル
	Image::Load(gm.currentSceneID);

	PlayMusic("res/BGM/gameover_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを再生
}

void GameOverScene::Update()
{
	// タイマーが0になるまで操作を許さない
	if (m_toAllowActionTimer > 0)
	{
		m_toAllowActionTimer--;
		return;
	}

	if (gm.playingInputType == InputType::XInput && XInput::GetButtonDown(XInputDigitalID::X))
	{
		m_isDead = true;
	}
	else if (gm.playingInputType == InputType::DirectInput && DInput::GetButtonDown(DInputID::ZKey))
	{
		m_isDead = true;
	}
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, Image::At((unsigned char)GameOverSceneImageID::BG), FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_toAllowActionTimer * 255 / m_toAllowActionTime);
	DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}