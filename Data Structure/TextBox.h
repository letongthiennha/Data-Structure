//#pragma once
//#include "GUIAnimatingObject.h"
//#include "GUIText.h"
////Class to combine text and a box
//class TextBox :public GUIAnimatingObject{
//protected:
//	GUIText m_text;
//	Color m_outline_color;
//	int m_thickness;
//public:
//	TextBox();
//	TextBox(float x, float y, std::string text);
//
//	//=================================================Text Function=======================================
//	void					setText(std::string text);
//
//	void					setTextColor(Color color);
//
//	void					setTextSize(int textSize);
//
//	void					setFont(Font font);
//
//	void					setSpacing(float space);
//
//	std::string				getText();
//
//	void					changeTextColor(Color color);
//
//	void					setThickness(int thickness);
//	//=================================================Box Function=======================================
//	void					setOutlineColor(Color color);
//
//	void					setBackgroundColor(Color color);
//
//	void					changeBackgroundColor(Color color);
//
//	Color					getOutlineColor();
//	//Color					getBackGroundColor() { return m_state->getMainColor(); };
//	//================================================Combine Funtion=======================================
//	//===========Timing Function=======================
//	void					setAnimationDuration(float time) override;
//
//	//=================================================Position Function=======================================
//	//===========MovingFunction========================
//	virtual void			setPosition(Vector2 position) override=0,
//
//							moveToPosition(Vector2 newPos) override=0;
//
//	//=================================================Update Function=======================================
//	virtual void			update() override;
//	//=================================================Render Function=======================================
//	virtual void			render()override =0;
//
//	virtual void			addStep()override;
//
//};
//
