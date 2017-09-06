#ifndef VLCPLAYERWIDGET_H
#define VLCPLAYERWIDGET_H

#include <QWidget>
#include <vlc.h>
#include <QImage>

namespace Ui {
class VlcPlayerWidget;
}

class VlcPlayerWidget : public QWidget //, public Player
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
    void paintEvent(QPaintEvent *event);
private:
    Ui::VlcPlayerWidget *ui;

private:
    libvlc_instance_t* m_vlc;
    libvlc_media_player_t *m_vlcplayer;

private:
    QString m_input;
    QImage *m_Front;
    QImage *m_Back;
};

#endif // VLCPLAYERWIDGET_H
