//Execise 1
//Not attempted Question 1

#include<iostream>
#include<GLM/glm.hpp>
#include<GLM/vec3.hpp>

float mag(glm::vec3 in)
{
	return sqrt(in.x * in.x + in.y * in.y + in.z * in.z);
}


//Question 2
void PlanevsPoint(glm::vec3 n, glm::vec3 pPlane, glm::vec3 p)
{
	float d = -n.x * pPlane.x - n.y * pPlane.y - n.z * pPlane.z;

	float distance = (n.x * p.x + n.y * p.y + n.z * p.z + d) / mag(n);

	if (abs(distance) < 0.001f)
	{
		std::cout << "ON_PLANE";
	}

	else if (distance > 0.001f)
	{
		std::cout << "IN_FRONT";
	}

	else if (distance < -0.001f)
	{
		std::cout << "BEHIND";
	}
	std::cout << '\n';
}


//Question 3
bool PlanevsLine(glm::vec3 n, glm::vec3 pPlane, glm::vec3 p1, glm::vec3 p2)
{
	float t = glm::dot(n, pPlane - p1) / glm::dot(n, (p2 - p1));

	if (t > 0.0f && t < 1.0f)
	{
		//std::cout << "Collision";
		return true;
	}


	else
	{
		//std::cout << "No Collision";
		return false;
	}

}

int main()
{
	glm::vec3 normal;
	glm::vec3 planePoint;
	glm::vec3 point;
	glm::vec3 point2;
	glm::vec3 point3;


	std::cout << "Enter normal\nx:";
	std::cin >> normal.x;
	std::cout << "y:";
	std::cin >> normal.y;
	std::cout << "z:";
	std::cin >> normal.z;

	std::cout << "Enter planePoint\nx:";
	std::cin >> planePoint.x;
	std::cout << "y:";
	std::cin >> planePoint.y;
	std::cout << "z:";
	std::cin >> planePoint.z;

	std::cout << "Enter point\nx:";
	std::cin >> point.x;
	std::cout << "y:";
	std::cin >> point.y;
	std::cout << "z:";
	std::cin >> point.z;

	std::cout << "Enter point2\nx:";
	std::cin >> point2.x;
	std::cout << "y:";
	std::cin >> point2.y;
	std::cout << "z:";
	std::cin >> point2.z;

	std::cout << "Enter point3\nx:";
	std::cin >> point3.x;
	std::cout << "y:";
	std::cin >> point3.y;
	std::cout << "z:";
	std::cin >> point3.z;

	PlanevsPoint(normal, planePoint, point);
	
	(PlanevsLine(normal, planePoint, point, point2)) ? std::cout << "Collision" : std::cout << "No Collision";
	std::cout << '\n';


	//Question 4
	if (PlanevsLine(normal, planePoint, point, point2) || PlanevsLine(normal, planePoint, point3, point2) || PlanevsLine(normal, planePoint, point, point3))
	{
		std::cout << "Triangle Collision";
	}
	else
	{
		std::cout << "No triangle collision";
	}

	

}