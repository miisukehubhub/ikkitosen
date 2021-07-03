#include "TitleScene.h"

#include "../../Image/Image.h"
#include "../../SE/SE.h"

TitleScene::TitleScene()
	: Scene()
{

}

TitleScene::~TitleScene()
{
	Image::Delete();
}

void TitleScene::Init()
{
	nextSceneID = SceneID::Play;
	Image::Load(gm.currentSceneID);

	// ボタンを2つ生成
	auto bp = std::make_shared<Button>(Vector2(600.f, 700.f), 200, 60, "DirectInputでプレイ");
	DirectInputButton = bp;
	UIs.push_back(bp);

	bp = std::make_shared<Button>(Vector2(1100.f, 700.f), 200, 60, "  XInputでプレイ");
	XInputButton = bp;
	UIs.push_back(bp);

	PlayMusic("res/BGM/title_bgm.mp3", DX_PLAYTYPE_LOOP); // BGMを再生する
}

void TitleScene::Update()
{
	// UIの更新
	for (auto ui : UIs)
	{
		ui->Update();
	}

	if (DirectInputButton.lock()->IsClick())
	{
		// 使用する入力をDirectInputにする
		gm.playingInputType = InputType::DirectInput;
		PlaySoundMem(SE::At(SEID::Start), DX_PLAYTYPE_BACK); // 音を鳴らす
		m_isDead = true;
	}
	else if (XInputButton.lock()->IsClick())
	{
		// 使用する入力をXInputにする
		gm.playingInputType = InputType::XInput;
		PlaySoundMem(SE::At(SEID::Start), DX_PLAYTYPE_BACK); // 音を鳴らす
		m_isDead = true;
	}
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, Image::At((unsigned char)TitleSceneImageID::BG), TRUE);

	DrawGraph(0, 0, Image::At((unsigned char)TitleSceneImageID::Text), TRUE);

	// UIの描画
	for (auto ui : UIs)
	{
		ui->Draw();
	}
}