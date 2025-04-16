#include "SLL.h"
#include "Motion.h"
#include "Pointer.h"
#include <random>
#include"Setting.h"

SLL::SLL() {
	m_current_function = listFunctionWithParameter::operation_type::NONE;
    m_pHead = nullptr;
	highlighted_line = 0;
	messageLog = "";
	isPausing = false;
	m_skipCurrentStep = false;
	LinkedListSpeed = 1.0f;
}



//====================State Control================
//Speed
void SLL::setSpeed(float newSpeed) { LinkedListSpeed = newSpeed; }
float SLL::getSpeed() const { return LinkedListSpeed; }
void SLL::setStop(bool paused) { isPausing = paused; }
bool SLL::isStop() const { return isPausing; }

void SLL::storeOperation(listFunctionWithParameter::operation_type functionType, int firstParameter, int secondParameter) {
    functionQueue.push(listFunctionWithParameter(functionType, firstParameter, secondParameter));
}
void SLL::updateOperations() {
    if (m_current_function == listFunctionWithParameter::operation_type::NONE||m_current_function==listFunctionWithParameter::operation_type::RANDOM) return;
    SLLNode* pCurr = m_pHead;
    while (pCurr) {
        if (pCurr->m_currentAnimation) {
            return;
        }
        pCurr = pCurr->m_pNext;
    }

    switch (m_current_function){

    case listFunctionWithParameter::operation_type::INSERT: updateForInsert(); break;

    case listFunctionWithParameter::operation_type::REMOVE: updateForRemove(); break;

    case listFunctionWithParameter::operation_type::FIND: updateForSearch(); break;

    case listFunctionWithParameter::operation_type::UPDATE: updateForChangingValue(); break;
    }
}

//====================Skip========================
void SLL::setSkip() { m_skipCurrentStep = true; }

void SLL::Forward() {
    switch (m_current_function) {
    case listFunctionWithParameter::INSERT: skipInsert(); break;
    case listFunctionWithParameter::REMOVE: skipRemove(); break;
    case listFunctionWithParameter::FIND: skipFind(); break;
    case listFunctionWithParameter::UPDATE: skipUpdate(); break;
    }
}

void SLL::skipInsert() {
    if (m_current_function != listFunctionWithParameter::INSERT) return;
	SLLNode*& newNode = currOperationInfo.newNode;
    if (!m_pHead) {
        newNode->m_currentPosition = LinkedListInitPosition;
        newNode->m_destination = newNode->m_currentPosition;
        m_pHead = newNode;
        return;
    }
    
    SLLNode* pCurr = m_pHead;
    while (pCurr->m_pNext) {
        pCurr = pCurr->m_pNext;
    }

    pCurr->m_currentAnimation = nodeAnimation::IDLE;
    pCurr->m_animationPhase = 0.0f;
    pCurr->m_isHighlight = false;

	float newX = pCurr->m_currentPosition.x + pointerLength;
    float newY = LinkedListInitPosition.y;
    Vector2 pos = { newX,newY };
    newNode->m_currentPosition = pos;
    newNode->m_destination = pos;
    newNode->m_opacity = 1.0f;

    pCurr->m_pNext = newNode;
    highlighted_line = 10;
    
    int val = 0;
    if (newNode) {
        val = newNode->m_val;
    }

    messageLog = std::to_string(val) + " was added to the list";
    newNode = nullptr;
    resetOperation();
}
void SLL::skipRemove() {
    if (m_current_function != listFunctionWithParameter::REMOVE) return;

    if (!m_pHead) {
        messageLog = "Empty list";
        resetOperation();
        return;
    }

    if (m_pHead->m_val == currOperationInfo.removeVal) {
        SLLNode* temp = m_pHead;
        m_pHead = m_pHead->m_pNext;
        delete temp;
        repositionNode();
        
        messageLog = "Deleted node with value " + std::to_string(currOperationInfo.removeVal) + ".";
        resetOperation();
        return;
    }

    SLLNode* pCurr = m_pHead;
    while (pCurr->m_pNext) {
        pCurr->m_currentAnimation = nodeAnimation::IDLE;
        pCurr->m_animationPhase = 0.0f;
        pCurr->m_isHighlight = false;
        if (pCurr->m_pNext->m_val == currOperationInfo.removeVal) {

            SLLNode* del = pCurr->m_pNext;
            pCurr->m_pNext = del->m_pNext;
            delete del;

            repositionNode();
            messageLog = "Deleted " + std::to_string(currOperationInfo.removeVal) + ".";
            resetOperation();
            return;
        }
        pCurr = pCurr->m_pNext;
    }

    messageLog = std::to_string(currOperationInfo.removeVal) + " not found.";
    resetOperation();
}
void SLL::skipFind() {
    if (m_current_function != listFunctionWithParameter::FIND) return;
    currOperationInfo.isFound = false;

    if (!currOperationInfo.currNode) {
        messageLog = "Not Found.";
        resetOperation();
        return;
    }

    SLLNode*& pCurr = currOperationInfo.currNode;
    while (pCurr) {
        pCurr->m_currentAnimation = static_cast<nodeAnimation> (1);
        pCurr->m_animationPhase = 0.0f;
        pCurr->m_isHighlight = false;
        if (pCurr->m_val == currOperationInfo.findVal) {
            messageLog = "Found " + std::to_string(currOperationInfo.findVal) ;
            currOperationInfo.isFound = true;
            resetOperation();
            return;
        }
        pCurr = pCurr->m_pNext;
    }
    messageLog = " Not found.";
    resetOperation();
}
void SLL::skipUpdate() {
    if (m_current_function != listFunctionWithParameter::UPDATE) return;

    if (!currOperationInfo.currNode) {
        messageLog = "Not Found";
        resetOperation();
        return;
    }

    SLLNode* &pCurr = currOperationInfo.currNode;
    while (pCurr) {
        pCurr->m_currentAnimation = nodeAnimation::IDLE;
        pCurr->m_animationPhase = 0.0f;
        pCurr->m_isHighlight = false;
        if (pCurr->m_val == currOperationInfo.oldVal) {

            pCurr->m_val = currOperationInfo.newVal;
            pCurr->m_opacity = 1.0f;
            
            messageLog = "Changed " + std::to_string(currOperationInfo.oldVal) + " to " + std::to_string(currOperationInfo.newVal) ;
            resetOperation();
            return;
        }
        pCurr = pCurr->m_pNext;
    }

    messageLog = "Not found";
    resetOperation();
}



//=================Function=======================
void SLL::updateForInsert() {
    if (!currOperationInfo.isStarted) return;

    // Handle inserting the first node
    if (!m_pHead) {
        highlighted_line = 1;
        int val = 0;
        if (currOperationInfo.newNode) {
            val = currOperationInfo.newNode->m_val;
        }
        messageLog = std::to_string(val) + " was added to the list";

        currOperationInfo.newNode->m_currentPosition = LinkedListInitPosition;
        currOperationInfo.newNode->m_destination = LinkedListInitPosition;

        m_pHead = currOperationInfo.newNode;
        currOperationInfo.newNode = nullptr;

        resetOperation();
        return;
    }

    highlighted_line = 4;
    highlighted_line = 5;

    if (!currOperationInfo.currNode)
        currOperationInfo.currNode = m_pHead;

    SLLNode*& currNode = currOperationInfo.currNode;


    if (currNode->m_pNext) {
        highlighted_line = 6;
        currNode->m_currentAnimation = nodeAnimation::HIGHLIGHT;
        currNode->m_animationPhase = 0.0f;

        highlighted_line = 7;
        currNode = currNode->m_pNext;
    }
    else {//Found the end
        highlighted_line = 8;
        currNode->m_currentAnimation = nodeAnimation::HIGHLIGHT;
        currNode->m_animationPhase = 0.0f;

        highlighted_line = 9;
        currOperationInfo.newNode->m_currentPosition = {
            currNode->m_currentPosition.x + pointerLength, 100
        };
        currOperationInfo.newNode->m_destination = {
            currNode->m_currentPosition.x + pointerLength, LinkedListInitPosition.y
        };

        currNode->m_pNext = currOperationInfo.newNode;

        highlighted_line = 10;
        currOperationInfo.newNode->m_currentAnimation = nodeAnimation::MOVING;
        currOperationInfo.newNode->m_animationPhase = 0.0f;

        int val = 0;
        if (currOperationInfo.newNode) {
            val = currOperationInfo.newNode->m_val;
        }
        messageLog = std::to_string(val) + "was added to the list";

        currOperationInfo.newNode = nullptr;
        resetOperation();
    }
}
void SLL::updateForRemove() {
    if (!currOperationInfo.isStarted ) return;
        highlighted_line = 1;
        //Empty List
        if (!m_pHead) {
            messageLog = "Empty List";
            resetOperation();
            return;
        }

        //Exception of the first node
        if (m_pHead->m_val == currOperationInfo.removeVal) {//Fount the node
            SLLNode* temp = m_pHead;
            highlighted_line = 3;
            temp->m_currentAnimation = nodeAnimation::CHANGINGOPACITY ;
            temp->m_animationPhase = 0.0f;  
            m_pHead = m_pHead->m_pNext;
            delete temp;
            highlighted_line = 4;
            repositionNodeSlowly();
            
            
            messageLog = "Removed " + std::to_string(currOperationInfo.removeVal) ;
            resetOperation();
            return;
        }

		//If it is not the first node
        highlighted_line = 5;
        highlighted_line = 6;
        if (!currOperationInfo.currNode) currOperationInfo.currNode = m_pHead;
        //Search until there is no node
        if (currOperationInfo.currNode) {
            currOperationInfo.currNode->m_currentAnimation = nodeAnimation::HIGHLIGHT;
            currOperationInfo.currNode->m_animationPhase = 0.0f;
        }
        if (currOperationInfo.currNode->m_pNext) {
			//If we meet the node we want to delete
            if (currOperationInfo.currNode->m_pNext->m_val == currOperationInfo.removeVal) {
                highlighted_line = 7;
                //Delete the node
                SLLNode* del = currOperationInfo.currNode->m_pNext;
                del->m_currentAnimation = nodeAnimation::CHANGINGOPACITY;
                del->m_animationPhase = 0.0f;
                currOperationInfo.currNode->m_pNext = del->m_pNext;
                delete del;

                highlighted_line = 8;
				//Reposition the node
                repositionNodeSlowly();
                
                
                messageLog = "Removed " + std::to_string(currOperationInfo.removeVal) ;
                resetOperation();
            }
            else {
                currOperationInfo.currNode = currOperationInfo.currNode->m_pNext;
                
            }
        }
        else {
            messageLog =  std::to_string(currOperationInfo.removeVal) + " not found.";
            resetOperation();
        }
}
void SLL::updateForSearch() {
    if (!currOperationInfo.isStarted ) return;
    if (!m_pHead) {
            currOperationInfo.isFound = false;
			messageLog = "Empty List.";
			resetOperation();
			return;
	}
	SLLNode*& pCurr = currOperationInfo.currNode;
    if (pCurr) {
       pCurr->m_currentAnimation = nodeAnimation::HIGHLIGHT;
       pCurr->m_animationPhase = 0.0f;
       highlighted_line = 3;
       if (pCurr->m_val == currOperationInfo.findVal) {
         currOperationInfo.isFound = true;
         messageLog = "Found " + std::to_string(currOperationInfo.findVal);
         resetOperation();
         return;
       }
       else {
           pCurr = pCurr->m_pNext;
       }
    if (!pCurr) {
          currOperationInfo.isFound = false;
          messageLog = std::to_string(currOperationInfo.findVal) + " not found.";
          resetOperation();
         }
    }
}
void SLL::updateForChangingValue() {
    //Check if there is any function calling
    if (!currOperationInfo.isStarted) return;
	//Check if the list is empty
	if (!m_pHead) {
		messageLog = "Empty List.";
		resetOperation();
		return;
	}
	SLLNode*& pCurr = currOperationInfo.currNode;
     if (pCurr) {
         pCurr->m_currentAnimation = nodeAnimation::HIGHLIGHT;
         pCurr->m_animationPhase = 0.0f;
         highlighted_line = 3;
         //Found the value
         if (pCurr->m_val == currOperationInfo.oldVal) {
			 //Change the value
                pCurr->m_val = currOperationInfo.newVal;
				//Set the opacity
                pCurr->m_opacity = 0.0f;

                //Moving the node down
                Vector2 currPos = pCurr->m_currentPosition;
                pCurr->m_currentPosition = { currPos.x, 100 };
                pCurr->m_destination = currPos;
                highlighted_line = 6;
                pCurr->m_currentAnimation = nodeAnimation::MOVING;

                //Begin the animation
                pCurr->m_animationPhase = 0.0f;
                
                
                messageLog = "Changing " + std::to_string(currOperationInfo.oldVal) + " to " + std::to_string(currOperationInfo.newVal);
                resetOperation();
				return;
            }
         else {
             pCurr = pCurr->m_pNext;
         }
	}
     else {
         messageLog = std::to_string(currOperationInfo.oldVal) + " not found";
         resetOperation();
     }
}
void SLL::updateAnimation() {
    if (isPausing) return;

    SLLNode* pCurr = m_pHead;
    const float phaseIncrement = LinkedListSpeed * (1.0f / 60.0f);

    while (pCurr) {
        if (pCurr->m_currentAnimation != nodeAnimation::IDLE) {
            pCurr->m_animationPhase += phaseIncrement;

            bool animationDone = (pCurr->m_animationPhase >= 1.0f || m_skipCurrentStep);
            if (animationDone) {
                pCurr->m_animationPhase = 1.0f;

                switch (pCurr->m_currentAnimation) {
                case nodeAnimation::HIGHLIGHT:
                    pCurr->m_isHighlight = false;
                    break;

                case nodeAnimation::MOVING:
                    pCurr->m_currentPosition = pCurr->m_destination;
                    pCurr->m_opacity = 1.0f;
                    break;

                case nodeAnimation::CHANGINGOPACITY:
                    pCurr->m_opacity = 0.0f;
                    break;

                case nodeAnimation::ADJUSTING:
                    pCurr->m_currentPosition = pCurr->m_destination;
                    break;

                default:
                    break;
                }

                pCurr->m_currentAnimation = nodeAnimation::IDLE;
            }
            else {
                float animationPhaseProgress = convertTimeToProgress(pCurr->m_animationPhase);

                switch (pCurr->m_currentAnimation) {
                case nodeAnimation::HIGHLIGHT:
                    pCurr->m_isHighlight = (pCurr->m_animationPhase < 0.5f);
                    break;

                case nodeAnimation::MOVING:
                    pCurr->m_currentPosition.y = smoothStep(pCurr->m_currentPosition.y, pCurr->m_destination.y, animationPhaseProgress);
                    pCurr->m_opacity = animationPhaseProgress;
                    break;

                case nodeAnimation::CHANGINGOPACITY:
                    pCurr->m_opacity = 1.0f - animationPhaseProgress;
                    break;

                case nodeAnimation::ADJUSTING:
                    pCurr->m_currentPosition.x = smoothStep(pCurr->m_currentPosition.x, pCurr->m_destination.x, animationPhaseProgress);

                    break;

                default:
                    break;
                }
            }
        }

        pCurr = pCurr->m_pNext;
    }

    if (m_skipCurrentStep) {
        Forward();
        m_skipCurrentStep = false;
    }
}

void SLL::create(std::vector<int>vals) {
	if (vals.empty()) {
		messageLog = "Empty Input.";
		return;
	}
	messageLog = "Create List.";
    resetList();
    resetOperation();
    Vector2 pos = LinkedListInitPosition;
	//Create the first node
    m_pHead = new SLLNode(vals[0]);
    m_pHead->m_currentPosition = pos;
    m_pHead->m_destination = pos;
    SLLNode* pTail = m_pHead;

    for (int i = 1; i < vals.size(); i++) {
		//Create the next node
        SLLNode* newNode = new SLLNode(vals[i]);
		//Set the position
        pos = { pTail->m_currentPosition.x + pointerLength, LinkedListInitPosition.y };
        newNode->m_currentPosition = pos;
        newNode->m_destination = pos;
        //Set the link
        pTail->m_pNext = newNode;
		//Move the pTail
        pTail = pTail->m_pNext;
    }
}
void SLL::randomCreate(int Amount) {
    messageLog = "Create " + std::to_string(Amount) + "random nodes.";
    resetList();
    resetOperation();
	Vector2 pos = LinkedListInitPosition;
    m_pHead = new SLLNode(GetRandomValue(1,500));
    m_pHead->m_currentPosition = pos;
    m_pHead->m_destination = pos;
    SLLNode* pTail = m_pHead;

    for (int i = 1; i < Amount; i++) {
        SLLNode* newNode = new SLLNode(GetRandomValue(1, 500));
        //Set the position
        pos = { pTail->m_currentPosition.x + pointerLength, LinkedListInitPosition.y };
        newNode->m_currentPosition = pos;
        newNode->m_destination = pos;
        //Set the link
        pTail->m_pNext = newNode;
        //Move the pTail
        pTail = pTail->m_pNext;
    }
}
void SLL::LoadFromFile(std::string path) {
    resetList();
    std::string input;
    std::ifstream fin(path);
    while (!fin.eof()) {
		std::getline(fin, input);
        std::stringstream stream(input);
        int value;
        while (stream >> value) {
            storeOperation(static_cast<listFunctionWithParameter::operation_type>(2), value);
        }
    }
    fin.close();
    
}

//====================RESET================
void SLL::repositionNodeSlowly() {
    SLLNode* pCurr = m_pHead;
	Vector2 nodePos = LinkedListInitPosition;
    while (pCurr) {
		//Set the destination position
        pCurr->m_destination = nodePos;
        //Set the animation
        pCurr->m_currentAnimation = static_cast<nodeAnimation> (4);
        pCurr->m_animationPhase = 0.0f;
        nodePos.x += pointerLength;

        //Move to next Node
        pCurr = pCurr->m_pNext;

    }
}
void SLL::repositionNode() {
    SLLNode* pCurr = m_pHead;
    Vector2 nodePos = LinkedListInitPosition;
    while (pCurr) {
        //Set the destination position
        pCurr->m_destination = nodePos;
        pCurr->m_destination = nodePos;
        //Set the animation
        pCurr->m_currentAnimation = static_cast<nodeAnimation> (0);

        pCurr->m_animationPhase = 0.0f;

        nodePos.x += pointerLength;

        //Move to next Node
        pCurr = pCurr->m_pNext;

    }
}
void SLL::resetList() {
	SLLNode* pCurr = m_pHead;
    while (pCurr) {
        SLLNode* del = pCurr;
        pCurr = pCurr->m_pNext;
        delete del;
    }
	m_pHead = nullptr;
	pCurr = nullptr;
}
void SLL::resetOperation() {
    m_current_function = listFunctionWithParameter::operation_type::NONE;
    currOperationInfo = operateInfo();
    //Reset the highlighted line
    highlighted_line = -1;
	//Reset to Idle
	currOperationInfo.isStarted = false;

}


//==============Render============================

void SLL::render() {
    SLLNode* curr = m_pHead;
    while (curr) {
		float newX = curr->m_currentPosition.x + 0;
		float newY = curr->m_currentPosition.y;
        Vector2 newPos = { newX, newY };
        curr->renderSLLNode( newPos);
        if (curr->m_pNext) {
            Pointer pNext;
            float newPosPointerHeadX = curr->m_pNext->m_currentPosition.x+ 0;
			float newPosPointerHeadY = curr->m_pNext->m_currentPosition.y;
            Vector2 pointerPos = { newPosPointerHeadX, newPosPointerHeadY };
			pNext.setTailPos(curr->m_currentPosition);
			pNext.setHeadPos(pointerPos);
            pNext.render();
        }
        curr = curr->m_pNext;
    }

    if (!messageLog.empty()) {
        DrawText(messageLog.c_str(), GetScreenWidth()/2- MeasureText(messageLog.c_str(), 30) / 2,20  , 30, messageLogColor);
    }
}

void SLL::renderCode() {
    if (m_current_function == listFunctionWithParameter::NONE) return;



    Vector2 linePos = LinkedListCodeBlockPos;
    for (int i = 0; i < SLLSourceCode[m_current_function - 1].size(); i++) {
        if (m_current_function >= 1 && m_current_function <= 5 && SLLSourceCode[m_current_function - 1][i][0] != '\0') {
            Color currentLineColor;
            if (i == highlighted_line) {
                currentLineColor = messageLogColorHighligth; 
            }
            else {
                currentLineColor = messageLogColor;
            }
            DrawText(SLLSourceCode[m_current_function - 1][i].c_str(), linePos.x, linePos.y, 20, currentLineColor);
        }
        linePos.y +=30;
    }
}

void SLL::handleOperations() {
    if (m_current_function != 0 || functionQueue.empty()) return;

    listFunctionWithParameter currOperation = functionQueue.front();

    //Pop the operation from the queue
    functionQueue.pop();
    //Detertmine the current function
    m_current_function = currOperation.functionType;
    //Code highlight
    highlighted_line = 1;
    //Reset the current step
    currOperationInfo.isStarted = 1;


    switch (currOperation.functionType) {
    case listFunctionWithParameter::RANDOM:
        currOperationInfo.randomAmount = currOperation.firstParameter;
        resetList();
        randomCreate(currOperationInfo.randomAmount);

        break;
    case listFunctionWithParameter::INSERT:
        currOperationInfo.newNode = new SLLNode(currOperation.firstParameter);

        break;
    case listFunctionWithParameter::REMOVE:
        currOperationInfo.removeVal = currOperation.firstParameter;
        currOperationInfo.currNode = m_pHead;

        break;
    case listFunctionWithParameter::FIND:
        currOperationInfo.findVal = currOperation.firstParameter;
        currOperationInfo.currNode = m_pHead;
        currOperationInfo.isFound = false;

        break;
    case listFunctionWithParameter::UPDATE:
        currOperationInfo.oldVal = currOperation.firstParameter;
        currOperationInfo.newVal = currOperation.secondParameter;
        currOperationInfo.currNode = m_pHead;

        break;
    }
}





