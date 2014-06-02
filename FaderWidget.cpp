#include "FaderWidget.h"

#include <QStyleOption>
#include <QGraphicsOpacityEffect>
#include <QDebug>


FaderWidget::FaderWidget(QWidget *parent) :
    QWidget(parent)
{
    _currentOpacity = 0;
    _timer = new QTimer(this);
    _timer2 = new QTimer(this);
    _isFading = false;
    _isFlashing = false;

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateFade()));
    connect(_timer2, SIGNAL(timeout()), this, SLOT(pauseFinished()));

    setOpacity(_currentOpacity);
}

FaderWidget::~FaderWidget()  {


}

void FaderWidget::setOpacity(qreal opacity) {
    if(opacity == 1.0) {
	this->setGraphicsEffect(NULL);
    } else {
	QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
	effect->setOpacity(opacity);
	this->setGraphicsEffect(effect);
    }
}

void FaderWidget::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void FaderWidget::pauseFinished() {
    _timer2->stop();
    fadeOut();
    _isFlashing = false;
}

void FaderWidget::updateFade() {
    _currentOpacity += _opacityIncrement;
    if(_currentOpacity < 0) {
	_currentOpacity = 0;
	_timer->stop();
	_isFading = false;
	_opacityIncrement = 0;
    } else if(_currentOpacity > 1) {
	_currentOpacity = 1;
	_timer->stop();
	_isFading = false;
	_opacityIncrement = 0;
	if(_isFlashing) {
	    _timer2->start(1000);
	}
    }
    setOpacity(_currentOpacity);
}

void FaderWidget::fadeIn() {
    if(_isFading) return;
    _isFading = true;
    //_currentOpacity = 0;
    _opacityIncrement = 0.05;
    _timer->start(10);
}

void FaderWidget::fadeOut() {
    if(_isFading) return;
    _isFading = true;
    //_currentOpacity = 1;
    _opacityIncrement = -0.01;
    _timer->start(10);
}

void FaderWidget::flash() {
    if(_isFlashing) {
	_timer2->start();
	return;
    }
    _isFlashing = true;
    if(_opacityIncrement < 0) _isFading = false;
    fadeIn();
}



