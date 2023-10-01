# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND main_sources
    ${CMAKE_CURRENT_LIST_DIR}/Render/Shader.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/Texture.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/ShaderPipeline.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/Camera.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/Viewer3D.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/TextManager.cpp
	${CMAKE_CURRENT_LIST_DIR}/Render/RenderEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceWidget.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceBox.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceLayout.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceButton.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceActionScreen.cpp
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/App/AppEngine.cpp
	${CMAKE_CURRENT_LIST_DIR}/SortingProvider.cpp
	${CMAKE_CURRENT_LIST_DIR}/NoiseProvider.cpp
	${CMAKE_CURRENT_LIST_DIR}/SingularAlgorithmPresenter.cpp
	${CMAKE_CURRENT_LIST_DIR}/SortingPresenter.cpp
	${CMAKE_CURRENT_LIST_DIR}/NoisePresenter.cpp
	${CMAKE_CURRENT_LIST_DIR}/AlgorithmVisualPresenter.cpp
	${CMAKE_CURRENT_LIST_DIR}/AlgorithmVisualPresenterScreen.cpp
)	

# /CMakeLists.txt-------------------------------------------------------------