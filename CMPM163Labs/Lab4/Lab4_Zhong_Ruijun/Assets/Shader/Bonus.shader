Shader "Unlit/Bonus"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
    } 

    SubShader
    {
       Pass 
	   {
        CGPROGRAM
        #include "UnityCG.cginc"
        #pragma vertex vert
        #pragma fragment frag
        sampler2D _MainTex;
        sampler2D _MainTex1;
        float _Wavyness;



        struct VertexShaderInput 
        {
              float4 vertex: POSITION;
              float2 uv    : TEXCOORD0;
              float4 normal : NORMAL;
        };

        struct VertexShaderOutput
        {
              float4 pos: SV_POSITION;
              float2 uv: TEXCOORD0;
              float2 objPos: TEXCOORD1;
              float4 normal : TEXCOORD2;
        } ;

        VertexShaderOutput vert(VertexShaderInput v)
        {
            VertexShaderOutput o;
            o.objPos = v.vertex;
            o.uv = v.uv;
            o.normal = v.normal;
            o.pos = UnityObjectToClipPos(v.vertex);

            return o; 
        }
        float4 frag(VertexShaderOutput i):SV_TARGET
        {
            return i.normal;

             
        }      
        ENDCG 
       } 
    }
}
