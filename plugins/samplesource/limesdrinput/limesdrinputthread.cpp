///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 Edouard Griffiths, F4EXB                                   //
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

#include "limesdrinputthread.h"

LimeSDRInputThread::LimeSDRInputThread(lms_stream_t* stream, SampleSinkFifo* sampleFifo, QObject* parent) :
    QThread(parent),
    m_running(false),
    m_stream(stream),
    m_convertBuffer(LIMESDR_BLOCKSIZE),
    m_sampleFifo(sampleFifo),
    m_log2Decim(0),
    m_fcPos(0)
{
}

LimeSDRInputThread::~LimeSDRInputThread()
{
    stopWork();
}

void LimeSDRInputThread::startWork()
{
    m_startWaitMutex.lock();
    start();
    while(!m_running)
        m_startWaiter.wait(&m_startWaitMutex, 100);
    m_startWaitMutex.unlock();
}

void LimeSDRInputThread::stopWork()
{
    m_running = false;
    wait();
}

void LimeSDRInputThread::setLog2Decimation(unsigned int log2_decim)
{
    m_log2Decim = log2_decim;
}

void LimeSDRInputThread::setFcPos(int fcPos)
{
    m_fcPos = fcPos;
}

void LimeSDRInputThread::run()
{
    int res;

    lms_stream_meta_t metadata;          //Use metadata for additional control over sample receive function behaviour
    metadata.flushPartialPacket = false; //Do not discard data remainder when read size differs from packet size
    metadata.waitForTimestamp = false;   //Do not wait for specific timestamps

    m_running = true;
    m_startWaiter.wakeAll();

    while (m_running)
    {
        if ((res = LMS_RecvStream(m_stream, (void *) m_buf, LIMESDR_BLOCKSIZE, &metadata, 1000)) < 0)
        {
            qCritical("LimeSDRInputThread::run read error: %s", strerror(errno));
            break;
        }

        callback(m_buf, 2 * LIMESDR_BLOCKSIZE);
    }

    m_running = false;
}

//  Decimate according to specified log2 (ex: log2=4 => decim=16)
void LimeSDRInputThread::callback(const qint16* buf, qint32 len)
{
    SampleVector::iterator it = m_convertBuffer.begin();

    if (m_log2Decim == 0)
    {
        m_decimators.decimate1(&it, buf, len);
    }
    else
    {
        if (m_fcPos == 0) // Infra
        {
            switch (m_log2Decim)
            {
            case 1:
                m_decimators.decimate2_inf(&it, buf, len);
                break;
            case 2:
                m_decimators.decimate4_inf(&it, buf, len);
                break;
            case 3:
                m_decimators.decimate8_inf(&it, buf, len);
                break;
            case 4:
                m_decimators.decimate16_inf(&it, buf, len);
                break;
            case 5:
                m_decimators.decimate32_inf(&it, buf, len);
                break;
            default:
                break;
            }
        }
        else if (m_fcPos == 1) // Supra
        {
            switch (m_log2Decim)
            {
            case 1:
                m_decimators.decimate2_sup(&it, buf, len);
                break;
            case 2:
                m_decimators.decimate4_sup(&it, buf, len);
                break;
            case 3:
                m_decimators.decimate8_sup(&it, buf, len);
                break;
            case 4:
                m_decimators.decimate16_sup(&it, buf, len);
                break;
            case 5:
                m_decimators.decimate32_sup(&it, buf, len);
                break;
            default:
                break;
            }
        }
        else if (m_fcPos == 2) // Center
        {
            switch (m_log2Decim)
            {
            case 1:
                m_decimators.decimate2_cen(&it, buf, len);
                break;
            case 2:
                m_decimators.decimate4_cen(&it, buf, len);
                break;
            case 3:
                m_decimators.decimate8_cen(&it, buf, len);
                break;
            case 4:
                m_decimators.decimate16_cen(&it, buf, len);
                break;
            case 5:
                m_decimators.decimate32_cen(&it, buf, len);
                break;
            default:
                break;
            }
        }
    }

    m_sampleFifo->write(m_convertBuffer.begin(), it);
}
