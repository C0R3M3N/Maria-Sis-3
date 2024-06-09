#include "Koopas.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	die_start = -1;
	SetState(KOOPA_STATE_WALKING_LEFT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_DIE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_KOOPA_DIE;
	}
	else if (vx < 0)
	{
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}
	else {
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}
	/*else if (state == KOOPA_STATE_WALKING_LEFT) {
		aniId = ID_ANI_KOOPA_WALKING_LEFT;
	}
	else if (state == KOOPA_STATE_WALKING_RIGHT) {
		aniId = ID_ANI_KOOPA_WALKING_RIGHT;
	}*/

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPA_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		nx = -1;
		break;
	case KOOPA_STATE_WALKING_RIGHT:
		vx = -KOOPA_WALKING_SPEED;
		nx = 1;
		break;
	}
}
