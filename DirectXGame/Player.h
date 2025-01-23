#pragma once

#include <3d/Camera.h>
#include <3d/Model.h>
#include <KamataEngine.h>
#include <list>
#include "AABB.h"

class Enemy;
class GameScene;

namespace KamataEngine {
class Input;
};



class Player {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);
	void Update();
	void Draw();
	~Player();
	AABB GetAABB();
	void OnCollision();

	KamataEngine::Vector3 GetWorldPosition();

	static inline const float kWidth = 1.0f;
	static inline const float kHeight = 1.0f;

private:
	bool isDead_ = false;
	bool isR_ = false;
	bool isL_ = false;
	KamataEngine::WorldTransform worldtransfrom_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Vector3 velocity_ = {0, 0, 0};

	static inline const float kJumpAcceleration = 1.0f;
	static inline const float kLimitFallSpeed = 0.03f;
	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.5f;


};