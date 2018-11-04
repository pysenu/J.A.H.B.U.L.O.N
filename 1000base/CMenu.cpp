#include "Main.h"

void CMenu::Menu() {

	static bool PressedButtons = false;

	if (!PressedButtons && GetAsyncKeyState(VK_DELETE))
	{
		PressedButtons = true;
	}
	else if (PressedButtons && !GetAsyncKeyState(VK_DELETE))
	{
		PressedButtons = false;
		g_Vars->Menu.Opened = !g_Vars->Menu.Opened;
	}

	static Vector2D MenuPos;
	static Vector2D StoredMenuPos;
	static Vector2D StoredMousePos;

	static int DragX = 0;
	static int DragY = 0;

	static std::string w = "JAHBULON"; // insert p2c name here
	
	static std::string Tab1 = "rage";
	static std::string Tab2 = "esp";
	static std::string Tab3 = "misc";
	static std::string Tab4 = "antiaim";

	static std::string f1 = "F1";
	static std::string f2 = "F2";
	static std::string f3 = "F3";
	static std::string f4 = "F4";
	static std::string yaw = "       yaw";
	static std::string pitch = "       pitch";
	static bool IsDraggingWindow = false;

	bool click = false;
	Color jahbulon;
	switch (int(I::Globals->curtime * 1.1) % 17)
	{
	case 0:
		jahbulon = Color(255, 0, 255, 155);
		w = "  10.1.8.2.21.12.15.14  "; break;
	case 1:
		jahbulon = Color(255, 15, 255, 160);
		w = "                 J        "; break;
	case 2:
		jahbulon = Color(255, 0, 155, 165);
		w = "                JA       "; break;
	case 3:
		jahbulon = Color(100, 0, 255, 170);
		w = "               JAH      "; break;
	case 4:
		jahbulon = Color(255, 0, 0, 175);
		w = "              JAHB     "; break;
	case 5:
		jahbulon = Color(55, 0, 255, 176);
		w = "             JAHBU    "; break;
	case 6:
		jahbulon = Color(255, 0, 133, 180);
		w = "            JAHBUL   "; break;
	case 7:
		jahbulon = Color(255, 255, 200, 190);
		w = "           JAHBULO  "; break;
	case 8:
		jahbulon = Color(200, 153, 235, 210);
		w = "          JAHBULON "; break;
	case 9: 
		jahbulon = Color(255, 0, 255, 220);
		w = "         JAHBULO"; break;
	case 10:
		jahbulon = Color(255, 193, 235, 225);
		w = "        JAHBUL "; break;
	case 11:
		jahbulon = Color(255, 255, 193, 226);
		w = "       JAHBU  "; break;
	case 12:
		jahbulon = Color(200, 150, 190, 230);
		w = "      JAHB   "; break;
	case 13:
		jahbulon = Color(135, 255, 0, 235);
		w = "     JAH    "; break;
	case 14:
		jahbulon = Color(255, 135, 135, 245);
		w = "    JA     "; break;
	case 15:
		jahbulon = Color(255, 133, 133, 255);
		w = "   J      "; break;
	case 16:
		w = " 10.1.8.2.21.12.15.14 "; break;


	}

	//600, 450
	I::Surface->DrawT(MenuPos.x + 577.f, MenuPos.y + 3.f, jahbulon, g_Globals->Titlefont, true, w.c_str()); // HvH Text
	
	if (g_Vars->Menu.Opened) {
	
		

		if (GetAsyncKeyState(VK_LBUTTON))
			click = true;

		if (I::Surface->MouseInRegion(MenuPos.x + 577.f, MenuPos.y + 1.f, 22.f, 22) && click)
			g_Vars->Menu.Opened = !g_Vars->Menu.Opened;

		Vector2D MousePos = I::Surface->GetMousePosition();

		if (IsDraggingWindow && !click)
		{
			IsDraggingWindow = false;
		}

		if (IsDraggingWindow && click)
		{
			MenuPos.x = MousePos.x - DragX;
			MenuPos.y = MousePos.y - DragY;
		}

		if (I::Surface->MouseInRegion(MenuPos.x, MenuPos.y, 576, 23))
		{
			IsDraggingWindow = true;
			DragX = MousePos.x - MenuPos.x;
			DragY = MousePos.y - MenuPos.y;
		}

		//I::Surface->FilledRect(MenuPos.x, MenuPos.y, 600, 450, Color(76, 76, 76, 255)); // Main Window
		//I::Surface->DrawT(MenuPos.x + 300, MenuPos.y, Color(255, 255, 255, 255), g_Globals->Titlefont, true, Title.c_str()); // Title
		//I::Surface->FilledRect(MenuPos.x + 577, MenuPos.y + 1, 22, 22, Color(233, 0, 41, 255)); // Red Box to close menu
		/*
		I::Surface->FilledRect(MenuPos.x + 1, MenuPos.y + 24, 148, 30, Color(99, 99, 99, 255)); // Aimbot Box
		I::Surface->DrawT(MenuPos.x + 75, MenuPos.y + 31, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab1.c_str()); // Aimbot Text
		I::Surface->FilledRect(MenuPos.x + 150, MenuPos.y + 24, 149, 30, Color(99, 99, 99, 255)); // Visuals Box
		I::Surface->DrawT(MenuPos.x + 225, MenuPos.y + 31, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab2.c_str()); // Visuals Text
		I::Surface->FilledRect(MenuPos.x + 300, MenuPos.y + 24, 149, 30, Color(99, 99, 99, 255)); // Misc Box
		I::Surface->DrawT(MenuPos.x + 375, MenuPos.y + 31, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab3.c_str()); // Misc Text
		I::Surface->FilledRect(MenuPos.x + 450, MenuPos.y + 24, 149, 30, Color(99, 99, 99, 255)); // HvH Box
		I::Surface->DrawT(MenuPos.x + 525, MenuPos.y + 31, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab4.c_str()); // HvH Text
		*/
		
		static int Tab = 1;


		if (GetKeyState(VK_F1) & 0x8000)

			Tab = 1;
		else if (GetKeyState(VK_F2) & 0x8000)
			Tab = 2;
		else if (GetKeyState(VK_F3) & 0x8000)
			Tab = 3;
		else if (GetKeyState(VK_F4) & 0x8000)
			Tab = 4;
		
	
		/*
		The check boxes need to be 22 pixels away from each other 
		the sliders need to be 48 away from checkboxes
		sliders are 45 away from other sliders

		im lazy so im not making it automatic
		*/

		if (Tab == 1) // Aimbot Tab selected
		{
			I::Surface->DrawT(MenuPos.x + 20.f, MenuPos.y + 41, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab1.c_str()); // HvH Text
			I::Surface->DrawT(MenuPos.x + 23.f, MenuPos.y + 41, Color(255, 0 , 0, 195), g_Globals->Menufont, true, f1.c_str()); // HvH Text
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64.f, "Enabled", &g_Vars->Aimbot.Enable);
		
			if (g_Vars->Aimbot.Enable)
			{

				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 1 * 22.f, "AutoStop", &g_Vars->Aimbot.AutoStop);
				
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 2 * 22.f, "lagshot", &g_Vars->Aimbot.lagshot);
				Slider(MenuPos.x + 10.f, MenuPos.y + 64 + 4 * 22.f, 100.f, "mindmg", &g_Vars->Aimbot.MinDamage);
				Slider(MenuPos.x + 10.f, MenuPos.y + 64 + 6 * 22.f, 100.f, "hitchance", &g_Vars->Aimbot.HitChance);
		
				Slider(MenuPos.x + 10.f, MenuPos.y + 64 + 8 * 22.f, 100.f, "pointscale", &g_Vars->Aimbot.BodyPointscale);
			//	CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 1 * 22.f, "Name ", &g_Vars->Visuals.Name);
			}
		}
		else if (Tab == 2) // Visuals Tab selected
		{                 
			I::Surface->DrawT(MenuPos.x + 20.f, MenuPos.y + 41, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab2.c_str()); // HvH Text
			I::Surface->DrawT(MenuPos.x + 23.f, MenuPos.y + 41, Color(255, 0, 0, 195), g_Globals->Menufont, true, f2.c_str()); // HvH Text
		

			
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 1 * 22.f, "name ", &g_Vars->Visuals.Name);
				
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 9 * 22.f, "info", &g_Vars->Visuals.Info);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 2 * 22.f, "box ", &g_Vars->Visuals.Box);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 3 * 22.f, "weapon ", &g_Vars->Visuals.Weapon);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 4 * 22.f, "health ", &g_Vars->Visuals.HealthBar);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 5 * 22.f, "ammo", &g_Vars->Visuals.Ammo);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 6 * 22.f, "chams", &g_Vars->Visuals.Chams);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 8 * 22.f, "fake skeleton", &g_Vars->Visuals.Skeleton);// g_Vars->Visuals.localglow
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 9 * 22.f, "glow", &g_Vars->Visuals.Glow);
				CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 10 * 22.f, "local glow", &g_Vars->Visuals.localglow);
			
		}
		else if (Tab == 3) // Misc Tab selected
		{
			I::Surface->DrawT(MenuPos.x + 20.f, MenuPos.y + 41, Color(255, 255, 255, 255), g_Globals->Menufont, true, Tab3.c_str()); // HvH Text
			I::Surface->DrawT(MenuPos.x + 23.f, MenuPos.y + 41, Color(255, 0, 0, 195), g_Globals->Menufont, true, f3.c_str()); // HvH Text
			
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 2 * 22.f, "thirdperson", &g_Vars->Misc.ThirdPerson);
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 0 * 22.f, "bhop", &g_Vars->Misc.AutoHop);
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 3 * 22.f, "antiuntrusted", &g_Vars->Misc.ClampAngles);
			if (g_Vars->Misc.AutoHop)
				g_Vars->Misc.AutoStrafe = true;
			else
				g_Vars->Misc.AutoStrafe = false;
		}
		else if (Tab == 4) // HvH Tab selected
		{
		

			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 1 * 22.f, "dormant", &g_Vars->HvH.AtTargets);
			//
			I::Surface->DrawT(MenuPos.x + 10.f, MenuPos.y + 64 + 2 * 22.f, Color(255, 0, 0, 195), g_Globals->Menufont, true, pitch.c_str()); // HvH Text
	

			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 3 * 22.f, "down", &g_Vars->HvH.down);
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 4 * 22.f, "half ", &g_Vars->HvH.half);
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 5 * 22.f, "jitter ", &g_Vars->HvH.jiter);
			I::Surface->DrawT(MenuPos.x + 10.f, MenuPos.y + 64 + 6 * 22.f, Color(255, 0, 0, 195), g_Globals->Menufont, true, yaw.c_str()); // HvH Text
		
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 7 * 22.f, "freestanding", &g_Vars->HvH.yfreestand);
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 8 * 22.f, "tank", &g_Vars->HvH.ytank);
			CheckBox(MenuPos.x + 10.f, MenuPos.y + 64 + 9 * 22.f, "180z", &g_Vars->HvH.y180);

		
			Slider(MenuPos.x + 10.f, MenuPos.y + 64 + 11 * 22.f, 15.f, "FakeLag", &g_Vars->HvH.FakeLag);
		}
	}
}
void gradient_verticle(int x, int y, int w, int h, Color c1, Color c2)
{
	I::Surface->DrawRect(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = i, fh = h;
		float a = fi / fh;
		DWORD ia = a * 255;
		I::Surface->DrawRect(x, y + i, w, 1, Color(first, second, third, ia));
	}
}
void CMenu::CheckBox(int x, int y, std::string name, bool* item)
{
	/*
	draw.gradient_verticle(a.x, a.y, 9, 9, Color(55, 55, 55, 255), Color(40, 40, 40, 245));
	draw.outline(a.x, a.y, 9, 9, Color(2, 2, 2, 255));
	*/
//	I::Surface->OutlinedRect(x, y, 18.f, 18.f, Color(99.f, 99.f, 99.f, 255));
	gradient_verticle(x, y, 14, 14, Color(55, 55, 55, 255), Color(40, 40, 40, 190));
	I::Surface->OutlinedRect(x, y, 14, 14, Color(2, 2, 2, 255));
	static bool pressed = false;

	if (!GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y, 15, 15))
	{
		if(pressed)
			*item = !*item;
		pressed = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y, 15, 15) && !pressed)
	{
		pressed = true;
	}

	if (*item == true)
	{
		
		gradient_verticle(x, y, 15, 15, Color(2, 2, 2, 255), Color(2, 2, 2, 255));
		I::Surface->OutlinedRect(x, y, 15, 15, Color(55, 55, 55, 255));
	}
		//I::Surface->FilledRect(x, y, 18.f, 18.f, Color(99.f, 99.f, 99.f, 255));

	I::Surface->DrawT(x + 23.f, y - 2.7f, Color(255.f, 255.f, 255.f, 255), g_Globals->Menufont, false, name.c_str());
}
void CMenu::CheckBox2(int x, int y, std::string name, bool* item)
{
	/*
	draw.gradient_verticle(a.x, a.y, 9, 9, Color(55, 55, 55, 255), Color(40, 40, 40, 245));
	draw.outline(a.x, a.y, 9, 9, Color(2, 2, 2, 255));
	*/
	//	I::Surface->OutlinedRect(x, y, 18.f, 18.f, Color(99.f, 99.f, 99.f, 255));
	
	I::Surface->DrawT(x + 23.f, y - 2.7f, Color(0.f, 0.f, 0.f, 255), g_Globals->Menufont, false, name.c_str());

	static bool pressed = false;

	if (!GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y, x + 23.f, y - 2.7f))
	{
		if (pressed)
			*item = !*item;
		pressed = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y, x + 23.f, y - 2.7f) && !pressed)
	{
		pressed = true;
	}

	if (*item == true)
	{

		I::Surface->DrawT(x + 23.f, y - 2.7f, Color(0.f, 0.f, 0.f, 255), g_Globals->Menufont, false, name.c_str());
	}
	//I::Surface->FilledRect(x, y, 18.f, 18.f, Color(99.f, 99.f, 99.f, 255));

	I::Surface->DrawT(x + 23.f, y - 2.7f, Color(255.f, 0, 0, 255), g_Globals->Menufont, false, name.c_str());
}
// minimum can only be 0 bec im bad at math
void CMenu::Sliderfloat(int x, int y, float max, std::string name, float* item)
{
	I::Surface->OutlinedRect(x, y, 192.f, 1.f, Color(99.f, 99.f, 99.f, 255));
	I::Surface->OutlinedRect(x - 3, x + 3, 192.f, 4.f, Color(99.f, 99.f, 99.f, 255));
	I::Surface->OutlinedRect(y - 3, y + 3, 1.f, 1.f, Color(99.f, 99.f, 99.f, 255));
	float PixelValue = max / 192;

	if (GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y - 12, 193, 24))
	{
		*item = (I::Surface->GetMousePosition().x - x) * PixelValue;
	}

	char buffer[24];
	sprintf_s(buffer, "[%d]", *item);
	RECT textsize = I::Surface->GetTextSizeRect(g_Globals->Menufont, name.c_str());
	I::Surface->DrawT((x + 102 + (textsize.right / 2)), y - 26.f, Color(255.f, 255.f, 255.f, 255), g_Globals->Menufont, false, buffer);
	I::Surface->DrawT(x + 96.f, y - 25.f, Color(255.f, 255.f, 255.f, 255), g_Globals->Menufont, true, name.c_str());

	I::Surface->FilledRect((x + (*item / PixelValue)), y - 6.f, 4.f, 8.f, Color(99.f, 99.f, 99.f, 255));
}
void CMenu::Slider(int x, int y, float max, std::string name, int* item)
{
	gradient_verticle(x, y, 192.f, 1.f, Color(55, 55, 55, 255), Color(40, 40, 40, 190));
//	I::Surface->OutlinedRect(x, y, 192.f, 1.f, Color(99.f, 99.f, 99.f, 255));
	I::Surface->DrawSetColor(Color(99.f, 99.f, 99.f, 255));
	
	
	//I::Surface->DrawLine(x - 3, y - 3, x + 3, y - 3);
	
	float PixelValue = max / 192;

	if (GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y - 12, 193, 24))
	{
		*item = (I::Surface->GetMousePosition().x - x) * PixelValue;
	}
	
	char buffer[24];
	sprintf_s(buffer, "[%d]", *item);
	RECT textsize = I::Surface->GetTextSizeRect(g_Globals->Menufont, name.c_str());
	I::Surface->DrawT((x + 102 + (textsize.right / 2)), y - 25.f, Color(255.f, 0.f, 255.f, 255), g_Globals->Menufont, false, buffer);
	I::Surface->DrawT(x + 96.f, y - 24.f, Color(255.f, 255.f, 255.f, 255), g_Globals->Menufont, true, name.c_str());
	I::Surface->DrawFilledCircle(Vector((x + (*item / PixelValue)), y, 0), Color(255, 0, 0, 180), 5, 30);
//	I::Surface->DrawOutlinedCircle((x + (*item / PixelValue)), y - 4.2f, 5, 30);
	//I::Surface->FilledRect((x + (*item / PixelValue)), y - 4.f, 4.f, 8.f, Color(99.f, 99.f, 99.f, 255));

}

void CMenu::SliderCombo(int x, int y, float indexes, std::string name, std::string itemname[], int* item)
{
	//I::Surface->OutlinedRect(x, y, 192.f, 1.f, Color(99.f, 99.f, 99.f, 255));

	float PixelValue = indexes / 192;

	if (GetAsyncKeyState(VK_LBUTTON) && I::Surface->MouseInRegion(x, y - 12.f, 193.f, 24))
	{
		*item = (I::Surface->GetMousePosition().x - x) * PixelValue;
	}

	name += "->";

	RECT textsize = I::Surface->GetTextSizeRect(g_Globals->Menufont, name.c_str());
	I::Surface->DrawT((x + 102 + (textsize.right / 2)), y - 26.f, Color(255.f, 255.f, 255.f, 255), g_Globals->Menufont, false, itemname[*item].c_str());
	I::Surface->DrawT(x + 96.f, y - 25.f, Color(255.f, 255.f, 255.f, 255), g_Globals->Menufont, true, name.c_str());

	I::Surface->FilledRect((x + (*item / PixelValue)), y - 4.2f, 4.f, 8.f, Color(99.f, 99.f, 99.f, 255));
}