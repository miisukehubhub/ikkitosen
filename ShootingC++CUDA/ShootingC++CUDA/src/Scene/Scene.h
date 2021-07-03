#ifndef SCENE_H_
#define SCENE_H_

#include "../GameManager/GameManager.h"

#include "SceneID.h"
#include "../Image/Image.h"

// �V�[���̊��N���X
class Scene
{
protected:

	GameManager& gm = GameManager::GetInstance();

	bool m_isDead{ false };

	SceneID nextSceneID{ SceneID::Title };

public:

	Scene() {}; // �R���X�g���N�^

	virtual ~Scene() {}; // �f�X�g���N�^

	virtual void Init() = 0; // ����������

	virtual void Update() = 0; // �X�V����

	virtual void Draw() = 0; // �`�揈��

	// isDead���擾
	bool GetIsDead() const
	{
		return m_isDead;
	}

	// isDead���Z�b�g
	void SetIsDead(const bool isDead)
	{
		this->m_isDead = isDead;
	}

	// ���̃V�[�����擾
	SceneID GetNextSceneID() const
	{
		return nextSceneID;
	}

	void SetNextSceneID(const SceneID id)
	{
		this->nextSceneID = id;
	}
};

#endif
