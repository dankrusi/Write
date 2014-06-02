#ifndef FADERWIDGET_H
#define FADERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>

class FaderWidget : public QWidget
{

Q_OBJECT

private:
    qreal _currentOpacity;
    qreal _opacityIncrement;
    bool _isFading;
    bool _isFlashing;
    QTimer *_timer;
    QTimer *_timer2;

public:
    explicit FaderWidget(QWidget *parent = 0);
    ~FaderWidget();
    void setOpacity(qreal opacity);

protected:
    void paintEvent(QPaintEvent *e);

signals:

public slots:
    void updateFade();
    void pauseFinished();
    void fadeIn();
    void fadeOut();
    void flash();

};

#endif // FADERWIDGET_H
