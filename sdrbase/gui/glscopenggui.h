///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 F4EXB                                                      //
// written by Edouard Griffiths                                                  //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef SDRBASE_GUI_GLSCOPENGGUI_H_
#define SDRBASE_GUI_GLSCOPENGGUI_H_

#include <QWidget>
#include "dsp/dsptypes.h"
#include "util/export.h"
#include "util/message.h"

namespace Ui {
    class GLScopeNGGUI;
}

class MessageQueue;
class GLScopeNG;
class ScopeVisNG;

class SDRANGEL_API GLScopeNGGUI : public QWidget {
    Q_OBJECT

public:
    explicit GLScopeNGGUI(QWidget* parent = 0);
    ~GLScopeNGGUI();

    void setBuddies(MessageQueue* messageQueue, ScopeVisNG* scopeVis, GLScopeNG* glScope);

    void setSampleRate(int sampleRate);
    void resetToDefaults();
    QByteArray serialize() const;
    bool deserialize(const QByteArray& data);

    bool handleMessage(Message* message);

private:
    Ui::GLScopeNGGUI* ui;

    MessageQueue* m_messageQueue;
    ScopeVisNG* m_scopeVis;
    GLScopeNG* m_glScope;

    int m_sampleRate;

    void applySettings();

private slots:
    void on_scope_sampleRateChanged(int value);
    void on_onlyX_toggled(bool checked);
    void on_onlyY_toggled(bool checked);
    void on_horizontalXY_toggled(bool checked);
    void on_verticalXY_toggled(bool checked);
    void on_polar_toggled(bool checked);
    void on_traceIntensity_valueChanged(int value);
    void on_gridIntensity_valueChanged(int value);
    void on_time_valueChanged(int value);
    void on_timeOfs_valueChanged(int value);
    void on_traceLen_valueChanged(int value);
};


#endif /* SDRBASE_GUI_GLSCOPENGGUI_H_ */