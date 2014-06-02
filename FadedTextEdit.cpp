#include "FadedTextEdit.h"

#include <QDebug>
#include <QLayout>
#include <QScrollBar>
#include <QGraphicsOpacityEffect>
#include <QGraphicsBlurEffect>

FadedTextEdit::FadedTextEdit(QWidget *parent) : QTextEdit(parent) {

    _blurred = false;

    this->setStyleSheet("QWidget { background-color: #000000; }");


    _textEdit = new QTextEdit(this);
    _textEdit->setStyleSheet("QTextEdit { color: white; padding-left: 60px; padding-right: 60px; font-family: Andale Mono; font-size: 18pt; }");
    _textEdit->document()->setDocumentMargin(40);
    _textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    //_textEdit->setFont(QFont("Andale Mono",14));
    //_textEdit->setTextColor(Qt::white);

    connect(_textEdit->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(scrollValueChanged(int)));


    _slider = new FaderWidget(this);
    _slider->resize(1,30);
    _slider->setObjectName("slider");
    _slider->setStyleSheet("#slider { background-color: white; }");

    _faderTop = new GradientWidget(GradientWidget::GradeDirectionTopDown, this);
    _faderBottom = new GradientWidget(GradientWidget::GradeDirectionBottomUp, this);

    //_textEdit->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc gravida sapien non odio feugiat posuere. Donec et dolor nulla, scelerisque pulvinar velit. Nam elementum orci eu eros volutpat non facilisis enim ultricies. Etiam nunc tellus, consectetur nec tincidunt in, imperdiet et sem. Morbi mattis placerat orci quis elementum. Aenean vitae ligula lectus, non sollicitudin mauris. Vestibulum elementum urna nec nisl varius sollicitudin. Donec ac ante quam. Donec elit lorem, aliquet sed bibendum sit amet, laoreet eu diam. Cras leo nunc, elementum vel venenatis ac, sagittis at ligula. Nunc eget tortor dui, vitae pharetra ipsum. Sed interdum hendrerit aliquam. Aliquam turpis ipsum, aliquet non ultricies vitae, interdum vitae metus. Ut egestas, magna et blandit sollicitudin, eros massa fermentum erat, et rhoncus tellus velit ut elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc gravida sapien non odio feugiat posuere. Donec et dolor nulla, scelerisque pulvinar velit. Nam elementum orci eu eros volutpat non facilisis enim ultricies. Etiam nunc tellus, consectetur nec tincidunt in, imperdiet et sem. Morbi mattis placerat orci quis elementum. Aenean vitae ligula lectus, non sollicitudin mauris. Vestibulum elementum urna nec nisl varius sollicitudin. Donec ac ante quam. Donec elit lorem, aliquet sed bibendum sit amet, laoreet eu diam. Cras leo nunc, elementum vel venenatis ac, sagittis at ligula. Nunc eget tortor dui, vitae pharetra ipsum. Sed interdum hendrerit aliquam. Aliquam turpis ipsum, aliquet non ultricies vitae, interdum vitae metus. Ut egestas, magna et blandit sollicitudin, eros massa fermentum erat, et rhoncus tellus velit ut elit. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nunc gravida sapien non odio feugiat posuere. Donec et dolor nulla, scelerisque pulvinar velit. Nam elementum orci eu eros volutpat non facilisis enim ultricies. Etiam nunc tellus, consectetur nec tincidunt in, imperdiet et sem. Morbi mattis placerat orci quis elementum. Aenean vitae ligula lectus, non sollicitudin mauris. Vestibulum elementum urna nec nisl varius sollicitudin. Donec ac ante quam. Donec elit lorem, aliquet sed bibendum sit amet, laoreet eu diam. Cras leo nunc, elementum vel venenatis ac, sagittis at ligula. Nunc eget tortor dui, vitae pharetra ipsum. Sed interdum hendrerit aliquam. Aliquam turpis ipsum, aliquet non ultricies vitae, interdum vitae metus. Ut egestas, magna et blandit sollicitudin, eros massa fermentum erat, et rhoncus tellus velit ut elit. ");

    scrollValueChanged(0);
}

FadedTextEdit::~FadedTextEdit()  {


}

void FadedTextEdit::setBrightness(qreal brightness) {
    if(brightness == 1.0) {
	this->setGraphicsEffect(NULL);
    } else {
	QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
	effect->setOpacity(brightness);
	this->setGraphicsEffect(effect);
    }
}

void FadedTextEdit::setBlur(bool blurred) {
    _blurred = blurred;
    if(blurred) {
	QGraphicsBlurEffect *effect = new QGraphicsBlurEffect(_textEdit);
	effect->setBlurRadius(10);
	_textEdit->setGraphicsEffect(effect);
    } else {
	_textEdit->setGraphicsEffect(NULL);
    }
}

bool FadedTextEdit::isBlurred() {
    return _blurred;
}

void FadedTextEdit::resizeEvent(QResizeEvent *e)
{
    int fadeSize = 40;

    _textEdit->setGeometry(0,0,this->width(),this->height());

    _faderTop->setGeometry(0,0,this->width(),fadeSize);
    _faderBottom->setGeometry(0,this->height()-fadeSize,this->width(),fadeSize);

    scrollValueChanged(_textEdit->verticalScrollBar()->value());

}

void FadedTextEdit::scrollValueChanged(int value) {
    double sp = _textEdit->verticalScrollBar()->maximum() == 0 ? 0 : (double)_textEdit->verticalScrollBar()->value() / (double)_textEdit->verticalScrollBar()->maximum();
    int w = 2;
    double hp = _textEdit->verticalScrollBar()->maximum() == 0 ? 0 : (double)this->height() / (double)_textEdit->verticalScrollBar()->maximum();
    int h = (int)( 40 * hp );
    if(h < 30 && hp != 0) h = 30;
    _slider->resize(w,h);
    int y = (int)( (this->height()-_slider->height()) * sp );
    _slider->move(this->width()-_slider->width()-2,y);
    _slider->flash();
}
