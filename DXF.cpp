#include "DXF.h"

DXF::DXF(std::string a)
{
	static std::ofstream myf(a);
	fp = &myf;

	myf << "0\nSECTION\n";
	myf << "2\nENTITIES\n";
}
DXF::~DXF()
{
	*fp << "0 \nENDSEC\n";
	*fp << "0 \nEOF";
	fp->close();
}

void DXF::L(Piont start, Piont end)
{
	*fp<<"0 \nLINE\n";
	*fp<<"8 \n0\n";
	*fp<<"62 \n0\n";
	*fp<<"10 \n"<<start.x<<"\n20 \n"<<start.y<<"\n11 \n"<<end.x<<"\n21 \n"<<end.y<<"\n";
}
void DXF::C(Piont center,double radius)
{
	*fp << "0 \nCIRCLE\n";
	*fp<<"8 \n0\n";
	*fp<<"62 \n0\n";
	*fp<<"10 \n"<<center.x<<"\n20 \n"<<center.y<<"\n40 \n"<<radius<<"\n";
}
void DXF::ARC(Piont center,double radius,double start, double end)
{
	*fp << "0 \nARC\n";
	*fp<<"8 \n0\n";
	*fp<<"62 \n0\n";
	*fp<<"10 \n"<<center.x<<"\n20 \n"<<center.y<<"\n40 \n"<<radius<<"\n50 \n"<<start<<"\n51 \n"<<end<<"\n";
}
int DXF::ARC(Piont Center,Piont start, Piont end)
{
	double jiaodu1,jiaodu2;
	float  banjin,banjin2;
	banjin=(float)sqrt((start.y-Center.y)*(start.y-Center.y)+(start.x-Center.x)*(start.x-Center.x));
	banjin2=(float)sqrt((end.y-Center.y)*(end.y-Center.y)+(end.x-Center.x)*(end.x-Center.x));
	if(banjin!=banjin2)
	{
		return -1;
	}

	jiaodu1=atan2((start.y-Center.y),(start.x-Center.x));
	jiaodu2=atan2((end.y-Center.y),(end.x-Center.x));
	if(jiaodu1>0)
	{
		jiaodu1=jiaodu1/PI*180;
	}
	else
	{
		jiaodu1=360+jiaodu1/PI*180;
	}

	if(jiaodu2>0)
	{
		jiaodu2=jiaodu2/PI*180;
	}
	else
	{
		jiaodu2=360+jiaodu2/PI*180;
	}



	ARC(Center,banjin,jiaodu1,jiaodu2);
	return 0;
}
void DXF::REC(Piont Center,double length,double width)
{
	Piont p1,p2,p3,p4;

	p1.x=Center.x-length/2;
	p1.y=Center.y-width/2;

	p2.x=Center.x+length/2;
	p2.y=Center.y-width/2;

	p3.x=Center.x+length/2;
	p3.y=Center.y+width/2;

	p4.x=Center.x-length/2;
	p4.y=Center.y+width/2;

	L(p1,p2);
	L(p2,p3);
	L(p3,p4);
	L(p4,p1);
	
}
void DXF::REC(Piont start, Piont end)
{
	Piont p1,p2,p3,p4;
	p1=start;
	p2.x=end.x;
	p2.y=start.y;
	p3=end;
	p4.x=start.x;
	p4.y=end.y;

	L(p1,p2);
	L(p2,p3);
	L(p3,p4);
	L(p4,p1);
}
void DXF::OB(Piont Center,double length,double width,double angle)
{
	double radius=width/2;
	Piont c1,c2,p1,p2,p3,p4;
	c1.x=Center.x-((length-width)/2);
	c1.y=Center.y;
	c2.x=Center.x+((length-width)/2);
	c2.y=Center.y;

	p1.x=c1.x;
	p1.y=Center.y-width/2;

	p2.x=c2.x;
	p2.y=Center.y-width/2;

	p3.x=c2.x;
	p3.y=Center.y+width/2;

	p4.x=c1.x;
	p4.y=Center.y+width/2;

	c1=Rotate(Center,c1,angle);
	c2=Rotate(Center,c2,angle);
	p1=Rotate(Center,p1,angle);
	p2=Rotate(Center,p2,angle);
	p3=Rotate(Center,p3,angle);
	p4=Rotate(Center,p4,angle);

	L(p1,p2);
	ARC(c2,p2,p3);
	L(p3,p4);
	ARC(c1,p4,p1);

}
bool DXF::Polygon(Piont Center,double diameter,int geshu,double angle)
{
	double radius = diameter / 2;
	Piont p1, p2, p3, p4, p5, p6, p7, p8;
	double x, y;
	double bian_chang;
	double hudu;
	switch (geshu)
	{
	case 3:	
		hudu = 0.16666666666*PI;
		y = radius * sin(hudu);
		x = radius * cos(hudu);
		bian_chang = 2 * x;

		p1.x = Center.x - x;
		p1.y = Center.y - y;

		p2.x = p1.x + bian_chang;
		p2.y = p1.y;

		p3.x = Center.x;
		p3.y = Center.y + radius;

		p1 = Rotate(Center, p1, angle);
		p2 = Rotate(Center, p2, angle);
		p3 = Rotate(Center, p3, angle);

		L(p1, p2);
		L(p2, p3);
		L(p3, p1);
		return 1;

	case 5:		
		hudu = 0.3 * PI;
		y = radius * sin(hudu);
		x = radius * cos(hudu);
		bian_chang = 2 * x;

		p1.x = Center.x - x;
		p1.y = Center.y - y;

		p2.x = p1.x + bian_chang;
		p2.y = p1.y;

		p3= Rotate(p2, p1, 252);
		p4= Rotate(p3, p2, 252);
		p5 = Rotate(p4, p3, 252);

		p1 = Rotate(Center, p1, angle);
		p2 = Rotate(Center, p2, angle);
		p3 = Rotate(Center, p3, angle);
		p4 = Rotate(Center, p4, angle);
		p5 = Rotate(Center, p5, angle);

		L(p1, p2);
		L(p2, p3);
		L(p3, p4);
		L(p4, p5);
		L(p5, p1);		
		return 1;
	case 6:
		hudu = 0.33333333333 * PI;
		y = radius * sin(hudu);
		x = radius * cos(hudu);
		bian_chang = 2 * x;

		p1.x = Center.x - x;
		p1.y = Center.y - y;

		p2.x = p1.x + bian_chang;
		p2.y = p1.y;

		p3 = Rotate(p2, p1, 240);
		p4 = Rotate(p3, p2, 240);
		p5 = Rotate(p4, p3, 240);
		p6 = Rotate(p5, p4, 240);

		p1 = Rotate(Center, p1, angle);
		p2 = Rotate(Center, p2, angle);
		p3 = Rotate(Center, p3, angle);
		p4 = Rotate(Center, p4, angle);
		p5 = Rotate(Center, p5, angle);
		p6 = Rotate(Center, p6, angle);

		L(p1, p2);
		L(p2, p3);
		L(p3, p4);
		L(p4, p5);
		L(p5, p6);
		L(p6, p1);

		return 1;
	case 8:
		hudu = 0.377777777777 * PI;
		y = radius * sin(hudu);
		x = radius * cos(hudu);
		bian_chang = 2 * x;

		p1.x = Center.x - x;
		p1.y = Center.y - y;

		p2.x = p1.x + bian_chang;
		p2.y = p1.y;

		p3 = Rotate(p2, p1, 225);
		p4 = Rotate(p3, p2, 225);
		p5 = Rotate(p4, p3, 225);
		p6 = Rotate(p5, p4, 225);
		p7 = Rotate(p6, p5, 225);
		p8 = Rotate(p7, p6, 225);

		p1 = Rotate(Center, p1, angle);
		p2 = Rotate(Center, p2, angle);
		p3 = Rotate(Center, p3, angle);
		p4 = Rotate(Center, p4, angle);
		p5 = Rotate(Center, p5, angle);
		p6 = Rotate(Center, p6, angle);
		p7 = Rotate(Center, p7, angle);
		p8 = Rotate(Center, p8, angle);

		L(p1, p2);
		L(p2, p3);
		L(p3, p4);
		L(p4, p5);
		L(p5, p6);
		L(p6, p7);
		L(p7, p8);
		L(p8, p1);
		return 1;
	default:
		return false;
	}
}

Piont DXF::Rotate(Piont center, Piont p11, double angle)
{
	//double dis;
	Piont p;
	//dis=distance(center,p1);
	//p.x=dis*cos(angle/180*PI);
	//p.y=dis*sin(angle/180*PI);

	//p.x=center.x+p.x;
	//p.y=center.y+p.y;
	p.x = (p11.x - center.x) * cos(angle / 180 * PI) - (p11.y - center.y) * sin(angle / 180 * PI) + center.x;
	p.y = (p11.x - center.x) * sin(angle / 180 * PI) + (p11.y - center.y) * cos(angle / 180 * PI) + center.y;
	return p;
}
double distance(Piont p1,Piont p2)
{
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}