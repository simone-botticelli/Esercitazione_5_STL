#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
/// Import the polygonal mesh and test if the mesh is correct
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportMesh(PolygonalMesh& mesh);

/// Import the Cell0D properties from Cell0Ds.csv file
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(PolygonalMesh& mesh);

/// Import the Cell1D properties from Cell1Ds.csv file
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(PolygonalMesh& mesh);

/// Import the Cell2D properties from Cell2Ds.csv file
/// mesh: a PolygonalMesh struct
/// return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(PolygonalMesh& mesh);

bool isEqual(const double& x, const double& y);

bool test_mesh(const PolygonalMesh& mesh);

/// Test if markers are correctly stored
bool test_markers(const PolygonalMesh& mesh);

///Test if there are edges with null lenght
bool test_edges_lenght(const PolygonalMesh& mesh);

///Test if there are polygons with null area
bool test_polygons_area(const PolygonalMesh& mesh);
}
