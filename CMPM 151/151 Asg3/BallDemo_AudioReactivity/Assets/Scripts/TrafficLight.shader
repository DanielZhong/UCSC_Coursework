Shader "Shader/GreenShader"
{
    Properties
    {
        _ColorA("ColorA", Color) = (1,1,1,1)
        _ColorB("ColorB", Color) = (0,0,0,1)
        _BlendFactor("BlendFactor",Range(0,1)) = 0.5
        [IntRange]_DelayFactor("DelayFactor",Range(1,3)) = 1
    }
        SubShader
    {


        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            float4 _ColorA;
            float4 _ColorB;
            float _BlendFactor;
            float _DelayFactor;

            struct VertexShaderInput
            {
                float4 vertex: POSITION;

            };

            struct VertexShaderOutput
            {
                float4 pos: SV_POSITION;

            };

            VertexShaderOutput vert(VertexShaderInput v)
            {
                VertexShaderOutput o;
                o.pos = UnityObjectToClipPos(v.vertex);

                return o;
            }

            float4 frag(VertexShaderOutput i) : SV_TARGET
            {

                _BlendFactor = float4(_SinTime.w / 2 + 1, 0.5, 0.5, 1);
                float _BlendFactor = sin(_DelayFactor * 2 + _Time.y);
                _ColorA = _BlendFactor * _ColorA + (1 - _BlendFactor) * _ColorB;


                return _ColorA;

            }
            ENDCG
        }


    }
}
