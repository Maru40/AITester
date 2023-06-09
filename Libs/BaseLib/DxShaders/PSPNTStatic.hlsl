//--------------------------------------------------------------------------------------
// File: PSPVTStatic.hlsl
//
//--------------------------------------------------------------------------------------

#include "INCStructs.hlsli"
#include "INCParameters.hlsli"

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

float4 main(PSPNTInput input) : SV_TARGET
{
    //return float4(input.norm, 1.0f);
	
    //return float4(1.0f, 0.0f, 0.0f, 1.0f);
	
	//法線ライティング
	float3 lightdir = normalize(LightDir.xyz);
	float3 N1 = normalize(input.norm);
	float4 Light = (saturate(dot(N1, -lightdir)) * Diffuse) + Emissive;
	Light += input.specular;
	Light.a = Diffuse.a;
	if (Activeflags.x) {
		Light = g_texture.Sample(g_sampler, input.tex) * Light;
	}
	return Light;
}
