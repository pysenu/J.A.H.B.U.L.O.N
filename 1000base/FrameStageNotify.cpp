#include "Main.h"

//unrelated variables
static char MapName[128] = "";

FrameStageNotifyFn oFrameStageNotify;
void  __stdcall Hooks::FrameStageNotify(ClientFrameStage_t curStage)
{
	
	

	static Vector oldViewPunch;
	static Vector oldAimPunch;
	g_MissedShots->FSN(curStage);

	g_MiscFunc->ThirdPerson(curStage);

	//g_MiscFunc->AnimFix(curStage);

	g_Resolver->Apply(curStage);

	if (strcmp(MapName, I::Engine->GetLevelName()))
	{
		g_Visuals->NightmodeComplete = false;
		strcpy_s(MapName, I::Engine->GetLevelName());
	}
	
	oFrameStageNotify(curStage);
}