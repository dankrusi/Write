#ifndef FADEDTEXTEDIT_H
#define FADEDTEXTEDIT_H


#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>

#include "FaderWidget.h"
#include "GradientWidget.h"


class FadedTextEdit : public QTextEdit {

    Q_OBJECT

private:
    QTextEdit *_textEdit;
    GradientWidget *_faderTop;
    GradientWidget *_faderBottom;
    FaderWidget *_slider;
    bool _blurred;

public:
    FadedTextEdit(QWidget *parent = 0);
    ~FadedTextEdit();
    QTextEdit* textEdit() { return _textEdit; };
    void setBrightness(qreal brightness);
    void setBlur(bool blurred);
    bool isBlurred();

protected:
    void resizeEvent(QResizeEvent *e);

public slots:
    void scrollValueChanged(int value);

};

#endif // FADEDTEXTEDIT_H
