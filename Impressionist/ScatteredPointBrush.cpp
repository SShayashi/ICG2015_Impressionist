//
// ScatteredPointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredPointBrush.h"
#include <math.h>
#define PI 3.1415

extern float frand();

ScatteredPointBrush::ScatteredPointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredPointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredPointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	//ƒXƒ‰ƒCƒ_[‚Â‚¯‚½‚ ‚Æ

	if ( pDoc == NULL ) {
		printf( "ScatteredPointBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	int size=pDoc->getSize();
	int angle=pDoc->getAngle();	// ŒX‚«iAnglej‚ðŽæ“¾
	int width = pDoc->getWidth();
	float Ax,Ay,Bx,By,Cx,Cy,Dx,Dy;

	//
	if(width <= 1){

		Ax=target.x+size*cos(PI*angle/180);
		Ay=target.y+size*sin(PI*angle/180);

		Bx=target.x-size*cos(PI*angle/180);
		By=target.y-size*sin(PI*angle/180);
	
		glBegin(GL_LINES);		// ü‚ð•`‰æ
		SetColor( source );
		glVertex2d(Ax,Ay);
		glVertex2d(Bx,By);

	}else{

		Ax=target.x+size*cos(PI*angle/180)-(width/2)*sin(PI*angle/180);
		Ay=target.y+size*sin(PI*angle/180)+(width/2)*cos(PI*angle/180);

		Dx=target.x+size*cos(PI*angle/180)+(width/2)*sin(PI*angle/180);
		Dy=target.y+size*sin(PI*angle/180)-(width/2)*cos(PI*angle/180);


		Bx=target.x-size*cos(PI*angle/180)-(width/2)*sin(PI*angle/180);
		By=target.y-size*sin(PI*angle/180)+(width/2)*cos(PI*angle/180);
	
		Cx=target.x-size*cos(PI*angle/180)+(width/2)*sin(PI*angle/180);
		Cy=target.y-size*sin(PI*angle/180)-(width/2)*cos(PI*angle/180);

	
		glBegin(GL_POLYGON);		// ü‚ð•`‰æ
		SetColor( source );
		glVertex2d(Ax,Ay);
		glVertex2d(Bx,By);
		glVertex2d(Cx,Cy);
		glVertex2d(Dx,Dy);	

	}

	glEnd();
}

void ScatteredPointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	glDisable(GL_BLEND);

}

