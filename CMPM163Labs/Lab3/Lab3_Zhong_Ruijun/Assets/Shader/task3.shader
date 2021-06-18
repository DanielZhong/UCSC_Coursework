
Shader "Shaders/FirstShader"
{
    Properties
    {
        _ColorA("Color A", Color) = (1,0,0,1)
        _ColorB("Color B", Color) = (0,1,0,1)
        _BlendFactor("BlendFactor", Range (0, 1)) = 0
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
            _BlendFactor = float4(_SinTime.w / 2 + 0.5, 0.5, 0.5, 1);
            float4 _blendColor = _BlendFactor * _ColorA + (1 - _BlendFactor) * _ColorB;
            return _blendColor;
           
}      
        ENDCG 

	}

    }

}