//------------------------------------------------------------
// @file		gameobject.cpp
// @brief	ゲームオブジェクト
// @detail	コンポーネントの情報を持ったオブジェクトです
//------------------------------------------------------------
#include "gameobject.h"
#include "component.h"
#include "components/3d/model.h"
#include <fstream>

using namespace std;
#include <vector>

// 静的メンバ変数の初期化
std::list<GameObject*> GameObject::m_gameObjects;

//=============================================================
// コンストラクタ
//=============================================================
GameObject::GameObject(std::string vName, std::string vTag, int priority)
{
	// 基本情報
	this->name = vName;
	this->tag = vTag;
	this->m_priority = priority;

	// トランスフォームを作成する
	transform = new Transform(this);

	// 優先順位で挿入する
	int idx = static_cast<int>(m_gameObjects.size());
	for (auto itr = m_gameObjects.rbegin(); itr != m_gameObjects.rend(); itr++, idx--)
	{
		if ((*itr)->m_priority <= priority)
		{
			m_gameObjects.insert(std::next(m_gameObjects.begin(), idx), this);
			return;
		}
	}

	m_gameObjects.push_back(this);
}

//=============================================================
// デストラクタ
//=============================================================
GameObject::~GameObject()
{
	// リストから削除する
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (*itr == this)
		{
			m_gameObjects.erase(itr);
			break;
		}
	}

	// トランスフォームを削除する
	if (transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
}

//=============================================================
// 初期化
//=============================================================
void GameObject::Init()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Init();
	}
}

//=============================================================
// 終了
//=============================================================
void GameObject::Uninit()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		(*itr)->Uninit();
	}
}

//=============================================================
// 更新
//=============================================================
void GameObject::Update()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->Update();
		}
	}
}

//=============================================================
// 描画
//=============================================================
void GameObject::Draw()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->Draw();
		}
	}
}

//=============================================================
// 描画UI
//=============================================================
void GameObject::DrawUI()
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->DrawUI();
		}
	}
}

//=============================================================
// すべてのオブジェクトを更新する
//=============================================================
void GameObject::AllUpdate()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->Update();
		}
	}
}

//=============================================================
// すべてのオブジェクトを描画する
//=============================================================
void GameObject::AllDraw()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->Draw();
		}
	}
}

//=============================================================
// すべてのオブジェクトをUI描画する
//=============================================================
void GameObject::AllDrawUI()
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->GetActive())
		{
			(*itr)->DrawUI();
		}
	}
}

//=============================================================
// 名前からゲームオブジェクトを取得する
//=============================================================
GameObject* GameObject::FindByName(const std::string& name)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->name == name)
		{
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// タグからゲームオブジェクトを取得する
//=============================================================
GameObject* GameObject::FindByTag(const std::string& tag)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->tag == tag)
		{
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// 名前とタグからゲームオブジェクトを取得する
//=============================================================
GameObject* GameObject::FindByNameTag(const std::string& name, const std::string& tag)
{
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if ((*itr)->name == name && (*itr)->tag == tag)
		{
			return *itr;
		}
	}
	return nullptr;
}

//=============================================================
// 親を設定する
//=============================================================
void GameObject::SetParent(GameObject* gameObject)
{
	if (gameObject != nullptr)
	{
		transform->SetParent(gameObject->transform);
	}
}

//=============================================================
// 優先順位を設定する
//=============================================================
void GameObject::SetPriority(const int& priority)
{
	if (m_priority != priority)
	{
		m_priority = priority;

		// 優先順位で移動する
		int idx = static_cast<int>(m_gameObjects.size());
		for (auto itr = m_gameObjects.rbegin(); itr != m_gameObjects.rend(); itr++, idx--)
		{
			if ((*itr)->m_priority <= priority)
			{
				m_gameObjects.splice(std::next(m_gameObjects.begin(), idx), m_gameObjects, std::find(m_gameObjects.begin(), m_gameObjects.end(), this));
				return;
			}
		}
	}
}

//=============================================================
// アクティブ状態を取得する
//=============================================================
bool GameObject::GetActive()
{
	if (transform->GetParent() != nullptr)
	{
		return transform->GetParent()->GetAttachObject()->GetActive();
	}
	return Object::GetActive();
}

//=============================================================
// コンポーネントをデタッチする
//=============================================================
void GameObject::DetachComponent(Component* component)
{
	for (auto itr = m_components.begin(); itr != m_components.end(); itr++)
	{
		if (*itr == component)
		{
			(*itr)->gameObject = nullptr;
			(*itr)->transform = nullptr;
			m_components.erase(itr);
			break;
		}
	}
}

//=============================================================
// Obuseファイルからオブジェクトを作成する
//=============================================================
GameObject* GameObject::CreateObuseObject(const std::string& path, const Transform& transform)
{
	// jsonファイルを読み込む
	std::ifstream ifs(path.c_str());
	if (ifs.fail())
	{
		Log::SendLog("ファイルが開けませんでした", Log::TYPE_ERROR);
		return nullptr;
	}

	// json形式に変換
	std::string inputData((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	auto j = json::parse(inputData);

	// オブジェクト情報が含まれていないときはエラー
	if (!j.contains("objects") || j["objects"].size() <= 0)
	{
		Log::SendLog("オブジェクト情報が取得できませんでした", Log::TYPE_ERROR);
		return nullptr;
	}

	// プレハブオブジェクトを生成する
	GameObject* prefab = new GameObject();

	// オブジェクト格納変数をつくる
	std::vector<GameObject*> objects(j["objects"].size() - 1);

	// オブジェクト情報を読み込む
	for (auto itr = j["objects"].items().begin(); itr != j["objects"].items().end(); itr++)
	{
		std::string id = (*itr).key();

		// ゲームオブジェクトを生成する
		GameObject* target = nullptr;
		if (id == "prefab")
		{
			target = prefab;
		}
		else
		{
			target = new GameObject();
		}

		// 基本情報
		if (j["objects"][id].contains("name"))
		{
			target->name = j["objects"][id]["name"];
		}
		if (j["objects"][id].contains("tag"))
		{
			target->tag = j["objects"][id]["tag"];
		}

		// トランスフォーム情報
		if (j["objects"][id].contains("transform"))
		{
			// 位置
			if (j["objects"][id]["transform"].contains("position"))
			{
				target->transform->position = {
					j["objects"][id]["transform"]["position"][0],
					j["objects"][id]["transform"]["position"][1],
					j["objects"][id]["transform"]["position"][2]
				};
			}

			// 回転
			if (j["objects"][id]["transform"].contains("rotation"))
			{
				target->transform->rotation = {
					j["objects"][id]["transform"]["rotation"][0],
					j["objects"][id]["transform"]["rotation"][1],
					j["objects"][id]["transform"]["rotation"][2],
					j["objects"][id]["transform"]["rotation"][3]
				};
			}

			// スケール
			if (j["objects"][id]["transform"].contains("scale"))
			{
				target->transform->scale = {
					j["objects"][id]["transform"]["scale"][0],
					j["objects"][id]["transform"]["scale"][1],
					j["objects"][id]["transform"]["scale"][2]
				};
			}
		}

		// プレハブのみトランスフォームを適用する
		if (id == "prefab")
		{
			prefab->transform->position += transform.position;
			prefab->transform->rotation *= transform.rotation;
			prefab->transform->scale.x *= transform.scale.x;
			prefab->transform->scale.y *= transform.scale.y;
			prefab->transform->scale.z *= transform.scale.z;
		}

		// モデル情報
		if (j["objects"][id].contains("model"))
		{
			target->AddComponent<Model>()->Load(j["objects"][id]["model"]);
		}

		// コライダー情報
		if (j["objects"][id].contains("collider"))
		{
			for (auto cols = j["objects"][id]["collider"].begin(); cols != j["objects"][id]["collider"].end(); cols++)
			{
				// タイプ
				if (!(*cols).contains("type")) continue;
				std::string colType = (*cols)["type"];

				// 基本設定の関数（オフセットと回転）
				auto defaultCollider = [cols](Collider* col) {
					if ((*cols).contains("offset"))
					{
						col->SetOffset({ (*cols)["offset"][0], (*cols)["offset"][1], (*cols)["offset"][2] });
					}
					if ((*cols).contains("rotation"))
					{
						col->SetRotation({ (*cols)["rotation"][0], (*cols)["rotation"][1], (*cols)["rotation"][2], (*cols)["rotation"][3] });
					}
				};

				// タイプごとの処理
				if (colType == "box")
				{
					BoxCollider* col = target->AddComponent<BoxCollider>();
					defaultCollider(col);
					if ((*cols).contains("size"))
					{
						col->SetSize({ (*cols)["size"][0], (*cols)["size"][1], (*cols)["size"][2] });
					}
				}
				else if (colType == "sphere")
				{
					SphereCollider* col = target->AddComponent<SphereCollider>();
					defaultCollider(col);
					if ((*cols).contains("radius"))
					{
						col->SetRadius((*cols)["radius"]);
					}
				}
				else if (colType == "capsule")
				{
					CapsuleCollider* col = target->AddComponent<CapsuleCollider>();
					defaultCollider(col);
					if ((*cols).contains("radius"))
					{
						col->SetRadius((*cols)["radius"]);
					}
					if ((*cols).contains("height"))
					{
						col->SetHeight((*cols)["height"]);
					}
				}
				else if (colType == "cylinder")
				{
					CylinderCollider* col = target->AddComponent<CylinderCollider>();
					defaultCollider(col);
					if ((*cols).contains("radius"))
					{
						col->SetRadius((*cols)["radius"]);
					}
					if ((*cols).contains("height"))
					{
						col->SetHeight((*cols)["height"]);
					}
				}
				else if (colType == "cone")
				{
					ConeCollider* col = target->AddComponent<ConeCollider>();
					defaultCollider(col);
					if ((*cols).contains("radius"))
					{
						col->SetRadius((*cols)["radius"]);
					}
					if ((*cols).contains("height"))
					{
						col->SetHeight((*cols)["height"]);
					}
				}
			}
		}

		// コリジョン情報
		Collision* collision = target->GetComponent<Collision>();
		if (collision != nullptr && j["objects"][id].contains("collision"))
		{
			// 摩擦量
			if (j["objects"][id]["collision"].contains("friction"))
			{
				collision->SetFriction(j["objects"][id]["collision"]["friction"]);
			}

			// プレハブのとき
			if (id == "prefab" && j["objects"][id]["collision"].contains("rigidbody"))
			{
				// リジッドボディか
				if (j["objects"][id]["collision"]["rigidbody"])
				{
					prefab->AddComponent<RigidBody>();

					// 質量
					if (j["objects"][id]["collision"].contains("mass"))
					{
						prefab->GetComponent<RigidBody>()->SetMass(j["objects"][id]["collision"]["mass"]);
					}
				}
			}

			// トリガーか
			if (prefab->GetComponent<RigidBody>() == nullptr &&
				j["objects"][id]["collision"].contains("trigger"))
			{
				collision->SetTrigger(j["objects"][id]["collision"]["trigger"]);
			}
		}

		// オブジェクトを格納する
		if (id != "prefab")
		{
			objects[atoi(id.c_str())] = target;
		}
	}

	// 親子関係
	if (j.contains("parents"))
	{
		for (auto itr = j["parents"].items().begin(); itr != j["parents"].items().end(); itr++)
		{
			int target = atoi((*itr).key().c_str());
			int parent = (*itr).value();

			if (parent != -1)
			{ // 通常
				objects[target]->SetParent(objects[parent]);
			}
			else
			{ // プレハブが親のとき
				objects[target]->SetParent(prefab);
			}
		}
	}

	return prefab;
}

//=============================================================
// 解放する
//=============================================================
void GameObject::Release()
{
	// 親子関係のあるオブジェクトを破棄する
	for (auto itr = m_gameObjects.begin(); itr != m_gameObjects.end(); itr++)
	{
		if (this->transform == (*itr)->transform->GetParent())
		{
			Destroy(*itr);
		}
	}

	// コンポーネントを解放する
	int idx = static_cast<int>(m_components.size());
	for (int i = idx - 1; i >= 0; i--)
	{
		Destroy(m_components[i]);
		m_components[i]->DetachGameObject();
	}
}
