#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	// GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	//creates a lists to hold all the vector points of the cone
	std::vector<vector3> coneList;

	//creates variables to hold the angles
	float angle = 0.0f;
	float angleChange = glm::radians(360.0f / a_nSubdivisions);

	//creates a for loop that will create all the points for the cone
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		coneList.push_back(vector3(a_fRadius * cos(angle), a_fRadius * sin(angle),a_fHeight/2));

		angle += angleChange;
	}

	//creates a loop that will draw the cone
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(vector3(0, 0, a_fHeight / 2), coneList[i], coneList[(i + 1) % a_nSubdivisions]);
		AddTri(vector3(0, 0, -a_fHeight / 2), coneList[(i + 1) % a_nSubdivisions], coneList[i]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	//Creates two list to hold the points for the top and bottom of the cylinder
	std::vector<vector3> bottomOfCylinder;
	std::vector<vector3> topOfCylinder;

	//creates variables to hold the angle and change of angle
	float angle = 0.0f;
	float angleChange = glm::radians(360.0f / a_nSubdivisions);

	//creates a loop to get the points of the cylinder
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		bottomOfCylinder.push_back(vector3(a_fRadius * cos(angle), a_fRadius * sin(angle), a_fHeight / 2));
		topOfCylinder.push_back(vector3(a_fRadius * cos(angle), a_fRadius * sin(angle), -a_fHeight / 2));

		angle += angleChange;
	}

	//creates a loop that will draw the cylinder
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(vector3(0, 0, a_fHeight / 2), bottomOfCylinder[i], bottomOfCylinder[(i + 1) % a_nSubdivisions]);
		AddTri(vector3(0, 0, -a_fHeight / 2), topOfCylinder[(i + 1) % a_nSubdivisions], topOfCylinder[i]);
		AddQuad(bottomOfCylinder[(i + 1) % a_nSubdivisions], bottomOfCylinder[i], topOfCylinder[(i + 1) % a_nSubdivisions], topOfCylinder[i]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	//creates 4 lists to hold the top and bottom of the inner and outer radii
	std::vector<vector3> bottomOuter;
	std::vector<vector3> topOuter;
	std::vector<vector3> bottomInner;
	std::vector<vector3> topInner;

	//creates variables to hold the angle and change of angle
	float angle = 0.0f;
	float angleChange = glm::radians(360.0f / a_nSubdivisions);

	//creates a loop to get the points for the tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		bottomOuter.push_back(vector3(a_fOuterRadius * cos(angle), a_fOuterRadius * sin(angle), a_fHeight / 2));
		topOuter.push_back(vector3(a_fOuterRadius * cos(angle), a_fOuterRadius * sin(angle), -a_fHeight / 2));

		bottomInner.push_back(vector3(a_fInnerRadius * cos(angle), a_fInnerRadius * sin(angle), a_fHeight / 2));
		topInner.push_back(vector3(a_fInnerRadius * cos(angle), a_fInnerRadius * sin(angle), -a_fHeight / 2));

		angle += angleChange;
	}

	//creates loop to draw the tube
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//bottom of tube
		AddQuad(bottomInner[(i + 1) % a_nSubdivisions], bottomInner[i], bottomOuter[(i + 1) % a_nSubdivisions], bottomOuter[i]);

		//top of tube
		AddQuad(topOuter[(i + 1) % a_nSubdivisions], topOuter[i], topInner[(i + 1) % a_nSubdivisions], topInner[i]);

		//inside of tube
		AddQuad(topInner[(i + 1) % a_nSubdivisions], topInner[i], bottomInner[(i + 1) % a_nSubdivisions], bottomInner[i]);

		//outside of tube
		AddQuad(bottomOuter[(i + 1) % a_nSubdivisions], bottomOuter[i], topOuter[(i + 1) % a_nSubdivisions], topOuter[i]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	//creates a list of list of vector3s. This will hold all the points for the inner circles and all the circles
	std::vector<std::vector<vector3>> torusList;

	//creates variables that will hold the different angles needed
	float circleAngle = 0.0f;
	float circleChange = glm::radians(360.0f / a_nSubdivisionsB);

	float torusAngle = 0.0f;
	float torusChange = glm::radians(360.0f / a_nSubdivisionsA);

	//creates a variable to hold the inner radius
	float circleRadius = (a_fOuterRadius - a_fInnerRadius) / 2;

	//Creates nested loops to get the points for the torus
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		//creates a variable to hold the inner list
		std::vector<vector3> circleList;

		for (int j = 0; j < a_nSubdivisionsB; j++)
		{
			//creates a variable to hold the circle to then add it to the list
			vector3 circle = vector3(cos(torusAngle) * (a_fOuterRadius - (circleRadius * sin(circleAngle))),
				sin(torusAngle) * (a_fOuterRadius - (circleRadius * sin(circleAngle))),
				cos(circleAngle) * circleRadius);

			//cos(torusAngle) * (a_fOuterRadius - (circleRadius * sin(circleAngle)), sin(torusAngle) * (a_fOuterRadius - (circleRadius * sin(circleAngle)), cos(circleAngle) * circleRadius)));
			
			circleAngle += circleChange;
			circleList.push_back(circle);
		}

		//changes the angle of the circles back to 0
		circleAngle = 0;
		//updates the torus angle
		torusAngle += torusChange;
 
		//adds the circle list into the torus list
		torusList.push_back(circleList);
	}

	//Creates nested loops to draw the torus
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		for (int j = 0; j < a_nSubdivisionsB; j++)
		{
			AddQuad(torusList[i][(j + 1) % a_nSubdivisionsB], torusList[i][j], torusList[(i + 1) % a_nSubdivisionsA][(j + 1) % a_nSubdivisionsB], torusList[(i + 1) % a_nSubdivisionsA][j]);
		}
	}


	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	//creates a list of a list of vector3 to hold the points for the sphere
	std::vector<std::vector<vector3>> sphereList;

	//creates a varible to hold my angles
	float angle = 0.0f;
	float angleChange = glm::radians(360.0f / a_nSubdivisions);

	//creates variables to hold the z value and the change of it
	float zChange = (a_fRadius * 2) / a_nSubdivisions;
	float zValue = a_fRadius - zChange;

	//creates nested loops to get the points for the sphere
	for (int i = 0; i < a_nSubdivisions - 1; i++)
	{
		//creates a temp list to hold the points for the circles
		std::vector<vector3> circleList;

		for (int j = 0; j < a_nSubdivisions; j++)
		{
			circleList.push_back(vector3(
				cos(angle) * (a_fRadius - abs(zValue) / 2),
				sin(angle) * (a_fRadius - abs(zValue) / 2),
				zValue
			));

			angle += angleChange;
		}

		angle = 0;
		zValue -= zChange;

		sphereList.push_back(circleList);
	}

	//creates a loop to draw just the top and bottom of the sphere
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//Draws the front of the sphere
		AddTri(vector3(0,0, a_fRadius), sphereList[0][i], sphereList[0][(i + 1) % a_nSubdivisions]);

		//Draws the end of the sphere
		AddTri(vector3(0, 0, -a_fRadius), sphereList[sphereList.size() - 1][(i + 1) % a_nSubdivisions], sphereList[sphereList.size() - 1][i]);
	}

	//creates nested for loops to draw the rest of the sphere
	for (int i = 0; i < a_nSubdivisions - 2; i++)
	{
		for (int j = 0; j < a_nSubdivisions; j++)
		{
			AddQuad(sphereList[i][(j + 1) % a_nSubdivisions], sphereList[i][j], sphereList[(i + 1) % a_nSubdivisions][(j + 1) % a_nSubdivisions], sphereList[(i + 1) % a_nSubdivisions][j]);
		}
	}


	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}