/*
Physics Effects Copyright(C) 2012 Sony Computer Entertainment Inc.
All rights reserved.

Physics Effects is open software; you can redistribute it and/or
modify it under the terms of the BSD License.

Physics Effects is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the BSD License for more details.

A copy of the BSD License is distributed with
Physics Effects under the filename: physics_effects_license.txt
*/

#pragma once
#include "stdafx.h"

#include "../../base_level/rigidbody/pfx_rigid_body.h"
#include "../../base_level/rigidbody/pfx_rigid_state.h"
#include "../../base_level/solver/pfx_solver_body.h"
#include "../../base_level/solver/pfx_constraint_pair.h"
#include "../../base_level/solver/pfx_joint.h"
#include "../../base_level/collision/pfx_contact_manifold.h"

#include "../task/pfx_task_manager.h"

namespace sce {
namespace PhysicsEffects {

///////////////////////////////////////////////////////////////////////////////
// Setup Solver Bodies

struct PfxSetupSolverBodiesParam {
	PfxRigidState *states;
	PfxRigidBody *bodies;
	PfxSolverBody *solverBodies;
	PfxUInt32 numRigidBodies;
};

PfxInt32 pfxSetupSolverBodies(PfxSetupSolverBodiesParam &param);

PfxInt32 pfxSetupSolverBodies(PfxSetupSolverBodiesParam &param,PfxTaskManager *taskManager);

///////////////////////////////////////////////////////////////////////////////
// Setup Constraints

struct PfxSetupContactConstraintsParam {
	PfxConstraintPair *contactPairs;
	PfxUInt32 numContactPairs;
	PfxContactManifold *offsetContactManifolds;
	PfxRigidState *offsetRigidStates;
	PfxRigidBody *offsetRigidBodies;
	PfxSolverBody *offsetSolverBodies;
	PfxUInt32 numRigidBodies;
	PfxFloat timeStep;
	PfxFloat separateBias;
	
	PfxSetupContactConstraintsParam():
		contactPairs(nullptr),
		numContactPairs(0),
		offsetContactManifolds(nullptr),
		offsetRigidStates(nullptr),
		offsetRigidBodies(nullptr),
		offsetSolverBodies(nullptr),
		numRigidBodies(0),
		timeStep(0),
		separateBias(0)
	{
		timeStep = 0.016f;
		separateBias = 0.2f;
	}
};

PfxInt32 pfxSetupContactConstraints(PfxSetupContactConstraintsParam &param);

PfxInt32 pfxSetupContactConstraints(PfxSetupContactConstraintsParam &param,PfxTaskManager *taskManager);

struct PfxSetupJointConstraintsParam {
	PfxConstraintPair *jointPairs;
	PfxUInt32 numJointPairs;
	PfxJoint *offsetJoints;
	PfxRigidState *offsetRigidStates;
	PfxRigidBody *offsetRigidBodies;
	PfxSolverBody *offsetSolverBodies;
	PfxUInt32 numRigidBodies;
	PfxFloat timeStep;

	PfxSetupJointConstraintsParam():
		jointPairs(nullptr),
		numJointPairs(0),
		offsetJoints(nullptr),
		offsetRigidStates(nullptr),
		offsetRigidBodies(nullptr),
		offsetSolverBodies(nullptr),
		numRigidBodies(0),
		timeStep(0.0f)
	{
		timeStep = 0.016f;
	}
};

PfxInt32 pfxSetupJointConstraints(PfxSetupJointConstraintsParam &param);

PfxInt32 pfxSetupJointConstraints(PfxSetupJointConstraintsParam &param,PfxTaskManager *taskManager);

///////////////////////////////////////////////////////////////////////////////
// Solve Constraints

struct PfxSolveConstraintsParam {
	void *workBuff;
	PfxUInt32 workBytes;
	PfxConstraintPair *contactPairs;
	PfxUInt32 numContactPairs;
	PfxContactManifold *offsetContactManifolds;
	PfxConstraintPair *jointPairs;
	PfxUInt32 numJointPairs;
	PfxJoint *offsetJoints;
	PfxRigidState *offsetRigidStates;
	PfxSolverBody *offsetSolverBodies;
	PfxUInt32 numRigidBodies;
	PfxUInt32 iteration;
	PfxBool skipPostProcess;
	SCE_PFX_PADDING(1,3)

	PfxSolveConstraintsParam():
		workBuff(nullptr),
		workBytes(0),
		contactPairs(nullptr),
		numContactPairs(0),
		offsetContactManifolds(nullptr),
		jointPairs(0),
		numJointPairs(0),
		offsetJoints(nullptr),
		offsetRigidStates(nullptr),
		offsetSolverBodies(nullptr),
		numRigidBodies(0),
		iteration(0),
		skipPostProcess(false)
	{
		iteration = 5;
		skipPostProcess = false;
	}
};

PfxUInt32 pfxGetWorkBytesOfSolveConstraints(PfxUInt32 numRigidBodies,PfxUInt32 numContactPairs,PfxUInt32 numJointPairs,PfxUInt32 maxTasks=1);

PfxInt32 pfxSolveConstraints(PfxSolveConstraintsParam &param);

PfxInt32 pfxSolveConstraints(PfxSolveConstraintsParam &param,PfxTaskManager *taskManager);

///////////////////////////////////////////////////////////////////////////////
// Apply Delta Velocity

struct PfxApplyDeltaVelocityParam {
	PfxRigidState *states;
	PfxSolverBody *solverBodies;
	PfxUInt32 numRigidBodies;
};

PfxInt32 pfxApplyDeltaVelocity(PfxApplyDeltaVelocityParam &param);

PfxInt32 pfxApplyDeltaVelocity(PfxApplyDeltaVelocityParam &param,PfxTaskManager *taskManager);

} //namespace PhysicsEffects
} //namespace sce


