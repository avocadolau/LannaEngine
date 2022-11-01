#pragma once
#include "Panel.h"
#include "lnpch.h"

namespace Lanna {
	struct ShadingView
	{
		const char* name;
		bool active = false;

		ShadingView() = default;

		ShadingView(const char* Name, bool Active)
			: name(Name), active(Active) {}
	};

	class ScenePanel : public Panel
	{
	public:
		ScenePanel();
		~ScenePanel();

		void Draw() override;
		void DrawElements();
	private:
		void ImportFBX(const std::filesystem::path& path);
	private:
		std::vector<ShadingView*> m_Shadings;
#ifdef CAMERA
		const Camera* m_Camera;

#endif // CAMERA

	};

}