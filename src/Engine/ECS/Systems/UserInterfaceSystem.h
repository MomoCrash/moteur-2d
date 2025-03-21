#pragma once



class UserInterfaceSystem
{
public:
    UserInterfaceSystem(RenderWindow* window);
    ~UserInterfaceSystem() = default;
    
    void Render(ECS* globalEC);

private:
    RenderWindow* window;
};
