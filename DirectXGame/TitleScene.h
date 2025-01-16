#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

	class TitleScene {
public:
	~TitleScene();
	void Initialize();
	void Update();
	void Draw();

	
	bool IsFinished() const { return finished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool finished_ = false;
	
	// 天球
	//Skydome* skydome_ = nullptr;
	//Model* modelSkydome_ = nullptr;

	KamataEngine::Model* modelTitle_ = nullptr;
	KamataEngine::WorldTransform worldTransform;
	KamataEngine::Camera* camera_ = nullptr;
	KamataEngine::Sprite* sprite_=nullptr;
	
	uint32_t textureHandle_ = 0;
    };
