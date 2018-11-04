#include "Main.h"
//#include "Backtracking.h"

#define TICK_INTERVAL			( I::Globals->interval_per_tick )
#define TIME_TO_TICKS( dt )		( floorf(( 0.5f + (float)(dt) / TICK_INTERVAL ) ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )
float Backtracking::GetEstimateServerTime()
{
	double v0; // st7@0
	INetChannelInfo* v1; // esi@1
	INetChannelInfo* v2; // eax@1
	float v3; // ST08_4@1
	float v4; // ST0C_4@1

	v1 = (INetChannelInfo*)I::Engine->GetNetChannelInfo();
	v2 = (INetChannelInfo*)I::Engine->GetNetChannelInfo();

	v3 = v1->GetAvgLatency(1);
	v4 = v2->GetAvgLatency(0);

	//return floorf(((v3 + v4) / g_pGlobals->interval_per_tick) + 0.5f) + 1 + G::UserCmdForBacktracking->tick_count;*/

	return v3 + v4 + TICKS_TO_TIME(1) + TICKS_TO_TIME(I::Globals->tickcount);

}
float Backtracking::GetNetworkLatency()
{
	// Get true latency
	INetChannelInfo *nci = I::Engine->GetNetChannelInfo();
	if (nci)
	{
		//float IncomingLatency = nci->GetAvgLatency(FLOW_INCOMING); //ppl say use only this one, but meh
		float OutgoingLatency = nci->GetLatency(0);
		return OutgoingLatency;
	}
	return 0.0f;
}
bool Backtracking::IsTickValid(tick_record record)
{
	float correct = 0;

	correct += I::Engine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
	correct += I::Engine->GetNetChannelInfo()->GetLatency(FLOW_INCOMING);
	correct += g_Backtrack->GetLerpTime();

	static ConVar* sv_maxunlag = I::CVar->FindVar("sv_maxunlag");
	correct = clamp<float>(correct, 0.0f, sv_maxunlag->GetFloat());

	float deltaTime = correct - (I::Globals->curtime - record.m_flSimulationTime);

	float latecy = 0;
	float ping = 0 ? latecy : 0.2f;

	return fabsf(deltaTime) < 0.2f;
}

ConVar* minupdate;
ConVar* maxupdate;
ConVar * updaterate;
ConVar * interprate;
ConVar* cmin;
ConVar* cmax;
ConVar* interp;

float Backtracking::GetLerpTime()
{
	if (!minupdate)
		minupdate = I::CVar->FindVar(("sv_minupdaterate"));
	if (!maxupdate)
		maxupdate = I::CVar->FindVar(("sv_maxupdaterate"));
	if (!updaterate)
		updaterate = I::CVar->FindVar(("cl_updaterate"));
	if (!interprate)
		interprate = I::CVar->FindVar(("cl_interp_ratio"));
	if (!cmin)
		cmin = I::CVar->FindVar(("sv_client_min_interp_ratio"));
	if (!cmax)
		cmax = I::CVar->FindVar(("sv_client_max_interp_ratio"));
	if (!interp)
		interp = I::CVar->FindVar(("cl_interp"));

	float UpdateRate = updaterate->GetFloat();
	float LerpRatio = interprate->GetFloat();

	return max(LerpRatio / UpdateRate, interp->GetFloat());
}

void Backtracking::UpdateBacktrackRecords(C_BaseEntity* pPlayer)
{
	int i = pPlayer->EntIndex();

	for (int j = g_Backtrack->PlayerRecord[i].records.size() - 1; j >= 0; j--)
	{
		float lerptime = g_Backtrack->GetLerpTime();
		float desired_time = g_Backtrack->PlayerRecord[i].records.at(j).m_flSimulationTime + lerptime;
		float estimated_time = g_Backtrack->GetEstimateServerTime();
		float SV_MAXUNLAG = 1.0f;
		float latency = g_Backtrack->GetNetworkLatency();
		float m_flLerpTime = g_Backtrack->GetLerpTime();
		float correct = clamp<float>(latency + m_flLerpTime, 0.0f, SV_MAXUNLAG);
		float deltaTime = correct - (estimated_time + lerptime - desired_time);

		if (fabs(deltaTime) > 0.2f)
			g_Backtrack->PlayerRecord[i].records.erase(g_Backtrack->PlayerRecord[i].records.begin() + j);
	}

	static Vector old_origin[64];

	if (PlayerRecord[i].records.size() > 0 && pPlayer->GetSimulationTime() == PlayerRecord[i].records.back().m_flSimulationTime) //already got such a record
		return;

	if (PlayerRecord[i].records.size() > 0 && PlayerRecord[i].records.back().m_flSimulationTime > pPlayer->GetSimulationTime())//Invalid lag record, maybe from diffrent game?
	{
		PlayerRecord[i].records.clear();
		return;
	}

	Vector cur_origin = pPlayer->GetOrigin();
	Vector v = cur_origin - old_origin[i];
	bool breaks_lagcomp = v.LengthSqr() > 4096.f;
	old_origin[i] = cur_origin;
	tick_record new_record;

	new_record.needs_extrapolation = breaks_lagcomp;
	static float OldLower[64];

	PlayerRecord[i].LowerBodyYawTarget = pPlayer->GetLowerBodyYaw();
	new_record.m_angEyeAngles = pPlayer->GetEyeAngles();

	new_record.m_flSimulationTime = pPlayer->GetSimulationTime();
	//new_record.m_flAnimTime = pPlayer->GetAnimTime();
	new_record.bLowerBodyYawUpdated = false;
	
	new_record.m_vecOrigin = pPlayer->GetAbsOrigin();
	new_record.m_vecVelocity = pPlayer->GetVelocity();
	new_record.m_flUpdateTime = I::Globals->curtime;
	new_record.backtrack_time = new_record.m_flSimulationTime + GetLerpTime();

	if (PlayerRecord[i].LowerBodyYawTarget != OldLower[i] || (pPlayer->GetFlags() & FL_ONGROUND && pPlayer->GetVelocity().Length() > 29.f))
		new_record.bLowerBodyYawUpdated = true;

	for (int i = 0; i < 24; i++)
		new_record.m_flPoseParameter[i] = *(float*)((DWORD)pPlayer + 0x2764 + sizeof(float) * i);

	pPlayer->SetupBones(new_record.boneMatrix, 128, 0x00000100, I::Globals->curtime);

	OldLower[i] = PlayerRecord[i].LowerBodyYawTarget;
	PlayerRecord[i].records.push_back(new_record);
}

static std::deque<CIncomingSequence>sequences;
static int lastincomingsequencenumber;
int Real_m_nInSequencenumber;



void Backtracking::ClearIncomingSequences()
{
	sequences.clear();
}

