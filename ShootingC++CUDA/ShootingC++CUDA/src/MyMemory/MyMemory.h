#ifndef MYMEMORY_H_
#define MYMEMORY_H_

namespace MyMemory
{
	extern void* baseHostPtr; // ベースのCPUメモリアドレス
	extern void* hostPtr; // アドレスを割り当てるたびに移動していくポインタ
	extern void* baseDevicePtr; // ベースのGPUメモリアドレス
	extern void* devicePtr; // アドレスを割り当てるたびに移動していくポインタ
	extern size_t mallocSize; // 確保するサイズ
	extern size_t usingSize; // 使用するサイズ

	// メモリ確保
	void Malloc();

	// メモリ破棄
	void Free();
}

#endif
