#pragma once
#include "Backtracking.h"

class Aimbot {
public:
	//void Aim(CUserCmd* pCmd, bool *bSendPacket);
	void StopMovement(CUserCmd* cmd);
	void DropTarget();
	float hitchance();
	void shoot(CUserCmd * pCmd, bool * bSendPacket, Vector aimpos);
	
	void GetBoneMatrix(C_BaseEntity * target, CUserCmd * pCmd, bool * bSendPacket);

	void SelectTarget();

	void Run(CUserCmd * pCmd, bool * bSendPacket);

	
	
	

	


	Vector full_multipoint(C_BaseEntity * entity);

	Vector full_multipoint(C_BaseEntity * entity, matrix3x4_t matrix[128]);

	Vector backtrackscan(C_BaseEntity * entity, tick_record record);


	bool CanFireWeapon(CUserCmd * cmd);
	 bool aimbotted_in_current_tick = false;
	C_BaseEntity* pTarget;
	matrix3x4_t matrix[128];
	matrix3x4_t matrix2[128];

	int best_tick = 0;
	
	Vector Angle;
	
	ConVar* RecoilScale;
	int target_index = -1;
	float best_distance = 8192.f;

	bool fired_in_that_tick;
	bool aimbotted = false;
	float current_aim_simulationtime;
	int current_minusticks;
	Vector current_aim_position;
	C_BaseCombatWeapon* pWeapon;
	float current_aim_damage;
	Vector current_aim_player_origin;

	//void setup_bone_matrix(C_BaseEntity * entity, matrix3x4_t * mat);
private:
	
	


}; extern Aimbot* g_Aimbot;