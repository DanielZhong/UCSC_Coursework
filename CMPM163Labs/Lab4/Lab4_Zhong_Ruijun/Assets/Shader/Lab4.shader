Shader "Unlit/Lab4"
{
    Properties
    {
        _MainTex("Texture", 2D) = "white" {}
        _Wavyness("Wavyness", float) = 0
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
        };

        struct VertexShaderOutput
        {
              float4 pos: SV_POSITION;
              float2 uv: TEXCOORD0;
              float2 objPos: TEXCOORD1;
        } ;

        VertexShaderOutput vert(VertexShaderInput v)
        {
            VertexShaderOutput o;
            o.objPos = v.vertex;
            o.uv = v.uv;
            v.vertex.y = sin(v.uv * _Wavyness + _Time.y*2);
            o.pos = UnityObjectToClipPos(v.vertex);

            return o; 
        }
        float4 frag(VertexShaderOutput i):SV_TARGET
        {
            float4 color = tex2D(_MainTex, i.uv);
            return color; 

             
        }      
        ENDCG 
       } 
    }
}