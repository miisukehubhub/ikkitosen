#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include <vector>
#include <memory>

#include "../Scene.h"

#include "../../UI/UI.h"
#include "../../UI/Button/Button.h"

// �^�C�g���V�[��
class TitleScene : public Scene
{
public:

	TitleScene(); // �R���X�g���N�^

	~TitleScene(); // �f�X�g���N�^

	// ����������
	void Init() override;

	// �X�V����
	void Update() override;

	// �`�揈��
	void Draw() override;

private:

	std::vector<std::shared_ptr<UI>> UIs{ std::vector<std::shared_ptr<UI>>() };
	std::weak_ptr<UI> DirectInputButton;
	std::weak_ptr<UI> XInputButton;
};

#endif