#include "include/graphics.h"

#include <iostream>
#include <vector>
#include <functional>

int WIDTH = 800;
int HEIGHT = 800;


class Entity {
protected:
    double x_c;
    double y_c;
    double radius;

public:
    Entity(double x, double y, double r) : x_c(x), y_c(y), radius(r) {}
    
    virtual void draw() = 0;
  //  virtual void erase();
    bool collide(Entity* other) {   //true - если две сущности столкнулись
        return this->radius + other->radius >= sqrt((this->x_c * this->x_c) - (other->x_c * other->x_c));
    }
};

class Player : public Entity {
private:
    double dx;
    double dy;
    int balance;
    int health;

public:
    Player(double x_c, double y_c, double radius, double dx, double dy, int bal, int health) : 
        Entity(x_c, y_c, radius), dx(dx), dy(dy), balance(bal), health(health) {}

    void rotate(double angle) {              //Поворот направления на угол angle
        double oldX = dx - x_c;
        double oldY = dy - y_c;
        dx = oldX * cos(angle) - oldY * sin(angle) + x_c;
        dy = oldX * sin(angle) + oldY * cos(angle) + y_c;
    }
    void move() {              //Передвижение в направлении dx, dy
        double oldX = x_c;
        double oldY = y_c;
        x_c += (dx - oldX)/5;
        y_c += (dy - oldY)/5;
        dx += (dx - oldX)/5;
        dy +=  (dy - oldY)/5;
    }
   
    void draw()override {                            //Отрисовка
        setfillstyle(SOLID_FILL, WHITE);
        fillellipse(x_c, y_c, radius, radius);
        setcolor(BLACK);
        line(x_c, y_c, dx, dy);
    }
    
};

class Coin : public Entity {

public:
    Coin(double x, double y, double r) : Entity(x, y, r) {}
    void draw()override {
        setfillstyle(SOLID_FILL,YELLOW);
        fillellipse(x_c, y_c, radius, radius);
    }
    
};

class Spike : public Entity {

public:
    Spike(double x, double y, double r) : Entity(x, y, r) {}
    
    void draw()override {
        setfillstyle(SOLID_FILL, RED);
        fillellipse(x_c, y_c, radius, radius);
    }
   
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
        
        initwindow(getWidth(), getHeight(), "Анимация", 0, 0, true);
        setbkcolor(BG_COLOR); // цвет фона
        clearviewport(); // закраска текущей страницы цветом фона
    }

    void draw();    //Отрисовка всех сущностей
    void addEntity(Entity* entity);
};


int main() {
    srand(time(NULL));
    double x_c = 400;
    double y_c = 400;
    double radius = 20.0;
    double dx = 420.0;
    double dy = 400.0;
    int balance = 0;
    int health = 3;
    double angle = 0;

    GameMap field(WIDTH, HEIGHT, BLACK);
    field.draw_map();
    Spike sp1(rand() % 760, rand() % 760 , radius);
    Coin c1(rand() % 760, rand() % 760, radius);
    Player p(x_c, y_c, radius, dx, dy, balance, health);
    

    while (true) {
        
        sp1.draw();
        c1.draw();
       

        if (kbhit()) {
 
            int key = getch();
            if (key == 0) {
                key = getch();
            }
            if (key == KEY_LEFT) {
                p.rotate(-3.14/90);

            }
            if (key == KEY_RIGHT) {
                p.rotate(3.14/90);

            }
            if (key == KEY_UP) {
                
                p.move();
            }
            if (key == KEY_DOWN) {
                dy = 1;
                dx = 0;
            }
        }
        
        p.draw();
        
        
       



        swapbuffers(); // делаем активную страницу видимой
        delay(30); // задержка на 1/30 секунды
       

        if (kbhit()) {
            int key = getch();
            if (key == KEY_ESC) {
                break;
            }
        }
   
    
    }

    return 0;
}

 