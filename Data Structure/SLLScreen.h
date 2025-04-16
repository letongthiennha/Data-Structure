#pragma once
#include "raylib.h"
#include "SLL.h"
#include "Button.h"
#include "Setting.h"
#include <string>
#include "TextBox.h"
#include "Slider.h"
class SLLScreen {
private:
    Button Home;
	Button Create;
    Button Random;
    Button Insert;
    Button Remove;
    Button Find;
    Button Update;
    Button Accept;
    Button Pause;
    Button Skip;

    Rectangle speed;

    SLL myList;
    bool inputting ;
	listFunctionWithParameter::operation_type choose = listFunctionWithParameter::operation_type::NONE;
    TextBox inputBox;
    int updateOldValue = 0;

    Slider speedChooser;

public:
    SLLScreen();
	bool goBack();
	void renderList();
    void updateList();
	void update();
};	