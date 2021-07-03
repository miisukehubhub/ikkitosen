#ifndef SINGLETON_H_
#define SINGLETON_H_

// �V���O���g��
template<class T>
class Singleton
{
public:

    static inline T& GetInstance()
    {   
        static T instance; //���������static�ϐ��m��(�Â��ɏ�ɑҋ@����instance)
        return instance; 
    }

protected:
    Singleton() {} // �O���ł̃C���X�^���X�쐬�͋֎~
    virtual ~Singleton() {} // ���z�f�X�g���N�^

private:
    void operator=(const Singleton& obj) {} // ������Z�q�֎~
    Singleton(const Singleton& obj) {} // �R�s�[�R���X�g���N�^�֎~
    static T* instance;
};

template< class T >
T* Singleton< T >::instance = 0;

#endif
