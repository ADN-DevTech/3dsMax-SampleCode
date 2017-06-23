#pragma once

#include <maxapi.h>
#include <Qt/QMaxParamBlockWidget.h>
#include "ui_sampleRollup.h"

namespace Ui { QT_Sample_Rollup; };
// Inherit from QMaxParamBockWidget
class Qt_Sample_Rollup :public MaxSDK::QMaxParamBlockWidget
{
	// Connects us to Qt's meta-object system
	Q_OBJECT

public:
	explicit Qt_Sample_Rollup(QWidget* parent = nullptr);
	~Qt_Sample_Rollup(void);

	// Virtual functions required by QMaxParamBockWidget
	virtual void SetParamBlock(ReferenceMaker* /*owner*/, IParamBlock2* const /*param_block*/) {};
	virtual void UpdateUI(const TimeValue /*t*/) {};
	virtual void UpdateParameterUI(const TimeValue /*t*/, const ParamID /*param_id*/, const int /*tab_index*/) {};

private:
	Ui::QT_Sample_Rollup* ui;

};