#pragma once
#include <list>
#include <memory>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObjectBase.h"


struct TransformData
{
	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalQuaternion;
	float4 LocalPosition;
	//float4 WorldScale;
	//float4 WorldRotation;
	//float4 WorldQuaternion;
	//float4 WorldPosition;
	float4x4 LocalScaleMatrix;
	float4x4 LocalRotationMatrix;
	float4x4 LocalPositionMatrix;
	float4x4 LocalWorldMatrix;
	float4x4 WorldMatrix;
	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;
	float4x4 WorldViewProjectionMatrix;


public:
	TransformData()
	{
		LocalScale = float4::One;
		LocalRotation = float4::Null;
		LocalQuaternion = float4::Null;
		LocalPosition = float4::Zero;
		//WorldScale = float4::One;
		//WorldRotation = float4::Null;
		//WorldQuaternion = float4::Null;
		//WorldPosition = float4::Zero;
	}
};

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
		//LocalScale = WorldScale = _Value;

		TransformUpdate();
		CalChild();
	}

	void SetWorldRotation(const float4& _Value)
	{
		AbsoluteRotation = true;
		//LocalRotation = WorldRotation = _Value;

		TransformUpdate();
		CalChild();
	}

	void SetWorldPosition(const float4& _Value)
	{
		AbsolutePosition = true;
		//LocalPosition = WorldPosition = _Value;

		TransformUpdate();
		CalChild();
	}

	void SetLocalScale(const float4& _Value)
	{

		AbsoluteScale = false;
		TransData.LocalScale = _Value;

		//if (nullptr == Parent)
		//{
		//	WorldScale = LocalScale;
		//}
		//else
		//{
		//	WorldScale = LocalScale * Parent->GetWorldMatrixRef();
		//}

		TransformUpdate();
		CalChild();
	}

	void SetLocalRotation(const float4& _Value)
	{
		AbsoluteRotation = false;
		TransData.LocalRotation = _Value;

		//if (nullptr == Parent)
		//{
		//	WorldRotation = LocalRotation;
		//}
		//else
		//{
		//	//  180         90, 0,           90, 0, 0
		//	WorldRotation = LocalRotation + Parent->GetWorldRotation();
		//}

		TransformUpdate();
		CalChild();
	}

	void SetLocalPosition(const float4& _Value)
	{
		AbsolutePosition = false;
		TransData.LocalPosition = _Value;

		//if (nullptr == Parent)
		//{
		//	WorldPosition = LocalPosition;
		//}
		//else
		//{
		//	LocalPosition = LocalPosition * Parent->GetWorldMatrixRef();
		//}

		TransformUpdate();
		CalChild();
	}

	void AddLocalScale(const float4& _Value)
	{
		SetLocalScale(TransData.LocalScale + _Value);
	}

	void AddLocalRotation(const float4& _Value)
	{
		SetLocalRotation(TransData.LocalRotation + _Value);
	}

	void AddLocalPosition(const float4& _Value)
	{
		SetLocalPosition(TransData.LocalPosition + _Value);
	}

	//void AddWorldScale(const float4& _Value)
	//{
	//	SetWorldScale(TransData.LocalScale + _Value);
	//}

	//void AddWorldRotation(const float4& _Value)
	//{
	//	SetWorldRotation(TransData.LocalRotation + _Value);
	//}

	//void AddWorldPosition(const float4& _Value)
	//{
	//	SetWorldPosition(TransData.LocalPosition + _Value);
	//}

	float4 GetWorldForwardVector()
	{
		return TransData.WorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.ArrVector[0].NormalizeReturn();
	}

	float4 GetWorldBackVector()
	{
		return -GetWorldForwardVector();
	}

	float4 GetWorldDownVector()
	{
		return -GetWorldUpVector();
	}

	float4 GetWorldLeftVector()
	{
		return -GetWorldRightVector();
	}

	float4 GetLocalPosition()
	{
		return TransData.LocalPosition;
	}

	float4 GetLocalScale()
	{
		return TransData.LocalScale;
	}

	float4 GetLocalRotation()
	{
		return TransData.LocalRotation;
	}

	float4 GetLocalForwardVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[2].NormalizeReturn();
	}

	float4 GetLocalUpVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[1].NormalizeReturn();
	}

	float4 GetLocalRightVector()
	{
		return TransData.LocalWorldMatrix.ArrVector[0].NormalizeReturn();
	}



	//float4 GetWorldPosition()
	//{
	//	return WorldPosition;
	//}

	//float4 GetWorldScale()
	//{
	//	return WorldScale;
	//}

	//float4 GetWorldRotation()
	//{
	//	return WorldRotation;
	//}


	float4x4 GetLocalWorldMatrix()
	{
		return TransData.LocalWorldMatrix;
	}

	const float4x4& GetLocalWorldMatrixRef()
	{
		return TransData.LocalWorldMatrix;
	}

	const float4x4 GetWorldMatrix()
	{
		return TransData.WorldMatrix;
	}

	const float4x4& GetWorldMatrixRef()
	{
		return TransData.WorldMatrix;
	}

	const float4x4 GetWorldViewProjectionMatrix()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	const float4x4& GetWorldViewProjectionMatrixRef()
	{
		return TransData.WorldViewProjectionMatrix;
	}

	inline const void SetCameraMatrix(const float4x4& _View, const float4x4& _Projection)
	{
		TransData.View = _View;
		TransData.Projection = _Projection;
		TransData.WorldViewProjectionMatrix = TransData.WorldMatrix * TransData.View * TransData.Projection;
	}

	inline const void SetViewPort(const float4x4& _ViewPort)
	{
		TransData.ViewPort = _ViewPort;
		TransData.WorldViewProjectionMatrix *= TransData.ViewPort;
	}

	void CalChild()
	{
		for (GameEngineTransform* ChildTrans : Child)
		{
			ChildTrans->SetLocalScale(ChildTrans->GetLocalScale());
			ChildTrans->SetLocalRotation(ChildTrans->GetLocalRotation());
			ChildTrans->SetLocalPosition(ChildTrans->GetLocalPosition());
		}
	}

	void SetParent(GameEngineTransform* _Parent);

	const TransformData& GetTransDataRef()
	{
		return TransData;
	}

	void SetTransformData(const TransformData& _Data)
	{
		TransData = _Data;
	}

protected:

private:
	void TransformUpdate();

	TransformData TransData;

	bool AbsoluteScale = false;
	bool AbsoluteRotation = false;
	bool AbsolutePosition = false;

	//float4 LocalScale = float4::One;
	//float4 LocalRotation = float4::Null;
	//Quaternion LocalQuaternion = DirectX::XMQuaternionIdentity();
	//float4 LocalPosition = float4::Zero;

	////float4 WorldScale = float4::One;
	////float4 WorldRotation = float4::Null;
	////Quaternion WorldQuaternion = DirectX::XMQuaternionIdentity();
	////float4 WorldPosition = float4::Zero;

	//float4x4 LocalScaleMatrix;
	//float4x4 LocalRotationMatrix;
	//float4x4 LocalPositionMatrix;

	//float4x4 LocalWorldMatrix;

	//float4x4 WorldMatrix;
	//float4x4 WorldViewProjectionMatrix;

	//float4x4 View;
	//float4x4 Projection;
	//float4x4 ViewPort;

	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Child;
};

