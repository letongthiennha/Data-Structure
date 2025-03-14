#pragma once
#include "GUIObject.h"
#include <string>
class GUIText: public GUIObject{
private:
	std::string			m_content;

	Font				m_font;
	float				m_fontSize,
						m_spacing;
	Color				m_color;
	
public:
	//Constructor
	GUIText();

	//Modify content
	void				setFont(const Font font),

						setTextSize(const float size),

						setTextColor(const Color color),

						setContent(const std::string text),

						setSpacing(const float space);
	//Get content
	std::string			getContent();

	float				getTextSize();
	
	void				update() override,
						render() override;
						
};

