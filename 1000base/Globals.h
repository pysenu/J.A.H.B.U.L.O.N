#pragma once

class Globals
{
public:
	HWND CSGOWindow;
	bool RenderInit;
	DWORD Espfont;
	DWORD Menufont;
	DWORD Menufont2;
	DWORD Titlefont;
	DWORD Namefont;
	C_BaseEntity* LocalPlayer;
	Vector AimPoints[64][25];
	int EnemyIndex;
	int EntShots[64];
	int EntHits[64];
	Vector RealAngle;
	bool Shot;
	Vector OriginalAng;
	Vector LastAimVec;
	Vector backtrackorigin[64];
	matrix3x4_t RealMatrix[128];
	matrix3x4_t	FakeMatrix[128];
	matrix3x4_t	LastAimMatrix[128];
	int MissedShotsResolve[64];
	Vector scanvector;
	float damage;
	std::string ResolverStage[64];
	bool IsChokingTicks[64];
	float m_r8time;
private:
}; extern Globals* g_Globals;