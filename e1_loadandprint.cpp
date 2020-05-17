// Example 1: Load and Print
//
// Load the data from the .obj then print it into a file
//	called e1Out.txt


#include <time.h>

// Iostream - STD I/O Library
#include <iostream>

// fStream - STD File I/O Library
#include <fstream>

// OBJ_Loader - .obj Loader
#include "OBJ_Loader.h"


#include <cstdlib>


// Main function
int main(int argc, char* argv[])
{
	// Initialize Loader
	objl::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile("labirinto.obj");

	// Check to see if it loaded

	srand(time(0));


	// If so continue
	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream file("main.txt");

		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = Loader.LoadedMeshes[i];


			float cor = (float) rand() / RAND_MAX;



			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			file << "Vertices \n";

			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{

				file << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ", \n";


			}

			file << "Cor : \n";

			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				file << 0.59 << ", " << 0.29 << ", " << 0 << ", \n";
			}


			file << "Size:" << curMesh.Vertices.size() << "\n";
		}

		// Close File
		file.close();
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("main.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}

	// Exit the program
	return 0;
}