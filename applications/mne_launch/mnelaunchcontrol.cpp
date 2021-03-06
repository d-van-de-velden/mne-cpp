//=============================================================================================================
/**
* @file     mnelaunchcontrol.cpp
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2016
*
* @section  LICENSE
*
* Copyright (C) 2016, Christoph Dinh. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    MNELaunchControl class implementation
*
*/

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "mnelaunchcontrol.h"


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QDebug>
#include <QCoreApplication>
#include <QFile>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================

MNELaunchControl::MNELaunchControl(QObject *parent)
: QObject(parent)
{
    m_requiredSampleFiles   <<  "/MNE-sample-data/MEG/sample/sample_audvis_raw.fif"
                            <<  "/MNE-sample-data/MEG/sample/sample_audvis-meg-eeg-oct-6-fwd.fif"
                            <<  "/MNE-sample-data/subjects/sample/label/lh.aparc.a2009s.annot"
                            <<  "/MNE-sample-data/subjects/sample/label/rh.aparc.a2009s.annot";
}


//*************************************************************************************************************

void MNELaunchControl::invokeScan()
{
    invokeApplication("mne_scan",QStringList());
}


//*************************************************************************************************************

void MNELaunchControl::invokeBrowse()
{
    invokeApplication("mne_browse",QStringList());
}


//*************************************************************************************************************

void MNELaunchControl::invokeAnalyze()
{
    invokeApplication("mne_analyze",QStringList());
}


//*************************************************************************************************************

void MNELaunchControl::invokeApplication(const QString &application, const QStringList &arguments)
{
    QFile file(QCoreApplication::applicationDirPath()+ "/" + application);
#if defined(_WIN32) || defined(_WIN32_WCE)
    file.setFileName(file.fileName() + ".exe");
#endif

    if(file.exists()) {
        try {
            QPointer<QProcess> process( new QProcess );
            process->start(file.fileName(), arguments);
            m_ListProcesses.append(process);
        } catch (int e) {
            qWarning() << "Not able to start" << file.fileName() << ". Error:" << e;
        }
    }
    else {
        qWarning() << "Application" << file.fileName() << "does not exists.";
    }
}


//*************************************************************************************************************

bool MNELaunchControl::getSampleDataAvailable() const
{
    bool sampleFilesExist = true;

    for(QString fileName : m_requiredSampleFiles)
    {
        QFile file (QCoreApplication::applicationDirPath() + fileName);
        if ( !file.exists() ) {
            qWarning() << "Missing sample file" << file.fileName();
            sampleFilesExist = false;
        }
    }
    return sampleFilesExist;
}
