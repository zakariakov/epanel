#include "menufolders.h"
//#include <EIcon>
#include "utils/edir.h"
#include <QDesktopServices>
#include <QStyle>
#include <QSettings>
#include <QUrl>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFile>
MenuFolders::MenuFolders(QWidget *parent) :
    QMenu(parent)
{

    setTitle(tr("Folders"));
    setIcon(QIcon::fromTheme("folder"));
    chargeMenus();
    refreshIcons();
}
void MenuFolders::chargeMenus()
{

    actHomeFolder=new QAction(tr("Home"),this);
    actHomeFolder->setData(QDir::homePath());
    actHomeFolder->setIcon(QIcon::fromTheme("user-home",QIcon::fromTheme("folder-home")));
    connect(actHomeFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
    this->addAction(actHomeFolder);
    //مجلد سطح المكتب
    if(QFile::exists(Edir::desktopDir())){
        actDesktopFolder=new QAction(Edir::desktopDirName(),this);
        actDesktopFolder->setData(Edir::desktopDir());
        actDesktopFolder->setIcon(QIcon::fromTheme("user-desktop",QIcon::fromTheme("folder-desktop")));
        connect(actDesktopFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
        this->addAction(actDesktopFolder);
    }
    //مجلد الصوت
    if(QFile::exists(Edir::musicDir())){
        actMusicFolder=new QAction(Edir::musicDirName(),this);
        actMusicFolder->setData(Edir::musicDir());
        actMusicFolder->setIcon(QIcon::fromTheme("folder-music",QIcon::fromTheme("folder-sound")));
        connect(actMusicFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
        this->addAction(actMusicFolder);
    }
    //مجلد الصور
    if(QFile::exists(Edir::picturesDir())){
        actPicturesFolder=new QAction(Edir::picturesDirName(),this);
        actPicturesFolder->setData(Edir::picturesDir());
        actPicturesFolder->setIcon(QIcon::fromTheme("folder-images",QIcon::fromTheme("folder-image")));
        connect(actPicturesFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
        this->addAction(actPicturesFolder);
    }
    //مجلد المستندات
    if(QFile::exists(Edir::documentsDir())){
        actDocumentsFolder=new QAction(Edir::documentsDirName(),this);
        actDocumentsFolder->setData(Edir::documentsDir());
        actDocumentsFolder->setIcon(QIcon::fromTheme("folder-documents",QIcon::fromTheme("folder_documents")));
        connect(actDocumentsFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
        this->addAction(actDocumentsFolder);
    }
    //مجلد الفيديو
    if(QFile::exists(Edir::moviesDir())){
        actMoviesFolder=new QAction(Edir::moviesDirName(),this);
        actMoviesFolder->setData(Edir::moviesDir());
        actMoviesFolder->setIcon(QIcon::fromTheme("folder-video",QIcon::fromTheme("folder-videos")));
        connect(actMoviesFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
        this->addAction(actMoviesFolder);
    }
    //مجلد download
    if(QFile::exists(Edir::downloadDir())){
        actMoviesFolder=new QAction(Edir::downloadDirName(),this);
        actMoviesFolder->setData(Edir::downloadDir());
        actMoviesFolder->setIcon(QIcon::fromTheme("folder-download",QIcon::fromTheme("folder-downloads")));
        connect(actMoviesFolder, SIGNAL(triggered()), this, SLOT(execFolder()));
        this->addAction(actMoviesFolder);
    }

}
void MenuFolders::refreshIcons()
{

 //this->setIcon(EIcon::fromTheme("folder"));


}

void MenuFolders::execFolder()
{
  qDebug()<<"execFolder" ;


    QAction *action = qobject_cast<QAction *>(sender());

    QString costumBrowser=QString();

    QByteArray sS=qgetenv("DESKTOP_SESSION");

    if(sS=="elokab-session"){

        QSettings setting("elokab","elokabsettings");
        setting.beginGroup("DefaultBrowser");
         costumBrowser=(setting.value("BROWSER","elokab-fm").toString());
        setting.endGroup();

    }else{

        QSettings setting;
        setting.beginGroup("Menu");
        costumBrowser=(setting.value("Browser","").toString());
        setting.endGroup();
    }



    if(costumBrowser.isEmpty()||costumBrowser=="default") {
        //تشغيل مجلدات المستخدم كمجلد المستندات والصور وغيرها

        if (action){
            QString localDir=action->data().toString();


            qDebug()<<"defaultBrowser"<<localDir;

            QProcess p;
            p.startDetached(QString("xdg-open \"%1\"").arg(localDir));
        }
    }else{
        if (action){
            QString localDir=action->data().toString();

            QStringList list;


            list<<localDir;
            QProcess process;
            process.startDetached(costumBrowser,list);
            qDebug()<<"else"<<costumBrowser<<list ;
        }
    }

    //   this->hide();
}
