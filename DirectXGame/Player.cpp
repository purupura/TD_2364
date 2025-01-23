#include "Player.h"
#include <algorithm>
#include <cassert>
#include "GameScene.h"

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


	// 押した方向で移動ベクトルを変更(左右)
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= kCharacterSpeed;
		    isR_ = false;
			isL_ = true; 
		} else if (input_->PushKey(DIK_RIGHT)) {
			move.x += kCharacterSpeed;
		    isL_ = false;
		    isR_ = true;
		}

		//// 押した方向で移動ベクトルを変更(上)
		//if (input_->PushKey(DIK_SPACE)) {
		//	move.y += kJumpAcceleration;

		//} else  {
		//	// 落下速度
		//	move.y -= kGravityAcceleration;
		//}

	
	worldtransfrom_.translation_.x += move.x;
	worldtransfrom_.translation_.y += move.y;

	const float kMoveLimitX = 6;
	const float kMoveLimitY = 10;

	worldtransfrom_.translation_.x = std::clamp(worldtransfrom_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldtransfrom_.translation_.y = std::clamp(worldtransfrom_.translation_.y, -kMoveLimitY, kMoveLimitY);

	 ImGui::Begin("Setmove");
	 ImGui::SliderFloat("Move X", &worldtransfrom_.translation_.x, -1.0f, 1.0f);
	 ImGui::SliderFloat("Move Y", &worldtransfrom_.translation_.y, -1.0f, 1.0f);
	 ImGui::SliderFloat("Move Z", &worldtransfrom_.translation_.z, -1.0f, 1.0f);
	 ImGui::End();

	worldtransfrom_.updateMatrix();
}

void Player::Draw() {

	model_->Draw(worldtransfrom_, *camera_);

}

AABB Player::GetAABB() {
	KamataEngine::Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Player::OnCollision() {
	// キャラクターの移動ベクトル
	KamataEngine::Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 1.0f;
	if (isL_==true) {
		move.x -= kCharacterSpeed;
	} else if (isR_ == true) {
		move.x += kCharacterSpeed;
	} else {
		move.x -= kCharacterSpeed;
	}


	worldtransfrom_.translation_.x += move.x;
	worldtransfrom_.translation_.z += move.z;
	worldtransfrom_.updateMatrix();
}

