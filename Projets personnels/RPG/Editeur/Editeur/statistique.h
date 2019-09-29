#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QWidgets>

class Statistique : public QWidget
{
    Q_OBJECT
public:
    explicit Statistique(QWidget *parent = 0);
    Statistique(QString nom);

signals:

public slots:


private:
    QLabel *m_label;
    QSpinBox *m_box;
};

#endif // STATISTIQUE_H
