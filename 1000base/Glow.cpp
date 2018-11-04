#include "Main.h"

void Glow::RenderGlow()
{
	if (g_Vars->Visuals.Enable)
	{
		C_BaseEntity *pLocal = I::EntityList->GetClientEntity(I::Engine->GetLocalPlayer());
		for (auto i = 0; i < I::GlowManager->size; i++)
		{
			auto glow_object = &I::GlowManager->m_GlowObjectDefinitions[i];
			C_BaseEntity* pEntity = glow_object->m_pEntity;

			if (!glow_object->m_pEntity || glow_object->IsUnused())
				continue;
			if (pEntity == pLocal && g_Vars->Visuals.localglow)

			{
				Vector GlowVec;
				Color GlowClr = Color(255, 0, 100);
				GlowVec.x = GlowClr.r();
				GlowVec.y = GlowClr.g();
				GlowVec.z = GlowClr.b();
					glow_object->m_bPulsatingChams = true;
				
					glow_object->m_vGlowColor = Vector(GlowVec.x / 255, GlowVec.y / 255, GlowVec.z / 255);
				glow_object->m_flGlowAlpha = 0.7f;

				glow_object->m_bRenderWhenOccluded = true;
				glow_object->m_bRenderWhenUnoccluded = false;
			}
			if (g_Vars->Visuals.Glow)
			{
				if (pEntity->GetClientClass()->iClassID == 35)
				{

					if (pEntity->GetTeam() == pLocal->GetTeam())
						continue;

					Vector GlowVec;
					Color GlowClr = Color(180, 0, 100);
					GlowVec.x = GlowClr.r();
					GlowVec.y = GlowClr.g();
					GlowVec.z = GlowClr.b();

					glow_object->m_vGlowColor = Vector(GlowVec.x / 255, GlowVec.y / 255, GlowVec.z / 255);
					glow_object->m_flGlowAlpha = 0.6f;
					glow_object->m_bRenderWhenOccluded = true;
					glow_object->m_bRenderWhenUnoccluded = false;
				}
			}
		}
	}
}