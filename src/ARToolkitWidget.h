#ifndef ARTOOLKIWWIDGET_H
#define ARTOOLKIWWIDGET_H

#include <QGLWidget>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>

namespace Ui {
class ARToolkitWidget;
}

class ARToolkitWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit ARToolkitWidget(QWidget* parent = 0);
    virtual ~ARToolkitWidget();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void timerEvent(QTimerEvent*);

private:
    // ============================================================================
    //	Constants
    // ============================================================================

    #define VIEW_SCALEFACTOR		0.025		// 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
    #define VIEW_DISTANCE_MIN		0.1			// Objects closer to the camera than this will not be displayed.
    #define VIEW_DISTANCE_MAX		100.0		// Objects further away from the camera than this will not be displayed.

    // ============================================================================
    //	Global variables
    // ============================================================================

    // Image acquisition.
    ARUint8	*gARTImage = NULL;

    // Marker detection.
    int	gARTThreshhold = 100;
    long gCallCountMarkerDetect = 0;

    class GPattClass
    {
    public:
        // Transformation matrix retrieval.
        double width;
        double centre[2];
        double trans[3][4];
        int found;
        int id;

        GPattClass(double pattWidth = 80.0)
        {
            width = pattWidth;
            centre[0] = 0.0;
            centre[1] = 0.0;

            found = FALSE;

        }
    };

    GPattClass gPatt;
    GPattClass gPatt2;

    // Drawing.
    ARParam	gARTCparam;
    ARGL_CONTEXT_SETTINGS_REF gArglSettings = NULL;
    int gDrawRotate = FALSE;
    float gDrawRotateAngle = 0;			// For use in drawing.

    int setupCamera(const char *cparam_name, char *vconf, ARParam *cparam);
    void debugReportMode(const ARGL_CONTEXT_SETTINGS_REF arglContextSettings);
    int setupMarker(const char *patt_name, int *patt_id);
    void drawCube(void);
};

#endif // ARTOOLKIWWIDGET_H
