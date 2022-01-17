#pragma once

class Layer
{
public:
	Layer() = default;
	~Layer() = default;

	virtual void onCreate() = 0;
	virtual void onUpdate(float deltaTime) = 0;
};
