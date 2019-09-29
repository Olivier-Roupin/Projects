#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include "pipelineoperation.h"
#include "histogram.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionOuvrir_triggered();

    void on_actionEnregistrer_sous_triggered();

    void on_actionFermer_triggered();

    void on_binarize_appliquer_clicked();

    void on_rgb2grayscale_appliquer_clicked();

    void on_inverse_appliquer_clicked();

    void on_rotation_appliquer_clicked();

    void on_colorpick_appliquer_clicked();

    void on_colorshift_appliquer_clicked();

    void on_palette_button_clicked();

    void on_palette_shift_button_clicked();

    void on_etalement_appliquer_clicked();

    void on_egalisation_appliquer_clicked();

    void on_scale_appliquer_clicked();

    void on_sobelfilter_appliquer_clicked();

    void on_angle_couleur_jauge_valueChanged(int value);

    void on_largeur_jauge_valueChanged(int value);

    void on_angle_shift_jauge_valueChanged(int value);

    void on_teinte_jauge_valueChanged(int value);

    void on_largeur_teinte_jauge_valueChanged(int value);

    //void on_pick_choix_clicked(bool checked);

    void on_actionAnnuler_triggered();

private:
    void process();
    void appliquer(Operation* operation);

private:
    Image *img,*apercu;
    Histogram histogram;
    Ui::MainWindow *ui;
    PipelineOperation* pipeline;
    QLabel* entree;
    QLabel* sortie;
};

#endif // MAINWINDOW_H
