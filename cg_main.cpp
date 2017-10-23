//includes do QT
#include <QApplication>
#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>

//includes do open gl
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

#define max 5

#define PI 3.1416
#define radius 50

int inc_x = 15, inc_y = 15;

int min_x = -500, max_x = 500;
int min_y = -500, max_y = 500;

int pos_x = 0;
int pos_y = 0;

int angle = 0;

class JanelaGL : public QGLWidget
{
    public:
        JanelaGL (){
            setFocusPolicy(Qt::TabFocus);
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
        }

		void keyPressEvent (QKeyEvent *e)
		{
			std::cout << angle;
			if (e->key() == Qt::Key_Escape || e->key() == Qt::Key_Q)
				exit (0);
			else
			{
				if (e->key() == Qt::Key_Up){
					if(angle <= -180){
						angle+=0;
					}else{
						angle+=10;
					}
				}else if (e->key() == Qt::Key_Down){
					if(angle >= 180){
						angle-=0;
					}else{
						angle-=10;
					}
				}else if (e->key() == Qt::Key_Right){
					pos_x+=10;
				}else if (e->key() == Qt::Key_Left){
					pos_x-=10;
				}
			}
		}

		void tank(){		
			glColor3f(0.0f, 0.0f, 1.0f); 

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();					//criar camada
				glTranslatef(5+pos_x,40,0);		//movi a tela
				glRotatef(angle,0,0,1.0);	//rotacionar
				glTranslatef (0,-20,0);		//desfiz moviment.
						glBegin (GL_QUADS);
							glVertex2i (0,30);
							glVertex2i (100,30);
							glVertex2i (100,10);
							glVertex2i (0,10);
						glEnd();
			glPopMatrix();					//mesclar camada



			circulo(((-80+pos_x)+(80+pos_x))/2, 30+pos_y, 25);

			glBegin(GL_POLYGON);
				glVertex2i(-50+pos_x,30+pos_y);
				glVertex2i(50+pos_x,30+pos_y);

				glVertex2i(80+pos_x,-10+pos_y);

				glVertex2i(20+pos_x,-20+pos_y);
				glVertex2i(-20+pos_x,-20+pos_y);

				glVertex2i(-80+pos_x,-10+pos_y);
			glEnd();


            glColor3f(0.0f, 1.0f, 1.0f);  			

			circulo(80+pos_x, -10+pos_y, 15);
			circulo(-80+pos_x, -10+pos_y, 15);
           
			circulo(0+pos_x, -20+pos_y, 15);
			circulo(40+pos_x,-20+pos_y, 15);
			circulo(-40+pos_x,-20+pos_y, 15);


		}

		void quadradinho(int pos_x, int pos_y, int size_x, int size_y){
			
			int min_x = pos_x, max_x = pos_x+size_x;
			int min_y = pos_y, max_y = pos_y+size_y;

			glBegin(GL_LINE_LOOP);	
				glVertex2i (min_x,min_y);
				glVertex2i (max_x,min_y);
				glVertex2i (max_x,max_y);
				glVertex2i (min_x,max_y);
			glEnd();

		}

		void circulo(int pos_x, int pos_y, int raio){

			glBegin (GL_POLYGON);
				for (float i=0; i<2*PI;i+=.1)
					glVertex2f(sin(i)*raio + pos_x,cos(i)*raio + pos_y);
			glEnd();
 
		}

        void updateGL (){
            glClear(GL_COLOR_BUFFER_BIT);

            glColor3f(0.0f, 0.0f, 1.0f); 

			tank();

			//glClear(GL_COLOR_BUFFER_BIT);

			// Especifica que a cor corrente é azul
			glColor3f(0.0f, 0.0f, 1.0f);              
			glBegin(GL_POLYGON);

			glEnd();
	


            swapBuffers();
        }
        QSize sizeHint() const
        {
            return QSize(1024, 768);
        }

    protected:
        void initializeGL(){
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1024, 1024, -600, 600, 0.0f, 1.0f);
			//glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
            resizeGL(1024,728);

        }
        void resizeGL(int w, int h)
        {
            glViewport(0, 0, w, h);
        }
};

QApplication *app;
JanelaGL *glWindow;
QWidget *qtWindow;

int main (int argc, char** argv)
{
    app = new QApplication (argc, argv);

    qtWindow = new QWidget();
    glWindow = new JanelaGL ();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWindow);

    qtWindow->setLayout(mainLayout);

    QTimer *timer = new QTimer (app);
    app->connect (timer,SIGNAL(timeout()), glWindow, SLOT(updateGL ()));
    timer->start (35);

    qtWindow->setWindowTitle ("App Max");
    qtWindow->show ();

    return (app->exec());
}
