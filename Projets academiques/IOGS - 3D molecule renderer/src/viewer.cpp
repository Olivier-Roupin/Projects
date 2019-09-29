#include "viewer.h"
#include "camera.h"

#include "SOIL2.h"

extern int WIDTH;
extern int HEIGHT;

using namespace Eigen;

Viewer::Viewer(): _sphere()
{
    _currentPrg = 0;
    _prgNames.push_back("simple");
    _prgNames.push_back("sphere");
    _prgNames.push_back("cylinder");
}

Viewer::~Viewer()
{
}

////////////////////////////////////////////////////////////////////////////////
// GL stuff

// initialize OpenGL context
void Viewer::init(int w, int h)
{
    _winWidth = w;
    _winHeight = h;

    // Couleur d'arrière plan
    glClearColor(0.5, 0.5, 0.5, 1.0);

    loadProgram();

    _length = 2.5f;

    Vector3f center(0,0,0);
    Vector3f barycenter(0,0,0);
    float radius(0);
    for(int i = 0; i < N; i++)
        barycenter += Vector3f(positions[3*i],positions[3*i+1],positions[3*i+2])/N;
    for(int i = 0; i < N; i++) {
        center = Vector3f(positions[3*i],positions[3*i+1],positions[3*i+2]);
        radius = std::max(radius, (center-barycenter).norm());
        _atoms.push_back(Atom(atoms[i], center-barycenter, _length));
    }

    _cam.setSceneCenter(Vector3f(0,0,0));
    _cam.setSceneRadius(radius);
    _cam.setSceneDistance(_cam.sceneRadius() * 3.f);
    _cam.setMinNear(0.1f);
    _cam.setNearFarOffsets(-_cam.sceneRadius() * 100.f,
                            _cam.sceneRadius() * 100.f);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Viewer::reshape(int w, int h){
    _winWidth = w;
    _winHeight = h;
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));
    glViewport(0, 0, w, h);
}


/*!
   callback to draw graphic primitives
 */
void Viewer::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Eigen::Matrix4f projectionMatrix = _cam.computeProjectionMatrix();
    Eigen::Matrix4f viewMatrix = _cam.computeViewMatrix();
    _prg2.activate();

    glUniformMatrix4fv(_prg2.getUniformLocation("projection_matrix"), 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(_prg2.getUniformLocation("view_matrix"), 1, GL_FALSE, viewMatrix.data());

    for(int i = 0; i < _atoms.size(); i++) {
        glUniformMatrix4fv(_prg2.getUniformLocation("model_matrix"),1, GL_FALSE, _atoms[i].transformation().data());

        glUniform3fv(_prg2.getUniformLocation("color"),1, _atoms[i].color().data());

        glUniform1f(_prg2.getUniformLocation("sphere_radius"), _atoms[i].radius());
        Vector3f C = (viewMatrix.matrix() * _atoms[i].transformation().matrix()).topRightCorner<3,1>();
        glUniform3fv(_prg2.getUniformLocation("sphere_center"),1, C.data() );

        _sphere.display(&_prg2);
    }

    _prg2.deactivate();

    _prg3.activate();

    glUniformMatrix4fv(_prg3.getUniformLocation("projection_matrix"), 1, GL_FALSE, projectionMatrix.data());
    glUniformMatrix4fv(_prg3.getUniformLocation("view_matrix"), 1, GL_FALSE, viewMatrix.data());

    for(int i = 0; i < _atoms.size(); i++) {
        Vector3f B = (viewMatrix.matrix() * _atoms[i].transformation().matrix()).topRightCorner<3,1>();
        Vector3f T = (viewMatrix.matrix() * _atoms[edges[i]].transformation().matrix()).topRightCorner<3,1>();
        Vector3f C = _atoms[i].transformation().matrix().topRightCorner<3,1>()/2 + _atoms[edges[i]].transformation().matrix().topRightCorner<3,1>()/2; // Center of the cylinder_vector
        Affine3f transformation = (Affine3f)Translation3f(C)*Scaling(_length);

        glUniformMatrix4fv(_prg3.getUniformLocation("model_matrix"),1, GL_FALSE, transformation.data());
        glUniform3fv(_prg3.getUniformLocation("color"),1, Vector3f(0.2,0.2,0.5).data());
        glUniform1f(_prg3.getUniformLocation("cylinder_radius"), 0.25f);
        glUniform3fv(_prg3.getUniformLocation("cylinder_bottom"),1, B.data() );
        glUniform3fv(_prg3.getUniformLocation("cylinder_top"),1, T.data() );

        _sphere.display(&_prg3);
    }

    _prg3.deactivate();

}


void Viewer::updateScene()
{
    display();
}

void Viewer::loadProgram()
{
    //_prg.loadFromFiles(DATA_DIR"/shaders/" + _prgNames[_currentPrg] +".vert",
    //                   DATA_DIR"/shaders/" + _prgNames[_currentPrg] + ".frag");
    _prg.loadFromFiles(DATA_DIR"/shaders/simple.vert",
                       DATA_DIR"/shaders/simple.frag");
    _prg2.loadFromFiles(DATA_DIR"/shaders/sphere.vert",
                        DATA_DIR"/shaders/sphere.frag");
    _prg3.loadFromFiles(DATA_DIR"/shaders/cylinder.vert",
                        DATA_DIR"/shaders/cylinder.frag");
    checkError();
}

////////////////////////////////////////////////////////////////////////////////
// Events

/*!
   callback to manage mouse : called when user press or release mouse button
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mousePressed(GLFWwindow *window, int button, int action)
{
    if(action == GLFW_PRESS) {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            _cam.startRotation(_lastMousePos);
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            _cam.startTranslation(_lastMousePos);
        }
        _button = button;
    }else if(action == GLFW_RELEASE) {
        if(_button == GLFW_MOUSE_BUTTON_LEFT)
        {
            _cam.endRotation();
        }
        else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            _cam.endTranslation();
        }
        _button = -1;
    }
}


/*!
   callback to manage mouse : called when user move mouse with button pressed
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mouseMoved(int x, int y)
{
    if(_button == GLFW_MOUSE_BUTTON_LEFT)
    {
        _cam.dragRotate(Vector2f(x,y));
    }
    else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        _cam.dragTranslate(Vector2f(x,y));
    }
    _lastMousePos = Vector2f(x,y);
}

void Viewer::mouseScroll(double x, double y)
{
    _cam.zoom((y>0)? 1.1: 1./1.1);
}

/*!
   callback to manage keyboard interactions
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::keyPressed(int key, int action, int mods)
{
    if(key == GLFW_KEY_R && action == GLFW_PRESS)
        loadProgram();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
        _currentPrg = (_currentPrg-1);
        if(_currentPrg<0)
            _currentPrg += _prgNames.size();
        loadProgram();
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        _currentPrg = (_currentPrg+1)%_prgNames.size();
        loadProgram();
    } else if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS) && _length > 1.0f){
        _length -= 0.1f;
        for(int i = 0; i < _atoms.size(); i++)
            _atoms[i].setLength(_length);
    } else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS) && _length < 20.0f){
        _length += 0.1f;
        for(int i = 0; i < _atoms.size(); i++)
            _atoms[i].setLength(_length);
    }
}

void Viewer::charPressed(int key)
{
}
