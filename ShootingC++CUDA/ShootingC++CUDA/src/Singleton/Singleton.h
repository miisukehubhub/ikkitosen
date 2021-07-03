#ifndef SINGLETON_H_
#define SINGLETON_H_

// シングルトン
template<class T>
class Singleton
{
public:

    static inline T& GetInstance()
    {   
        static T instance; //メモリ上にstatic変数確保(静かに常に待機するinstance)
        return instance; 
    }

protected:
    Singleton() {} // 外部でのインスタンス作成は禁止
    virtual ~Singleton() {} // 仮想デストラクタ

private:
    void operator=(const Singleton& obj) {} // 代入演算子禁止
    Singleton(const Singleton& obj) {} // コピーコンストラクタ禁止
    static T* instance;
};

template< class T >
T* Singleton< T >::instance = 0;

#endif
