#include "ClearScene.h"

#include "../../Input/XInput.h"
#include "../../Input/DInput.h"
#include "../../Image/Image.h"
#include "../../Screen/Screen.h"

ClearScene::ClearScene()
	: Scene()
{

}

ClearScene::~ClearScene()
{
	Image::Delete();
}

void ClearScene::Init()
{
	nextSceneID = SceneID::Title; // 次のシーンはタイトル
	Image::Load(gm.currentSceneID);
	PlayMusic("res/BGM/clear_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを再生
}

void ClearScene::Update()
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

void ClearScene::Draw()
{
	DrawGraph(0, 0, Image::At((unsigned char)ClearSceneImageID::BG), FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_toAllowActionTimer * 255 / m_toAllowActionTime);
	DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(255, 255, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}