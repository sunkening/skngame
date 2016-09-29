// ASCFile.cpp: implementation of the ASCFile class.
//
//////////////////////////////////////////////////////////////////////

#include "ASCFile.h"
#include "g3dlib.h"
#include "Parser.h"
#include "LOG.h"
#include "GColor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ASCFile::ASCFile()
{

}

ASCFile::~ASCFile()
{

}

int ASCFile::load(G3DObjectIndex* obj, char *filename, GVector4D* scale, GVector4D* pos, GVector4D* rot, int vertex_flags/*=0*/)
{
	// create a parser object
CParser parser; 

char seps[16];          // seperators for token scanning
char token_buffer[256]; // used as working buffer for token
char *token;            // pointer to next token

int r,g,b;              // working colors


// Step 1: clear out the object and initialize it a bit
//memset(obj, 0, sizeof(OBJECT4DV1));

// set state of object to active and visible
obj->state = OBJECT4DV1_STATE_ACTIVE | OBJECT4DV1_STATE_VISIBLE;

// set position of object is caller requested position
if (pos)
   {
   // set position of object
   obj->worldPosition.x = pos->x;
   obj->worldPosition.y = pos->y;
   obj->worldPosition.z = pos->z;
   obj->worldPosition.w = pos->w;
   } // end 
else
   {
   // set it to (0,0,0,1)
   obj->worldPosition.x = 0;
   obj->worldPosition.y = 0;
   obj->worldPosition.z = 0;
   obj->worldPosition.w = 1;
   } // end else

// Step 2: open the file for reading using the parser
if (!parser.open(filename))
   {
	//LOG::e("Couldn't open .ASC file %s.", filename);
	return(0);
   } // end if

// Step 3: 
 
// lets find the name of the object first 
while(1)
     {
     // get the next line, we are looking for "Named object:"
     if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
        {
		 LOG::wirtError("Image 'name' not found in .ASC file %s.", filename);
        return(0);
        } // end if
    
     // check for pattern?  
     if (parser.patternMatch(parser.buffer, "['Named'] ['object:']"))
        {
        // at this point we have the string with the name in it, parse it out by finding 
        // name between quotes "name...."
        strcpy(token_buffer, parser.buffer);
        strcpy(seps, "\"");        
        strtok( token_buffer, seps );
        
        // this will be the token between the quotes
        token = strtok(NULL, seps);
      
        // copy name into structure
        strcpy(obj->name, token);          


        break;    
        } // end if

     } // end while

// step 4: get number of vertices and polys in object
while(1)
     {
     // get the next line, we are looking for "Tri-mesh, Vertices:" 
     if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
        {
		 LOG::wirtError("'Tri-mesh' line not found in .ASC file %s.", filename);
        return(0);
        } // end if
    
     // check for pattern?  
     if (parser.patternMatch(parser.buffer, "['Tri-mesh,'] ['Vertices:'] [i] ['Faces:'] [i]"))
        {
        // simply extract the number of vertices and polygons from the pattern matching 
        // output arrays
        obj->numVertices = parser.pints[0];
        obj->numPolys    = parser.pints[1];


        break;    
 
        } // end if

     } // end while

// Step 5: load the vertex list

// advance parser to vertex list denoted by:
// "Vertex list:"
while(1)
     {
     // get next line
     if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
        {
        LOG::wirtError("\n'Vertex list:' line not found in .ASC file %s.", filename);
        return(0);
        } // end if
    
     // check for pattern?  
     if (parser.patternMatch(parser.buffer, "['Vertex'] ['list:']"))
        {
        LOG::wirtError("\nASC Reader found vertex list in .ASC file %s.", filename);
        break;
        } // end if
     } // end while

// now read in vertex list, format:
// "Vertex: d  X:d.d Y:d.d  Z:d.d"
 for (int vertex = 0; vertex < obj->numVertices; vertex++)
     {
     // hunt for vertex
     while(1)
     {
     // get the next vertex
     if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
        {
        LOG::wirtError("\nVertex list ended abruptly! in .ASC file %s.", filename);
        return(0);
        } // end if
    
     // strip all ":XYZ", make this easier, note use of input and output as same var, this is legal
     // since the output is guaranteed to be the same length or shorter as the input :)
     StripChars(parser.buffer, parser.buffer, ":XYZ");
     
     // check for pattern?  
     if (parser.patternMatch(parser.buffer, "['Vertex'] [i] [f] [f] [f]"))
        {
        // at this point we have the x,y,z in the the pfloats array locations 0,1,2
        obj->vlistLocal[vertex].x = parser.pfloats[0];
        obj->vlistLocal[vertex].y = parser.pfloats[1];
        obj->vlistLocal[vertex].z = parser.pfloats[2];
        obj->vlistLocal[vertex].w = 1;

        // do vertex swapping right here, allow muliple swaps, why not!
        // defines for vertex re-ordering flags

        //#define VERTEX_FLAGS_INVERT_X   1    // inverts the Z-coordinates
        //#define VERTEX_FLAGS_INVERT_Y   2    // inverts the Z-coordinates
        //#define VERTEX_FLAGS_INVERT_Z   4    // inverts the Z-coordinates
        //#define VERTEX_FLAGS_SWAP_YZ    8    // transforms a RHS model to a LHS model
        //#define VERTEX_FLAGS_SWAP_XZ    16   // ???
        //#define VERTEX_FLAGS_SWAP_XY    32
        //#define VERTEX_FLAGS_INVERT_WINDING_ORDER 64  // invert winding order from cw to ccw or ccw to cc

        float temp_f; // used for swapping

        // invert signs?
        if (vertex_flags & VERTEX_FLAGS_INVERT_X)
           obj->vlistLocal[vertex].x=-obj->vlistLocal[vertex].x;

        if (vertex_flags & VERTEX_FLAGS_INVERT_Y)
           obj->vlistLocal[vertex].y=-obj->vlistLocal[vertex].y;

        if (vertex_flags & VERTEX_FLAGS_INVERT_Z)
           obj->vlistLocal[vertex].z=-obj->vlistLocal[vertex].z;

        // swap any axes?
        if (vertex_flags & VERTEX_FLAGS_SWAP_YZ)
           SWAP(obj->vlistLocal[vertex].y, obj->vlistLocal[vertex].z, temp_f);
        
        if (vertex_flags & VERTEX_FLAGS_SWAP_XZ)
           SWAP(obj->vlistLocal[vertex].x, obj->vlistLocal[vertex].z, temp_f);

        if (vertex_flags & VERTEX_FLAGS_SWAP_XY)
           SWAP(obj->vlistLocal[vertex].x, obj->vlistLocal[vertex].y, temp_f);

 

        // scale vertices
        if (scale)
           {
           obj->vlistLocal[vertex].x*=scale->x;
           obj->vlistLocal[vertex].y*=scale->y;
           obj->vlistLocal[vertex].z*=scale->z;
           } // end if

        // found vertex, break out of while for next pass
        break;

        } // end if

    } // end while

    } // end for vertex

// compute average and max radius

obj->cumputeRadius();
// step 6: load in the polygons
// poly list starts off with:
// "Face list:"
while(1)
     {
     // get next line
     if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
        {
        LOG::wirtError("\n'Face list:' line not found in .ASC file %s.", filename);
        return(0);
        } // end if
    
     // check for pattern?  
     if (parser.patternMatch(parser.buffer, "['Face'] ['list:']"))
        {
        LOG::wirtError("\nASC Reader found face list in .ASC file %s.", filename);
        break;
        } // end if
     } // end while

// now read each face in format:
// Face ddd:    A:ddd B:ddd C:ddd AB:1|0 BC:1|0 CA:1|
// Material:"rdddgdddbddda0"
// the A, B, C part is vertex 0,1,2 but the AB, BC, CA part
// has to do with the edges and the vertex ordering
// the material indicates the color, and has an 'a0' tacked on the end???

int  poly_surface_desc = 0; // ASC surface descriptor/material in this case
int  poly_num_verts    = 0; // number of vertices for current poly (always 3)
char tmp_string[8];         // temp string to hold surface descriptor in and
                            // test if it need to be converted from hex

for (int poly=0; poly < obj->numPolys; poly++)
{ 
    // hunt until next face is found
    while(1)
    {
    // get the next polygon face
    if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
       {
       LOG::wirtError("\nface list ended abruptly! in .ASC file %s.", filename);
       return(0);
       } // end if
    
    // strip all ":ABC", make this easier, note use of input and output as same var, this is legal
    // since the output is guaranteed to be the same length or shorter as the input :)
    StripChars(parser.buffer, parser.buffer, ":ABC");
    
    // check for pattern?  
    if (parser.patternMatch(parser.buffer, "['Face'] [i] [i] [i] [i]"))
       { 
       // at this point we have the vertex indices in the the pints array locations 1,2,3, 
       // 0 contains the face number

       // insert polygon, check for winding order invert
       if (vertex_flags & VERTEX_FLAGS_INVERT_WINDING_ORDER)
          {    
          poly_num_verts = 3;
          obj->plist[poly].vert[0] = parser.pints[3];
          obj->plist[poly].vert[1] = parser.pints[2];
          obj->plist[poly].vert[2] = parser.pints[1];
          } // end if
       else
          { // leave winding order alone

          poly_num_verts           = 3;
          obj->plist[poly].vert[0] = parser.pints[1];
          obj->plist[poly].vert[1] = parser.pints[2];
          obj->plist[poly].vert[2] = parser.pints[3];
          } // end else

       // point polygon vertex list to object's vertex list
       // note that this is redundant since the polylist is contained
       // within the object in this case and its up to the user to select
       // whether the local or transformed vertex list is used when building up
       // polygon geometry, might be a better idea to set to NULL in the context
       // of polygons that are part of an object
       obj->plist[poly].vlist = obj->vlistLocal; 
  
       // found the face, break out of while for another pass
       break;

       } // end if
 
     } // end while      
 
    // hunt until next material for face is found
    while(1)
    { 
    // get the next polygon material (the "page xxx" breaks mess everything up!!!)
    if (!parser.getLine(PARSER_STRIP_EMPTY_LINES | PARSER_STRIP_WS_ENDS))
       {
       LOG::wirtError("\nmaterial list ended abruptly! in .ASC file %s.", filename);
       return(0);
       } // end if
    
    // Material:"rdddgdddbddda0"
    // replace all ':"rgba', make this easier, note use of input and output as same var, this is legal
    // since the output is guaranteed to be the same length or shorter as the input :)
    // the result will look like:
    // "M t ri l   ddd ddd ddd 0" 
    // which we can parse!
    ReplaceChars(parser.buffer, parser.buffer, ":\"rgba", ' ');
     
    // check for pattern?  
    if (parser.patternMatch(parser.buffer, "[i] [i] [i]"))
       { 
       // at this point we have the red, green, and blue components in the the pints array locations 0,1,2, 
       r = parser.pints[0];
       g = parser.pints[1];
       b = parser.pints[2];

       // set all the attributes of polygon as best we can with this format
       // SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_2SIDED);
    
       // we need to know what color depth we are dealing with, so check
       // the bits per pixel, this assumes that the system has already
       // made the call to DDraw_Init() or set the bit depth
 
          // cool, 16 bit mode
          SET_BIT(obj->plist[poly].attr,POLY4DV1_ATTR_RGB24);
          obj->plist[poly].color = GColor::RGB_(r, g, b);
 

       // for now manually set shading mode
       //SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_PURE);
       //SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_GOURAUD);
       //SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_PHONG);
       SET_BIT(obj->plist[poly].attr, POLY4DV1_ATTR_SHADE_MODE_FLAT);

       // set polygon to active
       obj->plist[poly].state = POLY4DV1_STATE_ACTIVE;    
       
       // found the material, break out of while for another pass
       break;

       } // end if
 
     } // end while      


 
    } // end for poly

// return success
return(1);
}
