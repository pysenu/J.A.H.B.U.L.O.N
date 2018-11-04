#pragma once

class CVars {
public:
	struct {
		bool Opened;
	} Menu;

	struct {
		bool Enable = false;
		bool Autowall = true;
		bool HeadOnly;
		bool lagshot = false;
		bool AutoStop = true;
		int MinDamage = 15;
		int HitChance = 66;
		int HeadHeight = 5;
		int BodyPointscale = 60;
		int LagFix = 1;
	} Aimbot;

	struct {
		bool Enable = true;
		bool Name = true;
		bool Box = true;
		bool Weapon = true;
		bool HealthBar = true;
		bool Ammo = true;
		bool Chams = false;
		bool Glow = false;
		bool Skeleton = true;
		bool localglow = false;
		bool Info = true;
	} Visuals;

	struct {
		bool AutoHop = true;
		bool AutoStrafe = true;
		bool ThirdPerson = true;
		bool ClampAngles = true;
	} Misc;

	struct {
		bool AtTargets = true;
		int Pitch = 1;
		int Yaws = 1;
		int FakeLag = 7;
		bool down = true;
		bool half = false;
		bool jiter = false;
		bool yfreestand = true;
		bool ytank = false;
		bool y180 = false;
	} HvH;

	// some vars for save/setup func.
}; extern CVars* g_Vars;