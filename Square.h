#pragma once
#include"Def.h"

class Square
{
public:
	Square();
	Square(const Square& e); //���ƹ��캯�������㸳ֵ���磺Square	tempSquare = nowSquare��
	void setColor(int color);    //������ɫ
	void setShape(int shape); //������״
	void setPosition(int x, int y); //����λ�ã����Ͻ�Ϊcore��
	void Rotate(); //��ת
	int getColor(); //��ȡ��ɫ
	int getShape(); //��ȡ��״
	int getMid(); //��ȡ���ĵ�
	int getWidth(); //��ȡ���
	int getHeight(); //��ȡ�߶�
	Vector2i getSquarePosition(int i); //��ȡ��i����������
	Vector2i getPosition();//��ȡcore���꣨���Ͻǣ�

//�ܱ����ĳ�Ա�����ⲻ��ͨ��"."��"thisָ��"��ֱ�Ӹı���Щֵ����߰�ȫ�ԣ����Ҫ��ȡ���޸���Щ��Ա�����������get/set��������Ա仯����������ȫ��
//����ֱ�Ӹı�shape�Ļ���width��heightԭ������Ҫ�ı�ģ�����ȴֻ�ı���shape
protected:  
	int color; //��ɫ
	int shape; //��״
	int mid; //���ĵ㣨5��
	int width, height; //����
	Vector2i Pos; //���Ͻ����꣨core��
	Vector2i squarePos[4]; //�ĸ��������꣨��������ϵ��

//˽�г�Ա����ʵ������protected��private��һ������Ϊ����಻�ᱻ����
private:
	Vector2i squareShape[4]; //����ʱ�����꣨Figures��
	void update(); //���£��ı�shape�����mid��width�ȣ�
};