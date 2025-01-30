#pragma once
//#include "Enemy.h"
#include "KamataEngine.h"
#include "Player.h"
//#include "Skydome.h"
using namespace KamataEngine;


class GameScene {
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

	//void CheckAllCollisions();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Player* player_ = nullptr;
	//Enemy* enemy_ = nullptr;
	//Skydome* skydome_ = nullptr;
	Vector3 playerPos = {};
	Vector3 enemyPos = {0, 3, 100};

	Model* modelPlayer_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelSkydome_ = nullptr;

	uint32_t textureHandle_ = 0;
	uint32_t enemyTextureHandle_ = 0;

	// std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	Camera camera_;

	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	// シーンの状態を管理する列挙型
	enum class SceneState { Start, Game, Clear, Over };

	// 現在のシーンの状態を管理する変数
	SceneState sceneState = SceneState::Start;

	uint32_t texturtitle_ = 0;
	KamataEngine::Sprite* title1_ = nullptr;

	uint32_t texturtitle2_ = 0;
	KamataEngine::Sprite* title2_ = nullptr;

	uint32_t texturtitle3_ = 0;
	KamataEngine::Sprite* title3_ = nullptr;
};