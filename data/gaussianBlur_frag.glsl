#version 110

uniform sampler2D tex0;

void main()
{
    float texR = texture2D(tex0, gl_TexCoord[0].st).r;
    float texG = texture2D(tex0, gl_TexCoord[0].st).g;
    float dstColor = ((14.0 - texR * 256.0) - texG) / 14.0;
    if(texR == 0.0 && texG == 0.0) dstColor = 0.0;

	gl_FragColor.r = dstColor;
    gl_FragColor.g = dstColor;
    gl_FragColor.b = dstColor;
	gl_FragColor.a = 1.0;
}