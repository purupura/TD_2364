#include "GameScene.h"
#include "ShakeSoda.h"
#include <algorithm>
#include <cassert>

ShakeSoda::~ShakeSoda() {}

void ShakeSoda::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {

	assert(model);
	model_ = model;
	camera_ = camera;
	worldtransfrom_.translation_ = pos;
	input_ = KamataEngine::Input::GetInstance();
	worldtransfrom_.Initialize();
}

// ワールド座標を取得
KamataEngine::Vector3 ShakeSoda::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[3][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void ShakeSoda::Update() {

	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	// 押した方向で移動ベクトルを変更(上)
	if (input_->TriggerKey(DIK_SPACE)) {
		move.y += kJumpAcceleration;

	} else {
		// 落下速度
		move.y -= kGravityAcceleration;
	}

	worldtransfrom_.translation_.x += move.x;
	worldtransfrom_.translation_.y += move.y;

	const float kMoveLimitX = 6;
	const float kMoveLimitY = 1;

	worldtransfrom_.translation_.x = std::clamp(worldtransfrom_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldtransfrom_.translation_.y = std::clamp(worldtransfrom_.translation_.y, -kMoveLimitY, kMoveLimitY);

	worldtransfrom_.updateMatrix();
}

void ShakeSoda::Draw() { model_->Draw(worldtransfrom_, *camera_); }

AABB ShakeSoda::GetAABB() {
	KamataEngine::Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

