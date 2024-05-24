#pragma once

namespace Time {
	float getTime();
	float getDeltaTime();
	float getUnscaledDeltaTime();
	float getTimeScale();
	void setTimeScale(float value);
	void onFrameStart();
}