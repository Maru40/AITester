#include "PlayerObjectBase.h"

#include "Maruyama/New/Component/InputerComponent.h"
#include "Maruyama/New/Component/InputMover.h"
#include "Maruyama/Utility/Component/RotationController.h"

#include "Maruyama/Utility/Component/CollisionAction.h"

using namespace basecross;

PlayerObjectBase::PlayerObjectBase(const std::shared_ptr<basecross::Stage>& stage) :
	GameObject(stage)
{

}

void
PlayerObjectBase::OnCreate()
{
	AddComponent<InputerComponent>();
	AddComponent<InputMover>();

	AddComponent<RotationController>();

	auto gravity = AddComponent<Gravity>();
	gravity->SetGravity(Vec3(0.0f, -9.8f * 3.0f, 0.0f));

	CreateModel();
	CreateCollision();
}

void 
PlayerObjectBase::CreateModel()
{
	Mat4x4 spanMat;
	const float fScale = 0.8f;
	Vec3 scale = Vec3(fScale);
	spanMat.affineTransformation(
		scale,
		Vec3(0.0f, 0.0f, 0.0f),
		Vec3(0.0f, XM_PI, 0.0f),
		Vec3(0.0f, -0.5f, 0.0f)
	);

	auto draw = AddComponent<DrawComp>();
	draw->SetMultiMeshResource(L"Player_Mesh");
	draw->SetMeshToTransformMatrix(spanMat);
	draw->SetModelTextureEnabled(false);
	draw->SetTextureResource(L"RedHeroTx");

	// アウトライン関係
	draw->SetOutlineActive(true);
	// ディゾブルアニメーションを有効
	draw->SetEnabledDissolve(true);

	SetAlphaActive(true);
}

void 
PlayerObjectBase::CreateCollision()
{
	return;
	auto collision = AddComponent<CollisionObb>();
	constexpr float CollisionSize = 1.0f;
	collision->SetMakedSize(CollisionSize);
	AddComponent<maru::CollisionAction>();
}