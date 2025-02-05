#include "bill.h"

void bill::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {
	worldtransfrom_.Initialize();
	model_ = model;
	camera_ = camera;
	worldtransfrom_.translation_ = pos;
}

KamataEngine::Vector3 bill::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[1][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void bill::Update() {
	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 3};

	worldtransfrom_.translation_.z -= move.z;

	if (worldtransfrom_.translation_.z <= -132.5) {
		worldtransfrom_.translation_.z += 132.5 * 4;
	}

	worldtransfrom_.updateMatrix();

}

void bill::Draw() { model_->Draw(worldtransfrom_, *camera_); }