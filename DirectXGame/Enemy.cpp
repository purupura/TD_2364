#include "Enemy.h"
#include "Player.h"

Enemy::~Enemy() {

}

void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {
	assert(model);
	model_ = model;
	camera_ = camera;
	enemyWorldTransfrom_.translation_ = pos;
	enemyWorldTransfrom_.Initialize();
}

KamataEngine::Vector3 Enemy::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = enemyWorldTransfrom_.matWorld_.m[3][0];
	worldPos.y = enemyWorldTransfrom_.matWorld_.m[3][1];
	worldPos.z = enemyWorldTransfrom_.matWorld_.m[3][2];

	return worldPos;
}

//void Enemy::OnCollision() {}


void Enemy::Update() {

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 3.0};

	// 移動(ベクトルを加算)
	enemyWorldTransfrom_.translation_.z -= move.z;

	enemyWorldTransfrom_.updateMatrix();
	ImGui::Begin("Enemy");
	ImGui::SliderFloat("Move X", &enemyWorldTransfrom_.translation_.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Move Y", &enemyWorldTransfrom_.translation_.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Move z", &enemyWorldTransfrom_.translation_.z, -1.0f, 1.0f);
	ImGui::End();
}

void Enemy::Draw() {

	model_->Draw(enemyWorldTransfrom_, *camera_);

}
