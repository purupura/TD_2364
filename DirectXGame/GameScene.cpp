#include "3d/AxisIndicator.h"
#include "GameScene.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelPlayer_;
	delete modelEnemy_;
	delete player_;
	delete debugCamera_;
	delete modelSkydome_;
	delete field_;
	delete hpBarSprite_;
	delete hpBarSprite2_;
	delete hpBarSprite3_;
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = new Player();
	skydome_ = new Skydome();
	field_ = new field();
	// 3Dモデルの生成
	modelPlayer_ = KamataEngine::Model::CreateFromOBJ("player", true);
	modelEnemy_ = KamataEngine::Model::CreateFromOBJ("cube", true);
	modelSkydome_ = KamataEngine::Model::CreateFromOBJ("skydome", true);
	modelField_ = KamataEngine::Model::CreateFromOBJ("field", true);

	// ビュープロジェクションの初期化
	camera_.Initialize();

	player_->Initialize(modelPlayer_, &camera_, playerPos);
	for (int32_t i = 0; i < 3; ++i) {
		Enemy* newEnemy = new Enemy();
		KamataEngine::Vector3 enemyPosition = {3.0f+i*-3, -10.0f, playerPos.z+500.0f+i*70};
		newEnemy->Initialize(modelEnemy_, &camera_, enemyPosition);

		enemies_.push_back(newEnemy);
	}
	
	skydome_->Initialize(modelSkydome_, &camera_);
	field_->Initialize(modelField_, &camera_,fieldPos);

	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示の表示を有効にする
	KamataEngine::AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	KamataEngine::AxisIndicator::GetInstance()->SetTargetCamera(&camera_);

	// 敵キャラに自キャラのアドレスを渡す
	//enemy_->SetPlayer(player_);
	hpBarTextureHandle_ = KamataEngine::TextureManager::Load("hpBarFront.png");
	hpBarTextureHandle2_ = KamataEngine::TextureManager::Load("hpBarBuck.png");
	hpBarTextureHandle3_ = KamataEngine::TextureManager::Load("hpBarflame.png");
	hpBarSprite_ = KamataEngine::Sprite::Create(hpBarTextureHandle_, {120, 10});
	hpBarSprite2_ = KamataEngine::Sprite::Create(hpBarTextureHandle2_, {120, 10});
	hpBarSprite3_ = KamataEngine::Sprite::Create(hpBarTextureHandle3_, {120, 10});
}

void GameScene::Update() {
	player_->Update();

	SodaGage();

		// 敵の更新
	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	//CheckAllCollisions();

	

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_V)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();

	} else {
		camera_.UpdateMatrix();
	}

	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	dxCommon_->ClearDepthBuffer();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理

	KamataEngine::Sprite::PreDraw(commandList);

	
	
	hpBarSprite2_->Draw();
	hpBarSprite_->Draw();
	hpBarSprite3_->Draw();
	KamataEngine::Sprite::PostDraw();

	
	KamataEngine::Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// 
	
	for (Enemy* enemy : enemies_) {
	enemy->Draw();
	}

	player_->Draw();
	
	skydome_->Draw();

	field_->Draw();

	/// </summary>

	KamataEngine::Model::PostDraw();
	Sprite::PreDraw(commandList);
	Sprite::PostDraw();
}

void GameScene::SodaGage() {
	KamataEngine::Vector2 size = hpBarSprite_->GetSize();

	size.x = nowSodaGage / maxSodaGage * width;
	size.y = 50.0f;

	hpBarSprite_->SetSize(size);

	if (input_->PushKey(DIK_SPACE)) {
		nowSodaGage -= 5;
	}

	nowSodaGage -= 1;

	if (nowSodaGage <= 0) {
		nowSodaGage = 0;
	}
}

//void GameScene::CheckAllCollisions() {
//
//	KamataEngine::Vector3 posA[4], posB[4];
//	float radiusA[3] = {0.8f, 2.0f, 0.8f}; // プレイヤーの半径（固定値）
//	float radiusB[3] = {0.8f, 2.0f, 0.8f}; // 敵弾の半径（固定値）
//
//	// 敵弾リストの取得
//	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullet();
//	// 自弾
//	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
//
//#pragma region 自キャラと敵弾の当たり判定
//
//	// 自キャラの座標
//	posA[0] = player_->GetWorldPosition();
//
//	// 自キャラと敵弾全ての当たり判定
//	for (EnemyBullet* bullet : enemyBullets) {
//		// 敵弾の座標
//		posB[0] = bullet->GetWorldPosition();
//
//		// 2つの球の中心間の距離の二乗を計算
//		float distanceSquared = (posA[0].x - posB[0].x) * (posA[0].x - posB[0].x) + (posA[0].y - posB[0].y) * (posA[0].y - posB[0].y) + (posA[0].z - posB[0].z) * (posA[0].z - posB[0].z);
//
//		// 半径の合計の二乗
//		float combinedRadiusSquared = (radiusA[0] + radiusB[0]) * (radiusA[0] + radiusB[0]);
//
//		// 衝突判定 (距離の二乗が半径の合計の二乗以下なら衝突)
//		if (distanceSquared <= combinedRadiusSquared) {
//			// 自キャラの衝突時コールバックを呼び出す
//			player_->OnCollision();
//			// 敵弾の衝突時コールバックを呼び出す
//			bullet->OnCollision();
//		}
//	}
//
//#pragma endregion
//
//#pragma region 自弾と敵キャラの当たり判定
//
//	// 敵
//	posA[1] = enemy_->GetWorldPosition();
//
//	for (PlayerBullet* bullet : playerBullets) {
//
//		posB[1] = bullet->GetWorldPosition();
//		float distanceSquared = (posA[1].x - posB[1].x) * (posA[1].x - posB[1].x) + (posA[1].y - posB[1].y) * (posA[1].y - posB[1].y) + (posA[1].z - posB[1].z) * (posA[1].z - posB[1].z);
//		float combinedRadiusSquared = (radiusA[2] + radiusB[2]) * (radiusA[2] + radiusB[2]);
//
//		if (distanceSquared <= combinedRadiusSquared) {
//			enemy_->OnCollision();
//			bullet->OnCollision();
//		}
//	}
//
//#pragma endregion
//
//#pragma region 自弾と敵弾の当たり判定
//
//	for (PlayerBullet* bullet : playerBullets) {
//		for (EnemyBullet* bullet2 : enemyBullets) {
//
//			posA[2] = bullet->GetWorldPosition();
//			posB[2] = bullet2->GetWorldPosition();
//
//			float distanceSquared = (posA[2].x - posB[2].x) * (posA[2].x - posB[2].x) + (posA[2].y - posB[2].y) * (posA[2].y - posB[2].y) + (posA[2].z - posB[2].z) * (posA[2].z - posB[2].z);
//			float combinedRadiusSquared = (radiusA[1] + radiusB[1]) * (radiusA[1] + radiusB[1]);
//
//			if (distanceSquared <= combinedRadiusSquared) {
//				bullet->OnCollision();
//				bullet2->OnCollision();
//			}
//		}
//	}
//
//#pragma endregion
//}
