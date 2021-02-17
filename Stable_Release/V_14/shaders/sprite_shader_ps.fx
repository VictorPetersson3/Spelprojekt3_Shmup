#include "common.fx"

SamplerState SampleType;

#define DIFFUSE_MAP 0
#define NORMAL_MAP 1

Texture2D shaderTextures[2] : register( t1 );

float4 PShader(PixelInputType input) : SV_TARGET
{
	float4 Diffuse = shaderTextures[DIFFUSE_MAP].Sample(SampleType, input.tex) * input.color;
	
	#ifdef USE_NOISE
	float4 noise = myNoiseTexture.Sample(SampleType, input.tex); 
	#endif
	
	float3 AmbientColor = Diffuse.xyz * myAmbience;
	float3 DirectColor = float3(0, 0, 0);
	
	#ifdef USE_LIGHTS
	float3 Normal = normalize((shaderTextures[NORMAL_MAP].Sample(SampleType, input.tex).xyz * 2.0f) - 1.0f);
	float2 Resolution = myResolution.xy;
	for (unsigned int index = 0; index < myNumberOfLights; index++)
	{
		float Intensity = myLights[index].myPosition.z;
		float Falloff = myLights[index].myPosition.w;

		float2 difference = float2((myLights[index].myPosition.xy - input.position.xy) / Resolution.xy);
		difference.x *= (Resolution.x / Resolution.y);
		difference.y *= -1; 

		float distance = length(difference); 

		float linearAttenuation = saturate((Falloff - distance) / Falloff);
		float physicalAttenuation = 1.0f/(1.0f + distance);
		float totalAttenuation = linearAttenuation * physicalAttenuation;

		float3 direction = normalize(float3(difference.xy, (Falloff / 2)));

		float lambert = dot(direction, Normal); 

		DirectColor += Diffuse.xyz * Intensity * totalAttenuation * myLights[index].myLightColor.xyz * lambert;
		
	} 
	#endif
	
	// Normal TGA2D
    float4 color = float4(AmbientColor + DirectColor, Diffuse.w);
	
	// Flash effect Hijack
	if (input.color.r > 1.0)
    {
		// White
        if (input.color.b > 1.0)
        {
            color.rgb = 1.0;
        }
		// Red
		else
        {
            color.r = 255.0 / 255.0;
            color.g = 16.0 / 255.0;
            color.b = 31.0 / 255.0;
        }
    }
	
	return color;
}