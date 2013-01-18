#include "pch.h"
#include "Layer3D.h"

Layer3D::Layer3D()
{
}

Layer3D::~Layer3D()
{
}

bool Layer3D::init()
{
    CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture);
    setShaderProgram(program);

    CCScheduler *s = CCDirector::sharedDirector()->getScheduler();
    s->scheduleUpdateForTarget(this, 0, false);

    m_pTexture = CCTextureCache::sharedTextureCache()->addImage("mmbg.png");

    m_fYav = 30.f;
    m_fPitch = 45.f;
    m_fRoll = 0;

    m_fSpeed = 80;

    return true;
}

void Layer3D::draw()
{
    CCDirector::sharedDirector()->setDepthTest(true);

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords ); 
    getShaderProgram()->use();


    CCSize size = CCDirector::sharedDirector()->getWinSize();

    float scale = size.width/640.f;

    kmMat4 matrixP;
    kmMat4 matrixMV;
    kmMat4 matrixMVP;

    kmGLGetMatrix(KM_GL_PROJECTION, &matrixP );
    kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV );

    kmQuaternion quat;
    kmQuaternionRotationYawPitchRoll(&quat, m_fYav, m_fPitch, m_fRoll);

    kmMat3 rotation;
    kmMat3RotationQuaternion(&rotation, &quat);

    kmVec3 translation;
    kmVec3Fill(&translation, size.width/2, size.height/2.2f, 0);

    kmMat4 rotationAndMove;
    kmMat4RotationTranslation(&rotationAndMove, &rotation, &translation);

    kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);
    kmMat4Multiply(&matrixMVP, &matrixMVP, &rotationAndMove); // apply rotation and translation to the matrix

    GLuint matrixId = glGetUniformLocation(getShaderProgram()->getProgram(), "CC_MVPMatrix");
    getShaderProgram()->setUniformLocationWithMatrix4fv(matrixId, matrixMVP.mat, 1);

    ccGLBindTexture2D( m_pTexture->getName() );

    ccVertex3F vertices[4];
    ccVertex2F uv[4];
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, uv);
    float x = 0;
    float y = 0;
    float len = 40*scale;
    /////////// front
    vertices[0] = vertex3(x-len,y-len,len);
    vertices[1] = vertex3(x-len,y+len,len);
    vertices[2] = vertex3(x+len,y-len,len);
    vertices[3] = vertex3(x+len,y+len,len);
    uv[0] = vertex2(0, 1);
    uv[1] = vertex2(0, 0);
    uv[2] = vertex2(1, 1);
    uv[3] = vertex2(1, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ////////// right
    vertices[0] = vertex3(x+len,y-len,len);                        
    vertices[1] = vertex3(x+len,y+len,len);
    vertices[2] = vertex3(x+len,y-len,-len);
    vertices[3] = vertex3(x+len,y+len,-len);
    uv[0] = vertex2(0, 1);
    uv[1] = vertex2(0, 0);
    uv[2] = vertex2(1, 1);
    uv[3] = vertex2(1, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ///////// back
    vertices[0] = vertex3(x+len,y-len,-len);        
    vertices[1] = vertex3(x+len,y+len,-len);
    vertices[2] = vertex3(x-len,y-len,-len);
    vertices[3] = vertex3(x-len,y+len,-len);
    uv[0] = vertex2(0, 1);
    uv[1] = vertex2(0, 0);
    uv[2] = vertex2(1, 1);
    uv[3] = vertex2(1, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ////////// left
    vertices[0] = vertex3(x-len,y-len,len);                        
    vertices[1] = vertex3(x-len,y+len,len);
    vertices[2] = vertex3(x-len,y-len,-len);
    vertices[3] = vertex3(x-len,y+len,-len);
    uv[0] = vertex2(0, 1);
    uv[1] = vertex2(0, 0);
    uv[2] = vertex2(1, 1);
    uv[3] = vertex2(1, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ///////// top
    vertices[0] = vertex3(x+len,y+len,len);        
    vertices[1] = vertex3(x-len,y+len,len);
    vertices[2] = vertex3(x+len,y+len,-len);
    vertices[3] = vertex3(x-len,y+len,-len);
    uv[0] = vertex2(0, 0);
    uv[1] = vertex2(1, 0);
    uv[2] = vertex2(0, 1);
    uv[3] = vertex2(1, 1);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    ///////// bottom
    vertices[0] = vertex3(x+len,y-len,len);        
    vertices[1] = vertex3(x-len,y-len,len);
    vertices[2] = vertex3(x+len,y-len,-len);
    vertices[3] = vertex3(x-len,y-len,-len);
    uv[0] = vertex2(0, 0);
    uv[1] = vertex2(1, 0);
    uv[2] = vertex2(0, 1);
    uv[3] = vertex2(1, 1);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}

Layer3D * Layer3D::create()
{
    Layer3D *pRet = new Layer3D();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void Layer3D::update( float fDelta )
{
    if (fDelta > 0.0167f)
        fDelta = 0.0167f;

    m_fYav += fDelta * m_fSpeed;
    m_fPitch += fDelta * m_fSpeed;
    m_fRoll += fDelta * m_fSpeed;
}
