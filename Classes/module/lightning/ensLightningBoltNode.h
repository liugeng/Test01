

#ifndef __HelloCpp__ensLightningBoltNode__
#define __HelloCpp__ensLightningBoltNode__

#include <iostream>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;
#include "ensCommon.h"
namespace_ens_begin

namespace lightningBolt{
    class ClineSeg{
    public:
        Point startPoint;
        Point endPoint;
        Point branchEndPoint;//only seed seg store this
        int branchID;//which branch the seg belongs to. branchID==0 means belongs to mainBranch
        int branchStartGenerationID;//in which generation the branch this seg belongs to start generated.
        int generationID;//this seg created in which generation, the original seg's generationID is 0
        ClineSeg*father;
        vector<ClineSeg*> childList;
        bool needReGenerate;//whether the branch use this seg as root seg need to regenerate
    public:
        ClineSeg(){
            initParameter();
        }
        ClineSeg(Point start,Point end){
            initParameter();//do not forget this
            init(start, end);
        }
        virtual~ClineSeg(){}
        void init(Point start,Point end);
        bool addChildRef(ClineSeg*child);
        bool removeChildRef(ClineSeg*child);
        float getLen()const;
        Point getDir()const;
        Point getVec()const;
        Point getRightNormal()const;
        Point getMidPoint()const;
    protected:
        void initParameter(){
            branchID=-1;
            branchStartGenerationID=-1;
            generationID=-1;
            father=NULL;
            needReGenerate=false;
        }
    };
}
namespace lightningBolt {
    

    
    class ClightningBoltSprite:public Sprite
	//ref to: http://drilian.com/2009/02/25/lightning-bolts/
    {
    public:
        ClightningBoltSprite(){
            m_mainSegLen=14;
            m_k_offset=0.13;
            updateNGeneration();
            m_headSeg=NULL;
            m_tailSeg=NULL;
            m_program=NULL;
            m_indexVBO=NULL;
            m_isDrawDebug=false;
            m_percentageOfJitterBranch=0.5;
            m_opacityZoom=1.2;//1.2;
            m_mesh=NULL;
        }
        virtual ~ClightningBoltSprite(){
            if(m_program)m_program->release();
            if(m_indexVBO)m_indexVBO->release();
            if(m_mesh)m_mesh->release();
        }
        void updateNGeneration();
//        void draw();
        bool init();
         void setStartAndEnd(Point start,Point end);
    //    void setEndPoint(Point endPointWorld);
    //    void setStartPoint(Point startPointWorld);
        void genLighting();
        void doJitter();
		bool getIsDrawDebug()const{return m_isDrawDebug;}
		void setIsDrawDebug(bool value){m_isDrawDebug=value;}
    protected:
        //----init program
        void initProgram();
        //----generate lighting
        void genSeges();
        void genMesh();
        vector<lightningBolt::ClineSeg*> genSegesFromBranchSeg(lightningBolt::ClineSeg*branchSeg,int nGeneration);
        vector<lightningBolt::ClineSeg*> splitSeg(lightningBolt::ClineSeg*seg,int generationID);
        //----jitter
        void releaseNeedReGenBranch(vector<lightningBolt::ClineSeg*>&branchList,vector<lightningBolt::ClineSeg*>&segList);
        void releaseNeedReGenBranch_inn(lightningBolt::ClineSeg*seg,vector<lightningBolt::ClineSeg*>&segList);
        //----debug draw
        void debugDraw_segWireFrame(float lineWidth);
        void debugDraw_segLineAndDot(float lineWidth,float pointSize);
    protected:
        //shader program
        CGLProgramWithUnifos*m_program;
        //core data of lightning
        Point m_startPoint_parentSpace;//parent space start point
        Point m_endPoint_parentSpace;//parent space end point
        Point m_startPoint;//local space start point
        Point m_endPoint;//local space end point
        vector<lightningBolt::ClineSeg*> m_segList;//hold seges compose the lighting
        int m_nGeneration;//split how many generations
        lightningBolt::ClineSeg*m_headSeg;//the lighting tree's main branch's head seg
        lightningBolt::ClineSeg*m_tailSeg;//the lighting tree's main branch's tail seg
        //model
        Cmesh* m_mesh;
        CindexVBO*m_indexVBO;
        //settings
        float m_k_offset;
        float m_mainSegLen;
        float m_percentageOfJitterBranch;
        float m_opacityZoom;
		bool m_isDrawDebug;
    };
}
namespace lightningBolt {
    class CflashAction;
}
class ClightningBoltNode:public Node
{
public:
    friend class lightningBolt::CflashAction;
public:
    ClightningBoltNode(){
        m_lbSprite=NULL;
        m_lbSprite2=NULL;
		m_isDrawDebug=false;
    }
    virtual~ClightningBoltNode(){}
    bool init(const Point&start,const Point&end);
    void setStartAndEnd(const Point&start,const Point&end){
        m_start=start;
        m_end=end;
        m_lbSprite->setStartAndEnd(m_start, m_end);
        m_lbSprite2->setStartAndEnd(m_start, m_end);
    }
/*    void setStart(const Point&point){
        m_start=point;
        m_lbSprite->setStartPoint(m_start);
        m_lbSprite2->setStartPoint(m_start);
    }
    void setEnd(const Point&point){
        m_end=point;
        m_lbSprite->setEndPoint(m_end);
        m_lbSprite2->setEndPoint(m_end);
    }*/
    Point getStart()const{return m_start;}
    Point getEnd()const{return m_end;}
	bool getIsDrawDebug()const{
		assert(m_lbSprite->getIsDrawDebug()==m_isDrawDebug);
		assert(m_lbSprite2->getIsDrawDebug()==m_isDrawDebug);
		return m_isDrawDebug;
	}
	void setIsDrawDebug(bool value){
		m_isDrawDebug=value;
		m_lbSprite->setIsDrawDebug(value);
		m_lbSprite2->setIsDrawDebug(value);
	}
protected:
    Point m_start;//parent space start point
    Point m_end;//parent space end point
    lightningBolt::ClightningBoltSprite*m_lbSprite;
    lightningBolt::ClightningBoltSprite*m_lbSprite2;
	bool m_isDrawDebug;


};

//namespace lightningBolt {
//    class CflashAction : public ActionInterval
//    //ref to CCRotateBy
//    //why use action: http://user.qzone.qq.com/350479720/blog/1403318648
//    {
//    public:
//        //creates the action
//        //if fDuration pass -1, will flash forever
//        static CflashAction* create(float fDuration,float oneFlashTime);
//        //initializes the action
//        //if fDuration pass -1, will flash forever
//        bool initWithDuration(float fDuration,float oneFlashTime);
//        virtual void stop();
//        virtual void startWithTarget(Node *pTarget);
//        virtual void update(float time);
//        virtual bool isDone() const;
//		virtual void step(float dt) {}
//        CflashAction(){initMembers();}
//        virtual~CflashAction(){
//        }
//		virtual CflashAction* reverse() const override = 0;
//		virtual CflashAction* clone() const override = 0;
//    protected:
//        void startAnimation(Node*pTarget);
//        void stopAnimation(Node*pTarget);
//        void callBack_flashForever(Node*sender);
//        void callBack_genLightning(Node* sender);
//        void callBack_jitter(Node*sender);
//        void callBack_resetOpacity(Node*sender);
//    protected:
//        void initMembers(){
//            m_timeFoe=0;
//            m_timeCur=0;
//            m_oneFlashTime=0;
//            m_jitterTimeOfOneFlash=0;
//            m_jitterInterval=0;
//            m_isDoJitter=true;
//            m_startOpacity=255;
//            m_endOpacity=80;
//        }
//    protected:
//        float m_timeFoe;
//        float m_timeCur;
//    protected:
//        float m_oneFlashTime;
//        float m_jitterTimeOfOneFlash;
//        float m_jitterInterval;
//        bool m_isDoJitter;
//        GLubyte m_startOpacity;//start opacity of one flash
//        GLubyte m_endOpacity;//end opacity of one flash
//    };
//
//}
namespace_ens_end
#endif /* defined(__HelloCpp__ensLightingSprite__) */
