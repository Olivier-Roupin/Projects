/************************************************************************************
 Filename    :   Flag.h
 Content     :   
 Created     :   November 6th, 2018
 Author      :   Olivier Roupin
 Copyright   :   
 *************************************************************************************/

#ifndef Flag_h
#define Flag_h

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

struct Flag
{
	int			Id;
	Vector3f	Path[13];
	Model *		Bloc;
	int   		Times[13];

	int Next()
	{
		if (Id < 12)
		{
			Id++;
			Bloc->Pos = Path[Id];
		}
		else if (Id == 12)
		{
			Id++;
			Bloc->numIndices = 0;
			Bloc->numVertices = 0;
		}
		return Times[Id];
	}

	bool Touch(Vector3f Pos)
	{
		return Pos.Distance(Path[Id]) < 0.6f;
	}

	void Render(Matrix4f view, Matrix4f proj, bool color = true)
	{
		Bloc->Render(view, proj, color);
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
			"   gl_Position = (matWVP * Position);\n"
			"   oTexCoord   = vec2(2*TexCoord.x,2*TexCoord.y/3);\n"
			"   oColor.rgb  = pow(Color.rgb, vec3(2.2));\n"   // convert from sRGB to linear
			"   oColor.a    = Color.a;\n"
			"}\n";

		//PROJET : utilisé pour passer en noir et blanc
		static const char* FragmentShaderSrc =
			"#version 150\n"
			"uniform sampler2D Texture0;\n"
			"uniform int       color;\n"
			"in      vec4      oColor;\n"
			"in      vec2      oTexCoord;\n"
			"out     vec4      FragColor;\n"
			"void main()\n"
			"{\n"
			"   float L     = dot(oColor, vec4(0.299,0.587,0.114,0));\n"
			"   vec4 eColor = color*oColor + (1-color)*vec4(L,L,L,oColor.a);\n"
			"   FragColor   = eColor * texture2D(Texture0, oTexCoord);\n"
			"}\n";

		GLuint    vshader = CreateShader(GL_VERTEX_SHADER, VertexShaderSrc);
		GLuint    fshader = CreateShader(GL_FRAGMENT_SHADER, FragmentShaderSrc);

		// Make textures
		ShaderFill * espace;
#define SIZEFLAG 16
#define HEIGHTFLAG 32
		static DWORD tex_espace[SIZEFLAG * SIZEFLAG];
		for (int i = 0; i < SIZEFLAG; ++i)
			for (int j = 0; j < SIZEFLAG; ++j)
			tex_espace[i*SIZEFLAG +j] = (i == 0 || i == SIZEFLAG - 1 || j == 0 || j == SIZEFLAG - 1 ) ? 0xff505050 : 0xffffffff;// blank

		TextureBuffer * generated_texture = new TextureBuffer(false, Sizei(SIZEFLAG, SIZEFLAG), 4, (unsigned char *)tex_espace);
		espace = new ShaderFill(vshader, fshader, generated_texture);

		glDeleteShader(vshader);
		glDeleteShader(fshader);

		// Construct geometry
		Bloc = new Model(Vector3f(0, 0, 0), espace);
		//Bloc->AddSolidColorBox(-0.25f, 0, -0.25f, 0.25f, 1.5f, 0.25f, 0xffff5050);
		Bloc->AddSolidColorBox(0, 0, 0, 0.5f, 1.5f, 0.5f, 0xffff5050);

		Vector3f temp[13] =
		{
			Vector3f(29, 0, 15),	//1 salle 1
			Vector3f(65, 0, 15),	//2 couloir 1
			Vector3f(68, 0, 20),	//3 couloir 1
			Vector3f(68, 0, 35),	//4 couloir 1
			Vector3f(92, 0, 35),	//5 couloir 1
			Vector3f(92, 2, -4),	//6 rampe 1
			Vector3f(118, 4, -26),	//7 colline
			Vector3f(70, 0, -26),	//8 grand creux
			Vector3f(70, 0, -90),	//9 petit creux
			Vector3f(92, 2, -101),	//10 rampe 2
			Vector3f(92, 0, -114),	//11 couloir 2
			Vector3f(110, 0, -114),	//12 couloir 2
			Vector3f(147, 0, -113),	//13 fin

		};
		for (int k = 0; k < 13; k++)
			Path[k] = temp[k] - Vector3f(0.25f, 0, 0.25f);

		Bloc->Pos = Path[0];
		Bloc->AllocateBuffers();

		int  temp3[13] =
		{
			30000,
			15000,
			05000,
			05000,
			05000,
			15000,
			10000,
			25000,
			30000,
			10000,
			05000,
			05000,
			15000
		};
		for (int k = 0; k < 13; k++)
			Times[k] = temp3[k];

	}

	int Time() const
	{
		if (Id >= 13)
			return -10000000;
		return Times[Id];
	}

	Flag() :
		Id(0)
	{
		Init();
	}
	void Release()
	{
		delete Bloc;
	}
	~Flag()
	{
		Release();
	}
};

#endif // Flag_h
