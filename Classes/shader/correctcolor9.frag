const char* correctcolor_frag9 = STRINGIFY
(

 \n#ifdef GL_ES\n
 precision lowp float;
 \n#endif\n
 
 varying vec4 v_fragmentColor;
 varying vec2 v_texCoord;

 uniform sampler2D u_masktex;

 void main() {

	 vec4 c = texture2D(CC_Texture0, v_texCoord);

	 vec4 c0 = texture2D(u_masktex, v_texCoord);

	 if (c0.a == 0.0) {
		 c.r = c.g = c.b = c.a = 0.0;
	 } else {
		 float limit = 0.5;
		 if (c.r >= limit && c.g >= limit && c.b >= limit && c.a >= limit ) {
			 c = c0;
		 }
	 }


	 gl_FragColor = v_fragmentColor * c;
 });