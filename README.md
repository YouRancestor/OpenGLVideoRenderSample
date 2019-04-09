# OpenGLVideoRenderSample
OpenGL渲染视频样例，依赖VLC、Qt。

## Build
```shell
qmake VlcPlayerWidget.pro INCLUDEPATH+=path/to/libvlc/include LIBS+=-Ldirectory/to/libvlc/libs
make # or mingw32-make for mingw or jom for msvc ...
```

## VLC links
- [Document](https://wiki.videolan.org)
- [Download](https://get.videolan.org)
- [CI](https://jenkins.videolan.org)
