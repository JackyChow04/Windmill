
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

int questionToDisplay = 2;
float x = 0.0f;
float y = 0.0f;
float x2 = 0.0f, y2 = 0.0f;
float velocity = 0.1f;

float angle = 0.0f, speed = 0.2f;
float r = 0.573f, g = 0.737f, b = 0.243;
float roofR = 0.071f, roofG = 0.035f, roofB = 0.016f;
float treeR = 0.427, treeG = 0.733, treeB = 0.384;
float snowballRoll = 0.0f;
float snowfall = 0.0f;

boolean clockwise = 1 ,snow = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);

		//left key go counter clockwise
		if (wParam == VK_LEFT) {
			x2 -= velocity;
			clockwise = 0;
		}

		//right key go clockwise
		if (wParam == VK_RIGHT) {
			x += velocity;
			clockwise = 1;
		}

		//up key to speed up
		if (wParam == VK_UP) {
			y += 0.1f;
			speed += 0.1f;
		}

		//down key to slow down
		if (wParam == VK_DOWN) {
			y2 -= 0.1f;
			if (speed < 0.1f) speed = 0.0f;
			else speed -= 0.1f;
		}

		//space key to stop
		if (wParam == VK_SPACE) {
			x = y = x2 = y2 = 0.0f;
			speed = 0.0f;
		} 

		//S key to snow
		if (wParam == 0x53) {
			snow = 1;
		}

		//O key back to original
		if (wParam == 0x4F) {
			snow = 0;
		}

		if (wParam == 0x31) questionToDisplay = 1;

		if (wParam == 0x32) questionToDisplay = 2;


		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//function to draw circle
void drawCircle(float r, float g, float b, float xValue, float xRadius, float yValue, float yRadius) {
	float theta;

	glPushMatrix();
		glBegin(GL_POLYGON);
		glColor3f(r, g, b);
		for (int i = 0;i < 360;i++) {
			theta = i * 3.142 / 180;
			glVertex2f(xValue + xRadius * cos(theta), yValue + yRadius * sin(theta));
		}
		glEnd();
	glPopMatrix();
}

//function to draw window
void drawWindow(float xValue, float yValue) {

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(xValue, yValue, 0.0f);
		glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(-0.03f, 0.0f);
		glVertex2f(-0.03f, 0.1f);
		glVertex2f(0.03f, 0.1f);
		glVertex2f(0.03f, 0.0f);
		glEnd();

		float theta;
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		for (int i = 0;i < 360;i++) {
			theta = i * 3.142 / 180;
			glVertex2f(0.03f * cos(theta), 0.1f + 0.03f * sin(theta));
		}
		glEnd();
	glPopMatrix();
}

//function to draw blades
void drawBlades(float angle) {

	glPushMatrix();
		glRotatef(angle ,0.0f, 0.0f, 1.0f);
		glLineWidth(4.0f);
		glBegin(GL_LINES);
			glColor3f(0.757f, 0.722f, 0.698f);
			//long lines
			glVertex2f(0.03f, 0.12f);
			glVertex2f(0.05f, 0.68f);

			glVertex2f(0.07f, 0.12f);
			glVertex2f(0.09f, 0.68f);

			glVertex2f(0.11f, 0.12f);
			glVertex2f(0.13f, 0.68f);

			//short lines
			glVertex2f(0.01f, 0.68f);
			glVertex2f(0.13f, 0.68f);

			glVertex2f(0.01f, 0.62f);
			glVertex2f(0.13f, 0.62f);

			glVertex2f(0.01f, 0.56f);
			glVertex2f(0.13f, 0.56f);

			glVertex2f(0.01f, 0.48f);
			glVertex2f(0.13f, 0.48f);

			glVertex2f(0.01f, 0.42f);
			glVertex2f(0.13f, 0.42f);

			glVertex2f(0.01f, 0.36f);
			glVertex2f(0.12f, 0.36f);

			glVertex2f(0.01f, 0.3f);
			glVertex2f(0.12f, 0.3f);

			glVertex2f(0.01f, 0.24f);
			glVertex2f(0.12f, 0.24f);

			glVertex2f(0.01f, 0.18f);
			glVertex2f(0.11f, 0.18f);

			glVertex2f(0.01f, 0.12f);
			glVertex2f(0.11f, 0.12f);
		glEnd();

	glPopMatrix();
}

//function to draw quad
void drawQuad(float xValue, float yValue) {

	glPushMatrix();
		glTranslatef(xValue, yValue, 0.0f);
		glBegin(GL_QUADS);
			glColor3f(0.451f, 0.329f, 0.251f);
			glVertex2f(-0.03f, 0.0f);
			glVertex2f(-0.03f, 0.03f);
			glVertex2f(0.03f, 0.03f);
			glVertex2f(0.03f, 0.0f);
		glEnd();
	glPopMatrix();
}

//function to draw tree
void drawTree(float xValue, float yValue, float angle) {

	glPushMatrix();
		glTranslatef(xValue, yValue, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);

		glLineWidth(7.0f);
		glBegin(GL_LINES);
			glColor3f(0.416f, 0.357f, 0.208f);
			glVertex2f(0.0f, 0.0f);
			glVertex2f(0.0f, 0.5f);
		glEnd();

		glBegin(GL_TRIANGLES);
			glColor3f(0.227f, 0.521f, 0.192f);
			glVertex2f(-0.2f, 0.2f);
			glVertex2f(0.2f, 0.2f);
			glVertex2f(0.0f, 0.3f);

			glColor3f(0.427f, 0.733f, 0.384f);
			glVertex2f(-0.18f, 0.23f);
			glVertex2f(0.18f, 0.23f);
			glVertex2f(0.0f, 0.35f);

			glColor3f(0.51f, 0.835f, 0.475f);
			glVertex2f(-0.16f, 0.26f);
			glVertex2f(0.16f, 0.26f);
			glVertex2f(0.0f, 0.45f);

			glColor3f(0.227f, 0.521f, 0.192f);
			glVertex2f(-0.16f, 0.3f);
			glVertex2f(0.16f, 0.3f);
			glVertex2f(0.0f, 0.4f);

			glColor3f(0.427f, 0.733f, 0.384f);
			glVertex2f(-0.14f, 0.33f);
			glVertex2f(0.14f, 0.33f);
			glVertex2f(0.0f, 0.45f);

			glColor3f(0.51f, 0.835f, 0.475f);
			glVertex2f(-0.1f, 0.36f);
			glVertex2f(0.1f, 0.36f);
			glVertex2f(0.0f, 0.55f);

			glColor3f(0.227f, 0.521f, 0.192f);
			glVertex2f(-0.12f, 0.4f);
			glVertex2f(0.12f, 0.4f);
			glVertex2f(0.0f, 0.5f);

			//glColor3f(0.427f, 0.733f, 0.384f);
			glColor3f(treeR, treeG, treeB);
			glVertex2f(-0.1f, 0.43f);
			glVertex2f(0.1f, 0.43f);
			glVertex2f(0.0f, 0.55f);

			

		glEnd();



	glPopMatrix();
}

//function to draw snow
void drawSnow(float xValue, float yValue) {
	glPushMatrix();

		glTranslatef(xValue, yValue ,0.0f);
		drawCircle(0.9f, 0.95f, 0.95f, -0.7f, 0.01f, 0.5f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.6f, 0.01f, 0.5f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.55f, 0.01f, 0.55f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.55f, 0.01f, 0.4f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.4f, 0.01f, 0.4f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.35f, 0.01f, 0.47f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.3f, 0.01f, 0.39f, 0.01);
		drawCircle(0.9f, 0.95f, 0.95f, -0.25f, 0.01f, 0.43f, 0.01);

	glPopMatrix();
}

//function to draw more snows
void drawMoreSnows(float xValue, float yValue) {
	glPushMatrix();

		glTranslatef(xValue, yValue, 0.0f);
		drawSnow(0.0f, 0.0f);
		drawSnow(0.5f, 0.2f);
		drawSnow(0.3f, 0.1f);
		drawSnow(0.7f, 0.1f);
		drawSnow(0.8f, 0.0f);
		drawSnow(0.8f, 0.2f);
		drawSnow(0.99f, 0.0f);

	glPopMatrix();
}


void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	

	switch (questionToDisplay) {

	case 1:
		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix();
			glTranslatef(x, y, 0.0f);

			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(-0.3f, 0.5f);
				glVertex2f(0.3f, 0.5f);
				glVertex2f(0.3f, 0.0f);
				glVertex2f(-0.3f, 0.0f);
			glEnd();

		glPopMatrix();

		glPushMatrix();
			glTranslatef(x2, y2, 0.0f);
			glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(-0.3f, 0.5f);
				glVertex2f(0.3f, 0.5f);
				glVertex2f(0.3f, 0.0f);
				glVertex2f(-0.3f, 0.0f);
			glEnd();
		glPopMatrix();
		break;

	case 2:	//WINDMILL 

		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//background
		drawCircle(0.722f, 0.875f, 0.914f, 0.0f, 1.0f, 0.05f, 0.8f);

		glEnd();

		if (snow) {
			//snow fall down
			glPushMatrix();
			glTranslatef(0.0f, snowfall, 0.0f);

			drawMoreSnows(0.0f, 0.0f);
			drawMoreSnows(0.13f, -0.1f);
			drawMoreSnows(0.05f, -0.2f);
			drawMoreSnows(0.0f, -0.3f);
			drawMoreSnows(-0.1f, -0.6f);
			drawMoreSnows(0.12f, -0.5f);
			drawMoreSnows(-0.1f, -0.8f);
			drawMoreSnows(0.0f, -0.7f);
			drawMoreSnows(0.1f, -0.5f);

			if (snowfall > -0.2f) snowfall -= 0.001f;
			else snowfall = 0.0f;
			glPopMatrix();
		}

		//ground-------------
		drawCircle(0.494f, 0.357f, 0.176f, 0.0f, 0.9f, -0.53f, 0.22f);
		drawCircle(r, g, b, 0.0f, 0.9f, -0.5f, 0.2f);
		drawCircle(r-0.13f, g-0.098f, b-0.094f, 0.0f, 0.8f, -0.5f, 0.15f);

		//drawCircle(0.573f, 0.737f, 0.243f, 0.0f, 0.9f, -0.5f, 0.2f);
		//drawCircle(0.443f, 0.639f, 0.149f, 0.0f, 0.8f, -0.5f, 0.15f);

		//tree----------------
		drawTree(-0.5f, -0.5f, 4.0f);
		drawTree(-0.7f, -0.55f, -3.0f);
		drawTree(-0.3f, -0.53f, -5.0f);
		drawTree(0.0f, -0.4f, 5.0f);
		drawTree(0.7f, -0.5f, -5.0f);

		glPushMatrix();
			glTranslatef(0.3f, 0.0f, 0.0f);
			//stand
			glBegin(GL_QUADS);
				glColor3f(0.62f, 0.447f, 0.341f); // Brown color
				glVertex2f(-0.3f, -0.47f);
				glVertex2f(-0.25f, 0.5f);
				glVertex2f(-0.1f, 0.5f);
				glVertex2f(-0.1f, -0.5f);
			glEnd();

			glBegin(GL_QUADS);
				glColor3f(0.549f, 0.404f, 0.302f); // Brown color
				glVertex2f(-0.1f, 0.5f);
				glVertex2f(-0.1f, -0.5f);
				glVertex2f(0.1f, -0.5f);
				glVertex2f(0.1f, 0.5f);
			glEnd();

			glBegin(GL_QUADS);
				glColor3f(0.482f, 0.357f, 0.267f); // Brown color
				glVertex2f(0.1f, -0.5f);
				glVertex2f(0.1f, 0.5f);
				glVertex2f(0.25f, 0.5f);
				glVertex2f(0.3f, -0.47f);
			glEnd();

			//roof
			glBegin(GL_TRIANGLES);
				//glColor3f(0.071f, 0.035f, 0.016f);
				glColor3f(roofR, roofG, roofB);
				glVertex2f(-0.3f, 0.5f);
				glVertex2f(0.3f, 0.5f);
				glVertex2f(0.0f, 0.8f);
			glEnd();

			//door---------
			glBegin(GL_QUADS);
				glColor3f(0.2f, 0.071f, 0.0f); // Brown color
				glVertex2f(-0.08f, -0.2f);
				glVertex2f(-0.08f, -0.46f);
				glVertex2f(0.08f, -0.46f);
				glVertex2f(0.08f, -0.2f);
			glEnd();

			drawCircle(0.2f, 0.071f, 0.0f, 0.0f, 0.079f, -0.21f, 0.06f);

			glBegin(GL_QUADS);
			glColor3f(0.29f, 0.114f, 0.0f); // Brown color
			glVertex2f(-0.06f, -0.2f);
			glVertex2f(-0.06f, -0.46f);
			glVertex2f(0.06f, -0.46f);
			glVertex2f(0.06f, -0.2f);
			glEnd();

			drawCircle(0.29f, 0.114f, 0.0f, 0.0f, 0.061f, -0.22f, 0.055f);

			//small quad to decorate
			drawQuad(0.02f, 0.0f);
			drawQuad(0.05f, -0.05f);
			drawQuad(0.0f, -0.1f);
			drawQuad(0.07f, -0.1f);
			drawQuad(-0.25f, -0.35f);
			drawQuad(-0.2f, -0.4f);
			drawQuad(-0.25f, -0.45f);
			drawQuad(-0.2f, 0.4f);
			drawQuad(-0.15f, 0.35f);
			drawQuad(0.2f, 0.3f);
			drawQuad(0.18f, 0.35f);

			/*
			glPushMatrix();
				//a lighter color to decorate the top of the tower
				glRotatef(-35.0f, 0.0f, 0.0f, 1.0f);
				drawCircle(0.361f, 0.294f, 0.239f, -0.42f, 0.02f, 0.45f, 0.13f);
			glPopMatrix();

			//top of the tower (curvy) 
			drawCircle(0.071f, 0.035f, 0.016f, 0.0f, 0.06f, 0.66f, 0.1f);
			*/

			//centre of the blades
			drawCircle(0.718f, 0.655f, 0.588f, 0.0f, 0.05f, 0.5f, 0.05f);
			drawCircle(0.38f, 0.337f, 0.298f, 0.0f, 0.035f, 0.5f, 0.035f);
			drawCircle(0.518f, 0.482f, 0.447f, 0.0f, 0.02f, 0.5f, 0.02f);
			

		glPopMatrix();

		//window------------------
		drawWindow(0.3f, 0.2f);
		drawWindow(0.1f, -0.15f);
		drawWindow(0.5f, -0.15f);
		
		//windmill-----------------
		glPushMatrix();

			glLineWidth(7.0f);
			glTranslatef(0.3f, 0.5f, 0.0f);
			glRotatef(angle, 0.0f, 0.0f, 1.0f);

			glBegin(GL_LINES);	//Blades line
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(0.0f, 0.02f);
				glVertex2f(0.0f, 0.7f);

				glVertex2f(-0.0f, -0.02f);
				glVertex2f(-0.0f, -0.7f);

				glVertex2f(-0.02f, 0.0f);
				glVertex2f(-0.7f, 0.0f);

				glVertex2f(0.02f, -0.0f);
				glVertex2f(0.7f, -0.0f);
				glEnd();
			glEnd();

			glPushMatrix();
				drawBlades(0.0f);	//first blade
				drawBlades(90.0f);	//second blade
				drawBlades(180.0f);	//third blade
				drawBlades(-90.0f);	//fourth blade
			glPopMatrix();

			if (clockwise) angle -= speed;
			else angle += speed;
		
		glPopMatrix();
		
		if (snow) {
			//change to snow color
			r += 0.005f;
			g += 0.005f;
			b += 0.005f;
			roofR += 0.005f;
			roofG += 0.005f;
			roofB += 0.005f;
			treeR += 0.005f;
			treeG += 0.005f;
			treeB += 0.005f;

			//a snow ball rolling
			glPushMatrix();
				glTranslatef(snowballRoll, 0.0f, 0.0f);
				drawCircle(0.8f, 0.85f, 0.85f, 0.0f, 0.1f, -0.5f, 0.1f);
				if (snowballRoll >= -0.7f) snowballRoll -= 0.0001f;
				else snowballRoll = 0.0001f;
			glPopMatrix();
			
		}
		else {
			//change to original color
			if (r > 0.573) r -= 0.01f;
			if (g > 0.737) g -= 0.01f;
			if (b > 0.243) b -= 0.01f;
			if (roofR > 0.071) roofR -= 0.01f;
			if (roofG > 0.035) roofG -= 0.01f;
			if (roofB > 0.016) roofB -= 0.01f;
			if (treeR > 0.427) treeR -= 0.01f;
			if (treeG > 0.733) treeG -= 0.01f;
			if (treeB > 0.384) treeB -= 0.01f;
		}


		break;


	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, "Windmill", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------