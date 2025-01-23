#include "Enemy.h"
#include "Player.h"

Enemy::~Enemy() {

}

void Enemy::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {
	assert(model);
	model_ = model;
	camera_ = camera;
	worldtransfrom_.translation_ = pos;
	worldtransfrom_.Initialize();
}

KamataEngine::Vector3 Enemy::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

//void Enemy::OnCollision() {}


void Enemy::Update() {

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 3.0};

	// 移動(ベクトルを加算)
	worldtransfrom_.translation_.z -= move.z;

	worldtransfrom_.updateMatrix();


}

void Enemy::Draw() {

	model_->Draw(worldtransfrom_, *camera_);

}
