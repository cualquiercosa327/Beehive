�,�        ��?�A       񟵦5       �q�          class ion::render::Shader+�.6       񟵦*       �q�          flatcoloured_pqD�V      񟵦J      �q�       .  
//Diffuse
float4 gDiffuseColour = float4(1.0f, 1.0f, 1.0f, 1.0f);

//Matrices
float4x4 gWorldViewProjectionMatrix;

struct InputV
{
	float4 mPosition	: POSITION;
	float4 mColour		: COLOR;
};

struct OutputV
{
	float4 mPosition	: POSITION;
	float4 mColour		: COLOR;
};

OutputV VertexProgram(InputV input)
{
	OutputV output;

	output.mPosition = mul(gWorldViewProjectionMatrix, input.mPosition);
	output.mColour = gDiffuseColour;

	return output;
}

float4 FragmentProgram(OutputV input) : COLOR
{
	return input.mColour;
};
 ���7       񟵦+       �q�          FragmentProgram��1          