#include "Settings.h"


#include <QColor>

Settings* Settings::s_instance = 0;

Settings::Settings(QObject *parent)
    : QSettings(IniFormat, UserScope, "knalltueten", "c4", parent)
{
    s_instance = this;
}


Settings::~Settings()
{
    s_instance = 0;
}

Settings* Settings::instance()
{
    return s_instance;
}

void Settings::setPlayerName(const QString& name)
{
    setValue( "playerName", name );
}

const QString Settings::playerName() const
{
    return value( "playerName", "Knalltuete" ).value< QString >();
}

void Settings::setPlayerColor(const QColor& color)
{
    setValue( "playerColor", color );
}

const QColor Settings::playerColor() const
{
    return value( "playerColor", QColor(Qt::red)).value< QColor >();
}

void Settings::setAiName(const QString& name)
{
    setValue( "aiName", name );
}

const QString Settings::aiName() const
{
    return value( "aiName", "Bob" ).value< QString >();
}

void Settings::setAiNameList(const QString& name)
{
    setValue( "aiNameList", name );
}

const QString Settings::aiNameList() const
{
    return value( "aiNameList", "Human|WeakAI|NormalAI|HardAI|ChuckNorris" ).value< QString >();
}

void Settings::setAiColor(const QColor& color)
{
    setValue( "aiColor", color );
    emit settingsChanged();
}

const QColor Settings::aiColor() const
{
    return value( "aiColor", QColor(Qt::yellow)).value< QColor >();

}

void Settings::setAiLevel(int aiLevel)
{
    setValue( "aiLevel", aiLevel );
}

int Settings::aiLevel() const
{
    return value( "aiLevel", 0).value< int >();
}

void Settings::setPlayerLevel(int playerLevel)
{
    setValue( "playerLevel", playerLevel );
}

int Settings::playerLevel() const
{
    return value( "playerLevel", 0).value< int >();
}

void Settings::setCameraWidth(int cameraWidth)
{
    setValue( "cameraWidth", cameraWidth );
}

int Settings::cameraWidth() const
{
    return value( "cameraWidth", 640).value< int >();
}

void Settings::setCameraHeight(int cameraHeight)
{
    setValue( "cameraHeight", cameraHeight );
}

int Settings::cameraHeight() const
{
    return value( "cameraHeight", 480).value< int >();
}
void Settings::setQuickSave(const QString& save)
{
    setValue( "quickSave", save );
}

const QString Settings::quickSave() const
{
    return value( "quickSave" ).value< QString >();
}

