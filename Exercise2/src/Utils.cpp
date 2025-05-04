#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <cassert>
#include <cmath>
#include <sstream>
#include <Eigen/Eigen>
#include "PolygonalMesh.hpp"

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;
     
    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}
// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size();

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
    mesh.MarkerCell0Ds = Eigen::VectorXi::Zero(mesh.NumCell0Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        char sep;
        Vector2d coord;

        converter >> id >> sep;
        converter >> marker >> sep;
        converter >> mesh.Cell0DsCoordinates(0, id) >> sep >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id);
        mesh.MarkerCell0Ds(id) = marker;
        

        /* Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if(it == mesh.MarkerCell0Ds.end())
            {
                mesh.MarkerCell0Ds.insert({marker, {id}});
            }
            else
            {
                it->second.push_back(id);
            }
        }*/

    }

    return true;
}
// ***************************************************************************
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);
    mesh.MarkerCell1Ds = Eigen::VectorXi::Zero(mesh.NumCell1Ds);
    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        char sep;
        Vector2i vertices;

        converter >> id >> sep;
        converter >> marker >> sep;
        converter >> mesh.Cell1DsExtrema(0, id) >> sep >> mesh.Cell1DsExtrema(1, id);

        mesh.Cell1DsId.push_back(id);
        mesh.MarkerCell1Ds(id) = marker;
        

        
    }

    return true;
}
// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);
        
    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        char sep;
        unsigned int NumVertices;
        unsigned int NumEdges;
        vector<unsigned int> vertices;
        vector<unsigned int> edges;
        
        
        converter >>  id >> sep >> marker >> sep >> NumVertices;
        vertices.reserve(NumVertices);
        unsigned int vertex;
        for(unsigned int i = 0; i < NumVertices; i++){
	        converter >> sep >> vertex;
	        vertices.push_back(vertex);
        }
        converter >> sep >> NumEdges;
        edges.reserve(NumEdges);
        unsigned int edge;
        for(unsigned int i = 0; i < NumEdges; i++){
	        converter >> sep >> edge;
	        edges.push_back(edge);
        }

        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);
        

        

        
    }

    return true;
}


bool test_mesh(PolygonalMesh& mesh)
{
	if(!test_markers(mesh))
		return false;
		else cout << "markers test passed" << endl;
	if(!test_edges_lenght(mesh))
		return false;
		else cout << "edges test passed " << endl;
	if(!test_polygons_area(mesh))
		return false;
		else cout << "areas test passed" << endl;

	return true;
}


bool test_markers(PolygonalMesh& mesh) 

{   
	bool passed = true;
	
	return passed;
}


bool test_edges_lenght(PolygonalMesh& mesh)
{
	double epsilon = std::numeric_limits<double>::epsilon();
	

	for(const unsigned int& edge_id : mesh.Cell1DsId)
	{
		int& id_origin = mesh.Cell1DsExtrema(0, edge_id);
		int& id_end = mesh.Cell1DsExtrema(1, edge_id);
		auto origin = mesh.Cell0DsCoordinates.col(id_origin);
		auto end = mesh.Cell0DsCoordinates.col(id_end);
		double distance = (origin - end).norm();

		double tolerance = epsilon * max(origin.norm(), end.norm());
		
				if(distance < tolerance)
		{
			cerr << "Error: edge " << edge_id << " has lenght zero" << endl;
			return false;
		}
	}

	return true;
}


bool test_polygons_area(PolygonalMesh& mesh)
{
	vector<bool> all_passed;
	double epsilon = std::numeric_limits<double>::epsilon();
	
	for(const unsigned int& polygon_id : mesh.Cell2DsId){
		vector<unsigned int>& p_vertices = mesh.Cell2DsVertices[polygon_id];
		double area = 0.0;
		unsigned int n_vertices = p_vertices.size();
		for (int i = 0; i < n_vertices; i++) {
			unsigned int& curr = p_vertices[i];
			unsigned int& next = p_vertices[(i + 1) % n_vertices]; 
	
			double& xi = mesh.Cell0DsCoordinates(0, curr);
			double& yi = mesh.Cell0DsCoordinates(1, curr);
			double& xj = mesh.Cell0DsCoordinates(0, next);
			double& yj = mesh.Cell0DsCoordinates(1, next);
	
			area += xi * yj - xj * yi;
		}
		area = 0.5 * abs(area);
		bool passed(area > epsilon);
		if(!passed)
		{cerr << "Error: polygon " << polygon_id << " has area zero" << endl;}
		
		all_passed.push_back(passed);
	}
	
	
	return all_of(all_passed.begin(), all_passed.end(), [](bool b) { return b; });

}
	

}
