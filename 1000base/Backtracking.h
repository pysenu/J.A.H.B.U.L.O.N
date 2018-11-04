#pragma once
struct tick_record
{
	Vector m_vecOrigin;//0 //4 // 8
	bool bLowerBodyYawUpdated;

	bool bFakelagging;
	float m_flSimulationTime; //12
	float m_flAnimTime;
	int32_t m_nFlags;
	int m_nSequence;//16
	float m_flCycle; //20
	Vector m_angEyeAngles;//x->24
	Vector m_absangles;
	Vector m_vecMins;
	Vector m_vecMax;			  //void SetAbsOrigin;				  //y->28//z->32
	float m_flUpdateTime;//36
	Vector m_vecVelocity;//40 //44 //48
	std::array<float, 24> ragpos;
	float m_flPoseParameter[24];//52
	
	float backtrack_time;
	Vector m_vecAbsOrigin;
	bool needs_extrapolation = false;
	/*my addition*/
	matrix3x4_t boneMatrix[128];
};
struct player_record
{
	//std::vector<tick_record> records;
	std::vector<tick_record> records;
	Vector EyeAngles;
	float LowerBodyYawTarget;
	int Flags;
	float unknown;
};
struct simulation_record
{
	Vector origin;
	Vector velocity;
	Vector acceleration;
	float simulation_time;
	float simulation_time_increasment_per_tick;
	float update_time;

};

struct CIncomingSequence
{
	CIncomingSequence::CIncomingSequence(int instate, int outstate, int seqnr, float time)
	{
		inreliablestate = instate;
		outreliablestate = outstate;
		sequencenr = seqnr;
		curtime = time;
	}
	int inreliablestate;
	int outreliablestate;
	int sequencenr;
	float curtime;
};



class Backtracking
{
public:
	player_record PlayerRecord[64];
	simulation_record SimRecord[64][7];

	float GetLerpTime();

	void UpdateBacktrackRecords(C_BaseEntity* pPlayer);
	float GetEstimateServerTime();
	float GetNetworkLatency();
	bool IsTickValid(tick_record record);
	void ClearIncomingSequences();

}; 
extern Backtracking* g_Backtrack;

