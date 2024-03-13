/*Texture2D gTexture : register(t0); // Texture register slot can vary based on your shader configuration
SamplerState gSampler : register(s0); // Sampler register slot can vary based on your shader configuration

		// Use the texture in your shader
float4 main(float2 texCoord : TEXCOORD) : SV_TARGET
{
    return gTexture.Sample(gSampler, texCoord);
}*/