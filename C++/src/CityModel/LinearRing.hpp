/* -*-c++-*- libcitygml - Copyright (c) 2010 Joachim Pouderoux, BRGM
*
* This file is part of libcitygml library
* http://code.google.com/p/libcitygml
*
* libcitygml is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 2.1 of the License, or
* (at your option) any later version.
*
* libcitygml is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __CITYGML_LINEARRING_HPP__
#define __CITYGML_LINEARRING_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "Object.hpp"
#include "Vecs.hpp"
#include "Envelope.hpp"
#include "CityGMLTypes.hpp"
//#include "citygml_export.h"
#ifdef _MSC_VER                // Inhibit dll-interface warnings concerning
#pragma warning(disable: 4251) // export problem on STL members
#endif

////////////////////////////////////////////////////////////////////////////////
namespace citygml
{
	////////////////////////////////////////////////////////////////////////////////
	class /*CITYGML_EXPORT*/ LinearRing : public Object
	{
		friend class CityGMLHandler;
		friend class Polygon;
	public:
		LinearRing(const std::string& id, bool isExterior);

		bool isExterior(void) const;

		unsigned int size(void) const;

		const std::vector<TVec3d>& getVertices(void) const;

		void addVertex(const TVec3d& v);

		TVec3d computeNormal(void) const;

		// Return the envelope (ie. the bounding box) of the object
		const Envelope& getEnvelope(void) const;

		std::vector<TVec3d>& getVertices(void);

		void finish(TexCoords*);

	protected:
		bool _exterior;

		std::vector<TVec3d> _vertices;

		Envelope _envelope;
	};
	////////////////////////////////////////////////////////////////////////////////
} // namespace citygml
////////////////////////////////////////////////////////////////////////////////
#endif //  __CITYGML_LINEARRING_HPP__
