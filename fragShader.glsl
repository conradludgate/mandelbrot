#version 330 core
in vec2 c;
out vec4 fragColor;

// Thanks, poro
vec3 hsv(float h, float s, float v) {
    return mix(vec3(1.),clamp((abs(fract(h+vec3(3.,2.,1.)/3.)*6.-3.)-1.),0.,1.),s)*v;
}

void main()
{
	float abs = dot(c, c);
	if (abs > 4)
	{
		fragColor = vec4(hsv(0, 0.7, 0.7), 1.0);
		return;
	}

	vec2 z = vec2(c.x * c.x - c.y * c.y + c.x, 2.0 * c.x * c.y + c.y);
	for (int i = 0; i < 1000; ++i)
	{
		abs = dot(z, z);
		if (abs > 4)
		{
			fragColor = vec4(hsv(radians(i), 0.7, 0.7), 1.0);
			return;
		}

		z = vec2(z.x * z.x - z.y * z.y + c.x, 2.0 * z.x * z.y + c.y);
	}

	fragColor = vec4(0.0, 0.0, 0.0, 1.0);
}