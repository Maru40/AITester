struct PSPNTInput
{
    float4 position : SV_POSITION;
    float3 norm : NORMAL;
    float4 specular : COLOR;
    float2 tex : TEXCOORD;
};

cbuffer ParametersBuffer : register(b0)
{
    float4x4 World : packoffset(c0);
    float4x4 View : packoffset(c4);
    float4x4 Projection : packoffset(c8);
    float4 Emissive : packoffset(c12);
    float4 Diffuse : packoffset(c13);
    float4 Specular : packoffset(c14);
    uint4 Activeflags : packoffset(c15); //�t���O
    float4 LightDir : packoffset(c16);
    float4 LightPos : packoffset(c17);
    float4 EyePos : packoffset(c18);
    float4x4 LightView : packoffset(c19);
    float4x4 LightProjection : packoffset(c23);
    float4x3 Bones[72] : packoffset(c27);
};

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

float4 main(PSPNTInput input) : SV_TARGET
{
    return g_texture.Sample(g_sampler, input.tex);
}
