#ifndef VLCPLAYERWIDGET_H
#define VLCPLAYERWIDGET_H

#include <QOpenGLWidget>
#include <vlc/vlc.h>
#include <QOpenGLFunctions_2_0>
#include <QMatrix4x4>
class I420Image
{
public:
    I420Image(int w, int h)
        : width(w)
        , height(h)
    {
        data = new uint8_t[w*h + w*h / 2];
    }
    ~I420Image()
    {
        delete []data;
    }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    uint8_t *GetY() const { return data; }
    uint8_t *GetU()const { return data + width*height; }
    uint8_t *GetV()const { return data + width*height + width*height / 4; }
protected:
private:
    int width;
    int height;
    uint8_t * data;
};



class VlcPlayerWidget : public QOpenGLWidget, public QOpenGLFunctions_2_0 //, public Player
{
    Q_OBJECT

public:
    explicit VlcPlayerWidget(QWidget *parent = 0);
    ~VlcPlayerWidget();

public:
    void setInput(QString input);
    void play();
    void pause();
    void stop();

public:
    static void *lock_cb(void *opaque, void **planes);
    static void unlock_cb(void *opaque, void *picture, void *const *planes);
    static void display_cb(void *opaque, void *picture);
    static unsigned setup_cb(void **opaque, char *chroma,
                             unsigned *width, unsigned *height,
                             unsigned *pitches,
                             unsigned *lines);
    static void cleanup_cb(void *opaque);

protected:
//    virtual void paintEvent(QPaintEvent *event) override;

    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;


private:
    void InitShaders();
    GLuint program;
    GLuint tex_y, tex_u, tex_v;
    GLuint sampler_y, sampler_u, sampler_v;
    GLuint matWorld, matView, matProj;
    QMatrix4x4 mProj;
    QMatrix4x4 mView;
    QMatrix4x4 mWorld;

private:
    libvlc_instance_t* m_vlc;
    libvlc_media_player_t *m_vlcplayer;
    I420Image *m_Front;
    I420Image *m_Back;

private:
    QString m_input;
};

#endif // VLCPLAYERWIDGET_H
