#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

class Point
{
	public:
	double x;
	double y;
};


//											
//			:								
//	P A R T (1) 	:	H E L P E R	 F U N C T I O N S	*******************************************
//			:								
//											


//
// ++++		returns the intersection point of two lines	++++++++++++++++++++++++++++++++++++++
//

Point segint(Point p1,Point p2, Point q1,Point q2)
{
	double a1 = p2.y - p1.y;
	double b1 = p1.x - p2.x;
	double c1 = (a1*(p1.x)) + (b1*(p1.y));
	double a2 = q2.y - q1.y;
	double b2 = q1.x - q2.x;
	double c2 = (a2*(q1.x)) + (b2*(q1.y));
	double deter = (a1*b2 - a2*b1);
	Point val;
	val.x = 999;
	val.y = 999;
	if(deter == 0.0)	return val;	
	val.y = (a1*c2 - a2*c1)/(deter*1.0);
	val.x = (b2*c1 - b1*c2)/(deter*1.0);
	return val;
}




//
// ++++		returns the side of  a line a point is on (returns 1 if it is on the left)	++++
//

double side(Point p1, Point p2, Point p)
{
	 return (( (p2.x)*(p.y) - (p2.y)*(p.x) )-((p1.x)*((p.y) - (p2.y))) + ((p1.y)*((p.x) - (p2.x))) > 0 ? 
			1 : 0);
}




//
// ++++		checks if a point is inside or outside a quadrilateral  	++++++++++++++++++++
//

int pointpos(Point r[4] , Point p)
{
	for( int k=0; k<=3; k++ )
	{
		if(!side( r[k], r[(k+1)%4], p))
		{
			return 0;				//outside
		}
	}
	return 1;						//inside
} 

//
// ++++		computes area of a triangle	++++++++++++++++++++++++++++++++++++++++++++++++++++
//

double tarea( Point a, Point b, Point c)
{
	double ab = sqrt( fabs((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) );
	double ac = sqrt( fabs((a.x - c.x)*(a.x - c.x) + (a.y - c.y)*(a.y - c.y)) );
	double bc = sqrt( fabs((b.x - c.x)*(b.x - c.x) + (b.y - c.y)*(b.y - c.y)) );
	double s = (ab + ac +bc)/2;
	return sqrt(fabs( s * (s - ab) * (s - ac) * (s - bc)));
}


//
// ++++		computes area of  polygon	++++++++++++++++++++++++++++++++++++++++++++++++++++
//

double parea(Point* p, int n)
{
	double area = 0;
	for(int i=2; i<n; i++)
	{
		area+= tarea(p[0], p[i], p[i-1]);
	}
	return area;
}




//									
//			:						
//	P A R T (2)	:	G R A P H I C A L	M E T H O D	******************************************	
//			:															
//		
							
double aoi1( Point R1[4], Point R2[4], int N )
{
	double count = 0.0;
	double low = 1.00/(2.0*N);
	double i = low, j = low;
	while(i<1.0)
	{
		j = low;
		while(j<1.0)
		{
			int isArea = 0;
			Point p;
			p.x = i, p.y = j;
			isArea+= pointpos( R1, p );
			isArea+= pointpos( R2, p );
			if(isArea == 2)
			count+=1.00;
			j+= 1.00/N;
		}
		i+= 1.00/N;
	}
	return (1.00 * count)/(N*N);	
}

//									
//			:						
//	P A R T (3)	:	N U M E R I C A L	M E T H O D	*******************************************
//			:						
//	
								
double aoi2( Point R1[4], Point R2[4], int N )
{	
	double sum = 0.0, maxR1 = R1[0].x, minR1 = R1[0].x, maxR2 = R2[0].x, minR2 = R2[0].x;

	for( int i = 0; i < 4; i++)
	{
		maxR1 = (R1[i].x > maxR1)? R1[i].x : maxR1;
		maxR2 = (R2[i].x > maxR2)? R2[i].x : maxR2;
		minR1 = (R1[i].x < minR1)? R1[i].x : minR1;
		minR2 = (R2[i].x < minR2)? R2[i].x : minR2;
	}	

	for(float i = 1.0/(2*N); i < 1 ; i+=(1.00/N))
	{
		double seg[4];
		int count = 0;
		if( ((i <= maxR1) && (i >= minR1) && (i <= maxR2) && (i >= minR2))) 	//contributing strip
		{
			for( int j = 0; j < 4; j++)
			{
				seg[count] = 0;
				if( ((i >= R1[j].x) && (i <= R1[(j+1)%4].x)) 
					|| 
				((i <= R1[j].x) && (i >= R1[(j+1)%4].x)) )
				{
					Point currUp, currDown;
					currUp.x = i, currUp.y = 1, currDown.x = i, currDown.y = 0;
					seg[count] = (segint(currUp, currDown, R1[j], R1[(j+1)%4])).y; 
					count++;
					seg[count] = 0;

				}
			}
			for( int j = 0; j < 4; j++)
			{
				if( ((i >= R2[j].x) && (i <= R2[(j+1)%4].x)) 
					||
				((i <= R2[j].x) && (i >= R2[(j+1)%4].x)) )
				{
					Point currUp, currDown;
					currUp.x = i, currUp.y = 1, currDown.x = i, currDown.y = 0;
					seg[count] = segint(currUp, currDown, R2[j], R2[(j+1)%4]).y;
					count++;
					seg[count] = 0;
				}	
			} 

			if( 	((seg[0] > seg[2]) && (seg[0] > seg[3]) && (seg[1] > seg[2]) && (seg[1] > seg[3])) 
				|| 
				((seg[0] < seg[2]) && (seg[0] < seg[3]) && (seg[1] < seg[2]) && (seg[1] < seg[3])))
				continue;	// check for a false overlap

			double max = seg[0], min = seg[0];
			double pt[2];
			int count2 = 0;
			for( int j = 0; j < 4; j++ )
			{
				max = seg[j] > max ? seg[j] : max;
				min = seg[j] < min ? seg[j] : min;
			}
			for ( int j = 0; j < 4; j++)
			{
				if((seg[j] != max) && (seg[j] != min))
				{
					pt[count2++] = seg[j];
				}
			}
			double length = ( pt[0] > pt[1] ) ? (pt[0] - pt[1]) : (pt[1] - pt[0]);
			double area = (length * 1.0) / N ; 
			sum+= area;
		}
	}
	return sum;
}


//								
//			:					
//	P A R T (4)	:	G E O M E T R I C	M E T H O D	*******************************************
//			:					
//				
				
double aoi3( Point R1[4], Point R2[4])
{

	int count = 0;
	double res = 0;
	Point l[8], l2[8];
	double slope[8];
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			// edge intersections
			if( (side(R1[i], R1[(i+1)%4], R2[j]) != side(R1[i], R1[(i+1)%4], R2[(j+1)%4]))	
			&& 
			( side(R2[j], R2[(j+1)%4], R1[i]) != side(R2[j], R2[(j+1)%4], R1[(i+1)%4]) ))
			{
				l[count] = segint(R1[i], R1[(i+1)%4], R2[j], R2[(j+1)%4]);
				l2[count].x = i;
				l2[count].y = j;
				count++;
			}
		}
	}
	cout << "\n--- Number of edge intersections = " << count << endl;
	for(int i=0; i<count; i++)
	{
		cout 	<< "\tI(" << (int)l2[i].x << "," << (int)l2[i].y 
			<< ") = (" 
			<< l[i].x << ", " << l[i].y << ")" << endl; 
	}
	
	
	for(int iter = 0; iter < 4; iter++)
	{
		// corners of quadrilateral
		if(pointpos( R1, R2[iter] ) > 0)
			l[count++] = R2[iter];
		if(pointpos( R2, R1[iter] ) > 0)
			l[count++] = R1[iter];
	}
	double meanX = 0.0, meanY = 0.0;
	for( int w=0; w<count; w++)
	{
		meanX += l[w].x;
		meanY += l[w].y;
	}
	meanX = meanX/count;
	meanY = meanY/count;
	 for( int m=0; m<count-1; m++)			// sort counterclockwise
	{
		for( int n=0; n<count-1-m; n++)
		{
			if((atan2((l[n].y - meanY), (l[n].x - meanX))) 
				> 
			(atan2((l[n+1].y - meanY), (l[n+1].x - meanX))))
			{
				Point swap;
				swap.x = l[n].x;
				swap.y = l[n].y;
				l[n].x = l[n+1].x;
				l[n].y = l[n+1].y;
				l[n+1].x = swap.x;
				l[n+1].y = swap.y; 
			}
		}
	}
	if(count)
	cout << "\n--- Number of corners on the intersection polygon = " << count << endl;
	for( int i =0; i<count; i++)
	{
		cout << "\tP[" << i << "] = (" << l[i].x << ", " << l[i].y << ")" << endl;
	}
	res = parea( l, count );
	return res;
	
}


//
//
//	M A I N		F U N C T I O N		*****************************************************************
//
//
int main()
{
	Point R1[4] , R2[4];

	//	INPUT	---------------------
	cout << "+++ Rectangle 1" << endl;
	cin 	>> R1[0].x >> R1[0].y 
		>> R1[1].x >> R1[1].y 
		>> R1[2].x >> R1[2].y 
		>> R1[3].x >> R1[3].y ;
		
	cout << "\n+++ Rectangle 2" << endl;
	cin	>> R2[0].x >> R2[0].y 
		>> R2[1].x >> R2[1].y 
		>> R2[2].x >> R2[2].y 
		>> R2[3].x >> R2[3].y ;

	cout << fixed;
	cout << std::setprecision(16);

	//	OUTPUT	----------------------

	//	Graphical
	cout << "\n\n+++Graphical Method" << endl;
	for(int i=10; i<=1000; i*=10)
	{
		double pixellate = aoi1(R1, R2, i);
		cout << "N =\t" << i <<".\t Area of intersection = " << pixellate << endl;
	}
	
	//	Numerical
	cout << "\n\n+++Numerical Method" << endl;
	for(int i=10; i<=100000; i*=10)
	{
	double vertical = aoi2(R1, R2, i);
	cout << "N =\t" << i <<".\t \tArea of intersection = " << vertical << endl;
	}
	double vertical = aoi2(R1, R2, 1000000);
	cout << "N =\t" << 1000000 <<".\tArea of intersection = " << vertical << endl;

	//	Geometrical
	cout << "\n\n+++Geometric Method " << endl;
	double geom = aoi3(R1,R2);
	cout << "\n\tArea of intersection = " << geom << endl;

	return 0;
}

