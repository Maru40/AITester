#pragma once

class Targeted;

class TargetingSystem : public basecross::Component
{
public:
	TargetingSystem(const std::shared_ptr<basecross::GameObject>& owner);

	~TargetingSystem() = default;

	void OnUpdate() override;

	Targeted* CalculateCurrentTarget();

	void AddTarget(const std::shared_ptr<Targeted>& target);

	void RemoveTarget(const std::shared_ptr<Targeted>& target);

	void SetCurrentTarget(Targeted* const target);

	Targeted* GetCurrentTarget() const;

	std::set<Targeted*> GetTargets() const;

private:

private:
	Targeted* mCurrentTarget = nullptr;

	std::set<Targeted*> mTargets;
};