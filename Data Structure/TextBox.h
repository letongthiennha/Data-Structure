#pragma once
#include "GUIAnimatingObject.h"
#include "GUIText.h"
class BoxState : public GUIState {
private:
	Color		m_outline_color;
public:
	BoxState();
	BoxState(Color outline_color, Color backgroud_color, Vector2 position);	
	//=================================================Color Function=======================================
	void					setOutlineColor(Color color);
	Color					getOutlineColor();
};
//Class to combine text and a box
class TextBox :public GUIAnimatingObject{
protected:
	GUIText m_text;
public:
	TextBox();
	TextBox(float x, float y, std::string text);

	//=================================================Text Function=======================================
	void					setText(std::string text);
	void					setTextColor(Color color);
	void					setTextSize(int textSize);
	void					setFont(Font font);
	void					setSpacing(float space);
	std::string				getText();
	void					changeTextColor(Color color);
	//=================================================Box Function=======================================
	void					setOutlineColor(Color color);
	void					setBackgroundColor(Color color);
	void					changeBackgroundColor(Color color);
	Color					getOutlineColor();
	//================================================Combine Funtion=======================================
	//===========Timing Function=======================
	void					setAnimationDuration(float time) override;
	//=================================================Position Function=======================================
	//===========MovingFunction========================
	virtual void			setPosition(Vector2 position) override=0,
							moveToPosition(Vector2 newPos) override=0;
	//=================================================Update Function=======================================
	virtual void			update() override;
	//=================================================Render Function=======================================
	virtual void			render()override =0;

};

