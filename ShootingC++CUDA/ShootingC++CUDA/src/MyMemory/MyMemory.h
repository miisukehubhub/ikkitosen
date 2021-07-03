#ifndef MYMEMORY_H_
#define MYMEMORY_H_

namespace MyMemory
{
	extern void* baseHostPtr; // �x�[�X��CPU�������A�h���X
	extern void* hostPtr; // �A�h���X�����蓖�Ă邽�тɈړ����Ă����|�C���^
	extern void* baseDevicePtr; // �x�[�X��GPU�������A�h���X
	extern void* devicePtr; // �A�h���X�����蓖�Ă邽�тɈړ����Ă����|�C���^
	extern size_t mallocSize; // �m�ۂ���T�C�Y
	extern size_t usingSize; // �g�p����T�C�Y

	// �������m��
	void Malloc();

	// �������j��
	void Free();
}

#endif
