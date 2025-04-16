#pragma once
#include "SLLNode.h"
#include "Setting.h"
#include <queue>

struct operateInfo {
    bool isStarted = false;
    //Create Function
    int randomAmount = 0;
    //Insert function
    SLLNode* newNode = nullptr;
    SLLNode* currNode = nullptr;
    //Remove function
    int removeVal = 0;
    //Search function
    int findVal = 0;
    bool isFound = false;
    //Update function
    int oldVal = 0;
    int newVal = 0;
};
class listFunctionWithParameter {

public:
    int firstParameter;
    int secondParameter;
    enum operation_type {
        NONE ,
		CREATE,
        RANDOM ,
        INSERT ,
        REMOVE ,
        FIND ,
        UPDATE 
    };
    operation_type functionType;


    listFunctionWithParameter(operation_type t, int first, int second = 0) : functionType(t), firstParameter(first), secondParameter(second) {}
};
