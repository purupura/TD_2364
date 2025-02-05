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

	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

private:
	bool isDead_ = false;
	bool isUp_ = true;
	bool isDown_ = false;
	KamataEngine::WorldTransform worldtransfrom_;

	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* model2_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0, 0, 0};

	static inline const float kJumpAcceleration = 1.0f;
	static inline const float kLimitFallSpeed = 0.03f;
	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.5f;
};