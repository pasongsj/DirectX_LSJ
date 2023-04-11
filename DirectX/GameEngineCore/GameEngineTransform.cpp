#include "PrecompileHeader.h"
#include "GameEngineTransform.h"
#include "GameEngineObject.h"

GameEngineTransform::GameEngineTransform()
{
}

GameEngineTransform::~GameEngineTransform()
{
}


void GameEngineTransform::TransformUpdate()
{
	LocalScaleMatrix.Scale(LocalScale);

	LocalRotation.w = 0.0f;
	LocalQuaternion = LocalRotation.EulerDegToQuaternion();
	LocalRotationMatrix = LocalQuaternion.QuaternionToRotationMatrix();
	LocalPositionMatrix.Pos(LocalPosition);

	LocalWorldMatrix = LocalScaleMatrix * LocalRotationMatrix * LocalPositionMatrix;
	

	if (nullptr == Parent)
	{
		WorldMatrix = LocalWorldMatrix;
	}
	else // 차이
	{
		float4x4 ParentWorldMatrix = Parent->GetWorldMatrixRef();		
		float4 PScale, PRoatation, PPosition;							
		ParentWorldMatrix.Decompose(PScale, PRoatation, PPosition);									 	


		if (true == AbsoluteScale)																	 	
		{																							 	
			PScale = float4::One;
		}
		if (true == AbsoluteRotation)
		{
			PRoatation = float4::Null;
			PRoatation.EulerDegToQuaternion();
		}
		if (true == AbsolutePosition)
		{
			PPosition = float4::Zero;
		}

		float4x4 MatScale, MatRot, MatPos;

		//scale
		MatScale.Scale(PScale);

		//rot
		MatRot = PRoatation.QuaternionToRotationMatrix();

		//pos
		MatPos.Pos(PPosition);

		WorldMatrix = LocalWorldMatrix * (MatScale * MatRot * MatPos);
	}
	
}

void GameEngineTransform::SetParent(GameEngineTransform* _Parent)
{
	Parent = _Parent;

	// 내가 이미 다른 부모가 있다면

	Parent->Child.push_back(this);
}


