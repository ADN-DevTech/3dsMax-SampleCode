#include "Qt_Sample_Rollup.h"

Qt_Sample_Rollup::Qt_Sample_Rollup(QWidget* parent)
	:QMaxParamBlockWidget(/*parent*/),
	ui(new Ui::QT_Sample_Rollup())
{
	ui->setupUi(this);
}


Qt_Sample_Rollup::~Qt_Sample_Rollup(void)
{
	delete ui;
}

