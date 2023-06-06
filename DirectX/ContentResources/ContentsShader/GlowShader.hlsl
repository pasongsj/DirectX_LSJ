cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}


struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

cbuffer AtlasData : register(b1)
{
    float2 FramePos;
    float2 FrameScale;
}


OutPut Percent_PS_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    
    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;
    
    return OutPutValue;
}


cbuffer PercentData : register(b1)
{
    // 상수버퍼는 
    float Percentage;
    bool Affect;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float4 Percent_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);

    if(true == Affect)
    {
        float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);
        float r = Color.r;
        float g = Color.g;
        float b = Color.b;
        float a = Color.a;

        Color.rgb = dot(Color.rgb, float3(0.7 * Percentage, 0.59 * Percentage, 0.11 * Percentage));

        r = r - (r - Color.rgb) * Percentage;
        g = g - (g - Color.rgb) * Percentage;
        b = b - (b - Color.rgb) * Percentage;
        Color.a = a;
        Color.r = r;
        Color.g = g;
        Color.b = b;
    }


    return Color;
}