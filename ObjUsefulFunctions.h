#ifndef OBJ_USEFUL_FUNCTIONS_H
#define OBJ_USEFUL_FUNCTIONS_H

#include <map>
#include <string>
#include <vector>
#include "Vec3.h"
#include "Vec2.h"


// Useful types
// ------------

// Face type - assumes all faces are triangles,
//  so is most efficient.
struct Face
{
	Face();

	// only triangles are allowed!
	int m_pointIndex[3];
	int m_normalIndex[3];
	int m_uvIndex[3];
};

typedef std::vector<Face> Faces;

// Group - has name, material name and collection of faces.
struct Group
{
    std::string m_name;
    std::string m_materialName;
    Faces m_faces;    
};

// Map of group name to group object
typedef std::map<std::string, Group> Groups;

// Other useful typedefs for collections
typedef std::vector<Vec3f> Vecs;
typedef std::vector<Vec2f> UVs;
typedef std::vector<std::string> Strings;


// Useful functions
// ----------------

// Strip whitespace from beginning and end of string
void Trim(std::string* ps);

// Split string cs into a vector of strings.
// Character c is used to split the strings.
// Strings in the result vector do not include the c character.
Strings Split(const std::string& cs, char c);

// Convert a string to a float
float ToFloat(const std::string& s);

// Convert a string to an int
int ToInt(const std::string& s);

// Convert a vector of four strings to a Vec3. 
// The zeroth string is ignored. Strings 1, 2 & 3 are
//  asssumed to be floats.
Vec3f ToVec3(const Strings& strs);

// Convert a vector of three strings to a Vec2. 
// The zeroth string is ignored. Strings 1 & 2 are
//  asssumed to be floats.
Vec2f ToVec2(const Strings& strs);

// Convert a vector of strings to a Face.
// The zeroth string is ignored. We only use the first 
//  three vertices.
void ToFace(const Strings& fstrs, Face* f);


#endif

