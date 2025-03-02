//------------------------------------------------------------
// @file		title.h
// @brief	タイトルシーン
//------------------------------------------------------------
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include "scene.h"

//@brief タイトルシーン
class TitleScene : public Scene
{
public:
	void Init() override;
	void Update() override;
private:
	GameObject* m_camera;
};

#endif // !_SCENE_TITLE_H_
