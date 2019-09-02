#version 330 core
out vec4 FragColor;
in vec3 outColor;

void main()
{
    FragColor = vec4(outColor, 1.0);    // note how the position value is linearly interpolated to get all the different colors
}

