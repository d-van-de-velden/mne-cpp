//=============================================================================================================
/**
* @file     renderable3Dentity.h
* @author   Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2015
*
* @section  LICENSE
*
* Copyright (C) 2015, Lorenz Esch and Matti Hamalainen. All rights reserved.
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
* @brief    Renderable3DEntity class declaration
*
*/

#ifndef RENDERABLE3DENTITY_H
#define RENDERABLE3DENTITY_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../../disp3D_global.h"
#include "custommesh.h"


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <Qt3DCore/QEntity>
#include <QVector3D>
#include <QPointer>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

namespace Qt3DCore {
    class QTransform;
}

namespace Qt3DRender{
    class QMaterial;
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

class ShaderMaterial;


//=============================================================================================================
/**
* Base class for renederable 3D QEntities.
*
* @brief Base class for renederable 3D QEntities.
*/
class DISP3DNEWSHARED_EXPORT Renderable3DEntity : public Qt3DCore::QEntity
{
    Q_OBJECT
    Q_PROPERTY(float rotX READ rotX WRITE setRotX NOTIFY rotXChanged)
    Q_PROPERTY(float rotY READ rotY WRITE setRotY NOTIFY rotYChanged)
    Q_PROPERTY(float rotZ READ rotZ WRITE setRotZ NOTIFY rotZChanged)
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)

public:
    typedef QSharedPointer<Renderable3DEntity> SPtr;             /**< Shared pointer type for Renderable3DEntity class. */
    typedef QSharedPointer<const Renderable3DEntity> ConstSPtr;  /**< Const shared pointer type for Renderable3DEntity class. */

    //=========================================================================================================
    /**
    * Default constructor for freesurfer mesh.#
    *
    * @param[in] parent         The parent of this entity.
    */
    explicit Renderable3DEntity(Qt3DCore::QEntity* parent = 0);

    //=========================================================================================================
    /**
    * Default constructor for freesurfer mesh.
    *
    * @param[in] tMatVert       Vertices in form of a matrix.
    * @param[in] tMatNorm       Normals in form of a matrix.
    * @param[in] tMatTris       Tris/Faces in form of a matrix.
    * @param[in] parent         The parent of this class.
    */
    Renderable3DEntity(const Eigen::MatrixX3f& tMatVert, const Eigen::MatrixX3f& tMatNorm, const Eigen::MatrixX3i& tMatTris, Qt3DCore::QEntity* parent = 0);

    //=========================================================================================================
    /**
    * Default destructor.
    */
    ~Renderable3DEntity();

    //=========================================================================================================
    /**
    * Refresh the vertices colors of the mesh.
    *
    * @param[in] tArrayColors     New color information for the vertices.
    */
    void setVertColor(const QByteArray &tArrayColors);

    //=========================================================================================================
    /**
    * Set the information needed to create the mesh.
    *
    * @param[in] tMatVert       Vertices in form of a matrix.
    * @param[in] tMatNorm       Normals in form of a matrix.
    * @param[in] tMatTris       Tris/Faces in form of a matrix.
    */
    void setMeshData(const Eigen::MatrixX3f& tMatVert,
                     const Eigen::MatrixX3f& tMatNorm,
                     const Eigen::MatrixXi &tMatTris,
                     const QByteArray &tArrayColors = QByteArray(),
                     Qt3DRender::QGeometryRenderer::PrimitiveType primitiveType = Qt3DRender::QGeometryRenderer::Triangles);

    //=========================================================================================================
    /**
    * Sets the entity's transformation.
    *
    * @param[in] pTransform     The new entity's transform.
    */
    void setTransform(QSharedPointer<Qt3DCore::QTransform> pTransform);

    //=========================================================================================================
    /**
    * Returns the current rotation around the x-axis.
    *
    * @return The x-axis rotation value.
    */
    float rotX() const;

    //=========================================================================================================
    /**
    * Returns the current rotation around the y-axis.
    *
    * @return The y-axis rotation value.
    */
    float rotY() const;

    //=========================================================================================================
    /**
    * Returns the current rotation around the z-axis.
    *
    * @return The z-axis rotation value.
    */
    float rotZ() const;

    //=========================================================================================================
    /**
    * Returns the current position/translation.
    *
    * @return The position/translation value.
    */
    QVector3D position() const;

    //=========================================================================================================
    /**
    * Sets the current rotation around the x-axis.
    *
    * @param[in] rotX     The x-axis rotation value.
    */
    void setRotX(float rotX);

    //=========================================================================================================
    /**
    * Sets the current rotation around the y-axis.
    *
    * @param[in] rotY     The y-axis rotation value.
    */
    void setRotY(float rotY);

    //=========================================================================================================
    /**
    * Sets the current rotation around the z-axis.
    *
    * @param[in] rotZ     The z-axis rotation value.
    */
    void setRotZ(float rotZ);

    //=========================================================================================================
    /**
    * Sets the current position/translation.
    *
    * @param[in] position     The position/translation value.
    */
    void setPosition(QVector3D position);

    //=========================================================================================================
    /**
    * Sets the value of a specific paramater of the materials for this entity.
    *
    * @param[in] fValue             The value to be set.
    * @param[in] sParameterName     The name of the parameter to be set.
    */
    void setMaterialParameter(float fValue, QString sParameterName);

protected: 
    QPointer<CustomMesh>                        m_pCustomMesh;           /**< The actual mesh information (vertices, normals, colors). */
    QPointer<Qt3DCore::QTransform>              m_pTransform;            /**< The main transformation. */

    float                                       m_fRotX;                 /**< The x axis rotation value. */
    float                                       m_fRotY;                 /**< The y axis rotation value. */
    float                                       m_fRotZ;                 /**< The z axis rotation value. */
    QVector3D                                   m_position;              /**< The position/translation value. */

    //=========================================================================================================
    /**
    * Update the set transformation with the currently set translation and rotation values.
    */
    void updateTransform();

signals:
    //=========================================================================================================
    /**
    * Emit this signal whenever the x-axis rotation changed.
    *
    * @param[in] rotX     The x-axis rotation value.
    */
    void rotXChanged(float rotX);

    //=========================================================================================================
    /**
    * Emit this signal whenever the y-axis rotation changed.
    *
    * @param[in] rotY     The y-axis rotation value.
    */
    void rotYChanged(float rotY);

    //=========================================================================================================
    /**
    * Emit this signal whenever the z-axis rotation changed.
    *
    * @param[in] rotZ     The z-axis rotation value.
    */
    void rotZChanged(float rotZ);

    //=========================================================================================================
    /**
    * Emit this signal whenever the position/translation changed.
    *
    * @param[in] position     The position/translation value.
    */
    void positionChanged(QVector3D position);

};

} // NAMESPACE

#ifndef metatype_renderable3Dentity
#define metatype_renderable3Dentity
Q_DECLARE_METATYPE(DISP3DLIB::Renderable3DEntity*)
#endif

#endif // RENDERABLE3DENTITY_H
