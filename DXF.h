#pragma once
#include <string>
#include"fstream"
#include"cmath"

const double PI=3.141592653;
struct Piont
{
	double x;
	double y;
};

//Piont Rotate(Piont center,Piont p,double angle);

double distance(Piont p1,Piont p2);

class DXF
{
private:
	std::string  FileName;
	std::ofstream * fp;
	Piont Rotate(Piont center,Piont p,double angle);
public:
	DXF(std::string a);
	~DXF();
	void L(Piont start, Piont end);//Ö±Ïß
	void C(Piont Center,double radius);//Ô²
	void ARC(Piont Center,double radius,double start, double end);//Ô²»¡1
	int ARC(Piont Center,Piont start, Piont end);//Ô²»¡2
	void REC(Piont Center,double length,double width);
	void REC(Piont start, Piont end);
	void OB(Piont Center,double length,double width,double angle=0);
	bool Polygon(Piont Center,double diameter,int geshu,double angle=0);//3,5,6,8
};

