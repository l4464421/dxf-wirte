#include"iostream"
#include"DXF.h"
using namespace std;

int main()
{
	Piont p,p1,p2;
	p1.x=0;
	p1.y=0;

	p2.x=200;
	p2.y=200;

	
	DXF dxf("123.dxf");
	dxf.Polygon(p1, 100, 8);
}