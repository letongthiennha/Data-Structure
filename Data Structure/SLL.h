#pragma once
#include"SLLOperation.h"
#include "SLLNode.h"
#include "Setting.h"
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>



class SLL {
private:
	//====================Logic====================
    SLLNode* m_pHead;
    listFunctionWithParameter::operation_type m_current_function; 

    //====================Control State========================
    bool isPausing;
    bool m_skipCurrentStep;
    float LinkedListSpeed=LinkedListDefaultSpeed;
    std::queue<listFunctionWithParameter> functionQueue;
	operateInfo currOperationInfo;

    //====================Outside Element================
    //Code block
    int highlighted_line;
    //Message Log
    std::string messageLog;

public:
    SLL();
    //LoadFile
    void LoadFromFile(std::string path);
	//====================State Control================
    void storeOperation(listFunctionWithParameter::operation_type type, int firstParameter, int secondParameter = 0);
    //==============State Control================
    void setStop(bool paused);
    bool isStop() const;
    void setSpeed(float speed);
    float getSpeed() const;

	//=========Skip===========
    void setSkip();
    void Forward();

    //Update
    void update();

    //====================Render================
    void render();

    void create(std::vector<int> vals);
    void randomCreate(int amount);

private:
    void renderCode();
    void renderList();

    //Handle operation input
    void handleOperationsInput();
    //Assure to complete the current operation before moving to the next
    void updateOperations();
    void updateAnimation();
    //==============Function===========
    void updateForInsert();
    void updateForRemove();
    void updateForSearch();
    void updateForChangingValue();
	//====================Skip================
	void skipUpdate();
    void skipInsert();
	void skipRemove();
	void skipFind();



	//====================State Control================
    void resetOperation();
    //======================Reset==================
    void repositionNodeSlowly();
    void repositionNode();
    void resetList();

};
