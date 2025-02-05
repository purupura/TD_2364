#pragma once
#include "mathUtility.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

class Player;

enum class Phase {
	Approach, // 接近する
	Leave,    // 離脱する
};

class Enemy {
public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos);
	void Update();
	void Draw();
	~Enemy();

	void OnCollision();

	KamataEngine::Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }



private:
	bool EnemyIsDead_ = false;

	KamataEngine::WorldTransform enemyWorldTransfrom_;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	Player* player_ = nullptr;

	int iMin =-3;
	int iMax = 3;

};