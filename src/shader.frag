#version 460

out vec4 FragColor;

uniform int width;
uniform int height;

void main () {
    gl_FragColor = vec4(sin(gl_FragCoord.x / width * 10), cos(gl_FragCoord.y / height * 10), 0, 1);
}

