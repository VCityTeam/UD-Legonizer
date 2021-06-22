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
#include <iostream>
#include "CityObject.hpp"
#include "Utils.hpp"

////////////////////////////////////////////////////////////////////////////////
namespace citygml
{
	////////////////////////////////////////////////////////////////////////////////
	CityObject::CityObject(const std::string& id, CityObjectsType type)
		: Object(id), _type(type), m_path(""), m_temporalUse(false)
	{}
	////////////////////////////////////////////////////////////////////////////////
	CityObject::~CityObject()
	{
		for (Geometry* geom : _geometries)
			delete geom;

		for (CityObject* obj : _children)
			delete obj;

	}
	////////////////////////////////////////////////////////////////////////////////
	// Get the object type
	CityObjectsType CityObject::getType(void) const
	{
		return _type;
	}
	////////////////////////////////////////////////////////////////////////////////
	std::string CityObject::getTypeAsString(void) const
	{
		return getCityObjectsClassName(_type);
	}
	////////////////////////////////////////////////////////////////////////////////
	// Return the envelope (ie. the bounding box) of the object
	const Envelope& CityObject::getEnvelope(void) const
	{
		return _envelope;
	}
	////////////////////////////////////////////////////////////////////////////////
	// Get the number of geometries contains in the object
	size_t CityObject::size(void) const
	{
		return _geometries.size();
	}
	////////////////////////////////////////////////////////////////////////////////
	// Access the geometries
	const Geometry* CityObject::getGeometry(unsigned int i) const
	{
		return _geometries[i];
	}
	////////////////////////////////////////////////////////////////////////////////
	std::vector< Geometry* >& CityObject::getGeometries()
	{
		return _geometries;
	}
	////////////////////////////////////////////////////////////////////////////////
	const std::vector< Geometry* >& CityObject::getGeometries() const
	{
		return _geometries;
	}
	////////////////////////////////////////////////////////////////////////////////
	// Access the children
	size_t CityObject::getChildCount(void) const
	{
		return _children.size();
	}
	////////////////////////////////////////////////////////////////////////////////
	const CityObject* CityObject::getChild(unsigned int i) const
	{
		return (i < getChildCount()) ? _children[i] : 0;
	}
	////////////////////////////////////////////////////////////////////////////////
	CityObject* CityObject::getChild(unsigned int i)
	{
		return (i < getChildCount()) ? _children[i] : 0;
	}
	////////////////////////////////////////////////////////////////////////////////
	const std::vector< CityObject* >& CityObject::getChildren(void) const
	{
		return _children;
	}
	////////////////////////////////////////////////////////////////////////////////
	std::vector< CityObject* >& CityObject::getChildren(void)
	{
		return _children;
	}
	////////////////////////////////////////////////////////////////////////////////
	//remove all the children of the CityObject (without deleting them)
	void CityObject::clearChildren()
	{
		_children.clear();
	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::addGeometry(Geometry* geom)
	{
		_geometries.push_back(geom);
	}
	////////////////////////////////////////////////////////////////////////////////
	CityObject* CityObject::getParent()
	{
		return _parent;
	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::deleteNode(const std::string& node)
	{

	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::deleteNode(CityObject* node)
	{

	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::insertNode(CityObject* node)
	{
		_children.push_back(node);
	}
	////////////////////////////////////////////////////////////////////////////////
	CityObject* CityObject::getNode(const vcity::URI& uri)
	{
		CityObject* res = this;
		CityObject* current = this;

		while (uri.getCursor() < uri.getDepth())
		{
			if (current->_isXlink == xLinkState::LINKED)
				for (Object* child : current->getXLinkTargets())
				{
					if (child->getId() == uri.getCurrentNode())
					{
						current = (CityObject*)child;
						res = current;
						break;
					}
				}
			for (CityObject* child : current->getChildren())
			{
				if (child->getId() == uri.getCurrentNode())
				{
					current = child;
					res = current;
					break;
				}
			}
			uri.popFront();
		}

		uri.resetCursor();

		return res;
	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::finish(AppearanceManager& appearanceManager, const ParserParams& params)
	{
		Appearance* myappearance = appearanceManager.getAppearance(getId());
		std::vector< Geometry* >::const_iterator it = _geometries.begin();
		for (; it != _geometries.end(); ++it)
		{
			(*it)->finish(appearanceManager, myappearance ? myappearance : 0, params);
		}

		bool finish = false;
		while (!finish && params.optimize)
		{
			finish = true;
			size_t len = _geometries.size();
			for (size_t i = 0; finish && i < len - 2; i++)
			{
				for (size_t j = i + 1; finish && j < len - 1; j++)
				{
					if (!_geometries[i]->merge(_geometries[j])) continue;
					delete _geometries[j];
					_geometries.erase(_geometries.begin() + j);
					finish = false;
				}
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	/*void CityObject::finish()
	{
		Appearance* myappearance = appearanceManager.getAppearance( getId() );
		std::vector< Geometry* >::const_iterator it = _geometries.begin();
		for(; it != _geometries.end(); ++it)
		{
			(*it)->finish( appearanceManager, myappearance ? myappearance : 0, params );
		}

		bool finish = false;
		while ( !finish && params.optimize )
		{
			finish = true;
			int len = _geometries.size();
			for ( int i = 0; finish && i < len - 2; i++ )
			{
				for ( int j = i+1; finish && j < len - 1; j++ )
				{
					if ( !_geometries[i]->merge( _geometries[j] ) ) continue;
					delete _geometries[j];
					_geometries.erase( _geometries.begin() + j );
					finish = false;
				}
			}
		}
	}*/
	////////////////////////////////////////////////////////////////////////////////
	bool CityObject::IsEmpty()
	{
		_isEmpty = true;

		for (Geometry* geom : _geometries)
		{
			if (geom->getPolygons().size() > 0)
			{
				_isEmpty = false;
				return _isEmpty;
			}
		}

		for (CityObject* obj : _children)
		{
			_isEmpty = obj->IsEmpty();
			if (!_isEmpty)
				return _isEmpty;
		}

		return _isEmpty;
	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::computeEnvelope()
	{
		// compute envelope

		for (Geometry* geom : _geometries) // geometry
		{
			for (Polygon* poly : geom->getPolygons())
			{
				for (const TVec3d& v : poly->getExteriorRing()->getVertices())
				{
					_envelope.merge(v);
				}
			}
		}

		for (CityObject* obj : _children)
		{
			// compute child envelope
			obj->computeEnvelope();

			// update parent envelope
			_envelope.merge(obj->getEnvelope());
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	void CityObject::computeCentroid()
	{

	}
	////////////////////////////////////////////////////////////////////////////////
	std::ostream& operator<<(std::ostream& os, const CityObject& o)
	{
		os << o.getType() << ": " << o.getId() << std::endl;
		os << o.getTypeAsString() << ": " << o.getId() << std::endl;
		os << "  Envelope: " << o.getEnvelope() << std::endl;

		AttributesMap::const_iterator it = o._attributes.begin();
		while (it != o._attributes.end())
		{
			os << "  + " << it->first << ": " << it->second << std::endl;
			it++;
		}

		std::vector< Geometry* >::const_iterator itp = o._geometries.begin();
		for (; itp != o._geometries.end(); itp++)
			os << **itp;

		os << "  * " << o._geometries.size() << " geometries." << std::endl;

		return os;
	}
	////////////////////////////////////////////////////////////////////////////////
	std::string getCityObjectsClassName(CityObjectsTypeMask mask)
	{
#define GETCITYNAME( _t_ ) if ( mask & COT_ ## _t_ ) ss << # _t_ << "|";
		std::stringstream ss;
		GETCITYNAME(GenericCityObject);
		GETCITYNAME(Building);
		GETCITYNAME(BuildingPart);
		GETCITYNAME(Room);
		GETCITYNAME(BuildingInstallation);
		GETCITYNAME(BuildingFurniture);
		GETCITYNAME(Door);
		GETCITYNAME(Window);
		GETCITYNAME(CityFurniture);
		GETCITYNAME(Track);
		GETCITYNAME(Road);
		GETCITYNAME(Railway);
		GETCITYNAME(Square);
		GETCITYNAME(PlantCover);
		GETCITYNAME(SolitaryVegetationObject);
		GETCITYNAME(WaterBody);
		GETCITYNAME(TINRelief);
		GETCITYNAME(LandUse);
		GETCITYNAME(Tunnel);
		GETCITYNAME(Bridge);
		GETCITYNAME(BridgeConstructionElement);
		GETCITYNAME(BridgeInstallation);
		GETCITYNAME(BridgePart);
		GETCITYNAME(RoofSurface);
		GETCITYNAME(WallSurface);
		GETCITYNAME(GroundSurface);
		GETCITYNAME(ClosureSurface);
		GETCITYNAME(FloorSurface);
		GETCITYNAME(InteriorWallSurface);
		GETCITYNAME(CeilingSurface);
#undef GETCITYNAME
		std::string s = ss.str();
		if (s != "") s.erase(s.length() - 1, 1); // remove the last | char
		return s;
	}
	////////////////////////////////////////////////////////////////////////////////
	CityObjectsTypeMask getCityObjectsTypeMaskFromString(const std::string& stringMask)
	{
		CityObjectsTypeMask mask = 0;

		std::vector<std::string> tokens = tokenize(stringMask);

#define COMPARECITYNAMEMASK( _t_ ) {\
bool neg = ( tokens[i][0] == '~' || tokens[i][0] == '!' );\
if ( ci_string_compare( #_t_, neg ? tokens[i].substr(1) : tokens[i] ) ) { mask = neg ? ( mask & (~ COT_ ## _t_ )) : ( mask | COT_ ## _t_ );}\
}

		for (unsigned int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i].length() == 0) continue;

			COMPARECITYNAMEMASK(GenericCityObject);
			COMPARECITYNAMEMASK(Building);
			COMPARECITYNAMEMASK(BuildingPart);
			COMPARECITYNAMEMASK(Room);
			COMPARECITYNAMEMASK(BuildingInstallation);
			COMPARECITYNAMEMASK(BuildingFurniture);
			COMPARECITYNAMEMASK(Door);
			COMPARECITYNAMEMASK(Window);
			COMPARECITYNAMEMASK(CityFurniture);
			COMPARECITYNAMEMASK(Track);
			COMPARECITYNAMEMASK(Road);
			COMPARECITYNAMEMASK(Railway);
			COMPARECITYNAMEMASK(Square);
			COMPARECITYNAMEMASK(PlantCover);
			COMPARECITYNAMEMASK(SolitaryVegetationObject);
			COMPARECITYNAMEMASK(WaterBody);
			COMPARECITYNAMEMASK(TINRelief);
			COMPARECITYNAMEMASK(LandUse);
			COMPARECITYNAMEMASK(Tunnel);
			COMPARECITYNAMEMASK(Bridge);
			COMPARECITYNAMEMASK(BridgeConstructionElement);
			COMPARECITYNAMEMASK(BridgeInstallation);
			COMPARECITYNAMEMASK(BridgePart);
			COMPARECITYNAMEMASK(GenericCityObject);

			COMPARECITYNAMEMASK(WallSurface);
			COMPARECITYNAMEMASK(RoofSurface);
			COMPARECITYNAMEMASK(GroundSurface);
			COMPARECITYNAMEMASK(ClosureSurface);
			COMPARECITYNAMEMASK(FloorSurface);
			COMPARECITYNAMEMASK(InteriorWallSurface);
			COMPARECITYNAMEMASK(CeilingSurface);
			COMPARECITYNAMEMASK(All);
		}
#undef COMPARECITYNAMEMASK
		return mask;
	}
	////////////////////////////////////////////////////////////////////////////////
} // namespace citygml
////////////////////////////////////////////////////////////////////////////////
