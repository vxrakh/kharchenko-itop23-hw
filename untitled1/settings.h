#ifndef SETTINGS_H
#define SETTINGS_H


class settings
{
public:
    settings();
    static settings *instanse();

    double getMin() const;
    void setMin(double min);
    double getMax() const;
    void setMax(double max);
private:
    double _min = 1.0;
    double _max = 10.0;
};

#endif // SETTINGS_H



