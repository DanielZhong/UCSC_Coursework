Shader "Unlit/NewUnlitShader"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        [MaterialToggle]_Invert("Invert",Float) = 0
        [MaterialToggle]_Grain("Grain",Float) = 0
        [MaterialToggle]_Blur("Blur",Float) = 0
        _Brightness ("Brightness", Range (0, 1)) = 0
        _Saturation ("Saturation", Range (0, 1)) = 0
        _Contrast ("Contrast", Range (0, 1)) = 0
    }
    SubShader
    {
            Cull Off ZWrite Off ZTest Always

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag


            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;
            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                // sample the texture
                fixed4 col = tex2D(_MainTex, i.uv);
                col.rgb = 1 - col.rgb;
                return col;
            }
            ENDCG
        }
    }
}
