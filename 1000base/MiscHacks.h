#pragma once

class MiscHacks {
public:

	void Move(CUserCmd* pCmd);
	bool IsBoneVisible(C_BaseEntity * Target, int Bone, matrix3x4_t matrix[]);
private:

	void AutoHop(CUserCmd* pCmd);

	void AutoStrafe(CUserCmd* pCmd);

	

	bool IsBoneVisible(C_BaseEntity * Target, int Bone, matrix3x4_t * matrix[]);

	bool IsBoneVisible(C_BaseEntity * Target, int Bone);

}; extern MiscHacks* g_MiscHacks;