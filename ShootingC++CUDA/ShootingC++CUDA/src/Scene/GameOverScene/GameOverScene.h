#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "../Scene.h"

// �Q�[���I�[�o�[�V�[��
class GameOverScene : public Scene
{
public:

	GameOverScene(); // �R���X�g���N�^

	~GameOverScene(); // �f�X�g���N�^

	// ����������
	void Init() override;

	// �X�V����
	void Update() override;

	// �`�揈��
	void Draw() override;

private:

	int m_toAllowActionTime{ 150 };
	int m_toAllowActionTimer{ 150 };
};

#endif