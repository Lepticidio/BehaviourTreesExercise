#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>
#include "PathFollowingSteering.h"
#include "PursueSteering.h"
#include "AlignToMovement.h"
#include "ArriveSteering.h"

#include "BehaviorIdle.h"
#include "BehaviorPursue.h"
#include "Sequence.h"
#include "Selector.h"
#include "ConditionCanSee.h"
#include "BehaviorWindup.h"
#include "BehaviorAttack.h"
#include "ConditionOtherIsAlive.h"

USVec2D Character::RotateVector(USVec2D _vInitialVector, float _fAngle)
{
	float fRadians = _fAngle / 57.2958f;
	return USVec2D(cos(fRadians) * _vInitialVector.mX - sin(fRadians) * _vInitialVector.mY, sin(fRadians) * _vInitialVector.mX + cos(fRadians) * _vInitialVector.mY);
}
float Character::AngleBetweenVectors(USVec2D _v0, USVec2D _v1)
{
	float fDot = _v0.Dot(_v1);
	fDot = (fDot < -1.0 ? -1.0 : (fDot > 1.0 ? 1.0 : fDot));
	float fAngle = acos(fDot);
	float fDegrees = fAngle * 57.2958f;
	return fDegrees;
}

Character::Character() : mLinearVelocity(00.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
		RTTI_END
		m_pSeek = new SeekSteering(this);
	m_pArrive = new ArriveSteering(this);
	m_pAlign = new AlignSteering(this);
	m_pAlignToMovement = new AlignToMovement(this, m_pAlign);
	const char* sPathName = "path.xml";
	m_pPath = new Path(sPathName);
	m_pPathSteering = new PathFollowingSteering(m_pSeek, m_pPath, this);
}

Character::~Character()
{

}

void Character::OnStart()
{
	ReadParams(m_sParamsName.c_str(), mParams);
	m_pSeek->Initialize();
	m_pArrive->Initialize();
	m_pAlign->Initialize();
	m_pPathSteering->Initialize();
	m_vRandomPos = USVec2D(Rand() * 1024.0f - 512, Rand() * 768.0f - 384);
}

void Character::OnStop()
{

}


void Character::OnUpdate(float step)
{
	//USVec2D vAcceleration = m_pSeek->GetSteering(mParams.targetPosition); 
	//USVec2D vAcceleration = m_pArrive->GetSteering(mParams.targetPosition);

	m_fLastStep = step;
	USVec2D vAcceleration(0, 0);
	if (m_bIsEnemy)
	{
		m_fCurrentTime += step;
		if (m_fCurrentTime - m_fPreviousTime > m_fSecondsToChangeTarget)
		{
			m_vRandomPos = USVec2D(Rand() * 1024.0f - 512, Rand() * 768.0f - 384);
			m_fPreviousTime = m_fCurrentTime;
		}

		vAcceleration = m_pArrive->GetSteering(m_vRandomPos);
	}
	else
	{
		m_pRoot->tick();
	}
	if (m_fHealth <= 0)
	{
		m_fHealth = 0;
		SetImage(1);
		vAcceleration = USVec2D(0, 0);
		SetLinearVelocity(0, 0);
	}
	if (m_fHealth > 0)
	{
		//USVec2D vAcceleration = m_pPathSteering->GetSteering();
		//USVec2D vAcceleration (0,0);
		USVec2D vCurrentVelocity = GetLinearVelocity() + vAcceleration * step;
		SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
		SetLoc(GetLoc() + GetLinearVelocity() * step);

		//float fAngularAcceleration = m_pAlign->GetSteering(mParams.targetRotation);
		float fAngularAcceleration = m_pAlignToMovement->GetSteering();
		//float fAngularAcceleration = 0;
		float fCurrentAngularVelocity = GetAngularVelocity() + fAngularAcceleration;
		SetAngularVelocity(fCurrentAngularVelocity);
		float fAngleToSet = GetRot() + fCurrentAngularVelocity;
		while (fAngleToSet >= 360 || fAngleToSet < 0)
		{
			if (fAngleToSet >= 360)
			{
				fAngleToSet -= 360;
			}
			else if (fAngleToSet < 0)
			{
				fAngleToSet += 360;
			}

		}
		SetRot(fAngleToSet);

	}

}

void Character::DrawDebug()
{
}


// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);

	luaL_Reg regTable[] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ "checkIsEnemy",			_checkIsEnemy},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

		float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")

		float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}

int Character::_checkIsEnemy(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
		bool bIsEnemy = state.GetValue<bool>(2, 0.0f);
	self->SetIsEnemy(bIsEnemy);
	if (bIsEnemy)
	{
		self->SetParamsName("params_enemy.xml");
	}
	else
	{
		Character* pToBePursued = state.GetLuaObject<Character>(3, 0.0f);
		self->SetParamsName("params_enemy.xml");
		//self->SetPursuedCharacter(pToBePursued);

		Selector* pRoot = new Selector();
		Sequence* pAlertSequence = new Sequence();
		ConditionCanSee* pCanSee = new ConditionCanSee(self, pToBePursued);
		ConditionOtherIsAlive* pOtherIsAlive = new ConditionOtherIsAlive(pToBePursued);
		BehaviorPursue* pPursue = new BehaviorPursue(self, pToBePursued);
		BehaviorIdle* pIdle = new BehaviorIdle(self);
		BehaviorWindup* pWindup = new BehaviorWindup(self);
		BehaviorAttack* pAttack = new BehaviorAttack(self, pToBePursued);

		pRoot->AddBehavior(pAlertSequence);
		pRoot->AddBehavior(pIdle);
		pAlertSequence->AddBehavior(pOtherIsAlive);
		pAlertSequence->AddBehavior(pCanSee);
		pAlertSequence->AddBehavior(pPursue);
		pAlertSequence->AddBehavior(pWindup);
		pAlertSequence->AddBehavior(pAttack);

		self->m_pRoot = pRoot;
	}

	return 0;
}