#pragma once
#include "Enemy.h"
#include "KamataEngine.h"
#include "Player.h"
#include "Rocket.h"
#include "Skydome.h"
#include "Soda.h"
#include "bill.h"
#include "field.h"
#include <random>

using namespace KamataEngine;

class GameScene {
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Rocket* rocket_ = nullptr;

	Model* modelRocket = nullptr;

	uint32_t textureHandle_ = 0;
	uint32_t enemyTextureHandle_ = 0;

	Camera camera_;

	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	uint32_t TextureHandle_ = 0;
	Sprite* hpBarSprite_ = nullptr;

	// 音楽
	uint32_t soundDataHandle_ = 0;
	uint32_t soundDataHandle2_ = 0;
	uint32_t voiceHandle_ = 0;
};