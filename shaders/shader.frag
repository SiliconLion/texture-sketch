#version 330 core
out vec4 FragColor;

in vec2 ourPos;
in vec2 ourTexCoord;

uniform sampler2D myTexture;

void main() {
    FragColor= texture(myTexture, ourTexCoord);
}