#pragma once
#include "Enemy.h"
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include "field.h"
#include "Soda.h"
#include "bill.h"
#include "Rocket.h"
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
	void BikeMove();

	void CheckAllCollisions();
	void SkyFry();


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
	Rocket* rocket_= nullptr;
	
	Vector3 playerPos = {0,-10.0,0};
	Vector3 fieldPos = {0, 0, 500};
	Vector3 rocketPos = {0, -10, playerPos.z + 500};
	Model* modelPlayer_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelField_ = nullptr;
	Model* modelSoda_ = nullptr;
	Model* modelBill_ = nullptr;
	Model* modelRocket = nullptr;

	uint32_t textureHandle_ = 0;
	uint32_t enemyTextureHandle_ = 0;
	
	Camera camera_;

	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;

	float maxSodaGage = 2880 + 60 * 67;//(6900)
	float nowSodaGage = 0;
	float width = 1000;
	float indexSoda = 0;


	uint32_t hpBarTextureHandle_ = 0;
	uint32_t hpBarTextureHandle2_ = 0;
	uint32_t hpBarTextureHandle3_ = 0;
	Sprite* hpBarSprite_ = nullptr;
	Sprite* hpBarSprite2_ = nullptr;
	Sprite* hpBarSprite3_ = nullptr;
	uint32_t goalLineTextureHandle_ = 0;
	uint32_t goalLineTextureHandle2_ = 0;
	Sprite* goalLineSprite_ = nullptr;
	Sprite* goalLineSprite2_ = nullptr;
	uint32_t skyTextureHandle_ = 0;
	Sprite* skySprite_ = nullptr;


	float limitTimer = 60;
	float goalTimer = 60 * limitTimer;

	int iMin = 20;
	int iMax = 70;

	//音楽
	uint32_t soundDataHandle_ = 0;
	uint32_t soundDataHandle2_ = 0;
	uint32_t soundDataHandle3_ = 0;
	uint32_t soundDataHandle4_ = 0;
	uint32_t voiceHandle_ = 0;
	uint32_t voiceHandle2_ = 0;
	uint32_t voiceHandle3_ = 0;
	uint32_t voiceHandle4_ = 0;
	bool isBGMPlaying_ = false;
	bool isBGMPlaying2_ = false;
	bool isBGMPlaying3_ = false;

	// シーンの状態を管理する列挙型
	enum class SceneState { Start, Game1,Game2, Game3,Clear, Over };

	// 現在のシーンの状態を管理する変数
	SceneState sceneState = SceneState::Start;

	uint32_t texturtitle_ = 0;
	KamataEngine::Sprite* title1_ = nullptr;

	uint32_t texturtitle2_ = 0;
	KamataEngine::Sprite* title2_ = nullptr;

	uint32_t texturtitle3_ = 0;
	KamataEngine::Sprite* title3_ = nullptr;



};