const char* correctcolor_frag8 = STRINGIFY
(

 varying vec4 v_fragmentColor;
 varying vec2 v_texCoord;

 uniform sampler2D u_masktex;
 uniform vec4 u_maskrect;

 void main() {

	 vec4 c = texture2D(CC_Texture0, v_texCoord);

	 if (v_texCoord.x > u_maskrect.r && v_texCoord.x < u_maskrect.b &&
		 v_texCoord.y > u_maskrect.g && v_texCoord.y < u_maskrect.a) {

		 vec2 maskTexCoord = vec2((v_texCoord.x - u_maskrect.r)/(u_maskrect.b-u_maskrect.r), (v_texCoord.y - u_maskrect.g)/(u_maskrect.a-u_maskrect.g));

		 vec4 c0 = texture2D(u_masktex, maskTexCoord);
		 
//		 if (c0.a == 0.0 && c.a != 0.0) {
//			 c.r = c.g = c.b = c.a = 0.0;
//		 }

		 float limit = 0.8;
		 if (c.r >= limit && c.g >= limit && c.b >= limit && c.a >= limit ) {
			 c = c0;
		 }
	 }


	 gl_FragColor = v_fragmentColor * c;
 });