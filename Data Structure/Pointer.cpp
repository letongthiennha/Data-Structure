#include "Pointer.h"
#include "Motion.h"
Pointer::Pointer() {
    head = { 0,0 };
    m_tailPos = { 0,0 };
    m_color = BLACK; // Default color
}
Pointer::Pointer(Vector2 firstPosition) {
    head = firstPosition;
    m_tailPos = firstPosition;
    m_color = BLACK; // Default color
}
//===Color=======
void Pointer::setColor(Color color) {
    m_color = color;
}

//==============Head===========================
void Pointer::setHeadPos(Vector2 headPosition) {
    head = headPosition;

}

//===============Tail=====================
void Pointer::setTailPos(Vector2 tailPosition) {
    m_tailPos = tailPosition;

}

Vector2 Pointer::getTailPos() {
    return m_tailPos;
}


Vector2 Pointer::getHeadPos() {
    return head;
}





void Pointer::render() {
    //Tinh huong cua mui ten
    Vector2 direction = { head.x - m_tailPos.x,head.y - m_tailPos.y };
    //Neu nhu khong co do dai thi khong ve
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0) return;
    Vector2 chiphuong = { direction.x / length, direction.y / length };
    //Tinh Vector phap tuyen
    Vector2 phaptuyen = { -chiphuong.y,  chiphuong.x };


    static const float edgeLength = 30.0f;

    //Dinh thu 2 bang duoi tru chieu dai canh nhan tan goc phap tuyen
    Vector2 secondVertex = {
    head.x - chiphuong.x * edgeLength + phaptuyen.x * (edgeLength * 0.5f),
    head.y - chiphuong.y * edgeLength + phaptuyen.y * (edgeLength * 0.5f)
    };

    Vector2 thirdVertex = {
        head.x - chiphuong.x * edgeLength - phaptuyen.x * (edgeLength * 0.5f),
        head.y - chiphuong.y * edgeLength - phaptuyen.y * (edgeLength * 0.5f)
    };

    Vector2 firstVertex= head;



    DrawLineEx(m_tailPos, head, 3, m_color);
    DrawTriangle(firstVertex, thirdVertex, secondVertex, m_color);
}


