//includes do QT
#include <QApplication>
#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QTimer>
#include <iostream>

#include <string> 
#include <sstream>
//includes do open gl
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>

#define max 5

#define PI 3.14159265 
#define radius 50


//To-Do == Fazer um array com os valos dos Y's ondulados.

// fast tanks

//Controles
	
float forca = 0;
float forcaPonteiro = 600;
int ForcaInc_y = 10;

//player 01
float 	play1_vida = 1000;
float   play1_podePercorrerRodada = 10;

int 	play1_posicaoTank_x = 0;
int 	play1_posicaoTank_y = 0;
float 	play1_angle = 0;
//DISTANCIA


int 	play1_Bala1 = 3;
int 	play1_Bala2 = 3;

//player 02
float 	play2_vida = 1000;
float   play2_podePercorrerRodada = 10;

int 	play2_posicaoTank_x = 0;
int 	play2_posicaoTank_y = 0;
float 	play2_angle = 0;

int 	play2_Bala1 = 3;
int 	play2_Bala2 = 3;
//
	


int inc_x = 15, inc_y = 15;

int min_x = -500, max_x = 500;
int min_y = -500, max_y = 500;

int pos_x = 0;
int pos_y = 0;

float angle = 0;
int tamanho = 0;

int x_Bala = 0;
int y_Bala = 0;

class JanelaGL : public QGLWidget
{
    public:
        JanelaGL (){
            setFocusPolicy(Qt::TabFocus);
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
        }

		void painel(){

			glColor3f(0.2f, 0.1f, 0.6f);			 
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_POLYGON);
				glVertex2d(-1024, 728);
				glVertex2d(-100, 728);
				glVertex2d(-350, 400);
				glVertex2d(-1024, 450);
			glEnd();
			glBegin(GL_POLYGON);
				glVertex2d(1024, 728);
				glVertex2d(100, 728);
				glVertex2d(350, 400);
				glVertex2d(1024, 450);
			glEnd();

			//Triangulo da força
			glBegin(GL_POLYGON);
				glVertex2d(0, 600);
				glVertex2d(50, 400);
				glVertex2d(-50, 400);
			glEnd();
			glColor3f(1.0f, 0.0f, 0.0f); 
			glBegin(GL_LINES);
				glVertex2d(-50, forcaPonteiro);
				glVertex2d(50, forcaPonteiro);
			glEnd();

			forcaPonteiro+=ForcaInc_y;

			if (forcaPonteiro+ForcaInc_y<400 || forcaPonteiro+ForcaInc_y>600) ForcaInc_y*=-1;


			glColor3f(1.0f, 1.0f, 1.0f); 
			
			//Nome dos jogadores
			//QString::number(angle)
			renderText (-1000,650,0.,*new QString("JOGADOR 1"),*new QFont ("Arial", 13),2000); 	//Player 1
			renderText (-1000,580,0.,*new QString("Vida: "+QString::number(play1_vida)+"%"),*new QFont ("Arial", 12),2000); //Player 2
			renderText (-1000,510,0.,*new QString("Angulo: "+QString::number(angle)+"'"),*new QFont ("Arial", 12),2000); //Player 2

			renderText (-700,650,0.,*new QString("Tipos de Municao"),*new QFont ("Arial", 12),2000);
			renderText (-700,600,0.,*new QString("Normal: infinita ('Espaco')"),*new QFont ("Arial", 11),2000);
			renderText (-700,550,0.,*new QString("BigFriend: " + QString::number(play1_Bala1) + " (letra 'Q')"),*new QFont ("Arial", 11),2000);
			renderText (-700,500,0.,*new QString("TriBomb: " + QString::number(play1_Bala2) + " (letra 'W')"),*new QFont ("Arial", 11),2000);


			renderText (770,650,0.,*new QString("JOGADOR 2"),*new QFont ("Arial", 13),2000); 	//Player 2
			renderText (770,580,0.,*new QString("Vida: " + QString::number(play2_vida)+"%"),*new QFont ("Arial", 12),2000); //Player 2
			renderText (770,510,0.,*new QString("Angulo: "+QString::number(angle)+"'"),*new QFont ("Arial", 12),2000); //Player 2

			renderText (300,650,0.,*new QString("Tipos de Municao"),*new QFont ("Arial", 12),2000);
			renderText (300,600,0.,*new QString("Normal: infinita ('Espaco')"),*new QFont ("Arial", 11),2000);
			renderText (300,550,0.,*new QString("BigFriend: " + QString::number(play2_Bala1) + " (letra 'Q')"),*new QFont ("Arial", 11),2000);
			renderText (300,500,0.,*new QString("TriBomb: " + QString::number(play2_Bala2) + " (letra 'W')"),*new QFont ("Arial", 11),2000);


			renderText (-65,650,0.,*new QString("FORCA"),*new QFont ("Arial", 12),2000);

			glColor3f(0.8f, 0.9f, 0.2f); 

		}

		void flor(){
			glBegin(GL_POLYGON);
			glVertex2d(-1200, -1000);
			glVertex2d(-1024, -600);
			float altura_flor = -600;
			for(int i = -1000; i < 1024; i++){
				
				if(i<-600){	
					altura_flor = altura_flor - 0.2;			
				}else if(i>=-600 && i<-300){
					altura_flor = altura_flor + 0.5;								
				}else if(i>=-300 && i<-200){
					altura_flor = altura_flor-0.4;
				}else if(i>=-200 && i<0){
					altura_flor = altura_flor+0.5;
				}else if(i>=0 && i<250){
					altura_flor = altura_flor-0.4;					
				}else if(i>=250 && i<500){
					altura_flor = altura_flor+0.3;					
				}else{
					altura_flor = altura_flor-0.2;					
				}

				glVertex2d(i, altura_flor);
			}
		
				glVertex2d(1024, -600);
				glVertex2d(1200, -1000);
			glEnd();
		}


		void keyPressEvent (QKeyEvent *e)
		{
			//std::cout << angle;
			if (e->key() == Qt::Key_Escape || e->key() == Qt::Key_Q)
				exit (0);
			else
			{
				if (e->key() == Qt::Key_Up){
					if(angle >= 90){
						angle+=0;
					}else{
						angle+=5;
					}
				}else if (e->key() == Qt::Key_Down){
					if(angle <= 0){
						angle-=0;
					}else{
						angle-=5;
					}
				}else if (e->key() == Qt::Key_Right){
					pos_x+=5;
				}else if (e->key() == Qt::Key_Left){
					pos_x-=5;
				}else if (e->key() == Qt::Key_Space){
					projetil();
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

			x_Bala = 5+pos_x;
			y_Bala = 40;

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


		void projetil(){
			float aux = 20;
		
			while(aux != 0){
//				x_Bala = x_Bala + 10*cos(angle);
//				y_Bala = y_Bala + 10*sin(angle);

				x_Bala = x_Bala + (20*(cos((angle*2*PI)/360)));
				y_Bala = y_Bala + (aux*(sin((angle*2*PI)/360)));
				aux = aux - 0.5;
				circulo(x_Bala, y_Bala, 5);
				//aux++;
				swapBuffers();
			}
			//X = X + Força * cos (Ângulo)
			//Y = Y + Força * sin (Ângulo)  		

			//circulo()

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
			glColor3f(0.3f, 0.3f, 1.0f); 
			painel();
			flor();
			renderText(0,0,0.,*new QString("JOGADOR 1"),*new QFont ("Arial", 12),2000); 
			renderText(0,0,0.,*new QString(QString::number(angle)),*new QFont ("Arial", 12),2000);

			renderText(0,100,0.,*new QString("MAXSUEL"),*new QFont ("Arial", 12),2000);

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
            glOrtho(-1024, 1024, -728, 728, 0.0f, 1.0f);
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
