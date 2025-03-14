#pragma once
#include "GUIObject.h"

#include <string>
#include "raylib.h"
class TextBox:public GUIObject {
protected:
	//Text
	std::string			content;
	float				textSize;
	Font				font;
	Color				textColor;
public:
	void				setPosition(Vector2 position) override,

						setContent(std::string text),

						getContent(),

						setTextSize(float size),
			
						setFont(const Font),

						setColor(const Color);


	virtual void		update() override,
						render() override;
};	
