
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
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};


cbuffer AtlasData : register(b1)
{
    float2 FramePos;
    float2 FrameScale;
}


OutPut BrightShader_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);

    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;
    
    return OutPutValue;
}

cbuffer BrightOption : register(b0)
{
    float4 BrightOptionValue;
}


Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

struct OutColor
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target2;
    float4 Color3 : SV_Target3;
};

float4 BrightShader_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);


    if(BrightOptionValue.x > 0)
    {
        float r =  Color.r * 0.35;
        float g =  Color.g * 0.35;
        float b =  Color.b * 0.35;

        
        r  += 0.65;
        g  += 0.65;
        b  += 0.65;

        Color.r = r;
        Color.g = g;
        Color.b = b;
    }
    return Color;
}


// 노이즈 쉐이더 써도 될지도??
//float4 GlowShader_PS(OutPut _Value) : SV_Target0
//{
//    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);
//
//
//     if(0 < PercentOptionValue.a)
//    {
//        float r = Color.r;
//        float g = Color.g;
//        float b = Color.b;
//        float a = Color.a;
//
//        Color.rgb = dot(Color.rgb, float3(0.7 * PercentOptionValue.r, 0.59 * PercentOptionValue.r, 0.11 * PercentOptionValue.r));
//
//        r = r - (r - Color.rgb) * PercentOptionValue.r;
//        g = g - (g - Color.rgb) * PercentOptionValue.r;
//        b = b - (b - Color.rgb) * PercentOptionValue.r;
//        Color.a = a;
//        Color.r = r;
//        Color.g = g;
//        Color.b = b;
//    }
//    
//    return Color;
//}



// + 추가

//float luma(vec4 color) {
//  return dot(color.rgb, vec3(0.299, 0.587, 0.114));
//}
//
//void mainImage( out vec4 fragColor, in vec2 fragCoord )
//{
//	vec2 uv = fragCoord.xy / iResolution.xy;
//	fragColor = vec4(vec3(luma(texture(iChannel0, uv))), 1.0);
//}