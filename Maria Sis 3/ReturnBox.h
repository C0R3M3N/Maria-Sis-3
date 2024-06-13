#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CReturnBox : public CGameObject
{
	//int scene_id;	// target scene to switch to 

	float width;
	float height;
public:
	CReturnBox(float l, float t, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void RenderBoundingBox(void);

	//int GetSceneId() { return scene_id; }
	int IsBlocking() { return 0; }
};