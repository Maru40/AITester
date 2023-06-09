#include "stdafx.h"

#include "MaruTestStage_DebugLog.h"

#include "Watanabe/DebugClass/Debug.h"

#include "Maruyama/Thread/ThreadPool.h"

#include "Patch/PlayerInputer.h"

#include "Maruyama/Enemy/ImpactMap/Cell.h"
#include "Maruyama/Enemy/ImpactMap/FieldCellMap.h"

#include "Maruyama/Enemy/ImpactMap/Factory_WayPointMap_FloodFill.h"

#include "Maruyama/Patch/Graphs/SparseGraph_Ex.h"

#include "Maruyama/Enemy/Astar/AstarNode.h"
#include "Maruyama/StateMachine/NodeBase.h"
#include "Maruyama/StateMachine/EdgeBase.h"
#include "Maruyama/Enemy/Astar/AstarEdge_Ex.h"

#include "Maruyama/Utility/UtilityObstacle.h"
#include "Maruyama/Utility/Utility.h"
#include "Watanabe/StageObject/Block.h"

#include "Maruyama/Thread/ThreadPool.h"

#include "Maruyama/Enemy/AIDirector/AIDirector_Ex.h"

#include "Maruyama/New/AI/AIPlayer/AIPlayerObject_Ex.h"

#include "Maruyama/New/Camera/DebugCamera.h"

namespace basecross {

	//デバッグ変数
	std::shared_ptr<maru::SparseGraph<maru::AstarNode, maru::AstarEdge>> m_debugGraph;
	int test_debugCount = 0;
	bool mIsDebugGraph = false;
	
	void MaruTestStage_DebugLog::CreateViewLight() {
		//const Vec3 eye(0.0f, 30.0f, -0.000001f);
		const Vec3 eye(0.0f, 252.4f, -0.000001f);
		//const Vec3 eye(0.0f, 0.0f, -20.0f);
		const Vec3 at(0, 0.0f, 0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	struct Test {

	};

	int say_ok(const int number) {
		return 0;
	}

	void MaruTestStage_DebugLog::OnCreate() {
		CreateViewLight();
		auto log = AddGameObject<Debug>();
		Debug::GetInstance()->Log(L"MaruTestStage_DebugLog");

		//スレッドプールのデバッグ
		//AddGameObject<Tester::TesterThreadObject>();

		//セルデバッグ表示
		//AddGameObject<GameObject>()->AddComponent<maru::FieldCellMap>();

		//テストAIDirectorの生成
		AddGameObject<GameObject>()->AddComponent<Enemy::AIDirector_Ex>();

		//テストマップの生成
		CreateTestMap();

		auto player = AddGameObject<AI::AIPlayer::Object>();

		//デバッグカメラを生成
		auto debubCamera = AddGameObject<DebugCamera>();
	}

	void MaruTestStage_DebugLog::OnUpdate() {

		if (mIsDebugGraph && m_debugGraph) {
			//return;
			for (auto& node : m_debugGraph->GetNodes()) {
				node.second->OnDebugDraw();
			}

			for (auto& pair : m_debugGraph->GetEdgesMap()) {
				for (auto& edge : pair.second) {
					edge->OnDebugDraw();
				}
			}
		}

		if (PlayerInputer::GetInstance()->IsChangeNodeDebugDraw()) {
			mIsDebugGraph = !mIsDebugGraph;

			for (auto& node : m_debugGraph->GetNodes()) {
				node.second->SetDebugDrawActive(mIsDebugGraph);
			}

			for (auto& pair : m_debugGraph->GetEdgesMap()) {
				for (auto& edge : pair.second) {
					edge->SetDebugDrawActive(mIsDebugGraph);
				}
			}
		}
	}

	void MaruTestStage_DebugLog::CreateTestMap() {
		// Mapの読み込み
		CreateMap(L"StageS2.csv");

		//フラッドフィルアルゴリズムテスト
		auto graph = std::make_shared<maru::SparseGraph<maru::AstarNode, maru::AstarEdge>>();
		auto floodFill = std::make_shared<maru::Factory_WayPointMap_FloodFill>(GetThis<Stage>());
		auto factoryParam = maru::Factory_WayPointMap_FloodFill::Parametor();
		auto& rect = factoryParam.rect;
		factoryParam.intervalRange = 5.0f;	//インターバールレンジが1でも処理が可能。
		constexpr float Width = 100.0f;
		constexpr float Depth = 200.0f;
		rect.width = Width - factoryParam.intervalRange;
		rect.depth = Depth - factoryParam.intervalRange;
		floodFill->AddWayPointMap(graph, factoryParam);

		//デバッグ生成
		Debug::GetInstance()->Log((int)graph->GetNodes().size());
		Debug::GetInstance()->Log((int)graph->GetNumAllEdges());

		std::unordered_map<int, std::shared_ptr<maru::AstarNode>> copyNodes;
		auto nodes = graph->GetNodes();

		//auto size = (u32)nodes.size();
		//copyNodes = nodes;
		copyNodes.insert(nodes.begin(), nodes.end());
		////std::copy(copyNodes.begin(), nodes.begin(), nodes.end());
		//auto iter = copyNodes.begin();

		auto selfNode = nodes[0];
		auto p = selfNode.get();
		auto copyNode = copyNodes[0];
		auto p2 = copyNode.get();

		if (p == p2) {
			int i = true;
		}

		m_debugGraph = graph;
	}

	//デバッグ系---------------------------------------------------------------------------------------------

	void MaruTestStage_DebugLog::CreateDebugObstacle()
	{
		Vec3 positions[] = {
			Vec3(-2.5f, 0.0f, 0.0f),
		};

		for (auto& position : positions) {
			auto object = Instantiate<GameObject>(position, Quat::Identity());
			object->AddComponent<PNTStaticDraw>()->SetMeshResource(L"DEFAULT_CUBE");
			object->AddComponent<CollisionObb>();
			object->GetComponent<Transform>()->SetScale(Vec3(1.0f, 5.0f, 15.0f));
			object->AddTag(maru::UtilityObstacle::DEFAULT_OBSTACLE_TAGS[0]);
		}
	}

	void MaruTestStage_DebugLog::DebugPointer()
	{
		//ポインタのアドレス確認
		GameObject* objPtr = new GameObject(GetThis<Stage>());
		Debug::GetInstance()->Log((int)(uintptr_t)objPtr);
		delete(objPtr);
		Debug::GetInstance()->Log((int)(uintptr_t)objPtr);
	}

}