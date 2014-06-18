#ifndef ARTOOLKIWWIDGET_H
#define ARTOOLKIWWIDGET_H

#include <QGLWidget>
#include <QVector>
#include <AR/config.h>
#include <AR/video.h>
#include <AR/param.h>			// arParamDisp()
#include <AR/ar.h>
#include <AR/gsub_lite.h>

namespace Ui {
class ARToolkitWidget;
}

class Pattern;
class GameModel;

class ARToolkitWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit ARToolkitWidget(QWidget* parent = 0);
    virtual ~ARToolkitWidget();

    void setGameModel(GameModel* model);
    void addPattern(Pattern* patt);
    virtual void drawObjects();
    QVector<Pattern*> patterns;

signals:
    void arChipDropped(int column);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void timerEvent(QTimerEvent*);

    Pattern* loadPattern(const char *patt_name);

private:
    int setupCamera(const char *cparam_name, char *vconf, ARParam *cparam);
    void debugReportMode(const ARGL_CONTEXT_SETTINGS_REF arglContextSettings);
    int setupMarker(const char *patt_name, int *patt_id);
    void drawCube(void);

    // Image acquisition.
    ARUint8* gARTImage;

    // Marker detection.
    int	gARTThreshhold;
    long gCallCountMarkerDetect;

    // Markers
    Pattern* gPatt;
    Pattern* gPatt2;

    // Drawing.
    ARParam	gARTCparam;
    ARGL_CONTEXT_SETTINGS_REF gArglSettings;
    int gDrawRotate;
    float gDrawRotateAngle;			// For use in drawing.


    GameModel* m_model;
};

#endif // ARTOOLKIWWIDGET_H
