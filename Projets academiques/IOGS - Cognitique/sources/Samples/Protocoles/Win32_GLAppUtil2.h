/************************************************************************************
 Filename    :   Win32_GLAppUtil.h
 Content     :   OpenGL and Application/Window setup functionality for RoomTiny
 Created     :   October 20th, 2014
 Author      :   Tom Heath
 Copyright   :   Copyright 2014 Oculus, LLC. All Rights reserved.
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 *************************************************************************************/

#ifndef OVR_Win32_GLAppUtil_h
#define OVR_Win32_GLAppUtil_h

#include "GL/CAPI_GLE.h"
#include "Extras/OVR_Math.h"
#include "OVR_CAPI_GL.h"
#include <assert.h>

//PROJET
#include "Collisions.h"

using namespace OVR;

#ifndef VALIDATE
    #define VALIDATE(x, msg) if (!(x)) { MessageBoxA(NULL, (msg), "OculusRoomTiny", MB_ICONERROR | MB_OK); exit(-1); }
#endif

#ifndef OVR_DEBUG_LOG
    #define OVR_DEBUG_LOG(x)
#endif


//---------------------------------------------------------------------------------------
struct DepthBuffer
{
    GLuint        texId;

    DepthBuffer(Sizei size)
    {
        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        GLenum internalFormat = GL_DEPTH_COMPONENT24;
        GLenum type = GL_UNSIGNED_INT;
        if (GLE_ARB_depth_buffer_float)
        {
            internalFormat = GL_DEPTH_COMPONENT32F;
            type = GL_FLOAT;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.w, size.h, 0, GL_DEPTH_COMPONENT, type, NULL);
    }
    ~DepthBuffer()
    {
        if (texId)
        {
            glDeleteTextures(1, &texId);
            texId = 0;
        }
    }
};

//--------------------------------------------------------------------------
struct TextureBuffer
{
    GLuint              texId;
    GLuint              fboId;
    Sizei               texSize;

    TextureBuffer(bool rendertarget, Sizei size, int mipLevels, unsigned char * data) :
        texId(0),
        fboId(0),
        texSize(0, 0)
    {
        texSize = size;

        glGenTextures(1, &texId);
        glBindTexture(GL_TEXTURE_2D, texId);

        if (rendertarget)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, texSize.w, texSize.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        if (mipLevels > 1)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        if(rendertarget)
        {
            glGenFramebuffers(1, &fboId);
        }
    }

    ~TextureBuffer()
    {
        if (texId)
        {
            glDeleteTextures(1, &texId);
            texId = 0;
        }
        if (fboId)
        {
            glDeleteFramebuffers(1, &fboId);
            fboId = 0;
        }
    }

    Sizei GetSize() const
    {
        return texSize;
    }

    void SetAndClearRenderSurface(DepthBuffer* dbuffer)
    {
        VALIDATE(fboId, "Texture wasn't created as a render target");

        GLuint curTexId = texId;

        glBindFramebuffer(GL_FRAMEBUFFER, fboId);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, curTexId, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, dbuffer->texId, 0);

        glViewport(0, 0, texSize.w, texSize.h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_FRAMEBUFFER_SRGB);
    }

    void UnsetRenderSurface()
    {
        VALIDATE(fboId, "Texture wasn't created as a render target");

        glBindFramebuffer(GL_FRAMEBUFFER, fboId);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    }
};

//-------------------------------------------------------------------------------------------
struct OGL
{
    static const bool       UseDebugContext = false;

    HWND                    Window;
    HDC                     hDC;
    HGLRC                   WglContext;
    OVR::GLEContext         GLEContext;
    bool                    Running;
    bool                    Key[256];
    int                     WinSizeW;
    int                     WinSizeH;
    GLuint                  fboId;
    HINSTANCE               hInstance;

    static LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT Msg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        OGL *p = reinterpret_cast<OGL *>(GetWindowLongPtr(hWnd, 0));
        switch (Msg)
        {
        case WM_KEYDOWN:
            p->Key[wParam] = true;
            break;
        case WM_KEYUP:
            p->Key[wParam] = false;
            break;
        case WM_DESTROY:
            p->Running = false;
            break;
        default:
            return DefWindowProcW(hWnd, Msg, wParam, lParam);
        }
        if ((p->Key['Q'] && p->Key[VK_CONTROL]) || p->Key[VK_ESCAPE])
        {
            p->Running = false;
        }
        return 0;
    }

    OGL() :
        Window(nullptr),
        hDC(nullptr),
        WglContext(nullptr),
        GLEContext(),
        Running(false),
        WinSizeW(0),
        WinSizeH(0),
        fboId(0),
        hInstance(nullptr)
    {
		// Clear input
		for (int i = 0; i < sizeof(Key) / sizeof(Key[0]); ++i)
            Key[i] = false;
    }

    ~OGL()
    {
        ReleaseDevice();
        CloseWindow();
    }

    bool InitWindow(HINSTANCE hInst, LPCWSTR title)
    {
        hInstance = hInst;
        Running = true;

        WNDCLASSW wc;
        memset(&wc, 0, sizeof(wc));
        wc.style = CS_CLASSDC;
        wc.lpfnWndProc = WindowProc;
        wc.cbWndExtra = sizeof(struct OGL *);
        wc.hInstance = GetModuleHandleW(NULL);
        wc.lpszClassName = L"ORT";
        RegisterClassW(&wc);

        // adjust the window size and show at InitDevice time
        Window = CreateWindowW(wc.lpszClassName, title, WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, 0, 0, hInstance, 0);
        if (!Window) return false;

        SetWindowLongPtr(Window, 0, LONG_PTR(this));

        hDC = GetDC(Window);

        return true;
    }

    void CloseWindow()
    {
        if (Window)
        {
            if (hDC)
            {
                ReleaseDC(Window, hDC);
                hDC = nullptr;
            }
            DestroyWindow(Window);
            Window = nullptr;
            UnregisterClassW(L"OGL", hInstance);
        }
    }

    // Note: currently there is no way to get GL to use the passed pLuid
    bool InitDevice(int vpW, int vpH, const LUID* /*pLuid*/, bool windowed = true)
    {
        UNREFERENCED_PARAMETER(windowed);

        WinSizeW = vpW;
        WinSizeH = vpH;

        RECT size = { 0, 0, vpW, vpH };
        AdjustWindowRect(&size, WS_OVERLAPPEDWINDOW, false);
        const UINT flags = SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW;
        if (!SetWindowPos(Window, nullptr, 0, 0, size.right - size.left, size.bottom - size.top, flags))
            return false;

        PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARBFunc = nullptr;
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARBFunc = nullptr;
        {
            // First create a context for the purpose of getting access to wglChoosePixelFormatARB / wglCreateContextAttribsARB.
            PIXELFORMATDESCRIPTOR pfd;
            memset(&pfd, 0, sizeof(pfd));
            pfd.nSize = sizeof(pfd);
            pfd.nVersion = 1;
            pfd.iPixelType = PFD_TYPE_RGBA;
            pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
            pfd.cColorBits = 32;
            pfd.cDepthBits = 16;
            int pf = ChoosePixelFormat(hDC, &pfd);
            VALIDATE(pf, "Failed to choose pixel format.");

            VALIDATE(SetPixelFormat(hDC, pf, &pfd), "Failed to set pixel format.");

            HGLRC context = wglCreateContext(hDC);
            VALIDATE(context, "wglCreateContextfailed.");
            VALIDATE(wglMakeCurrent(hDC, context), "wglMakeCurrent failed.");

            wglChoosePixelFormatARBFunc = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
            wglCreateContextAttribsARBFunc = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
            assert(wglChoosePixelFormatARBFunc && wglCreateContextAttribsARBFunc);

            wglDeleteContext(context);
        }

        // Now create the real context that we will be using.
        int iAttributes[] =
        {
            // WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_COLOR_BITS_ARB, 32,
            WGL_DEPTH_BITS_ARB, 16,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
            0, 0
        };

        float fAttributes[] = { 0, 0 };
        int   pf = 0;
        UINT  numFormats = 0;

        VALIDATE(wglChoosePixelFormatARBFunc(hDC, iAttributes, fAttributes, 1, &pf, &numFormats),
            "wglChoosePixelFormatARBFunc failed.");

        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(pfd));
        VALIDATE(SetPixelFormat(hDC, pf, &pfd), "SetPixelFormat failed.");

        GLint attribs[16];
        int   attribCount = 0;
        if (UseDebugContext)
        {
            attribs[attribCount++] = WGL_CONTEXT_FLAGS_ARB;
            attribs[attribCount++] = WGL_CONTEXT_DEBUG_BIT_ARB;
        }

        attribs[attribCount] = 0;

        WglContext = wglCreateContextAttribsARBFunc(hDC, 0, attribs);
        VALIDATE(wglMakeCurrent(hDC, WglContext), "wglMakeCurrent failed.");

        OVR::GLEContext::SetCurrentContext(&GLEContext);
        GLEContext.Init();

        glGenFramebuffers(1, &fboId);

        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CW);
        glEnable(GL_CULL_FACE);

        if (UseDebugContext && GLE_ARB_debug_output)
        {
            glDebugMessageCallbackARB(DebugGLCallback, NULL);
            if (glGetError())
            {
                OVR_DEBUG_LOG(("glDebugMessageCallbackARB failed."));
            }

            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);

            // Explicitly disable notification severity output.
            glDebugMessageControlARB(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
        }

        return true;
    }

    bool HandleMessages(void)
    {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return Running;
    }

    void Run(bool (*MainLoop)(bool retryCreate))
    {
        while (HandleMessages())
        {
            // true => we'll attempt to retry for ovrError_DisplayLost
            if (!MainLoop(true))
                break;
            // Sleep a bit before retrying to reduce CPU load while the HMD is disconnected
            Sleep(10);
        }
    }

    void ReleaseDevice()
    {
        if (fboId)
        {
            glDeleteFramebuffers(1, &fboId);
            fboId = 0;
        }
        if (WglContext)
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(WglContext);
            WglContext = nullptr;
        }
        GLEContext.Shutdown();
    }

    static void GLAPIENTRY DebugGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        UNREFERENCED_PARAMETER(source);
        UNREFERENCED_PARAMETER(type);
        UNREFERENCED_PARAMETER(id);
        UNREFERENCED_PARAMETER(severity);
        UNREFERENCED_PARAMETER(length);
        UNREFERENCED_PARAMETER(message);
        UNREFERENCED_PARAMETER(userParam);
        OVR_DEBUG_LOG(("Message from OpenGL: %s\n", message));
    }
};

// Global OpenGL state
static OGL Platform;

//------------------------------------------------------------------------------
struct ShaderFill
{
    GLuint            program;
    TextureBuffer   * texture;

    ShaderFill(GLuint vertexShader, GLuint pixelShader, TextureBuffer* _texture)
    {
        texture = _texture;

        program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);

        glLinkProgram(program);

        glDetachShader(program, vertexShader);
        glDetachShader(program, pixelShader);

        GLint r;
        glGetProgramiv(program, GL_LINK_STATUS, &r);
        if (!r)
        {
            GLchar msg[1024];
            glGetProgramInfoLog(program, sizeof(msg), 0, msg);
            OVR_DEBUG_LOG(("Linking shaders failed: %s\n", msg));
        }
    }

    ~ShaderFill()
    {
        if (program)
        {
            glDeleteProgram(program);
            program = 0;
        }
        if (texture)
        {
            delete texture;
            texture = nullptr;
        }
    }
};

//----------------------------------------------------------------
struct VertexBuffer
{
    GLuint    buffer;

    VertexBuffer(void* vertices, size_t size)
    {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    ~VertexBuffer()
    {
        if (buffer)
        {
            glDeleteBuffers(1, &buffer);
            buffer = 0;
        }
    }
};

//----------------------------------------------------------------
struct IndexBuffer
{
    GLuint    buffer;

    IndexBuffer(void* indices, size_t size)
    {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }
    ~IndexBuffer()
    {
        if (buffer)
        {
            glDeleteBuffers(1, &buffer);
            buffer = 0;
        }
    }
};

//---------------------------------------------------------------------------
struct Model
{
    struct Vertex
    {
        Vector3f  Pos;
        DWORD     C;
        float     U, V;
    };

    Vector3f        Pos;
    Quatf           Rot;
    Matrix4f        Mat;
    int             numVertices, numIndices;
    Vertex          Vertices[2000]; // Note fixed maximum
    GLushort        Indices[2000];
    ShaderFill    * Fill;
    VertexBuffer  * vertexBuffer;
    IndexBuffer   * indexBuffer;

    Model(Vector3f pos, ShaderFill * fill) :
        numVertices(0),
        numIndices(0),
        Pos(pos),
        Rot(),
        Mat(),
        Fill(fill),
        vertexBuffer(nullptr),
        indexBuffer(nullptr)
    {}

    ~Model()
    {
        FreeBuffers();
    }

    Matrix4f& GetMatrix()
    {
        Mat = Matrix4f(Rot);
        Mat = Matrix4f::Translation(Pos) * Mat;
        return Mat;
    }

    void AddVertex(const Vertex& v) { Vertices[numVertices++] = v; }
    void AddIndex(GLushort a) { Indices[numIndices++] = a; }

    void AllocateBuffers()
    {
        vertexBuffer = new VertexBuffer(&Vertices[0], numVertices * sizeof(Vertices[0]));
        indexBuffer = new IndexBuffer(&Indices[0], numIndices * sizeof(Indices[0]));
    }

    void FreeBuffers()
    {
        delete vertexBuffer; vertexBuffer = nullptr;
        delete indexBuffer; indexBuffer = nullptr;
    }

    void AddSolidColorBox(float x1, float y1, float z1, float x2, float y2, float z2, DWORD c)
    {
        Vector3f Vert[][2] =
        {
            Vector3f(x1, y2, z1), Vector3f(z1, x1), Vector3f(x2, y2, z1), Vector3f(z1, x2),
            Vector3f(x2, y2, z2), Vector3f(z2, x2), Vector3f(x1, y2, z2), Vector3f(z2, x1),
            Vector3f(x1, y1, z1), Vector3f(z1, x1), Vector3f(x2, y1, z1), Vector3f(z1, x2),
            Vector3f(x2, y1, z2), Vector3f(z2, x2), Vector3f(x1, y1, z2), Vector3f(z2, x1),
            Vector3f(x1, y1, z2), Vector3f(z2, y1), Vector3f(x1, y1, z1), Vector3f(z1, y1),
            Vector3f(x1, y2, z1), Vector3f(z1, y2), Vector3f(x1, y2, z2), Vector3f(z2, y2),
            Vector3f(x2, y1, z2), Vector3f(z2, y1), Vector3f(x2, y1, z1), Vector3f(z1, y1),
            Vector3f(x2, y2, z1), Vector3f(z1, y2), Vector3f(x2, y2, z2), Vector3f(z2, y2),
            Vector3f(x1, y1, z1), Vector3f(x1, y1), Vector3f(x2, y1, z1), Vector3f(x2, y1),
            Vector3f(x2, y2, z1), Vector3f(x2, y2), Vector3f(x1, y2, z1), Vector3f(x1, y2),
            Vector3f(x1, y1, z2), Vector3f(x1, y1), Vector3f(x2, y1, z2), Vector3f(x2, y1),
            Vector3f(x2, y2, z2), Vector3f(x2, y2), Vector3f(x1, y2, z2), Vector3f(x1, y2)
        };

        GLushort CubeIndices[] =
        {
            0, 1, 3, 3, 1, 2,
            5, 4, 6, 6, 4, 7,
            8, 9, 11, 11, 9, 10,
            13, 12, 14, 14, 12, 15,
            16, 17, 19, 19, 17, 18,
            21, 20, 22, 22, 20, 23
        };

        for (int i = 0; i < sizeof(CubeIndices) / sizeof(CubeIndices[0]); ++i)
            AddIndex(CubeIndices[i] + GLushort(numVertices));

        // Generate a quad for each box face
        for (int v = 0; v < 6 * 4; v++)
        {
            // Make vertices, with some token lighting
            Vertex vvv; vvv.Pos = Vert[v][0]; vvv.U = Vert[v][1].x; vvv.V = Vert[v][1].y;
            float dist1 = (vvv.Pos - Vector3f(-2, 4, -2)).Length();
            float dist2 = (vvv.Pos - Vector3f(3, 4, -3)).Length();
            float dist3 = (vvv.Pos - Vector3f(-4, 3, 25)).Length();
            int   bri = rand() % 160;
            float B = ((c >> 16) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
            float G = ((c >>  8) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
            float R = ((c >>  0) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
            vvv.C = (c & 0xff000000) +
                ((R > 255 ? 255 : DWORD(R)) << 16) +
                ((G > 255 ? 255 : DWORD(G)) << 8) +
                 (B > 255 ? 255 : DWORD(B));
            AddVertex(vvv);
        }
    }

	//PROJET
	void AddSolidColorRamp(float x1, float y1, float z1, float x2, float y2, float z2, int r, DWORD c)
	{
		float y11(y2), y12(y2), y21(y2), y22(y2);

		switch (r)
		{
		case 0:
			y11 = y1; y21 = y1;
			break;
		case 1:
			y11 = y1; y12 = y1;
			break;
		case 2:
			y12 = y1; y22 = y1;
			break;
		case 3:
		default:
			y21 = y1; y22 = y1;
			break;
		}

		Vector3f Vert[][2] =
		{
			Vector3f(x1, y11, z1), Vector3f(z1, x1), Vector3f(x2, y21, z1), Vector3f(z1, x2),
			Vector3f(x2, y22, z2), Vector3f(z2, x2), Vector3f(x1, y12, z2), Vector3f(z2, x1),
			Vector3f(x1, y1, z1), Vector3f(z1, x1), Vector3f(x2, y1, z1), Vector3f(z1, x2),
			Vector3f(x2, y1, z2), Vector3f(z2, x2), Vector3f(x1, y1, z2), Vector3f(z2, x1),
			Vector3f(x1, y1, z2), Vector3f(z2, y1), Vector3f(x1, y1, z1), Vector3f(z1, y1),
			Vector3f(x1, y11, z1), Vector3f(z1, y2), Vector3f(x1, y12, z2), Vector3f(z2, y2),
			Vector3f(x2, y1, z2), Vector3f(z2, y1), Vector3f(x2, y1, z1), Vector3f(z1, y1),
			Vector3f(x2, y21, z1), Vector3f(z1, y2), Vector3f(x2, y22, z2), Vector3f(z2, y2),
			Vector3f(x1, y1, z1), Vector3f(x1, y1), Vector3f(x2, y1, z1), Vector3f(x2, y1),
			Vector3f(x2, y21, z1), Vector3f(x2, y2), Vector3f(x1, y11, z1), Vector3f(x1, y2),
			Vector3f(x1, y1, z2), Vector3f(x1, y1), Vector3f(x2, y1, z2), Vector3f(x2, y1),
			Vector3f(x2, y22, z2), Vector3f(x2, y2), Vector3f(x1, y12, z2), Vector3f(x1, y2)
		};

		GLushort CubeIndices[] =
		{
			0, 1, 3, 3, 1, 2,
			5, 4, 6, 6, 4, 7,
			8, 9, 11, 11, 9, 10,
			13, 12, 14, 14, 12, 15,
			16, 17, 19, 19, 17, 18,
			21, 20, 22, 22, 20, 23
		};

		for (int i = 0; i < sizeof(CubeIndices) / sizeof(CubeIndices[0]); ++i)
			AddIndex(CubeIndices[i] + GLushort(numVertices));

		// Generate a quad for each box face
		for (int v = 0; v < 6 * 4; v++)
		{
			// Make vertices, with some token lighting
			Vertex vvv; vvv.Pos = Vert[v][0]; vvv.U = Vert[v][1].x; vvv.V = Vert[v][1].y;
			float dist1 = (vvv.Pos - Vector3f(-2, 4, -2)).Length();
			float dist2 = (vvv.Pos - Vector3f(3, 4, -3)).Length();
			float dist3 = (vvv.Pos - Vector3f(-4, 3, 25)).Length();
			int   bri = rand() % 160;
			float B = ((c >> 16) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
			float G = ((c >> 8) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
			float R = ((c >> 0) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
			vvv.C = (c & 0xff000000) +
				((R > 255 ? 255 : DWORD(R)) << 16) +
				((G > 255 ? 255 : DWORD(G)) << 8) +
				 (B > 255 ? 255 : DWORD(B));
			AddVertex(vvv);
		}
	}

	//PROJET
	void AddSolidColorCorner(float x1, float y1, float z1, float x2, float y2, float z2, int r, DWORD c)
	{
		float y11(y2), y12(y2), y21(y2), y22(y2);
		GLushort m(r == 0 || r == 2);

		switch (r)
		{
		case 0:
			y11 = y1; y21 = y1; y12 = y1;
			break;
		case 1:
			y11 = y1; y12 = y1; y22 = y1;
			break;
		case 2:
			y12 = y1; y22 = y1; y21 = y1;
			break;
		case 3:
		default:
			y21 = y1; y22 = y1; y11 = y1;
			break;
		}

		Vector3f Vert[][2] =
		{
			Vector3f(x1, y11, z1), Vector3f(z1, x1), Vector3f(x2, y21, z1), Vector3f(z1, x2),
			Vector3f(x2, y22, z2), Vector3f(z2, x2), Vector3f(x1, y12, z2), Vector3f(z2, x1),
			Vector3f(x1, y1, z1), Vector3f(z1, x1), Vector3f(x2, y1, z1), Vector3f(z1, x2),
			Vector3f(x2, y1, z2), Vector3f(z2, x2), Vector3f(x1, y1, z2), Vector3f(z2, x1),
			Vector3f(x1, y1, z2), Vector3f(z2, y1), Vector3f(x1, y1, z1), Vector3f(z1, y1),
			Vector3f(x1, y11, z1), Vector3f(z1, y2), Vector3f(x1, y12, z2), Vector3f(z2, y2),
			Vector3f(x2, y1, z2), Vector3f(z2, y1), Vector3f(x2, y1, z1), Vector3f(z1, y1),
			Vector3f(x2, y21, z1), Vector3f(z1, y2), Vector3f(x2, y22, z2), Vector3f(z2, y2),
			Vector3f(x1, y1, z1), Vector3f(x1, y1), Vector3f(x2, y1, z1), Vector3f(x2, y1),
			Vector3f(x2, y21, z1), Vector3f(x2, y2), Vector3f(x1, y11, z1), Vector3f(x1, y2),
			Vector3f(x1, y1, z2), Vector3f(x1, y1), Vector3f(x2, y1, z2), Vector3f(x2, y1),
			Vector3f(x2, y22, z2), Vector3f(x2, y2), Vector3f(x1, y12, z2), Vector3f(x1, y2)
		};

		GLushort CubeIndices[] =
		{
			0, 1, 3 - m, 3, 1 - m, 2,
			5, 4, 6 - m, 6, 4 - m, 7,
			8, 9, 11 - m, 11, 9 - m, 10,
			13, 12, 14 - m, 14, 12 - m, 15,
			16, 17, 19 - m, 19, 17 - m, 18,
			21, 20, 22 - m, 22, 20 - m, 23
		};

		for (int i = 0; i < sizeof(CubeIndices) / sizeof(CubeIndices[0]); ++i)
			AddIndex(CubeIndices[i] + GLushort(numVertices));

		// Generate a quad for each box face
		for (int v = 0; v < 6 * 4; v++)
		{
			// Make vertices, with some token lighting
			Vertex vvv; vvv.Pos = Vert[v][0]; vvv.U = Vert[v][1].x; vvv.V = Vert[v][1].y;
			float dist1 = (vvv.Pos - Vector3f(-2, 4, -2)).Length();
			float dist2 = (vvv.Pos - Vector3f(3, 4, -3)).Length();
			float dist3 = (vvv.Pos - Vector3f(-4, 3, 25)).Length();
			int   bri = rand() % 160;
			float B = ((c >> 16) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
			float G = ((c >> 8) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
			float R = ((c >> 0) & 0xff) * (bri + 192.0f * (0.65f + 8 / dist1 + 1 / dist2 + 4 / dist3)) / 255.0f;
			vvv.C = (c & 0xff000000) +
				((R > 255 ? 255 : DWORD(R)) << 16) +
				((G > 255 ? 255 : DWORD(G)) << 8) +
				 (B > 255 ? 255 : DWORD(B));
			AddVertex(vvv);
		}
	}

    void Render(Matrix4f view, Matrix4f proj)
    {
        Matrix4f combined = proj * view * GetMatrix();

        glUseProgram(Fill->program);
        glUniform1i(glGetUniformLocation(Fill->program, "Texture0"), 0);
        glUniformMatrix4fv(glGetUniformLocation(Fill->program, "matWVP"), 1, GL_TRUE, (FLOAT*)&combined);

		glUniform1i(glGetUniformLocation(Fill->program, "color"), 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Fill->texture->texId);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->buffer);

        GLuint posLoc = glGetAttribLocation(Fill->program, "Position");
        GLuint colorLoc = glGetAttribLocation(Fill->program, "Color");
        GLuint uvLoc = glGetAttribLocation(Fill->program, "TexCoord");

        glEnableVertexAttribArray(posLoc);
        glEnableVertexAttribArray(colorLoc);
        glEnableVertexAttribArray(uvLoc);

        glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OVR_OFFSETOF(Vertex, Pos));
        glVertexAttribPointer(colorLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)OVR_OFFSETOF(Vertex, C));
        glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OVR_OFFSETOF(Vertex, U));

        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

        glDisableVertexAttribArray(posLoc);
        glDisableVertexAttribArray(colorLoc);
        glDisableVertexAttribArray(uvLoc);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glUseProgram(0);
    }

	//PROJET : utilisé pour passer en noir et blanc
	void Render(Matrix4f view, Matrix4f proj, bool color)
	{
		Matrix4f combined = proj * view * GetMatrix();

		glUseProgram(Fill->program);
		glUniform1i(glGetUniformLocation(Fill->program, "Texture0"), 0);
		glUniformMatrix4fv(glGetUniformLocation(Fill->program, "matWVP"), 1, GL_TRUE, (FLOAT*)&combined);

		glUniform1i(glGetUniformLocation(Fill->program, "color"), color);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Fill->texture->texId);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->buffer);

		GLuint posLoc = glGetAttribLocation(Fill->program, "Position");
		GLuint colorLoc = glGetAttribLocation(Fill->program, "Color");
		GLuint uvLoc = glGetAttribLocation(Fill->program, "TexCoord");

		glEnableVertexAttribArray(posLoc);
		glEnableVertexAttribArray(colorLoc);
		glEnableVertexAttribArray(uvLoc);

		glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OVR_OFFSETOF(Vertex, Pos));
		glVertexAttribPointer(colorLoc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)OVR_OFFSETOF(Vertex, C));
		glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)OVR_OFFSETOF(Vertex, U));

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, NULL);

		glDisableVertexAttribArray(posLoc);
		glDisableVertexAttribArray(colorLoc);
		glDisableVertexAttribArray(uvLoc);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glUseProgram(0);
	}

};

//------------------------------------------------------------------------- 
struct Scene
{
    int     numModels;
    Model * Models[10];
#define FLOOR (2+7+4+9+4+1)
#define WALLS 26
	Vector3f Floor[4 * FLOOR];
	Vector2f Walls[2 * WALLS];

    void    Add(Model * n)
    {
        Models[numModels++] = n;
    }

    void Render(Matrix4f view, Matrix4f proj)
    {
        for (int i = 0; i < numModels; ++i)
            Models[i]->Render(view, proj);
    }

	//PROJET
	void Render(Matrix4f view, Matrix4f proj, bool color)
	{
		for (int i = 0; i < numModels; ++i)
			Models[i]->Render(view, proj, color);
	}

	//PROJET
	Vector3f Impact(Vector3f& PosP, Vector3f PosO, Vector3f PosF) // On ne gère encore que 2 murs simultanément
	{
		Vector2f A, B, AB; // Mur étudié
		Vector2f C, D, CD; // Mur en mémoire
		Vector2f P, O, T, F, G, OT; // Précédent, Orginal, Temporaire, Finale, Finale2
		bool wall(false);
		P.x = PosP.x; P.y = PosP.z;
		O.x = PosO.x; O.y = PosO.z;
		T.x = PosF.x; T.y = PosF.z;
		OT = T - O;
		F = T;
		for (int k = 0; k < WALLS; k++)
		{
			A = Walls[2 * k];
			B = Walls[2 * k + 1];
			AB = B - A;
			if (OT.y*AB.x < OT.x*AB.y) // Le déplacement et la résistance du mur sont opposées
			{
				if (CollisionSegment(A, B, T, 0.75f)) // Le cercle du héros coupe le mur
				{
					if (wall == false) // C'est le premier mur coupé
					{
						F = Projeter(A, B, T);
						C = A; D = B; CD = AB;
						wall = true;
					}
					else // Ce n'est pas le premier mur coupé
					{
						// Identifier chaque mur
						if (A.DistanceSq(D) < C.DistanceSq(B)) // AB est "1" et CD est "2", on compare "1" à la normale de "2"
						{
							// Déterminer s'ils se contrarient
							if (AB.x*CD.y < AB.y*CD.x) // Les murs sont en accord
							{
								F = Projeter(A, B, F); // on ne change pas de mur référent et on projette
							}
							else // Les murs se contrarient
							{
								G = Projeter(A, B, T);
								// Déterminer lequel est prioritaire : par continuité de la vitesse
								if ((O - P).Distance(F - O) >(O - P).Distance(G - O))
								{
									F = G;
									C = A; D = B; CD = AB;
								}
							}
						}
						else // CD est "1" et AB est "2"
						{
							// Determiner s'ils se contrarient
							if (CD.x*AB.y < CD.y*AB.x) // Les murs sont en accord
							{
								F = Projeter(A, B, F); // on ne change pas de mur référent et on projette
							}
							else // Les murs se contrarient
							{
								G = Projeter(A, B, T);
								// Déterminer lequel est prioritaire : par continuité de la vitesse
								if ((O - P).Distance(F - O) >(O - P).Distance(G - O))
								{
									F = G;
									C = A; D = B; CD = AB;
								}
							}
						}
					}
				}
			}
		}
		PosP = PosO;
		PosF.x = F.x;
		PosF.z = F.y;
		return PosF;
	}

	float Hauteur(Vector3f Pos)
	{
		float hauteur(0);
		Vector3f A, B, C, D;
		float a, b, c, d, n;
		for (int k = 0; k < FLOOR; k++)
		{
			A = Floor[4 * k];
			B = Floor[4 * k + 1];
			C = Floor[4 * k + 2];
			D = Floor[4 * k + 3];
			if (Pos.x >= A.x && Pos.z >= A.z && Pos.x <= C.x && Pos.z <= C.z)
			{
				n = (C.x - A.x)*(C.z - A.z);
				a = (C.x - Pos.x)*(C.z - Pos.z) / n;
				b = (Pos.x - A.x)*(C.z - Pos.z) / n;
				c = (Pos.x - A.x)*(Pos.z - A.z) / n;
				d = (C.x - Pos.x)*(Pos.z - A.z) / n;
				if (hauteur < a*A.y + b * B.y + c * C.y + d * D.y)
					hauteur = a * A.y + b * B.y + c * C.y + d * D.y;
			}
		}
		return hauteur;
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

    void Init(int includeIntensiveGPUobject)
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
            "   oTexCoord   = TexCoord;\n"
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
        ShaderFill * grid_material[5];
        for (int k = 0; k < 4; ++k)
        {
            static DWORD tex_pixels[256 * 256];
            for (int j = 0; j < 256; ++j)
            {
                for (int i = 0; i < 256; ++i)
                {
                    if (k == 0) tex_pixels[j * 256 + i] = (((i >> 7) ^ (j >> 7)) & 1) ? 0xffb4b4b4 : 0xff505050;// floor
                    if (k == 1) tex_pixels[j * 256 + i] = (((j / 4 & 15) == 0) || (((i / 4 & 15) == 0) && ((((i / 4 & 31) == 0) ^ ((j / 4 >> 4) & 1)) == 0)))
                        ? 0xff3c3c3c : 0xffb4b4b4;// wall
                    //if (k == 2) tex_pixels[j * 256 + i] = (i / 4 == 0 || j / 4 == 0) ? 0xff505050 : 0xffb4b4b4;// ceiling
					//PROJET
					if (k == 2) tex_pixels[j * 256 + i] = (i / 4 == 0 || j / 4 == 0) ? 0xffb4b4b4 : 0xff505050;// ceiling
                    if (k == 3) tex_pixels[j * 256 + i] = 0xffffffff;// blank
                }
            }
            TextureBuffer * generated_texture = new TextureBuffer(false, Sizei(256, 256), 4, (unsigned char *)tex_pixels);
            grid_material[k] = new ShaderFill(vshader, fshader, generated_texture);
        }

		//PROJET
		static DWORD tex_pixels[2048 * 2048];
		for (int j = 0; j < 2048; ++j)
		{
			for (int i = 0; i < 2048; ++i)
				tex_pixels[j * 2048 + i] = ((i - 1023)*(i - 1023) + (j - 1023)*(j - 1023) > 700000) ? 0xffffffff : \
				((i - 1023)*(i - 1023) + (j - 1023)*(j - 1023) > 650000) ? 0xbfffffff : \
				((i - 1023)*(i - 1023) + (j - 1023)*(j - 1023) > 600000) ? 0x80ffffff : \
				((i - 1023)*(i - 1023) + (j - 1023)*(j - 1023) > 550000) ? 0x40ffffff : \
				((i - 1023)*(i - 1023) + (j - 1023)*(j - 1023) > 500000) ? 0x20ffffff : 0x00ffffff;// blank
		}
		TextureBuffer * generated_texture = new TextureBuffer(false, Sizei(2048, 2048), 4, (unsigned char *)tex_pixels);
		grid_material[4] = new ShaderFill(vshader, fshader, generated_texture);

        glDeleteShader(vshader);
        glDeleteShader(fshader);

		/*
        // Construct geometry
        Model * m = new Model(Vector3f(0, 0, 0), grid_material[2]);  // Moving box
        m->AddSolidColorBox(0, 0, 0, +1.0f, +1.0f, 1.0f, 0xff404040);
        m->AllocateBuffers();
        Add(m);

        m = new Model(Vector3f(0, 0, 0), grid_material[1]);  // Walls
        m->AddSolidColorBox(-10.1f, 0.0f, -20.0f, -10.0f, 4.0f, 20.0f, 0xff808080); // Left Wall
        m->AddSolidColorBox(-10.0f, -0.1f, -20.1f, 10.0f, 4.0f, -20.0f, 0xff808080); // Back Wall
        m->AddSolidColorBox(10.0f, -0.1f, -20.0f, 10.1f, 4.0f, 20.0f, 0xff808080); // Right Wall
        m->AllocateBuffers();
        Add(m);

        if (includeIntensiveGPUobject)
        {
            m = new Model(Vector3f(0, 0, 0), grid_material[0]);  // Floors
            for (float depth = 0.0f; depth > -3.0f; depth -= 0.1f)
                m->AddSolidColorBox(9.0f, 0.5f, -depth, -9.0f, 3.5f, -depth, 0x10ff80ff); // Partition
            m->AllocateBuffers();
            Add(m);
        }

        m = new Model(Vector3f(0, 0, 0), grid_material[0]);  // Floors
        m->AddSolidColorBox(-10.0f, -0.1f, -20.0f, 10.0f, 0.0f, 20.1f, 0xff808080); // Main floor
        m->AddSolidColorBox(-15.0f, -6.1f, 18.0f, 15.0f, -6.0f, 30.0f, 0xff808080); // Bottom floor
        m->AllocateBuffers();
        Add(m);

        m = new Model(Vector3f(0, 0, 0), grid_material[2]);  // Ceiling
        m->AddSolidColorBox(-10.0f, 4.0f, -20.0f, 10.0f, 4.1f, 20.1f, 0xff808080);
        m->AllocateBuffers();
        Add(m);

        m = new Model(Vector3f(0, 0, 0), grid_material[3]);  // Fixtures & furniture
        m->AddSolidColorBox(9.5f, 0.75f, 3.0f, 10.1f, 2.5f, 3.1f, 0xff383838);   // Right side shelf// Verticals
        m->AddSolidColorBox(9.5f, 0.95f, 3.7f, 10.1f, 2.75f, 3.8f, 0xff383838);   // Right side shelf
        m->AddSolidColorBox(9.55f, 1.20f, 2.5f, 10.1f, 1.30f, 3.75f, 0xff383838); // Right side shelf// Horizontals
        m->AddSolidColorBox(9.55f, 2.00f, 3.05f, 10.1f, 2.10f, 4.2f, 0xff383838); // Right side shelf
        m->AddSolidColorBox(5.0f, 1.1f, 20.0f, 10.0f, 1.2f, 20.1f, 0xff383838);   // Right railing   
        m->AddSolidColorBox(-10.0f, 1.1f, 20.0f, -5.0f, 1.2f, 20.1f, 0xff383838);   // Left railing  
        for (float f = 5.0f; f <= 9.0f; f += 1.0f)
        {
            m->AddSolidColorBox(f, 0.0f, 20.0f, f + 0.1f, 1.1f, 20.1f, 0xff505050);// Left Bars
            m->AddSolidColorBox(-f, 1.1f, 20.0f, -f - 0.1f, 0.0f, 20.1f, 0xff505050);// Right Bars
        }
        m->AddSolidColorBox(-1.8f, 0.8f, 1.0f, 0.0f, 0.7f, 0.0f, 0xff505000); // Table
        m->AddSolidColorBox(-1.8f, 0.0f, 0.0f, -1.7f, 0.7f, 0.1f, 0xff505000); // Table Leg 
        m->AddSolidColorBox(-1.8f, 0.7f, 1.0f, -1.7f, 0.0f, 0.9f, 0xff505000); // Table Leg 
        m->AddSolidColorBox(0.0f, 0.0f, 1.0f, -0.1f, 0.7f, 0.9f, 0xff505000); // Table Leg 
        m->AddSolidColorBox(0.0f, 0.7f, 0.0f, -0.1f, 0.0f, 0.1f, 0xff505000); // Table Leg 
        m->AddSolidColorBox(-1.4f, 0.5f, -1.1f, -0.8f, 0.55f, -0.5f, 0xff202050); // Chair Set
        m->AddSolidColorBox(-1.4f, 0.0f, -1.1f, -1.34f, 1.0f, -1.04f, 0xff202050); // Chair Leg 1
        m->AddSolidColorBox(-1.4f, 0.5f, -0.5f, -1.34f, 0.0f, -0.56f, 0xff202050); // Chair Leg 2
        m->AddSolidColorBox(-0.8f, 0.0f, -0.5f, -0.86f, 0.5f, -0.56f, 0xff202050); // Chair Leg 2
        m->AddSolidColorBox(-0.8f, 1.0f, -1.1f, -0.86f, 0.0f, -1.04f, 0xff202050); // Chair Leg 2
        m->AddSolidColorBox(-1.4f, 0.97f, -1.05f, -0.8f, 0.92f, -1.10f, 0xff202050); // Chair Back high bar

        for (float f = 3.0f; f <= 6.6f; f += 0.4f)
            m->AddSolidColorBox(-3, 0.0f, f, -2.9f, 1.3f, f + 0.1f, 0xff404040); // Posts

        m->AllocateBuffers();
        Add(m);
		*/
		// Construct geometry
		Model * m = new Model(Vector3f(0, 0, 0), grid_material[3]);  // Moving box
		m->AddSolidColorBox(0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 0.0f, 0x00000000);
		m->AllocateBuffers();
		Add(m); //Model[0]

		m = new Model(Vector3f(0, 0, 0), grid_material[1]);  // Walls
															 // Main floor 1
		m->AddSolidColorBox(-0.1f, 0.0f, 0.0f, 0.0f, 8.0f, 30.0f, 0xff808080);
		m->AddSolidColorBox(0.0f, 0.0f, 30.0f, 30.0f, 8.0f, 30.1f, 0xff808080);
		m->AddSolidColorBox(-0.1f, 0.0f, 0.0f, 30.0f, 8.0f, 0.0f, 0xff808080);
		//porte
		m->AddSolidColorBox(30.0f, 0.0f, 0.0f, 30.1f, 8.0f, 13.0f, 0xff808080);
		m->AddSolidColorBox(30.0f, 0.0f, 17.0f, 30.1f, 8.0f, 30.0f, 0xff808080);

		// Main floor 2
		m->AddSolidColorBox(39.9f, 0.0f, -102.0f, 40.0f, 8.0f, -2.0f, 0xff808080);
		m->AddSolidColorBox(40.0f, 0.0f, -2.0f, 90.0f, 8.0f, -1.9f, 0xff808080);
		//porte
		m->AddSolidColorBox(94.0f, 0.0f, -2.0f, 144.0f, 8.0f, -1.9f, 0xff808080);
		m->AddSolidColorBox(40.0f, 0.0f, -102.1f, 90.0f, 8.0f, -102.0f, 0xff808080);
		//porte
		m->AddSolidColorBox(94.0f, 0.0f, -102.1f, 144.0f, 8.0f, -102.0f, 0xff808080);
		m->AddSolidColorBox(144.0f, 0.0f, -102.0f, 144.1f, 8.0f, -2.0f, 0xff808080);

		// Couloir 1
		m->AddSolidColorBox(30.1f, 0.0f, 13.0f, 70.1f, 8.0f, 13.0f, 0xff808080);
		m->AddSolidColorBox(30.1f, 0.0f, 17.0f, 66.0f, 8.0f, 17.1f, 0xff808080);

		m->AddSolidColorBox(70.0f, 0.0f, 13.0f, 70.1f, 8.0f, 33.0f, 0xff808080);
		m->AddSolidColorBox(66.0f, 0.0f, 17.0f, 66.1f, 8.0f, 37.0f, 0xff808080);

		m->AddSolidColorBox(66.0f, 0.0f, 37.0f, 94.1f, 8.0f, 37.0f, 0xff808080);
		m->AddSolidColorBox(70.1f, 0.0f, 33.0f, 90.0f, 8.0f, 33.0f, 0xff808080);

		m->AddSolidColorBox(93.9f, 0.0f, -2.0f, 94.f, 8.0f, 37.0f, 0xff808080);
		m->AddSolidColorBox(90.0f, 0.0f, -2.0f, 90.1f, 8.0f, 33.0f, 0xff808080);

		// Couloir 2
		m->AddSolidColorBox(90.0f, 0.0f, -116.0f, 90.1f, 8.0f, -102.0f, 0xff808080);
		m->AddSolidColorBox(93.9f, 0.0f, -112.0f, 94.0f, 8.0f, -102.0f, 0xff808080);
		m->AddSolidColorBox(90.0f, 0.0f, -116.1f, 149.0f, 8.0f, -116.0f, 0xff808080);
		m->AddSolidColorBox(93.9f, 0.0f, -112.1f, 139.1f, 8.0f, -112.0f, 0xff808080);

		// Main floor 3
		m->AddSolidColorBox(139.0f, 0.0f, -112.0f, 139.1f, 8.0f, -106.0f, 0xff808080);
		m->AddSolidColorBox(139.0f, 0.0f, -106.1f, 149.0f, 8.0f, -106.0f, 0xff808080);
		m->AddSolidColorBox(149.0f, 0.0f, -116.0f, 149.1f, 8.0f, -106.0f, 0xff808080);

		m->AllocateBuffers();
		Add(m);//Model[1]

		Vector2f temp2[2 * 26] =
		{
			// Main floor 1
			Vector2f(0.0f, 30.0f), Vector2f(0.0f, 0.0f),
			Vector2f(30.0f, 30.0f), Vector2f(0.0f, 30.0f),
			Vector2f(0.0f, 0.0f), Vector2f(30.0f, 0.0f),
			// porte
			Vector2f(30.0f, 0.0f), Vector2f(30.0f, 13.0f),
			Vector2f(30.0f, 17.0f), Vector2f(30.0f, 30.0f),

			// Main floor 2
			Vector2f(40.0f, -2.0f), Vector2f(40.0f, -102.0f),
			Vector2f(144.0f, -102.0f), Vector2f(144.0f, -2.0f),
			// porte 1
			Vector2f(90.0f, -2.0f), Vector2f(40.0f, -2.0f),
			Vector2f(144.0f, -2.0f), Vector2f(94.0f, -2.0f),
			// porte 2
			Vector2f(40.0f, -102.0f), Vector2f(90.0f, -102.0f),
			Vector2f(94.0f, -102.0f), Vector2f(144.0f, -102.0f),

			// Couloir 1
			Vector2f(30.0f, 13.0f), Vector2f(70.0f, 13.0f),
			Vector2f(66.0f, 17.0f), Vector2f(30.0f, 17.0f),

			Vector2f(70.0f, 13.0f), Vector2f(70.0f, 33.0f),
			Vector2f(66.0f, 37.0f), Vector2f(66.0f, 17.0f),

			Vector2f(70.0f, 33.0f), Vector2f(90.0f, 33.0f),
			Vector2f(94.0f, 37.0f), Vector2f(66.0f, 37.0f),

			Vector2f(94.0f, -2.0f), Vector2f(94.0f, 37.0f),
			Vector2f(90.0f, 33.0f), Vector2f(90.0f, -2.0f),

			// Couloir 2
			Vector2f(90.0f, -102.0f), Vector2f(90.0f, -116.0f),
			Vector2f(94.0f, -112.0f), Vector2f(94.0f, -102.0f),

			Vector2f(139.0f, -112.0f), Vector2f(94.0f, -112.0f),
			Vector2f(90.0f, -116.0f), Vector2f(149.0f, -116.0f),

			// Main floor 3
			Vector2f(139.0f, -106.0f), Vector2f(139.0f, -112.0f),
			Vector2f(149.0f, -106.0f), Vector2f(139.0f, -106.0f),
			Vector2f(149.0f, -116.0f), Vector2f(149.0f, -106.0f),
		};

		for (int k = 0; k < 2 * 26; k++)
			Walls[k] = temp2[k];

		//sols
		m = new Model(Vector3f(0, 0, 0), grid_material[2]);  // Floors
		m->AddSolidColorBox(0.0f, -0.1f, 0.0f, 30.0f, 0.0f, 30.0f, 0xff000080); // Main floor 1
		m->AddSolidColorBox(30.0f, -0.1f, 13.0f, 66.0f, 0.0f, 17.0f, 0xff000080); // Hallway 1
		m->AddSolidColorBox(66.0f, -0.1f, 13.0f, 70.0f, 0.0f, 37.0f, 0xff000080); // Hallway 2
		m->AddSolidColorBox(70.0f, -0.1f, 33.0f, 90.0f, 0.0f, 37.0f, 0xff000080); // Hallway 3
		m->AddSolidColorBox(90.0f, -0.1f, -2.0f, 94.0f, 0.0f, 37.0f, 0xff000080); // Hallway 4
																				  // Rampe 1
		m->AddSolidColorRamp(90.1f, 0.0f, -2.0f, 93.9f, 2.0f, 33.0f, 2, 0xff808080);
		// Main floor 2
		m->AddSolidColorBox(40.0f, -0.1f, -102.0f, 144.0f, 0.0f, -2.0f, 0xff000080); // base
		m->AddSolidColorBox(40.0f, 0.0f, -6.0f, 144.0f, 2.0f, -2.0f, 0xff000080);
		m->AddSolidColorBox(40.0f, 0.0f, -46.0f, 50.0f, 2.0f, -6.0f, 0xff000080);
		m->AddSolidColorBox(40.0f, 0.0f, -100.0f, 60.0f, 2.0f, -46.0f, 0xff000080);
		m->AddSolidColorBox(40.0f, 0.0f, -102.0f, 144.0f, 2.0f, -100.0f, 0xff000080);
		m->AddSolidColorBox(60.0f, 0.0f, -80.0f, 80.0f, 2.0f, -46.0f, 0xff000080);
		m->AddSolidColorBox(80.0f, 0.0f, -100.0f, 144.0f, 2.0f, -46.0f, 0xff000080);
		m->AddSolidColorBox(90.0f, 0.0f, -46.0f, 144.0f, 2.0f, -6.0f, 0xff000080);
		// Creux 1
		m->AddSolidColorRamp(50.0f, 0.0f, -16.0f, 90.0f, 2.0f, -6.0f, 0, 0xff808080);
		m->AddSolidColorRamp(80.0f, 0.0f, -46.0f, 90.0f, 2.0f, -6.0f, 1, 0xff808080);
		m->AddSolidColorRamp(50.0f, 0.0f, -46.0f, 90.0f, 2.0f, -36.0f, 2, 0xff808080);
		m->AddSolidColorRamp(50.0f, 0.0f, -46.0f, 60.0f, 2.0f, -6.0f, 3, 0xff808080);
		// Colline 1
		m->AddSolidColorRamp(110.0f, 2.0f, -40.0f, 125.0f, 4.0f, -34.0f, 0, 0xff808080);
		m->AddSolidColorRamp(104.0f, 2.0f, -34.0f, 110.0f, 4.0f, -19.0f, 1, 0xff808080);
		m->AddSolidColorRamp(110.0f, 2.0f, -19.0f, 125.0f, 4.0f, -13.0f, 2, 0xff808080);
		m->AddSolidColorRamp(125.0f, 2.0f, -34.0f, 131.0f, 4.0f, -19.0f, 3, 0xff808080);
		m->AddSolidColorCorner(104.0f, 2.0f, -40.0f, 110.0f, 4.0f, -34.0f, 0, 0xff808080);
		m->AddSolidColorCorner(104.0f, 2.0f, -19.0f, 110.0f, 4.0f, -13.0f, 1, 0xff808080);
		m->AddSolidColorCorner(125.0f, 2.0f, -19.0f, 131.0f, 4.0f, -13.0f, 2, 0xff808080);
		m->AddSolidColorCorner(125.0f, 2.0f, -40.0f, 131.0f, 4.0f, -34.0f, 3, 0xff808080);
		m->AddSolidColorBox(110.0f, 2.0f, -34.0f, 125.0f, 4.0f, -19.0f, 0xff808080);
		// Creux 2
		m->AddSolidColorRamp(60.0f, 0.0f, -85.0f, 80.0f, 2.0f, -80.0f, 0, 0xff808080);
		m->AddSolidColorRamp(75.0f, 0.0f, -100.0f, 80.0f, 2.0f, -80.0f, 1, 0xff808080);
		m->AddSolidColorRamp(60.0f, 0.0f, -100.0f, 80.0f, 2.0f, -95.0f, 2, 0xff808080);
		m->AddSolidColorRamp(60.0f, 0.0f, -100.0f, 65.0f, 2.0f, -80.0f, 3, 0xff808080);
		// Rampe 2
		m->AddSolidColorRamp(90.0f, 0.0f, -112.0f, 94.0f, 2.0f, -102.0f, 0, 0xff808080);

		m->AddSolidColorBox(90.0f, -0.1f, -116.0f, 94.0f, 0.0f, -102.0f, 0xff000080); // Hallway 5
		m->AddSolidColorBox(94.0f, -0.1f, -116.0f, 139.0f, 0.0f, -112.0f, 0xff000080); // Hallway 6
		m->AddSolidColorBox(139.0f, -0.1f, -116.0f, 149.0f, 0.0f, -106.0f, 0xff000080); // Main floor 3

		m->AllocateBuffers();
		Add(m);//Model[2]

		Vector3f temp[4 * FLOOR] =
		{
			// Main floor
			Vector3f(0.0f, 0.0f, -116.0f),	  Vector3f(149.0f, 0.0f, -116.0f), Vector3f(149.0f, 0.0f, 37.0f),	  Vector3f(0.0f, 0.0f, 37.0f),
			// Rampe 1
			Vector3f(90.0f, 2.0f, -2.0f),	  Vector3f(94.0f, 2.0f, -2.0f),	   Vector3f(94.0f, 0.0f, 33.0f),	  Vector3f(90.0f, 0.0f, 33.0f),
			// Main floor 2
			Vector3f(40.0f, 2.0f, -6.0f),	Vector3f(144.0f, 2.0f, -6.0f),		Vector3f(144.0f, 2.0f, -2.0f),		Vector3f(40.0f, 2.0f, -2.0f),
			Vector3f(40.0f, 2.0f, -46.0f),	Vector3f(50.0f, 2.0f, -46.0f),		Vector3f(50.0f, 2.0f, -6.0f),		Vector3f(40.0f, 2.0f, -6.0f),
			Vector3f(40.0f, 2.0f, -100.0f),	Vector3f(60.0f, 2.0f, -100.0f),		Vector3f(60.0f, 2.0f, -46.0f),		Vector3f(40.0f, 2.0f, -46.0f),
			Vector3f(40.0f, 2.0f, -102.0f),	Vector3f(144.0f, 2.0f, -102.0f),	Vector3f(144.0f, 2.0f, -100.0f),	Vector3f(40.0f, 2.0f, -100.0f),
			Vector3f(60.0f, 2.0f, -80.0f),	Vector3f(80.0f, 2.0f, -80.0f),		Vector3f(80.0f, 2.0f, -46.0f),		Vector3f(60.0f, 2.0f, -46.0f),
			Vector3f(80.0f, 2.0f, -100.0f),	Vector3f(144.0f, 2.0f, -100.0f),	Vector3f(144.0f, 2.0f, -46.0f),		Vector3f(80.0f, 2.0f, -46.0f),
			Vector3f(90.0f, 2.0f, -46.0f),	Vector3f(144.0f, 2.0f, -46.0f),		Vector3f(144.0f, 2.0f, -6.0f),		Vector3f(90.0f, 2.0f, -6.0f),
			// Creux 1
			Vector3f(50.0f, 0.0f, -16.0f),	  Vector3f(90.0f, 0.0f, -16.0f),   Vector3f(90.0f, 2.0f, -6.0f),	  Vector3f(50.0f, 2.0f, -6.0f),		//0
			Vector3f(80.0f, 0.0f, -46.0f),	  Vector3f(90.0f, 2.0f, -46.0f),   Vector3f(90.0f, 2.0f, -6.0f),	  Vector3f(80.0f, 0.0f, -6.0f),		//1
			Vector3f(50.0f, 2.0f, -46.0f),	  Vector3f(90.0f, 2.0f, -46.0f),   Vector3f(90.0f, 0.0f, -36.0f),	  Vector3f(50.0f, 0.0f, -36.0f),	//2
			Vector3f(50.0f, 2.0f, -46.0f),	  Vector3f(60.0f, 0.0f, -46.0f),   Vector3f(60.0f, 0.0f, -6.0f),	  Vector3f(50.0f, 2.0f, -6.0f),		//3
			// Colline 1
			Vector3f(110.0f, 2.0f, -40.0f), Vector3f(125.0f, 2.0f, -40.0f), Vector3f(125.0f, 4.0f, -34.0f), Vector3f(110.0f, 4.0f, -34.0f), //Ramp 0
			Vector3f(104.0f, 2.0f, -34.0f), Vector3f(110.0f, 4.0f, -34.0f), Vector3f(110.0f, 4.0f, -19.0f), Vector3f(104.0f, 2.0f, -19.0f), //Ramp 1
			Vector3f(110.0f, 4.0f, -19.0f), Vector3f(125.0f, 4.0f, -19.0f), Vector3f(125.0f, 2.0f, -13.0f), Vector3f(110.0f, 2.0f, -13.0f), //Ramp 2
			Vector3f(125.0f, 4.0f, -34.0f), Vector3f(131.0f, 2.0f, -34.0f), Vector3f(131.0f, 2.0f, -19.0f), Vector3f(125.0f, 4.0f, -19.0f), //Ramp 3
			Vector3f(104.0f, 2.0f, -40.0f), Vector3f(110.0f, 2.0f, -40.0f), Vector3f(110.0f, 4.0f, -34.0f), Vector3f(104.0f, 2.0f, -34.0f), //Corner 0
			Vector3f(104.0f, 2.0f, -19.0f), Vector3f(110.0f, 4.0f, -19.0f), Vector3f(110.0f, 2.0f, -13.0f), Vector3f(104.0f, 2.0f, -13.0f), //Corner 1
			Vector3f(125.0f, 4.0f, -19.0f), Vector3f(131.0f, 2.0f, -19.0f), Vector3f(131.0f, 2.0f, -13.0f), Vector3f(125.0f, 2.0f, -13.0f), //Corner 2
			Vector3f(125.0f, 2.0f, -40.0f), Vector3f(131.0f, 2.0f, -40.0f), Vector3f(131.0f, 2.0f, -34.0f), Vector3f(125.0f, 4.0f, -34.0f), //Corner 3
			Vector3f(110.0f, 4.0f, -34.0f), Vector3f(125.0f, 4.0f, -34.0f), Vector3f(125.0f, 4.0f, -19.0f), Vector3f(110.0f, 4.0f, -19.0f), //Box
			// Creux 2
			Vector3f(60.0f, 0.0f, -85.0f),	Vector3f(80.0f, 0.0f, -85.0f),	Vector3f(80.0f, 2.0f, -80.0f),	Vector3f(60.0f, 2.0f, -80.0f),	//0
			Vector3f(75.0f, 0.0f, -100.0f),	Vector3f(80.0f, 2.0f, -100.0f),	Vector3f(80.0f, 2.0f, -80.0f),	Vector3f(75.0f, 0.0f, -80.0f),	//1
			Vector3f(60.0f, 2.0f, -100.0f),	Vector3f(80.0f, 2.0f, -100.0f),	Vector3f(80.0f, 0.0f, -95.0f),	Vector3f(60.0f, 0.0f, -95.0f),	//2
			Vector3f(60.0f, 2.0f, -100.0f),	Vector3f(65.0f, 0.0f, -100.0f),	Vector3f(65.0f, 0.0f, -80.0f),	Vector3f(60.0f, 2.0f, -80.0f),	//3
			// Rampe 2
			Vector3f(90.0f, 0.0f, -112.0f),	Vector3f(94.0f, 0.0f, -112.0f), Vector3f(94.0f, 2.0f, -102.0f), Vector3f(90.0f, 2.0f, -102.0f)
		};

		for (int k = 0; k < 4 * FLOOR; k++)
			Floor[k] = temp[k];

		m = new Model(Vector3f(0, 0, 0), grid_material[2]);  // Ceiling
		m->AddSolidColorBox(0.0f, 8.0f, -116.0f, 149.0f, 8.1f, 37.0f, 0xff008080); //plafond
		m->AllocateBuffers();
		Add(m);//Model[3]

		m = new Model(Vector3f(0, 0, 0), grid_material[3]);  // LASER
															 //m->AddSolidColorBox(0, 0, 0, +1.0f, +1.0f, 1.0f, 0xff500000);
		m->AllocateBuffers();
		Add(m);//Model[4]

		m = new Model(Vector3f(-0.5f, -0.5f, 0.15f), grid_material[4]);
		m->AllocateBuffers();
		Add(m);//Model[5]

		m = new Model(Vector3f(-0.5f, -0.5f, 0.15f), grid_material[3]);
		m->AllocateBuffers();
		Add(m);//Model[6]
    }

    Scene() : numModels(0) {}
    Scene(bool includeIntensiveGPUobject) :
        numModels(0)
    {
        Init(includeIntensiveGPUobject);
    }
    void Release()
    {
        while (numModels-- > 0)
            delete Models[numModels];
    }
    ~Scene()
    {
        Release();
    }
};

#endif // OVR_Win32_GLAppUtil_h
