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
	
	// angle increment per section
	float angle = 0.0f;
	float increment = 2 * PI / a_nSubdivisions;

	float top = a_fHeight/2, btm = a_fHeight/-2;
	vector3 v1 = vector3(a_fRadius, btm, 0.0f);
	vector3 v2 = vector3(0.0f, btm, 0.0f);
	vector3 circleCenter = vector3(0.0f, btm, 0.0f);
	vector3 topCenter = vector3(0.0f, top, 0.0f);

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		angle += increment;
		v2.x = circleCenter.x + (cos(angle) * a_fRadius);
		v2.z = circleCenter.z + (sin(angle) * a_fRadius);

		// add triangle for body
		AddTri(topCenter, v2, v1);
		// add triangle for base
		AddTri(circleCenter, v1, v2);
		v1 = v2;
	}
	// -------------------------------

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

	// angle increment per section
	float angle = 0.0f;
	float increment = 2 * PI / a_nSubdivisions;

	float top = a_fHeight / 2, btm = a_fHeight / -2;
	float x1 = a_fRadius, z1 = 0.0f;
	float x2 = 0.0f, z2 = 0.0f;
	vector3 center = ZERO_V3;

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		angle += increment;
		x2 = center.x + (cos(angle) * a_fRadius);
		z2 = center.z + (sin(angle) * a_fRadius);

		// add quad for body
		AddQuad(vector3(x2, btm, z2), vector3(x1, btm, z1), vector3(x2, top, z2), vector3(x1, top, z1));
		// add triangle for top
		AddTri(vector3(0.0f, top, 0.0f), vector3(x2, top, z2), vector3(x1, top, z1));
		// add triangle for base
		AddTri(vector3(0.0f, btm, 0.0f), vector3(x1, btm, z1), vector3(x2, btm, z2));
		x1 = x2;
		z1 = z2;
	}
	// -------------------------------

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

	// angle increment per section
	float angle = 0.0f;
	float increment = 2 * PI / a_nSubdivisions;

	float top = a_fHeight / 2, btm = a_fHeight / -2;
	float x1 = a_fOuterRadius, z1 = 0.0f;
	float x2 = 0.0f, z2 = 0.0f;
	float x3 = a_fInnerRadius, z3 = 0.0f;
	float x4 = 0.0f, z4 = 0.0f;
	vector3 center = ZERO_V3;

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		angle += increment;
		x2 = center.x + (cos(angle) * a_fOuterRadius);
		z2 = center.z + (sin(angle) * a_fOuterRadius);
		x4 = center.x + (cos(angle) * a_fInnerRadius);
		z4 = center.z + (sin(angle) * a_fInnerRadius);

		// add quad for outer body
		AddQuad(vector3(x2, btm, z2), vector3(x1, btm, z1), vector3(x2, top, z2), vector3(x1, top, z1));
		// add quad for inner body
		AddQuad(vector3(x4, top, z4), vector3(x3, top, z3), vector3(x4, btm, z4), vector3(x3, btm, z3));
		// add quad for top
		AddQuad(vector3(x3, top, z3), vector3(x4, top, z4), vector3(x1, top, z1), vector3(x2, top, z2));
		// add quad for base
		AddQuad(vector3(x1, btm, z1), vector3(x2, btm, z2), vector3(x3, btm, z3), vector3(x4, btm, z4));
		x1 = x2;
		z1 = z2;
		x3 = x4;
		z3 = z4;
	}
	// -------------------------------

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

	// angle increment per section
	float delta, theta = 0.0f;
	float thetaIncr = 2 * PI / a_nSubdivisionsB;
	// angle increment per axis section
	float gammaIncr = 2 * PI / a_nSubdivisionsA;

	// uncomment to match BTX radius usage
	//a_fInnerRadius = (a_fOuterRadius - a_fInnerRadius) / 2;
	//a_fOuterRadius = a_fOuterRadius + a_fInnerRadius;

	for (int i = 0; i < a_nSubdivisionsB; i++)
	{
		delta = theta;
		theta += thetaIncr;
		float gamma = 0.0f;

		vector3 v1, v2, v3, v4;
		v1.x = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * cos(theta);
		v1.y = sin(gamma) * a_fInnerRadius;
		v1.z = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * sin(theta);
		
		v3.x = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * cos(delta);
		v3.y = v1.y;
		v3.z = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * sin(delta);

		for (int j = 0; j < a_nSubdivisionsA; j++)
		{
			gamma += gammaIncr;

			v2.x = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * cos(theta);
			v2.y = sin(gamma) * a_fInnerRadius;
			v2.z = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * sin(theta);

			v4.x = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * cos(delta);
			v4.y = v2.y;
			v4.z = (a_fOuterRadius + (cos(gamma) * a_fInnerRadius)) * sin(delta);

			AddQuad(v2, v1, v4, v3);

			v1.x = v2.x;
			v1.y = v2.y;
			v1.z = v2.z;

			v3.x = v4.x;
			v3.y = v4.y;
			v3.z = v4.z;
		}
	}
	// -------------------------------

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

	float delta, theta = 0.0f;
	float thetaIncr = 2 * PI / a_nSubdivisions; // 360 deg increment
	float gammaIncr = -PI / a_nSubdivisions; // 180 deg increment

	for (int i = 0; i < a_nSubdivisions; i++) {
		delta = theta; // theta of previous iteration
		theta += thetaIncr;
		float gamma = PI / 2; // start at top of sphere
		vector3 v1, v2, v3, v4;

		for (int j = 0; j < a_nSubdivisions; j++)
		{
			gamma += gammaIncr;
			if (j == 0)
			{
				v1 = a_fRadius * vector3(cos(delta) * cos(gamma), sin(gamma), sin(delta) * cos(gamma));
				v3 = a_fRadius * vector3(cos(theta) * cos(gamma), sin(gamma), sin(theta) * cos(gamma));
				// draw top triangle
				AddTri(vector3(0.0f, a_fRadius, 0.0f), v1, v3);
			}
			else if (j < a_nSubdivisions-1)
			{
				v2 = a_fRadius * vector3(cos(delta) * cos(gamma), sin(gamma), sin(delta) * cos(gamma));
				v4 = a_fRadius * vector3(cos(theta) * cos(gamma), sin(gamma), sin(theta) * cos(gamma));
				// draw quad
				AddQuad(v2, v4, v1, v3);
				v1 = v2;
				v3 = v4;
			}
			else
			{
				// draw bottom triangle
				AddTri(vector3(0.0f, -a_fRadius, 0.0f), v4, v2);
			}
		}
	}
	// -------------------------------

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