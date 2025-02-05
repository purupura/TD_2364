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
	delete hpBarSprite_;
	delete hpBarSprite2_;
	delete hpBarSprite3_;
	delete soda_;
	delete modelSoda_;
	delete goalLineSprite_;
	delete goalLineSprite2_;
	delete rocket_;
	delete modelRocket;
	delete shakeSoda_;
	delete modelShake;
	for (Enemy* enemy : enemies_) {
		delete enemy;
	}
	for (field* field : fields_) {
		delete field;
	}
	for (bill* bill : bills_) {
		delete bill;
	}
}

void GameScene::Initialize() {
	std::random_device seed;
	std::mt19937 random(seed());
	std::uniform_int_distribution<> number(iMin, iMax);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	player_ = new Player();
	skydome_ = new Skydome();
	soda_ = new Soda();
	rocket_ = new Rocket();
	shakeSoda_ = new ShakeSoda();

	// 3Dモデルの生成
	modelPlayer_ = KamataEngine::Model::CreateFromOBJ("player", true);
	modelEnemy_ = KamataEngine::Model::CreateFromOBJ("corn", true);
	modelSkydome_ = KamataEngine::Model::CreateFromOBJ("skydome", true);
	modelField_ = KamataEngine::Model::CreateFromOBJ("field", true);
	modelSoda_ = KamataEngine::Model::CreateFromOBJ("soda", true);
	modelBill_ = KamataEngine::Model::CreateFromOBJ("bill", true);
	modelRocket = KamataEngine::Model::CreateFromOBJ("rocket", true);
	modelShake = KamataEngine::Model::CreateFromOBJ("can", true);
	// ビュープロジェクションの初期化
	camera_.Initialize();

	player_->Initialize(modelPlayer_, &camera_, playerPos);

	soda_->Initialize(modelSoda_, &camera_, playerPos);
	shakeSoda_->Initialize(modelShake, &camera_, shakePos);
	for (int32_t i = 0; i < 6; ++i) {
		Enemy* newEnemy = new Enemy();
		KamataEngine::Vector3 enemyPosition = {-6.0f+i*2, -10.0f, playerPos.z+500.0f+i*70};
		newEnemy->Initialize(modelEnemy_, &camera_, enemyPosition);

		enemies_.push_back(newEnemy);
	}
	for (int32_t i = 0; i < 2; ++i) {
		field* newField = new field();
		KamataEngine::Vector3 fieldPosition = {0.0f, 0.0f, i*4927.0f};
		newField->Initialize(modelField_, &camera_, fieldPosition);

		fields_.push_back(newField);
	}
	for (int32_t i = 0; i < 6; ++i) {
		bill* newBill = new bill();
		KamataEngine::Vector3 billPosition = {0.0f, 0.0f, i * 132.5f};
		newBill->Initialize(modelBill_, &camera_, billPosition);

		bills_.push_back(newBill);
	}
	
	skydome_->Initialize(modelSkydome_, &camera_);

	rocket_->Initialize(modelRocket, &camera_, rocketPos);

	debugCamera_ = new DebugCamera(1280, 720);


	
	//スプライト系統
	hpBarTextureHandle_ = KamataEngine::TextureManager::Load("hpBarFront.png");
	hpBarTextureHandle2_ = KamataEngine::TextureManager::Load("hpBarBuck.png");
	hpBarTextureHandle3_ = KamataEngine::TextureManager::Load("hpBarflame.png");
	hpBarSprite_ = KamataEngine::Sprite::Create(hpBarTextureHandle_, {120, 10});
	hpBarSprite2_ = KamataEngine::Sprite::Create(hpBarTextureHandle2_, {120, 10});
	hpBarSprite3_ = KamataEngine::Sprite::Create(hpBarTextureHandle3_, {120, 10});

	goalLineTextureHandle_ = KamataEngine::TextureManager::Load("goalLine.png");
	goalLineTextureHandle2_ = KamataEngine::TextureManager::Load("bike.png");

	goalLineSprite_ = KamataEngine::Sprite::Create(goalLineTextureHandle_, {0, 0});
	goalLineSprite2_ = KamataEngine::Sprite::Create(goalLineTextureHandle2_, {0, 0});

	skyTextureHandle_ = KamataEngine::TextureManager::Load("sky.png");
	skySprite_ = KamataEngine::Sprite::Create(skyTextureHandle_, {0, -720*4});

	//音楽
	audio_ = KamataEngine::Audio::GetInstance();
	soundDataHandle_ = audio_->LoadWave("Audio/gan.wav");
	soundDataHandle2_ = audio_->LoadWave("Audio/Search_and_Chase_2.wav");
	soundDataHandle3_ = audio_->LoadWave("Audio/Engine.wav");
	soundDataHandle4_ = audio_->LoadWave("Audio/Rocket.wav");
	soundDataHandle5_ = audio_->LoadWave("Audio/potya.wav");
	soundDataHandle6_ = audio_->LoadWave("Audio/BGM2.wav");
	soundDataHandle7_ = audio_->LoadWave("Audio/good.wav");
	soundDataHandle8_ = audio_->LoadWave("Audio/bad.wav");
	switch (sceneState) {
	case GameScene::SceneState::Game1:
		voiceHandle5_ = audio_->PlayWave(soundDataHandle5_, true);
		case GameScene::SceneState::Game2:
		voiceHandle2_ = audio_->PlayWave(soundDataHandle2_, true);
		voiceHandle3_ = audio_->PlayWave(soundDataHandle3_, true);
		    break;
	    case GameScene::SceneState::Game3:
		    voiceHandle4_ = audio_->PlayWave(soundDataHandle4_, true);
		    break;
	}
	
	
	// タイトルスプライトの初期化
	texturtitle_ = TextureManager::Load("title.png");
	title1_ = Sprite::Create(texturtitle_, {0, 0});

	texturtitle2_ = TextureManager::Load("clear.png");
	title2_ = Sprite::Create(texturtitle2_, {0, 0});

	texturtitle3_ = TextureManager::Load("over.png");
	title3_ = Sprite::Create(texturtitle3_, {0, 0});

	// 結果のスプライト

	resultTextureHandle_ = TextureManager::Load("Result1.png");
	resultSprite_ = Sprite::Create(resultTextureHandle_, {0, 0});

	resultTextureHandle2_ = TextureManager::Load("Result2.png");
	resultSprite2_ = Sprite::Create(resultTextureHandle2_, {0, 0});

	resultTextureHandle3_ = TextureManager::Load("Result3.png");
	resultSprite3_ = Sprite::Create(resultTextureHandle3_, {0, 0});

	resultTextureHandle4_ = TextureManager::Load("Result4.png");
	resultSprite4_ = Sprite::Create(resultTextureHandle4_, {0, 0});

	guidTextureHandle_ = TextureManager::Load("Guid1.png");
	guidSprite_ = Sprite::Create(guidTextureHandle_, {0, 0});

	guidTextureHandle2_ = TextureManager::Load("Guid2.png");
	guidSprite2_ = Sprite::Create(guidTextureHandle2_, {0, 0});

	guidTextureHandle3_ = TextureManager::Load("Guid3.png");
	guidSprite3_ = Sprite::Create(guidTextureHandle3_, {0, 0});

	guidTextureHandle4_ = TextureManager::Load("Guid4.png");
	guidSprite4_ = Sprite::Create(guidTextureHandle4_, {0, 0});
}

void GameScene::Update() {
	switch (sceneState)
	{
	case GameScene::SceneState::Start:
		// スタートシーンの更新処理
		KamataEngine::Vector2 pos = goalLineSprite2_->GetPosition();
		nowSodaGage = 0;
		enemies_.remove_if([](Enemy* enemy) {
			delete enemy;
			return true;
		});

		for (int32_t i = 0; i < 6; ++i) {
			Enemy* newEnemy = new Enemy();
			Vector3 enemyPosition = {-6.0f + i * 2, -10.0f, playerPos.z + 500.0f + i * 70};
			newEnemy->Initialize(modelEnemy_, &camera_, enemyPosition);

			enemies_.push_back(newEnemy);
		}

		pos.x = 0;
		pos.y =0;

		goalLineSprite2_->SetPosition(pos);

		KamataEngine::Vector2 pos2 = skySprite_->GetPosition();

		
		pos2.x = 0;
		pos2.y = -720*4;

		skySprite_->SetPosition(pos2);

		if (input_->TriggerKey(DIK_SPACE)) {
			sceneState = SceneState::Guid1;
		}
		break;
	case GameScene::SceneState::Guid1:
		if (input_->TriggerKey(DIK_RETURN)) {
			sceneState = SceneState::Guid2;
		}
		break;
	case GameScene::SceneState::Guid2:
		if (input_->TriggerKey(DIK_RETURN)) {
			sceneState = SceneState::Game1;
		}
		break;
	case GameScene::SceneState::Game1:
		if (!isBGMPlaying4_) {
			// BGMを再生し、再生中フラグをtrueに設定
			voiceHandle5_ = audio_->PlayWave(soundDataHandle6_, false, 0.3f);
			isBGMPlaying4_ = true;
		} else if (!audio_->IsPlaying(voiceHandle5_)) {
			// BGMが止まったらフラグをリセット
			isBGMPlaying4_ = false;
		}
		Shake();
		shakeSoda_->Update();
		break;
	case GameScene::SceneState::Guid3:
		if (input_->TriggerKey(DIK_RETURN)) {
			sceneState = SceneState::Guid4;
		}
		break;
	case GameScene::SceneState::Guid4:
		if (input_->TriggerKey(DIK_RETURN)) {
			sceneState = SceneState::Game2;
		}
		break;
	case GameScene::SceneState::Game2:

			if (!isBGMPlaying_) {
			// BGMを再生し、再生中フラグをtrueに設定
			voiceHandle2_ = audio_->PlayWave(soundDataHandle2_, false, 0.3f);
			isBGMPlaying_ = true;
		    } else if (!audio_->IsPlaying(voiceHandle2_)) {
			// BGMが止まったらフラグをリセット
			isBGMPlaying_ = false;
		}
		    if (!isBGMPlaying2_) {
			    // BGMを再生し、再生中フラグをtrueに設定
			    voiceHandle3_ = audio_->PlayWave(soundDataHandle3_, false, 1.0f);
			    isBGMPlaying2_ = true;
		    } else if (!audio_->IsPlaying(voiceHandle3_)) {
			    // BGMが止まったらフラグをリセット
			    isBGMPlaying2_ = false;
		    }

		goalTimer--;


		player_->Update();
		soda_->Update();

		

		if (goalTimer >= 60 * 2) {
			// 敵の更新
			for (Enemy* enemy : enemies_) {
				enemy->Update();
			}
		
		}
		for (bill* bill : bills_) {
			bill->Update();
		}
		for (field* field : fields_) {
			field->Update();
		}
		BikeMove();
		SodaGage();

		if (goalTimer <= 60 * 2) {
			rocket_->Update();
		}

		CheckAllCollisions();

	debugCamera_->Update();

	if (goalTimer <= 0) {
		audio_->StopWave(voiceHandle2_);
		audio_->StopWave(voiceHandle3_);
		goalTimer = 60 * limitTimer;
		indexSoda =nowSodaGage;
		if (nowSodaGage>=2880) {
			indexSoda = 2880;
		}
		sceneState = SceneState::Game3;
	
		}

		break;
	case GameScene::SceneState::Game3:

		SkyFry();

		break;

	case GameScene::SceneState::End1:
		// クリアシーンの更新処理
		if (input_->TriggerKey(DIK_SPACE)) {
			sceneState = SceneState::Start;
			player_->Initialize(modelPlayer_, &camera_, playerPos);
			rocket_->Initialize(modelRocket, &camera_, rocketPos);
			soda_->Initialize(modelSoda_, &camera_, playerPos);
		}
		break;
	case GameScene::SceneState::End2:
		// クリアシーンの更新処理
		if (input_->TriggerKey(DIK_SPACE)) {
			sceneState = SceneState::Start;
			player_->Initialize(modelPlayer_, &camera_, playerPos);
			rocket_->Initialize(modelRocket, &camera_, rocketPos);
			soda_->Initialize(modelSoda_, &camera_, playerPos);
		}
		break;
	case GameScene::SceneState::End3:
		// クリアシーンの更新処理
		if (input_->TriggerKey(DIK_SPACE)) {
			sceneState = SceneState::Start;
			player_->Initialize(modelPlayer_, &camera_, playerPos);
			rocket_->Initialize(modelRocket, &camera_, rocketPos);
			soda_->Initialize(modelSoda_, &camera_, playerPos);
		}
		break;

	case GameScene::SceneState::End4:
		// クリアシーンの更新処理
		if (input_->TriggerKey(DIK_SPACE)) {
			sceneState = SceneState::Start;
			player_->Initialize(modelPlayer_, &camera_, playerPos);
			rocket_->Initialize(modelRocket, &camera_, rocketPos);
			soda_->Initialize(modelSoda_, &camera_, playerPos);
		}
		break;
	case GameScene::SceneState::Over:
		if (input_->TriggerKey(DIK_SPACE)) {
			sceneState = SceneState::Start;
		}

	}

	
}

void GameScene::Draw() {



	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	switch (sceneState) {
	case SceneState::Game3:
		Sprite::PreDraw(commandList);
		skySprite_->Draw();
		Sprite::PostDraw();

		break;
	}
	dxCommon_->ClearDepthBuffer();

	KamataEngine::Model::PreDraw(commandList);
	switch (sceneState) {
	case SceneState::Start:
		// スタートシーンの描画処理
		break;
	case SceneState::Game1:
		// スタートシーンの描画処理
		skydome_->Draw();
		shakeSoda_->Draw();
		break;
	case SceneState::Game2:
		// ゲームシーンの描画処理
		
		if (goalTimer >= 60 *2) {
		for (Enemy* enemy : enemies_) {
			enemy->Draw();
		}
	}


	player_->Draw();
	soda_->Draw();
	skydome_->Draw();
	if (goalTimer <= 60 * 2) {
		rocket_->Draw();
	}
	

	for (field* field : fields_) {
		field->Draw();
	}

	for (bill* bill : bills_) {
		bill->Draw();
	}

		
		break;
	case SceneState::Game3:
		rocket_->Draw();

		break;
	case SceneState::End1:
		// クリアシーンの描画処理
		break;
	case SceneState::Over:
		// クリアシーンの描画処理
		break;
	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// 
	
		
	/// </summary>

	KamataEngine::Model::PostDraw();
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理

	KamataEngine::Sprite::PreDraw(commandList);
	switch (sceneState) {
	case SceneState::Start:
		// スタートシーンの描画処理
		title1_->Draw();
		break;
	case SceneState::Guid1:
		guidSprite_->Draw();
		break;
	case SceneState::Guid2:
		guidSprite2_->Draw();
		break;
	case SceneState::Game1:
		hpBarSprite2_->Draw();
		hpBarSprite_->Draw();
		hpBarSprite3_->Draw();
		break;
	case SceneState::Guid3:
		guidSprite3_->Draw();
		break;
	case SceneState::Guid4:
		guidSprite4_->Draw();
		break;
	case SceneState::Game2:
		hpBarSprite2_->Draw();
	    hpBarSprite_->Draw();
	    hpBarSprite3_->Draw();
		goalLineSprite_->Draw();
	    goalLineSprite2_->Draw();
		break;

	case GameScene::SceneState::Game3:
		

		break;
	case SceneState::End1:
		// クリアシーンの描画処理
		resultSprite_->Draw();
		break;
	case SceneState::End2:
		// クリアシーンの描画処理
		resultSprite2_->Draw();
		break;
	case SceneState::End3:
		// クリアシーンの描画処理
		resultSprite3_->Draw();
		break;
	case SceneState::End4:
		// クリアシーンの描画処理
		resultSprite4_->Draw();
		break;

	case SceneState::Over:
		// クリアシーンの描画処理
		title3_->Draw();
		break;
	}
	
	

	KamataEngine::Sprite::PostDraw();

	
	

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


void GameScene::BikeMove() {
	KamataEngine::Vector2 pos = goalLineSprite2_->GetPosition();

	pos.x = 0;
	pos.y -= (goalTimer/goalTimer/limitTimer)*7;

	goalLineSprite2_->SetPosition(pos);
	debugCamera_->Update();

}

void GameScene::CheckAllCollisions() {

	KamataEngine::Vector3 posA[4], posB[4];
	float radiusA[3] = {0.8f, 2.0f, 0.8f}; // プレイヤーの半径（固定値）
	float radiusB[3] = {0.8f, 2.0f, 0.8f}; // 敵の半径（固定値）
#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA[0] = player_->GetWorldPosition();

	// 自キャラと敵全ての当たり判定
	for (Enemy* enemy : enemies_) {
		// 敵弾の座標
		posB[0] = enemy->GetWorldPosition();

		// 2つの球の中心間の距離の二乗を計算
		//float distanceSquared = (posA[0].x - posB[0].x) * (posA[0].x - posB[0].x) + (posA[0].y - posB[0].y) * (posA[0].y - posB[0].y) + (posA[0].z - posB[0].z) * (posA[0].z - posB[0].z);
		// 半径の合計の二乗
		//float combinedRadiusSquared = (radiusA[0] + radiusB[0]) * (radiusA[0] + radiusB[0]);

		// 衝突判定 (距離の二乗が半径の合計の二乗以下なら衝突)
		if (abs(posA[0].z - posB[0].z) <= 1 && abs(posA[0].x - posB[0].x) <= 1 && abs(posA[0].y - posB[0].y) <= 1) {
			nowSodaGage -= 50;
			player_->OnCollision();
			soda_->OnCollision();
			voiceHandle_ = audio_->PlayWave(soundDataHandle_, false);
		}

	}

}

void GameScene::SkyFry() {
	indexSoda-=5;
	KamataEngine::Vector2 pos2 = skySprite_->GetPosition();

	if (pos2.y < 0 && indexSoda > 0) {
		pos2.y += 5;
		if (!isBGMPlaying3_) {
			// BGMを再生し、再生中フラグをtrueに設定
			voiceHandle4_ = audio_->PlayWave(soundDataHandle4_, false, 0.3f);
			isBGMPlaying3_ = true;
		} else if (!audio_->IsPlaying(voiceHandle4_)) {
			// BGMが止まったらフラグをリセット
			isBGMPlaying3_ = false;
		}
	}

	if (indexSoda <= 0) {
		audio_->StopWave(voiceHandle4_);
	}


	skySprite_->SetPosition(pos2);
	// クリアシーンの更新処理
	if (indexSoda <= -600&&pos2.y==-2880) {

		sceneState = SceneState::End1;
	}
	if (indexSoda <= -600&&pos2.y<=-700) {//-1960

		sceneState = SceneState::End2;
	}
	if (indexSoda <= -600 && pos2.y > -700) {

		sceneState = SceneState::End3;
	}
	if (indexSoda <= -600 && pos2.y == -5) {

		sceneState = SceneState::End4;
	}

}

void GameScene::Shake() {
	KamataEngine::Vector2 size = hpBarSprite_->GetSize();

	size.x = nowSodaGage / maxSodaGage * width;
	size.y = 50.0f;

	hpBarSprite_->SetSize(size);

	if(nowSodaGage >= maxSodaGage) {
		nowSodaGage = maxSodaGage;
	}

	// タイマーが0になるまでSPACEで振れる
	if (shakeTimer > 0) {
		shakeTimer -= 1;
		if (input_->TriggerKey(DIK_SPACE) && nowSodaGage < maxSodaGage) {
			nowSodaGage += 50;
			voiceHandle6_ = audio_->PlayWave(soundDataHandle5_, false,0.3f);
		}
	
	}
	// タイマーが0になると連打した分稼いだカウントが減っていく
	if (shakeTimer <= 0) {
		shakeTimer = 60*15;
		audio_->StopWave(voiceHandle5_);
		sceneState = SceneState::Guid3;

	}

}

