#include "Pointer.h"
#include "Motion.h"
Pointer::Pointer(Vector2 firstPosition) {
    m_headPos = firstPosition;
    m_tailPos = firstPosition;
    m_headTargetPos = firstPosition;
    m_tailTargetPos = firstPosition;
    m_color = BLACK; // Default color
}
//===Color=======
void Pointer::setColor(Color color) {
    m_color = color;
}

//==============Head===========================
void Pointer::setHeadPos(Vector2 headPosition) {
    m_headPos = headPosition;
}

void Pointer::setTargetHeadPos(Vector2 targetHeadPosition) {
    m_headTargetPos = targetHeadPosition;
}

//===============Tail=====================
void Pointer::setTailPos(Vector2 tailPosition) {
    m_tailPos = tailPosition;
}

void Pointer::setTargetTailPos(Vector2 targetTail) {
    m_tailTargetPos = targetTail;
}

Vector2 Pointer::getTailPos() {
    return m_tailPos;
}

Vector2 Pointer::getHeadPos() {
    return m_headPos;
}

void Pointer::update() {
    slowMovingBetWeen2Pos(m_headPos, m_headTargetPos);
    slowMovingBetWeen2Pos(m_tailPos, m_tailTargetPos);
}



void Pointer::render() {
    //Tinh huong cua mui ten
    Vector2 direction = { m_headPos.x - m_tailPos.x,m_headPos.y - m_tailPos.y };
    //Neu nhu khong co do dai thi khong ve
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0) return;
    Vector2 chiphuong = { direction.x / length, direction.y / length };
    //Tinh Vector phap tuyen
    Vector2 phaptuyen = { -chiphuong.y,  chiphuong.x };


    static const float edgeLength = 30.0f;

    //Dinh thu 2 bang duoi tru chieu dai canh nhan tan goc phap tuyen
    Vector2 secondVertex = {
    m_headPos.x - chiphuong.x * edgeLength + phaptuyen.x * (edgeLength * 0.5f),
    m_headPos.y - chiphuong.y * edgeLength + phaptuyen.y * (edgeLength * 0.5f)
    };

    Vector2 thirdVertex = {
        m_headPos.x - chiphuong.x * edgeLength - phaptuyen.x * (edgeLength * 0.5f),
        m_headPos.y - chiphuong.y * edgeLength - phaptuyen.y * (edgeLength * 0.5f)
    };

    Vector2 firstVertex= m_headPos;



    DrawLineEx(m_tailPos, m_headPos, 3, m_color);
    DrawTriangle(firstVertex, thirdVertex, secondVertex, m_color);
}


