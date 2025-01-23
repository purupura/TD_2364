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

void field::Update() {
	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 10};

	worldtransfrom_.translation_.z -= move.z;

	if (worldtransfrom_.translation_.z <= -4927) {
		worldtransfrom_.translation_.z += 4927 * 2;
	}

	worldtransfrom_.updateMatrix();

	ImGui::Begin("field");
	ImGui::SliderFloat("Move X", &worldtransfrom_.translation_.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Move Y", &worldtransfrom_.translation_.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Move Z", &worldtransfrom_.translation_.z, -1.0f, 1.0f);
	ImGui::End();
}

void field::Draw() { model_->Draw(worldtransfrom_, *camera_); }