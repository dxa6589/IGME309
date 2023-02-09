#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	for (int i = 0; i < m_uMeshCount; i++)
	{
		m_pMeshList[i] = new MyMesh();
		m_pMeshList[i]->GenerateCube(1.0f, C_BLACK);
	}	
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	float scaleFactor = 0.5f;
	matrix4 m4Scale = glm::scale(ToMatrix4(m_qArcBall), vector3(scaleFactor));

	static float translationFactor = 0.0f;
	translationFactor += 0.01f;
	matrix4 m4Translate = glm::translate(ToMatrix4(m_qArcBall),
		vector3(translationFactor, 0.0f, 0.0f));

	matrix4 m4Model = m4Scale * m4Translate;

	int i = 0;

	// row 1/8
	for (int j = -5; j <= 5; j++) {
		if (j != -3 && j != 3)
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View, 
				glm::translate(m4Model, vector3(j, 4.0f, 0.0f)));
			i++;
		}
	}

	// row 2/8
	for (int j = -5; j <= 5; j++) {
		if (j != -2 && j != 2)
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View, 
				glm::translate(m4Model, vector3(j, 3.0f, 0.0f)));
			i++;
		}
	}

	// row 3/8
	for (int j = -5; j <= 5; j++) {
		if (j == -5 || j == -4 || j == 4 || j == 5) 
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View, 
				glm::translate(m4Model, vector3(j, 2.0f, 0.0f)));
			i++;
		}
	}

	// row 4/8
	for (int j = -5; j <= 5; j++) {
		if (j == -5 || j == -2 || j == 2 || j == 5)
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View,
				glm::translate(m4Model, vector3(j, 1.0f, 0.0f)));
			i++;
		}
	}

	// row 5/8
	for (int j = -5; j <= 5; j++) {
		m_pMeshList[i]->Render(m4Projection, m4View, 
			glm::translate(m4Model, vector3(j, 0.0f, 0.0f)));
		i++;
	}

	// row 6/8
	for (int j = -5; j <= 5; j++) {
		if (j == -4 || j == 4)
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View,
				glm::translate(m4Model, vector3(j, -1.0f, 0.0f)));
			i++;
		}
	}

	// row 7/8
	for (int j = -5; j <= 5; j++) {
		if (j != -5 && j != -3 && j != 3 && j != 5)
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View,
				glm::translate(m4Model, vector3(j, -2.0f, 0.0f)));
			i++;
		}
	}

	// row 8/8
	for (int j = -5; j <= 5; j++) {
		if (j != -2 && j != -1 && j != 1 && j != 2)
		{
			continue;
		}
		else
		{
			m_pMeshList[i]->Render(m4Projection, m4View,
				glm::translate(m4Model, vector3(j, -3.0f, 0.0f)));
			i++;
		}
	}

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes 
	for (int i = 0; i < m_uMeshCount; i++)
	{
		SafeDelete(m_pMeshList[i]);
	}

	//release GUI
	ShutdownGUI();
}