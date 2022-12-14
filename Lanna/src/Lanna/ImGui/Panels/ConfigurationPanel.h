#pragma once

#include "Panel.h"
#include "Lanna/Application.h"

#include <list>

#define MAX 64

namespace Lanna {
	class ConfigurationPanel : public Panel
	{
	public:
		ConfigurationPanel();
		~ConfigurationPanel();

		void Draw() override;

	private:
		std::vector<float> fpsLog;
		std::vector<float> msLog;
		std::vector<float> allocLog;
		std::vector<float> byteLog;

		bool fullscreen = false;
		bool resizable = false;
		bool vsync = false;

		Lanna::SysInfo info;
	};

}