#include "vlcplayerwidget.h"
#include "ui_vlcplayerwidget.h"
#include <QPainter>

#include <assert.h>


VlcPlayerWidget::VlcPlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VlcPlayerWidget),
    m_vlcplayer(NULL),
    m_vlc(NULL),
    m_Front(NULL),
    m_Back(NULL)
{
    ui->setupUi(this);

    m_vlc = libvlc_new(0,0);

    m_vlcplayer = libvlc_media_player_new(m_vlc);
    libvlc_video_set_callbacks(m_vlcplayer,lock_cb,unlock_cb,display_cb,this);
    libvlc_video_set_format_callbacks(m_vlcplayer,setup_cb,cleanup_cb);
//    libvlc_video_set_format(m_vlcplayer,"RGBA",960,540,960);
}

VlcPlayerWidget::~VlcPlayerWidget()
{
    libvlc_release(m_vlc);
    delete ui;
}

void VlcPlayerWidget::setInput(QString input)
{
    m_input = input;
}

void VlcPlayerWidget::play()
{
    stop();
    libvlc_media_t *pmedia = libvlc_media_new_location(m_vlc,m_input.toLocal8Bit().data());

    libvlc_media_add_option(pmedia, ":rtsp-tcp=true :network-caching=300");
    libvlc_media_player_set_media(m_vlcplayer,pmedia);
    libvlc_media_player_play(m_vlcplayer);

    libvlc_media_release(pmedia);

}

void VlcPlayerWidget::pause()
{
    if(libvlc_media_player_can_pause(m_vlcplayer))
    {
        libvlc_media_player_pause(m_vlcplayer);
    }
}

void VlcPlayerWidget::stop()
{
    if(libvlc_media_player_is_playing(m_vlcplayer))
        libvlc_media_player_stop(m_vlcplayer);

    if(m_Front)
    {
        delete m_Front;
        m_Front = NULL;
    }
    if(m_Back)
    {
        delete m_Back;
        m_Back = NULL;
    }
}

void *VlcPlayerWidget::lock_cb(void *opaque, void **planes)
{
    VlcPlayerWidget *pthis = static_cast<VlcPlayerWidget*>(opaque);

    planes[0] = pthis->m_Back->bits();

    return pthis->m_Back;
}

void VlcPlayerWidget::unlock_cb(void *opaque, void *picture, void * const *planes)
{
    VlcPlayerWidget *pthis = static_cast<VlcPlayerWidget*>(opaque);

    QImage* p = pthis->m_Front;
    pthis->m_Front = pthis->m_Back;
    pthis->m_Back = p;

}

void VlcPlayerWidget::display_cb(void *opaque, void *picture)
{
    VlcPlayerWidget *pthis = static_cast<VlcPlayerWidget*>(opaque);

//    pthis->update();
}

unsigned VlcPlayerWidget::setup_cb(void **opaque, char *chroma, unsigned *width, unsigned *height, unsigned *pitches, unsigned *lines)
{
    VlcPlayerWidget *pthis = static_cast<VlcPlayerWidget*>(*opaque);
    assert(pthis);

    *chroma++='R';
    *chroma++='G';
    *chroma++='B';
    *chroma='A';

    pthis->m_Front = new QImage(*width,*height,QImage::Format_RGBA8888);
    pthis->m_Back = new QImage(*width,*height,QImage::Format_RGBA8888);

    pitches[0]=*width * 4;
    lines[0] = *height;

    return 1;
}

void VlcPlayerWidget::cleanup_cb(void *opaque)
{

}

void VlcPlayerWidget::paintEvent(QPaintEvent *event)
{
    QImage img;
    if(m_Front)
    {
        int x,y,w,h;
        if((width()/height())>(m_Front->width()/m_Front->height()))
        {
            img = m_Front->scaledToHeight(height());
        }
        else
        {
            img = m_Front->scaledToWidth(width());
        }
        w = img.width();
        h = img.height();
        x = (width()-w)/2;
        y = (height()-h)/2;
        QPainter draw(this);        //创建QPainter，将指针传入该设备
        QRect rect(x,y,w,h);  //创建绘图区域
        draw.drawImage(rect,img);
    }
    QWidget::paintEvent(event);
}
