#include "Main.h"

void AntiAim::FreeStanding(CUserCmd* pCmd, bool bSendPacket) // cancer
{
	static float FinalAngle;
	bool bside1 = false;
	bool bside2 = false;
	bool autowalld = false;
	for (int i = 1; i <= I::Engine->GetMaxClients(); ++i) {
		C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
		if (!Entity
			|| !Entity->IsAlive()
			|| Entity->IsDormant()
	        || Entity->IsGhost()
			|| Entity == g_Globals->LocalPlayer
			|| Entity->GetTeam() == g_Globals->LocalPlayer->GetTeam())
			continue;

		float angToLocal = g_Math->CalcAngle(g_Globals->LocalPlayer->GetOrigin(), Entity->GetOrigin()).y;
		Vector ViewPoint = Entity->GetOrigin() + Vector(0, 0, 90);

		Vector2D Side1 = { (45 * sin(g_Math->GRD_TO_BOG(angToLocal))),(45 * cos(g_Math->GRD_TO_BOG(angToLocal))) };
		Vector2D Side2 = { (45 * sin(g_Math->GRD_TO_BOG(angToLocal + 180))) ,(45 * cos(g_Math->GRD_TO_BOG(angToLocal + 180))) };

		Vector2D Side3 = { (50 * sin(g_Math->GRD_TO_BOG(angToLocal))),(50 * cos(g_Math->GRD_TO_BOG(angToLocal))) };
		Vector2D Side4 = { (50 * sin(g_Math->GRD_TO_BOG(angToLocal + 180))) ,(50 * cos(g_Math->GRD_TO_BOG(angToLocal + 180))) };

		Vector Origin = g_Globals->LocalPlayer->GetOrigin();

		Vector2D OriginLeftRight[] = { Vector2D(Side1.x, Side1.y), Vector2D(Side2.x, Side2.y) };

		Vector2D OriginLeftRightLocal[] = { Vector2D(Side3.x, Side3.y), Vector2D(Side4.x, Side4.y) };

		static float dmg;

		for (int side = 0; side < 2; side++)
		{
			Vector OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 80 };
			Vector OriginAutowall2 = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };

			if (g_Autowall->CanHitFloatingPoint(OriginAutowall, ViewPoint, &dmg))
			{
				if (side == 0)
				{
					bside1 = true;
					FinalAngle = angToLocal + 90;
				}
				else if (side == 1)
				{
					bside2 = true;
					FinalAngle = angToLocal - 90;
				}
				autowalld = true;
			}
			else
			{
				for (int side222 = 0; side222 < 2; side222++)
				{
					Vector OriginAutowall222 = { Origin.x + OriginLeftRight[side222].x,  Origin.y - OriginLeftRight[side222].y , Origin.z + 80 };

					if (g_Autowall->CanHitFloatingPoint(OriginAutowall222, OriginAutowall2, &dmg))
					{
						if (side222 == 0)
						{
							bside1 = true;
							FinalAngle = angToLocal + g_Math->RandomFloat(0.f, 80.f);
						}
						else if (side222 == 1)
						{
							bside2 = true;
							FinalAngle = angToLocal - g_Math->RandomFloat(0.f, 70.f);
						}
						autowalld = true;
					}
				}
			}
		}
	}

	if (!autowalld || (bside1 && bside2))
		pCmd->viewangles.y += bSendPacket ? 90 : 180;
	else
		pCmd->viewangles.y = bSendPacket ? FinalAngle + 180 : FinalAngle;
}


void AntiAim::Move(CUserCmd* pCmd, bool *bSendPacket)
{

	if (g_Globals->LocalPlayer->IsKnifeorNade())
		return;
	

	static bool Switch = true;
	if (g_Vars->HvH.AtTargets && g_Vars->HvH.Yaws != 1)
		AtTargets(pCmd);


	

	if (!g_Aimbot->pWeapon)
		return;


		 

	if (pCmd->buttons & IN_ATTACK && g_Aimbot->CanFireWeapon(pCmd) && g_Aimbot->pWeapon->GetItemDefenitionIndex() != 64)
		return;

	else if (pCmd->buttons & IN_ATTACK && g_Aimbot->CanFireWeapon(pCmd) && g_Aimbot->pWeapon->GetItemDefenitionIndex() == 64)
	{
		if (g_Globals->m_r8time > (float)(0.25f + I::Globals->curtime))
			return;
	}
	
	if (pCmd->buttons & IN_USE)
		return;

	if (g_Aimbot->aimbotted_in_current_tick)
		return;

	if (g_Vars->HvH.down)
		pCmd->viewangles.x = 89.f;
	else if (g_Vars->HvH.half)//765.f
		pCmd->viewangles.x = 765.f;
	else if (g_Vars->HvH.jiter)
		pCmd->viewangles.x = Switch ? 720.f : 765.f;




	static int tick = 0;

	if (tick >= 180)
		tick = 0;

	if (g_Vars->HvH.yfreestand)
		FreeStanding(pCmd, *bSendPacket);
	else if (g_Vars->HvH.ytank)
		*bSendPacket ? pCmd->viewangles.y += 90.f : pCmd->viewangles.y += 180.f;
	else if (g_Vars->HvH.y180)
		*bSendPacket ? Switch ? pCmd->viewangles.y += 90.f : pCmd->viewangles.y -= 180.f : pCmd->viewangles.y += 180 + -45.f + ((tick * 2) % 90);
	
	static bool chek = true;

	if (*bSendPacket && chek)
	{
		Switch = !Switch;
		chek = false;
	}
	else if (!*bSendPacket)
		chek = true;

	tick++;

	FakeWalk(pCmd, false, *bSendPacket);
}

void AntiAim::FakeLag(bool *bSendPacket)
{/*
	if (g_Globals->LocalPlayer->IsKnifeorNade())
		return;
		*/
	auto NetChannel = I::Engine->GetNetChannel();
	if (!NetChannel)
		return;

	int wanted_choke = I::Engine->IsVoiceRecording() ? 2 : g_Vars->HvH.FakeLag;
	*bSendPacket = (NetChannel->m_nChokedPackets >= max(min(15, wanted_choke), 1));
}

void AntiAim::AtTargets(CUserCmd* pCmd)
{
	for (int i = 1; i <= I::Engine->GetMaxClients(); ++i) {
		C_BaseEntity* Entity = I::EntityList->GetClientEntity(i);
		if (!Entity
			|| !Entity->IsAlive()
			|| Entity->IsDormant()
			|| Entity == g_Globals->LocalPlayer
			|| Entity->GetTeam() == g_Globals->LocalPlayer->GetTeam())
			continue;

		pCmd->viewangles.y = g_Math->CalcAngle(g_Globals->LocalPlayer->GetOrigin(), Entity->GetOrigin()).y;
		continue;
	}
}

void AntiAim::FakeWalk(CUserCmd* pCmd, bool auto_stop, bool bSendPacket)
{
	if (!GetAsyncKeyState(VK_SHIFT) && !auto_stop)
		return;

	bSendPacket = true;
	Vector velocity = g_Globals->LocalPlayer->GetVelocity();
	int choked = I::Engine->GetNetChannel()->m_nChokedPackets;

	int ticks_left = 14 - choked;

	bSendPacket = (choked < 14) ? false : true;

	if (!choked || ticks_left < 4 || bSendPacket)
		g_Aimbot->StopMovement(pCmd);
}