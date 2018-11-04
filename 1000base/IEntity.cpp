#include "Main.h"

Vector C_BaseEntity::GetHitboxPosition(int Hitbox, matrix3x4_t matrix[])
{

	studiohdr_t* hdr = I::ModelInfo->GetStudiomodel(this->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

	if (hitbox)
	{
		Vector vMin, vMax, vCenter, sCenter;
		g_Math->VectorTransform(hitbox->min, matrix[hitbox->bone], vMin);
		g_Math->VectorTransform(hitbox->max, matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) * 0.5;

		return vCenter;
	}

	return Vector(0, 0, 0);
}
Vector C_BaseEntity::GetHitboxPosition3(int Hitbox, matrix3x4_t matrix[], Vector *vMin, Vector *vMax)
{

	studiohdr_t* hdr = I::ModelInfo->GetStudiomodel(this->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

	if (hitbox)
	{
		Vector vMin2, vMax2, vCenter, sCenter;
		g_Math->VectorTransform(hitbox->min, matrix[hitbox->bone], vMin2);
		g_Math->VectorTransform(hitbox->max, matrix[hitbox->bone], vMax2);
		vCenter = (vMin2 + vMax2) * 0.5;
		*vMin = vMin2;
		*vMax = vMax2;
		return vCenter;
	}

	return Vector(0, 0, 0);
}


void C_BaseEntity::ForceSetupBonesAtTimeFakeInterpolation(matrix3x4_t *pBonesOut, float curtimeOffset)
{
	// we don't have any interpolation data, so fake it
	
	Vector origin = this->GetOrigin();

	// blow the cached prev bones
	InvalidateBoneCache();
	// reset root position to flTime


	// force cycle back by boneDt
	
	SetupBones(pBonesOut, 128, 256, I::Globals->curtime + curtimeOffset);
	
}
Vector C_BaseEntity::GetHitboxPosition2(int Hitbox, matrix3x4_t matrix[])
{
	
	Vector vMin, vMax, vCenter, sCenter;
	
		studiohdr_t * hdr = I::ModelInfo->GetStudiomodel(this->GetModel());
		mstudiohitboxset_t * set = hdr->GetHitboxSet(0);

		mstudiobbox_t * hitbox = set->GetHitbox(Hitbox);

		// Points to MultiPoint
		Vector Point[] =
		{
			Vector(hitbox->min.x, hitbox->min.y, hitbox->min.z),
			Vector(hitbox->min.x, hitbox->max.y, hitbox->min.z),
			Vector(hitbox->max.x, hitbox->max.y, hitbox->min.z),
			Vector(hitbox->max.x, hitbox->min.y, hitbox->min.z),
			Vector(hitbox->max.x, hitbox->max.y, hitbox->max.z),
			Vector(hitbox->min.x, hitbox->max.y, hitbox->max.z),
			Vector(hitbox->min.x, hitbox->min.y, hitbox->max.z),
			Vector(hitbox->max.x, hitbox->min.y, hitbox->max.z)
		};

		C_BaseEntity* pLocal = g_Globals->LocalPlayer;
		//  if ((pLocal->GetVelocity().Length2D() * 0.0078125f) > 64.0f) {
		//  vCenter += (pLocal->GetAbsOrigin() - pLocal->GetVecOrigin());
		//  }

		if (hitbox)
		{
			// Just Hitscan
			g_Math->VectorTransform(hitbox->min, matrix[hitbox->bone], vMin);
			g_Math->VectorTransform(hitbox->max, matrix[hitbox->bone], vMax);

			vCenter = ((vMin + vMax) * 0.5f);

			return vCenter;

			// Multipoint
			
				int iCount = 7;
				for (int i = 0; i <= iCount; i++)
				{
					Vector vTargetPos;
					switch (i)
					{
					case 0:
					default:
						vTargetPos = vCenter; break;
					case 1:
						vTargetPos = (Point[7] + Point[1]) * g_Vars->Aimbot.BodyPointscale; break;
					case 2:
						vTargetPos = (Point[3] + Point[4]) * g_Vars->Aimbot.BodyPointscale; break;
					case 3:
						vTargetPos = (Point[4] + Point[0]) * g_Vars->Aimbot.BodyPointscale; break;
					case 4:
						vTargetPos = (Point[2] + Point[7]) * g_Vars->Aimbot.BodyPointscale; break;
					case 5:
						vTargetPos = (Point[6] + Point[7]) * g_Vars->Aimbot.BodyPointscale; break;
					case 6:
						vTargetPos = (Point[5] + Point[3]) * g_Vars->Aimbot.BodyPointscale; break;
					case 7:
						vTargetPos = (Point[1] + Point[2]) * g_Vars->Aimbot.BodyPointscale; break;
					}
					return vTargetPos;
				}
		}
		
	


	return Vector(0, 0, 0);
}
std::vector<Vector> C_BaseEntity::GetMultiplePointsForHitbox(int iHitbox, matrix3x4_t matrix[])
{
	
	studiohdr_t* hdr = I::ModelInfo->GetStudiomodel(this->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	mstudiobbox_t* hitbox = set->GetHitbox(iHitbox);

	std::vector<Vector> vecArray;
	Vector vMin, vMax, vCenter, sCenter;
	g_Math->VectorTransform(hitbox->min, matrix[hitbox->bone], vMin);
	g_Math->VectorTransform(hitbox->max, matrix[hitbox->bone], vMax);
	vCenter = (vMin + vMax) * 0.5;

	Vector CurrentAngles = g_Math->CalcAngle(vCenter, g_Globals->LocalPlayer->GetEyePosition());

	Vector Forward;
	g_Math->AngleVectors(CurrentAngles, &Forward);

	Vector Right = Forward.Cross(Vector(0, 0, 1));
	Vector Left = Vector(-Right.x, -Right.y, Right.z);

	Vector Top = Vector(0, 0, 1);
	Vector Bot = Vector(0, 0, -1);

	switch (iHitbox) {
	case (int)HITBOX_HEAD:
		for (auto i = 0; i < 4; ++i)
		{
			vecArray.emplace_back(vCenter);
		}
		vecArray[1] += Top * (hitbox->radius * g_Vars->Aimbot.HeadHeight);
		vecArray[2] += Right * (hitbox->radius * g_Vars->Aimbot.HeadHeight);
		vecArray[3] += Left * (hitbox->radius * g_Vars->Aimbot.HeadHeight);
		break;

	default:

		for (auto i = 0; i < 3; ++i)
		{
			vecArray.emplace_back(vCenter);
		}
		vecArray[1] += Right * (hitbox->radius * g_Vars->Aimbot.BodyPointscale);
		vecArray[2] += Left * (hitbox->radius * g_Vars->Aimbot.BodyPointscale);
		break;
	}
	return vecArray;
}

C_BaseCombatWeapon* C_BaseEntity::GetActiveWeapon()
{
	static int m_hActiveWeapon = g_pNetvars->GetOffset("DT_BaseCombatCharacter", "m_hActiveWeapon");
	const auto weaponData = GetValue<CBaseHandle>(m_hActiveWeapon);
	return reinterpret_cast<C_BaseCombatWeapon*>(I::EntityList->GetClientEntityFromHandle(weaponData));
}

void C_BaseEntity::SetAbsAngles(Vector angles)
{
	using Fn = void(__thiscall*)(C_BaseEntity*, const Vector& angles);
	static Fn func;

	if (!func)
		func = (Fn)(g_Utils->FindPattern("client_panorama.dll", (BYTE*)"\x55\x8B\xEC\x83\xE4\xF8\x83\xEC\x64\x53\x56\x57\x8B\xF1\xE8", "xxxxxxxxxxxxxxx"));

	func(this, angles);
}

void C_BaseEntity::SetAbsOrigin(Vector ArgOrigin)
{
	using Fn = void(__thiscall*)(C_BaseEntity*, const Vector& origin);
	static Fn func;

	if (!func)
		func = (Fn)(g_Utils->FindPattern("client_panorama.dll", (PBYTE)"\x55\x8B\xEC\x83\xE4\xF8\x51\x53\x56\x57\x8B\xF1\xE8\x00\x00", "xxxxxxxxxxxxx??"));

	func(this, ArgOrigin);
}
bool C_BaseEntity::IsScp()
{
	C_BaseCombatWeapon *pWeapon = (C_BaseCombatWeapon*)this->GetActiveWeapon();

	if (!pWeapon)
		return false;

	std::string WeaponName = pWeapon->GetName();

	if (WeaponName == "weapon_awp")
		return true;
	else if (WeaponName == "weapon_ssg08")
		return true;
	else if (WeaponName == "weapon_g3sg1")
		return true;
	else if (WeaponName == "weapon_scar20")
		return true;
	

	return false;
}
bool C_BaseEntity::IsKnifeorNade()
{
	C_BaseCombatWeapon *pWeapon = (C_BaseCombatWeapon*)this->GetActiveWeapon();

	if (!pWeapon)
		return false;

	std::string WeaponName = pWeapon->GetName();

	if (WeaponName == "weapon_knife")
		return true;
	else if (WeaponName == "weapon_incgrenade")
		return true;
	else if (WeaponName == "weapon_decoy")
		return true;
	else if (WeaponName == "weapon_flashbang")
		return true;
	else if (WeaponName == "weapon_hegrenade")
		return true;
	else if (WeaponName == "weapon_smokegrenade")
		return true;
	else if (WeaponName == "weapon_molotov")
		return true;

	return false;
}

bool C_BaseEntity::IsKnife()
{
	C_BaseCombatWeapon *pWeapon = (C_BaseCombatWeapon*)this->GetActiveWeapon();

	if (!pWeapon)
		return false;

	std::string WeaponName = pWeapon->GetName();

	if (WeaponName == "weapon_knife")
		return true;

	return false;
}

bool C_BaseEntity::IsNade()
{
	C_BaseCombatWeapon *pWeapon = (C_BaseCombatWeapon*)this->GetActiveWeapon();

	if (!pWeapon)
		return false;

	std::string WeaponName = pWeapon->GetName();

	if (WeaponName == "weapon_incgrenade")
		return true;
	else if (WeaponName == "weapon_decoy")
		return true;
	else if (WeaponName == "weapon_flashbang")
		return true;
	else if (WeaponName == "weapon_hegrenade")
		return true;
	else if (WeaponName == "weapon_smokegrenade")
		return true;
	else if (WeaponName == "weapon_molotov")
		return true;

	return false;
}

void C_BaseEntity::InvalidateBoneCache()
{
	static uintptr_t InvalidateBoneCache = g_Utils->FindPattern("client_panorama.dll", (PBYTE)"\x80\x3D\x00\x00\x00\x00\x00\x74\x16\xA1", "xx????xxxx");
	static uintptr_t g_iModelBoneCounter = **(uintptr_t**)(InvalidateBoneCache + 10);
	static 	uintptr_t m_nForceBone = g_pNetvars->GetOffset("DT_BaseAnimating", "m_nForceBone");;
	*(int*)((uintptr_t)this + m_nForceBone + 0x20) = 0;
	*(uintptr_t*)((uintptr_t)this + 0x2914) = 0xFF7FFFFF;
	*(uintptr_t*)((uintptr_t)this + 0x2680) = (g_iModelBoneCounter - 1);
}

// Invalidates the abs state of all children
void C_BaseEntity::InvalidatePhysicsRecursive(int nChangeFlags) // mutiny
{
	//55  8B  EC  83  E4  F8  83  EC  0C  53  8B  5D  08  8B  C3  56  83  E0  04

	static DWORD AdrOf_InvalidatePhysicsRecursive = g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 0C 53 8B 5D 08 8B C3 56 83 E0 04");

	return ((void(__thiscall*)(C_BaseEntity*, int))AdrOf_InvalidatePhysicsRecursive)(this, nChangeFlags);
}

CUtlVectorSimple* C_BaseEntity::GetAnimOverlayStruct()
{
	return (CUtlVectorSimple*)((DWORD)this + 0x2970);
}

AnimationLayer* C_BaseEntity::GetAnimOverlay(int i)
{
	if (i >= 0 && i < 15)
	{
		CUtlVectorSimple *m_AnimOverlay = GetAnimOverlayStruct();
		return (AnimationLayer*)m_AnimOverlay->Retrieve(i, sizeof(AnimationLayer));

	}
	return nullptr;
}

int C_BaseEntity::GetNumAnimOverlays()
{
	CUtlVectorSimple *m_AnimOverlay = GetAnimOverlayStruct();
	return m_AnimOverlay->count;
}

int C_BaseEntity::GetSequenceActivity(int sequence) {
	const auto model = GetModel();
	if (!model)
		return -1;

	const auto hdr = I::ModelInfo->GetStudiomodel(model);
	if (!hdr)
		return -1;

	static auto offset = (DWORD)g_Utils->FindPatternIDA("client_panorama.dll", "55 8B EC 83 7D 08 FF 56 8B F1 74 3D");
	static auto GetSequenceActivity = reinterpret_cast< int(__fastcall*)(void *, studiohdr_t *, int) >(offset);

	return GetSequenceActivity(this, hdr, sequence);
}


bool C_BaseCombatWeapon::IsReloading()
{
	static auto inReload = *(uint32_t*)(g_Utils->FindPatternIDA("client_panorama.dll", "C6 87 ? ? ? ? ? 8B 06 8B CE FF 90") + 2);
	return *(bool*)((uintptr_t)this + inReload);
}

bool C_BaseCombatWeapon::CanFire()
{
	if (IsReloading() || GetAmmo() <= 0)
		return false;
}