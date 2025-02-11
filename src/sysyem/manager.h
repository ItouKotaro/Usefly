//------------------------------------------------------------
// @file		manager.h
// @brief	マネージャー
// @detail	システムの管理を行います
//------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//@brief 管理クラス
class Manager final
{
public:
	//@brief 初期化
	void Init();

	//@brief 終了
	void Uninit();

	//@brief 更新
	void Update();

	//@brief 描画
	void Draw();

	//@brief インスタンスの取得
	static Manager* getInstance()
	{
		static Manager instance;
		return &instance;
	}
private:

};

#endif // !_MANAGER_H_
