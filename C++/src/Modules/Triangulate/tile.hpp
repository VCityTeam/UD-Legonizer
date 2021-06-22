// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

////////////////////////////////////////////////////////////////////////////////
#ifndef __TILE_HPP__
#define __TILE_HPP__

#include <memory>
#include <map>
#include "../../CityModel/CityGML.hpp"
#include "../../CityModel/URI.hpp"

#ifdef _MSC_VER
#pragma warning(disable: 4251) // VC++ DLL jejune complains on STL _Id member
#endif

namespace vcity
{

/// \brief The Tile class
/// Holds citygml, shp data
class Tile
{
public:
  Tile();

  /// Build a tile and load a CityGML file
  /// \param filepath CityGML file pathe(const std::s
  Tile(const std::string& filepath);
  //Tile(const TVec3d& pMin, const TVec3d& pMax);
  ~Tile();

  /// Get tile enveloppe
  citygml::Envelope& getEnvelope();
  const citygml::Envelope& getEnvelope() const;

  /// Compute envoloppe
  void computeEnvelope();

  void loadT(const std::string& filepath);
  //osg::ref_ptr<osg::Node> buildOsgData();

  citygml::CityModel* getCityModel();
  const citygml::CityModel* getCityModel() const;

  /// Get tile name
  const std::string& getName() const;

  /// Set tile name
  void setName(const std::string& name);
  //osg::ref_ptr<osg::Node> getOsgRoot();

  //citygml::CityObject* findNode(const std::string& name);

  void deleteNode(const std::string& name);
  void insertNode(citygml::CityObject* node);
  void replaceNode(const std::string& name, citygml::CityObject* node);

  /// \brief getNode Get a CityGML node
  /// \param uri URI pointing to the CityGML node
  /// \return Ptr to CityGML node or nullptr
  citygml::CityObject* getNode(const URI& uri, bool inPickingMode = false);

  /// Get the path of the CityGML file loaded
  const std::string& getCityGMLfilePath() const;

private:
  std::string m_name;             ///< tile name
  std::string m_citygmlFilePath;  ///< Path of the CityGML file loaded

  citygml::CityModel* m_root; // TODO : remove
};

typedef std::shared_ptr<Tile> TilePtr;

} // namespace vity

#endif // __TILE_HPP__
