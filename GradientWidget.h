#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

class GradientWidget : public QWidget
{

Q_OBJECT

public:
    enum GradeDirection {
	GradeDirectionTopDown,
	GradeDirectionBottomUp
    };

private:
    QLinearGradient _gradient;
    GradeDirection _fadeDirection;

public:
    explicit GradientWidget(GradeDirection fadeDirection, QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:

};

#endif // GRADIENTWIDGET_H
