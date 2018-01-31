const char *vertexShaderSource = "#version 330 core\n"
	"// x = center_real, y = center_imag\n"
	"uniform vec2 center;\n"

	"// x = width/2, y = height/2\n"
	"uniform vec2 size;\n"

	"layout (location = 0) in vec3 aPos;\n"
	"out vec2 c;\n"

	"void main()\n"
	"{\n"
		"gl_Position = vec4(aPos, 1.0);\n"
		"c = vec2(aPos.x * size.x + center.x, aPos.y * size.y + center.y);\n"
	"}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"in vec2 c;\n"
	"out vec4 fragColor;\n"

	"// Thanks, poro\n"
	"vec3 hsv(float h, float s, float v) {\n"
	    "return mix(vec3(1.),clamp((abs(fract(h+vec3(3.,2.,1.)/3.)*6.-3.)-1.),0.,1.),s)*v;\n"
	"}\n"

	"void main()\n"
	"{\n"
		"float abs = dot(c, c);\n"
		"if (abs > 4)\n"
		"{\n"
			"fragColor = vec4(hsv(0, 0.7, 0.7), 1.0);\n"
			"return;\n"
		"}\n"

		"vec2 z = vec2(c.x * c.x - c.y * c.y + c.x, 2.0 * c.x * c.y + c.y);\n"
		"for (int i = 0; i < 1000; ++i)\n"
		"{\n"
			"abs = dot(z, z);\n"
			"if (abs > 4)\n"
			"{\n"
				"fragColor = vec4(hsv(radians(i), 0.7, 0.7), 1.0);\n"
				"return;\n"
			"}\n"

			"z = vec2(z.x * z.x - z.y * z.y + c.x, 2.0 * z.x * z.y + c.y);\n"
		"}\n"

		"fragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
	"}\n\0";