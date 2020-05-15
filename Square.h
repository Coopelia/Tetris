#pragma once
#include"Def.h"

class Square
{
public:
	Square();
	Square(const Square& e); //复制构造函数（方便赋值，如：Square	tempSquare = nowSquare）
	void setColor(int color);    //设置颜色
	void setShape(int shape); //设置形状
	void setPosition(int x, int y); //设置位置（左上角为core）
	void Rotate(); //旋转
	int getColor(); //获取颜色
	int getShape(); //获取形状
	int getMid(); //获取中心点
	int getWidth(); //获取宽度
	int getHeight(); //获取高度
	Vector2i getSquarePosition(int i); //获取第i个方块坐标
	Vector2i getPosition();//获取core坐标（左上角）

//受保护的成员，类外不能通过"."、"this指针"来直接改变这些值，提高安全性，如果要获取或修改这些成员，调用上面的get/set函数（会对变化作出处理，安全）
//比如直接改变shape的话，width和height原则上是要改变的，但是却只改变了shape
protected:  
	int color; //颜色
	int shape; //形状
	int mid; //中心点（5）
	int width, height; //宽、高
	Vector2i Pos; //左上角坐标（core）
	Vector2i squarePos[4]; //四个方块坐标（世界坐标系）

//私有成员，其实在这里protected和private都一样，因为这个类不会被派生
private:
	Vector2i squareShape[4]; //编码时的坐标（Figures）
	void update(); //更新（改变shape后更新mid、width等）
};