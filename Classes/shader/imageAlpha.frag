const char* imageAlpha_frag = STRINGIFY(

\n#ifdef GL_ES\n
precision lowp float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_masktex;

void main() {

	vec4 c = texture2D(CC_Texture0, v_texCoord);
	vec4 cm = texture2D(u_masktex, v_texCoord);

	c.a = cm.r;

	gl_FragColor = v_fragmentColor * c;
}
);