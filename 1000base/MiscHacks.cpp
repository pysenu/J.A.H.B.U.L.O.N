#include "Main.h"

void MiscHacks::Move(CUserCmd* pCmd)
{
	if (g_Vars->Misc.AutoHop)
		AutoHop(pCmd);

	if (g_Vars->Misc.AutoStrafe)
		AutoStrafe(pCmd);
}

void MiscHacks::AutoHop(CUserCmd* pCmd)
{
	if (pCmd->buttons & IN_JUMP)
	{
		if (!(g_Globals->LocalPlayer->GetFlags() & FL_ONGROUND))
			pCmd->buttons &= ~IN_JUMP;
	}
}

void MiscHacks::AutoStrafe(CUserCmd* pCmd)
{
	if (!(g_Globals->LocalPlayer->GetFlags() & FL_ONGROUND) && GetAsyncKeyState(VK_SPACE))
	{
		pCmd->forwardmove = (10000.f / g_Globals->LocalPlayer->GetVelocity().Length2D() > 450.f) ? 450.f : 10000.f / g_Globals->LocalPlayer->GetVelocity().Length2D();
		pCmd->sidemove = (pCmd->mousedx != 0) ? (pCmd->mousedx < 0.0f) ? -450.f : 450.f : (pCmd->command_number % 2) == 0 ? -450.f : 450.f;
	}
}
bool MiscHacks::IsBoneVisible(C_BaseEntity* Target, int Bone, matrix3x4_t  matrix[])
{
	Vector vEnd;
	vEnd = Target->GetHitboxPosition(Bone, matrix);

	trace_t Trace;
	Ray_t Ray;

	CTraceFilter Filter;
	Filter.pSkip = g_Globals->LocalPlayer;

	Ray.Init(g_Globals->LocalPlayer->GetEyePosition(), vEnd);
	I::Trace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	if (Trace.hit_entity)
	{
		if (Trace.physicsbone <= 128 && Trace.physicsbone > 0)
		{
			return true;
		}
	}

	return false;
}
