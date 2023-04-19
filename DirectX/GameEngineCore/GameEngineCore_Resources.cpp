#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"

#include "GameEngineVertex.h"

#include "GameEngineMesh.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRenderingPipeLine.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineConstantBuffer.h"

#include "GameEngineVertexShader.h"


void GameEngineCore::CoreResourcesInit()
{
	// 버텍스 버퍼의 내용과 인풋 레이아웃의 내용이 더 중요하다.
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);

	//typedef struct D3D11_INPUT_ELEMENT_DESC
	//{
	//	LPCSTR SemanticName; = "POSITION"
	//	UINT SemanticIndex; = 0
	//	DXGI_FORMAT Format; 
	//	UINT InputSlot;
	//	UINT AlignedByteOffset;
	//	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	//	UINT InstanceDataStepRate; 
	//} 	


	//const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
	//UINT NumElements, // 
	//const void* pShaderBytecodeWithInputSignature,  // 쉐이더의 바이너리 코드를 내놔
	//SIZE_T BytecodeLength,
	//ID3D11InputLayout** ppInputLayout // 만들어져 나오는 포인터

	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);
		// 앞면
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, float4::Red };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, float4::Green };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, float4::Black };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, float4::White };

		std::vector<UINT> ArrIndex = { 0, 1, 2, 0, 2, 3 };

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);

	}

	{
		// 최초의 버텍스의 위치를 로컬공간이라고 부릅니다.
		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// 앞면
		ArrVertex[0] = { -0.5f, 0.5f, -0.5f };
		ArrVertex[1] = { 0.5f, 0.5f, -0.5f };
		ArrVertex[2] = { 0.5f, -0.5f, -0.5f };
		ArrVertex[3] = { -0.5f, -0.5f, -0.5f };

		// 뒷면
		ArrVertex[4] = ArrVertex[0].RotaitonXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotaitonXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotaitonXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotaitonXDegReturn(180.0f);

		// 왼쪽면
		ArrVertex[8] = ArrVertex[0].RotaitonYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotaitonYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotaitonYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotaitonYDegReturn(90.0f);

		// 오른쪽
		ArrVertex[12] = ArrVertex[0].RotaitonYDegReturn(-90.0f);
		ArrVertex[13] = ArrVertex[1].RotaitonYDegReturn(-90.0f);
		ArrVertex[14] = ArrVertex[2].RotaitonYDegReturn(-90.0f);
		ArrVertex[15] = ArrVertex[3].RotaitonYDegReturn(-90.0f);

		ArrVertex[16] = ArrVertex[0].RotaitonXDegReturn(90.0f);
		ArrVertex[17] = ArrVertex[1].RotaitonXDegReturn(90.0f);
		ArrVertex[18] = ArrVertex[2].RotaitonXDegReturn(90.0f);
		ArrVertex[19] = ArrVertex[3].RotaitonXDegReturn(90.0f);

		ArrVertex[20] = ArrVertex[0].RotaitonXDegReturn(-90.0f);
		ArrVertex[21] = ArrVertex[1].RotaitonXDegReturn(-90.0f);
		ArrVertex[22] = ArrVertex[2].RotaitonXDegReturn(-90.0f);
		ArrVertex[23] = ArrVertex[3].RotaitonXDegReturn(-90.0f);

		std::vector<GameEngineVertex> cube;
		std::vector<UINT> cubeIndex;
		cube.resize(24);
		cubeIndex.resize(36);
		for (UINT i = 0; i < 6; i++)
		{
			for (UINT j = 0; j < 4; j++)
			{
				cube[i * 4 + j] = { ArrVertex[i * 4 + j], float4::White };

			}
			cubeIndex.push_back(i * 4 + 0);
			cubeIndex.push_back(i * 4 + 1);
			cubeIndex.push_back(i * 4 + 2);
			cubeIndex.push_back(i * 4 + 0);
			cubeIndex.push_back(i * 4 + 2);
			cubeIndex.push_back(i * 4 + 3);

		}
		std::string _Name = "Cube";
		GameEngineVertexBuffer::Create(_Name, cube);
		GameEngineIndexBuffer::Create(_Name, cubeIndex);

	}
	{

		int n = 30; // number of triangles
		std::vector<float4> circleVertex;
		std::vector<GameEngineVertex> circle;
		std::vector<UINT> circleIndex;

		circleVertex.resize(3 * n);
		circle.resize(3 * n);
		circleIndex.resize(3 * n);

		float deltaTheta = 2 * GameEngineMath::PIE / n; // Change in theta for each vertex

		for (int i = 0; i < n; i++) 
		{
			float theta = i * deltaTheta; // Theta is the angle for that triangle
			int index = 3 * i;
	
			circleVertex[index + 0] = float4::Zero;
			circleVertex[index + 2] = float4{ cos(theta), sin(theta), 0 };
			circleVertex[index + 1] = float4(cos(theta + deltaTheta), sin(theta + deltaTheta), 0);

		}

		for (int i = 0; i < 3 * n; i++)
		{
			circle[i] = { circleVertex[i] , float4::White };
			circleIndex[i] = static_cast<UINT>(i);
		}


		std::string _Name = "Circle";
		GameEngineVertexBuffer::Create(_Name, circle);
		GameEngineIndexBuffer::Create(_Name, circleIndex);

	}

	// 버텍스 쉐이더 컴파일
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx" });

		GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");

	}


	{
		D3D11_RASTERIZER_DESC Desc = {};

		//D3D11_FILL_MODE FillMode;
		// 렌더링할 때 사용할 채우기 모드를 결정합니다( D3D11_FILL_MODE 참조 ).
		//D3D11_CULL_MODE CullMode;
		// 지정된 방향을 향하는 삼각형이 그려지지 않음을 나타냅니다( D3D11_CULL_MODE 참조 ).
		//BOOL FrontCounterClockwise;
		// 삼각형이 앞면인지 뒷면인지 결정합니다. 
		// 이 매개변수가 TRUE 이면 정점 이 렌더 대상에서 
		// 시계 반대 방향이면 삼각형이 전면을 향하는 것으로 
		// 간주되고 시계 방향이면 후면을 향하는 것으로 간주됩니다. 
		// 이 매개변수가 FALSE 이면 그 반대입니다.
		//INT DepthBias;
		// 지정된 픽셀에 추가된 깊이 값입니다. 깊이 편향에 대한 정보는 깊이 편향 을 참조하십시오 .
		//FLOAT DepthBiasClamp;
		// 픽셀의 최대 깊이 편향. 깊이 편향에 대한 정보는 깊이 편향 을 참조하십시오 .
		//FLOAT SlopeScaledDepthBias;
		// 주어진 픽셀의 기울기에 대한 스칼라. 깊이 편향에 대한 정보는 깊이 편향 을 참조하십시오 .
		//BOOL DepthClipEnable;
		// 거리에 따라 클리핑을 활성화합니다.
		// 하드웨어는 항상 래스터화된 좌표의 x 및 y 클리핑을 수행합니다.
		// DepthClipEnable이 기본값인 TRUE 로 설정 되면 하드웨어도 z 
		// 값을 자릅니다(즉, 하드웨어는 다음 알고리즘의 마지막 단계를 수행합니다).
		//BOOL ScissorEnable;
		// 가위 사각형 컬링을 활성화합니다. 활성 가위 사각형 외부의 모든 픽셀이 추려집니다.
		//BOOL MultisampleEnable;
		// 다중 샘플 앤티앨리어싱(MSAA) 렌더 대상에서 사변형 또는 알파 라인 앤티앨리어싱 
		// 알고리즘을 사용할지 여부를 지정합니다. 사변형 라인 앤티 앨리어싱 알고리즘을 
		// 사용하려면 TRUE 로 설정 하고 알파 라인 앤티 앨리어싱 알고리즘을 사용하려면 
		// FALSE 로 설정합니다. 이 멤버에 대한 자세한 내용은 비고를 참조하세요.
		//BOOL AntialiasedLineEnable;
		// 선 앤티앨리어싱을 활성화할지 여부를 지정합니다. 선 그리기를 수행하고 MultisampleEnable이 
		// FALSE 인 경우에만 적용됩니다 . 이 멤버에 대한 자세한 내용은 비고를 참조하세요.

		// 와이어 프레임은 선으로 표현하는 겁니다. 
		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		Desc.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("EngineBase", Desc);
	}


	{
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");
			//for (int i = 0; i < 6; i++) {
			//	std::string _BufferName = "Rect" + std::to_string(i);
			//	Pipe->SetVertexBuffer(_BufferName);
			//	Pipe->SetIndexBuffer(_BufferName);

			//}
			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("EngineBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			// Pipe->SetFILL_MODE(D3D11_FILL_WIREFRAME);
		}
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("3DTexture");
			Pipe->SetVertexBuffer("Cube");
			Pipe->SetIndexBuffer("Cube");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("EngineBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			// Pipe->SetFILL_MODE(D3D11_FILL_WIREFRAME);
		}		
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureCircle");
			Pipe->SetVertexBuffer("Circle");
			Pipe->SetIndexBuffer("Circle");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("EngineBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			// Pipe->SetFILL_MODE(D3D11_FILL_WIREFRAME);
		}
	}

}

void GameEngineCore::CoreResourcesEnd()
{
	GameEngineConstantBuffer::ResourcesClear();
	GameEnginePixelShader::ResourcesClear();
	GameEngineRasterizer::ResourcesClear();
	GameEngineVertexShader::ResourcesClear();
	GameEngineIndexBuffer::ResourcesClear();
	GameEngineVertexBuffer::ResourcesClear();
	GameEngineMesh::ResourcesClear();
	GameEngineTexture::ResourcesClear();
	GameEngineRenderTarget::ResourcesClear();
}
