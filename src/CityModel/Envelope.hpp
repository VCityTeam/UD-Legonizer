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
#ifndef __CITYGML_ENVELOPE_HPP__
#define __CITYGML_ENVELOPE_HPP__

#include <ostream>
#include "Vecs.hpp"
//#include "citygml_export.h"

#ifdef _MSC_VER                // Inhibit dll-interface warnings concerning
#pragma warning(disable: 4251) // export problem on STL members
#endif

namespace citygml
{

	class /*CITYGML_EXPORT*/ Envelope
	{
		friend class CityGMLHandler;
	public:
		Envelope();
		Envelope(const TVec3d& lowerBound, const TVec3d& upperBound);

		const TVec3d& getLowerBound() const;
		const TVec3d& getUpperBound() const;

		void merge(const Envelope& e);

		void merge(const TVec3d& p);

	protected:
		TVec3d _lowerBound;
		TVec3d _upperBound;
	};

	std::ostream& operator<<(std::ostream&, const citygml::Envelope&);

} // namespace citygml

#endif // __CITYGML_ENVELOPE_HPP__
