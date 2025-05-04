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


int main()
{
    PolygonalMesh mesh;
    if (!ImportMesh(mesh))
    {
	    cerr << "file not found" << endl;
	    return 1;
    }
    
    Gedim::UCDUtilities utilities;
    {
        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates,
                               {},
                               mesh.MarkerCell0Ds);
    }

    {
        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {},
                                 {},
                                 mesh.MarkerCell1Ds);
    }
    
    std::cout << "Running mesh tests...\n";
    if (!test_mesh(mesh))
    	cerr << "Test failed!\n" ;
    
    else
    	std::cout << "All tests passed!\n";
    
    

    
    return 0;
}
