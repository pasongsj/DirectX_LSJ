#include "PrecompileHeader.h"
#include "GameEngineCore.h"
#include <GameEngineBase\GameEngineDebug.h>
#include <GameEnginePlatform\GameEngineWindow.h>
#include <GameEnginePlatform\GameEngineSound.h>
#include "GameEngineResource.h"
#include "GameEngineShaderResHelper.h"

#include "GameEngineVertex.h"

#include "GameEngineMesh.h"
#include "GameEngineBlend.h"
#include "GameEngineTexture.h"
#include "GameEngineRasterizer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineVertexShader.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineRenderingPipeLine.h"


void GameEngineCore::CoreResourcesInit()
{
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");

		std::vector<GameEngineFile> File = NewDir.GetAllFile({ ".Png", });


		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}


	// ���ؽ� ������ ����� ��ǲ ���̾ƿ��� ������ �� �߿��ϴ�.
	// �� ���� �̷��� ������ ������ �־� ��� �ǹ�
	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT_R32G32B32A32_FLOAT);

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
	//const void* pShaderBytecodeWithInputSignature,  // ���̴��� ���̳ʸ� �ڵ带 ����
	//SIZE_T BytecodeLength,
	//ID3D11InputLayout** ppInputLayout // ������� ������ ������

	{
		D3D11_SAMPLER_DESC SamperData = {};

		// 

		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		// �ؽ�ó�� �ָ������� ��������
		// �ȹ�����.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("CLAMPSAMPLER", SamperData);
	}

	{
		D3D11_SAMPLER_DESC SamperData = {};

		// 

		SamperData.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamperData.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// �ؽ�ó�� �ָ������� ��������
		// �ȹ�����.
		SamperData.MipLODBias = 0.0f;
		SamperData.MaxAnisotropy = 1;
		SamperData.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		SamperData.MinLOD = -FLT_MAX;
		SamperData.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("WRAPSAMPLER", SamperData);
	}

	{
		// ����
		D3D11_BLEND_DESC Desc = { 0, };

		// �ڵ����� ���ĺκ��� �����ؼ� ������ִ� �ǵ�
		// ��������ϴ�.
		Desc.AlphaToCoverageEnable = false;
		// ���带 ������ �����ų�
		// TRUE�� ���带 ������ �ֽ��ϴ�.
		// false�� ��� ����Ÿ���� �ְ� 0���� ���õ� �ɷ� ���δ� ����.
		Desc.IndependentBlendEnable = false;

		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_ALPHA;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;

		GameEngineBlend::Create("AlphaBlend", Desc);
	}

	{
		std::vector<GameEngineVertex> ArrVertex;
		ArrVertex.resize(4);

		// 0   1
		// 3   2
		// �ո�
		ArrVertex[0] = { { -0.5f, 0.5f, 0.0f }, {0.0f, 0.0f} };
		ArrVertex[1] = { { 0.5f, 0.5f, 0.0f }, {1.0f, 0.0f} };
		ArrVertex[2] = { { 0.5f, -0.5f, 0.0f }, {1.0f, 1.0f} };
		ArrVertex[3] = { { -0.5f, -0.5f, 0.0f }, {0.0f, 1.0f} };

		std::vector<UINT> ArrIndex = {0, 1, 2, 0, 2, 3};

		GameEngineVertexBuffer::Create("Rect", ArrVertex);
		GameEngineIndexBuffer::Create("Rect", ArrIndex);

	}

	{
		// ������ ���ؽ��� ��ġ�� ���ð����̶�� �θ��ϴ�.
		std::vector<float4> ArrVertex;
		ArrVertex.resize(24);
		// �ո�
		ArrVertex[0] = { -0.5f, 0.5f, -0.5f };
		ArrVertex[1] = { 0.5f, 0.5f, -0.5f };
		ArrVertex[2] = { 0.5f, -0.5f, -0.5f };
		ArrVertex[3] = { -0.5f, -0.5f, -0.5f };

		// �޸�
		ArrVertex[4] = ArrVertex[0].RotaitonXDegReturn(180.0f);
		ArrVertex[5] = ArrVertex[1].RotaitonXDegReturn(180.0f);
		ArrVertex[6] = ArrVertex[2].RotaitonXDegReturn(180.0f);
		ArrVertex[7] = ArrVertex[3].RotaitonXDegReturn(180.0f);

		// ���ʸ�
		ArrVertex[8] = ArrVertex[0].RotaitonYDegReturn(90.0f);
		ArrVertex[9] = ArrVertex[1].RotaitonYDegReturn(90.0f);
		ArrVertex[10] = ArrVertex[2].RotaitonYDegReturn(90.0f);
		ArrVertex[11] = ArrVertex[3].RotaitonYDegReturn(90.0f);

		// ������
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

	// ���ؽ� ���̴� ������
	{
		GameEngineDirectory NewDir;
		NewDir.MoveParentToDirectory("EngineResources");
		NewDir.Move("EngineResources");
		NewDir.Move("Shader");

		std::vector<GameEngineFile> Files = NewDir.GetAllFile({ ".hlsl", ".fx"});

		std::shared_ptr<GameEngineVertexShader> VertexShader = GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		//GameEngineVertexShader::Load(Files[0].GetFullPath(), "Texture_VS");
		GameEnginePixelShader::Load(Files[0].GetFullPath(), "Texture_PS");

		//for (size_t i = 0; i < Files.size(); i++)
		//{
		//}

	}


	{
		D3D11_RASTERIZER_DESC Desc = {};

		//D3D11_FILL_MODE FillMode;
		// �������� �� ����� ä��� ��带 �����մϴ�( D3D11_FILL_MODE ���� ).
		//D3D11_CULL_MODE CullMode;
		// ������ ������ ���ϴ� �ﰢ���� �׷����� ������ ��Ÿ���ϴ�( D3D11_CULL_MODE ���� ).
		//BOOL FrontCounterClockwise;
		// �ﰢ���� �ո����� �޸����� �����մϴ�. 
		// �� �Ű������� TRUE �̸� ���� �� ���� ��󿡼� 
		// �ð� �ݴ� �����̸� �ﰢ���� ������ ���ϴ� ������ 
		// ���ֵǰ� �ð� �����̸� �ĸ��� ���ϴ� ������ ���ֵ˴ϴ�. 
		// �� �Ű������� FALSE �̸� �� �ݴ��Դϴ�.
		//INT DepthBias;
		// ������ �ȼ��� �߰��� ���� ���Դϴ�. ���� ���⿡ ���� ������ ���� ���� �� �����Ͻʽÿ� .
		//FLOAT DepthBiasClamp;
		// �ȼ��� �ִ� ���� ����. ���� ���⿡ ���� ������ ���� ���� �� �����Ͻʽÿ� .
		//FLOAT SlopeScaledDepthBias;
		// �־��� �ȼ��� ���⿡ ���� ��Į��. ���� ���⿡ ���� ������ ���� ���� �� �����Ͻʽÿ� .
		//BOOL DepthClipEnable;
		// �Ÿ��� ���� Ŭ������ Ȱ��ȭ�մϴ�.
		// �ϵ����� �׻� ������ȭ�� ��ǥ�� x �� y Ŭ������ �����մϴ�.
		// DepthClipEnable�� �⺻���� TRUE �� ���� �Ǹ� �ϵ��� z 
		// ���� �ڸ��ϴ�(��, �ϵ����� ���� �˰����� ������ �ܰ踦 �����մϴ�).
		//BOOL ScissorEnable;
		// ���� �簢�� �ø��� Ȱ��ȭ�մϴ�. Ȱ�� ���� �簢�� �ܺ��� ��� �ȼ��� �߷����ϴ�.
		//BOOL MultisampleEnable;
		// ���� ���� ��Ƽ�ٸ����(MSAA) ���� ��󿡼� �纯�� �Ǵ� ���� ���� ��Ƽ�ٸ���� 
		// �˰����� ������� ���θ� �����մϴ�. �纯�� ���� ��Ƽ �ٸ���� �˰����� 
		// ����Ϸ��� TRUE �� ���� �ϰ� ���� ���� ��Ƽ �ٸ���� �˰����� ����Ϸ��� 
		// FALSE �� �����մϴ�. �� ����� ���� �ڼ��� ������ ��� �����ϼ���.
		//BOOL AntialiasedLineEnable;
		// �� ��Ƽ�ٸ������ Ȱ��ȭ���� ���θ� �����մϴ�. �� �׸��⸦ �����ϰ� MultisampleEnable�� 
		// FALSE �� ��쿡�� ����˴ϴ� . �� ����� ���� �ڼ��� ������ ��� �����ϼ���.

		// ���̾� �������� ������ ǥ���ϴ� �̴ϴ�. 
		//Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Desc.FrontCounterClockwise = FALSE;

		std::shared_ptr<GameEngineRasterizer> Res = GameEngineRasterizer::Create("Engine2DBase", Desc);
	}


	{
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTexture");

			Pipe->SetVertexBuffer("Rect");
			Pipe->SetIndexBuffer("Rect");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			Pipe->SetBlend("AlphaBlend");
			// Pipe->SetFILL_MODE(D3D11_FILL_WIREFRAME);
		}
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("3DTexture");
			Pipe->SetVertexBuffer("Cube");
			Pipe->SetIndexBuffer("Cube");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			Pipe->SetBlend("AlphaBlend");

		}
		{
			std::shared_ptr<GameEngineRenderingPipeLine> Pipe = GameEngineRenderingPipeLine::Create("2DTextureCircle");
			Pipe->SetVertexBuffer("Circle");
			Pipe->SetIndexBuffer("Circle");
			Pipe->SetVertexShader("TextureShader.hlsl");
			Pipe->SetRasterizer("Engine2DBase");
			Pipe->SetPixelShader("TextureShader.hlsl");
			Pipe->SetBlend("AlphaBlend");
			// Pipe->SetFILL_MODE(D3D11_FILL_WIREFRAME);
		}
	}
}

void GameEngineCore::CoreResourcesEnd()
{
	GameEngineMesh::ResourcesClear();
	GameEngineBlend::ResourcesClear();
	GameEngineTexture::ResourcesClear();
	GameEngineRasterizer::ResourcesClear();
	GameEngineIndexBuffer::ResourcesClear();
	GameEnginePixelShader::ResourcesClear();
	GameEngineVertexShader::ResourcesClear();
	GameEngineVertexBuffer::ResourcesClear();
	GameEngineRenderTarget::ResourcesClear();
	GameEngineConstantBuffer::ResourcesClear();
	GameEngineRenderingPipeLine::ResourcesClear();
}
