#ifndef CLEARSCENE_H_
#define CLEARSCENE_H_

#include "../Scene.h"

// �N���A�V�[��
class ClearScene : public Scene
{
public:

	ClearScene(); // �R���X�g���N�^

	~ClearScene(); // �f�X�g���N�^

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