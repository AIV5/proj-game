#version 460

out vec4 FragColor;

uniform int width;
uniform int height;

void main () {
    gl_FragColor = vec4(gl_FragCoord.x / width, gl_FragCoord.y / height, 0, 1);
}

