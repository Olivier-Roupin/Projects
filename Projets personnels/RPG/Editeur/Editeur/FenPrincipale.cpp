#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{
    //Menu
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    /*QMenu *fichiersRecents = menuFichier->addMenu("Fichiers &récents");
    fichiersRecents->addAction("Fichier bidon 1.txt");
    fichiersRecents->addAction("Fichier bidon 2.txt");
    fichiersRecents->addAction("Fichier bidon 3.txt");*/

    QAction *actionEnregistrer = new QAction("&Enregistrer", this);
    actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
    menuFichier->addAction(actionEnregistrer);

    QAction *actionQuitter = new QAction("&Quitter", this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    menuFichier->addAction(actionQuitter);


    QMenu *menuEdition = menuBar()->addMenu("&Edition");
    QAction *actionGras = new QAction("&Gras", this);
    actionGras->setShortcut(QKeySequence("Ctrl+G"));
    actionGras->setCheckable(true);
    menuEdition->addAction(actionGras);

/*
    //Barre d'Outils
    QToolBar *toolBarFichier = addToolBar("Fichier");
    toolBarFichier->addAction(actionQuitter);

    toolBarFichier->addSeparator();

    QFontComboBox *choixPolice = new QFontComboBox;
    toolBarFichier->addWidget(choixPolice);
*/

    //Zone Centrale
    QWidget *zoneCentrale = new QWidget;

    QGridLayout *grille = new QGridLayout;

    QLineEdit *nom = new QLineEdit;

    QSpinBox *PVMAX = new QSpinBox;
    QSpinBox *PMMAX = new QSpinBox;

    QSpinBox *PV = new QSpinBox;
    QSpinBox *AP = new QSpinBox;
    QSpinBox *DP = new QSpinBox;

    QSpinBox *PM = new QSpinBox;
    QSpinBox *AM = new QSpinBox;
    QSpinBox *DM = new QSpinBox;

    QSpinBox *VIT = new QSpinBox;
    QSpinBox *PRE = new QSpinBox;
    QSpinBox *ESQ = new QSpinBox;

    QSpinBox *STATUS = new QSpinBox;
    QSpinBox *EXP = new QSpinBox;
    QSpinBox *NIV = new QSpinBox;

    QSpinBox *FOR = new QSpinBox;
    QSpinBox *INT = new QSpinBox;
    QSpinBox *AGI = new QSpinBox;
    QSpinBox *RANG = new QSpinBox;

    QSpinBox * = new QSpinBox;
    QSpinBox * = new QSpinBox;
    QSpinBox * = new QSpinBox;
    QSpinBox * = new QSpinBox;
    QSpinBox * = new QSpinBox;
    QSpinBox * = new QSpinBox;

/*
    QFormLayout *layout = new QFormLayout;
    layout->addRow("Votre nom", nom);
    layout->addRow("Votre prénom", prenom);
    layout->addRow("Votre âge", age);
*/

    zoneCentrale->setLayout(grille);

    setCentralWidget(zoneCentrale);

    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
}
