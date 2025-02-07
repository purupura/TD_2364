#pragma once

#include "AABB.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <KamataEngine.h>
#include <list>

class Enemy;
class GameScene;

namespace KamataEngine {
class Input;
};

class ShakeSoda {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);
	void Update();
	void Draw();
	~ShakeSoda();
	AABB GetAABB();
	void OnCollision();

	KamataEngine::Vector3 GetWorldPosition();

private:

	KamataEngine::WorldTransform worldtransfrom_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0, 0, 0};

	static inline const float shakeMove = 1.0f;

};