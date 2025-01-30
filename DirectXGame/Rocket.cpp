#include "Rocket.h"
#include "Player.h"
#include <random>

Rocket::~Rocket() {}

void Rocket::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {
	assert(model);
	model_ = model;
	camera_ = camera;
	WorldTransfrom_.translation_ = pos;
	WorldTransfrom_.Initialize();
}

KamataEngine::Vector3 Rocket::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = WorldTransfrom_.matWorld_.m[3][0];
	worldPos.y = WorldTransfrom_.matWorld_.m[3][1];
	worldPos.z = WorldTransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void Rocket::Update() {

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 3.0};

	// 移動(ベクトルを加算)
	WorldTransfrom_.translation_.z -= move.z;
	WorldTransfrom_.updateMatrix();
}

void Rocket::Draw() { model_->Draw(WorldTransfrom_, *camera_); }
