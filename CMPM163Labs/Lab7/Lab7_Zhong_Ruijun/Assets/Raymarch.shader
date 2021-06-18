Shader "Unlit/Raymarch"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

           

            #include "UnityCG.cginc"
            #define MAX_STEPS 100
            #define MAX_DIST 100
            #define SURF_DIST 1e-3
            float4 _LightColor0;


            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
                float4 normal : NORMAL;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
                float3 ro : TEXCORD1;
                float3 hitPos : TEXCOORD2;
                float4 worldnormal:TEXCOORD3;
				float4 worldvertex:TEXCOORD4;
                
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                o.ro = mul(unity_WorldToObject, float4(_WorldSpaceCameraPos, 1));
                o.hitPos = v.vertex;
                o.worldnormal = float4(UnityObjectToWorldNormal(v.normal), 1);
				o.worldvertex = mul(unity_ObjectToWorld, v.vertex);
                return o;
            }
            float GetDist(float3 p){
                float d = length(p) - 0.5;
                //d = length(float2(length(p.xz)-0.5, p.y)) - .1;
                return d;
            }
            float Raymarch(float3 ro, float3 rd){
                float dO = 0;
                float dS;
                for(int i=0; i < MAX_STEPS; i++){
                    float3 p = ro + dO * rd;
                    dS = GetDist(p);
                    dO += dS;
                    if(dS<SURF_DIST || dO>MAX_DIST) break;
                }
                return dO;
            }

            float3 GetNormal(float3 p){
                float2 e = float2(1e-2, 0);
                float3 n = GetDist(p) - float3(
                    GetDist(p-e.xyy),
                    GetDist(p-e.yxy),
                    GetDist(p-e.yyx)
                );
                return normalize(n);
            }

            fixed4 frag (v2f i) : SV_Target
            {
                // sample the texture
                float2 uv = i.uv - 0.5;
                float3 ro = i.ro;
                float3 rd = normalize(i.hitPos-ro);

                float d = Raymarch(ro, rd);
                fixed4 col = 0;
                
                if(d < MAX_DIST){
                float3 p = ro + rd * d;
                    float3 n = GetNormal(p);
                    col.rgb = tex2D(_MainTex, i.uv);
                    float3 lightDir = GetNormal(_WorldSpaceLightPos0.xyz);
                    float3 normalDir = GetNormal(p);
                    float3 diffuse = _LightColor0.rgb * (col)* saturate(dot(lightDir, normalDir));
                    return float4(diffuse, 1);
                    
                }
                else
                    discard;

                return col;
            }
            ENDCG
        }
    }
}
