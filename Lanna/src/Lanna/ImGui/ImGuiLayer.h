#pragma once

#include "Lanna/ImGui/ImGuiLog.h"
#include "Lanna/Layer.h"

#include "Lanna/Events/ApplicationEvent.h"
#include "Lanna/Events/KeyEvent.h"
#include "Lanna/Events/MouseEvent.h"

#include "Lanna/ImGui/Panels/Panel.h"
#include "Lanna/Resources/Texture.h"

#include <vector>

namespace Lanna {

	class LANNA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;

		// Scene Serialization functions
		void SaveAScene();
		void OpenAScene();

		void Begin();
		void End();

		void OnEvent(Event& event) override;
		void OnImGuiRender() override;


		enum class SceneState
		{
			Edit = 0, Play = 1
		};

		SceneState m_SceneState = SceneState::Edit;

		Texture* m_IconPlay;
		Texture* m_IconStop;
		Texture* m_IconPause;


	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		void MainMenuBar();
		void DockSpace();

	private:
		bool logActive;

		float m_Time = 0.0f;

		Panel* m_about = nullptr;
		Panel* m_configuration = nullptr;
		Panel* m_hardware = nullptr;
		Panel* m_scene = nullptr;
		Panel* m_Inspector = nullptr;
		Panel* m_Hierarchy = nullptr;
		Panel* m_Assets = nullptr;
		Panel* m_GameScene = nullptr;
		Panel* m_Animation = nullptr;

		std::vector<Panel*> m_panels;

	};

}
