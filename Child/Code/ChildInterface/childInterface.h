//-*-c++-*-

/**************************************************************************/
/**
**  @file ChildInterface.h
**
**  @brief Header file for the general interface to CHILD.
**
**    This is the header file for ChildInterface, which
**    provides a generalized, OpenMI-style interface to the CHILD
**    landscape evolution model.
**
**  The first version is really just a sketch.
**
**  For information regarding this program, please contact Greg Tucker at:
**
**     Cooperative Institute for Research in Environmental Sciences (CIRES)
**     and Department of Geological Sciences
**     University of Colorado
**     2200 Colorado Avenue, Campus Box 399
**     Boulder, CO 80309-0399
**
*/
/**************************************************************************/

#ifndef CHILDINTERFACE_H
#define CHILDINTERFACE_H

#include <string>
#include <sstream>
#include <vector>
#include "../trapfpe.h"
#include "../Inclusions.h"
#include "../tFloodplain/tFloodplain.h"
#include "../tStratGrid/tStratGrid.h"
#include "../tEolian/tEolian.h"
#include "../tOption/tOption.h"

#include "../tMeshList/tMeshList.h"

using namespace std;

// A type definition to implement OpenMI IElement interface
enum ElementType
{
	IDBased,
	XYPoint,
	XYLine,
	XYPolyLine,
	XYPolygon,
	XYZPoint,
	XYZLine,
	XYZPolyLine,
	XYZPolygon,
	XYZPolyhedron
};

//Predicates predicate;

/**************************************************************************/
/**
**  Class childInterface
**
**  The class childInterface acts as a copy of CHILD, providing access
**  to it via methods to Initialize, RunOneStorm, Run (for a given
**  duration as given as an argument or in an input file), and CleanUp.
*/
/**************************************************************************/
class childInterface
{
public:
	// Public methods
	childInterface();
	void Initialize( int argc, char **argv );
	double RunOneStorm();
	void Run( double run_duration );
	void CleanUp();
	~childInterface();
  void ExternalErosionAndDeposition( vector<double> dz );
	
	// Public methods that implement the OpenMI IElement interface
	string getID();
	string getDescription();
	//Question: how to handle ISpatialReference? what type is it? do I define such a class?
	ElementType getElementType();
	int getElementCount();
	int getVersion();
	int GetElementIndex( string elementID );
	string GetElementID( int element_index );
	int GetVertexCount( int element_index );
	int GetFaceCount( int element_index );
	vector<int> GetFaceVertexIndices( int element_index, int face_index );
	double GetXCoordinate( int element_index, int vertex_index );
	double GetYCoordinate( int element_index, int vertex_index );
	double GetZCoordinate( int element_index, int vertex_index );
	
		
private:
	// Private data
	bool initialized;      // Flag indicated whether model has been initialized
	bool optDetachLim,      // Option for detachment-limited erosion only
        optFloodplainDep,  // Option for floodplain (overbank) deposition
        optLoessDep,       // Option for eolian deposition
        optVegetation,     // Option for dynamic vegetation cover
        optMeander,        // Option for stream meandering
        optDiffuseDepo,    // Option for deposition / no deposition by diff'n
        optStratGrid,      // Option to enable stratigraphy grid
		optNonlinearDiffusion; // Option for nonlinear creep transport
	tRand *rand;             // -> random number generator
	tMesh<tLNode> *mesh;        // -> mesh object
	tLOutput<tLNode> *output;   // -> output handler
	tStorm *storm;              // -> storm generator
	tStreamNet *strmNet;	    // -> stream network module
	tErosion *erosion;          // -> erosion module
	tUplift *uplift;            // -> uplift/baselevel module
	tRunTimer *time;             // -> run timer
	
	tVegetation *vegetation;  // -> vegetation object
	tFloodplain *floodplain;  // -> floodplain object
	tStratGrid *stratGrid;     // -> Stratigraphy Grid object
	tEolian *loess;           // -> eolian deposition object
	tStreamMeander *strmMeander; // -> stream meander object
	//Predicates predicate;   // Math-related stuff
	
	// Private data for implementing OpenMI IElement interface
	string element_set_id;
	string element_set_description;
	int version;
	
	
	
};


#endif