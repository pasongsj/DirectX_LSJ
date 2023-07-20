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

OutPut CircleTrans_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    // 화면 전체 범위
    return OutPutValue;
}


cbuffer TimeData : register(b1)
{
    // 상수버퍼는 
    float4 TimeValue;
}


Texture2D DiffuseTex : register(t0);
SamplerState POINTSAMPLER : register(s0);

float4 CircleTrans_PS(OutPut _Value) : SV_Target0
{
    float Time = TimeValue.x;
    
    float2 ScreenSize = float2(1280.0f, 720.0f);
    float2 OrientUV = _Value.UV.xy;
    float R = ScreenSize.x /ScreenSize.y;  
    
    float4 Center = float4(0.5f, 0.5f, 0.0f, 0.0f);
    Center.x *= R;
    OrientUV.x = OrientUV.x * R;
    float Len = length(Center.xy - OrientUV.xy);
    
    
    
    float4 ResultColor = DiffuseTex.Sample(POINTSAMPLER, _Value.UV.xy);
    if(Len >= Time)
    {
        ResultColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    return ResultColor;

}

//    vec2 uv = (fragCoord - iResolution.xy * 0.5) / iResolution.y;
//
//    // input circle radius
//    float inputRadius = (1.0 + sin(iTime)) * 0.5;
//    
//    float l = length(uv);
//    float a = smoothstep(inputRadius + 0.005, inputRadius, l);
//    vec4 c = texture(iChannel0, uv) * a;
//
//    // Output to screen
//    fragColor = vec4(c.rgb, 1.0);