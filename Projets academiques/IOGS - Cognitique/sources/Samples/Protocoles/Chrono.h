/************************************************************************************
 Filename    :   Chrono.h
 Content     :   
 Created     :   November 22th, 2018
 Author      :   Olivier Roupin
 Copyright   :   
 *************************************************************************************/

#ifndef Chrono_h
#define Chrono_h

#include "GL/CAPI_GLE.h"
#include "Extras/OVR_Math.h"
#include "OVR_CAPI_GL.h"
#include <assert.h>

using namespace OVR;

#ifndef VALIDATE
    #define VALIDATE(x, msg) if (!(x)) { MessageBoxA(NULL, (msg), "OculusRoomTiny", MB_ICONERROR | MB_OK); exit(-1); }
#endif

#ifndef OVR_DEBUG_LOG
    #define OVR_DEBUG_LOG(x)
#endif

struct Chrono
{
	int		maxTime;
	int		originTime;
	int		numModels;
	int		numLetters;
#define DIGITS 12
	Model * Models[DIGITS];
	char	Digits[DIGITS]; //' ', '0'-'9' et ':'

	void    Add(Model * n)
	{
		Models[numModels++] = n;
	}

	void EraseText()
	{
		numLetters = 0;
		for (int i = 0; i < numModels; ++i)
		{
			Models[i]->numIndices = 0;
			Models[i]->numVertices = 0;
		}
	}

#define SIZEDIGIT 40.0f
#define DEPTH 1.0f

	void AddDigit(int i)
	{
		numLetters++;
		float originex = (float)((numLetters - 1) % 32-0.0675f) / SIZEDIGIT;
		float originey = (float)((numLetters - 1) / 32-0.0675f) / SIZEDIGIT;
		Model * m;
		if (i >= 0) //'0'-'9' et ':'
			m = Models[i + 1];
		else //' '
			m = Models[0];
		if (maxTime)
			m->AddSolidColorBox(originex, originey, DEPTH, originex + 0.025f, originey + 0.025f, DEPTH, 0xffff0000);
		else
			m->AddSolidColorBox(originex, originey, DEPTH, originex + 0.025f, originey + 0.025f, DEPTH, 0xffffffff);
		m->AllocateBuffers();
	}

	void AddSeparator()
	{
		numLetters++;
		float originex = (float)((numLetters - 1) % 32-0.0675f) / SIZEDIGIT;
		float originey = (float)((numLetters - 1) / 32-0.0675f) / SIZEDIGIT;
		Model * m = Models[11];
		if (maxTime)
			m->AddSolidColorBox(originex, originey, DEPTH, originex + 0.025f, originey + 0.025f, DEPTH, 0xffff0000);
		else
			m->AddSolidColorBox(originex, originey, DEPTH, originex + 0.025f, originey + 0.025f, DEPTH, 0xffffffff);
		m->AllocateBuffers();
	}

	void SetTime(int time, int origin)
	{
		maxTime = time;
		originTime = origin;
	}

	void GiveTime(int time)
	{
		maxTime += time;
	}

	void PrintTime(int time) //time ms
	{
		time -= originTime;
		EraseText();
		if (maxTime)
			time = maxTime - time;
		if (time >= 0)
		{
			int ms = time % 1000;
			time = (time - ms) / 1000;
			int s = time % 60;
			time = (time - s) / 60;
			int m = time % 60;
			time = (time - m) / 60;
			PrintTime(time, m, s, ms);
		}
		else
		{
			if (maxTime)
				time = maxTime - time;
			originTime += time;
			maxTime = -1;
		}
	}

	void PrintTime(int hour, int minutes, int seconds, int ms)
	{
		//AddDigit((hour - (hour % 10)) / 10);
		//AddDigit(hour % 10); // < 10 heures de jeu
		//AddSeparator();
		AddDigit((minutes - (minutes % 10)) / 10);
		AddDigit(minutes % 10);
		AddSeparator();
		AddDigit((seconds - (seconds % 10)) / 10);
		AddDigit(seconds % 10);
		AddSeparator();
		AddDigit((ms - (ms % 100)) / 100);
		AddDigit(((ms % 100) - (ms % 10)) / 10);
		//AddDigit((ms - (ms % 10)));
		
		for (int i = 0; i < numModels; ++i)
			Models[i]->Pos = Vector3f(-(float)((numLetters - 1) % 32) / (2*SIZEDIGIT), -(float)((numLetters - 1) / 32) / (2*SIZEDIGIT), 0) + Vector3f(0.0f,-0.25f,0);
	}

	void Render(Matrix4f view, Matrix4f proj, bool color = true)
	{
		for (int i = 0; i < numModels; ++i)
			Models[i]->Render(view, proj, color);
	}

	GLuint CreateShader(GLenum type, const GLchar* src)
	{
		GLuint shader = glCreateShader(type);

		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		GLint r;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &r);
		if (!r)
		{
			GLchar msg[1024];
			glGetShaderInfoLog(shader, sizeof(msg), 0, msg);
			if (msg[0]) {
				OVR_DEBUG_LOG(("Compiling shader failed: %s\n", msg));
			}
			return 0;
		}
		return shader;
	}

	void Init()
	{
		static const GLchar* VertexShaderSrc =
			"#version 150\n"
			"uniform mat4 matWVP;\n"
			"in      vec4 Position;\n"
			"in      vec4 Color;\n"
			"in      vec2 TexCoord;\n"
			"out     vec2 oTexCoord;\n"
			"out     vec4 oColor;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = matWVP * Position;\n"
			"   oTexCoord   = TexCoord*40;\n"
			"   oColor.rgb  = pow(Color.rgb, vec3(2.2));\n"   // convert from sRGB to linear
			"   oColor.a    = Color.a;\n"
			"}\n";

		static const char* FragmentShaderSrc =
			"#version 150\n"
			"uniform sampler2D Texture0;\n"
			"in      vec4      oColor;\n"
			"in      vec2      oTexCoord;\n"
			"out     vec4      FragColor;\n"
			"void main()\n"
			"{\n"
			"   FragColor = oColor * texture2D(Texture0, oTexCoord);\n"
			"}\n";

		GLuint    vshader = CreateShader(GL_VERTEX_SHADER, VertexShaderSrc);
		GLuint    fshader = CreateShader(GL_FRAGMENT_SHADER, FragmentShaderSrc);

		// Make textures

		ShaderFill * digits[DIGITS];

		static DWORD tex_digits[DIGITS * 8 * 8] = {
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,

			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			1,1,1,1,1,1,1,1,

			1,1,0,0,1,1,1,1,
			1,0,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,0,0,0,0,1,1,1,
			1,1,1,1,1,1,1,1,

			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,1,1,1,0,0,1,1,
			1,1,0,0,1,1,1,1,
			1,0,0,1,1,1,1,1,
			0,0,0,0,0,0,0,1,
			1,1,1,1,1,1,1,1,

			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,1,1,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			1,1,1,1,1,1,1,1,

			1,1,1,0,0,0,1,1,
			1,1,0,0,0,0,1,1,
			1,0,0,1,0,0,1,1,
			1,0,1,1,0,0,1,1,
			0,0,1,1,0,0,1,1,
			0,0,0,0,0,0,0,1,
			1,1,1,1,0,0,1,1,
			1,1,1,1,1,1,1,1,

			0,0,0,0,0,0,0,1,
			0,0,1,1,1,1,1,1,
			0,0,0,0,0,0,1,1,
			1,1,1,1,1,0,0,1,
			1,1,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			1,1,1,1,1,1,1,1,

			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,1,1,1,
			0,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			1,1,1,1,1,1,1,1,

			0,0,0,0,0,0,0,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,1,1,1,0,0,1,1,
			1,1,1,0,0,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,1,1,1,1,1,1,

			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			1,1,1,1,1,1,1,1,

			1,0,0,0,0,0,1,1,
			0,0,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,0,1,
			1,1,1,1,1,0,0,1,
			0,0,1,1,1,0,0,1,
			1,0,0,0,0,0,1,1,
			1,1,1,1,1,1,1,1,

			1,1,1,1,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,0,0,1,1,1,1,
			1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1
		};

		for (int k = 0; k < DIGITS * 8 * 8; k++)
			tex_digits[k] = (tex_digits[k] == 1) ? 0x50000000 : 0xffffffff;

		static unsigned char* pointeur = (unsigned char *)tex_digits;
		for (int k = 0; k < DIGITS; k++)
		{
			TextureBuffer * generated_texture = new TextureBuffer(false, Sizei(8, 8), 2, pointeur);
			digits[k] = new ShaderFill(vshader, fshader, generated_texture);
			pointeur += 8 * 8 * sizeof(DWORD);
		}


		glDeleteShader(vshader);
		glDeleteShader(fshader);

		// Construct geometry
		Model * m;
		for (int k = 0; k < DIGITS; k++)
		{
			m = new Model(Vector3f(0, 0, 0), digits[k]);
			m->AllocateBuffers();
			Add(m);
		}

	}

	Chrono() :
		numModels(0), numLetters(0), maxTime(-1), originTime(0)
	{
		Init();
	}
	void Release()
	{
		while (numModels-- > 0)
			delete Models[numModels];
	}
	~Chrono()
	{
		Release();
	}
};

#endif // Chrono_h
