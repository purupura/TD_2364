#pragma once
#include "mathUtility.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

class Player;



class Rocket {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);
	void Update();
	void Draw();
	~Rocket();

	KamataEngine::Vector3 GetWorldPosition();

private:
	KamataEngine::WorldTransform WorldTransfrom_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	Player* player_ = nullptr;

	int iMin = -3;
	int iMax = 3;
};