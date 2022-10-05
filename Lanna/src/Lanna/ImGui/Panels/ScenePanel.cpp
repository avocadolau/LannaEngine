#include "lnpch.h"
#include "ScenePanel.h"
#include <gl/GL.h>

#include <imgui.h>

ScenePanel::ScenePanel(): Panel("Scene")
{
	active = true;
	m_Shadings.push_back(new ShadingView("Default", true));
	m_Shadings.push_back(new ShadingView("Wireframe", true));
	m_Shadings.push_back(new ShadingView("Stil WIP T_T", true));

#ifdef CAMERA
	m_Camera = new Camera(45.0f, 0.1f, 100.0f);

#endif // CAMERA


}

ScenePanel::~ScenePanel()
{

	m_Shadings.clear();
}

void ScenePanel::Draw()
{
	ImGui::Begin(name, &active, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Shading"))
		{
			for (auto c : m_Shadings)
			{
				if (ImGui::MenuItem(c->name, "", &c->active))
				{
					LN_INFO("{0}, {1}", c->name, c->active);
				}
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}


	// draw geometry
	
	DrawElements();

	ImGui::End();

}

void ScenePanel::DrawElements()
{
	glBegin(GL_TRIANGLES);

	glVertex3f(0.5f, 0.f, 0.f);
	glVertex3f(0.f, 0.5f, 0.f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glEnd();
}
