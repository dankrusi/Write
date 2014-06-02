#include "GradientWidget.h"

#include <QLinearGradient>
#include <QPalette>

GradientWidget::GradientWidget(GradeDirection fadeDirection, QWidget *parent) :
    QWidget(parent), _fadeDirection(fadeDirection)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);

    if(_fadeDirection == GradeDirectionBottomUp) {
	_gradient.setStart(QPointF(0, 1));
	_gradient.setFinalStop(QPointF(0, 0));
    } else {
	_gradient.setStart(QPointF(0, 0));
	_gradient.setFinalStop(QPointF(0, 1));
    }

    _gradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    _gradient.setColorAt(1, Qt::transparent);
}

void GradientWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    _gradient.setColorAt(0, this->parentWidget()->palette().background().color());


    painter.fillRect(this->rect(), _gradient);


}
