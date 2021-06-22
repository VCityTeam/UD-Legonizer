// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

////////////////////////////////////////////////////////////////////////////////
#ifndef __DATAPROFILE_HPP__
#define __DATAPROFILE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <string>
#include "../CityModel/Vecs.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief The DataProfile class holds informations about a data set
////////////////////////////////////////////////////////////////////////////////
class DataProfile
{
public:
	DataProfile();

	TVec3d m_bboxLowerBound;    ///< lower corner coordinates of data
	TVec3d m_bboxUpperBound;    ///< upper corner coordinates of data
	TVec3d m_offset;            ///< data offset (used to avoid big coordinates and
	float m_xStep;              ///< tile width
	float m_yStep;              ///< tile height
	int m_TileIdOriginX;        ///< tile id at the X origin
	int m_TileIdOriginY;        ///< tile id at the X origin
	// data origin : vec3
	// data offset : vec3
	// tile x size
	// tile y size
	// file prefix
	// file suffix
	// file ordering convention
	// srs -> proj string format ?

	// citygml
	// ign data

	std::string m_dataPathCityGML;  ///< default path for CityGML data
	int m_id;                   ///< id of the data profile
	std::string m_name;         ///< name of the data profile
	float  getTileWidth() const;
	float  getTileHeight() const;
	double getTileXOffset() const;
	double getTileYOffset() const;

	////////////////////////////////////////////////////////////////////////////////
	// default data profile
	static DataProfile createDataProfileDefault();
	static DataProfile createDataProfileNone();
	static DataProfile createDataProfileLyon();
	////////////////////////////////////////////////////////////////////////////////
private:
};

#endif // __DATAPROFILE_HPP__
