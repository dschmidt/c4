#ifndef ARTOOLKIWWIDGET_H
#define ARTOOLKIWWIDGET_H


#include "Config.h"

namespace Ui {
class ARToolkitWidget;
}

class Pattern;
class GameModel;

#include <QGLWidget>
#include <QMap>
#ifdef ARTOOLKIT_FOUND
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>
#endif

class GlObject;

class ARToolkitWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit ARToolkitWidget(QWidget* parent = 0);
    virtual ~ARToolkitWidget();

    void setGameModel(GameModel* model);
    void addPattern(Pattern* patt, GlObject* obj);
    virtual void drawObjects();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void timerEvent(QTimerEvent*);

    Pattern* loadPattern(const char *patt_name, double pattWidth = 80.0);

    // ============================================================================
    //	Constants
    // ============================================================================

    static const double VIEW_SCALEFACTOR = 0.025;      // 1.0 ARToolKit unit becomes 0.025 of my OpenGL units.
    static const double VIEW_DISTANCE_MIN = 0.1;		// Objects closer to the camera than this will not be displayed.
    static const double VIEW_DISTANCE_MAX = 100.0;		// Objects further away from the camera than this will not be displayed.

    QMap<Pattern*, GlObject*> m_patterns;

private:
#ifdef ARTOOLKIT_FOUND
    int setupCamera(const char *cparam_name, char *vconf, ARParam *cparam);
    void debugReportMode(const ARGL_CONTEXT_SETTINGS_REF arglContextSettings);
#endif
    int setupMarker(const char *patt_name, int *patt_id);
    void drawCube(void);

#ifdef ARTOOLKIT_FOUND
    // Image acquisition.
    ARUint8* gARTImage;

    // Marker detection.
    int	gARTThreshhold;
    long gCallCountMarkerDetect;

    // Drawing.
    ARParam	gARTCparam;
    ARGL_CONTEXT_SETTINGS_REF gArglSettings;
#endif
    int gDrawRotate;
    float gDrawRotateAngle;			// For use in drawing.
};

#endif // ARTOOLKIWWIDGET_H
