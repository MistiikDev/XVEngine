cbuffer Matrices : register(b0) {
    float4x4 mvp;
};

struct VSInput {
    float3 pos: POSITION;
    float3 color: COLOR;
};

struct VSOutput {
    float4 sv_pos: SV_POSITION;
    float3 color: COLOR;
};

VSOutput VS(VSInput input)
{
    VSOutput o;
    o.color = input.color;
    o.sv_pos = mul(float4(input.pos, 1.0), mvp);

    return o;
}

float4 PS(VSOutput vs_output) : SV_TARGET
{
    return float4(vs_output.color, 1.0f);
}