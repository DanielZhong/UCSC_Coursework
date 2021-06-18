Shader "Shader/Shader"
{
    Properties
    {
        _Albedo("Albedo", 2D) = "white" {}
        _Metalness("Metalness", 2D) = "white" {}
        _Roughness("Roughness", 2D) = "white" {}
        _SpecularColor("Specular Color", Color) = (1,1,1,1)
        _Cube("Cubemap", CUBE) = "" {}
        
    }
    SubShader
    {
        

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"

            float4 _LightColor0;
            sampler2D _Albedo;
            sampler2D _Metalness;
            sampler2D _Roughness;
            float4 _SpecularColor;
            samplerCUBE _Cube;
            
            
            struct VertexShaderInput
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
                float4 normal : NORMAL;
            };

            struct VertexShaderOutput
            {
                float4 pos:SV_POSITION;
                float2 uv: TEXCOORD0;
                float4 worldnormal:TEXCOORD1;
                float4 worldvertex:TEXCOORD2;
  
            };


            VertexShaderOutput vert(VertexShaderInput v)
            {
                VertexShaderOutput o;
                o.uv = v.uv;
                o.pos = UnityObjectToClipPos(v.vertex);
                o.worldnormal = float4(UnityObjectToWorldNormal(v.normal), 1);
                o.worldvertex = mul(unity_ObjectToWorld, v.vertex);

                return o;
            }

            float DistributionGGX(float NdotH, float roughness) 
            {
                float a2 = roughness * roughness;
                float NdotH2 = NdotH * NdotH;

                float nom = a2;
                float denom = (NdotH2 * (a2 - 1.0) + 1.0);
                denom = 3.14 * denom * denom;


                return nom / denom;

            }
            
            float GeometrySchlickGGX(float NdotV, float roughness)
            {
                float nom = NdotV;
                float denom = NdotV * (1.0 - roughness) + roughness;

                return nom / denom;

            }

            float GeometrySmith(float NdotV, float NdotL, float roughness)
            {
                float ggx1 = GeometrySchlickGGX(NdotV, roughness);
                float ggx2 = GeometrySchlickGGX(NdotL, roughness);

                return ggx1 * ggx2;
            }

            float3 FresnelSchlick(float3 F0, float NdotV)
            {
                return F0 + (1.0 - F0) * pow(1.0 - NdotV, 5.0);
            }


            float4 frag(VertexShaderOutput i) : SV_TARGET
            {
                float3 lightDir = normalize(_WorldSpaceLightPos0.xyz);
                float3 normalDir = normalize(i.worldvertex);
                float3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldvertex);
                float3 camDir = normalize(_WorldSpaceCameraPos.xyz);
                float3 halfVector = normalize(lightDir + viewDir);
                float3 Reflect_Direction = reflect(normalDir, viewDir);
                float3 Refrag_Direction = refract(-viewDir, normalize(i.worldnormal) ,0.5);

                float NdotL = saturate(dot(i.worldnormal, normalize(lightDir)));
                float NdotH = saturate(dot(i.worldnormal, halfVector));
                float NdotV = saturate(dot(i.worldnormal, normalize(viewDir)));
                
                float4 albedo = tex2D(_Albedo, i.uv);
                float4 col1 = texCUBE(_Cube, Reflect_Direction);
                float4 col = texCUBE(_Cube, Refrag_Direction);
                float roughness = tex2D(_Roughness, i.uv);
                float metalness = tex2D(_Metalness, i.uv);
                float3 F0 = lerp(_SpecularColor, tex2D(_Albedo, i.uv).rgb, metalness);

                float D = DistributionGGX(NdotH,roughness);
                float G = GeometrySmith(NdotV,NdotL,roughness);
                float3 F = FresnelSchlick(F0,NdotV);

               
               
                
                float3 Diffuse_factor = 1 - F;
                Diffuse_factor = Diffuse_factor * (1 - metalness);
                float3 DiffuseBRDF = Diffuse_factor * albedo;
                float3 SpecularBRDF = (D * G * F) / (4 * NdotV * NdotL);
                float3 task6c = lerp(col1, col, 0.7);
                //float4 Color = float4(DiffuseBRDF + SpecularBRDF + task6c, 0.5) * _LightColor0 * NdotL;
                float4 Color = float4(DiffuseBRDF + SpecularBRDF + col, 0.5) * _LightColor0 * NdotL;



                

                return Color;
            }

                ENDCG
        }
    }
}
