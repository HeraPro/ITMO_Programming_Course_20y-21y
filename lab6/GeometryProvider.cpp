#include "RubikCubeController.h"

#ifdef MODE_OPENGL

//-----------------------------------------------------------------------------
// Name: beginRenderText()
// Desc: Utility function for using the bitmap-based character fonts defined 
//       above. Call this function to begin rendering text. Call the function 
//       endRenderText to stop.
//-----------------------------------------------------------------------------

void GeometryProvider::beginRenderText( int nWindowWidth, int nWindowHeight )
{
    // Push back and cache the current state of pixel alignment.
    glPushClientAttrib( GL_CLIENT_PIXEL_STORE_BIT );
    glPixelStorei( GL_UNPACK_SWAP_BYTES, GL_FALSE );
    glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE );
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // Push back and cache the current state of depth testing and lighting
    // and then disable them.
    glPushAttrib( GL_TEXTURE_BIT | GL_DEPTH_TEST | GL_LIGHTING );

    glDisable( GL_TEXTURE_2D );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );

    // Push back the current matrices and go orthographic for text rendering.
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, (double)nWindowWidth, (double)nWindowHeight, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
}

//-----------------------------------------------------------------------------
// Name: endRenderText()
// Desc: Utility function for using the bitmap-based character fonts defined 
//       above. Call this function to stop rendering text. The call to 
//       beginRenderText should come first and be paired with this function.
//-----------------------------------------------------------------------------
void GeometryProvider::endRenderText( void )
{
    // Pop everything back to what ever it was set to before we started 
    // rendering text to the screen.

	
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    glPopClientAttrib();

    glPopAttrib();
}



//-----------------------------------------------------------------------------
// Name: getBitmapFontDataByType()
// Desc: Matches a BitmapFontType with a BitmapFontData structure pointer.
//-----------------------------------------------------------------------------
const BitmapFontData* GeometryProvider::getBitmapFontDataByType( BitmapFontType font )
{
    if( font == BITMAP_FONT_TYPE_HELVETICA_10 )
        return &FontHelvetica10;
    return 0;
}


//-----------------------------------------------------------------------------
// Name: renderText()
// Desc: Utility function for using the bitmap-based character fonts defined 
//       above. This function must be called in between a call to 
//       beginRenderText and endRenderText. See the example below:
//
//       beginRenderText( nWindowWidth, nWindowHeight );
//       {
//           renderText( 5, 10, "This is a test!", BITMAP_FONT_TYPE_HELVETICA_12 );
//       }
//       endRenderText();
//
//-----------------------------------------------------------------------------
void GeometryProvider::renderText( float x, float y, BitmapFontType fontType, char *string )
{
	
    glRasterPos2f( x, y );

    const BitmapFontData *font = getBitmapFontDataByType( fontType );
    const unsigned char* face;
    char *c = '\0';

    for( c = string; *c != '\0'; ++c )
    {
        // Find the character face that we want to draw.
        face = font->Characters[*c-1];

        glBitmap( face[0], font->Height,    // The bitmap's width and height
                  font->xorig, font->yorig, // The origin in the font glyph
                  (float)(face[0]), 0.0,    // The raster advance -- inc. x,y
                  (face+1) );               // The packed bitmap data...
    }
	
}



void GeometryProvider::renderTextFull(float x, float y, char *str)
{
	beginRenderText(800, 600);
	{
		renderText(x, y, BITMAP_FONT_TYPE_HELVETICA_10, str);
	}
	endRenderText();
}

void GeometryProvider::renderSide(struct mycolor *colors )
{
    int i,j,n=0;
	
	glTranslatef((-1.0), -1.0, -0.25);
	double dst = 0.5;

	
	for(i=0; i!=3; i++)
	{
		glPushMatrix();
		{
			glTranslatef(1.0*i, (-dst), 0.0);
			renderGridColor(0.8, colors[n].red, colors[n].green, colors[n].blue);
			n++;
		}
		glPopMatrix();
	}
	for(i=0; i!=3; i++)
	{
		glPushMatrix();
		{
			glTranslatef(1.0*i, (2.0 + dst+0.006), 0.0);
			renderGridColor(0.8, colors[n].red, colors[n].green, colors[n].blue);
			n++;
		}
		glPopMatrix();
	}

	for(j=0; j!=3; j++)
	{
		glPushMatrix();
		{
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, (dst+0.006), 0.0);
		renderGridColor(0.8, colors[n].red, colors[n].green, colors[n].blue);
		glTranslatef(0.0, (-dst-0.006), 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		n++;
		
		for(i=0; i!=3; i++)
		{
			glTranslatef(0.0, 0.0, 0.0);
			renderCubeColor(1.0, 0.5);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glTranslatef(0.0, (dst+0.006), 0.0);
			renderGridColor(0.8, colors[n].red, colors[n].green, colors[n].blue);
			glTranslatef(0.0, (-dst-0.006), 0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			
			
			n++;

			glTranslatef(1.0, 0.0, 0.0);
		}
		
		glRotatef(90.0, 0.0, 0.0, 1.0);
		glTranslatef(0.0, (dst-0.006), 0.0);
		renderGridColor(0.8, colors[n].red, colors[n].green, colors[n].blue);
		glTranslatef(0.0, (-dst+0.006), 0.0);
		glRotatef(-90.0, 0.0, 0.0, 1.0);
		
		n++;

		glTranslatef(-3.0, 1.0, 0.0);
		
		}
		glPopMatrix();
		glTranslatef(0.0, 1.0, 0.0);
		
	}
}

void GeometryProvider::renderSideCells()
{
	int i;
	int j;
	glPushMatrix();
	{
		for(i=0; i!=3; i++)
		{
			for(j=0; j!=3; j++)
			{
				renderCubeColor(0.95, 0.5);
				glTranslatef(0.95, 0.0, 0.0);
			}
			glTranslatef(-(3*0.95), 0.95, 0.0);
		}
	}
	glPopMatrix();
}

void GeometryProvider::renderCubeColor( GLdouble dSize, double color)
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

	double red=0.05;
	double green=0.05;
	double blue=0.05;
    /*
     * PWO: I dared to convert the code to use macros...
     */
    glBegin( GL_QUADS ); glColor3f(red, green, blue); N( 1.0, 0.0, 0.0); V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+); glEnd();
    glBegin( GL_QUADS); glColor3f(red, green, blue); N( 0.0, 1.0, 0.0); V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+); glEnd();
    glBegin( GL_QUADS ); glColor3f(red, green, blue); N( 0.0, 0.0, 1.0); V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+); glEnd();
    glBegin( GL_QUADS); glColor3f(red, green, blue); N(-1.0, 0.0, 0.0); V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-); glEnd();
    glBegin(GL_QUADS); glColor3f(red, green, blue); N( 0.0,-1.0, 0.0); V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+); glEnd();
    glBegin( GL_QUADS ); glColor3f(red, green, blue); N( 0.0, 0.0,-1.0); V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-); glEnd();

#   undef V
#   undef N
}

void GeometryProvider::renderGridColor(GLdouble dSize, double red, double green, double blue)
{
    double size = dSize * 0.5;

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

    /*
     * PWO: I dared to convert the code to use macros...
     */
	double j;
	double y = size;
	double range = 0.05;
	
	glPushMatrix();
	{
		glColor4f(red, green, blue, 1.0); 

		N( 1.0, 0.0, 0.0); 
		
		glBegin(GL_QUADS);
		{
			glVertex3d(y, 0.0, y);
			glVertex3d(y, 0.0, -y);
			glVertex3d(-y, 0.0, -y);
			glVertex3d(-y, 0.0, y);
		}
		glEnd();
	}
	glPopMatrix();
#   undef V
#   undef N
}

void GeometryProvider::renderGrid(float y, float range)
{
	float i,j;

	glColor3f(0.3, 0.3, 0.3);
	for(j=-y; j!=y; j+=range)
	{
		glBegin(GL_LINE_LOOP);
		{
			glVertex3d(j, 0.0, -y);
			glVertex3d(j, 0.0, y);
		}
		glEnd();

		glBegin(GL_LINE_LOOP);
		{
			glVertex3d(-y, 0.0, j);
			glVertex3d(y, 0.0, j);
		}
		glEnd();
					
	}
}



#endif