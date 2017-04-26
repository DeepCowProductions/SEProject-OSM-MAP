#ifndef ROADSMODEL_H
#define ROADSMODEL_H

#include <QObject>

class RoadsModel : public QObject
{
    Q_OBJECT
public:
    explicit RoadsModel(QObject *parent = 0);

signals:

public slots:
};

#endif // ROADSMODEL_H