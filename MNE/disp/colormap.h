//=============================================================================================================
/**
* @file     colormap.h
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>;
* @version  1.0
* @date     March, 2013
*
* @section  LICENSE
*
* Copyright (C) 2013, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    ColorMap class declaration
*
*/

#ifndef COLORMAP_H
#define COLORMAP_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "disp_global.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QSharedPointer>
#include <QColor>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE FSLIB
//=============================================================================================================

namespace DISPLIB
{

//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* Provides diffenrent color maps like Jet,...
*
* @brief Color map RGB transformations
*/
class DISPSHARED_EXPORT ColorMap
{
public:
    typedef QSharedPointer<ColorMap> SPtr;            /**< Shared pointer type for ColorMap class. */
    typedef QSharedPointer<const ColorMap> ConstSPtr; /**< Const shared pointer type for ColorMap class. */
    
    //=========================================================================================================
    /**
    * Default constructor
    */
    ColorMap();
    
    //=========================================================================================================
    /**
    * Destroys the ColorMap class.
    */
    ~ColorMap();

    static inline QRgb valueToJet(double v);

    static inline QRgb valueToHot(double v);

    static inline QRgb valueToBone(double v);
    
protected:
    static double linearSlope(double x, double m, double n);

    static int jetR(double v);
    static int jetG(double v);
    static int jetB(double v);

    static int hotR(double v);
    static int hotG(double v);
    static int hotB(double v);

    static int boneR(double v);
    static int boneG(double v);
    static int boneB(double v);

private:
    
};

//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================

inline QRgb ColorMap::valueToJet(double v)
{
    QRgb p_qRgb = qRgb(jetR(v), jetG(v), jetB(v));
    return p_qRgb;
}


//*************************************************************************************************************

inline QRgb ColorMap::valueToHot(double v)
{
    QRgb p_qRgb = qRgb(hotR(v), hotG(v), hotB(v));
    return p_qRgb;
}


//*************************************************************************************************************

inline QRgb ColorMap::valueToBone(double v)
{
    QRgb p_qRgb = qRgb(boneR(v), boneG(v), boneB(v));
    return p_qRgb;
}

} // NAMESPACE

#endif // COLORMAP_H
