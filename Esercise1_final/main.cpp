#include <iostream>
#include "TriangularMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"

using namespace std;
using namespace Eigen;
using namespace TriangularLibrary;

int main()
{
    TriangularMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }

    /// Per visualizzare online le mesh:
    /// 1. Convertire i file .inp in file .vtu con https://meshconverter.it/it
    /// 2. Caricare il file .vtu su https://kitware.github.io/glance/app/

    Gedim::UCDUtilities utilities;
    {
        vector<Gedim::UCDProperty<double>> cell0Ds_properties(1);

        cell0Ds_properties[0].Label = "Marker";
        cell0Ds_properties[0].UnitLabel = "-";
        cell0Ds_properties[0].NumComponents = 1;

        vector<double> cell0Ds_marker(mesh.NumCell0Ds, 0.0);
        for(const auto &m : mesh.MarkerCell0Ds)
            for(const unsigned int id: m.second)
                cell0Ds_marker.at(id) = m.first;

        cell0Ds_properties[0].Data = cell0Ds_marker.data();

        utilities.ExportPoints("./Cell0Ds.inp",
                               mesh.Cell0DsCoordinates,
                               cell0Ds_properties);
    }

    {

        vector<Gedim::UCDProperty<double>> cell1Ds_properties(1);

        cell1Ds_properties[0].Label = "Marker";
        cell1Ds_properties[0].UnitLabel = "-";
        cell1Ds_properties[0].NumComponents = 1;

        vector<double> cell1Ds_marker(mesh.NumCell1Ds, 0.0);
        for(const auto &m : mesh.MarkerCell1Ds)
            for(const unsigned int id: m.second)
                cell1Ds_marker.at(id) = m.first;

        cell1Ds_properties[0].Data = cell1Ds_marker.data();

        utilities.ExportSegments("./Cell1Ds.inp",
                                 mesh.Cell0DsCoordinates,
                                 mesh.Cell1DsExtrema,
                                 {},
                                 cell1Ds_properties);
    }

    return 0;
}
