#include "Core/Application.h"
int main(int argc,char** argv)
{
    auto& app = CPUScheduling::Core::Application::Instance();
    app.Run();
    return 0;
}