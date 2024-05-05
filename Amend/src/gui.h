#define WIDTH 450
#define HEIGHT 370

RECT rc;
HWND hwnd;

using namespace ImGui;

namespace c_gui 
{
    ImVec4 white = { 1, 1, 1, 1 };
    ImVec4 red = { 0.9804, 0.2235, 0.2118, 1 };
    ImVec4 gray = { 0.7f, 0.7f, 0.7f, 1.0f };
    ImVec4 purp = { 0.2588f, 0.1686f, 0.7098f, 1.0f };

    char user[64] = "";
    char pass[64] = "";
    char license[64] = "";

    static bool newUser = false;

    static bool logged = false;

    static float item1Ypos = 350;
    static float item2Ypos = 400;
    static float item3Ypos = -250;
    static float item4Ypos = -170;
    static float item5Ypos = -80;
    static float item6Ypos = -60;
    static float item7Ypos = -10;
    bool button1Active = true;
    bool button2Active = false;

    static bool change_alpha = false;
    static float menu_alpha = 1.f;
    
    static bool IsAll0 = false;

	class gui
	{

	public:

        DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoSavedSettings;
        
        void sws(float X, float Y)
        {
            SetWindowSize({ X, Y });
        }

        void setDefaultValuesForLogin()
        {
            item1Ypos = 350;
            item2Ypos = 400;
            item3Ypos = -250;
            item4Ypos = -170;
            item5Ypos = -80;
            item6Ypos = -20;
            item7Ypos = -10;
        }

        void anims()
        {
            if (item1Ypos >= 30) 
            {
                if (item1Ypos >= 60) 
                {
                    item1Ypos -= 3.5;
                }
                else 
                {
                    item1Ypos -= 1.2;
                }
                ImGui::SetCursorPosY(item1Ypos);
            }

            if (item2Ypos >= 60)
            {
                if (item2Ypos >= 90)
                {
                    item2Ypos -= 3.5;
                }
                else
                {
                    item2Ypos -= 1.3;
                }
                ImGui::SetCursorPosY(item2Ypos);
            }

            if (item3Ypos <= 120)
            {
                if (item3Ypos <= 90)
                {
                    item3Ypos += 3.5;
                }
                else
                {
                    item3Ypos += 1.5;
                }
                ImGui::SetCursorPosY(item3Ypos);
            }

            if (item4Ypos <= 170)
            {
                if (item4Ypos <= 140)
                {
                    item4Ypos += 3.5;
                }
                else
                {
                    item4Ypos += 1.4;
                }
                ImGui::SetCursorPosY(item4Ypos);
            }

            if (item5Ypos <= 220)
            {
                if (item5Ypos <= 190)
                {
                    item5Ypos += 3.5;
                }
                else
                {
                    item5Ypos += 1.2;
                }
                ImGui::SetCursorPosY(item5Ypos);
            }

            if ((item6Ypos <= 280 && newUser) || (item6Ypos <= 230 && !newUser))
            {
                if (item6Ypos <= 250 || item6Ypos <= 220)
                {
                    item6Ypos += 3.5;
                }
                else
                {
                    item6Ypos += 1.2;
                }
                ImGui::SetCursorPosY(item6Ypos);
            }
            else if (item6Ypos <= 230 && !newUser)
            {
                item6Ypos = -90;
                ImGui::SetCursorPosY(item6Ypos);
            }

            if (item7Ypos <= 330)
            {
                if (item7Ypos <= 300)
                {
                    item7Ypos += 4.;
                }
                else
                {
                    item7Ypos += 1.5;
                }
                ImGui::SetCursorPosY(item7Ypos);
            }
        }
        void mw() { //makes possible moving the window

            GetWindowRect(hwnd, &rc);

            if (ImGui::GetWindowPos().x != 0 || ImGui::GetWindowPos().y != 0)
            {
                MoveWindow(hwnd, rc.left + ImGui::GetWindowPos().x, rc.top + ImGui::GetWindowPos().y, WIDTH, HEIGHT, TRUE);
                ImGui::SetWindowPos(ImVec2(0.f, 0.f));
            }
        }
        bool checkbox(const char* name, bool& f, float posX, float posY)
        {
            setpos(posX, posY);
            return ImGui::Checkbox(name, &f);
        }

        void apstyle()
        {
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.23f, 0.23f, 0.23f, 0.5)); //FOR INPUT TEXT BG
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2588f, 0.1686f, 0.7098f, 0.7f)); //NORMAL BUTTON COLOR
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3588f, 0.2686f, 0.8098f, 0.7f)); //BUTTON HOVERED
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3588f, 0.2686f, 0.8098f, 0.7f)); //BUTTON ACTIVE
            ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.2588f, 0.1686f, 0.7098f, 0.7f)); //CHECKBOX TICK COLOR
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3588f, 0.2686f, 0.8098f, 0.7f));
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.3588f, 0.2686f, 0.8098f, 0.7f));
        }

        void pushFont(int x)
        {
            ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[x]);
        }

        void begin(const char* name, float X, float Y, float op)
        {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0941, 0.0941, 0.1059, op));

            ImGui::Begin(name, NULL, window_flags);
            sws(X, Y);
        }

        void end()
        {
            ImGui::End();
        }

        void COText(const char* text, float posX, float posY, ImVec4 color, float op)
        {
            setpos(posX, posY);
            ImGui::TextColored(color, text);
        }

        void CEText(const char* text, float posX, float posY, ImVec4 color)
        {
            auto windowWidth = ImGui::GetWindowSize().x;
            auto textWidth = ImGui::CalcTextSize(text).x;

            ImGui::SetCursorPos(ImVec2((windowWidth - textWidth) * 0.5f + posX, posY));
            ImGui::TextColored(color, text);
        }

        bool button(const char* name, float sizeX, float sizeY, float posX, float posY)
        {
            SetCursorPos({ posX, posY });
            return ImGui::Button(name, ImVec2(sizeX, sizeY));
        }

        bool ibutton(const char* name, float posX, float posY, float sizeX, float sizeY, IDirect3DTexture9* texture, bool& isActive)
        {
            if (isActive)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3588f, 0.2686f, 0.8098f, 0.7f));
            }

            else
            {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2588f, 0.1686f, 0.7098f, 0.7f));
            }

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(sizeX, sizeY));
            setpos(posX, posY);
            bool pressed = ImGui::ImageButton(name, texture, ImVec2(32, 32));
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();

            if (pressed)
            {
                isActive = true;
            }

            return pressed;
        }

        void hintInput(const char* name, const char* hint, char test[], int x, float posX, float posY, float width)
        {
            ImGui::SetNextItemWidth(width);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 10));
            SetCursorPos({ posX, posY });

            ImGui::InputTextWithHint(name, hint, test, x);
            TreePop();
            ImGui::PopStyleVar();
        }

        void hintInputPass(const char* name, const char* hint, char test[], int x, float posX, float posY, float width)
        {
            ImGui::SetNextItemWidth(width);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 10));
            SetCursorPos({ posX, posY });

            ImGui::InputTextWithHint(name, hint, test,x, ImGuiInputTextFlags_Password);
            TreePop();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
        }

        void child(const char* name, float sizeX, float sizeY, float posX, float posY, float op)
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.3, 0.3, 0.3, op));
            SetCursorPos({ posX, posY });
            ImGui::BeginChild(name, { sizeX, sizeY });
        }

        void endChild()
        {
            ImGui::EndChild();
        }

        void setpos(float X, float Y)
        {
            SetCursorPos({ X, Y });
        }
	};
}