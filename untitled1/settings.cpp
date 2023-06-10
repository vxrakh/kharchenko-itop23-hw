#include "settings.h"
#include <QObject>

settings::settings()
{

}

Q_GLOBAL_STATIC(settings, global_inst)
settings *settings::instanse()
{
    return global_inst();
}

double settings::getMin() const
{
    return _min;
}

void settings::setMin(double min)
{
    _min = min;
}

double settings::getMax() const
{
    return _max;
}

void settings::setMax(double max)
{
    _max = max;
}
