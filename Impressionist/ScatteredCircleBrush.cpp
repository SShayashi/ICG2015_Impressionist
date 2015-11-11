//
// ScatteredCircleBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredCircleBrush.h"
#include <math.h>
#define PI 3.1415

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	//スライダーつけたあと

	if ( pDoc == NULL ) {
		printf( "ScatteredCircleBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	int size=pDoc->getSize();
	float Ax,Ay,TGx,TGy,RandomX,RandomY;
	int div = 12;
	float radius = size/2.0;

	for(int i=0; i < 4 ; i++){
		glBegin(GL_POLYGON);
		SetColor(source);
		RandomX = (rand()%size - size/2)*3;
		RandomY = (rand()%size - size/2)*3;

		TGx = target.x + RandomX;
		TGy = target.y + RandomY;

		for (int j = 0 ; j < div ; j++){
			Ax = TGx + radius*cos(2*PI*j/div);
			Ay = TGy + radius*sin(2*PI*j/div);
			glVertex2f(Ax,Ay);
		}
		glEnd();
	}
}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	glDisable(GL_BLEND);

}

