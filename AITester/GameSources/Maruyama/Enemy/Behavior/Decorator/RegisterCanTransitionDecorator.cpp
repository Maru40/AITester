/*!
@file OutSpecificTarget.cpp
@brief OutSpecificTargetなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "../Interface/I_Decorator.h"

#include "RegisterCanTransitionDecorator.h"

namespace basecross {
	namespace maru {

		namespace Behavior {

			namespace Decorator {

				void ResgisterCanTrasitionDecorator::OnStart() {
					for (auto& start : m_startFunctions) {
						start();
					}
				}

				void ResgisterCanTrasitionDecorator::ReserveCanTransition() {
					for (auto& reserveFunction : m_reserveCanTransitions) {
						reserveFunction();
					}
				}

				bool ResgisterCanTrasitionDecorator::CanTransition() const {
					for (auto& canTransition : m_canTransitions) {
						//一つでも遷移できない条件があったら。
						if (!canTransition()) {	
							return false;	//遷移不可
						}
					}

					return true;
				}

				bool ResgisterCanTrasitionDecorator::CanUpdate() {
					for (auto& canUpdate : m_canUpdates) {
						//一つでも遷移できない条件があったら。
						if (!canUpdate()) {
							return false;	//遷移不可
						}
					}

					return true;
				}

				void ResgisterCanTrasitionDecorator::AddStartFunction(const std::function<void()>& startFunction) {
					m_startFunctions.push_back(startFunction);
				}

				void ResgisterCanTrasitionDecorator::AddReserveCanTransitionFunction(const std::function<void()>& function) {
					m_reserveCanTransitions.push_back(function);
				}

				void ResgisterCanTrasitionDecorator::AddCanTransitionFunction(const std::function<bool()>& canTransition) {
					m_canTransitions.push_back(canTransition);
				}

				void ResgisterCanTrasitionDecorator::AddCanUpdateFunction(const std::function<bool()>& canUpdate) {
					m_canUpdates.push_back(canUpdate);
				}

				
			}
		}
	}
}