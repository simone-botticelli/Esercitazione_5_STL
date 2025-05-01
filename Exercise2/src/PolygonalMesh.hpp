#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

namespace PolygonalLibrary {
	struct PolygonalMesh{
		unsigned int NumCell0Ds = 0; ///< number of Cell0D
		vector<unsigned int> Cell0DsId = {}; ///< Cell0D id, size 1 x NumberCell0D
		MatrixXd Cell0DsCoordinates = {}; ///< Cell0D coordinates, size 2 x NumberCell0D (x,y)
		map<unsigned int, list<unsigned int>> MarkerCell0Ds = {}; ///< Cell0D markers
	
		unsigned int NumCell1Ds = 0; ///< number of Cell1D
		vector<unsigned int> Cell1DsId = {}; ///< Cell1D id, size 1 x NumberCell1D
		MatrixXi Cell1DsExtrema = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
		map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; ///< Cell1D properties
		
		unsigned int NumCell2Ds = 0; ///< number of Cell2D
		vector<unsigned int> Cell2DsId = {}; ///< Cell2D id, size 1 x NumberCell2D
		vector<vector<unsigned int>> Cell2DsVertices = {}; ///< Cell2D Vertices indices, size 1 x NumberCell2DVertices[NumberCell2D]
		vector<vector<unsigned int>> Cell2DsEdges = {}; ///< Cell2D Cell1D indices, size 1 x NumberCell2DEdges[NumberCell2D]
		map<unsigned int, list<unsigned int>> MarkerCell2Ds = {}; ///< Cell2D properties
	};
}