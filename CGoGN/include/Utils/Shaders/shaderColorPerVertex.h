/*******************************************************************************
* CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
* version 0.1                                                                  *
* Copyright (C) 2009-2012, IGG Team, LSIIT, University of Strasbourg           *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Web site: http://cgogn.unistra.fr/                                           *
* Contact information: cgogn@unistra.fr                                        *
*                                                                              *
*******************************************************************************/

#ifndef __CGOGN_SHADER_CPV__
#define __CGOGN_SHADER_CPV__

#include "Utils/GLSLShader.h"
#include "Utils/Shaders/shaderPointsLines.h"
#include "Geometry/vector_gen.h"

#include "Utils/dll.h"

namespace CGoGN
{

namespace Utils
{

class CGoGN_UTILS_API ShaderColorPerVertex : public ShaderPointsLines
{
protected:
	// shader sources
    static std::string vertexShaderText;
    static std::string fragmentShaderText;
	static std::string vertexShaderClipText;
	static std::string fragmentShaderClipText;

    VBO* m_vboPos;
    VBO* m_vboCol;

    CGoGNGLuint m_unif_alpha;
    float m_opacity;

	/// clipping
	CGoGNGLuint m_unif_planeClip;
	Geom::Vec4f m_planeClip;


    void restoreUniformsAttribs();

public:
	ShaderColorPerVertex(bool withClipping = false, bool black_is_transparent = false);

	/**
	 * set the VBO of position (vec3)
	 */
    unsigned int setAttributePosition(VBO* vbo);

	/**
	 * set the VBO of color (vec3)
	 */
    unsigned int setAttributeColor(VBO* vbo);

	/// just for uniform interface with gl3 BoldLines shaders
	inline void setLineWidth(float pix) { glLineWidth(pix); }

	/**
	 * set opacity (0=transparent / 1=opaque)
	 */
	void setOpacity(float op);

	float getOpacity() const  { return m_opacity;}

	void setClippingPlane(const Geom::Vec4f& plane);
	inline void setNoClippingPlane() { setClippingPlane(Geom::Vec4f(0.0f, 0.0f, 0.0f, 0.0f)); }
};

} // namespace Utils

} // namespace CGoGN

#endif
