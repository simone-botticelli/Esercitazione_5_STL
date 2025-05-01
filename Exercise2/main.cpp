#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Eigen>
#include <cmath>

#include "PolygonalMesh.hpp"
#include "Utils.hpp"      
#include "UCDUtilities.hpp" 
 


using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;
using namespace Gedim;
int main()
{
    PolygonalMesh mesh;
    if (!ImportMesh(mesh))
    {
	    cerr << "file not found" << endl;
	    return 1;
    }
    
    UCDUtilities utilities;
	utilities.ExportPoints("./Cell0Ds.inp",
						   mesh.Cell0DsCoordinates);    
    
    utilities.ExportSegments("./Cell1Ds.inp",
							 mesh.Cell0DsCoordinates,
							 mesh.Cell1DsExtrema);
                                 
                                 
    return 0;
}
