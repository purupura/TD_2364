#include "field.h"

void field::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {
	worldtransfrom_.Initialize();
	model_ = model;
	camera_ = camera;
	worldtransfrom_.translation_ = pos;

}

KamataEngine::Vector3 field::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[1][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void field::Update() {}

void field::Draw() { model_->Draw(worldtransfrom_, *camera_); }