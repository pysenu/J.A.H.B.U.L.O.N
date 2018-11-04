#include "Main.h"

CreateMoveFn oCreateMove;
bool __stdcall Hooks::CreateMove(float flInputSampleTime, CUserCmd* pCmd)
{
	if (!I::Engine->IsInGame() || !I::Engine->IsConnected() || !g_Globals->LocalPlayer || !g_Globals->LocalPlayer->IsAlive())
		return oCreateMove(flInputSampleTime, pCmd);

	oCreateMove(flInputSampleTime, pCmd);
	if (!pCmd->command_number)
		return true;

	bool bSendPacket = true;
	g_Globals->OriginalAng = pCmd->viewangles;

	g_MiscFunc->Spoof();

	g_AntiAim->FakeLag(&bSendPacket);

	g_MiscHacks->Move(pCmd);

	g_Aimbot->DropTarget();

	g_MiscFunc->EnginePrediction(pCmd);

	g_AntiAim->Move(pCmd, &bSendPacket);

	g_Aimbot->Run(pCmd, &bSendPacket);
	if (pCmd->forwardmove > 0)
	{
		pCmd->buttons |= IN_BACK;
		pCmd->buttons &= ~IN_FORWARD;
	}

	if (pCmd->forwardmove < 0)
	{
		pCmd->buttons |= IN_FORWARD;
		pCmd->buttons &= ~IN_BACK;
	}

	if (pCmd->sidemove < 0)
	{
		pCmd->buttons |= IN_MOVERIGHT;
		pCmd->buttons &= ~IN_MOVELEFT;
	}

	if (pCmd->sidemove > 0)
	{
		pCmd->buttons |= IN_MOVELEFT;
		pCmd->buttons &= ~IN_MOVERIGHT;
	}

	//g_Math->Cl(pCmd->viewangles);
	g_Math->skeetclamp(pCmd->viewangles);
	g_MiscFunc->MovementFix(g_Globals->OriginalAng, pCmd);

	g_Globals->Shot = (pCmd->buttons & IN_ATTACK);

	Color lbyupdate;

	
	if (!bSendPacket)
	{
		
		g_Globals->RealAngle = pCmd->viewangles;
		Vector bkp = g_Globals->LocalPlayer->GetEyeAngles();
		g_Globals->LocalPlayer->SetAbsAngles(Vector(0, pCmd->viewangles.y, 0));
		g_Globals->LocalPlayer->InvalidateBoneCache();
		g_Globals->LocalPlayer->SetupBones(g_Globals->RealMatrix, 128, 0x100, I::Globals->curtime);

		g_Globals->LocalPlayer->SetAbsAngles(Vector(0, bkp.y, 0));
		g_Globals->LocalPlayer->InvalidateBoneCache();
	}
	else
	{
		Vector bkp = g_Globals->LocalPlayer->GetEyeAngles();
		g_Globals->LocalPlayer->SetAbsAngles(Vector(0, pCmd->viewangles.y, 0));
		g_Globals->LocalPlayer->InvalidateBoneCache();
		g_Globals->LocalPlayer->SetupBones(g_Globals->FakeMatrix, 128, 0x100, I::Globals->curtime);
	
		g_Globals->LocalPlayer->SetAbsAngles(Vector(0, bkp.y, 0));
		g_Globals->LocalPlayer->InvalidateBoneCache();

		
	}
	uintptr_t* yeet;
	__asm mov yeet, ebp;
	*(bool*)(*yeet - 0x1C) = bSendPacket;

	return false;
}
