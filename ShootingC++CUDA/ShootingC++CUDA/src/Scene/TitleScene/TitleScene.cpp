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

	// �{�^����2����
	auto bp = std::make_shared<Button>(Vector2(600.f, 700.f), 200, 60, "DirectInput�Ńv���C");
	DirectInputButton = bp;
	UIs.push_back(bp);

	bp = std::make_shared<Button>(Vector2(1100.f, 700.f), 200, 60, "  XInput�Ńv���C");
	XInputButton = bp;
	UIs.push_back(bp);

	PlayMusic("res/BGM/title_bgm.mp3", DX_PLAYTYPE_LOOP); // BGM���Đ�����
}

void TitleScene::Update()
{
	// UI�̍X�V
	for (auto ui : UIs)
	{
		ui->Update();
	}

	if (DirectInputButton.lock()->IsClick())
	{
		// �g�p������͂�DirectInput�ɂ���
		gm.playingInputType = InputType::DirectInput;
		PlaySoundMem(SE::At(SEID::Start), DX_PLAYTYPE_BACK); // ����炷
		m_isDead = true;
	}
	else if (XInputButton.lock()->IsClick())
	{
		// �g�p������͂�XInput�ɂ���
		gm.playingInputType = InputType::XInput;
		PlaySoundMem(SE::At(SEID::Start), DX_PLAYTYPE_BACK); // ����炷
		m_isDead = true;
	}
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, Image::At((unsigned char)TitleSceneImageID::BG), TRUE);

	DrawGraph(0, 0, Image::At((unsigned char)TitleSceneImageID::Text), TRUE);

	// UI�̕`��
	for (auto ui : UIs)
	{
		ui->Draw();
	}
}