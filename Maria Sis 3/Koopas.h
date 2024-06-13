#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_HYPE_FAST_SPEED 0.20f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 26
#define KOOPA_BBOX_HEIGHT_DIE 7
#define KOOPA_BBOX_HEIGHT_HYPE 7

#define KOOPA_DIE_TIMEOUT 500
#define KOOPA_HYPE_TIMEOUT 5000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_WALKING_LEFT 600
#define KOOPA_STATE_WALKING_RIGHT 500
#define KOOPA_STATE_DIE 200
#define KOOPA_STATE_HYPE 300
#define KOOPA_STATE_UNSTABLE 400
#define KOOPA_STATE_HYPE_FAST_LEFT 700
#define KOOPA_STATE_HYPE_FAST_RIGHT 800
#define KOOPA_STATE_ON_MARIO_HAND_LEFT 900
#define KOOPA_STATE_ON_MARIO_HAND_RIGHT 1000

#define ID_ANI_KOOPA_WALKING_LEFT 7000
#define ID_ANI_KOOPA_WALKING_RIGHT 7002
//#define ID_ANI_KOOPA_DIE 7001
#define ID_ANI_KOOPA_HYPER 7001
#define ID_ANI_KOOPA_BLINK 7003

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;
	ULONGLONG hype_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void OnCollisionWithReturnBox(LPCOLLISIONEVENT e);
public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
};