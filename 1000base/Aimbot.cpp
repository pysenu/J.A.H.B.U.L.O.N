#include "Main.h"

/*
matrix3x4_t cf[128];
Vector bkp = Entity->GetEyeAngles();
Entity->SetAbsAngles(Vector(0, Entity->GetEyeAngles().y, 0));
*reinterpret_cast<int*>(uintptr_t(Entity) + 0xA30) = I::Globals->framecount;
*reinterpret_cast<int*>(uintptr_t(Entity) + 0xA28) = 0;
Entity->SetFlags2(FL_CLIENT);

Entity->SetupBones(cf, 128, 0x100, I::Globals->curtime);
Entity->SetFlags2(flag);
Entity->SetAbsAngles(Vector(0, bkp.y, 0));

Entity->InvalidateBoneCache();
*/

int bestHitbox = -1, mostDamage;
static bool hitchanced = false;
int btdamage = 0;
int ldamage = 0;
Vector Aimbot::full_multipoint(C_BaseEntity* entity, matrix3x4_t matrix[128])
{
	auto local_player = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!local_player)
		return Vector(0, 0, 0);

	Vector local_position = local_player->GetOrigin() + local_player->GetViewOffset();

	Vector vector_best_point = Vector(0, 0, 0);

	mostDamage = g_Vars->Aimbot.MinDamage;

	
	// reset root position to flTime


	// force cycle back by boneDt


 
	

	int hitboxes[] =
	{
		HITBOX_HEAD,
		HITBOX_PELVIS,
		HITBOX_LEFT_UPPER_ARM,
		HITBOX_LEFT_FOREARM,
		HITBOX_RIGHT_UPPER_ARM,
		HITBOX_RIGHT_FOREARM,
		HITBOX_UPPER_CHEST,
		HITBOX_LEFT_CALF,
		HITBOX_RIGHT_CALF,
		HITBOX_LEFT_FOOT,
		HITBOX_RIGHT_FOOT
	};

	for (int i = 0; i < ARRAYSIZE(hitboxes); i++)
	{
		for (auto point : g_Math->GetMultiplePointsForHitbox(local_player, entity, hitboxes[i], matrix))
		{
			trace_t trace;

			int damage = g_Autowall->CanHit(local_position, point);
			if (damage > mostDamage)
			{
				bestHitbox = hitboxes[i];
				mostDamage = damage;
				vector_best_point = point;
		
				

				if (mostDamage >= entity->GetHealth())
				{
				
					return vector_best_point;
					std::memcpy(matrix2, matrix, sizeof(matrix));
					g_Globals->scanvector = vector_best_point;
				}

			}
		}
		
	}
	return vector_best_point;
	
	
}

float simtime = 0.f;
Vector Aimbot::backtrackscan(C_BaseEntity* entity, tick_record record)
{
	auto local_player = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());

	if (!local_player)
		return Vector(0, 0, 0);

	Vector local_position = local_player->GetOrigin() + local_player->GetViewOffset();

	Vector vector_best_point = Vector(0, 0, 0);

	mostDamage = g_Vars->Aimbot.MinDamage;







	int hitboxes[] =
	{
		HITBOX_HEAD,
		HITBOX_PELVIS,
		
		HITBOX_UPPER_CHEST,
		HITBOX_LEFT_FOOT,
		HITBOX_RIGHT_FOOT
	};

	

	
	
		for (int i = 0; i < ARRAYSIZE(hitboxes); i++)
		{
			for (auto point : g_Math->GetMultiplePointsForHitbox(local_player, entity, hitboxes[i], record.boneMatrix))
			{
				trace_t trace;

				int damage = g_Autowall->CanHit(local_position, point);
				if (damage > mostDamage)
				{
					bestHitbox = hitboxes[i];
					mostDamage = damage;
					vector_best_point = point;



					if (mostDamage >= entity->GetHealth())
					{

						return vector_best_point;
						btdamage = mostDamage;
					
						best_tick = TIME_TO_TICKS(record.m_flSimulationTime);
						std::memcpy(matrix2, record.boneMatrix, sizeof(record.boneMatrix));
					
						g_Globals->scanvector = vector_best_point;
						
					}

				}
			}

		}
	
	return vector_best_point;
	

}
/*
bool Aimbot::Hitscan(C_BaseEntity* Entity, C_BaseCombatWeapon* pWeapon, Vector *Aimpoint, float *LastDmg, matrix3x4_t cf[])
{
	RecoilScale = I::CVar->FindVar("weapon_recoil_scale");
	static float DamageArray[25];
	float tempDmg = 0;
	Vector tempHitbox;

	int HitboxForMuti[] = { 2, 2, 4, 4, 6, 6 };

	float angToLocal = g_Math->CalcAngle(g_Globals->LocalPlayer->GetOrigin(), Entity->GetOrigin()).y;

	Vector2D MutipointXY = { (g_Vars->Aimbot.BodyPointscale * sin(g_Math->GRD_TO_BOG(angToLocal))),(g_Vars->Aimbot.BodyPointscale * cos(g_Math->GRD_TO_BOG(angToLocal))) };
	Vector2D MutipointXY180 = { (g_Vars->Aimbot.BodyPointscale * sin(g_Math->GRD_TO_BOG(angToLocal + 180))) ,(g_Vars->Aimbot.BodyPointscale * cos(g_Math->GRD_TO_BOG(angToLocal + 180))) };
	Vector2D Mutipoint[] = { Vector2D(MutipointXY.x, MutipointXY.y), Vector2D(MutipointXY180.x, MutipointXY180.y) };

	float Velocity = abs(Entity->GetVelocity().Length2D());

	static bool initHitscan = true;

	std::vector<int> Scan;

	Scan.push_back(HITBOX_HEAD);

	if (!g_Vars->Aimbot.HeadOnly) // somebody fix this aids soon please
	{
		Scan.push_back(HITBOX_PELVIS);
		Scan.push_back(19); // pelvis mutipoint 1
		Scan.push_back(20); // pelvis mutipoint 2
		Scan.push_back(HITBOX_THORAX);
		Scan.push_back(21); // thorax mutipoint 1
		Scan.push_back(22); // thorax mutipoint 2
		Scan.push_back(HITBOX_LOWER_CHEST);
		Scan.push_back(HITBOX_UPPER_CHEST);
		Scan.push_back(23); // upper chest mutipoint 1
		Scan.push_back(24); // upper chest mutipoint 2
		Scan.push_back(HITBOX_LEFT_UPPER_ARM);
		Scan.push_back(HITBOX_RIGHT_UPPER_ARM);
		Scan.push_back(HITBOX_LEFT_THIGH);
		Scan.push_back(HITBOX_RIGHT_THIGH);
		Scan.push_back(HITBOX_RIGHT_CALF);
		Scan.push_back(HITBOX_LEFT_CALF);

		(Velocity <= 29) ? Scan.push_back(HITBOX_LEFT_FOOT) : DamageArray[HITBOX_LEFT_FOOT] = 0;
		(Velocity <= 29) ? Scan.push_back(HITBOX_RIGHT_FOOT) : DamageArray[HITBOX_RIGHT_FOOT] = 0;

		if (initHitscan)
			initHitscan = false;
	}
	else
	{
		if (!initHitscan)
		{
			for (int i = 1; i < 25; i++)
				DamageArray[i] = 0;

			initHitscan = true;
		}
	}
	matrix3x4_t cf[128];

	Vector Hitbox;


	for (int hitbox : Scan)
	{
		if (hitbox < 19)
			Hitbox = Entity->GetHitboxPosition(hitbox, cf) + Vector(0, 0, (hitbox == 0) ? -5 + g_Vars->Aimbot.HeadHeight : 0);
		else if (hitbox > 18 && hitbox < 25)
		{
			Hitbox = Entity->GetHitboxPosition(HitboxForMuti[hitbox - 19], cf);
			Hitbox = Vector(Hitbox.x + Mutipoint[((hitbox - 19) % 2)].x, Hitbox.y - Mutipoint[((hitbox - 19) % 2)].y, Hitbox.z);
		}

	
		float damage = g_Autowall->CanHit(g_Globals->LocalPlayer->GetEyePosition(), Hitbox);
		if (damage >= g_Vars->Aimbot.MinDamage && g_Vars->Aimbot.Autowall)
			DamageArray[hitbox] = damage;
		else
			DamageArray[hitbox] = 0;

		if (DamageArray[hitbox] > tempDmg)
		{
			tempHitbox = Hitbox;
			tempDmg = DamageArray[hitbox];
		}
	}

	if (tempDmg > g_Vars->Aimbot.MinDamage)
	{
		*Aimpoint = tempHitbox;
		*LastDmg = tempDmg;

		best_tick = TIME_TO_TICKS(Entity->GetSimulationTime());



		Vector HitchanceAngle = g_Math->CalcAngle(g_Globals->LocalPlayer->GetEyePosition(), tempHitbox) - g_Globals->LocalPlayer->GetAimPunchAngle() * RecoilScale->GetFloat();
		hitchanced = g_Vars->Aimbot.HitChance > 0 ? g_MiscFunc->HitChance(Entity, pWeapon, HitchanceAngle, g_Vars->Aimbot.HitChance) : true;

	}



	return false;
}
*/

bool Aimbot::CanFireWeapon(CUserCmd* cmd)
{
	auto local_player = g_Globals->LocalPlayer;
	if (!local_player || !local_player->IsAlive())
		return false;

	if (local_player->GetFlags() & FL_ATCONTROLS)
		return false;

	C_BaseCombatWeapon *weapon = (C_BaseCombatWeapon*)local_player->GetActiveWeapon();
	if (!weapon)
		return false;

	if (weapon->GetAmmo() == 0)
		return false;

	return (weapon->GetNextAttack() < I::Globals->curtime) && (weapon->GetNextAttack() < I::Globals->curtime);
}


void Aimbot::StopMovement(CUserCmd* cmd)
{
	Vector Velocity = g_Globals->LocalPlayer->GetVelocity();
	float speed = Velocity.Length();

	Vector direction;
	Vector RealView;
	g_Math->VectorAngles(Velocity, direction);
	I::Engine->GetViewAngles(RealView);
	direction.y = RealView.y - direction.y;

	Vector forward;
	g_Math->AngleVectors(direction, &forward);
	Vector negated_direction = forward * -speed;

	cmd->forwardmove = negated_direction.x;
	cmd->sidemove = negated_direction.y;
}

matrix3x4_t matrixxx[128];
void Aimbot::DropTarget()
{
	target_index = -1;
	best_distance = 99999.f;
	aimbotted_in_current_tick = false;
	fired_in_that_tick = false;
	current_aim_position = Vector();
	pTarget = nullptr;
}
void Aimbot::Run(CUserCmd* pCmd, bool *bSendPacket)
{
	ConVar* RecoilScale = I::CVar->FindVar("weapon_recoil_scale");
	bool shoot;
	static bool Shot = false;

	static float ShotTime = 0;
	Vector view;
	if (!g_Vars->Aimbot.Enable)
		return;

	I::Engine->GetViewAngles(view);
	pWeapon = g_Globals->LocalPlayer->GetActiveWeapon();

	static float Damage;

	for (int i = 1; i < 64; ++i) {
		if (i == I::Engine->GetLocalPlayer())
			continue;

		C_BaseEntity* target = I::EntityList->GetClientEntity(i);
		if (!target || target->IsDormant() || target->IsGhost() || target->GetHealth() < 1 || target->HasImmunity())
			continue;

		if (target->GetTeam() == g_Globals->LocalPlayer->GetTeam())
			continue;

		if (g_Globals->LocalPlayer->IsKnifeorNade())
			return;

		Vector aim_position = Vector(0, 0, 0);
		
		target->UpdateClientAnimation();
		target->InvalidateBoneCache();
		target->SetupBones(matrixxx, 128, 256, I::Globals->curtime);

		aim_position = full_multipoint(target, matrixxx);

	
		if (aim_position == Vector(0, 0, 0))
			continue;


		float selection_value = 0;

		selection_value = target->GetHealth();


		if (best_distance >= selection_value && aim_position != Vector(0, 0, 0)) {
		

			best_distance = selection_value;
			current_aim_position = aim_position;

	
		
			pTarget = target;
			target_index = i;
			current_aim_simulationtime = simtime;
		
			g_Globals->EnemyIndex = target->EntIndex();
		}
	}


	if (target_index != -1 && current_aim_position != Vector(0, 0, 0) && pTarget)
	{


	

	//	I::Engine->SetViewAngles(pCmd->viewangles);

		Vector HitchanceAngle = g_Math->CalcAngle(g_Globals->LocalPlayer->GetEyePosition(), current_aim_position) - g_Globals->LocalPlayer->GetAimPunchAngle() * RecoilScale->GetFloat();
		hitchanced = g_Vars->Aimbot.HitChance > 0 ? g_MiscFunc->HitChance(pTarget, pWeapon, HitchanceAngle, g_Vars->Aimbot.HitChance) : true;
	
		
		if (!(pCmd->buttons & IN_ATTACK) && hitchanced)// && !*bSendPacket)
		{
		
					if (!CanFireWeapon(pCmd) && g_Vars->Aimbot.lagshot)
						return;
					g_Globals->LocalPlayer->SetEyeAngles(HitchanceAngle);
					this->fired_in_that_tick = true;
					
					pCmd->viewangles = HitchanceAngle;
					pCmd->buttons |= IN_ATTACK;
					g_Aimbot->aimbotted_in_current_tick = false;
					g_Globals->LocalPlayer->SetEyeAngles(pCmd->viewangles);

					Shot = true;
					/* used for shot records */
					g_Globals->LastAimVec = current_aim_position;
						std::memcpy(g_Globals->LastAimMatrix, matrixxx, sizeof(matrixxx));
					g_MissedShots->AddSnapshot(pTarget);

					/* aimbot stuff */

						
					ShotTime = g_MiscFunc->FireRate(pWeapon) + I::Globals->curtime; //cancer

					if (pWeapon->GetItemDefenitionIndex() == 64)
						g_Globals->m_r8time = (float)(0.25f + I::Globals->curtime + 0.002f);
				}
			

			
			
		












	}
}