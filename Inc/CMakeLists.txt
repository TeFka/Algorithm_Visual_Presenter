# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND main_includes
    ${CMAKE_CURRENT_LIST_DIR}/Render/Shader.h
	${CMAKE_CURRENT_LIST_DIR}/Render/Texture.h
	${CMAKE_CURRENT_LIST_DIR}/Render/ShaderPipeline.h
	${CMAKE_CURRENT_LIST_DIR}/Render/Camera.h
	${CMAKE_CURRENT_LIST_DIR}/Render/Viewer3D.h
	${CMAKE_CURRENT_LIST_DIR}/Render/TextManager.h
	${CMAKE_CURRENT_LIST_DIR}/Render/RenderEngine.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceWidget.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceBox.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceLayout.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceButton.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceScreen.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceActionScreen.h
	${CMAKE_CURRENT_LIST_DIR}/Interface/InterfaceEngine.h
	${CMAKE_CURRENT_LIST_DIR}/App/AppEngine.h
	${CMAKE_CURRENT_LIST_DIR}/SortingProvider.h
	${CMAKE_CURRENT_LIST_DIR}/NoiseProvider.h
	${CMAKE_CURRENT_LIST_DIR}/SingularAlgorithmPresenter.h
	${CMAKE_CURRENT_LIST_DIR}/SortingPresenter.h
	${CMAKE_CURRENT_LIST_DIR}/NoisePresenter.h
	${CMAKE_CURRENT_LIST_DIR}/AlgorithmVisualPresenter.h
	${CMAKE_CURRENT_LIST_DIR}/AlgorithmVisualPresenterScreen.h
)

# /CMakeLists.txt-------------------------------------------------------------