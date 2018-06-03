// FRAGMENT SHADER
uniform sampler2D texSampler;
uniform int hasTexture;
varying vec2 ftex;

void main() {
	if (hasTexture == 0)
        gl_FragColor = vec4(1, 1, 1, 1);
    else
        gl_FragColor = texture2D(texSampler, ftex);
}
