#ifndef CONFIG_H
#define CONFIG_H

#include "include.h"
#include "environment.h"

enum class config_state
{
    student = 0,
    teacher = 1,
    admin = 2,
    obligatory = 3,
    elective = 4,
    nop = 5
};

class Config_file
{
public:
    Config_file();
    ~Config_file();

    void setEnvir(Envir* envir);

    void readConfig();
    void writeConfig();

private:
    Envir* m_envir = NULL;
};

#endif // CONFIG_H
