// FRAGMENT SHADER
uniform sampler2D texSampler;
uniform bool hasTexture;
varying vec2 ftex;
uniform vec3 diffuse;
uniform vec3 specular;

void main() {
	if (hasTexture)
        gl_FragColor = texture2D(texSampler, ftex);
    else
        gl_FragColor = vec4(1, 1, 1, 1);
}
