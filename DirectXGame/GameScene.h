#pragma once
#include "Enemy.h"
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "field.h"
#include "Soda.h"
#include "bill.h"
#include <random>

using namespace KamataEngine;

class GameScene {
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

	void SodaGage();
	void ClearTime();

	void CheckAllCollisions();



private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Player* player_ = nullptr;
	std::list<Enemy*> enemies_;
	Skydome* skydome_ = nullptr;
	std::list<field*> fields_;
	Soda* soda_ = nullptr;
	std::list<bill*> bills_;
	
	Vector3 playerPos = {0,-10.0,0};
	Vector3 fieldPos = {0, 0, 500};
	Model* modelPlayer_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelField_ = nullptr;
	Model* modelSoda_ = nullptr;
	Model* modelBill_ = nullptr;

	uint32_t textureHandle_ = 0;
	uint32_t enemyTextureHandle_ = 0;
	
	Camera camera_;

	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	float maxSodaGage = 5000;
	float nowSodaGage = maxSodaGage;
	float width = 1000;

	uint32_t hpBarTextureHandle_ = 0;
	uint32_t hpBarTextureHandle2_ = 0;
	uint32_t hpBarTextureHandle3_ = 0;
	Sprite* hpBarSprite_ = nullptr;
	Sprite* hpBarSprite2_ = nullptr;
	Sprite* hpBarSprite3_ = nullptr;

	float startTimer = 60 * 3;
	float goalTimer = 60 * 120;

	int iMin = 20;
	int iMax = 70;
};