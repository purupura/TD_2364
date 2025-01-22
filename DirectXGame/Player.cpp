#include "Player.h"
#include <algorithm>
#include <cassert>

Player::~Player() {

}

void Player::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& pos) {

	assert(model);
	model_ = model;
	camera_ = camera;
	worldtransfrom_.translation_ = pos;
	input_ = KamataEngine::Input::GetInstance();
	worldtransfrom_.Initialize();
}


// ワールド座標を取得
KamataEngine::Vector3 Player::GetWorldPosition() {

	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldtransfrom_.matWorld_.m[3][0];
	worldPos.y = worldtransfrom_.matWorld_.m[1][1];
	worldPos.z = worldtransfrom_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Update() {


	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.3f;
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;
	if (onGround_) {

		// 押した方向で移動ベクトルを変更(左右)
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= kCharacterSpeed;
		} else if (input_->PushKey(DIK_RIGHT)) {
			move.x += kCharacterSpeed;
		}

		// 押した方向で移動ベクトルを変更(上)
		if (input_->TriggerKey(DIK_SPACE)) {
			move.y += kJumpAcceleration;

		} else  {
			// 落下速度
			move.y -= kGravityAcceleration;
			

		}

		// 押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_A)) {
			worldtransfrom_.rotation_.y += kRotSpeed;
		} else if (input_->PushKey(DIK_D)) {
			worldtransfrom_.rotation_.y -= kRotSpeed;
		}
	}
	worldtransfrom_.translation_.x += move.x;
	worldtransfrom_.translation_.y += move.y;

	const float kMoveLimitX = 30;
	const float kMoveLimitY = 15;

	worldtransfrom_.translation_.x = std::clamp(worldtransfrom_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldtransfrom_.translation_.y = std::clamp(worldtransfrom_.translation_.y, -kMoveLimitY, kMoveLimitY);


	worldtransfrom_.updateMatrix();
}

void Player::Draw() {

	model_->Draw(worldtransfrom_, *camera_);

}