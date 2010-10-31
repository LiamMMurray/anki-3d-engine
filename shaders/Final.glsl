// The final pass

#pragma anki vertShaderBegins

#pragma anki include "shaders/SimpleVert.glsl"

#pragma anki fragShaderBegins

uniform sampler2D rasterImage;
in vec2 vTexCoords;
out vec3 fragColor;

void main()
{
	//if( gl_FragCoord.x > 0.5 ) discard;

	fragColor.rgb = texture2D(rasterImage, vTexCoords).rgb;


	//gl_FragColor.rgb = vec3(texture2D(rasterImage, vTexCoords).r);
	/*vec4 c = texture2D( rasterImage, texCoords );
	if( c.r == 0.0 && c.g == 0.0 && c.b==0.0 && c.a != 0.0 )*/
		//gl_FragColor.rgb = vec3( texture2D( rasterImage, texCoords ).a );
	//gl_FragColor.rgb = MedianFilter( rasterImage, texCoords );
	//gl_FragColor.rgb = vec3( gl_FragCoord.xy/tex_size_, 0.0 );
	//gl_FragColor.rgb = vec3( gl_FragCoord.xy*vec2( 1.0/R_W, 1.0/R_H ), 0.0 );
	//gl_FragColor.rgb = texture2D( rasterImage, gl_FragCoord.xy/textureSize(rasterImage,0) ).rgb;
}