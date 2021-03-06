///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2018 Edouard Griffiths, F4EXB                                   //
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

#include <QDebug>

#include "xtrx_api.h"
#include "devicextrx.h"

const uint32_t DeviceXTRX::m_lnaTbl[m_nbGains] = {
        0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,
        5,  5,  6,  6,  6,  7,  7,  7,  8,  9,  10, 11, 11, 11, 11, 11,
        11, 11, 11, 11, 11, 11, 11, 11, 12, 13, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
        14, 14, 14, 14, 14, 14, 14, 14, 14, 14
};

const uint32_t DeviceXTRX::m_pgaTbl[m_nbGains] = {
        0,  1,  2,  0,  1,  2,  0,  1,  2,  0,  1,  2,  0,  1,  2,  0,
        1,  2,  0,  1,  2,  0,  1,  2,  0,  0,  0,  0,  1,  2,  3,  4,
        5,  6,  7,  8,  9,  10, 11, 12, 12, 12, 12, 4,  5,  6,  7,  8,
        9,  10, 11, 12, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31
};

DeviceXTRX::DeviceXTRX() :
    m_dev(0),
    m_inputRate(0),
    m_outputRate(0),
    m_masterRate(0),
    m_clockGen(0)
{}

DeviceXTRX::~DeviceXTRX()
{
    close();
}

bool DeviceXTRX::open(const char* deviceStr)
{
    int res;
    qDebug("DeviceXTRX::open: serial: %s", (const char *) deviceStr);

    res = xtrx_open(deviceStr, XTRX_O_RESET | 4, &m_dev);

    if (res)
    {
        qCritical() << "DeviceXTRX::open: cannot open device " << deviceStr;
        return false;
    }

    return true;
}

void DeviceXTRX::close()
{
    if (m_dev)
    {
        xtrx_close(m_dev);
        m_dev = 0;
    }
}

void DeviceXTRX::getAutoGains(uint32_t autoGain, uint32_t& lnaGain, uint32_t& tiaGain, uint32_t& pgaGain)
{
    uint32_t value = autoGain + 12 > 73 ? 73 : autoGain + 12;

    if (value > 51) {
        tiaGain = 2;
    } else if (value > 42) {
        tiaGain = 1;
    } else {
        tiaGain = 0;
    }

    lnaGain = m_lnaTbl[value];
    pgaGain = m_pgaTbl[value];
}

double DeviceXTRX::set_samplerate(double rate, double master, bool output)
{
    if (output)
    {
        m_outputRate = rate;

        if (master != 0.0) {
            m_masterRate = master;
        }
    }
    else
    {
        m_inputRate = rate;

        if (master != 0.0) {
            m_masterRate = master;
        }
    }

    int res = xtrx_set_samplerate(m_dev,
          m_masterRate,
          m_inputRate,
          m_outputRate,
          0,
          &m_clockGen,
          &m_actualInputRate,
          &m_actualOutputRate);

    if (res)
    {
        qCritical("DeviceXTRX::set_samplerate: Unable to set %s samplerate, m_masterRate: %f, m_inputRate: %f, m_outputRate: %f, error=%d\n",
                output ? "output" : "input", m_masterRate, m_inputRate, m_outputRate, res);
        return 0;
    }
    else
    {
        qDebug() << "DeviceXTRX::set_samplerate: sample rate set: "
                << "output: "<< output
                << "m_masterRate: " << m_masterRate
                << "m_inputRate: " << m_inputRate
                << "m_outputRate: " << m_outputRate
                << "m_clockGen: " << m_clockGen
                << "m_actualInputRate: " << m_actualInputRate
                << "m_actualOutputRate: " << m_actualOutputRate;
    }

    if (output) {
        return m_outputRate;
    }

    return m_inputRate;
}