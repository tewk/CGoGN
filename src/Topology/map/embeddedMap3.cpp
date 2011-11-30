/*******************************************************************************
* CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
* version 0.1                                                                  *
* Copyright (C) 2009-2011, IGG Team, LSIIT, University of Strasbourg           *
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
* Web site: http://cgogn.u-strasbg.fr/                                         *
* Contact information: cgogn@unistra.fr                                        *
*                                                                              *
*******************************************************************************/

#include "Topology/map/embeddedMap3.h"

namespace CGoGN
{

Dart EmbeddedMap3::deleteVertex(Dart d)
{
	Dart v = Map3::deleteVertex(d) ;
	if(v != NIL)
	{
		if (isOrbitEmbedded(VOLUME))
		{
			embedOrbit(VOLUME, v, getEmbedding(VOLUME, v)) ;
		}
	}
	return v ;
}

void EmbeddedMap3::cutEdge(Dart d)
{
	Map3::cutEdge(d);

	if(isOrbitEmbedded(EDGE))
	{
		Dart nd = phi1(d) ;

		// embed the new darts created in the cut edge
		embedOrbit(EDGE, d, getEmbedding(EDGE, d)) ;
		// embed a new cell for the new edge and copy the attributes' line (c) Lionel
		embedNewCell(EDGE, nd) ;
		copyCell(EDGE, nd, d) ;
	}

	if(isOrbitEmbedded(FACE))
	{
		Dart f = d;
		do
		{
			Dart nd = phi1(f) ;
			copyDartEmbedding(FACE, nd, f);
			Dart e = phi2(nd);
			copyDartEmbedding(FACE, phi1(e), e);
			f = alpha2(f);
		} while(f != d);
	}

	if(isOrbitEmbedded(VOLUME))
	{
		Dart f = d;
		do
		{
			unsigned int vEmb = getEmbedding(VOLUME, f) ;
			setDartEmbedding(VOLUME, phi1(f), vEmb);
			setDartEmbedding(VOLUME, phi2(f), vEmb);
			f = alpha2(f);
		} while(f != d);
	}
}

bool EmbeddedMap3::uncutEdge(Dart d)
{
	if(Map3::uncutEdge(d))
	{
		//embed all darts from the old two edges to one of the two edge embedding
		if(isOrbitEmbedded(EDGE))
		{
			embedOrbit(EDGE, d, getEmbedding(EDGE, d)) ;
		}
		return true ;
	}
	return false ;
}

void EmbeddedMap3::splitFace(Dart d, Dart e)
{
	Map3::splitFace(d,e);

	//copy the vertex embedding to new darts (same vertex embedding for all darts)
	if(isOrbitEmbedded(VERTEX))
	{
		copyDartEmbedding(VERTEX, phi2(phi_1(d)), d);
		copyDartEmbedding(VERTEX, phi2(phi_1(e)), e);

		if(!isBoundaryFace(d))
		{
			Dart d3 = phi3(d);
			Dart e3 = phi3(e);

			copyDartEmbedding(VERTEX, phi1(d3), phi1(phi2(phi1(d3))));
			copyDartEmbedding(VERTEX, phi1(e3), phi1(phi2(phi1(e3))));
		}
	}

	//add a new face embedding to the created face
	if(isOrbitEmbedded(FACE))
	{
		embedNewCell(FACE, phi2(phi_1(d)));
		copyCell(FACE, phi2(phi_1(d)), d);
	}

	//copy the volume embedding to new darts (same volume embedding for all darts on the faces)
	if(isOrbitEmbedded(VOLUME))
	{
		copyDartEmbedding(VOLUME, phi_1(d),  d);
		copyDartEmbedding(VOLUME, phi2(phi_1(d)),  d);

		if(!isBoundaryFace(d))
		{
			Dart d3 = phi3(d);

			copyDartEmbedding(VOLUME, phi1(d3), d3);
			copyDartEmbedding(VOLUME, phi2(phi1(d3)), d3);
		}
	}

}

void EmbeddedMap3::sewVolumes(Dart d, Dart e)
{
	//topological sewing
	Map3::sewVolumes(d,e);

	//embed the vertex orbits from the oriented face with dart e
	//with vertex orbits value from oriented face with dart d
	if (isOrbitEmbedded(VERTEX))
	{
		unsigned int vEmb1 = EMBNULL ;
		Dart dd = d ;
		do {
			vEmb1 = getEmbedding(VERTEX, dd);
			embedOrbit(VERTEX, dd, vEmb1) ;
			dd = phi1(dd) ;
		} while(dd != d) ;
	}

	//embed the new edge orbit with the old edge orbit value
	//for all the face
	if (isOrbitEmbedded(EDGE))
	{
		unsigned int vEmb1 = EMBNULL ;
		Dart dd = d ;
		do {
			vEmb1 = getEmbedding(EDGE, d);
			embedOrbit(EDGE, d, vEmb1) ;
			dd = phi1(dd) ;
		} while(dd != d) ;
	}

	//embed the face orbit from the volume sewn
	if (isOrbitEmbedded(FACE))
	{
		unsigned int vEmb1 = getEmbedding(FACE, d);
		embedOrbit(FACE, e, vEmb1) ;
	}
}

void EmbeddedMap3::unsewVolumes(Dart d)
{
	if(!Map3::isBoundaryFace(d))
	{
		Dart dd = phi1(phi3(d));
		Map3::unsewVolumes(d);

		Dart dit = d;
		do
		{
			//embed the unsewn vertex orbit with the vertex embedding if it is deconnected
			if(isOrbitEmbedded(VERTEX))
			{
				if(!sameVertex(dit,dd))
				{
					embedNewCell(VERTEX, dd);
					copyCell(VERTEX, dd, dit);
				}
			}

			dd = phi_1(dd);

			//embed the unsewn edge with the edge embedding if it is deconnected
			if(isOrbitEmbedded(EDGE))
			{
				if(!sameEdge(dit,dd))
				{
					embedNewCell(EDGE, dd);
					copyCell(EDGE, dd, dit);
				}
			}

			dit = phi1(dit);
		} while(dit!=d);

		//embed the unsewn face with the face embedding
		if (isOrbitEmbedded(FACE))
		{
			embedNewCell(FACE, dd);
			copyCell(FACE, dd, d);
		}
	}
}

bool EmbeddedMap3::mergeVolumes(Dart d)
{
	Dart d2 = phi2(d);

	if(Map3::mergeVolumes(d))
	{
		if (isOrbitEmbedded(VOLUME))
		{
				unsigned int vEmb = getEmbedding(VOLUME, d2);
				embedOrbit(VOLUME, d2, vEmb) ;
		}
		return true;
	}
	return false;
}

void EmbeddedMap3::splitVolume(std::vector<Dart>& vd)
{
	Map3::splitVolume(vd);

	//follow the edge path a second time to embed the vertex, edge and volume orbits
	for(std::vector<Dart>::iterator it = vd.begin() ; it != vd.end() ; ++it)
	{
		Dart dit = *it;
		Dart dit3 = alpha2(dit);

		//embed the vertex embedded from the origin volume to the new darts
		if(isOrbitEmbedded(VERTEX))
		{
			copyDartEmbedding(VERTEX, dit3, dit);
			copyDartEmbedding(VERTEX, phi2(dit), phi2(dit3));
		}

		//embed the edge embedded from the origin volume to the new darts
		if(isOrbitEmbedded(EDGE))
		{
			copyDartEmbedding(EDGE, dit3, dit);
			copyDartEmbedding(EDGE, phi2(dit), dit);
		}

		//embed the volume embedded from the origin volume to the new darts
		if(isOrbitEmbedded(VOLUME))
		{
			copyDartEmbedding(VOLUME, dit3, dit);
			copyDartEmbedding(VOLUME, phi2(dit), dit);
		}
	}
}

bool EmbeddedMap3::check()
{
	bool topo = Map3::check() ;
	if (!topo)
		return false ;

	std::cout << "Check: embedding begin" << std::endl ;
	DartMarker mv(*this);
	for(Dart d = begin(); d != end(); next(d))
	{
		if(isOrbitEmbedded(VERTEX))
		{
			if(!mv.isMarked(d))
			{
				mv.markOrbit(VERTEX, d);
				unsigned int emb = getEmbedding(VERTEX, d);
				FunctorCheckEmbedding<Map3> fce(*this, VERTEX, emb);
				if(foreach_dart_of_orbit(VERTEX, d, fce))
				{
					std::cout << "Embedding Check : different embeddings on vertex" << std::endl;
				}
			}
		}

	}
	std::cout << "Check: embedding ok" << std::endl ;
	return true ;
}

} // namespace CGoGN