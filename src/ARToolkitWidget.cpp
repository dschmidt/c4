//#include <GL/glew.h>

#include "ARToolkitWidget.h"

#include <QDebug>
#include <QApplication>




ARToolkitWidget::ARToolkitWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::Rgba | QGL::DepthBuffer), parent)
{
}

ARToolkitWidget::~ARToolkitWidget()
{
    arglCleanup(gArglSettings);
    arVideoCapStop();
    arVideoClose();
}


int ARToolkitWidget::setupCamera(const char *cparam_name, char *vconf, ARParam *cparam)
{
    ARParam wparam;
    int xsize, ysize;

    // Open the video path.
    if (arVideoOpen(vconf) < 0) {
        qDebug() << "setupCamera(): Unable to open connection to camera.\n";
        return (FALSE);
    }

    // Find the size of the window.
    if (arVideoInqSize(&xsize, &ysize) < 0) return (FALSE);
    qDebug() << "Camera image size (x,y) = (" << xsize << "," << ysize << ")\n";

    // Load the camera parameters, resize for the window and init.
    if (arParamLoad(cparam_name, 1, &wparam) < 0) {
        qDebug() << "setupCamera(): Error loading parameter file " << cparam_name << " for camera.\n";
        return (FALSE);
    }
    arParamChangeSize(&wparam, xsize, ysize, cparam);
    qDebug() << "*** Camera Parameter ***\n";
    arParamDisp(cparam);

    arInitCparam(cparam);

    if (arVideoCapStart() != 0) {
        qDebug() << "setupCamera(): Unable to begin camera data capture.\n";
        return (FALSE);
    }

    return (TRUE);
}

// Report state of ARToolKit global variables arFittingMode,
// arImageProcMode, arglDrawMode, arTemplateMatchingMode, arMatchingPCAMode.
void ARToolkitWidget::debugReportMode(const ARGL_CONTEXT_SETTINGS_REF arglContextSettings)
{
    if (arFittingMode == AR_FITTING_TO_INPUT) {
        qDebug() << "FittingMode (Z): INPUT IMAGE\n";
    } else {
        qDebug() << "FittingMode (Z): COMPENSATED IMAGE\n";
    }

    if (arImageProcMode == AR_IMAGE_PROC_IN_FULL) {
        qDebug() << "ProcMode (X)   : FULL IMAGE\n";
    } else {
        qDebug() << "ProcMode (X)   : HALF IMAGE\n";
    }

    if (arglDrawModeGet(arglContextSettings) == AR_DRAW_BY_GL_DRAW_PIXELS) {
        qDebug() << "DrawMode (C)   : GL_DRAW_PIXELS\n";
    } else if (arglTexmapModeGet(arglContextSettings) == AR_DRAW_TEXTURE_FULL_IMAGE) {
        qDebug() << "DrawMode (C)   : TEXTURE MAPPING (FULL RESOLUTION)\n";
    } else {
        qDebug() << "DrawMode (C)   : TEXTURE MAPPING (HALF RESOLUTION)\n";
    }

    if (arTemplateMatchingMode == AR_TEMPLATE_MATCHING_COLOR) {
        qDebug() << "TemplateMatchingMode (M)   : Color Template\n";
    } else {
        qDebug() << "TemplateMatchingMode (M)   : BW Template\n";
    }

    if (arMatchingPCAMode == AR_MATCHING_WITHOUT_PCA) {
        qDebug() << "MatchingPCAMode (P)   : Without PCA\n";
    } else {
        qDebug() << "MatchingPCAMode (P)   : With PCA\n";
    }
}

int ARToolkitWidget::setupMarker(const char *patt_name, int *patt_id)
{
    // Loading only 1 pattern in this example.
    if ((*patt_id = arLoadPatt(patt_name)) < 0) {
        qDebug() << "setupMarker(): pattern load error !!\n";
        return (FALSE);
    }

    return (TRUE);
}

void ARToolkitWidget::initializeGL()
{
    startTimer(0);

    //char glutGamemode[32];
    const char *cparam_name = "camera_para.dat";
    //
    // Camera configuration.
    //
#ifdef _WIN32
    char *vconf = "Data\\WDM_camera_flipV.xml";
#else
    char *vconf = "v4l2src ! ffmpegcolorspace ! capsfilter caps=video/x-raw-rgb,bpp=24,width=640,height=480 ! identity name=artoolkit ! fakesink";
#endif


    const char *patt_name  = "patt.hiro";
    const char *patt_name2 = "patt.kanji";

    // ----------------------------------------------------------------------------
    // Hardware setup.
    //

    if (!setupCamera(cparam_name, vconf, &gARTCparam)) {
        qDebug() << "main(): Unable to set up AR camera.\n";
        QApplication::instance()->exit(-1);
    }

    // Setup argl library for current context.
    if ((gArglSettings = arglSetupForCurrentContext()) == NULL) {
        qDebug() << "main(): arglSetupForCurrentContext() returned error.\n";
        QApplication::instance()->exit(-1);
    }
    debugReportMode(gArglSettings);
    glEnable(GL_DEPTH_TEST);
    arUtilTimerReset();

    if (!setupMarker(patt_name, &gPatt.id)) {
        qDebug() << "main(): Unable to set up AR marker.\n";
        QApplication::instance()->exit(-1);
    }
    if (!setupMarker(patt_name2, &gPatt2.id)) {
        qDebug() << "main(): Unable to set up AR marker.\n";
        QApplication::instance()->exit(-1);
    }
}

void ARToolkitWidget::resizeGL(int width, int height)
{
    qDebug() << Q_FUNC_INFO << width << height;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Something to look at, draw a rotating colour cube.
void ARToolkitWidget::drawCube(void)
{
    // Colour cube data.
    static GLuint polyList = 0;
    float fSize = 0.5f;
    long f, i;
    const GLfloat cube_vertices [8][3] = {
    {1.0, 1.0, 1.0}, {1.0, -1.0, 1.0}, {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0},
    {1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, {-1.0, -1.0, -1.0}, {-1.0, 1.0, -1.0} };
    const GLfloat cube_vertex_colors [8][3] = {
    {1.0, 1.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 1.0, 1.0},
    {1.0, 0.0, 1.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0} };
    GLint cube_num_faces = 6;
    const short cube_faces [6][4] = {
    {3, 2, 1, 0}, {2, 3, 7, 6}, {0, 1, 5, 4}, {3, 0, 4, 7}, {1, 2, 6, 5}, {4, 5, 6, 7} };

    if (!polyList) {
        polyList = glGenLists (1);
        glNewList(polyList, GL_COMPILE);
        glBegin (GL_QUADS);
        for (f = 0; f < cube_num_faces; f++)
            for (i = 0; i < 4; i++) {
                glColor3f (cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
                glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
            }
        glEnd ();
        glColor3f (0.0, 0.0, 0.0);
        for (f = 0; f < cube_num_faces; f++) {
            glBegin (GL_LINE_LOOP);
            for (i = 0; i < 4; i++)
                glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
            glEnd ();
        }
        glEndList ();
    }

    glPushMatrix(); // Save world coordinate system.
    glTranslatef(0.0, 0.0, 0.5); // Place base of cube on marker surface.
    glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
    glDisable(GL_LIGHTING);	// Just use colours.
    glCallList(polyList);	// Draw the cube.
    glPopMatrix();	// Restore world coordinate system.

}

void ARToolkitWidget::paintGL()
{
    GLdouble p[16];
    GLdouble m[16];

    // Select correct buffer for this context.
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers for new frame.

    arglDispImage(gARTImage, &gARTCparam, 1.0, gArglSettings);	// zoom = 1.0.
    arVideoCapNext();
    gARTImage = NULL; // Image data is no longer valid after calling arVideoCapNext().

    // Projection transformation.
    arglCameraFrustumRH(&gARTCparam, VIEW_DISTANCE_MIN, VIEW_DISTANCE_MAX, p);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(p);
    glMatrixMode(GL_MODELVIEW);

    // Viewing transformation.
    glLoadIdentity();
    // Lighting and geometry that moves with the camera should go here.
    // (I.e. must be specified before viewing transformations.)
    //none

    if (gPatt.found) {

        // Calculate the camera position relative to the marker.
        // Replace VIEW_SCALEFACTOR with 1.0 to make one drawing unit equal to 1.0 ARToolKit units (usually millimeters).
        arglCameraViewRH(gPatt.trans, m, VIEW_SCALEFACTOR);
        glLoadMatrixd(m);

        // All lighting and geometry to be drawn relative to the marker goes here.
        drawCube();

    } // gPatt.found
    if (gPatt2.found) {

        // Calculate the camera position relative to the marker.
        // Replace VIEW_SCALEFACTOR with 1.0 to make one drawing unit equal to 1.0 ARToolKit units (usually millimeters).
        arglCameraViewRH(gPatt2.trans, m, VIEW_SCALEFACTOR);
        glLoadMatrixd(m);

        // All lighting and geometry to be drawn relative to the marker goes here.
        drawCube();

    } // gPatt2.found

    // Any 2D overlays go here.
    //none

    swapBuffers();
}


void ARToolkitWidget::timerEvent(QTimerEvent *)
{
    static int ms_prev;
    int ms;
    float s_elapsed;
    ARUint8 *image;

    ARMarkerInfo    *marker_info;					// Pointer to array holding the details of detected markers.
    int             marker_num;						// Count of number of markers detected.
    int             j, k, k2;

    // Grab a video frame.
    if ((image = arVideoGetImage()) != NULL) {
        gARTImage = image;	// Save the fetched image.

        gCallCountMarkerDetect++; // Increment ARToolKit FPS counter.

        // Detect the markers in the video frame.
        if (arDetectMarker(gARTImage, gARTThreshhold, &marker_info, &marker_num) < 0) {
            exit(-1);
        }

        // Check through the marker_info array for highest confidence
        // visible marker matching our preferred pattern.
        k = -1;
        for (j = 0; j < marker_num; j++) {
            if (marker_info[j].id == gPatt.id) {
                if (k == -1) k = j; // First marker detected.
                else if(marker_info[j].cf > marker_info[k].cf) k = j; // Higher confidence marker detected.
            }
        }
        k2 = -1;
        for (j = 0; j < marker_num; j++) {
            if (marker_info[j].id == gPatt2.id) {
                if (k2 == -1) k2 = j; // First marker detected.
                else if(marker_info[j].cf > marker_info[k].cf) k2 = j; // Higher confidence marker detected.
            }
        }

        if (k != -1) {
            // Get the transformation between the marker and the real camera into gPatt_trans.
            arGetTransMat(&(marker_info[k]), gPatt.centre, gPatt.width, gPatt.trans);
            gPatt.found = TRUE;
        } else {
            gPatt.found = FALSE;
        }
        if (k2 != -1) {
            // Get the transformation between the marker and the real camera into gPatt_trans.
            arGetTransMat(&(marker_info[k2]), gPatt2.centre, gPatt2.width, gPatt2.trans);
            gPatt2.found = TRUE;
        } else {
            gPatt2.found = FALSE;
        }

        // Tell Qt the display has changed.
        updateGL();
    }
}

