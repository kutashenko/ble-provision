//  ────────────────────────────────────────────────────────────
//                     ╔╗  ╔╗ ╔══╗      ╔════╗
//                     ║╚╗╔╝║ ╚╣╠╝      ║╔╗╔╗║
//                     ╚╗╚╝╔╝  ║║  ╔══╗ ╚╝║║╚╝
//                      ╚╗╔╝   ║║  ║╔╗║   ║║
//                       ║║   ╔╣╠╗ ║╚╝║   ║║
//                       ╚╝   ╚══╝ ╚══╝   ╚╝
//    ╔╗╔═╗                    ╔╗                     ╔╗
//    ║║║╔╝                   ╔╝╚╗                    ║║
//    ║╚╝╝  ╔══╗ ╔══╗ ╔══╗  ╔╗╚╗╔╝  ╔══╗ ╔╗ ╔╗╔╗ ╔══╗ ║║  ╔══╗
//    ║╔╗║  ║║═╣ ║║═╣ ║╔╗║  ╠╣ ║║   ║ ═╣ ╠╣ ║╚╝║ ║╔╗║ ║║  ║║═╣
//    ║║║╚╗ ║║═╣ ║║═╣ ║╚╝║  ║║ ║╚╗  ╠═ ║ ║║ ║║║║ ║╚╝║ ║╚╗ ║║═╣
//    ╚╝╚═╝ ╚══╝ ╚══╝ ║╔═╝  ╚╝ ╚═╝  ╚══╝ ╚╝ ╚╩╩╝ ║╔═╝ ╚═╝ ╚══╝
//                    ║║                         ║║
//                    ╚╝                         ╚╝
//
//    Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>
//  ────────────────────────────────────────────────────────────

#ifndef YIOT_ROOT_OF_TRUST_LIST_H
#define YIOT_ROOT_OF_TRUST_LIST_H

#include <QtCore>
#include <QHash>
#include <QAbstractTableModel>

#include <virgil/iot/qt/VSQIoTKit.h>
#include <yiot-iotkit/root-of-trust/KSQRoT.h>

class KSQRoTController : public QAbstractTableModel {
    Q_OBJECT
    enum Element { ID = Qt::UserRole,
                   Name,
                   Image,
                   TrustList,
                   ECType,
                   Recovery1, Recovery2,
                   Auth1, Auth2,
                   TL1, TL2,
                   Firmware1, Firmware2,
                   ElementMax };
public:
    KSQRoTController();
    virtual ~KSQRoTController() = default;

    bool
    isValid() const {
        return m_isValid;
    }

    /**
     * QAbstractTableModel implementation
     */
    int
    rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int
    columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant
    data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray>
    roleNames() const override;

public slots:

signals:

private:
    std::list<QSharedPointer<KSQRoT>> m_rots;
    bool m_isValid;

    bool
    prepare();

    QStringList
    loadRoTList();

    bool
    saveRoTList(const QStringList& list);

    vs_storage_element_id_t m_listStorageId;
};

#endif // YIOT_ROOT_OF_TRUST_LIST_H