#pragma once

#include <string_view>

namespace Constants {
	inline constexpr int openGlVersionMajor{ 4 };
	inline constexpr int openGlVersionMinor{ 6 };
	inline constexpr int defaultWindowWidth{ 800 };
	inline constexpr int defaultWindowHeight{ 600 };
	inline constexpr std::string_view windowTitle{ "Minecraft Clone 2" };
	inline constexpr int defaultDebugNumberPrecision{ 2 };
	inline constexpr float defaultCameraFovDegrees{ 45.0f };
	inline constexpr float defaultCameraNearPlane{ 0.1f };
	inline constexpr float defaultCameraFarPlane{ 100.0f };
}