#include "Time.h"

#include <GLFW/glfw3.h>

namespace Time {
	float timeScale{ 1.0f };
	float frameStartTime{ 0.0f };
	float unscaledDeltaTime{ 0.0f };

	float getTime() {
		return static_cast<float>(glfwGetTime());
	}

	float getDeltaTime() {
		return unscaledDeltaTime * timeScale;
	}

	float getUnscaledDeltaTime() {
		return unscaledDeltaTime;
	}

	float getTimeScale() {
		return timeScale;
	}

	void setTimeScale(float value) {
		timeScale = value;
	}

	void onFrameStart() {
		unscaledDeltaTime = getTime() - frameStartTime;
		frameStartTime = getTime();
	}
}