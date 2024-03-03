# Makefile

APP_SRC := app.c callbacks.c core.c engine/Camera2D/camera2D.c engine/Renderer/renderer.c ext/glad/glad.c ext/nanovg/nanovg.c 
web:
	emcc $(APP_SRC) -DWEB=1 -o index.html -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1
	emrun index.html

web2:	
	emcc test.c ext/glad/glad.c -DWEB=1 -o index.html -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1
	emrun index.html
