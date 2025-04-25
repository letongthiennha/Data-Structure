#include "SLL.h"
#include "Motion.h"
#include "Button.h"
#include "raylib.h"
#include "Setting.h"
#include "SLLScreen.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <cmath>
SLLScreen::SLLScreen() {
	speedChooser.setPosition({ 1400, 50 });
	speedChooser.setSize({ 20, 200 });

	inputBox.setPosition({ 50,830 });
	inputBox.setBoxTitle("Input");
	inputBox.setMaxLength(10);
	inputBox.setBoxSize({ 200,70 });


	Home = Button(homeButtonPosition, homeButtonSize, "Home");
	Home.SetIdleColor(controllerIdleColor);
	Home.SetHoverColor(controllerHoveringColor);
	Home.SetActiveColor(controllerActiveColor);
	Home.setTexture("assets/Icon/home.png");

	Create = Button({ 100, 500 }, stateControlButtonSize, "Create");
	Create.SetIdleColor(controllerIdleColor);
	Create.SetHoverColor(controllerHoveringColor);
	Create.SetActiveColor(controllerActiveColor);

	Random = Button({ 100, 550 }, stateControlButtonSize, "Random");
	Random.SetIdleColor(controllerIdleColor);
	Random.SetHoverColor(controllerHoveringColor);
	Random.SetActiveColor(controllerActiveColor);

	Insert = Button({ 100, 600 }, stateControlButtonSize, "Insert");
	Insert.SetIdleColor(controllerIdleColor);
	Insert.SetHoverColor(controllerHoveringColor);
	Insert.SetActiveColor(controllerActiveColor);

	Remove = Button({ 100, 650 }, stateControlButtonSize, "Remove");
	Remove.SetIdleColor(controllerIdleColor);
	Remove.SetHoverColor(controllerHoveringColor);
	Remove.SetActiveColor(controllerActiveColor);

	Find = Button({ 100, 700 }, stateControlButtonSize, "Find");
	Find.SetIdleColor(controllerIdleColor);
	Find.SetHoverColor(controllerHoveringColor);
	Find.SetActiveColor(controllerActiveColor);

	Update = Button({ 100 ,750 }, stateControlButtonSize, "Update");
	Update.SetIdleColor(controllerIdleColor);
	Update.SetHoverColor({ 85,156,236,255 });
	Update.SetActiveColor(controllerActiveColor);

	Accept = Button({ 300 ,850 }, stateControlButtonSize, "");
	Accept.setTexture("assets/Icon/accept.png");
	Accept.SetIdleColor(controllerIdleColor);
	Accept.SetHoverColor({ 85,156,236,255 });
	Accept.SetActiveColor(controllerActiveColor);

	Pause = Button(stateControlPosition, homeButtonSize, "Pause");
	Pause.setTexture("assets/Icon/pause.png");
	Pause.SetIdleColor(controllerIdleColor);
	Pause.SetHoverColor({ 85,156,236,255 });
	Pause.SetActiveColor(controllerActiveColor);

	Skip = Button(Vector2Add(stateControlPosition, Vector2{100,0}), homeButtonSize, "Skip");
	Skip.setTexture("assets/Icon/skip.png");
	Skip.SetIdleColor(controllerIdleColor);
	Skip.SetHoverColor({ 85,156,236,255 });
	Skip.SetActiveColor(controllerActiveColor);


}
void SLLScreen::updateList() {
	myList.update();

	
	myList.setSpeed(speedChooser.getProgress());
	if (inputting) {
		inputBox.update();	
		Accept.update();
	}
	if (Accept.isClicked()) {
		if (!inputBox.isEmpty()) {
			if (choose == listFunctionWithParameter::CREATE) {
				std::string input = inputBox.getText();
				std::vector<int> vals;
				std::stringstream ss(input);
				int val;
				while (ss >> val) {
					vals.push_back(val);
					if (ss.peek() == ' ') ss.ignore();
				}
				myList.create(vals);
			}
			if (choose == listFunctionWithParameter::UPDATE) {
				std::string input = inputBox.getText();
				//First Value
				int oldValue = std::stoi(input.substr(0, input.find(" ")));
				//Second Value
				int newValue = std::stoi(input.substr(input.find(" ") + 1));
				myList.storeOperation(listFunctionWithParameter::operation_type::UPDATE, oldValue, newValue);
			}
			else {
				int input = std::stoi(inputBox.getText());
				switch (choose) {

				case listFunctionWithParameter::RANDOM: myList.storeOperation(listFunctionWithParameter::operation_type::RANDOM, input); break;
				case listFunctionWithParameter::INSERT: myList.storeOperation(listFunctionWithParameter::operation_type::INSERT, input); break;
				case listFunctionWithParameter::REMOVE: myList.storeOperation(listFunctionWithParameter::operation_type::REMOVE, input); break;
				case listFunctionWithParameter::FIND: myList.storeOperation(listFunctionWithParameter::operation_type::FIND, input); break;
				}
			}

		}
		inputBox.clearContent();
		inputting = false;
		choose = listFunctionWithParameter::operation_type::NONE;

	}
	
}

void SLLScreen::update() {
	Random.update();
	Create.update();
	Insert.update();
	Remove.update();
	Find.update();
	Update.update();
	Home.update();
	Pause.update();
	Skip.update();
	speedChooser.update();

	if (Random.isClicked()) {
		inputting = true;
		choose = listFunctionWithParameter::RANDOM;
		inputBox.setBoxTitle("Input Amount");
	}
	if (Create.isClicked()) {
		inputting = true;
		choose = listFunctionWithParameter::CREATE;
		inputBox.setBoxTitle("Input Value");
	}
	if (Insert.isClicked()) {
		inputting = true;
		choose = listFunctionWithParameter::INSERT;
		inputBox.setBoxTitle("Input Value");
	}
	if (Remove.isClicked()) {
		inputting = true;
		choose = listFunctionWithParameter::REMOVE;
		inputBox.setBoxTitle("Input Value");
	}
	if (Find.isClicked()) {
		inputting = true;
		choose = listFunctionWithParameter::FIND;
		inputBox.setBoxTitle("Input Value");
	}
	if (Update.isClicked()) {
		inputting = true;
		choose = listFunctionWithParameter::UPDATE;
		inputBox.setBoxTitle("Input (OldValue NewValue)");
	}
	if (Pause.isClicked()) {
		myList.setStop(!myList.isStop());
		if (myList.isStop()) {
			Pause.setTexture("assets/Icon/play.png");
		}
		else {
			Pause.setTexture("assets/Icon/pause.png");
		}
	}
	if (Skip.isClicked()) myList.setSkip();
	if (IsFileDropped()) {
		FilePathList droppedFiles = LoadDroppedFiles();
		std::string path = droppedFiles.paths[0];
		if (droppedFiles.count > 0) {
			myList.LoadFromFile(droppedFiles.paths[0]);
		}
		UnloadDroppedFiles(droppedFiles);
	}
	updateList();
	inputBox.update();
}
void SLLScreen::render() {
	Create.renderRectangle();
	Create.drawTexture();
	Create.drawOutline(10, 10, 2, BLACK);
	Create.drawText({ 0,0,0,255 });

    Random.renderRectangle();
	Random.drawTexture();
	Random.drawOutline(10, 10, 2, BLACK);
	Random.drawText({ 0,0,0,255 });

	Insert.renderRectangle();
	Insert.drawTexture();
	Insert.drawOutline(10, 10, 2, BLACK);
	Insert.drawText({ 0,0,0,255 });

	Remove.renderRectangle();
	/*Remove.drawTexture();*/
	Remove.drawOutline(10, 10, 2, BLACK);
	Remove.drawText({ 0,0,0,255 });

	Find.renderRectangle();
	Find.drawTexture();
	Find.drawOutline(10, 10, 2, BLACK);
	Find.drawText({ 0,0,0,255 });

	Update.renderRectangle();
	Update.drawTexture();
	Update.drawOutline(10, 10, 2, BLACK);
	Update.drawText({ 0,0,0,255 });


	

	Home.drawTexture();
	
	Skip.drawTexture();

	Pause.drawTexture();

	if (inputting) {
		inputBox.render();
		Accept.drawTexture();
	}


	speedChooser.render();

	myList.render();
}
bool SLLScreen::goBack() {
	return Home.isClicked();
}
