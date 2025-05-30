//------------------------------------------------------------
// @file			world.cpp
// @brief		ワールド
//------------------------------------------------------------
#include "world.h"
#include <fstream>
#include "components/3d/model.h"

//=============================================================
// ワールドを読み込む
//=============================================================
void LoadWorld(const std::string& path)
{
	// jsonファイルを読み込む
	std::ifstream ifs(path.c_str());
	if (ifs.fail())
	{
		Log::SendLog("PLCWファイルが開けませんでした", Log::TYPE_ERROR);
		return;
	}

	// json形式に変換
	std::string inputData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto j = json::parse(inputData);

	// オブジェクト情報を取得する
	if (j.contains("x-objects"))
	{
		// パス
		for (auto pathItr = j["x-objects"].items().begin(); pathItr != j["x-objects"].items().end(); pathItr++)
		{
			std::string path = (*pathItr).key();

			// オブジェクト
			for (auto itr = j["x-objects"][path].begin(); itr != j["x-objects"][path].end(); itr++)
			{
				// トランスフォームを構築する
				Transform trans;
				trans.position = {
					(*itr)["transform"]["position"][0], (*itr)["transform"]["position"][1], (*itr)["transform"]["position"][2]
				};
				trans.rotation = {
					(*itr)["transform"]["rotation"][0], (*itr)["transform"]["rotation"][1], (*itr)["transform"]["rotation"][2], (*itr)["transform"]["rotation"][3]
				};
				trans.scale = {
					(*itr)["transform"]["scale"][0], (*itr)["transform"]["scale"][1], (*itr)["transform"]["scale"][2]
				};

				// 設置する
				GameObject* placeObj = new GameObject();
				*placeObj->transform = trans;
				placeObj->AddComponent<Model>()->Load(path);
				placeObj->name = (*itr)["name"];
				placeObj->tag = (*itr)["tag"];
			}
		}
	}

	// オブジェクト情報を取得する
	if (j.contains("prefab-objects"))
	{
		// パス
		for (auto pathItr = j["prefab-objects"].items().begin(); pathItr != j["prefab-objects"].items().end(); pathItr++)
		{
			std::string path = (*pathItr).key();

			// オブジェクト
			for (auto itr = j["prefab-objects"][path].begin(); itr != j["prefab-objects"][path].end(); itr++)
			{
				// トランスフォームを構築する
				Transform trans;
				trans.position = {
					(*itr)["transform"]["position"][0], (*itr)["transform"]["position"][1], (*itr)["transform"]["position"][2]
				};
				trans.rotation = {
					(*itr)["transform"]["rotation"][0], (*itr)["transform"]["rotation"][1], (*itr)["transform"]["rotation"][2], (*itr)["transform"]["rotation"][3]
				};
				trans.scale = {
					(*itr)["transform"]["scale"][0], (*itr)["transform"]["scale"][1], (*itr)["transform"]["scale"][2]
				};

				// 設置する
				GameObject* placeObj = GameObject::CreateObuseObject(path, trans);
				placeObj->name = (*itr)["name"];
				placeObj->tag = (*itr)["tag"];
			}
		}
	}
}