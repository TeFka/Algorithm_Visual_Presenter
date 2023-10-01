#ifndef CIRCUITSIMULATORSCREEN_H_INCLUDED
#define CIRCUITSIMULATORSCREEN_H_INCLUDED

#include "Interface/InterfaceLayout.h"
#include "Interface/InterfaceBox.h"
#include "Interface/InterfaceButton.h"
#include "Interface/InterfaceActionScreen.h"
#include "Interface/InterfaceScreen.h"
#include "App/AppEngine.h"
#include "AlgorithmVisualPresenter.h"

class AlgorithmVisualPresenterScreen : public InterfaceScreen{

private:

    RenderEngine* renderEngine;
    AlgorithmVisualPresenter* theAlgorithmPresenter;

    void setSimulatorMode();
public:
    AlgorithmVisualPresenterScreen(std::string, InterfaceEngine*, RenderEngine*, int);
    ~AlgorithmVisualPresenterScreen();

    AlgorithmVisualPresenter* getPresenter();
    void setPresenter(AlgorithmVisualPresenter*);

    void setSortMode();
    void setNoiseMode();

    void setValueNoiseMode();
    void setPerlinNoiseMode();

    void manageSortChange();
    void manageNoiseChange();

    void checkForFunctions();
    void update();

    void render();

    void printTest();
};
#endif // CIRCUITSIMULATORSCREEN_H_INCLUDED
