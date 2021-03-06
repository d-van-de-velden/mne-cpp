//=============================================================================================================
/**
* @file     measurement.h
* @author   Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2016
*
* @section  LICENSE
*
* Copyright (C) 2016, Lorenz Esch and Matti Hamalainen. All rights reserved.
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
* @brief     MeasurementTreeItem class declaration.
*
*/

#ifndef MEASUREMENTTREEITEM_H
#define MEASUREMENTTREEITEM_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../../../disp3D_global.h"
#include "../common/abstracttreeitem.h"

#include <mne/mne_forwardsolution.h>
#include <connectivity/network/network.h>


//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QPointer>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

namespace FSLIB {
    class SurfaceSet;
    class AnnotationSet;
    class Surface;
    class Annotation;
}

namespace MNELIB {
    class MNESourceSpace;
    class MNESourceEstimate;
}

namespace FIFFLIB{
    class FiffDigPointSet;
}

namespace INVERSELIB{
    class ECDSet;
}

namespace Qt3DCore {
    class QEntity;
}


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE DISP3DLIB
//=============================================================================================================

namespace DISP3DLIB
{

//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class MneEstimateTreeItem;
class NetworkTreeItem;
class EcdDataTreeItem;
class FsSurfaceTreeItem;
class SourceSpaceTreeItem;
class DigitizerSetTreeItem;


//=============================================================================================================
/**
* MeasurementTreeItem provides a generic brain tree item to hold of brain data (hemi, vertices, tris, etc.) from different sources (FreeSurfer, etc.).
*
* @brief Provides a generic MeasurementTreeItem.
*/
class DISP3DNEWSHARED_EXPORT MeasurementTreeItem : public AbstractTreeItem
{
    Q_OBJECT

public:
    typedef QSharedPointer<MeasurementTreeItem> SPtr;             /**< Shared pointer type for MeasurementTreeItem class. */
    typedef QSharedPointer<const MeasurementTreeItem> ConstSPtr;  /**< Const shared pointer type for MeasurementTreeItem class. */

    //=========================================================================================================
    /**
    * Default constructor.
    *
    * @param[in] iType      The type of the item. See types.h for declaration and definition.
    * @param[in] text       The text of this item. This is also by default the displayed name of the item in a view.
    */
    explicit MeasurementTreeItem(int iType = Data3DTreeModelItemTypes::MeasurementItem, const QString& text = "Unknown measurement");

    //=========================================================================================================
    /**
    * Default destructor
    */
    ~MeasurementTreeItem();

    //=========================================================================================================
    /**
    * AbstractTreeItem functions
    */
    QVariant data(int role = Qt::UserRole + 1) const;
    void setData(const QVariant& value, int role = Qt::UserRole + 1);

    //=========================================================================================================
    /**
    * Adds source space data to this item.
    *
    * @param[in] tSourceSpace       The source space data.
    * @param[in] p3DEntityParent    The Qt3D entity parent of the new item.
    *
    * @return                       Returns a pointer to the added tree item. Default is a NULL pointer if no item was added.
    */
    SourceSpaceTreeItem* addData(const MNELIB::MNESourceSpace& tSourceSpace, Qt3DCore::QEntity* p3DEntityParent = 0);

    //=========================================================================================================
    /**
    * Adds source estimated activation data (MNE, RTC-MUSIC) to this item.
    *
    * @param[in] tSourceEstimate    The MNESourceEstimate.
    * @param[in] tForwardSolution   The MNEForwardSolution.
    *
    * @return                       Returns a pointer to the added tree item. Default is a NULL pointer if no item was added.
    */
    MneEstimateTreeItem* addData(const MNELIB::MNESourceEstimate& tSourceEstimate, const MNELIB::MNEForwardSolution& tForwardSolution = MNELIB::MNEForwardSolution());

    //=========================================================================================================
    /**
    * Adds source estimated activation data (dipole fit) to this item.
    *
    * @param[in] tECDSet            The ECDSet dipole data.
    * @param[in] p3DEntityParent    The Qt3D entity parent of the new item.
    *
    * @return                       Returns a pointer to the added tree item. Default is a NULL pointer if no item was added.
    */
    EcdDataTreeItem* addData(QSharedPointer<INVERSELIB::ECDSet> &pECDSet, Qt3DCore::QEntity* p3DEntityParent = 0);

    //=========================================================================================================
    /**
    * Adds digitizer data to this item.
    *
    * @param[in] digitizerkind      The kind of the digitizer data.
    * @param[in] tDigitizer         The digitizer data.
    * @param[in] p3DEntityParent    The Qt3D entity parent of the new item.
    *
    * @return                       Returns a pointer to the added tree item. Default is a NULL pointer if no item was added.
    */
    DigitizerSetTreeItem* addData(const FIFFLIB::FiffDigPointSet& tDigitizer, Qt3DCore::QEntity* p3DEntityParent = 0);

    //=========================================================================================================
    /**
    * Adds connectivity estimation data.
    *
    * @param[in] pNetworkData       The connectivity data.
    *
    * @return                       Returns a pointer to the added tree item. Default is a NULL pointer if no item was added.
    */
    NetworkTreeItem* addData(CONNECTIVITYLIB::Network::SPtr pNetworkData, Qt3DCore::QEntity* p3DEntityParent = 0);

    //=========================================================================================================
    /**
    * This function gets called whenever the origin of the surface vertex color (curvature, annotation, etc.) changed.
    * The color generation then based on the current user chosen color origin.
    *
    * @param[in] leftHemiColor        Color of the left hemisphere.
    * @param[in] rightHemiColor       Color of the right hemisphere.
    */
    void setColorOrigin(const QByteArray& leftHemiColor, const QByteArray& rightHemiColor);

private:
    //=========================================================================================================
    /**
    * Call this function whenever the check box of this item was checked.
    *
    * @param[in] checkState        The current checkstate.
    */
    virtual void onCheckStateChanged(const Qt::CheckState& checkState);

    //=========================================================================================================
    /**
    * Call this function whenever new colors for the activation data plotting are available.
    *
    * @param[in] sourceColorSamples     The color values for each estimated source for left and right hemisphere.
    */
    void onRtVertColorChanged(const QPair<QByteArray, QByteArray>& sourceColorSamples);

    MneEstimateTreeItem*                m_pMneEstimateTreeItem;        /**< The rt source loc data item of this item. */
    NetworkTreeItem*                    m_pNetworkTreeItem;                     /**< The rt connectivity data item of this item. */
    EcdDataTreeItem*                    m_EcdDataTreeItem;                      /**< The rt dipole fit data item of this item. */

signals:
    //=========================================================================================================
    /**
    * emit this signal whenver the color info of the underlying hemisphere surfaes changed.
    *
    * @param[in] sourceColorSamples        Real tiem colors for both hemispheres.
    */
    void rtVertColorChanged(const QPair<QByteArray, QByteArray>& sourceColorSamples);

};

} //NAMESPACE DISP3DLIB

#endif // MEASUREMENTTREEITEM_H
