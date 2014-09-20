const char* testshader_frag = STRINGIFY(

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_masktex;
uniform vec4 u_maskrect;

void main() {

	vec4 c = texture2D(CC_Texture0, v_texCoord);

	if (v_texCoord.x > u_maskrect.r && v_texCoord.x < u_maskrect.b &&
		v_texCoord.y > u_maskrect.g && v_texCoord.y < u_maskrect.a) {

		vec2 maskTexCoord = vec2((v_texCoord.x - u_maskrect.r)/(u_maskrect.b-u_maskrect.r), (v_texCoord.y - u_maskrect.g)/(u_maskrect.a-u_maskrect.g));
		vec4 maskc = texture2D(u_masktex, maskTexCoord);

		if (maskc.a == 0.0) {
			c.r = c.g = c.b = c.a = 0.0;
		} else if (c.a > 0.5 && !(maskc.r > 0.7 && maskc.g > 0.7 && maskc.b > 0.7 && maskc.a > 0.7)) {
			c.rgb = mix(c.rgb, maskc.rgb, 1.0);
		}
	}
    gl_FragColor = v_fragmentColor * c;
}
);