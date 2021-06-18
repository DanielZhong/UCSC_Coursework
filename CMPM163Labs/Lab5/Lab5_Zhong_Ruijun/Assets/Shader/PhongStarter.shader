// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Shaders/PhongStarter"
{
	Properties{
		_MainTex("Albedo", 2D) = "white" {}
		_Color("Color", Color) = (1,1,1,1)
		[MaterialToggle]_Ambient("Ambient",Float) = 0
		[MaterialToggle]_Diffuse("Diffuse",Float) = 0
		[MaterialToggle]_Specular("Specular",Float) = 0
		_Shininess("Shininess", Float) = 0.5
		_SpecularColor("Specular Color", Color) = (1,1,1,1)
	}

	SubShader
	{
		//PASS 1		
		Pass 
		{
			Tags { "LightMode" = "ForwardBase" } // Since we are doing forward rendering and we want to get directional light
			// Tags { "LightMode" = "ForwardAdd"} For point lights. One pass per light
			// Blend One One //Turn on additive blending if you have more than one point light (optional)
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag


			#include "UnityCG.cginc" // Predefined variables and helper functions Unity provides

			float4 _LightColor0; //Light color, declared in UnityCG
			sampler2D _MainTex;
			float4 _Color;
			bool _Ambient;
			bool _Diffuse;
			bool _Specular;
			float _Shininess;
			float4 _SpecularColor;





			struct VertexShaderInput
			{
				float4 vertex : POSITION;
				float2 uv	  : TEXCOORD0;
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

			float4 frag(VertexShaderOutput i):SV_TARGET
			{
				float4 output;
				output = tex2D(_MainTex, i.uv);
				float3 ambient= UNITY_LIGHTMODEL_AMBIENT.rgb;
				float3 lightDir = normalize(_WorldSpaceLightPos0.xyz);
				float3 normalDir = normalize(i.worldnormal);
				float3 diffuse = _LightColor0.rgb * (output*_Color.rgb )* saturate(dot(lightDir, normalDir));
				float3 reflectDir = normalize(reflect(-lightDir, normalDir));//
				float3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldvertex);//
				//float3 viewDir = normalize(_WorldSpaceCameraPos.xyz - i.worldvertex); // Blinn-Phong
				//float3 helfDir = normalize(lightDir + viewDir);//Blinn-Phong
				float3 specular = _SpecularColor * _LightColor0.rgb * pow(max(dot(reflectDir, viewDir), 0.0),_Shininess);//
				//float3 specular = _SpecularColor * _LightColor0.rgb * pow(max(dot(normalDir, viewDir), 0), _Shininess);//



				float3 tempcolor = diffuse + ambient + specular;
				
				

				if (_Ambient & _Diffuse & _Specular)
					return float4(tempcolor, 0.5);
				else if (_Diffuse)
					return float4(diffuse, 1);
				else if (_Specular)
					return float4(specular, 0);
				else if (!_Ambient)
					return float4(ambient, 0.5);
				else
					return output;

					
				
		
			}
			ENDCG
		}

		//// PASS 2	
		//Pass
		//{
		//	//Tags { "LightMode" = "ForwardBase" } // Since we are doing forward rendering and we want to get directional light
		//	Tags { "LightMode" = "ForwardAdd"} //For point lights. One pass per light
		//	// Blend One One //Turn on additive blending if you have more than one point light (optional)
		//	CGPROGRAM
		//	#pragma vertex vert
		//	#pragma fragment frag

		//	#include "UnityCG.cginc" // predefined variables and helper functions Unity provides

		//	float4 _LightColor0; //Light color, declared in UnityCG
		//	sampler2D _MainTex;
		//	float4 _Color;

		//	struct VertexShaderInput
		//	{
		//		float4 vertex : POSITION;
		//		float2 uv	  : TEXCOORD0;

		//	};

		//	struct VertexShaderOutput
		//	{
		//		float4 pos:SV_POSITION;
		//		float2 uv: TEXCOORD0;

		//	};

		//	VertexShaderOutput vert(VertexShaderInput v)
		//	{
		//		VertexShaderOutput o;
		//		o.uv = v.uv;
		//		o.pos = UnityObjectToClipPos(v.vertex);
		//		return o;
		//	}

		//	float4 frag(VertexShaderOutput i) :SV_TARGET
		//	{
		//		float4 output;
		//		output = tex2D(_MainTex, i.uv);
		//		return output * _LightColor0;
		//	}
		//	ENDCG
		//}
	}
}
