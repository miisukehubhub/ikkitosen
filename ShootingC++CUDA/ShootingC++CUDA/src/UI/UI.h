#ifndef UI_H_
#define UI_H_

#include "../Vector2/Vector2.h"

class UI
{
public:

	UI(Vector2 position) :m_position(position){} // �R���X�g���N�^

	virtual ~UI() = default; // �f�X�g���N�^

	virtual void Update() = 0; // �X�V����

	virtual void Draw() = 0; // �`�揈��

	virtual bool IsClick() { return false; } // �N���b�N���ꂽ���ǂ���

protected:

	Vector2 m_position;
};

#endif
