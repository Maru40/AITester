#include "NewMainStage.h"

#include "Watanabe/DebugClass/Debug.h"
#include "Patch/PlayerInputer.h"

#include "Patch/CameraHelper.h"
#include "Watanabe/Effekseer/EfkEffect.h"

#include "Maruyama/Utility/Object/GameManagerObject.h"

using namespace basecross;

void
MainStage::OnCreate()
{

}

void 
MainStage::OnUpdate()
{
	AddGameObject<EfkInterface>();
	AddGameObject<GameManagerObject>();

	AddGameObject<Debug>();
	Debug::GetInstance()->Log(L"NewMainStage");

	CreateLightView();

	auto cameraObj = Instantiate<CameraObject>();

	EventSystem::GetInstance(GetThis<Stage>())->SetBasicInputer(PlayerInputer::GetInstance());

	CreateMap(L"StageS2.csv");
}

void
MainStage::CreateLightView()
{
	//CreateStartCamera(sm_loadMapName);
	CreateMainCamera();
	//マルチライトの作成
	auto PtrMultiLight = CreateLight<MultiLight>();
	//デフォルトのライティングを指定
	PtrMultiLight->SetDefaultLighting();

	ChangeMainCamera(); //初期カメラの設定
}