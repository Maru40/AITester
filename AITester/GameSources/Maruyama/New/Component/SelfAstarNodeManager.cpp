#include "SelfAstarNodeManager.h"

SelfAstarNodeManager::SelfAstarNodeManager(const std::shared_ptr<basecross::GameObject>& owner):
	Component(owner)
{}

void SelfAstarNodeManager::OnCreate()
{

}

void SelfAstarNodeManager::OnUpdate()
{

}

void SelfAstarNodeManager::SetCurrentNode(AstarNode* const node) { mCurrentNode = node; }

SelfAstarNodeManager::AstarNode* SelfAstarNodeManager::GetCurrentNode() const { return mCurrentNode; }