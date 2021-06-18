
Shader "Shaders/task4"
{
    Properties
    {
        _ColorA("Color A", Color) = (1,0,0,1)
        _ColorB("Color B", Color) = (0,0,0,1)
        _BlendFactor("Blend Factor", Range (0, 1)) = 0
        _DelayFactor("Delay Factor", Range(0, 3)) = 0
    } 

    SubShader
    {
	    Pass 
	    {
	    CGPROGRAM
        #pragma vertex vert
        #pragma fragment frag
        float _BlendFactor;
        float4 _ColorA;
        float4 _ColorB;
        float4 _blendColor;
        float _DelayFactor;



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
            
            float _BlendFactor = sin((_Time.y + _DelayFactor)* 2);
            float4 _BlendColor = _BlendFactor * _ColorA + (1 - _BlendFactor) * _ColorB;

            return _BlendColor;
           
}      
        ENDCG 

	}

    }

}