#include "include/graphics.h"

#include <iostream>
#include <vector>
#include <functional>

class Entity {
protected:
    double x_c;
    double y_c;
    double radius;

public:
    Entity(double x, double y, double r) : x_c(x), y_c(y), radius(r) {}

    virtual void draw() = 0;
    bool collide(Entity* other);    //true - ���� ��� �������� �����������
};

class Player : public Entity {
private:
    double dx;
    double dy;
    int balance;
    int health;

public:
    Player(double dx, double dy, int bal, int health) : 
        Entity(x_c, y_c, radius), dx(dx), dy(dy), balance(bal), health(health) {}

    void rotate(double angle);              //������� ����������� �� ���� angle
    void move(bool backwards);              //������������ � ����������� dx, dy
    void draw()override {                            //���������

    }

};

class Coin : public Entity {

public:
    //�����������
    void draw();
};

class Spike : public Entity {

public:
    //�����������
    void draw();
};

class GameMap {
private:
    int WIDTH;
    int HEIGHT;
    int BG_COLOR;
    std::vector<Entity*> entities;

public:
    GameMap(int W, int H, int BG) : WIDTH(W), HEIGHT(H), BG_COLOR(BG) {};
    ~GameMap() {
        closegraph();
    }

    int getWidth()const {
        return WIDTH;
    }
    int getHeight()const {
        return HEIGHT;
    }
    void draw_map() {
        
        initwindow(getWidth(), getHeight(), "��������", 0, 0, true);
        setbkcolor(BG_COLOR); // ���� ����
        clearviewport(); // �������� ������� �������� ������ ����
    }
    void draw();    //��������� ���� ���������
    void addEntity(Entity* entity);
};


int main() {

    GameMap field(800, 800, BLACK);
    field.draw_map();

    while (true) {
        
       




        swapbuffers(); // ������ �������� �������� �������
        delay(30); // �������� �� 1/30 �������
        if (kbhit()) break; // ���� ������ ������� - ��������� ������
   
    
    }

    return 0;
}

 