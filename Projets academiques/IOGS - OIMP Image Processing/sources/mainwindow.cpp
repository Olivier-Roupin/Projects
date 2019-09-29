#include "mainwindow.h"

#include "image.h"
#include "binarize.h"
#include "inverse.h"
#include "scale.h"
#include "rgb2grayscale.h"
#include "rotation.h"
#include "colorpicknshift.h"
#include "colorpick.h"
#include "etalement.h"
#include "egalisation.h"
#include "sobelfilter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    entree = new QLabel;
    sortie = new QLabel;
    entree->setAlignment(Qt::AlignHCenter);
    sortie->setAlignment(Qt::AlignHCenter);
    ui->scroll_entree->setBackgroundRole(QPalette::Dark);
    ui->scroll_entree->setWidget(entree);
    ui->scroll_sortie->setBackgroundRole(QPalette::Dark);
    ui->scroll_sortie->setWidget(sortie);

    img = new Image();
    apercu = new Image();
    pipeline = new PipelineOperation();
}

MainWindow::~MainWindow()
{
    QFile::remove("histo.pbm");
    QFile::remove("apercu.pbm");
    QFile::remove("apercu.ppm");
    delete ui;
}

void MainWindow::on_actionOuvrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir Image"), ".", tr("Image Files (*.ppm *.pgm)"));
    if(fileName.isEmpty())
        return;
    on_actionFermer_triggered();
    ui->menuBar->setEnabled(false);
    ui->statusBar->showMessage(tr("Ouverture du fichier..."));
    QPixmap pixmap(fileName);

    img->load(fileName.toStdString());
    apercu->load(fileName.toStdString());
    entree->setPixmap(pixmap);
    sortie->setPixmap(pixmap);

    histogram = Histogram(*img);
    histogram.save();
    ui->histo->setPixmap(QPixmap("histo.pbm"));

    std::string Titre("OIMP - "+ (fileName.right(fileName.length()-1-fileName.lastIndexOf("/")).toStdString()));
    setWindowTitle(Titre.c_str());
    setWindowIcon(QIcon(pixmap));

    ui->actionEnregistrer_sous->setEnabled(true);
    ui->actionFermer->setEnabled(true);
    ui->Operations->setEnabled(true);
    ui->Parametres->setEnabled(true);

    ui->menuBar->setEnabled(true);
    ui->statusBar->clearMessage();

    return;
}

void MainWindow::on_actionEnregistrer_sous_triggered()
{
    QString fileName;
    if(apercu->getType() == Image::RGB)
        fileName = QFileDialog::getSaveFileName(this, tr("Sauver Image"), ".", tr("Image Files (*.ppm)"));
    else
        fileName = QFileDialog::getSaveFileName(this, tr("Sauver Image"), ".", tr("Image Files (*.pgm)"));
    if(fileName.isEmpty())
        return;

    ui->Parametres->setEnabled(false);
    ui->Operations->setEnabled(false);
    ui->menuBar->setEnabled(false);
    ui->statusBar->showMessage(tr("Enregistrement en cours..."));

    apercu->save(fileName.toStdString());

    ui->menuBar->setEnabled(true);
    ui->Operations->setEnabled(true);
    ui->Parametres->setEnabled(true);
    ui->statusBar->clearMessage();

    return;
}

void MainWindow::on_actionFermer_triggered()
{
    delete img;
    img = new Image();
    delete apercu;
    apercu = new Image();
    delete pipeline;
    pipeline = new PipelineOperation();
    entree->setPixmap(QPixmap());
    sortie->setPixmap(QPixmap());
    ui->histo->setPixmap(QPixmap());

    ui->actionEnregistrer_sous->setEnabled(false);
    ui->actionFermer->setEnabled(false);
    ui->Operations->setEnabled(false);
    ui->Parametres->setEnabled(false);
}

void MainWindow::appliquer(Operation* operation)
{
    ui->Parametres->setEnabled(false);
    ui->Operations->setEnabled(false);
    ui->menuBar->setEnabled(false);
    ui->statusBar->showMessage(tr("Traitement en cours..."));
    Image temp;
    operation->process(*apercu, temp);
    pipeline->addOperation(operation);

    ui->actionAnnuler->setEnabled(true);

    delete apercu;
    apercu = new Image(temp);

    if(apercu->getType() == Image::RGB)
        apercu->save("apercu.ppm");
    else
        apercu->save("apercu.pgm");

    if(apercu->getType() == Image::RGB)
        sortie->setPixmap(QPixmap("apercu.ppm"));
    else
        sortie->setPixmap(QPixmap("apercu.pgm"));

    histogram = Histogram(*apercu);
    histogram.save();
    ui->histo->setPixmap(QPixmap("histo.pbm"));

    ui->menuBar->setEnabled(true);
    ui->Operations->setEnabled(true);
    ui->Parametres->setEnabled(true);
    ui->statusBar->clearMessage();
}

void MainWindow::on_actionAnnuler_triggered()
{
    ui->Parametres->setEnabled(false);
    ui->Operations->setEnabled(false);
    ui->menuBar->setEnabled(false);
    ui->statusBar->showMessage(tr("Annulation en cours..."));

    pipeline->cancel();
    pipeline->process(*img, *apercu);
    if(pipeline->is_Empty())
        ui->actionAnnuler->setEnabled(false);

    if(apercu->getType() == Image::RGB)
        apercu->save("apercu.ppm");
    else
        apercu->save("apercu.pgm");

    if(apercu->getType() == Image::RGB)
        sortie->setPixmap(QPixmap("apercu.ppm"));
    else
        sortie->setPixmap(QPixmap("apercu.pgm"));

    histogram = Histogram(*apercu);
    histogram.save();
    ui->histo->setPixmap(QPixmap("histo.pbm"));

    ui->menuBar->setEnabled(true);
    ui->Operations->setEnabled(true);
    ui->Parametres->setEnabled(true);
    ui->statusBar->clearMessage();
}

void MainWindow::on_binarize_appliquer_clicked()
{
    Binarize* binarize = new Binarize(ui->jauge->value()/100.0);
    appliquer(binarize);
}

void MainWindow::on_rgb2grayscale_appliquer_clicked()
{
    RGB2GrayScale* rgb2grayscale = new RGB2GrayScale();
    appliquer(rgb2grayscale);
}

void MainWindow::on_inverse_appliquer_clicked()
{
    Inverse* inverse = new Inverse();
    appliquer(inverse);
}

void MainWindow::on_rotation_appliquer_clicked()
{
    Rotation* rotation = new Rotation(ui->angle_jauge->value());
    appliquer(rotation);
}

void MainWindow::on_colorpick_appliquer_clicked()
{
    ColorPick* colorpick = new ColorPick(ui->angle_couleur_jauge->value(),ui->largeur_jauge->value());
    appliquer(colorpick);
}

void MainWindow::on_colorshift_appliquer_clicked()
{
    if(ui->pick_choix->isChecked())
    {
        ColorPicknShift* colorpicknshift = new ColorPicknShift(ui->teinte_jauge->value(),ui->largeur_teinte_jauge->value(),ui->angle_shift_jauge->value());
        appliquer(colorpicknshift);
    }
    else
    {
        ColorShift* colorshift = new ColorShift(ui->angle_shift_jauge->value());
        appliquer(colorshift);
    }
}

void MainWindow::on_palette_button_clicked()
{
    QColor couleur;
    couleur.setHsl(ui->angle_couleur_jauge->value(),255,255);
    couleur = QColorDialog::getColor(couleur, this);
    if(couleur.isValid())
        ui->angle_couleur_jauge->setValue(couleur.hue());
}

void MainWindow::on_palette_shift_button_clicked()
{
    QColor couleur;
    couleur.setHsl(ui->teinte_jauge->value(),255,255);
    couleur = QColorDialog::getColor(couleur, this);
    if(couleur.isValid())
        ui->teinte_jauge->setValue(couleur.hue());
}

void MainWindow::on_etalement_appliquer_clicked()
{
    Etalement* etalement = new Etalement(histogram);
    appliquer(etalement);
}

void MainWindow::on_egalisation_appliquer_clicked()
{
    Egalisation* egalisation = new Egalisation(histogram);
    appliquer(egalisation);
}

void MainWindow::on_scale_appliquer_clicked()
{
    Scale* scale = new Scale(ui->coefficient_spin->value());
    appliquer(scale);
}

void MainWindow::on_sobelfilter_appliquer_clicked()
{
    SobelFilter* sobelfilter = new SobelFilter();
    appliquer(sobelfilter);
}

void MainWindow::on_angle_couleur_jauge_valueChanged(int value)
{
    QPalette pal = ui->pick_preview->palette();
    QColor color;
    QLinearGradient buttonGradient(0,0,ui->pick_preview->width(),0);
    int i;
    for(i = 0; i < 7; i++)
    {
        color.setHsv((value+(ui->largeur_jauge->value()*(i-3))/6+360)%360,255,255);
        buttonGradient.setColorAt(i/6.0,color);
    }
    pal.setBrush(QPalette::Active, QPalette::Background, buttonGradient);
    ui->pick_preview->setPalette(pal);
}

void MainWindow::on_largeur_jauge_valueChanged(int value)
{
    on_angle_couleur_jauge_valueChanged(ui->angle_couleur_jauge->value());
}

void MainWindow::on_angle_shift_jauge_valueChanged(int value)
{
    QPalette pal = ui->shifted_preview->palette();
    QColor color;
    QLinearGradient buttonGradient(0,0,ui->shifted_preview->width(),0);
    int i;
    for(i = 0; i < 7; i++)
    {
        color.setHsv((value+ui->teinte_jauge->value()+(ui->largeur_teinte_jauge->value()*(i-3))/6+360)%360,255,255);
        buttonGradient.setColorAt(i/6.0,color);
    }
    pal.setBrush(QPalette::Active, QPalette::Background, buttonGradient);
    ui->shifted_preview->setPalette(pal);
}

void MainWindow::on_teinte_jauge_valueChanged(int value)
{
    QPalette pal = ui->picked_preview->palette();
    QColor color;
    QLinearGradient buttonGradient(0,0,ui->picked_preview->width(),0);
    int i;
    for(i = 0; i < 7; i++)
    {
        color.setHsv((value+(ui->largeur_teinte_jauge->value()*(i-3))/6+360)%360,255,255);
        buttonGradient.setColorAt(i/6.0,color);
    }
    pal.setBrush(QPalette::Active, QPalette::Background, buttonGradient);
    ui->picked_preview->setPalette(pal);
    on_angle_shift_jauge_valueChanged(ui->angle_shift_jauge->value());
}

void MainWindow::on_largeur_teinte_jauge_valueChanged(int value)
{
    on_teinte_jauge_valueChanged(ui->teinte_jauge->value());
}
