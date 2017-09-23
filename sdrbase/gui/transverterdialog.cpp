///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 F4EXB                                                      //
// written by Edouard Griffiths                                                  //
//                                                                               //
// OpenGL interface modernization.                                               //
// See: http://doc.qt.io/qt-5/qopenglshaderprogram.html                          //
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

#include "transverterdialog.h"

#include "ui_transverterdialog.h"


TransverterDialog::TransverterDialog(qint64 *deltaFrequency, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::TransverterDialog),
    m_deltaFrequency(deltaFrequency)
{
    ui->setupUi(this);
    ui->deltaFrequencyLabel->setText(QString("%1f").arg(QChar(0x94, 0x03)));
    ui->deltaFrequency->setColorMapper(ColorMapper(ColorMapper::GrayGold));
    ui->deltaFrequency->setValueRange(false, 7, -9999999, 9999999);
    ui->deltaFrequency->setValue(*m_deltaFrequency/1000);
}

TransverterDialog::~TransverterDialog()
{
    delete ui;
}

void TransverterDialog::accept()
{
    *m_deltaFrequency = ui->deltaFrequency->getValueNew()*1000;
    QDialog::accept();
}