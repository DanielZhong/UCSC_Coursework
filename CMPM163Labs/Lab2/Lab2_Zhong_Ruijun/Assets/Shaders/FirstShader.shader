// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Shaders/FirstShader"
{
    Properties
    {
        _Color("My Custom Color", Color) = (1,1,1,1)
        _red ("Red Color", Range (0, 1)) = 0
        _green ("Green Color", Range (0, 1)) = 0
        _blue ("Blue Color", Range (0, 1)) = 0
        _alpha ("Alpha", Range (0, 1)) = 0
    } 

    SubShader
    {
	    Pass 
	    {
	    CGPROGRAM
        #pragma vertex vert
        #pragma fragment frag
        float4 _Color;
        float _red;
        float _green;
        float _blue;
        float _alpha;



        struct VertexShaderInput 
        {
              float4 vertex: POSITION;
        };

        struct VertexShaderOutput
        {
              float4 pos: SV_POSITION;
        } ;

        VertexShaderOutput vert(VertexShaderInput v)
        {
            VertexShaderOutput o;
                
            o.pos = UnityObjectToClipPos(v.vertex);
                
            return o; 
        }
        float4 frag(VertexShaderOutput i):SV_TARGET
        {
        
           float4 _Color = float4 (_red, _green, _blue, _alpha);
           return _Color;
           
}      
        ENDCG 

	}

    }

}