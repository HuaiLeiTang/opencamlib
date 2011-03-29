#ifndef GLWIDGET
#define GLWIDGET

#include <QObject>
#include <QGLBuffer>
#include <QVarLengthArray>
#include <QtGui>
#include <QTimer>

#include <boost/foreach.hpp> 

#include <iostream>
#include <cassert>
#include <set>
#include <vector>

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + (i))

#include "gldata.h"


class GLWidget : public QGLWidget {
    Q_OBJECT
    public:
        GLWidget( QWidget *parent=0, char *name=0 ) ;
        ~GLWidget() {
        }

        void initializeGL();
        /// add new GLData object and return pointer to it.
        GLData* addObject() {
            GLData* g = new GLData();
            glObjects.push_back(g);
            return g;
        }
    protected:
        
        void resizeGL( int width, int height );
        void paintGL();

        void keyPressEvent( QKeyEvent *e ) {
            std::cout << e->key() << " pressed.\n";
            return;
        }
        void timeOut() {
            z=z-0.1;
            updateGL();
        }
        
        void genVBO() {
            BOOST_FOREACH(GLData* g, glObjects) {
                g->genVBO();
            }
        }


    protected slots:
        void timeOutSlot() {
            timeOut();
        }
  
    private:
        std::vector<GLData*> glObjects;
        GLfloat z;
        QTimer* timer;
};
#endif
