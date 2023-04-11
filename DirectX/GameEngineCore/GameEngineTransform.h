#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"

// 설명 : 특정한 문체의 크기 회전 이동에 관련된 기하속성을 관리해준다.
class GameEngineTransform : public GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineTransform();
	~GameEngineTransform();

	// delete Function
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;

	void SetWorldScale(const float4& _Value)
	{
		AbsoluteScale = true;
		LocalScale = WorldScale = _Value;

		TransformUpdate();
		CalChild();
	}

	void SetWorldRotation(const float4& _Value)
	{
		AbsoluteRotation = true;
		LocalRotation = WorldRotation = _Value;

		TransformUpdate();
		CalChild();
	}

	void SetWorldPosition(const float4& _Value)
	{
		AbsolutePosition = true;
		LocalPosition = WorldPosition = _Value;

		TransformUpdate();
		CalChild();
	}

	void SetLocalScale(const float4& _Value, bool isChildCul = false)
	{

		AbsoluteScale = false;/*(true == isChildCul ? AbsoluteScale : false);*/
		LocalScale = _Value;

		if (nullptr == Parent)
		{
			WorldScale = LocalScale;
		}
		else
		{
			WorldScale = LocalScale * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalRotation(const float4& _Value, bool isChildCul = false)
	{
		AbsoluteRotation = false;/*(true == isChildCul ? AbsoluteRotation : false);*/
		LocalRotation = _Value;

		if (nullptr == Parent)
		{
			WorldRotation = LocalRotation;
		}
		else
		{
			//  180         90, 0,           90, 0, 0
			WorldRotation = LocalRotation + Parent->GetWorldRotation();
		}

		TransformUpdate();
		CalChild();
	}

	void SetLocalPosition(const float4& _Value, bool isChildCul = false)
	{
		AbsolutePosition = false;/*(true == isChildCul ? AbsolutePosition : false);*/
		LocalPosition = _Value;

		if (nullptr == Parent)
		{
			WorldPosition = LocalPosition;
		}
		else
		{
			WorldPosition = LocalPosition * Parent->GetWorldMatrixRef();
		}

		TransformUpdate();
		CalChild();
	}

	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(LocalScale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(LocalRotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(LocalPosition + _Value);
	}

	float4 GetWorldForwardVector()
	{
		return WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetWorldUpVector()
	{
		return WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetWorldRightVector()
	{
		return WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetLocalForwardVector()
	{
		return LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		return LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetLocalRightVector()
	{
		return LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetLocalPosition()
	{
		return LocalPosition;
	}

	float4 GetLocalScale()
	{
		return LocalScale;
	}

	float4 GetLocalRotation()
	{
		return LocalRotation;
	}


	float4 GetWorldPosition()
	{
		return WorldPosition;
	}

	float4 GetWorldScale()
	{
		return WorldScale;
	}

	float4 GetWorldRotation()
	{
		return WorldRotation;
	}


	float4x4 GetLocalWorldMatrix()
	{
		return LocalWorldMatrix;
	}

	const float4x4& GetLocalWorldMatrixRef()
	{
		return LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return WorldMatrix;
	}

	const float4x4 GetWorldViewProjectionMatrix()
	{
		return WorldViewProjectionMatrix;
	}

	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return WorldViewProjectionMatrix;
	}

	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		View = _View;
		Projection = _Projection;
		WorldViewProjectionMatrix = WorldMatrix * View * Projection;
	}

	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		ViewPort = _ViewPort;
		WorldViewProjectionMatrix *= ViewPort;
	}

	void CalChild()
	{
		for (GameEngineTransform* ChildTrans : Child)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale(), true);
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation(), true);
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition(), true);
		}
	}

	void SetParent(GameEngineTransform* _Parent);

protected:

private:
	void TransformUpdate();
	bool AbsoluteScale = false;
	bool AbsoluteRotation = false;
	bool AbsolutePosition = false;

	float4 LocalScale = float4::One;
	float4 LocalRotation = float4::Null;
	Quaternion LocalQuaternion = DirectX::XMQuaternionIdentity();
	float4 LocalPosition = float4::Zero;

	float4 WorldScale = float4::One;
	float4 WorldRotation = float4::Null;
	Quaternion WorldQuaternion = DirectX::XMQuaternionIdentity();
	float4 WorldPosition = float4::Zero;

	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;

	float4x4 LocalWorldMatrix;

	float4x4 WorldMatrix;
	float4x4 WorldViewProjectionMatrix;

	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

